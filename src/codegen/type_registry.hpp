#pragma once

#include <memory>
#include <string>
#include <unordered_map>
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

    void registerType(const std::string& name, TypeInfoPtr typeInfo);
    TypeInfoPtr getTypeInfo(const std::string& name) const;
    llvm::Type* getLLVMType(const std::string& name) const;

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

    bool isPointerType(llvm::Type* type) const { return type && type->isPointerTy(); }
    bool isStringType(llvm::Type* type) const { return type && type->isPointerTy(); }
    bool isNumericType(llvm::Type* type) const;
    bool isBoolType(llvm::Type* type) const { return type && type->isIntegerTy(1); }

    llvm::Value* convertType(llvm::Value* value, const std::string& targetType) const;

private:
    llvm::LLVMContext& context;
    std::unordered_map<std::string, TypeInfoPtr> types;
    void initializeBasicTypes();
};

} // namespace pryst
