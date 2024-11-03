#pragma once

#include "../semantic/type_info.hpp"
#include "type_metadata.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <iostream>
#include <mutex>
#include <stdexcept>

// LLVM-specific type registry extensions
class LLVMTypeRegistry {
public:
    static LLVMTypeRegistry& getInstance() {
        std::cerr << "DEBUG: Getting LLVMTypeRegistry instance - START" << std::endl;
        static bool initialized = false;
        static LLVMTypeRegistry instance;
        if (!initialized) {
            std::cerr << "DEBUG: First time initialization of LLVMTypeRegistry instance" << std::endl;
            initialized = true;
        } else {
            std::cerr << "DEBUG: Returning existing LLVMTypeRegistry instance" << std::endl;
        }
        std::cerr << "DEBUG: Getting LLVMTypeRegistry instance - END" << std::endl;
        return instance;
    }

    // Convert TypeInfo to LLVM Type
    llvm::Type* getLLVMType(TypeInfoPtr type, llvm::LLVMContext& context) {
        if (!type) {
            std::cerr << "DEBUG: getLLVMType called with null type" << std::endl;
            return nullptr;
        }

        std::cerr << "DEBUG: getLLVMType for type: " << type->getName() << std::endl;
        const std::string& typeName = type->getName();

        switch (type->getKind()) {
            case TypeInfo::Kind::Basic:
                std::cerr << "DEBUG: Processing basic type: " << typeName << std::endl;
                if (typeName == "int")
                    return llvm::Type::getInt32Ty(context);
                if (typeName == "float")
                    return llvm::Type::getDoubleTy(context);
                if (typeName == "bool")
                    return llvm::Type::getInt1Ty(context);
                if (typeName == "str")
                    return llvm::Type::getInt8Ty(context);  // Strings are opaque i8
                break;
            case TypeInfo::Kind::Function: {
                std::cerr << "DEBUG: Processing function type" << std::endl;
                auto funcType = std::dynamic_pointer_cast<FunctionTypeInfo>(type);
                if (!funcType) return nullptr;

                std::vector<llvm::Type*> paramTypes;
                for (const auto& paramType : funcType->getParamTypes()) {
                    if (auto llvmType = getLLVMType(paramType, context))
                        paramTypes.push_back(llvmType);
                }

                auto returnType = getLLVMType(funcType->getReturnType(), context);
                if (!returnType) return nullptr;

                return llvm::FunctionType::get(returnType, paramTypes, false);
            }
            case TypeInfo::Kind::Class:
                std::cerr << "DEBUG: Processing class type as opaque i8" << std::endl;
                return llvm::Type::getInt8Ty(context);
            case TypeInfo::Kind::Array:
                std::cerr << "DEBUG: Processing array type as opaque i8" << std::endl;
                return llvm::Type::getInt8Ty(context);
            case TypeInfo::Kind::Pointer:
                std::cerr << "DEBUG: Processing pointer type as opaque i8" << std::endl;
                return llvm::Type::getInt8Ty(context);
            default:
                std::cerr << "DEBUG: Unknown type kind" << std::endl;
                break;
        }
        return nullptr;
    }

private:
    LLVMTypeRegistry() {
        std::cerr << "DEBUG: LLVMTypeRegistry constructor - START" << std::endl;
        std::cerr << "DEBUG: LLVMTypeRegistry constructor - END" << std::endl;
    }
    ~LLVMTypeRegistry() = default;
    LLVMTypeRegistry(const LLVMTypeRegistry&) = delete;
    LLVMTypeRegistry& operator=(const LLVMTypeRegistry&) = delete;
};
