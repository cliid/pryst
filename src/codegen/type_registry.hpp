#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <antlr4-runtime.h>
#include "../semantic/type_info.hpp"
#include <memory>
#include <string>
#include <map>

namespace pryst {

class LLVMTypeRegistry {
public:
    LLVMTypeRegistry(llvm::LLVMContext& context) : context(context) {}

    // Basic type getters
    llvm::Type* getVoidType() { return llvm::Type::getVoidTy(context); }
    llvm::Type* getIntType() { return llvm::Type::getInt32Ty(context); }
    llvm::Type* getFloatType() { return llvm::Type::getDoubleTy(context); }
    llvm::Type* getBoolType() { return llvm::Type::getInt1Ty(context); }

    // String type (opaque pointer to i8)
    llvm::Type* getStrType() {
        return llvm::PointerType::get(context, 0);
    }

    // Pointer type handling for LLVM 20.0.0 opaque pointers
    llvm::Type* getPointerType() {
        return llvm::PointerType::get(context, 0);
    }

    // Function type creation
    llvm::FunctionType* getFunctionType(llvm::Type* returnType,
                                      llvm::ArrayRef<llvm::Type*> paramTypes,
                                      bool isVarArg = false) {
        return llvm::FunctionType::get(returnType, paramTypes, isVarArg);
    }

    // Array type creation
    llvm::ArrayType* getArrayType(llvm::Type* elementType, uint64_t size) {
        return llvm::ArrayType::get(elementType, size);
    }

    // Struct type creation
    llvm::StructType* getStructType(llvm::ArrayRef<llvm::Type*> elements,
                                   const std::string& name = "",
                                   bool isPacked = false) {
        if (name.empty()) {
            return llvm::StructType::get(context, elements, isPacked);
        }
        auto* existingType = llvm::StructType::getTypeByName(context, name);
        if (existingType) {
            return existingType;
        }
        return llvm::StructType::create(context, elements, name, isPacked);
    }

    // Type registration and lookup
    void registerType(const std::string& name, TypeInfoPtr typeInfo, llvm::Type* llvmType) {
        typeInfoMap[name] = typeInfo;
        llvmTypeMap[name] = llvmType;
    }

    TypeInfoPtr lookupType(const std::string& name) {
        auto it = typeInfoMap.find(name);
        return (it != typeInfoMap.end()) ? it->second : nullptr;
    }

    llvm::Type* lookupLLVMType(const std::string& name) {
        auto it = llvmTypeMap.find(name);
        return (it != llvmTypeMap.end()) ? it->second : nullptr;
    }

    // Type conversion and parsing methods
    llvm::Type* getType(antlr4::tree::ParseTree* typeContext);
    llvm::Type* getClassType(const std::string& className);
    llvm::Value* convertType(llvm::Value* value, llvm::Type* targetType, llvm::IRBuilder<>* builder);
    llvm::Value* convertClassType(llvm::Value* value, llvm::Type* targetType, llvm::IRBuilder<>* builder);
    llvm::Type* getLLVMType(TypeInfoPtr typeInfo);

private:
    llvm::LLVMContext& context;
    std::map<std::string, TypeInfoPtr> typeInfoMap;
    std::map<std::string, llvm::Type*> llvmTypeMap;
};

} // namespace pryst
