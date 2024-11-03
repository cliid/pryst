#include "llvm_codegen.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <stdexcept>

// Type conversion helper functions
llvm::Value* LLVMCodegen::convertToString(llvm::Value* value) {
    if (value->getType()->isIntegerTy()) {
        // Call toString for int
        llvm::Function* toStrFunc = declareToString();
        llvm::FunctionCallee toStrCallee(toStrFunc->getFunctionType(), toStrFunc);
        return builder->CreateCall(toStrCallee, {value}, "tostr");
    } else if (value->getType()->isFloatingPointTy()) {
        // Call toString for float
        llvm::Function* toStrFunc = declareToString();
        llvm::FunctionCallee toStrCallee(toStrFunc->getFunctionType(), toStrFunc);
        return builder->CreateCall(toStrCallee, {value}, "tostr");
    }
    return value;
}

llvm::Value* LLVMCodegen::convertFromString(llvm::Value* value, llvm::Type* targetType) {
    if (targetType->isIntegerTy()) {
        // Call toInt for string
        llvm::Function* toIntFunc = declareToInt();
        llvm::FunctionCallee toIntCallee(toIntFunc->getFunctionType(), toIntFunc);
        return builder->CreateCall(toIntCallee, {value}, "toint");
    } else if (targetType->isFloatingPointTy()) {
        // Call toFloat for string
        llvm::Function* toFloatFunc = declareToFloat();
        llvm::FunctionCallee toFloatCallee(toFloatFunc->getFunctionType(), toFloatFunc);
        return builder->CreateCall(toFloatCallee, {value}, "tofloat");
    }
    return value;
}

// Type conversion expression visitor: type(expr)
std::any LLVMCodegen::visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) {
    // Visit the expression to get the value to convert
    visit(ctx->expression());
    llvm::Value* value = lastValue;

    // Get the target type
    std::string targetTypeName = ctx->type()->getText();
    llvm::Type* targetType = getLLVMType(targetTypeName);

    // Get type information from registry using our type tracking system
    auto& registry = TypeRegistry::getInstance();
    TypeInfoPtr valueTypeInfo = getTypeInfo(value);
    TypeInfoPtr targetTypeInfo = registry.lookupType(targetTypeName);

    // Handle string conversions
    if (valueTypeInfo && valueTypeInfo->getKind() == TypeKind::String) {
        // Converting from string
        lastValue = convertFromString(value, targetType);
    } else if (targetTypeInfo && targetTypeInfo->getKind() == TypeKind::String) {
        // Converting to string
        lastValue = convertToString(value);
    } else if (value->getType()->isIntegerTy() && targetType->isFloatingPointTy()) {
        // Int to float conversion
        lastValue = builder->CreateSIToFP(value, targetType, "int2float");
    } else if (value->getType()->isFloatingPointTy() && targetType->isIntegerTy()) {
        // Float to int conversion
        lastValue = builder->CreateFPToSI(value, targetType, "float2int");
    } else if (value->getType() == targetType) {
        // No conversion needed
        lastValue = value;
    } else {
        throw std::runtime_error("Unsupported type conversion from " +
                               (valueTypeInfo ? valueTypeInfo->getTypeName() : "unknown") +
                               " to " + targetTypeName);
    }

    return nullptr;
}

// Class conversion expression visitor: c!ClassName(expr)
std::any LLVMCodegen::visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) {
    // Visit the expression to get the value to convert
    visit(ctx->expression());
    llvm::Value* value = lastValue;

    // Get the target class name and conversion method name
    std::string className = ctx->IDENTIFIER()->getText();
    std::string conversionMethodName = "c!" + className;

    // Look up the conversion method
    auto it = functions.find(conversionMethodName);
    if (it == functions.end()) {
        throw std::runtime_error("Class conversion method not found: " + conversionMethodName);
    }

    // Call the conversion method
    std::vector<llvm::Value*> args = {value};
    lastValue = builder->CreateCall(it->second, args, "classconv");
    return nullptr;
}

// Named function visitor: handles functions with explicit return types
std::any LLVMCodegen::visitNamedFunction(PrystParser::NamedFunctionContext* ctx) {
    std::string funcName = ctx->IDENTIFIER()->getText();

    // Get return type
    llvm::Type* returnType = nullptr;
    if (ctx->type()) {
        returnType = getLLVMType(ctx->type()->getText());
    } else {
        // If no return type specified, use void
        returnType = llvm::Type::getVoidTy(*context);
    }

    // Get parameter types and names
    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(getLLVMType(param->type()->getText()));
            paramNames.push_back(param->IDENTIFIER()->getText());
        }
    }

    // Create function type
    llvm::FunctionType* funcType = llvm::FunctionType::get(returnType, paramTypes, false);

    // Create function
    llvm::Function* function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        funcName,
        module.get()
    );

    // Set parameter names
    unsigned idx = 0;
    for (auto &arg : function->args()) {
        arg.setName(paramNames[idx++]);
    }

    // Create entry block
    llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(entry);

    // Create scope for function body
    pushScope();

    // Add parameters to scope
    idx = 0;
    for (auto &arg : function->args()) {
        llvm::AllocaInst* alloca = createEntryBlockAlloca(function, arg.getName().str(), arg.getType());
        builder->CreateStore(&arg, alloca);
        namedValues[arg.getName().str()] = alloca;
    }

    // Visit function body
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Verify all return statements match declared type
    if (!verifyReturnTypes(function, returnType)) {
        throw std::runtime_error("Return type mismatch in function " + funcName);
    }

    // Add return void if no terminator
    if (!builder->GetInsertBlock()->getTerminator()) {
        if (returnType->isVoidTy()) {
            builder->CreateRetVoid();
        } else {
            throw std::runtime_error("Non-void function " + funcName + " must return a value");
        }
    }

    // Pop scope
    popScope();

    // Verify function
    std::string error;
    llvm::raw_string_ostream errorStream(error);
    if (llvm::verifyFunction(*function, &errorStream)) {
        throw std::runtime_error("Function verification failed: " + error);
    }

    return nullptr;
}

// Anonymous function visitor: handles functions with type deduction
std::any LLVMCodegen::visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) {
    static int anonFuncCount = 0;
    std::string funcName = "__anon_" + std::to_string(anonFuncCount++);

    // Get parameter types and names
    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(getLLVMType(param->type()->getText()));
            paramNames.push_back(param->IDENTIFIER()->getText());
        }
    }

    // Create temporary function with void return type
    llvm::Type* tempReturnType = llvm::Type::getVoidTy(*context);
    llvm::FunctionType* tempFuncType = llvm::FunctionType::get(tempReturnType, paramTypes, false);
    llvm::Function* tempFunction = llvm::Function::Create(
        tempFuncType,
        llvm::Function::ExternalLinkage,
        funcName + "_temp",
        module.get()
    );

    // Create entry block
    llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", tempFunction);
    builder->SetInsertPoint(entry);

    // Create scope for function body
    pushScope();

    // Add parameters to scope
    unsigned idx = 0;
    for (auto &arg : tempFunction->args()) {
        arg.setName(paramNames[idx++]);
        // Use TypeRegistry for parameter type handling
        auto paramType = typeRegistry.getPointerType();
        auto llvmType = LLVMTypeRegistry::getInstance().getLLVMType(paramType, *context);
        llvm::AllocaInst* alloca = builder->CreateAlloca(llvmType, nullptr, arg.getName().str());
        builder->CreateStore(&arg, alloca);
        namedValues[arg.getName().str()] = alloca;
        // Track type information
        typeMetadata->addTypeInfo(&arg, paramType);
    }

    // Visit function body to collect return types
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    std::vector<llvm::Type*> returnTypes = collectReturnTypes(tempFunction);

    // Deduce return type
    llvm::Type* returnType = deduceReturnType(returnTypes);

    // Create actual function with deduced return type
    llvm::FunctionType* funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    llvm::Function* function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        funcName,
        module.get()
    );

    // Copy parameter names
    idx = 0;
    for (auto &arg : function->args()) {
        arg.setName(paramNames[idx++]);
    }

    // Delete temporary function
    tempFunction->eraseFromParent();

    // Create new entry block
    entry = llvm::BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(entry);

    // Reset scope
    pushScope();

    // Add parameters to scope again
    idx = 0;
    for (auto &arg : function->args()) {
        // Use TypeRegistry for parameter type handling
        auto paramType = typeRegistry.getPointerType();
        auto llvmType = LLVMTypeRegistry::getInstance().getLLVMType(paramType, *context);
        llvm::AllocaInst* alloca = builder->CreateAlloca(llvmType, nullptr, arg.getName().str());
        builder->CreateStore(&arg, alloca);
        namedValues[arg.getName().str()] = alloca;
        // Track type information
        typeMetadata->addTypeInfo(&arg, paramType);
    }

    // Visit function body again with correct return type
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Add return void if no terminator and return type is void
    if (!builder->GetInsertBlock()->getTerminator()) {
        if (returnType->isVoidTy()) {
            builder->CreateRetVoid();
        } else {
            throw std::runtime_error("Non-void anonymous function must return a value");
        }
    }

    // Pop scope
    popScope();

    // Verify function
    std::string error;
    llvm::raw_string_ostream errorStream(error);
    if (llvm::verifyFunction(*function, &errorStream)) {
        throw std::runtime_error("Anonymous function verification failed: " + error);
    }

    lastValue = function;
    return nullptr;
}

// Helper function to verify return types match declared type
bool LLVMCodegen::verifyReturnTypes(llvm::Function* function, llvm::Type* declaredType) {
    for (auto& block : *function) {
        if (auto* ret = llvm::dyn_cast<llvm::ReturnInst>(block.getTerminator())) {
            if (declaredType->isVoidTy()) {
                if (ret->getNumOperands() != 0) {
                    return false;
                }
            } else {
                if (ret->getNumOperands() == 0 || ret->getOperand(0)->getType() != declaredType) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Helper function to collect return types from function
std::vector<llvm::Type*> LLVMCodegen::collectReturnTypes(llvm::Function* function) {
    std::vector<llvm::Type*> types;
    for (auto& block : *function) {
        if (auto* ret = llvm::dyn_cast<llvm::ReturnInst>(block.getTerminator())) {
            if (ret->getNumOperands() > 0) {
                types.push_back(ret->getOperand(0)->getType());
            }
        }
    }
    return types;
}

// Helper function to deduce return type from collected types
llvm::Type* LLVMCodegen::deduceReturnType(const std::vector<llvm::Type*>& types) {
    if (types.empty()) {
        return llvm::Type::getVoidTy(*context);
    }

    llvm::Type* deducedType = types[0];
    for (size_t i = 1; i < types.size(); ++i) {
        if (types[i]->getTypeID() != deducedType->getTypeID()) {
            if (deducedType->isIntegerTy() && types[i]->isFloatingPointTy()) {
                deducedType = types[i];
            } else if (deducedType->isFloatingPointTy() && types[i]->isIntegerTy()) {
                // Keep float
            } else {
                throw std::runtime_error("Inconsistent return types in anonymous function");
            }
        }
    }
    return deducedType;
}
