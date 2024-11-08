#pragma once

// Include project headers first
#include "../semantic/type_info.hpp"
#include "../utils/debug.hpp"

// Then include LLVM headers
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

// Standard library headers
#include <unordered_map>
#include <string>
#include <memory>

namespace pryst {

class LLVMTypeRegistry {
public:
    LLVMTypeRegistry(llvm::LLVMContext& context, llvm::IRBuilder<>& builder, llvm::Module& module)
        : context(&context), builder(builder), module(module) {
        PRYST_DEBUG("Initializing LLVMTypeRegistry");
        initialize();
    }

    void initialize() {
        PRYST_DEBUG("Initializing built-in types");
        // Register basic types
        registerBasicType("void", llvm::Type::getVoidTy(*context));
        registerBasicType("bool", llvm::Type::getInt1Ty(*context));
        registerBasicType("int", llvm::Type::getInt32Ty(*context));
        registerBasicType("float", llvm::Type::getFloatTy(*context));
        // Use opaque pointer for string type
        registerBasicType("string", createOpaquePointer());
    }

    llvm::Type* getVoidType() {
        auto type = getType("void");
        if (!type) {
            type = llvm::Type::getVoidTy(*context);
            registerBasicType("void", type);
        }
        return type;
    }

    llvm::Type* getIntType(unsigned bits = 32) {
        if (bits == 32) {
            auto type = getType("int");
            if (!type) {
                type = llvm::Type::getInt32Ty(*context);
                registerBasicType("int", type);
            }
            return type;
        }
        return llvm::Type::getIntNTy(*context, bits);
    }

    llvm::Type* getFloatType() {
        auto type = getType("float");
        if (!type) {
            type = llvm::Type::getFloatTy(*context);
            registerBasicType("float", type);
        }
        return type;
    }

    llvm::Type* getBoolType() {
        auto type = getType("bool");
        if (!type) {
            type = llvm::Type::getInt1Ty(*context);
            registerBasicType("bool", type);
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

    llvm::Type* createOpaquePointer() {
        // Create an opaque pointer type with addrspace 0
        return llvm::PointerType::get(*context, 0);
    }

    void registerBasicType(const std::string& name, llvm::Type* type) {
        if (!type) {
            PRYST_ERROR("Attempted to register null type for " + name);
            return;
        }
        PRYST_DEBUG("Registering basic type: " + name);
        typeCache[name] = type;
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
                else if (typeName == "string") result = createOpaquePointer();
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

            case TypeInfo::Kind::Class: {
                auto classType = std::dynamic_pointer_cast<ClassTypeInfo>(type);
                if (!classType) {
                    PRYST_ERROR("Failed to cast to ClassTypeInfo");
                    return nullptr;
                }

                std::vector<llvm::Type*> memberTypes;
                for (const auto& [name, type] : classType->getMembers()) {
                    if (auto memberType = getLLVMType(type, context)) {
                        memberTypes.push_back(memberType);
                    }
                }

                result = llvm::StructType::create(context, memberTypes, classType->getName());
                break;
            }

            case TypeInfo::Kind::Array: {
                auto arrayType = std::dynamic_pointer_cast<ArrayTypeInfo>(type);
                if (!arrayType) {
                    PRYST_ERROR("Failed to cast to ArrayTypeInfo");
                    return nullptr;
                }

                auto elementType = getLLVMType(arrayType->getElementType(), context);
                if (!elementType) {
                    PRYST_ERROR("Failed to get array element type");
                    return nullptr;
                }

                result = llvm::ArrayType::get(elementType, arrayType->getSize());
                break;
            }

            case TypeInfo::Kind::Pointer: {
                auto ptrType = std::dynamic_pointer_cast<PointerTypeInfo>(type);
                if (!ptrType) {
                    PRYST_ERROR("Failed to cast to PointerTypeInfo");
                    return nullptr;
                }

                result = createOpaquePointer();
                break;
            }

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

    // Convert a value from one type to another
    llvm::Value* convertValue(llvm::Value* value, llvm::Type* targetType) {
        if (!value || !targetType) {
            PRYST_ERROR("Null value or target type in conversion");
            return nullptr;
        }

        llvm::Type* sourceType = value->getType();
        if (sourceType == targetType) {
            return value;
        }

        // Integer to floating point
        if (sourceType->isIntegerTy() && targetType->isFloatingPointTy()) {
            return builder.CreateSIToFP(value, targetType, "int2float");
        }

        // Floating point to integer
        if (sourceType->isFloatingPointTy() && targetType->isIntegerTy()) {
            return builder.CreateFPToSI(value, targetType, "float2int");
        }

        // Integer or float to string
        if ((sourceType->isIntegerTy() || sourceType->isFloatingPointTy()) &&
            targetType == getStringType()) {
            // Call runtime conversion function
            std::vector<llvm::Value*> args = {value};
            if (sourceType->isIntegerTy()) {
                return builder.CreateCall(module.getFunction("int_to_string"), args, "int2str");
            } else {
                return builder.CreateCall(module.getFunction("float_to_string"), args, "float2str");
            }
        }

        PRYST_ERROR("Unsupported type conversion");
        return nullptr;
    }

    // Get default value for a type
    llvm::Value* getDefaultValue(llvm::Type* type) {
        if (!type) {
            PRYST_ERROR("Null type in getDefaultValue");
            return nullptr;
        }

        if (type->isIntegerTy()) {
            return llvm::ConstantInt::get(type, 0);
        }
        if (type->isFloatingPointTy()) {
            return llvm::ConstantFP::get(type, 0.0);
        }
        if (type == getStringType()) {
            // Return empty string
            return builder.CreateCall(module.getFunction("create_empty_string"), {}, "empty_str");
        }
        if (type->isPointerTy()) {
            return llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(type));
        }

        PRYST_ERROR("Unsupported type for default value");
        return nullptr;
    }

private:
    llvm::LLVMContext* context;
    std::unordered_map<std::string, llvm::Type*> typeCache;
    llvm::IRBuilder<>& builder;
    llvm::Module& module;
};

} // namespace pryst
