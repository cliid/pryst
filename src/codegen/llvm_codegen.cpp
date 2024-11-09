#include "llvm_codegen.hpp"
#include "../utils/debug.hpp"
#include "type_registry.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <stdexcept>
#include <string>

namespace pryst {

LLVMCodegen::LLVMCodegen() {
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("pryst_module", *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
    typeRegistry.initialize(context.get());

    // Initialize builtin functions
    declarePrintFunctions();
    declareTypeConversionFunctions();
    declareMathFunctions();
}

void LLVMCodegen::declarePrintFunctions() {
    PRYST_DEBUG("Declaring print functions");
    try {
        // Print int function
        std::vector<llvm::Type*> printIntArgs = {llvm::Type::getInt32Ty(*context)};
        llvm::FunctionType* printIntType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*context), printIntArgs, false);
        module->getOrInsertFunction("print_int", printIntType);

        // Print float function
        std::vector<llvm::Type*> printFloatArgs = {llvm::Type::getDoubleTy(*context)};
        llvm::FunctionType* printFloatType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*context), printFloatArgs, false);
        module->getOrInsertFunction("print_float", printFloatType);

        // Print bool function
        std::vector<llvm::Type*> printBoolArgs = {llvm::Type::getInt1Ty(*context)};
        llvm::FunctionType* printBoolType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*context), printBoolArgs, false);
        module->getOrInsertFunction("print_bool", printBoolType);

        // Print string function using opaque pointers for LLVM 20.0.0 compatibility
        std::vector<llvm::Type*> printStrArgs = {typeRegistry.getStringType()};
        llvm::FunctionType* printStrType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*context), printStrArgs, false);
        module->getOrInsertFunction("print_str", printStrType);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Failed to declare print functions: " + std::string(ex.what()));
        throw;
    }
}

void LLVMCodegen::declareTypeConversionFunctions() {
    PRYST_DEBUG("Declaring type conversion functions");
    try {
        // bool to string
        std::vector<llvm::Type*> boolToStrArgs = {llvm::Type::getInt1Ty(*context)};
        llvm::FunctionType* boolToStrType = llvm::FunctionType::get(
            typeRegistry.getStringType(), boolToStrArgs, false);
        module->getOrInsertFunction("bool_to_str", boolToStrType);

        // int to string
        std::vector<llvm::Type*> intToStrArgs = {llvm::Type::getInt32Ty(*context)};
        llvm::FunctionType* intToStrType = llvm::FunctionType::get(
            typeRegistry.getStringType(), intToStrArgs, false);
        module->getOrInsertFunction("int_to_str", intToStrType);

        // float to string
        std::vector<llvm::Type*> floatToStrArgs = {llvm::Type::getDoubleTy(*context)};
        llvm::FunctionType* floatToStrType = llvm::FunctionType::get(
            typeRegistry.getStringType(), floatToStrArgs, false);
        module->getOrInsertFunction("float_to_str", floatToStrType);

        // String concatenation
        std::vector<llvm::Type*> strConcatArgs = {
            typeRegistry.getStringType(),
            typeRegistry.getStringType()
        };
        llvm::FunctionType* strConcatType = llvm::FunctionType::get(
            typeRegistry.getStringType(), strConcatArgs, false);
        module->getOrInsertFunction("str_concat", strConcatType);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Failed to declare type conversion functions: " + std::string(ex.what()));
        throw;
    }
}

void LLVMCodegen::declareMathFunctions() {
    PRYST_DEBUG("Declaring math functions");
    try {
        // sqrt function
        std::vector<llvm::Type*> sqrtArgs = {llvm::Type::getDoubleTy(*context)};
        llvm::FunctionType* sqrtType = llvm::FunctionType::get(
            llvm::Type::getDoubleTy(*context), sqrtArgs, false);
        module->getOrInsertFunction("sqrt", sqrtType);

        // Other math functions can be added here
    } catch (const std::exception& ex) {
        PRYST_ERROR("Failed to declare math functions: " + std::string(ex.what()));
        throw;
    }
}

std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(PrystParser::ProgramContext* ctx) {
    PRYST_DEBUG("Generating LLVM module");
    try {
        visit(ctx);
        return std::move(module);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Failed to generate module: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitProgram(PrystParser::ProgramContext* ctx) {
    PRYST_DEBUG("Visiting program");
    try {
        for (auto decl : ctx->declaration()) {
            visit(decl);
        }
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in program: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitDeclaration(PrystParser::DeclarationContext *ctx) {
    PRYST_DEBUG("Visiting declaration");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitNamespaceDecl(PrystParser::NamespaceDeclContext *ctx) {
    PRYST_DEBUG("Visiting namespace declaration");
    try {
        auto qualifiedId = visit(ctx->qualifiedIdentifier());
        currentNamespace.push_back(std::any_cast<std::string>(qualifiedId));

        for (auto decl : ctx->declaration()) {
            visit(decl);
        }

        currentNamespace.pop_back();
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in namespace declaration: " + std::string(ex.what()));
        currentNamespace.pop_back();
        throw;
    }
}

std::any LLVMCodegen::visitModuleDecl(PrystParser::ModuleDeclContext *ctx) {
    PRYST_DEBUG("Visiting module declaration");
    try {
        auto qualifiedId = visit(ctx->qualifiedIdentifier());
        currentModule = std::any_cast<std::string>(qualifiedId);

        for (auto decl : ctx->declaration()) {
            visit(decl);
        }

        currentModule.clear();
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in module declaration: " + std::string(ex.what()));
        currentModule.clear();
        throw;
    }
}

std::any LLVMCodegen::visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext *ctx) {
    PRYST_DEBUG("Visiting block-scoped namespace declaration");
    try {
        symbolTable.enterScope();
        auto result = visitNamespaceDecl(ctx->namespaceDecl());
        symbolTable.exitScope();
        return result;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in block-scoped namespace: " + std::string(ex.what()));
        symbolTable.exitScope();
        throw;
    }
}

std::any LLVMCodegen::visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext *ctx) {
    PRYST_DEBUG("Visiting block-scoped module declaration");
    try {
        symbolTable.enterScope();
        auto result = visitModuleDecl(ctx->moduleDecl());
        symbolTable.exitScope();
        return result;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in block-scoped module: " + std::string(ex.what()));
        symbolTable.exitScope();
        throw;
    }
}

std::any LLVMCodegen::visitImportDecl(PrystParser::ImportDeclContext *ctx) {
    PRYST_DEBUG("Visiting import declaration");
    try {
        auto importPath = visit(ctx->importPath());
        std::string path = std::any_cast<std::string>(importPath);
        if (!moduleLoader.loadModule(path)) {
            throw std::runtime_error("Failed to load module: " + path);
        }
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in import declaration: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitUsingDecl(PrystParser::UsingDeclContext *ctx) {
    PRYST_DEBUG("Visiting using declaration");
    try {
        auto qualifiedId = visit(ctx->qualifiedIdentifier());
        std::string target = std::any_cast<std::string>(qualifiedId);
        symbolTable.addUsingDeclaration(target, ctx->MODULE() != nullptr);
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in using declaration: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext *ctx) {
    PRYST_DEBUG("Visiting global using declaration");
    try {
        return visitUsingDecl(ctx->usingDecl());
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in global using declaration: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) {
    PRYST_DEBUG("Visiting function declaration");
    try {
        std::string returnType = std::any_cast<std::string>(visit(ctx->type()));
        std::string name = ctx->IDENTIFIER()->getText();
        currentFunction = name;

        // Create function type
        std::vector<llvm::Type*> paramTypes;
        if (ctx->parameterList()) {
            for (auto param : ctx->parameterList()->parameter()) {
                std::string paramType = std::any_cast<std::string>(visit(param->type()));
                paramTypes.push_back(typeRegistry.getLLVMType(paramType));
            }
        }

        llvm::FunctionType* functionType = llvm::FunctionType::get(
            typeRegistry.getLLVMType(returnType),
            paramTypes,
            false
        );

        // Create function
        llvm::Function* function = llvm::Function::Create(
            functionType,
            llvm::Function::ExternalLinkage,
            name,
            module.get()
        );

        // Name parameters
        unsigned idx = 0;
        if (ctx->parameterList()) {
            for (auto &arg : function->args()) {
                arg.setName(ctx->parameterList()->parameter()[idx++]->IDENTIFIER()->getText());
            }
        }

        // Create entry block
        llvm::BasicBlock* bb = llvm::BasicBlock::Create(*context, "entry", function);
        builder->SetInsertPoint(bb);

        // Create scope for function body
        symbolTable.enterScope();

        // Add parameters to symbol table
        idx = 0;
        if (ctx->parameterList()) {
            for (auto &arg : function->args()) {
                std::string paramType = std::any_cast<std::string>(
                    visit(ctx->parameterList()->parameter()[idx++]->type()));
                symbolTable.addVariable(arg.getName().str(), paramType);
            }
        }

        if (ctx->functionBody()) {
            visit(ctx->functionBody());
        }

        // Add return instruction if none exists
        if (!bb->getTerminator()) {
            if (returnType == "void") {
                builder->CreateRetVoid();
            } else {
                builder->CreateRet(llvm::Constant::getNullValue(typeRegistry.getLLVMType(returnType)));
            }
        }

        symbolTable.exitScope();
        currentFunction.clear();

        // Verify function
        std::string error;
        llvm::raw_string_ostream rso(error);
        if (llvm::verifyFunction(*function, &rso)) {
            PRYST_ERROR("Function verification failed: " + error);
            function->eraseFromParent();
            throw std::runtime_error("Invalid function: " + error);
        }

        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in function declaration: " + std::string(ex.what()));
        symbolTable.exitScope();
        currentFunction.clear();
        throw;
    }
}

std::any LLVMCodegen::visitFunctionBody(PrystParser::FunctionBodyContext *ctx) {
    PRYST_DEBUG("Visiting function body");
    try {
        for (auto stmt : ctx->statement()) {
            visit(stmt);
        }
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in function body: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitLambdaFunction(PrystParser::LambdaFunctionContext *ctx) {
    PRYST_DEBUG("Visiting lambda function");
    try {
        // Implementation similar to visitFunctionDecl but for anonymous functions
        std::string returnType = std::any_cast<std::string>(visit(ctx->type()));
        std::string name = "lambda_" + std::to_string(lambdaCounter++);

        // Create function type
        std::vector<llvm::Type*> paramTypes;
        if (ctx->parameterList()) {
            for (auto param : ctx->parameterList()->parameter()) {
                std::string paramType = std::any_cast<std::string>(visit(param->type()));
                paramTypes.push_back(typeRegistry.getLLVMType(paramType));
            }
        }

        llvm::FunctionType* functionType = llvm::FunctionType::get(
            typeRegistry.getLLVMType(returnType),
            paramTypes,
            false
        );

        llvm::Function* function = llvm::Function::Create(
            functionType,
            llvm::Function::ExternalLinkage,
            name,
            module.get()
        );

        // Process parameters and body similar to visitFunctionDecl
        // ... [similar implementation to visitFunctionDecl]

        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in lambda function: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitAddition(PrystParser::AdditionContext* ctx) {
    PRYST_DEBUG("Visiting addition");
    try {
        llvm::Value* left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
        llvm::Value* right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

        if (left->getType()->isIntegerTy() && right->getType()->isIntegerTy()) {
            return builder->CreateAdd(left, right, "addtmp");
        } else if (left->getType()->isDoubleTy() && right->getType()->isDoubleTy()) {
            return builder->CreateFAdd(left, right, "addtmp");
        } else {
            throw std::runtime_error("Invalid types for addition");
        }
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in addition: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitMultiplication(PrystParser::MultiplicationContext* ctx) {
    PRYST_DEBUG("Visiting multiplication");
    try {
        llvm::Value* left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
        llvm::Value* right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

        if (left->getType()->isIntegerTy() && right->getType()->isIntegerTy()) {
            return builder->CreateMul(left, right, "multmp");
        } else if (left->getType()->isDoubleTy() && right->getType()->isDoubleTy()) {
            return builder->CreateFMul(left, right, "multmp");
        } else {
            throw std::runtime_error("Invalid types for multiplication");
        }
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in multiplication: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitComparison(PrystParser::ComparisonContext* ctx) {
    PRYST_DEBUG("Visiting comparison");
    try {
        llvm::Value* left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
        llvm::Value* right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

        bool isFloat = left->getType()->isDoubleTy() && right->getType()->isDoubleTy();
        std::string op = ctx->op->getText();

        if (isFloat) {
            if (op == "<") return builder->CreateFCmpOLT(left, right, "cmptmp");
            if (op == "<=") return builder->CreateFCmpOLE(left, right, "cmptmp");
            if (op == ">") return builder->CreateFCmpOGT(left, right, "cmptmp");
            if (op == ">=") return builder->CreateFCmpOGE(left, right, "cmptmp");
        } else {
            if (op == "<") return builder->CreateICmpSLT(left, right, "cmptmp");
            if (op == "<=") return builder->CreateICmpSLE(left, right, "cmptmp");
            if (op == ">") return builder->CreateICmpSGT(left, right, "cmptmp");
            if (op == ">=") return builder->CreateICmpSGE(left, right, "cmptmp");
        }

        throw std::runtime_error("Unknown comparison operator: " + op);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in comparison: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitEquality(PrystParser::EqualityContext* ctx) {
    PRYST_DEBUG("Visiting equality");
    try {
        llvm::Value* left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
        llvm::Value* right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

        bool isFloat = left->getType()->isDoubleTy() && right->getType()->isDoubleTy();
        std::string op = ctx->op->getText();

        if (isFloat) {
            if (op == "==") return builder->CreateFCmpOEQ(left, right, "eqtmp");
            if (op == "!=") return builder->CreateFCmpONE(left, right, "neqtmp");
        } else {
            if (op == "==") return builder->CreateICmpEQ(left, right, "eqtmp");
            if (op == "!=") return builder->CreateICmpNE(left, right, "neqtmp");
        }

        throw std::runtime_error("Unknown equality operator: " + op);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in equality: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitLogicAnd(PrystParser::LogicAndContext* ctx) {
    PRYST_DEBUG("Visiting logical AND");
    try {
        llvm::Value* left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
        llvm::Value* right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

        if (!left->getType()->isIntegerTy(1) || !right->getType()->isIntegerTy(1)) {
            throw std::runtime_error("Logical AND requires boolean operands");
        }

        return builder->CreateAnd(left, right, "andtmp");
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in logical AND: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitLogicOr(PrystParser::LogicOrContext* ctx) {
    PRYST_DEBUG("Visiting logical OR");
    try {
        llvm::Value* left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
        llvm::Value* right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

        if (!left->getType()->isIntegerTy(1) || !right->getType()->isIntegerTy(1)) {
            throw std::runtime_error("Logical OR requires boolean operands");
        }

        return builder->CreateOr(left, right, "ortmp");
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in logical OR: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitUnary(PrystParser::UnaryContext* ctx) {
    PRYST_DEBUG("Visiting unary expression");
    try {
        llvm::Value* operand = std::any_cast<llvm::Value*>(visit(ctx->expression()));
        std::string op = ctx->op->getText();

        if (op == "-") {
            if (operand->getType()->isIntegerTy()) {
                return builder->CreateNeg(operand, "negtmp");
            } else if (operand->getType()->isDoubleTy()) {
                return builder->CreateFNeg(operand, "negtmp");
            }
        } else if (op == "!") {
            if (operand->getType()->isIntegerTy(1)) {
                return builder->CreateNot(operand, "nottmp");
            }
        }

        throw std::runtime_error("Invalid unary operator: " + op);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in unary expression: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitLiteral(PrystParser::LiteralContext* ctx) {
    PRYST_DEBUG("Visiting literal");
    try {
        if (ctx->INTEGER_LITERAL()) {
            int value = std::stoi(ctx->INTEGER_LITERAL()->getText());
            return builder->getInt32(value);
        } else if (ctx->FLOAT_LITERAL()) {
            double value = std::stod(ctx->FLOAT_LITERAL()->getText());
            return llvm::ConstantFP::get(*context, llvm::APFloat(value));
        } else if (ctx->BOOL_LITERAL()) {
            bool value = ctx->BOOL_LITERAL()->getText() == "true";
            return builder->getInt1(value);
        } else if (ctx->STRING_LITERAL()) {
            std::string text = ctx->STRING_LITERAL()->getText();
            text = text.substr(1, text.length() - 2); // Remove quotes
            return builder->CreateGlobalStringPtr(text);
        } else if (ctx->NULL_LITERAL()) {
            return llvm::Constant::getNullValue(typeRegistry.getNullType());
        }

        throw std::runtime_error("Unknown literal type");
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in literal: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitPrintStatement(PrystParser::PrintStatementContext* ctx) {
    PRYST_DEBUG("Visiting print statement");
    try {
        llvm::Value* value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
        llvm::Type* type = value->getType();

        llvm::Function* printFn = nullptr;
        if (type->isIntegerTy(32)) {
            printFn = module->getFunction("print_int");
        } else if (type->isDoubleTy()) {
            printFn = module->getFunction("print_float");
        } else if (type->isIntegerTy(1)) {
            printFn = module->getFunction("print_bool");
        } else if (type->isPointerTy()) {
            printFn = module->getFunction("print_str");
        } else {
            throw std::runtime_error("Unsupported type for print statement");
        }

        builder->CreateCall(printFn, {value});
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in print statement: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitSimpleString(PrystParser::SimpleStringContext* ctx) {
    PRYST_DEBUG("Visiting simple string");
    try {
        std::string text = ctx->STRING_LITERAL()->getText();
        text = text.substr(1, text.length() - 2); // Remove quotes
        return builder->CreateGlobalStringPtr(text);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in simple string: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitInterpolatedString(PrystParser::InterpolatedStringContext* ctx) {
    PRYST_DEBUG("Visiting interpolated string");
    try {
        // Get the string format function
        llvm::Function* strFormatFn = module->getFunction("str_format");
        if (!strFormatFn) {
            throw std::runtime_error("String format function not found");
        }

        // Process format string and expressions
        std::string format;
        std::vector<llvm::Value*> args;

        for (size_t i = 0; i < ctx->stringPart().size(); ++i) {
            format += ctx->stringPart(i)->getText();
            if (i < ctx->expression().size()) {
                llvm::Value* expr = std::any_cast<llvm::Value*>(visit(ctx->expression(i)));
                args.push_back(expr);
                format += "{}"; // Placeholder for interpolation
            }
        }


        // Create format string
        llvm::Value* formatStr = builder->CreateGlobalStringPtr(format);

        // Create array for arguments
        std::vector<llvm::Value*> callArgs = {formatStr};
        callArgs.insert(callArgs.end(), args.begin(), args.end());

        // Call format function
        return builder->CreateCall(strFormatFn, callArgs, "interpolated");
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in interpolated string: " + std::string(ex.what()));
        throw;
    }
}

std::any LLVMCodegen::visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx) {
    PRYST_DEBUG("Visiting type cast expression");
    try {
        llvm::Value* value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
        std::string targetType = ctx->type()->getText();

        llvm::Type* fromType = value->getType();
        llvm::Type* toType = typeRegistry.getLLVMType(targetType);

        // Handle numeric conversions
        if (fromType->isIntegerTy() && toType->isDoubleTy()) {
            return builder->CreateSIToFP(value, toType, "cast");
        } else if (fromType->isDoubleTy() && toType->isIntegerTy()) {
            return builder->CreateFPToSI(value, toType, "cast");
        }

        // Handle other conversions using runtime functions
        std::string conversionFunc = typeRegistry.getConversionFunction(
            fromType->getTypeID(),
            toType->getTypeID()
        );

        if (conversionFunc.empty()) {
            throw std::runtime_error("Unsupported type conversion");
        }

        llvm::Function* convertFn = module->getFunction(conversionFunc);
        if (!convertFn) {
            throw std::runtime_error("Conversion function not found: " + conversionFunc);
        }

        return builder->CreateCall(convertFn, {value}, "converted");
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in type cast: " + std::string(ex.what()));
        throw;
    }
}

} // namespace pryst
