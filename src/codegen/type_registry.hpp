#pragma once

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "../utils/logger.hpp"
#include <unordered_map>
#include <string>
#include <memory>

namespace pryst {

class TypeRegistry {
public:
    explicit TypeRegistry(llvm::LLVMContext* context) : context(context) {
        initializeBasicTypes();
    }

    // Basic type getters
    llvm::Type* getVoidType() {
        return llvm::Type::getVoidTy(*context);
    }

    llvm::Type* getBoolType() {
        auto type = getType("bool");
        if (!type) {
            type = llvm::Type::getInt1Ty(*context);
            registerBasicType("bool", type);
        }
        return type;
    }

    llvm::Type* getIntType() {
        auto type = getType("int");
        if (!type) {
            type = llvm::Type::getInt32Ty(*context);
            registerBasicType("int", type);
        }
        return type;
    }

    llvm::Type* getFloatType() {
        auto type = getType("float");
        if (!type) {
            type = llvm::Type::getFloatTy(*context);
            registerBasicType("float", type);
        }
        return type;
    }

    llvm::Type* getStringType() {
        auto type = getType("string");
        if (!type) {
            type = createOpaquePointer();
            registerBasicType("string", type);
        }
        return type;
    }

    // Pointer type handling
    llvm::Type* getPointerType(const std::string& elementTypeName) {
        std::string pointerTypeName = elementTypeName + "*";
        auto type = getType(pointerTypeName);
        if (!type) {
            type = createOpaquePointer();
            typeCache[pointerTypeName] = type;
            elementTypes[pointerTypeName] = elementTypeName;
        }
        return type;
    }

    // Get element type name for a pointer type
    std::string getElementTypeName(const std::string& pointerTypeName) {
        auto it = elementTypes.find(pointerTypeName);
        if (it != elementTypes.end()) {
            return it->second;
        }
        PRYST_ERROR("Element type not found for pointer type: " + pointerTypeName);
        return "";
    }

    // Function type creation
    llvm::FunctionType* getFunctionType(llvm::Type* returnType,
                                      const std::vector<llvm::Type*>& paramTypes,
                                      bool isVarArg = false) {
        return llvm::FunctionType::get(returnType, paramTypes, isVarArg);
    }

    // Array type creation
    llvm::ArrayType* getArrayType(llvm::Type* elementType, uint64_t numElements) {
        return llvm::ArrayType::get(elementType, numElements);
    }

    // Struct type creation
    llvm::StructType* createStructType(const std::string& name,
                                     const std::vector<llvm::Type*>& elements) {
        return llvm::StructType::create(*context, elements, name);
    }

    // Type registration
    void registerType(const std::string& name, llvm::Type* type) {
        if (!type) {
            PRYST_ERROR("Attempted to register null type for " + name);
            return;
        }
        PRYST_DEBUG("Registering type: " + name);
        typeCache[name] = type;
    }

    // Type lookup
    llvm::Type* getType(const std::string& name) {
        auto it = typeCache.find(name);
        if (it != typeCache.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Type compatibility checking
    bool areTypesCompatible(llvm::Type* type1, llvm::Type* type2) {
        if (type1 == type2) return true;

        // Handle numeric type promotion (int to float)
        if (type1->isFloatTy() && type2->isIntegerTy(32)) return true;

        // All pointers are compatible with each other in LLVM 20.0.0
        if (type1->isPointerTy() && type2->isPointerTy()) return true;

        return false;
    }

private:
    llvm::LLVMContext* context;
    std::unordered_map<std::string, llvm::Type*> typeCache;
    std::unordered_map<std::string, std::string> elementTypes;

    void initializeBasicTypes() {
        registerBasicType("void", getVoidType());
        registerBasicType("bool", getBoolType());
        registerBasicType("int", getIntType());
        registerBasicType("float", getFloatType());
        registerBasicType("string", getStringType());
    }

    void registerBasicType(const std::string& name, llvm::Type* type) {
        if (!type) {
            PRYST_ERROR("Attempted to register null basic type for " + name);
            return;
        }
        PRYST_DEBUG("Registering basic type: " + name);
        typeCache[name] = type;
    }

    llvm::Type* createOpaquePointer() {
        return llvm::PointerType::get(*context, 0);
    }
};

} // namespace pryst
