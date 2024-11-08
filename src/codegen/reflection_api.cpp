#include "llvm_codegen.hpp"
#include "type_registry.hpp"
#include "type_metadata.hpp"
#include "../utils/debug.hpp"
#include <stdexcept>
#include <memory>

// Implementation of reflection API functions
llvm::Value* LLVMCodegen::generateGetType(llvm::Value* value) {
    PRYST_DEBUG("Generating getType() call");

    // Get type info from type registry
    auto typeInfo = typeMetadata->getTypeInfo(value);
    if (!typeInfo) {
        PRYST_ERROR("No type info found for value");
        return nullptr;
    }

    // Create a string constant with the type name
    std::string typeName = typeInfo->getName();
    auto& context = module->getContext();
    auto globalStr = builder->CreateGlobalString(typeName);
    // Use opaque pointer type for string
    auto& llvmTypeRegistry = LLVMTypeRegistry::getInstance();
    auto charPtrTy = llvmTypeRegistry.getOpaquePointerType(context);
    return builder->CreateBitCast(globalStr, charPtrTy);
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    PRYST_DEBUG("Generating isInstance() call for type '" + typeName + "'");

    // Get type info from type registry
    auto typeInfo = typeMetadata->getTypeInfo(value);
    if (!typeInfo) {
        PRYST_ERROR("No type info found for value");
        return llvm::ConstantInt::getFalse(module->getContext());
    }

    // Get the target class type info from registry
    auto& registry = TypeRegistry::getInstance();
    auto targetType = registry.lookupType(typeName);
    if (!targetType || targetType->getKind() != TypeInfo::Kind::Class) {
        return llvm::ConstantInt::getFalse(module->getContext());
    }

    auto targetClassType = std::dynamic_pointer_cast<ClassTypeInfo>(targetType);
    if (!targetClassType) {
        return llvm::ConstantInt::getFalse(module->getContext());
    }

    // Check if types match exactly
    if (typeInfo->getName() == typeName) {
        return llvm::ConstantInt::getTrue(module->getContext());
    }

    // Check inheritance chain if it's a class type
    if (typeInfo->getKind() == TypeInfo::Kind::Class) {
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
TypeInfoPtr LLVMCodegen::getTypeInfo(llvm::Value* value) {
    if (!value) return nullptr;
    return typeMetadata->getTypeInfo(value);
}

// Attach type information using TypeRegistry and TypeMetadata
void LLVMCodegen::attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) {
    if (!value || !typeInfo) return;
    typeMetadata->addTypeInfo(value, typeInfo);
}
