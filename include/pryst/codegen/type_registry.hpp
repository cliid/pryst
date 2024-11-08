#pragma once

// Include project headers first
#include <pryst/semantic/type_info.hpp>
#include <pryst/utils/debug.hpp>

// Then include LLVM headers
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

// Standard library headers
#include <unordered_map>
#include <string>
#include <memory>

namespace pryst {

class LLVMTypeRegistry {
public:
    LLVMTypeRegistry(llvm::LLVMContext& context) : context(&context) {
        PRYST_DEBUG("Initializing LLVMTypeRegistry");
    }

    void registerType(TypeInfoPtr type) {
        if (!type) {
            PRYST_ERROR("Attempted to register null type");
            return;
        }
        PRYST_DEBUG("Registering type: " + type->getName());
        typeCache[type->getName()] = getLLVMType(type, *context);
    }

    llvm::Type* getType(const std::string& name) {
        auto it = typeCache.find(name);
        if (it != typeCache.end()) {
            return it->second;
        }
        PRYST_DEBUG("Type not found in cache: " + name);
        return nullptr;
    }

    llvm::Type* getLLVMType(TypeInfoPtr type, llvm::LLVMContext& context) {
        if (!type) {
            PRYST_ERROR("Attempted to get LLVM type for null TypeInfo");
            return nullptr;
        }

        auto it = typeCache.find(type->getName());
        if (it != typeCache.end()) {
            PRYST_DEBUG("Returning cached type for " + type->getName());
            return it->second;
        }

        PRYST_DEBUG("getLLVMType for type: " + type->getName());
        const std::string& typeName = type->getName();
        llvm::Type* result = nullptr;

        switch (type->getKind()) {
            case TypeInfo::Kind::Basic:
                if (typeName == "void") result = llvm::Type::getVoidTy(context);
                else if (typeName == "bool") result = llvm::Type::getInt1Ty(context);
                else if (typeName == "int") result = llvm::Type::getInt32Ty(context);
                else if (typeName == "float") result = llvm::Type::getFloatTy(context);
                else if (typeName == "string") result = llvm::PointerType::get(context, 0);
                break;

            case TypeInfo::Kind::Function: {
                auto funcType = std::dynamic_pointer_cast<FunctionTypeInfo>(type);
                if (!funcType) {
                    PRYST_ERROR("Failed to cast to FunctionTypeInfo");
                    return nullptr;
                }

                std::vector<llvm::Type*> paramTypes;
                for (const auto& paramType : funcType->getParamTypes()) {
                    if (auto llvmType = getLLVMType(paramType, context)) {
                        paramTypes.push_back(llvmType);
                    }
                }

                auto returnType = getLLVMType(funcType->getReturnType(), context);
                if (!returnType) {
                    PRYST_ERROR("Failed to get return type for function");
                    return nullptr;
                }

                result = llvm::FunctionType::get(returnType, paramTypes, false);
                break;
            }

            case TypeInfo::Kind::Class:
                // Handle class types (to be implemented)
                PRYST_DEBUG("Class type handling not yet implemented");
                break;

            case TypeInfo::Kind::Array:
                // Handle array types (to be implemented)
                PRYST_DEBUG("Array type handling not yet implemented");
                break;

            case TypeInfo::Kind::Pointer:
                // Handle pointer types (to be implemented)
                PRYST_DEBUG("Pointer type handling not yet implemented");
                break;

            default:
                PRYST_ERROR("Unknown type kind");
                return nullptr;
        }

        if (result) {
            typeCache[type->getName()] = result;
            PRYST_DEBUG("Cached type for " + type->getName());
        }

        return result;
    }

    llvm::Type* getLoadStoreType(TypeInfoPtr type, llvm::LLVMContext& context) {
        if (!type) {
            PRYST_ERROR("Attempted to get load/store type for null TypeInfo");
            return nullptr;
        }
        PRYST_DEBUG("Getting load/store type for " + type->getName());
        return getLLVMType(type, context);
    }

private:
    llvm::LLVMContext* context;
    std::unordered_map<std::string, llvm::Type*> typeCache;
};

} // namespace pryst
