#pragma once

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
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
    void registerType(const std::string& name, llvm::Type* type) {
        typeMap[name] = type;
    }

    llvm::Type* lookupType(const std::string& name) {
        auto it = typeMap.find(name);
        return (it != typeMap.end()) ? it->second : nullptr;
    }

private:
    llvm::LLVMContext& context;
    std::map<std::string, llvm::Type*> typeMap;
};

} // namespace pryst
