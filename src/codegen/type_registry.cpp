#include "type_registry.hpp"
#include "../semantic/basic_type_info.hpp"
#include "../utils/debug.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

namespace pryst {

TypeRegistry::TypeRegistry(llvm::LLVMContext& context) : context(context) {
    initializeBasicTypes();
}

llvm::Type* TypeRegistry::getLLVMType(const std::string& typeName) const {
    auto it = types.find(typeName);
    if (it == types.end()) {
        PRYST_ERROR("Unknown type: " + typeName);
        return nullptr;
    }
    return it->second->getLLVMType();
}

void TypeRegistry::registerType(const std::string& name, TypeInfoPtr typeInfo) {
    types[name] = typeInfo;
}

TypeInfoPtr TypeRegistry::getTypeInfo(const std::string& name) const {
    auto it = types.find(name);
    return it != types.end() ? it->second : nullptr;
}

bool TypeRegistry::isNumericType(llvm::Type* type) const {
    return type && (type->isIntegerTy(32) || type->isDoubleTy());
}

llvm::Value* TypeRegistry::convertType(llvm::Value* value, const std::string& targetType) const {
    if (!value) return nullptr;

    auto sourceType = value->getType();
    auto targetLLVMType = getLLVMType(targetType);
    if (!targetLLVMType) return nullptr;

    // Handle numeric conversions
    if (sourceType->isIntegerTy(32) && targetLLVMType->isDoubleTy()) {
        return llvm::IRBuilder<>(llvm::BasicBlock::Create(context)).CreateSIToFP(value, targetLLVMType);
    }

    if (sourceType->isDoubleTy() && targetLLVMType->isIntegerTy(32)) {
        return llvm::IRBuilder<>(llvm::BasicBlock::Create(context)).CreateFPToSI(value, targetLLVMType);
    }

    // Handle string conversions (assuming we have toString functions implemented)
    if (targetLLVMType->isPointerTy()) {
        // TODO: Implement string conversion
        return nullptr;
    }

    return value;
}

void TypeRegistry::initializeBasicTypes() {
    // Register basic types
    registerType("void", std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Void, "void", getVoidType()));
    registerType("bool", std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Bool, "bool", getBoolType()));
    registerType("int", std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Int, "int", getInt32Type()));
    registerType("float", std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Float, "float", getFloatType()));
    registerType("str", std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::String, "str", getStringType()));
}

} // namespace pryst
