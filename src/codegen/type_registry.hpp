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

    bool isSameType(const TypeInfoPtr& type1, const TypeInfoPtr& type2) const {
        if (!type1 || !type2) return false;
        return type1->getName() == type2->getName();
    }

    // Main implementation of getLLVMType
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

    llvm::PointerType* getOpaquePointerType(llvm::LLVMContext& context) const {
        return llvm::PointerType::get(context, 0);
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

    // Get TypeInfo by name
    std::shared_ptr<TypeInfo> getTypeInfo(const std::string& typeName) const {
        auto it = typeInfoCache.find(typeName);
        return (it != typeInfoCache.end()) ? it->second : nullptr;
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

    // Alias for getStringType to maintain compatibility
    llvm::Type* getStrType() {
        return getStringType();
    }

    // Get pointer type for LLVM 20.0.0 compatibility
    llvm::Type* getPointerType(llvm::Type* elementType) {
        return llvm::PointerType::get(*context, 0);
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

    llvm::Type* getLoadStoreType(TypeInfoPtr type, llvm::LLVMContext& context) {
        if (!type) {
            PRYST_ERROR("Attempted to get load/store type for null TypeInfo");
            return nullptr;
        }
        PRYST_DEBUG("Getting load/store type for " + type->getName());
        return getLLVMType(type, context);
    }

    // Convert a value from one type to another
    llvm::Value* convertValue(llvm::Value* value, TypeInfoPtr fromType, TypeInfoPtr toType, llvm::IRBuilder<>& builder) {
        if (!value || !fromType || !toType) {
            PRYST_ERROR("Invalid arguments for type conversion");
            return nullptr;
        }

        // If types are the same, no conversion needed
        if (isSameType(fromType, toType)) {
            return value;
        }

        // Handle basic type conversions
        if (fromType->getKind() == TypeInfo::Kind::Basic && toType->getKind() == TypeInfo::Kind::Basic) {
            const std::string& fromName = fromType->getName();
            const std::string& toName = toType->getName();

            // Integer to float conversion
            if (fromName == "int" && toName == "float") {
                return builder.CreateSIToFP(value, llvm::Type::getFloatTy(builder.getContext()), "int_to_float");
            }

            // Float to integer conversion
            if (fromName == "float" && toName == "int") {
                return builder.CreateFPToSI(value, llvm::Type::getInt32Ty(builder.getContext()), "float_to_int");
            }

            // Integer to boolean conversion
            if (fromName == "int" && toName == "bool") {
                return builder.CreateICmpNE(value, llvm::ConstantInt::get(llvm::Type::getInt32Ty(builder.getContext()), 0), "int_to_bool");
            }

            // Boolean to integer conversion
            if (fromName == "bool" && toName == "int") {
                return builder.CreateZExt(value, llvm::Type::getInt32Ty(builder.getContext()), "bool_to_int");
            }
        }

        PRYST_ERROR("Unsupported type conversion from " + fromType->getName() + " to " + toType->getName());
        return nullptr;
    }

    // Get default value for a type
    llvm::Value* getDefaultValue(TypeInfoPtr type) {
        if (!type) {
            PRYST_ERROR("Attempted to get default value for null type");
            return nullptr;
        }

        const std::string& typeName = type->getName();
        if (typeName == "int") return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0);
        if (typeName == "float") return llvm::ConstantFP::get(llvm::Type::getFloatTy(*context), 0.0);
        if (typeName == "bool") return llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context), 0);
        if (typeName == "string") return llvm::ConstantPointerNull::get(llvm::PointerType::get(*context, 0));

        PRYST_ERROR("No default value implemented for type: " + typeName);
        return nullptr;
    }

    // Get TypeInfo from LLVM Type
    TypeInfoPtr getTypeInfoFromLLVMType(llvm::Type* type) {
        if (!type) {
            PRYST_ERROR("Attempted to get TypeInfo for null LLVM type");
            return nullptr;
        }

        std::string typeName = getLLVMTypeName(type);
        if (typeName.empty()) {
            PRYST_ERROR("Could not determine type name for LLVM type");
            return nullptr;
        }

        return getTypeInfo(typeName);
    }

private:
    // Helper method to get type name from LLVM type
    std::string getLLVMTypeName(llvm::Type* type) {
        if (!type) return "";

        if (type->isVoidTy()) return "void";
        if (type->isIntegerTy(32)) return "int";
        if (type->isFloatTy()) return "float";
        if (type->isIntegerTy(1)) return "bool";
        if (type->isPointerTy()) return "string";

        PRYST_ERROR("Unknown LLVM type encountered");
        return "";
    }

    llvm::LLVMContext* context;
    llvm::IRBuilder<>& builder;
    llvm::Module& module;
    std::unordered_map<std::string, llvm::Type*> typeCache;
    std::unordered_map<std::string, TypeInfoPtr> typeInfoCache;

public:
    // Semantic type info management
    TypeInfoPtr getTypeInfo(const std::string& name) {
        auto it = typeInfoCache.find(name);
        if (it != typeInfoCache.end()) {
            return it->second;
        }
        PRYST_DEBUG("Type info not found in cache: " + name);
        return nullptr;
    }

    void registerTypeInfo(TypeInfoPtr typeInfo) {
        if (!typeInfo) {
            PRYST_ERROR("Attempted to register null type info");
            return;
        }
        PRYST_DEBUG("Registering type info: " + typeInfo->getName());
        typeInfoCache[typeInfo->getName()] = typeInfo;
        // Also register corresponding LLVM type
        registerType(typeInfo);
    }
};

} // namespace pryst
