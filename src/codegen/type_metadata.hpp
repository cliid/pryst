#pragma once

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <memory>
#include <unordered_map>
#include <string>
#include "../semantic/type_info.hpp"

namespace pryst {

// LLVM-specific type information that extends semantic types
class LLVMTypeInfo {
public:
    virtual ~LLVMTypeInfo() = default;
    virtual llvm::Type* getLLVMType() const = 0;
};

// LLVM-specific function type information
class LLVMFunctionTypeInfo : public FunctionTypeInfo, public LLVMTypeInfo {
public:
    LLVMFunctionTypeInfo(const std::string& name,
                        TypeInfoPtr returnType,
                        std::vector<TypeInfoPtr> paramTypes,
                        llvm::FunctionType* type)
        : FunctionTypeInfo(returnType, std::move(paramTypes)),
          llvmType(type) {}

    llvm::Type* getLLVMType() const override { return llvmType; }
    llvm::FunctionType* getFunctionType() const { return llvmType; }

private:
    llvm::FunctionType* llvmType;
};

// LLVM-specific class type information
class LLVMClassTypeInfo : public ClassTypeInfo, public LLVMTypeInfo {
public:
    LLVMClassTypeInfo(const std::string& name,
                      llvm::StructType* type,
                      ClassTypeInfoPtr parent = nullptr)
        : ClassTypeInfo(name, parent),
          structType(type) {}

    llvm::Type* getLLVMType() const override { return structType; }
    llvm::StructType* getStructType() const { return structType; }

    void addMember(const std::string& memberName, size_t index, TypeInfoPtr type) {
        memberIndices[memberName] = index;
        addField(memberName, type);
    }

    size_t getMemberIndex(const std::string& memberName) const {
        auto it = memberIndices.find(memberName);
        if (it != memberIndices.end()) {
            return it->second;
        }
        auto parent = getParent();
        if (auto llvmParent = std::dynamic_pointer_cast<LLVMClassTypeInfo>(parent)) {
            return llvmParent->getMemberIndex(memberName);
        }
        throw std::runtime_error("Member not found: " + memberName);
    }

private:
    llvm::StructType* structType;
    std::unordered_map<std::string, size_t> memberIndices;
};

using LLVMFunctionTypeInfoPtr = std::shared_ptr<LLVMFunctionTypeInfo>;
using LLVMClassTypeInfoPtr = std::shared_ptr<LLVMClassTypeInfo>;

// Container for all type metadata
class TypeMetadata {
public:
    TypeMetadata() : context(nullptr), module(nullptr) {}

    TypeMetadata(llvm::LLVMContext& ctx, llvm::Module& mod)
        : context(&ctx), module(&mod) {}

    void setContext(llvm::LLVMContext& ctx) { context = &ctx; }
    void setModule(llvm::Module& mod) { module = &mod; }

    void addTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) {
        if (!value || !typeInfo) return;
        valueTypes[value] = std::move(typeInfo);
    }

    void addFunctionTypeInfo(llvm::Function* function, LLVMFunctionTypeInfoPtr typeInfo) {
        if (!function || !typeInfo) return;
        functionTypes[function] = std::move(typeInfo);
    }

    void addClassTypeInfo(llvm::StructType* structType, LLVMClassTypeInfoPtr typeInfo) {
        if (!structType || !typeInfo) return;
        classTypes[structType] = std::move(typeInfo);
    }

    TypeInfoPtr getTypeInfo(llvm::Value* value) const {
        auto it = valueTypes.find(value);
        return it != valueTypes.end() ? it->second : nullptr;
    }

    LLVMFunctionTypeInfoPtr getFunctionTypeInfo(llvm::Function* function) const {
        auto it = functionTypes.find(function);
        return it != functionTypes.end() ? it->second : nullptr;
    }

    LLVMClassTypeInfoPtr getClassTypeInfo(llvm::StructType* structType) const {
        auto it = classTypes.find(structType);
        return it != classTypes.end() ? it->second : nullptr;
    }

private:
    llvm::LLVMContext* context;
    llvm::Module* module;
    std::unordered_map<llvm::Value*, TypeInfoPtr> valueTypes;
    std::unordered_map<llvm::Function*, LLVMFunctionTypeInfoPtr> functionTypes;
    std::unordered_map<llvm::StructType*, LLVMClassTypeInfoPtr> classTypes;
};

} // namespace pryst
