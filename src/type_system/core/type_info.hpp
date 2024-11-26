#pragma once

#include "types.hpp"
#include <string>
#include <memory>
#include <sstream>

namespace pryst {

class TypeInfo : public Type {
public:
    explicit TypeInfo(std::shared_ptr<Type> describedType, bool isNullable = false)
        : Type(Kind::MetaType),
          describedType_(describedType),
          isNullable_(isNullable) {}

    std::string getName() const { return describedType_->toString(); }
    std::string getFullName() const { return describedType_->toString(); }
    bool isNullable() const { return isNullable_; }
    std::string getKind() const {
        std::stringstream ss;
        ss << describedType_->getKind();
        return ss.str();
    }
    bool isInterface() const { return describedType_->getKind() == Kind::Interface; }
    bool isArray() const { return describedType_->getKind() == Kind::Array; }
    bool isClass() const { return describedType_->getKind() == Kind::Class; }
    bool isPrimitive() const {
        auto kind = describedType_->getKind();
        return kind == Kind::Int || kind == Kind::Float ||
               kind == Kind::Bool || kind == Kind::String;
    }

    std::string toString() const override {
        return "TypeInfo<" + describedType_->toString() + ">";
    }

private:
    std::shared_ptr<Type> describedType_;
    bool isNullable_;
};

} // namespace pryst
