#pragma once

#include "../semantic/type_info.hpp"
#include "../utils/logger.hpp"
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace pryst {

class TypeMetadata;
class LLVMTypeRegistry;
class ClassTypeInfo;

using ClassTypeInfoPtr = std::shared_ptr<ClassTypeInfo>;

namespace pryst {

// Helper functions declarations
bool isSubclassOf(const ClassTypeInfoPtr& derived, const ClassTypeInfoPtr& base);
size_t getMemberIndexInHierarchy(const ClassTypeInfoPtr& classInfo, const std::string& memberName);
bool isInstanceOf(const TypeInfoPtr& type, const ClassTypeInfoPtr& classType);

// LLVM-specific type information that extends semantic types

class LLVMTypeInfo {
public:
    virtual ~LLVMTypeInfo() = default;
    virtual llvm::Type* getLLVMType() const = 0;
};

using LLVMTypeInfoPtr = std::shared_ptr<LLVMTypeInfo>;

// LLVM-specific function type information
class LLVMFunctionTypeInfo : public pryst::FunctionTypeInfo, public LLVMTypeInfo {
public:
    LLVMFunctionTypeInfo(const std::string& name,
                        pryst::TypeInfoPtr returnType,
                        std::vector<pryst::TypeInfoPtr> paramTypes,
                        llvm::FunctionType* type)
        : FunctionTypeInfo(name, returnType, std::move(paramTypes)),
          llvmType(type) {}

    llvm::Type* getLLVMType() const override { return llvmType; }
    llvm::FunctionType* getFunctionType() const { return llvmType; }
    llvm::FunctionType* getFunctionType(llvm::LLVMContext& context) const;

private:
    llvm::FunctionType* createFunctionType(llvm::LLVMContext& context) const;
    llvm::FunctionType* llvmType;
};

// LLVM-specific class type information
class LLVMClassTypeInfo : public pryst::ClassTypeInfo, public LLVMTypeInfo {
public:
    LLVMClassTypeInfo(const std::string& name,
                      llvm::StructType* type,
                      std::shared_ptr<ClassTypeInfo> parent = nullptr)
        : ClassTypeInfo(name),
          structType(type),
          parentClass(parent) {}

    llvm::Type* getLLVMType() const override { return structType; }
    llvm::StructType* getStructType() const { return structType; }
    void addMember(const std::string& name, size_t index, TypeInfoPtr type);
    TypeInfoPtr getMemberType(const std::string& name) const;
    size_t getMemberIndex(const std::string& memberName) const;
    TypeInfoPtr getMemberTypeInfo(const std::string& memberName) const;
    std::string getClassName() const;

private:
    llvm::StructType* structType;
    std::unordered_map<std::string, size_t> memberIndices;
    std::unordered_map<std::string, TypeInfoPtr> memberTypes;
    std::shared_ptr<ClassTypeInfo> parentClass;
};

using LLVMFunctionTypeInfoPtr = std::shared_ptr<LLVMFunctionTypeInfo>;
using LLVMClassTypeInfoPtr = std::shared_ptr<LLVMClassTypeInfo>;

// Type metadata management class

class TypeMetadata {
public:
    TypeMetadata(llvm::LLVMContext& ctx, llvm::Module& mod);

    void addTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo);
    void addFunctionTypeInfo(llvm::Function* function, LLVMFunctionTypeInfoPtr typeInfo);
    void addClassTypeInfo(llvm::StructType* structType, LLVMClassTypeInfoPtr typeInfo);

    TypeInfoPtr getTypeInfo(llvm::Value* value) const;
    LLVMFunctionTypeInfoPtr getFunctionTypeInfo(llvm::Function* function) const;
    LLVMClassTypeInfoPtr getClassTypeInfo(llvm::StructType* structType) const;

private:
    llvm::LLVMContext& context;
    llvm::Module& module;
    std::unordered_map<llvm::Value*, TypeInfoPtr> typeInfoMap;
    std::unordered_map<llvm::Function*, LLVMFunctionTypeInfoPtr> functionTypes;
    std::unordered_map<llvm::StructType*, LLVMClassTypeInfoPtr> classTypes;
};

} // namespace pryst
