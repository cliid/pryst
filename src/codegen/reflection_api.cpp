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
    auto charPtrTy = typeRegistry->getPointerType(llvm::Type::getInt8Ty(context));
    return builder->CreateBitCast(globalStr, charPtrTy);
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    PRYST_DEBUG("Generating isInstance() call for type '" + typeName + "'");

    // Get type info from type metadata
    auto valueTypeInfo = typeMetadata->getTypeInfo(value);
    if (!valueTypeInfo) {
        PRYST_ERROR("No type info found for value");
        return llvm::ConstantInt::getFalse(getModule()->getContext());
    }

    // Get the target type info from registry
    auto targetTypeInfo = typeRegistry->getTypeInfo(typeName);
    if (!targetTypeInfo) {
        PRYST_ERROR("Target type '" + typeName + "' not found in registry");
        return llvm::ConstantInt::getFalse(module->getContext());
    }

    // Check if value's type is convertible to target type
    bool isInstance = valueTypeInfo->isConvertibleTo(targetTypeInfo);
    return isInstance ? llvm::ConstantInt::getTrue(module->getContext())
                     : llvm::ConstantInt::getFalse(module->getContext());
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
