#pragma once

#include <string>
#include <memory>
#include <stdexcept>
#include <vector>

namespace pryst {

class Type {
public:
    enum class Kind {
        Primitive,
        Nullable,
        Error,
        Function,
        Class,
        Array
    };

    explicit Type(Kind kind) : kind_(kind) {}
    virtual ~Type() = default;

    virtual std::string toString() const = 0;

    virtual bool isPrimitive() const { return false; }
    virtual bool isNullable() const { return false; }
    virtual bool isError() const { return false; }
    virtual bool isFunction() const { return false; }
    virtual bool isClass() const { return false; }
    virtual bool isArray() const { return false; }

    Kind getKind() const { return kind_; }

protected:
    Kind kind_;
};

class Error : public std::runtime_error {
public:
    Error(const std::string& type, const std::string& message)
        : std::runtime_error(message), type_(type) {}

    const std::string& getType() const { return type_; }

private:
    std::string type_;
};

class ErrorType : public Type {
public:
    explicit ErrorType(const std::string& name) : Type(Kind::Error), name_(name) {}
    std::string toString() const override { return name_; }
    bool isError() const override { return true; }
private:
    std::string name_;
};

class PrimitiveType : public Type {
public:
    explicit PrimitiveType(const std::string& name, bool isError = false)
        : Type(isError ? Kind::Error : Kind::Primitive), name_(name) {}
    std::string toString() const override { return name_; }
    bool isPrimitive() const override { return !isError(); }
    bool isError() const override { return getKind() == Kind::Error; }
private:
    std::string name_;
};

class FunctionType : public Type {
public:
    FunctionType(const std::vector<std::shared_ptr<Type>>& paramTypes, std::shared_ptr<Type> returnType)
        : Type(Kind::Function), parameterTypes_(paramTypes), returnType_(returnType) {}

    std::string toString() const override {
        std::string result = "(";
        for (size_t i = 0; i < parameterTypes_.size(); ++i) {
            if (i > 0) result += ", ";
            result += parameterTypes_[i]->toString();
        }
        result += ") -> " + returnType_->toString();
        return result;
    }

    bool isFunction() const override { return true; }
    const std::vector<std::shared_ptr<Type>>& getParameterTypes() const { return parameterTypes_; }
    std::shared_ptr<Type> getReturnType() const { return returnType_; }

private:
    std::vector<std::shared_ptr<Type>> parameterTypes_;
    std::shared_ptr<Type> returnType_;
};

class NullableType : public Type {
public:
    explicit NullableType(const std::string& baseTypeName)
        : Type(Kind::Nullable), baseTypeName_(baseTypeName) {}

    std::string toString() const override { return baseTypeName_ + "?"; }
    bool isNullable() const override { return true; }
    std::string getBaseType() const { return baseTypeName_; }

private:
    std::string baseTypeName_;
};

class GenericType : public Type {
public:
    explicit GenericType(const std::string& name)
        : Type(Kind::Class), name_(name) {}

    std::string toString() const override { return name_; }  // Return name as-is, type parameters included
    bool isClass() const override { return true; }

private:
    std::string name_;
};

class ArrayType : public Type {
public:
    explicit ArrayType(std::shared_ptr<Type> elementType)
        : Type(Kind::Array), elementType_(elementType) {}

    std::string toString() const override {
        return elementType_->toString() + "[]";
    }

    bool isArray() const override { return true; }
    std::shared_ptr<Type> getElementType() const { return elementType_; }

private:
    std::shared_ptr<Type> elementType_;
};

} // namespace pryst
