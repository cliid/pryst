#include "llvm_codegen.hpp"
#include "utils/debug.hpp"
#include "../generated/PrystLexer.h"
#include "../generated/PrystParser.h"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <string>

namespace pryst {

void LLVMCodegen::initializeModule() {
    context_ = std::make_unique<llvm::LLVMContext>();
    module_ = std::make_unique<llvm::Module>("pryst_module", *context_);
    builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
    typeRegistry_ = std::make_unique<LLVMTypeRegistry>(*context_);
    typeMetadata_ = std::make_unique<TypeMetadata>(*context_, *module_);
    currentFunction_ = nullptr;
}

std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(PrystParser::ProgramContext* ctx) {
    // Initialize module components
    context_ = std::make_unique<llvm::LLVMContext>();
    module_ = std::make_unique<llvm::Module>("pryst_module", *context_);
    builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
    typeRegistry_ = std::make_unique<LLVMTypeRegistry>(*context_);
    typeMetadata_ = std::make_unique<TypeMetadata>(*context_, *module_);
    declarePrintFunctions();
    visitProgram(ctx);

    // Verify module
    std::string errorInfo;
    llvm::raw_string_ostream errorStream(errorInfo);
    if (llvm::verifyModule(*module_, &errorStream)) {
        PRYST_ERROR("Module verification failed: " + errorInfo);
        return nullptr;
    }
    return std::move(module_);
}

std::any LLVMCodegen::visitProgram(PrystParser::ProgramContext *ctx) {
    PRYST_DEBUG("Visiting program");
    for (auto decl : ctx->declaration()) {
        visitDeclaration(decl);
    }
    return std::any();
}

std::any LLVMCodegen::visitDeclaration(PrystParser::DeclarationContext *ctx) {
    PRYST_DEBUG("Visiting declaration");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext *ctx) {
    PRYST_DEBUG("Visiting global using declaration");
    return std::any();
}

std::any LLVMCodegen::visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext *ctx) {
    PRYST_DEBUG("Visiting block scoped namespace declaration");
    return std::any();
}

std::any LLVMCodegen::visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext *ctx) {
    PRYST_DEBUG("Visiting block scoped module declaration");
    return std::any();
}

std::any LLVMCodegen::visitNamespaceDecl(PrystParser::NamespaceDeclContext *ctx) {
    PRYST_DEBUG("Visiting namespace declaration");
    return std::any();
}

std::any LLVMCodegen::visitModuleDecl(PrystParser::ModuleDeclContext *ctx) {
    PRYST_DEBUG("Visiting module declaration");
    return std::any();
}

std::any LLVMCodegen::visitImportDecl(PrystParser::ImportDeclContext *ctx) {
    PRYST_DEBUG("Visiting import declaration");
    return std::any();
}

std::any LLVMCodegen::visitImportPath(PrystParser::ImportPathContext *ctx) {
    PRYST_DEBUG("Visiting import path");
    return std::any();
}

// String handling
std::any LLVMCodegen::visitStringLiteral(PrystParser::StringLiteralContext *ctx) {
    PRYST_DEBUG("Visiting string literal");
    std::string result;
    for (auto part : ctx->stringPart()) {
        result += std::any_cast<std::string>(visit(part));
    }
    auto global = builder_->CreateGlobalString(result);
    auto zero = llvm::ConstantInt::get(*context_, llvm::APInt(32, 0));
    return builder_->CreateGEP(global->getValueType(), global, {zero, zero});
}

std::any LLVMCodegen::visitStringPart(PrystParser::StringPartContext *ctx) {
    PRYST_DEBUG("Visiting string part");
    if (ctx->STRING_CONTENT()) {
        return ctx->STRING_CONTENT()->getText();
    } else if (ctx->ESCAPE_SEQ()) {
        std::string escSeq = ctx->ESCAPE_SEQ()->getText();
        if (escSeq == "\\n") return std::string("\n");
        if (escSeq == "\\t") return std::string("\t");
        if (escSeq == "\\r") return std::string("\r");
        if (escSeq == "\\\"") return std::string("\"");
        if (escSeq == "\\\\") return std::string("\\");
        return escSeq.substr(1);
    } else if (ctx->expression()) {
        auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
        return typeRegistry_->convertToString(value, builder_.get());
    }
    return std::string();
}

// Class member declarations
std::any LLVMCodegen::visitClassVariableDecl(PrystParser::ClassVariableDeclContext *ctx) {
    PRYST_DEBUG("Visiting class variable declaration");
    auto type = typeRegistry_->getType(ctx->type());
    auto name = ctx->IDENTIFIER()->getText();
    auto value = ctx->expression() ? std::any_cast<llvm::Value*>(visit(ctx->expression())) : nullptr;

    // Create class member variable
    auto alloca = createEntryBlockAlloca(currentFunction_, name, type);
    if (value) {
        builder_->CreateStore(value, alloca);
    }
    namedValues_[name] = alloca;
    return std::any();
}

// Type conversions
std::any LLVMCodegen::visitTypeCastExpr(PrystParser::TypeCastExprContext *ctx) {
    PRYST_DEBUG("Visiting type cast expression");
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto targetType = typeRegistry_->getType(ctx->type());
    return typeRegistry_->convertType(value, targetType, builder_.get());
}

std::any LLVMCodegen::visitTypeConversionExpr(PrystParser::TypeConversionExprContext *ctx) {
    PRYST_DEBUG("Visiting type conversion expression");
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto targetType = typeRegistry_->getType(ctx->type());
    return typeRegistry_->convertType(value, targetType, builder_.get());
}

std::any LLVMCodegen::visitClassConversionExpr(PrystParser::ClassConversionExprContext *ctx) {
    PRYST_DEBUG("Visiting class conversion expression");
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto targetClassName = ctx->IDENTIFIER()->getText();
    auto targetType = typeRegistry_->getClassType(targetClassName);
    return typeRegistry_->convertClassType(value, targetType, builder_.get());
}

llvm::AllocaInst* LLVMCodegen::createEntryBlockAlloca(llvm::Function* function,
    const std::string& varName, llvm::Type* type) {
    llvm::IRBuilder<> tmpBuilder(&function->getEntryBlock(),
        function->getEntryBlock().begin());
    return tmpBuilder.CreateAlloca(type, nullptr, varName);
}

void LLVMCodegen::declarePrintFunctions() {
    // Print function declarations will be implemented in subsequent updates
}

llvm::Value* LLVMCodegen::generateGetType(llvm::Value* value) {
    if (!value) return nullptr;
    auto typeInfo = typeMetadata_->getTypeInfo(value);
    if (!typeInfo) return nullptr;
    auto global = builder_->CreateGlobalString(typeInfo->getName());
    auto zero = llvm::ConstantInt::get(*context_, llvm::APInt(32, 0));
    return builder_->CreateGEP(global->getValueType(), global, {zero, zero});
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    if (!value) return nullptr;
    auto typeInfo = typeMetadata_->getTypeInfo(value);
    if (!typeInfo) return nullptr;
    bool isInstance = (typeInfo->getName() == typeName);
    if (!isInstance && typeInfo->isClass()) {
        auto classType = std::dynamic_pointer_cast<ClassTypeInfo>(typeInfo);
        while (classType->getParent()) {
            classType = std::dynamic_pointer_cast<ClassTypeInfo>(classType->getParent());
            if (classType->getName() == typeName) {
                isInstance = true;
                break;
            }
        }
    }
    return llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context_), isInstance);
}

TypeInfoPtr LLVMCodegen::getTypeInfo(llvm::Value* value) const {
    return typeMetadata_->getTypeInfo(value);
}

void LLVMCodegen::attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) {
    typeMetadata_->addTypeInfo(value, typeInfo);
}

std::any LLVMCodegen::visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) {
    PRYST_DEBUG("Visiting function declaration");
    return visit(ctx->namedFunction());
}

std::any LLVMCodegen::visitNamedFunction(PrystParser::NamedFunctionContext *ctx) {
    PRYST_DEBUG("Visiting named function");
    auto name = ctx->IDENTIFIER()->getText();
    auto returnType = ctx->type() ? typeRegistry_->getType(ctx->type()) : llvm::Type::getVoidTy(*context_);

    // Process parameters
    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(typeRegistry_->getType(param->type()));
            paramNames.push_back(param->IDENTIFIER()->getText());
        }
    }

    // Create function type and declaration
    auto functionType = llvm::FunctionType::get(returnType, paramTypes, false);
    auto function = llvm::Function::Create(
        functionType, llvm::Function::ExternalLinkage,
        name, module_.get()
    );

    // Set parameter names
    unsigned idx = 0;
    for (auto &arg : function->args()) {
        arg.setName(paramNames[idx++]);
    }

    // Create basic block and generate body
    auto bb = llvm::BasicBlock::Create(*context_, "entry", function);
    builder_->SetInsertPoint(bb);

    // Save current function and create new scope
    auto savedFunction = currentFunction_;
    currentFunction_ = function;

    // Process function body
    if (ctx->functionBody()) {
        visit(ctx->functionBody());
    }

    // Restore previous function
    currentFunction_ = savedFunction;

    // Verify function
    llvm::verifyFunction(*function);
    return std::any();
}

std::any LLVMCodegen::visitClassDeclaration(PrystParser::ClassDeclarationContext *ctx) {
    PRYST_DEBUG("Visiting class declaration");
    auto className = ctx->IDENTIFIER()->getText();
    auto classType = typeRegistry_->createClassType(className);

    // Handle inheritance
    if (ctx->type()) {
        auto parentType = typeRegistry_->getType(ctx->type());
        typeRegistry_->setParentType(classType, parentType);
    }

    // Process class body
    if (ctx->classBody()) {
        visit(ctx->classBody());
    }

    return std::any();
}

std::any LLVMCodegen::visitLambdaFunction(PrystParser::LambdaFunctionContext *ctx) {
    PRYST_DEBUG("Visiting lambda function");
    auto returnType = ctx->type() ? typeRegistry_->getType(ctx->type()) : llvm::Type::getVoidTy(*context_);

    // Process parameters
    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(typeRegistry_->getType(param->type()));
            paramNames.push_back(param->IDENTIFIER()->getText());
        }
    }

    // Create unique name for lambda
    static int lambdaCounter = 0;
    std::string name = "lambda_" + std::to_string(lambdaCounter++);

    // Create function type and declaration
    auto functionType = llvm::FunctionType::get(returnType, paramTypes, false);
    auto function = llvm::Function::Create(
        functionType, llvm::Function::ExternalLinkage,
        name, module_.get()
    );

    // Set parameter names
    unsigned idx = 0;
    for (auto &arg : function->args()) {
        arg.setName(paramNames[idx++]);
    }

    // Create basic block and generate body
    auto bb = llvm::BasicBlock::Create(*context_, "entry", function);
    builder_->SetInsertPoint(bb);

    // Save current function and create new scope
    auto savedFunction = currentFunction_;
    currentFunction_ = function;

    // Process function body
    if (ctx->functionBody()) {
        visit(ctx->functionBody());
    }

    // Restore previous function
    currentFunction_ = savedFunction;

    // Verify function
    llvm::verifyFunction(*function);
    return function;
}

std::any LLVMCodegen::visitFunctionBody(PrystParser::FunctionBodyContext *ctx) {
    PRYST_DEBUG("Visiting function body");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitParamList(PrystParser::ParamListContext *ctx) {
    PRYST_DEBUG("Visiting parameter list");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitParam(PrystParser::ParamContext *ctx) {
    PRYST_DEBUG("Visiting parameter");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitParamTypeList(PrystParser::ParamTypeListContext *ctx) {
    PRYST_DEBUG("Visiting parameter type list");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitTryCatchStatement(PrystParser::TryCatchStatementContext *ctx) {
    PRYST_DEBUG("Visiting try-catch statement");

    // Create basic blocks for try, catch, and continue
    auto tryBlock = llvm::BasicBlock::Create(*context_, "try", currentFunction_);
    auto catchBlock = llvm::BasicBlock::Create(*context_, "catch", currentFunction_);
    auto continueBlock = llvm::BasicBlock::Create(*context_, "continue", currentFunction_);

    // Set up exception handling
    auto personality = module_->getOrInsertFunction("__gxx_personality_v0",
        llvm::FunctionType::get(llvm::Type::getInt32Ty(*context_), true));
    currentFunction_->setPersonalityFn(personality.getCallee());

    // Generate try block code
    builder_->CreateBr(tryBlock);
    builder_->SetInsertPoint(tryBlock);
    visit(ctx->statement(0));
    builder_->CreateBr(continueBlock);

    // Generate catch block code
    builder_->SetInsertPoint(catchBlock);
    if (ctx->type()) {
        auto catchType = typeRegistry_->getType(ctx->type());
        auto catchVar = ctx->IDENTIFIER()->getText();
        auto alloca = createEntryBlockAlloca(currentFunction_, catchVar, catchType);
        namedValues_[catchVar] = alloca;
        visit(ctx->statement(1));
    }
    builder_->CreateBr(continueBlock);

    // Continue block
    builder_->SetInsertPoint(continueBlock);
    return std::any();
}

std::any LLVMCodegen::visitLogicOr(PrystParser::LogicOrContext *ctx) {
    PRYST_DEBUG("Visiting logic OR expression");
    auto left = std::any_cast<llvm::Value*>(visit(ctx->logicAnd(0)));

    for (size_t i = 1; i < ctx->logicAnd().size(); i++) {
        auto right = std::any_cast<llvm::Value*>(visit(ctx->logicAnd(i)));
        left = builder_->CreateOr(left, right, "ortmp");
    }
    return left;
}

std::any LLVMCodegen::visitLogicAnd(PrystParser::LogicAndContext *ctx) {
    PRYST_DEBUG("Visiting logic AND expression");
    auto left = std::any_cast<llvm::Value*>(visit(ctx->equality(0)));

    for (size_t i = 1; i < ctx->equality().size(); i++) {
        auto right = std::any_cast<llvm::Value*>(visit(ctx->equality(i)));
        left = builder_->CreateAnd(left, right, "andtmp");
    }
    return left;
}

std::any LLVMCodegen::visitEquality(PrystParser::EqualityContext *ctx) {
    PRYST_DEBUG("Visiting equality expression");
    auto left = std::any_cast<llvm::Value*>(visit(ctx->comparison(0)));

    for (size_t i = 1; i < ctx->comparison().size(); i++) {
        auto right = std::any_cast<llvm::Value*>(visit(ctx->comparison(i)));
        auto op = ctx->NOT_EQUAL() ? builder_->CreateICmpNE(left, right, "neqtmp")
                                 : builder_->CreateICmpEQ(left, right, "eqtmp");
        left = op;
    }
    return left;
}

std::any LLVMCodegen::visitComparison(PrystParser::ComparisonContext *ctx) {
    PRYST_DEBUG("Visiting comparison expression");
    auto left = std::any_cast<llvm::Value*>(visit(ctx->addition(0)));

    for (size_t i = 1; i < ctx->addition().size(); i++) {
        auto right = std::any_cast<llvm::Value*>(visit(ctx->addition(i)));
        llvm::Value* op;
        if (ctx->LESS()) op = builder_->CreateICmpSLT(left, right, "cmptmp");
        else if (ctx->LESS_EQUAL()) op = builder_->CreateICmpSLE(left, right, "cmptmp");
        else if (ctx->GREATER()) op = builder_->CreateICmpSGT(left, right, "cmptmp");
        else op = builder_->CreateICmpSGE(left, right, "cmptmp");
        left = op;
    }
    return left;
}

// Expression visitor methods
std::any LLVMCodegen::visitAddition(PrystParser::AdditionContext *ctx) {
    PRYST_DEBUG("Visiting addition expression");
    auto left = std::any_cast<llvm::Value*>(visit(ctx->multiplication(0)));

    for (size_t i = 1; i < ctx->multiplication().size(); i++) {
        auto right = std::any_cast<llvm::Value*>(visit(ctx->multiplication(i)));
        if (ctx->PLUS()) {
            left = builder_->CreateAdd(left, right, "addtmp");
        } else {
            left = builder_->CreateSub(left, right, "subtmp");
        }
    }
    return left;
}

std::any LLVMCodegen::visitMultiplication(PrystParser::MultiplicationContext *ctx) {
    PRYST_DEBUG("Visiting multiplication expression");
    auto left = std::any_cast<llvm::Value*>(visit(ctx->unary(0)));

    for (size_t i = 1; i < ctx->unary().size(); i++) {
        auto right = std::any_cast<llvm::Value*>(visit(ctx->unary(i)));
        if (ctx->STAR()) {
            left = builder_->CreateMul(left, right, "multmp");
        } else if (ctx->SLASH()) {
            left = builder_->CreateSDiv(left, right, "divtmp");
        } else {
            left = builder_->CreateSRem(left, right, "modtmp");
        }
    }
    return left;
}

std::any LLVMCodegen::visitUnary(PrystParser::UnaryContext *ctx) {
    PRYST_DEBUG("Visiting unary expression");
    if (ctx->BANG()) {
        auto operand = std::any_cast<llvm::Value*>(visit(ctx->unary()));
        return builder_->CreateNot(operand, "nottmp");
    } else if (ctx->MINUS()) {
        auto operand = std::any_cast<llvm::Value*>(visit(ctx->unary()));
        return builder_->CreateNeg(operand, "negtmp");
    } else if (ctx->INCREMENT()) {
        auto operand = std::any_cast<llvm::Value*>(visit(ctx->unary()));
        auto result = builder_->CreateAdd(operand, llvm::ConstantInt::get(*context_, llvm::APInt(32, 1)), "inctmp");
        builder_->CreateStore(result, operand);
        return result;
    } else if (ctx->DECREMENT()) {
        auto operand = std::any_cast<llvm::Value*>(visit(ctx->unary()));
        auto result = builder_->CreateSub(operand, llvm::ConstantInt::get(*context_, llvm::APInt(32, 1)), "dectmp");
        builder_->CreateStore(result, operand);
        return result;
    }
    return visit(ctx->postfix());
}

std::any LLVMCodegen::visitPostfix(PrystParser::PostfixContext *ctx) {
    PRYST_DEBUG("Visiting postfix expression");
    auto expr = std::any_cast<llvm::Value*>(visit(ctx->primary()));

    if (ctx->INCREMENT()) {
        auto oldValue = builder_->CreateLoad(expr->getType()->getPointerElementType(), expr);
        auto newValue = builder_->CreateAdd(oldValue, llvm::ConstantInt::get(*context_, llvm::APInt(32, 1)));
        builder_->CreateStore(newValue, expr);
        return oldValue;
    } else if (ctx->DECREMENT()) {
        auto oldValue = builder_->CreateLoad(expr->getType()->getPointerElementType(), expr);
        auto newValue = builder_->CreateSub(oldValue, llvm::ConstantInt::get(*context_, llvm::APInt(32, 1)));
        builder_->CreateStore(newValue, expr);
        return oldValue;
    }

    return expr;
}

std::any LLVMCodegen::visitCall(PrystParser::CallContext *ctx) {
    PRYST_DEBUG("Visiting call expression");
    auto callee = std::any_cast<llvm::Value*>(visit(ctx->primary()));

    std::vector<llvm::Value*> args;
    if (ctx->arguments()) {
        for (auto arg : ctx->arguments()->expression()) {
            args.push_back(std::any_cast<llvm::Value*>(visit(arg)));
        }
    }

    if (auto func = llvm::dyn_cast<llvm::Function>(callee)) {
        return builder_->CreateCall(func, args);
    } else {
        // Handle member function calls
        auto funcPtr = builder_->CreateBitCast(callee, llvm::FunctionType::get(
            llvm::Type::getVoidTy(*context_), false)->getPointerTo());
        return builder_->CreateCall(funcPtr, args);
    }
}

std::any LLVMCodegen::visitPrimary(PrystParser::PrimaryContext *ctx) {
    PRYST_DEBUG("Visiting primary expression");
    if (ctx->INTEGER()) {
        int value = std::stoi(ctx->INTEGER()->getText());
        return (llvm::Value*)llvm::ConstantInt::get(*context_, llvm::APInt(32, value));
    } else if (ctx->FLOAT()) {
        double value = std::stod(ctx->FLOAT()->getText());
        return (llvm::Value*)llvm::ConstantFP::get(*context_, llvm::APFloat(value));
    } else if (ctx->STRING()) {
        return visit(ctx->stringLiteral());
    } else if (ctx->TRUE()) {
        return (llvm::Value*)llvm::ConstantInt::get(*context_, llvm::APInt(1, 1));
    } else if (ctx->FALSE()) {
        return (llvm::Value*)llvm::ConstantInt::get(*context_, llvm::APInt(1, 0));
    } else if (ctx->IDENTIFIER()) {
        std::string name = ctx->IDENTIFIER()->getText();
        if (auto val = namedValues_[name]) {
            return builder_->CreateLoad(val->getType()->getPointerElementType(), val, name.c_str());
        }
        PRYST_ERROR("Unknown variable name: " + name);
        return nullptr;
    } else if (ctx->expression()) {
        return visit(ctx->expression());
    }
    return nullptr;
}
