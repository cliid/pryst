#pragma once

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <memory>
#include <unordered_map>
#include <string>

namespace pryst {

enum class TypeKind {
    Int,
    Float,
    Bool,
    String,
    Function,
    Class,
    Array,
    Void,
    Pointer
};

class TypeInfo;
class FunctionTypeInfo;
class ClassTypeInfo;

using TypeInfoPtr = std::shared_ptr<TypeInfo>;
using FunctionTypeInfoPtr = std::shared_ptr<FunctionTypeInfo>;
using ClassTypeInfoPtr = std::shared_ptr<ClassTypeInfo>;

// Base class for type information
class TypeInfo {
public:
    explicit TypeInfo(TypeKind kind) : kind(kind) {}
    virtual ~TypeInfo() = default;
    virtual std::string getTypeName() const {
        switch (kind) {
            case TypeKind::Int: return "int";
            case TypeKind::Float: return "float";
            case TypeKind::Bool: return "bool";
            case TypeKind::String: return "string";
            case TypeKind::Void: return "void";
            case TypeKind::Pointer: return "pointer";
            default: return "unknown";
        }
    }
    virtual bool isClass() const { return kind == TypeKind::Class; }
    virtual bool isFunction() const { return kind == TypeKind::Function; }
    TypeKind getKind() const { return kind; }

protected:
    TypeKind kind;
};

// Basic type implementations
class BasicTypeInfo : public TypeInfo {
public:
    explicit BasicTypeInfo(TypeKind kind) : TypeInfo(kind) {}
    std::string getTypeName() const override {
        return TypeInfo::getTypeName();
    }
};

// Type information for functions
class FunctionTypeInfo : public TypeInfo {
public:
    FunctionTypeInfo(std::string name, llvm::FunctionType* type)
        : TypeInfo(TypeKind::Function), name(std::move(name)), functionType(type) {}

    std::string getTypeName() const override { return name; }
    llvm::FunctionType* getFunctionType() const { return functionType; }

private:
    std::string name;
    llvm::FunctionType* functionType;
};

// Type information for classes
class ClassTypeInfo : public TypeInfo {
public:
    ClassTypeInfo(std::string name, llvm::StructType* type)
        : TypeInfo(TypeKind::Class), name(std::move(name)), structType(type) {}

    std::string getTypeName() const override { return name; }
    llvm::StructType* getStructType() const { return structType; }
    llvm::Type* getLLVMType() const { return structType; }

    void setBaseClass(ClassTypeInfoPtr base) { baseClass = std::move(base); }
    ClassTypeInfoPtr getBaseClass() const { return baseClass; }

    void addMember(std::string memberName, size_t index, TypeInfoPtr type) {
        memberIndices[memberName] = index;
        memberTypes[memberName] = std::move(type);
    }

    size_t getMemberIndex(const std::string& memberName) const {
        auto it = memberIndices.find(memberName);
        if (it != memberIndices.end()) {
            return it->second;
        }
        if (baseClass) {
            return baseClass->getMemberIndex(memberName);
        }
        throw std::runtime_error("Member not found: " + memberName);
    }

    TypeInfoPtr getMemberType(const std::string& memberName) const {
        auto it = memberTypes.find(memberName);
        if (it != memberTypes.end()) {
            return it->second;
        }
        if (baseClass) {
            return baseClass->getMemberType(memberName);
        }
        throw std::runtime_error("Member type not found: " + memberName);
    }

private:
    std::string name;
    llvm::StructType* structType;
    ClassTypeInfoPtr baseClass;
    std::unordered_map<std::string, size_t> memberIndices;
    std::unordered_map<std::string, TypeInfoPtr> memberTypes;
};

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

    void addFunctionTypeInfo(llvm::Function* function, FunctionTypeInfoPtr typeInfo) {
        if (!function || !typeInfo) return;
        functionTypes[function] = std::move(typeInfo);
    }

    void addClassTypeInfo(llvm::StructType* structType, ClassTypeInfoPtr typeInfo) {
        if (!structType || !typeInfo) return;
        classTypes[structType] = std::move(typeInfo);
    }

    TypeInfoPtr getTypeInfo(llvm::Value* value) const {
        auto it = valueTypes.find(value);
        return it != valueTypes.end() ? it->second : nullptr;
    }

    FunctionTypeInfoPtr getFunctionTypeInfo(llvm::Function* function) const {
        auto it = functionTypes.find(function);
        return it != functionTypes.end() ? it->second : nullptr;
    }

    ClassTypeInfoPtr getClassTypeInfo(llvm::StructType* structType) const {
        auto it = classTypes.find(structType);
        return it != classTypes.end() ? it->second : nullptr;
    }

private:
    llvm::LLVMContext* context;
    llvm::Module* module;
    std::unordered_map<llvm::Value*, TypeInfoPtr> valueTypes;
    std::unordered_map<llvm::Function*, FunctionTypeInfoPtr> functionTypes;
    std::unordered_map<llvm::StructType*, ClassTypeInfoPtr> classTypes;
};

} // namespace pryst
