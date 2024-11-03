#include "llvm_codegen.hpp"
#include "llvm_utils.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>

std::any LLVMCodegen::visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) {
    // Create a unique name for the lambda function
    static int lambdaCounter = 0;
    std::string lambdaName = "lambda_" + std::to_string(lambdaCounter++);

    // Get return type and parameter types
    std::string returnType = ctx->type() ? ctx->type()->getText() : "void";
    std::vector<std::string> paramTypes;
    std::vector<std::string> paramNames;

    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(param->type()->getText());
            paramNames.push_back(param->IDENTIFIER()->getText());
        }
    }

    // Create function type
    llvm::Type* llvmReturnType = getLLVMType(returnType);
    std::vector<llvm::Type*> llvmParamTypes;
    for (const auto& paramType : paramTypes) {
        llvmParamTypes.push_back(getLLVMType(paramType));
    }

    llvm::FunctionType* functionType = llvm::FunctionType::get(llvmReturnType, llvmParamTypes, false);
    llvm::Function* function = llvm::Function::Create(
        functionType, llvm::Function::ExternalLinkage, lambdaName, module.get());

    // Create entry block
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(entryBlock);

    // Set parameter names and create allocas for parameters
    size_t idx = 0;
    for (auto& arg : function->args()) {
        arg.setName(paramNames[idx]);
        // Create alloca for parameter
        llvm::AllocaInst* alloca = builder->CreateAlloca(arg.getType(), nullptr, paramNames[idx]);
        builder->CreateStore(&arg, alloca);
        namedValues[paramNames[idx]] = alloca;
        idx++;
    }

    // Generate code for function body
    visit(ctx->statement());

    // Add return instruction if needed
    if (!builder->GetInsertBlock()->getTerminator()) {
        if (returnType == "void") {
            builder->CreateRetVoid();
        } else {
            // Return a default value for non-void functions
            llvm::Value* defaultValue = getDefaultValue(llvmReturnType);
            builder->CreateRet(defaultValue);
        }
    }

    return function;
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
