#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include "../semantic/type_info.hpp"

namespace pryst {

using TypeInfoPtr = std::shared_ptr<TypeInfo>;

class TypeRegistry {
public:
    explicit TypeRegistry(llvm::LLVMContext& context);
    ~TypeRegistry() = default;

    // Namespace management
    void registerNamespace(const std::string& ns);
    bool isNamespaceRegistered(const std::string& ns) const;
    void setCurrentNamespace(const std::string& ns);
    std::string getCurrentNamespace() const;

    // Using declarations
    void addUsingDeclaration(const std::string& type);
    void addUsingNamespace(const std::string& ns);

    // Type registration and lookup
    void registerType(const std::string& name, TypeInfoPtr typeInfo);
    TypeInfoPtr getTypeInfo(const std::string& name) const;
    llvm::Type* getLLVMType(const std::string& name) const;
    bool isTypeAvailableInScope(const std::string& name) const;

    // Basic type getters
    llvm::Type* getVoidType() const { return llvm::Type::getVoidTy(context); }
    llvm::Type* getBoolType() const { return llvm::Type::getInt1Ty(context); }
    llvm::Type* getInt8Type() const { return llvm::Type::getInt8Ty(context); }
    llvm::Type* getInt32Type() const { return llvm::Type::getInt32Ty(context); }
    llvm::Type* getInt64Type() const { return llvm::Type::getInt64Ty(context); }
    llvm::Type* getFloatType() const { return llvm::Type::getDoubleTy(context); }
    llvm::Type* getStringType() const { return getPointerType(getInt8Type()); }

    llvm::Type* getPointerType(llvm::Type* elementType) const {
        return llvm::PointerType::get(context, 0);
    }

    // Type checking
    bool isPointerType(llvm::Type* type) const { return type && type->isPointerTy(); }
    bool isStringType(llvm::Type* type) const { return type && type->isPointerTy(); }
    bool isNumericType(llvm::Type* type) const;
    bool isBoolType(llvm::Type* type) const { return type && type->isIntegerTy(1); }

    llvm::Value* convertType(llvm::Value* value, const std::string& targetType) const;

private:
    llvm::LLVMContext& context;
    std::unordered_map<std::string, TypeInfoPtr> types;
    std::vector<std::string> namespaces_;
    std::string currentNamespace_;
    std::vector<std::string> usingDeclarations_;
    std::vector<std::string> usingNamespaces_;

    void initializeBasicTypes();
    std::string normalizeTypeName(const std::string& name) const;
    std::string resolveTypeInCurrentNamespace(const std::string& name) const;
    bool isTypeVisibleThroughUsing(const std::string& name) const;
};

} // namespace pryst
