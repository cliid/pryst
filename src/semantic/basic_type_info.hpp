#pragma once

#include <string>
#include <vector>
#include <memory>
#include "type_info.hpp"
#include "type_kinds.hpp"

namespace pryst {

// Forward declarations
class TypeInfo;
using TypeInfoPtr = std::shared_ptr<TypeInfo>;

class BasicTypeInfo : public TypeInfo {
public:
    enum class BasicKind {
        Int,
        Float,
        Bool,
        String,
        Void,
        Class,  // Added Class type
        Unknown
    };

    BasicTypeInfo(BasicKind basicKind, const std::string& name, llvm::Type* llvmType)
        : TypeInfo(name, llvmType)
        , basicKind_(basicKind) {}

    BasicKind getBasicKind() const { return basicKind_; }
    TypeKind getKind() const override {
        switch (basicKind_) {
            case BasicKind::Int: return TypeKind::Int;
            case BasicKind::Float: return TypeKind::Float;
            case BasicKind::Bool: return TypeKind::Bool;
            case BasicKind::String: return TypeKind::String;
            case BasicKind::Void: return TypeKind::Void;
            case BasicKind::Class: return TypeKind::Class;
            case BasicKind::Unknown: return TypeKind::Unknown;
            default: return TypeKind::Unknown;
        }
    }

private:
    BasicKind basicKind_;
};

class ArrayTypeInfo : public TypeInfo {
public:
    ArrayTypeInfo(const std::string& name, llvm::Type* llvmType, TypeInfoPtr elementType)
        : TypeInfo(name, llvmType)
        , elementType_(elementType) {}

    TypeInfoPtr getElementType() const { return elementType_; }
    TypeKind getKind() const override { return TypeKind::Array; }

    std::string toString() const override {
        return elementType_->toString() + "[]";
    }

private:
    TypeInfoPtr elementType_;
};

class FunctionTypeInfo : public TypeInfo {
public:
    FunctionTypeInfo(const std::string& name, llvm::Type* llvmType,
                    TypeInfoPtr returnType, const std::vector<TypeInfoPtr>& paramTypes)
        : TypeInfo(name, llvmType)
        , returnType_(returnType)
        , paramTypes_(paramTypes) {}

    TypeInfoPtr getReturnType() const { return returnType_; }
    const std::vector<TypeInfoPtr>& getParamTypes() const { return paramTypes_; }
    TypeKind getKind() const override { return TypeKind::Function; }

    std::string toString() const override {
        std::string result = "fn<" + returnType_->toString() + ">(";
        for (size_t i = 0; i < paramTypes_.size(); ++i) {
            if (i > 0) result += ", ";
            result += paramTypes_[i]->toString();
        }
        result += ")";
        return result;
    }

private:
    TypeInfoPtr returnType_;
    std::vector<TypeInfoPtr> paramTypes_;
};

} // namespace pryst
