#pragma once

#include <string>
#include <memory>
#include <vector>
#include "../../../../include/type.hpp"

namespace pryst {
namespace core {

// Forward declarations
class UnionType;
class IntersectionType;
class HigherKindedType;
class ParameterizedType;

class UnionType : public Type {
public:
    UnionType(const std::vector<std::shared_ptr<core::Type>>& types)
        : Type(Kind::Class), types_(types) {}

    std::string toString() const override {
        std::string result;
        for (size_t i = 0; i < types_.size(); ++i) {
            if (i > 0) result += " | ";
            result += types_[i]->toString();
        }
        return result;
    }

    const std::vector<std::shared_ptr<core::Type>>& getTypes() const { return types_; }
    bool isUnion() const { return true; }

private:
    std::vector<std::shared_ptr<core::Type>> types_;
};

class IntersectionType : public Type {
public:
    IntersectionType(const std::vector<std::shared_ptr<core::Type>>& types)
        : Type(Kind::Class), types_(types) {}

    std::string toString() const override {
        std::string result;
        for (size_t i = 0; i < types_.size(); ++i) {
            if (i > 0) result += " & ";
            result += types_[i]->toString();
        }
        return result;
    }

    const std::vector<std::shared_ptr<core::Type>>& getTypes() const { return types_; }
    bool isIntersection() const { return true; }

private:
    std::vector<std::shared_ptr<core::Type>> types_;
};

class HigherKindedType : public Type {
public:
    HigherKindedType(const std::string& name, const std::vector<std::string>& typeParams)
        : Type(Kind::Class), name_(name), typeParameters_(typeParams) {}

    std::string toString() const override {
        std::string result = name_ + "<";
        for (size_t i = 0; i < typeParameters_.size(); ++i) {
            if (i > 0) result += ", ";
            result += typeParameters_[i];
        }
        result += ">";
        return result;
    }

    const std::string& getName() const { return name_; }
    const std::vector<std::string>& getTypeParameters() const { return typeParameters_; }
    bool isHigherKinded() const { return true; }

private:
    std::string name_;
    std::vector<std::string> typeParameters_;
};

class ParameterizedType : public Type {
public:
    ParameterizedType(const std::string& baseType, const std::vector<std::shared_ptr<core::Type>>& typeArgs)
        : Type(Kind::Class), baseType_(baseType), typeArguments_(typeArgs) {}

    std::string toString() const override {
        std::string result = baseType_ + "<";
        for (size_t i = 0; i < typeArguments_.size(); ++i) {
            if (i > 0) result += ", ";
            result += typeArguments_[i]->toString();
        }
        result += ">";
        return result;
    }

    const std::string& getBaseType() const { return baseType_; }
    const std::vector<std::shared_ptr<core::Type>>& getTypeArguments() const { return typeArguments_; }
    bool isParameterized() const { return true; }

private:
    std::string baseType_;
    std::vector<std::shared_ptr<core::Type>> typeArguments_;
};

} // namespace core
} // namespace pryst
