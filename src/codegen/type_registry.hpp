#pragma once

#include "type_metadata.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

namespace pryst {

class TypeRegistry {
public:
    static TypeRegistry& getInstance() {
        static TypeRegistry instance;
        return instance;
    }

    TypeInfoPtr getIntType() {
        if (!intType) {
            intType = std::make_shared<BasicTypeInfo>(TypeKind::Int);
        }
        return intType;
    }

    TypeInfoPtr getFloatType() {
        if (!floatType) {
            floatType = std::make_shared<BasicTypeInfo>(TypeKind::Float);
        }
        return floatType;
    }

    TypeInfoPtr getBoolType() {
        if (!boolType) {
            boolType = std::make_shared<BasicTypeInfo>(TypeKind::Bool);
        }
        return boolType;
    }

    TypeInfoPtr getStrType() {
        if (!strType) {
            strType = std::make_shared<BasicTypeInfo>(TypeKind::String);
        }
        return strType;
    }

    TypeInfoPtr getFunctionType(const std::string& name, llvm::FunctionType* type) {
        return std::make_shared<FunctionTypeInfo>(name, type);
    }

    TypeInfoPtr getPointerType() {
        if (!pointerType) {
            pointerType = std::make_shared<BasicTypeInfo>(TypeKind::Pointer);
        }
        return pointerType;
    }

    TypeInfoPtr lookupType(const std::string& name) {
        auto it = namedTypes.find(name);
        return it != namedTypes.end() ? it->second : nullptr;
    }

    void registerType(const std::string& name, TypeInfoPtr type) {
        namedTypes[name] = type;
    }

private:
    TypeRegistry() = default;
    ~TypeRegistry() = default;
    TypeRegistry(const TypeRegistry&) = delete;
    TypeRegistry& operator=(const TypeRegistry&) = delete;

    TypeInfoPtr intType;
    TypeInfoPtr floatType;
    TypeInfoPtr boolType;
    TypeInfoPtr strType;
    TypeInfoPtr pointerType;
    std::unordered_map<std::string, TypeInfoPtr> namedTypes;
};

} // namespace pryst
