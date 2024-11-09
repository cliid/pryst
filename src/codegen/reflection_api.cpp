#include "reflection_api.hpp"
#include "type_utils.hpp"
#include "type_metadata.hpp"
#include "type_registry.hpp"
#include "../utils/debug.hpp"
#include <llvm/IR/Constants.h>
#include <memory>

namespace pryst {

// Implementation of reflection API functions
llvm::Value* LLVMCodegen::generateGetType(llvm::Value* value) {
    PRYST_DEBUG("Generating getType() call");

    // Get type info from type registry
    auto typeInfo = getTypeInfo(value);
    if (!typeInfo) {
        PRYST_ERROR("No type info found for value");
        return nullptr;
    }

    // Create a string constant with the type name
    std::string typeName = typeInfo->getName();
    auto& context = module->getContext();
    auto globalStr = builder->CreateGlobalString(typeName);
    // Use pointer type from type registry
    auto charPtrTy = typeRegistry->getPointerType();
    return builder->CreateBitCast(globalStr, charPtrTy);
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    PRYST_DEBUG("Generating isInstance() call for type '" + typeName + "'");

    // Get type info from type registry or metadata
    auto typeInfo = getTypeInfo(value);
    if (!typeInfo) {
        PRYST_ERROR("No type info found for value");
        return llvm::ConstantInt::getFalse(module->getContext());
    }

    // Get the target class type info from registry
    auto targetType = typeRegistry->lookupType(typeName);
    if (!targetType || !targetType->isClass()) {
        PRYST_ERROR("Target type '" + typeName + "' is not a class type");
        return llvm::ConstantInt::getFalse(module->getContext());
    }

    auto targetClassType = std::dynamic_pointer_cast<ClassTypeInfo>(targetType);
    if (!targetClassType) {
        PRYST_ERROR("Failed to cast target type to ClassTypeInfo");
        return llvm::ConstantInt::getFalse(module->getContext());
    }

    // Check if types match exactly
    if (typeInfo->getName() == typeName) {
        return llvm::ConstantInt::getTrue(module->getContext());
    }

    // Check inheritance chain if it's a class type
    if (typeInfo->isClass()) {
        auto currentClass = std::dynamic_pointer_cast<ClassTypeInfo>(typeInfo);
        while (currentClass) {
            if (currentClass->getName() == targetClassType->getName()) {
                return llvm::ConstantInt::getTrue(module->getContext());
            }
            currentClass = currentClass->getParent();
        }
    }

    return llvm::ConstantInt::getFalse(module->getContext());
}

// Get type information from TypeRegistry and TypeMetadata
TypeInfoPtr LLVMCodegen::getTypeInfo(llvm::Value* value) const {
    if (!value) return nullptr;

    // First try to get type info from metadata
    auto typeInfo = typeMetadata->getTypeInfo(value);
    if (typeInfo) return typeInfo;

    // If not found in metadata, try to get from type registry using LLVM type
    auto* type = value->getType();
    if (auto* structTy = llvm::dyn_cast<llvm::StructType>(type)) {
        std::string typeName = structTy->getName().str();
        return typeRegistry->lookupType(typeName);
    }

    // For non-struct types, try to determine basic type
    if (type->isIntegerTy(1)) return typeRegistry->lookupType("bool");
    if (type->isIntegerTy(32)) return typeRegistry->lookupType("int");
    if (type->isDoubleTy()) return typeRegistry->lookupType("float");
    if (type->isPointerTy()) return typeRegistry->lookupType("str");

    return nullptr;
}

// Attach type information using TypeRegistry and TypeMetadata
void LLVMCodegen::attachTypeInfo(llvm::Value* value, pryst::TypeInfoPtr typeInfo) {
    if (!value || !typeInfo) return;
    typeMetadata.addTypeInfo(value, typeInfo);
}

} // namespace pryst
