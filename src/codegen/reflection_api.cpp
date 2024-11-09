#include "llvm_codegen.hpp"
#include "type_registry.hpp"
#include "type_metadata.hpp"
#include "../utils/debug.hpp"
#include <stdexcept>
#include <memory>

namespace pryst {

// Implementation of reflection API functions
llvm::Value* LLVMCodegen::generateGetType(llvm::Value* value) {
    PRYST_DEBUG("Generating getType() call");

    // Get type info from type registry
    auto typeInfo = typeMetadata_->getTypeInfo(value);
    if (!typeInfo) {
        PRYST_ERROR("No type info found for value");
        return nullptr;
    }

    // Create a string constant with the type name
    std::string typeName = typeInfo->getName();
    auto& context = module_->getContext();
    auto globalStr = builder_->CreateGlobalString(typeName);
    // Use pointer type from type registry
    auto charPtrTy = typeRegistry_->getPointerType();
    return builder_->CreateBitCast(globalStr, charPtrTy);
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    PRYST_DEBUG("Generating isInstance() call for type '" + typeName + "'");

    // Get type info from type registry or metadata
    auto typeInfo = getTypeInfo(value);
    if (!typeInfo) {
        PRYST_ERROR("No type info found for value");
        return llvm::ConstantInt::getFalse(module_->getContext());
    }

    // Get the target class type info from registry
    auto targetType = typeRegistry_->lookupType(typeName);
    if (!targetType || !targetType->isClass()) {
        PRYST_ERROR("Target type '" + typeName + "' is not a class type");
        return llvm::ConstantInt::getFalse(module_->getContext());
    }

    auto targetClassType = std::dynamic_pointer_cast<ClassTypeInfo>(targetType);
    if (!targetClassType) {
        PRYST_ERROR("Failed to cast target type to ClassTypeInfo");
        return llvm::ConstantInt::getFalse(module_->getContext());
    }

    // Check if types match exactly
    if (typeInfo->getName() == typeName) {
        return llvm::ConstantInt::getTrue(module_->getContext());
    }

    // Check inheritance chain if it's a class type
    if (typeInfo->isClass()) {
        auto currentClass = std::dynamic_pointer_cast<ClassTypeInfo>(typeInfo);
        while (currentClass) {
            if (currentClass->getName() == targetClassType->getName()) {
                return llvm::ConstantInt::getTrue(module_->getContext());
            }
            currentClass = currentClass->getParent();
        }
    }

    return llvm::ConstantInt::getFalse(module_->getContext());
}

// Get type information from TypeRegistry and TypeMetadata
TypeInfoPtr LLVMCodegen::getTypeInfo(llvm::Value* value) const {
    if (!value) return nullptr;

    // First try to get type info from metadata
    auto typeInfo = typeMetadata_->getTypeInfo(value);
    if (typeInfo) return typeInfo;

    // If not found in metadata, try to get from type registry using LLVM type
    auto* type = value->getType();
    if (auto* structTy = llvm::dyn_cast<llvm::StructType>(type)) {
        std::string typeName = structTy->getName().str();
        return typeRegistry_->lookupType(typeName);
    }

    // For non-struct types, try to determine basic type
    if (type->isIntegerTy(1)) return typeRegistry_->lookupType("bool");
    if (type->isIntegerTy(32)) return typeRegistry_->lookupType("int");
    if (type->isDoubleTy()) return typeRegistry_->lookupType("float");
    if (type->isPointerTy()) return typeRegistry_->lookupType("str");

    return nullptr;
}

// Attach type information using TypeRegistry and TypeMetadata
void LLVMCodegen::attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) {
    if (!value || !typeInfo) return;
    typeMetadata_->addTypeInfo(value, typeInfo);
}

} // namespace pryst
