#include "type_registry.hpp"
#include "../semantic/basic_type_info.hpp"
#include "../utils/debug.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <algorithm>

namespace pryst {

TypeRegistry::TypeRegistry(llvm::LLVMContext& context)
    : context(context), currentNamespace_("") {
    initializeBasicTypes();
}

void TypeRegistry::registerNamespace(const std::string& ns) {
    if (std::find(namespaces_.begin(), namespaces_.end(), ns) == namespaces_.end()) {
        namespaces_.push_back(ns);
    }
}

bool TypeRegistry::isNamespaceRegistered(const std::string& ns) const {
    return std::find(namespaces_.begin(), namespaces_.end(), ns) != namespaces_.end();
}

void TypeRegistry::setCurrentNamespace(const std::string& ns) {
    if (!ns.empty() && !isNamespaceRegistered(ns)) {
        PRYST_ERROR("Namespace '" + ns + "' is not registered");
        return;
    }
    currentNamespace_ = ns;
}

std::string TypeRegistry::getCurrentNamespace() const {
    return currentNamespace_;
}

void TypeRegistry::addUsingDeclaration(const std::string& type) {
    if (std::find(usingDeclarations_.begin(), usingDeclarations_.end(), type) == usingDeclarations_.end()) {
        usingDeclarations_.push_back(type);
    }
}

void TypeRegistry::addUsingNamespace(const std::string& ns) {
    if (!isNamespaceRegistered(ns)) {
        PRYST_ERROR("Cannot use namespace '" + ns + "': not registered");
        return;
    }
    if (std::find(usingNamespaces_.begin(), usingNamespaces_.end(), ns) == usingNamespaces_.end()) {
        usingNamespaces_.push_back(ns);
    }
}

llvm::Type* TypeRegistry::getLLVMType(const std::string& typeName) const {
    auto resolvedName = resolveTypeInCurrentNamespace(typeName);
    auto it = types.find(resolvedName);
    if (it == types.end()) {
        PRYST_ERROR("Unknown type: " + typeName);
        return nullptr;
    }
    return it->second->getLLVMType();
}

void TypeRegistry::registerType(const std::string& name, TypeInfoPtr typeInfo) {
    std::string fullName = normalizeTypeName(name);
    types[fullName] = typeInfo;
}

TypeInfoPtr TypeRegistry::getTypeInfo(const std::string& name) const {
    auto resolvedName = resolveTypeInCurrentNamespace(name);
    auto it = types.find(resolvedName);
    return it != types.end() ? it->second : nullptr;
}

bool TypeRegistry::isTypeAvailableInScope(const std::string& name) const {
    // Check if it's a fully qualified name
    if (name.find("::") != std::string::npos) {
        return types.find(name) != types.end();
    }

    // Check in current namespace
    if (!currentNamespace_.empty()) {
        std::string fullName = currentNamespace_ + "::" + name;
        if (types.find(fullName) != types.end()) {
            return true;
        }
    }

    // Check using declarations
    if (isTypeVisibleThroughUsing(name)) {
        return true;
    }

    // Check global namespace
    return types.find(name) != types.end();
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
    // Register basic types in global namespace
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

std::string TypeRegistry::normalizeTypeName(const std::string& name) const {
    if (name.empty()) return name;
    if (name[0] == ':') {
        return name.substr(2); // Remove leading ::
    }
    if (!currentNamespace_.empty() && name.find("::") == std::string::npos) {
        return currentNamespace_ + "::" + name;
    }
    return name;
}

std::string TypeRegistry::resolveTypeInCurrentNamespace(const std::string& name) const {
    if (name.find("::") != std::string::npos) {
        return normalizeTypeName(name);
    }

    // Try current namespace
    if (!currentNamespace_.empty()) {
        std::string fullName = currentNamespace_ + "::" + name;
        if (types.find(fullName) != types.end()) {
            return fullName;
        }
    }

    // Try using declarations
    for (const auto& usingDecl : usingDeclarations_) {
        if (usingDecl.substr(usingDecl.rfind("::") + 2) == name) {
            return usingDecl;
        }
    }

    // Try using namespaces
    for (const auto& ns : usingNamespaces_) {
        std::string fullName = ns + "::" + name;
        if (types.find(fullName) != types.end()) {
            return fullName;
        }
    }

    // Try global namespace
    if (types.find(name) != types.end()) {
        return name;
    }

    return normalizeTypeName(name);
}

bool TypeRegistry::isTypeVisibleThroughUsing(const std::string& name) const {
    // Check using declarations
    for (const auto& usingDecl : usingDeclarations_) {
        if (usingDecl.substr(usingDecl.rfind("::") + 2) == name) {
            return true;
        }
    }

    // Check using namespaces
    for (const auto& ns : usingNamespaces_) {
        if (types.find(ns + "::" + name) != types.end()) {
            return true;
        }
    }

    return false;
}

} // namespace pryst
