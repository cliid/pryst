#include "type_registry.hpp"
#include "utils/debug.hpp"
#include "../generated/PrystParser.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>

namespace pryst {

llvm::Type* LLVMTypeRegistry::getType(antlr4::tree::ParseTree* typeContext) {
    auto* ctx = dynamic_cast<PrystParser::TypeContext*>(typeContext);
    if (!ctx) {
        PRYST_ERROR("Invalid type context");
        return nullptr;
    }

    std::string typeName = ctx->getText();
    if (typeName == "int") return getIntType();
    if (typeName == "float") return getFloatType();
    if (typeName == "bool") return getBoolType();
    if (typeName == "str") return getStrType();
    if (typeName == "void") return getVoidType();

    // Try to find a registered type (class or custom type)
    auto typeInfo = lookupType(typeName);
    if (typeInfo) return getLLVMType(typeInfo);

    PRYST_ERROR("Unknown type: " + typeName);
    return nullptr;
}

llvm::Type* LLVMTypeRegistry::getClassType(const std::string& className) {
    auto typeInfo = lookupType(className);
    if (!typeInfo) {
        PRYST_ERROR("Unknown class type: " + className);
        return nullptr;
    }
    return getLLVMType(typeInfo);
}

llvm::Value* LLVMTypeRegistry::convertType(llvm::Value* value, llvm::Type* targetType, llvm::IRBuilder<>* builder) {
    if (!value || !targetType || !builder) {
        PRYST_ERROR("Invalid conversion parameters");
        return nullptr;
    }

    auto* sourceType = value->getType();
    if (sourceType == targetType) return value;

    // Integer to Float
    if (sourceType->isIntegerTy() && targetType->isDoubleTy()) {
        return builder->CreateSIToFP(value, targetType);
    }
    // Float to Integer
    if (sourceType->isDoubleTy() && targetType->isIntegerTy()) {
        return builder->CreateFPToSI(value, targetType);
    }
    // Integer to Boolean
    if (sourceType->isIntegerTy() && targetType->isIntegerTy(1)) {
        return builder->CreateICmpNE(value, llvm::ConstantInt::get(sourceType, 0));
    }
    // Boolean to Integer
    if (sourceType->isIntegerTy(1) && targetType->isIntegerTy()) {
        return builder->CreateZExt(value, targetType);
    }

    PRYST_ERROR("Unsupported type conversion");
    return nullptr;
}

llvm::Value* LLVMTypeRegistry::convertClassType(llvm::Value* value, llvm::Type* targetType, llvm::IRBuilder<>* builder) {
    if (!value || !targetType || !builder) {
        PRYST_ERROR("Invalid class conversion parameters");
        return nullptr;
    }

    // For now, only support direct casting between compatible class types
    if (value->getType() == targetType) return value;

    PRYST_ERROR("Unsupported class type conversion");
    return nullptr;
}

llvm::Type* LLVMTypeRegistry::getLLVMType(TypeInfoPtr typeInfo) {
    if (!typeInfo) {
        PRYST_ERROR("Invalid type info");
        return nullptr;
    }

    auto it = llvmTypeMap.find(typeInfo->getName());
    if (it != llvmTypeMap.end()) {
        return it->second;
    }

    PRYST_ERROR("No LLVM type found for: " + typeInfo->getName());
    return nullptr;
}

} // namespace pryst
