#include "llvm_codegen.hpp"
#include "llvm_utils.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>

namespace pryst {

std::any LLVMCodegen::visitProgram(PrystParser::ProgramContext* ctx) {
    PRYST_DEBUG("Visiting program");

    // Process all declarations in the program
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    return nullptr;
}

std::any LLVMCodegen::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    PRYST_DEBUG("Visiting declaration");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitBlockStatement(PrystParser::BlockStatementContext* ctx) {
    PRYST_DEBUG("Visiting block statement");

    // Create a new scope for the block
    builder->CreateAlloca(llvm::Type::getInt32Ty(*context), nullptr, "block_scope");

    // Visit all statements in the block
    for (auto stmt : ctx->statement()) {
        visit(stmt);
    }

    return nullptr;
}

std::any LLVMCodegen::visitStatement(PrystParser::StatementContext* ctx) {
    PRYST_DEBUG("Visiting statement");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitExprStatement(PrystParser::ExprStatementContext* ctx) {
    PRYST_DEBUG("Visiting expression statement");
    return visit(ctx->expression());
}

std::any LLVMCodegen::visitCall(PrystParser::CallContext* ctx) {
    PRYST_DEBUG("Visiting function call");

    // Get callee name
    std::string calleeName = ctx->callee->getText();

    // Handle print function specially
    if (calleeName == "print") {
        std::vector<llvm::Value*> args;

        // If no arguments, call empty print
        if (ctx->arguments.empty()) {
            auto printEmptyFn = printFunctions["empty"];
            if (!printEmptyFn) {
                throw std::runtime_error("Print function for empty call not found");
            }
            return builder->CreateCall(printEmptyFn);
        }

        // Process all arguments
        for (auto arg : ctx->arguments) {
            std::any argResult = visit(arg);
            llvm::Value* argValue = std::any_cast<llvm::Value*>(argResult);

            // Get argument type
            llvm::Type* argType = argValue->getType();
            std::string typeName;

            if (argType->isIntegerTy(32)) typeName = "int";
            else if (argType->isDoubleTy()) typeName = "float";
            else if (argType->isPointerTy()) typeName = "str";
            else if (argType->isIntegerTy(1)) typeName = "bool";
            else throw std::runtime_error("Unsupported type for print");

            // Get corresponding print function
            auto printFn = printFunctions[typeName];
            if (!printFn) {
                throw std::runtime_error("Print function for type " + typeName + " not found");
            }

            // Create the call
            builder->CreateCall(printFn, {argValue});
        }

        return nullptr;
    }

    // Handle normal function calls
    auto callee = functions.find(calleeName);
    if (callee == functions.end()) {
        throw std::runtime_error("Unknown function: " + calleeName);
    }

    llvm::Function* function = callee->second;

    // Verify argument count
    if (function->arg_size() != ctx->arguments.size()) {
        throw std::runtime_error("Incorrect number of arguments for function " + calleeName);
    }

    // Process arguments
    std::vector<llvm::Value*> args;
    auto argIt = function->arg_begin();

    for (size_t i = 0; i < ctx->arguments.size(); i++, argIt++) {
        std::any argResult = visit(ctx->arguments[i]);
        llvm::Value* argValue = std::any_cast<llvm::Value*>(argResult);

        // Perform type conversion if needed
        llvm::Type* expectedType = argIt->getType();
        if (argValue->getType() != expectedType) {
            argValue = createCastInstruction(argValue, expectedType);
        }

        args.push_back(argValue);
    }

    // Create the function call
    return builder->CreateCall(function, args, "calltmp");
}

std::any LLVMCodegen::visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) {
    std::any exprResult = visit(ctx->expression());
    llvm::Value* value = std::any_cast<llvm::Value*>(exprResult);
    std::string targetType = ctx->type()->getText();

    return convertValue(value, targetType);
}

std::any LLVMCodegen::visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) {
    std::any exprResult = visit(ctx->expression());
    llvm::Value* value = std::any_cast<llvm::Value*>(exprResult);
    std::string targetClassName = ctx->IDENTIFIER()->getText();

    // Get class info for target class
    auto classInfo = getClassInfo(targetClassName);
    if (!classInfo) {
        throw std::runtime_error("Unknown class: " + targetClassName);
    }

    // Call conversion method if it exists
    std::string convMethodName = "c!" + targetClassName;
    return generateMethodCall(value, convMethodName, {});
}

bool LLVMCodegen::isClassType(const std::string& typeName) {
    return classTypes.find(typeName) != classTypes.end();
}

ClassTypeInfo* LLVMCodegen::getClassInfo(const std::string& className) {
    auto it = classTypes.find(className);
    if (it == classTypes.end()) {
        return nullptr;
    }
    return it->second.get();
}

llvm::Value* LLVMCodegen::convertValue(llvm::Value* value, const std::string& targetType) {
    if (!value) return nullptr;

    llvm::Type* sourceType = value->getType();
    llvm::Type* destType = getLLVMType(targetType);

    if (sourceType == destType) return value;

    // Get type information from registry using our type tracking system
    auto& registry = TypeRegistry::getInstance();
    TypeInfoPtr sourceTypeInfo = getTypeInfo(value);
    TypeInfoPtr destTypeInfo = registry.lookupType(targetType);

    // Handle numeric conversions
    if (sourceType->isIntegerTy() && destType->isDoubleTy()) {
        return builder->CreateSIToFP(value, destType, "int_to_double");
    }
    if (sourceType->isDoubleTy() && destType->isIntegerTy()) {
        return builder->CreateFPToSI(value, destType, "double_to_int");
    }

    // Handle string conversions
    if (destTypeInfo && destTypeInfo->getKind() == TypeKind::String) {
        return convertToString(value);
    }
    if (sourceTypeInfo && sourceTypeInfo->getKind() == TypeKind::String) {
        return convertFromString(value, destType);
    }

    throw std::runtime_error("Unsupported type conversion from " +
                           (sourceTypeInfo ? sourceTypeInfo->getTypeName() : "unknown") +
                           " to " + targetType);
}

llvm::Value* LLVMCodegen::generateMethodCall(llvm::Value* object, const std::string& methodName,
                                           const std::vector<llvm::Value*>& args) {
    if (!object) {
        throw std::runtime_error("Cannot call method on null object");
    }

    llvm::Type* objectType = object->getType();
    auto& registry = TypeRegistry::getInstance();
    TypeInfoPtr typeInfo = getTypeInfo(object);

    if (!typeInfo || typeInfo->getKind() != TypeKind::Class) {
        throw std::runtime_error("Method calls are only supported on class instances");
    }

    std::string className = typeInfo->getTypeName();
    auto classInfo = getClassInfo(className);
    if (!classInfo) {
        throw std::runtime_error("Unknown class type: " + className);
    }

    // Build method name with class prefix
    std::string fullMethodName = className + "_" + methodName;
    auto methodIt = functions.find(fullMethodName);
    if (methodIt == functions.end()) {
        throw std::runtime_error("Method not found: " + methodName + " in class " + className);
    }

    llvm::Function* method = methodIt->second;

    // Prepare arguments, including 'this' pointer
    std::vector<llvm::Value*> callArgs;
    callArgs.push_back(object);  // 'this' pointer
    callArgs.insert(callArgs.end(), args.begin(), args.end());

    // Create method call using LLVM 20.0.0 compatible API
    llvm::FunctionType* funcType = method->getFunctionType();
    return builder->CreateCall(funcType, method, callArgs, "method_call");
}

// Expression-related visitor methods
std::any LLVMCodegen::visitLogicOr(PrystParser::LogicOrContext* ctx) {
    PRYST_DEBUG("Visiting logic OR");

    // Create basic blocks for the right operand and merge
    llvm::Function* function = builder->GetInsertBlock()->getParent();
    llvm::BasicBlock* rightBB = llvm::BasicBlock::Create(*context, "or.right", function);
    llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(*context, "or.merge", function);

    // Visit left operand
    std::any leftResult = visit(ctx->logicAnd(0));
    llvm::Value* leftValue = std::any_cast<llvm::Value*>(leftResult);

    // Short circuit: if left is true, skip right operand
    builder->CreateCondBr(leftValue, mergeBB, rightBB);

    // Right operand
    builder->SetInsertPoint(rightBB);
    std::any rightResult = visit(ctx->logicAnd(1));
    llvm::Value* rightValue = std::any_cast<llvm::Value*>(rightResult);
    builder->CreateBr(mergeBB);

    // Merge block
    builder->SetInsertPoint(mergeBB);
    llvm::PHINode* phi = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "or.result");
    phi->addIncoming(leftValue, builder->GetInsertBlock());
    phi->addIncoming(rightValue, rightBB);

    return phi;
}

std::any LLVMCodegen::visitLogicAnd(PrystParser::LogicAndContext* ctx) {
    PRYST_DEBUG("Visiting logic AND");

    // Create basic blocks for the right operand and merge
    llvm::Function* function = builder->GetInsertBlock()->getParent();
    llvm::BasicBlock* rightBB = llvm::BasicBlock::Create(*context, "and.right", function);
    llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(*context, "and.merge", function);

    // Visit left operand
    std::any leftResult = visit(ctx->logicOr(0));
    llvm::Value* leftValue = std::any_cast<llvm::Value*>(leftResult);

    // Short circuit: if left is false, skip right operand
    builder->CreateCondBr(leftValue, rightBB, mergeBB);

    // Right operand
    builder->SetInsertPoint(rightBB);
    std::any rightResult = visit(ctx->logicOr(1));
    llvm::Value* rightValue = std::any_cast<llvm::Value*>(rightResult);
    builder->CreateBr(mergeBB);

    // Merge block
    builder->SetInsertPoint(mergeBB);
    llvm::PHINode* phi = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "and.result");
    phi->addIncoming(llvm::ConstantInt::getFalse(*context), builder->GetInsertBlock());
    phi->addIncoming(rightValue, rightBB);

    return phi;
}

// Arithmetic operation visitor methods
std::any LLVMCodegen::visitAddition(PrystParser::AdditionContext* ctx) {
    PRYST_DEBUG("Visiting addition");

    std::any leftResult = visit(ctx->multiplication(0));
    std::any rightResult = visit(ctx->multiplication(1));

    llvm::Value* leftValue = std::any_cast<llvm::Value*>(leftResult);
    llvm::Value* rightValue = std::any_cast<llvm::Value*>(rightResult);

    // Get types
    llvm::Type* leftType = leftValue->getType();
    llvm::Type* rightType = rightValue->getType();

    // Handle string concatenation
    if (leftType->isPointerTy() || rightType->isPointerTy()) {
        if (!leftType->isPointerTy()) {
            leftValue = convertToString(leftValue);
        }
        if (!rightType->isPointerTy()) {
            rightValue = convertToString(rightValue);
        }
        return generateMethodCall(leftValue, "concat", {rightValue});
    }

    // Handle numeric addition
    if (leftType->isDoubleTy() || rightType->isDoubleTy()) {
        if (!leftType->isDoubleTy()) {
            leftValue = builder->CreateSIToFP(leftValue, llvm::Type::getDoubleTy(*context));
        }
        if (!rightType->isDoubleTy()) {
            rightValue = builder->CreateSIToFP(rightValue, llvm::Type::getDoubleTy(*context));
        }
        return builder->CreateFAdd(leftValue, rightValue, "addtmp");
    }

    // Integer addition
    return builder->CreateAdd(leftValue, rightValue, "addtmp");
}

std::any LLVMCodegen::visitMultiplication(PrystParser::MultiplicationContext* ctx) {
    PRYST_DEBUG("Visiting multiplication");

    std::any leftResult = visit(ctx->unary(0));
    std::any rightResult = visit(ctx->unary(1));

    llvm::Value* leftValue = std::any_cast<llvm::Value*>(leftResult);
    llvm::Value* rightValue = std::any_cast<llvm::Value*>(rightResult);

    // Get types
    llvm::Type* leftType = leftValue->getType();
    llvm::Type* rightType = rightValue->getType();

    // Handle floating-point multiplication
    if (leftType->isDoubleTy() || rightType->isDoubleTy()) {
        if (!leftType->isDoubleTy()) {
            leftValue = builder->CreateSIToFP(leftValue, llvm::Type::getDoubleTy(*context));
        }
        if (!rightType->isDoubleTy()) {
            rightValue = builder->CreateSIToFP(rightValue, llvm::Type::getDoubleTy(*context));
        }
        return builder->CreateFMul(leftValue, rightValue, "multmp");
    }

    // Integer multiplication
    return builder->CreateMul(leftValue, rightValue, "multmp");
}

std::any LLVMCodegen::visitTryStmtWrapper(PrystParser::TryStmtWrapperContext* ctx) {
    PRYST_DEBUG("Visiting try-catch statement");

    // Create basic blocks for try, catch, and continue
    llvm::Function* function = builder->GetInsertBlock()->getParent();
    llvm::BasicBlock* tryBlock = llvm::BasicBlock::Create(*context, "try", function);
    llvm::BasicBlock* catchBlock = llvm::BasicBlock::Create(*context, "catch", function);
    llvm::BasicBlock* continueBlock = llvm::BasicBlock::Create(*context, "continue", function);

    // Create landing pad for exception handling
    builder->CreateBr(tryBlock);
    builder->SetInsertPoint(tryBlock);

    // Visit try block
    visit(ctx->statement());
    if (!builder->GetInsertBlock()->getTerminator()) {
        builder->CreateBr(continueBlock);
    }

    // Visit catch blocks
    for (auto catchCtx : ctx->catchBlock()) {
        visit(catchCtx);
    }

    // Continue block
    builder->SetInsertPoint(continueBlock);
    return nullptr;
}

std::any LLVMCodegen::visitStringLiteralRule(PrystParser::StringLiteralRuleContext* ctx) {
    PRYST_DEBUG("Visiting string literal");

    std::vector<llvm::Value*> parts;

    // Process string parts
    for (auto part : ctx->stringPart()) {
        std::any partResult = visit(part);
        parts.push_back(std::any_cast<llvm::Value*>(partResult));
    }

    // Concatenate all parts
    llvm::Value* result = parts[0];
    for (size_t i = 1; i < parts.size(); i++) {
        result = generateMethodCall(result, "concat", {parts[i]});
    }

    return result;
}

std::any LLVMCodegen::visitNamespaceDecl(PrystParser::NamespaceDeclContext* ctx) {
    PRYST_DEBUG("Visiting namespace declaration");

    std::string namespaceName = ctx->IDENTIFIER()->getText();
    currentNamespace = namespaceName;

    // Visit all declarations in namespace
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    currentNamespace.clear();
    return nullptr;
}

std::any LLVMCodegen::visitModuleDecl(PrystParser::ModuleDeclContext* ctx) {
    PRYST_DEBUG("Visiting module declaration");

    std::string moduleName = ctx->IDENTIFIER()->getText();
    currentModule = moduleName;

    // Visit all declarations in module
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    currentModule.clear();
    return nullptr;
}

std::any LLVMCodegen::visitImportDecl(PrystParser::ImportDeclContext* ctx) {
    PRYST_DEBUG("Visiting import declaration");

    std::string importPath;
    for (auto id : ctx->IDENTIFIER()) {
        if (!importPath.empty()) importPath += "::";
        importPath += id->getText();
    }

    // Register imported module
    importedModules.insert(importPath);
    return nullptr;
}

std::any LLVMCodegen::visitUsingDecl(PrystParser::UsingDeclContext* ctx) {
    PRYST_DEBUG("Visiting using declaration");

    std::string target = ctx->IDENTIFIER()->getText();
    if (ctx->MODULE()) {
        // Using module declaration
        activeModules.insert(target);
    } else {
        // Using namespace declaration
        activeNamespaces.insert(target);
    }

    return nullptr;
}

// Comparison operation visitor methods
std::any LLVMCodegen::visitEquality(PrystParser::EqualityContext* ctx) {
    PRYST_DEBUG("Visiting equality");

    std::any leftResult = visit(ctx->comparison(0));
    std::any rightResult = visit(ctx->comparison(1));

    llvm::Value* leftValue = std::any_cast<llvm::Value*>(leftResult);
    llvm::Value* rightValue = std::any_cast<llvm::Value*>(rightResult);

    // Get types
    llvm::Type* leftType = leftValue->getType();
    llvm::Type* rightType = rightValue->getType();

    // Handle string comparison
    if (leftType->isPointerTy() || rightType->isPointerTy()) {
        if (!leftType->isPointerTy()) {
            leftValue = convertToString(leftValue);
        }
        if (!rightType->isPointerTy()) {
            rightValue = convertToString(rightValue);
        }
        // Call string comparison method
        auto result = generateMethodCall(leftValue, "equals", {rightValue});
        return ctx->op->getType() == PrystParser::NOT_EQUAL ?
            builder->CreateNot(result) : result;
    }

    // Handle floating-point comparison
    if (leftType->isDoubleTy() || rightType->isDoubleTy()) {
        if (!leftType->isDoubleTy()) {
            leftValue = builder->CreateSIToFP(leftValue, llvm::Type::getDoubleTy(*context));
        }
        if (!rightType->isDoubleTy()) {
            rightValue = builder->CreateSIToFP(rightValue, llvm::Type::getDoubleTy(*context));
        }
        if (ctx->op->getType() == PrystParser::EQUAL) {
            return builder->CreateFCmpOEQ(leftValue, rightValue, "eqtmp");
        } else {
            return builder->CreateFCmpONE(leftValue, rightValue, "netmp");
        }
    }

    // Integer comparison
    if (ctx->op->getType() == PrystParser::EQUAL) {
        return builder->CreateICmpEQ(leftValue, rightValue, "eqtmp");
    } else {
        return builder->CreateICmpNE(leftValue, rightValue, "netmp");
    }
}

std::any LLVMCodegen::visitComparison(PrystParser::ComparisonContext* ctx) {
    PRYST_DEBUG("Visiting comparison");

    std::any leftResult = visit(ctx->addition(0));
    std::any rightResult = visit(ctx->addition(1));

    llvm::Value* leftValue = std::any_cast<llvm::Value*>(leftResult);
    llvm::Value* rightValue = std::any_cast<llvm::Value*>(rightResult);

    // Get types
    llvm::Type* leftType = leftValue->getType();
    llvm::Type* rightType = rightValue->getType();

    // Handle floating-point comparison
    if (leftType->isDoubleTy() || rightType->isDoubleTy()) {
        if (!leftType->isDoubleTy()) {
            leftValue = builder->CreateSIToFP(leftValue, llvm::Type::getDoubleTy(*context));
        }
        if (!rightType->isDoubleTy()) {
            rightValue = builder->CreateSIToFP(rightValue, llvm::Type::getDoubleTy(*context));
        }

        switch (ctx->op->getType()) {
            case PrystParser::LESS:
                return builder->CreateFCmpOLT(leftValue, rightValue, "lttmp");
            case PrystParser::LESS_EQUAL:
                return builder->CreateFCmpOLE(leftValue, rightValue, "letmp");
            case PrystParser::GREATER:
                return builder->CreateFCmpOGT(leftValue, rightValue, "gttmp");
            case PrystParser::GREATER_EQUAL:
                return builder->CreateFCmpOGE(leftValue, rightValue, "getmp");
            default:
                throw std::runtime_error("Unknown comparison operator");
        }
    }

    // Integer comparison
    switch (ctx->op->getType()) {
        case PrystParser::LESS:
            return builder->CreateICmpSLT(leftValue, rightValue, "lttmp");
        case PrystParser::LESS_EQUAL:
            return builder->CreateICmpSLE(leftValue, rightValue, "letmp");
        case PrystParser::GREATER:
            return builder->CreateICmpSGT(leftValue, rightValue, "gttmp");
        case PrystParser::GREATER_EQUAL:
            return builder->CreateICmpSGE(leftValue, rightValue, "getmp");
        default:
            throw std::runtime_error("Unknown comparison operator");
    }
}

} // namespace pryst
