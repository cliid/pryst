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
    auto& context = getModule()->getContext();
    auto globalStr = getBuilder()->CreateGlobalString(typeName);
    // Use opaque pointer type for string
    auto charPtrTy = llvm::Type::getInt8PtrTy(context);
    return getBuilder()->CreateBitCast(globalStr, charPtrTy);
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    PRYST_DEBUG("Generating isInstance() call for type '" + typeName + "'");

    // Get type info from type registry
    auto typeInfo = getTypeInfo(value);
    if (!typeInfo) {
        PRYST_ERROR("No type info found for value");
        return llvm::ConstantInt::getFalse(getModule()->getContext());
    }

    // Get the target class type info from registry
    auto& registry = getTypeRegistry();
    auto targetType = registry.lookupType(typeName);
    if (!targetType || targetType->getKind() != pryst::TypeInfo::Kind::Class) {
        return llvm::ConstantInt::getFalse(getModule()->getContext());
    }

    auto targetClassType = std::dynamic_pointer_cast<pryst::ClassTypeInfo>(targetType);
    if (!targetClassType) {
        return llvm::ConstantInt::getFalse(getModule()->getContext());
    }

    // Check if types match exactly
    if (typeInfo->getName() == typeName) {
        return llvm::ConstantInt::getTrue(getModule()->getContext());
    }

    // Check inheritance chain if it's a class type
    if (typeInfo->getKind() == pryst::TypeInfo::Kind::Class) {
        auto currentClass = std::dynamic_pointer_cast<pryst::ClassTypeInfo>(typeInfo);
        while (currentClass) {
            if (currentClass->getName() == targetClassType->getName()) {
                return llvm::ConstantInt::getTrue(getModule()->getContext());
            }
            currentClass = std::dynamic_pointer_cast<pryst::ClassTypeInfo>(currentClass->getBaseClass());
        }
    }

    return llvm::ConstantInt::getFalse(getModule()->getContext());
}

// Get type information from TypeRegistry and TypeMetadata
pryst::TypeInfoPtr LLVMCodegen::getTypeInfo(llvm::Value* value) {
    if (!value) return nullptr;
    return typeMetadata.getTypeInfo(value);
}

// Attach type information using TypeRegistry and TypeMetadata
void LLVMCodegen::attachTypeInfo(llvm::Value* value, pryst::TypeInfoPtr typeInfo) {
    if (!value || !typeInfo) return;
    typeMetadata.addTypeInfo(value, typeInfo);
}

} // namespace pryst
