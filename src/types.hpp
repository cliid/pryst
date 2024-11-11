#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace pryst {

class Type;
class PrimitiveType;
class ArrayType;
class MapType;
class FunctionType;
class ClassType;
class InterfaceType;
class ErrorPropagationType;
class NullableType;
class GenericType;

extern std::shared_ptr<Type> INT_TYPE;
extern std::shared_ptr<Type> FLOAT_TYPE;
extern std::shared_ptr<Type> BOOL_TYPE;
extern std::shared_ptr<Type> STRING_TYPE;
extern std::shared_ptr<Type> VOID_TYPE;
extern std::shared_ptr<Type> ERROR_TYPE;
extern std::shared_ptr<Type> NULL_TYPE;

class Type : public std::enable_shared_from_this<Type> {
public:
    enum class Kind {
        Int,
        Float,
        Bool,
        String,
        Void,
        Array,
        Map,
        Function,
        Class,
        Interface,
        Error,
        Any,
        Nullable,
        Generic,
        Null    // Add Null kind
    };

    explicit Type(Kind kind) : kind_(kind) {}
    virtual ~Type() = default;

    Kind getKind() const { return kind_; }

    // Add helper methods for null handling
    virtual bool isNullable() const {
        return kind_ == Kind::Nullable || kind_ == Kind::Null;
    }

    virtual bool canBeNull() const {
        return isNullable();
    }

    virtual std::shared_ptr<Type> makeNullable() {
        if (isNullable()) return std::static_pointer_cast<Type>(shared_from_this());
        auto nullable = std::make_shared<NullableType>(std::static_pointer_cast<Type>(shared_from_this()));
        return std::static_pointer_cast<Type>(nullable);
    }

    virtual std::string toString() const {
        switch(kind_) {
            case Kind::Int: return "int";
            case Kind::Float: return "float";
            case Kind::Bool: return "bool";
            case Kind::String: return "str";
            case Kind::Void: return "void";
            case Kind::Null: return "null";
            case Kind::Array: return "array";
            case Kind::Map: return "map";
            case Kind::Function: return "function";
            case Kind::Class: return "class";
            case Kind::Interface: return "interface";
            default: return "unknown";
        }
    }

protected:
    Kind kind_;
};

class PrimitiveType : public Type {
public:
    explicit PrimitiveType(Kind kind) : Type(kind) {}
};

class ArrayType : public Type {
public:
    explicit ArrayType(std::shared_ptr<Type> elementType)
        : Type(Kind::Array), elementType_(elementType) {}

    std::shared_ptr<Type> getElementType() const { return elementType_; }

private:
    std::shared_ptr<Type> elementType_;
};

class MapType : public Type {
public:
    MapType(std::shared_ptr<Type> keyType, std::shared_ptr<Type> valueType)
        : Type(Kind::Map), keyType_(keyType), valueType_(valueType) {}

    std::shared_ptr<Type> getKeyType() const { return keyType_; }
    std::shared_ptr<Type> getValueType() const { return valueType_; }

private:
    std::shared_ptr<Type> keyType_;
    std::shared_ptr<Type> valueType_;
};

class FunctionType : public Type {
public:
    // Constructor for fn<ReturnType>(paramTypes) syntax
    FunctionType(std::shared_ptr<Type> returnType, const std::vector<std::shared_ptr<Type>>& paramTypes)
        : Type(Kind::Function), returnType_(returnType), paramTypes_(paramTypes), isArrowSyntax_(false) {}

    // Constructor for (paramTypes) -> ReturnType syntax (for lambda expressions)
    static std::shared_ptr<FunctionType> createArrowType(
        const std::vector<std::shared_ptr<Type>>& paramTypes,
        std::shared_ptr<Type> returnType) {
        auto type = std::make_shared<FunctionType>(returnType, paramTypes);
        type->isArrowSyntax_ = true;
        return type;
    }

    std::shared_ptr<Type> getReturnType() const { return returnType_; }
    const std::vector<std::shared_ptr<Type>>& getParamTypes() const { return paramTypes_; }
    bool isArrowSyntax() const { return isArrowSyntax_; }

private:
    std::shared_ptr<Type> returnType_;
    std::vector<std::shared_ptr<Type>> paramTypes_;
    bool isArrowSyntax_;  // true for lambda expressions using arrow syntax
};

class ClassType : public Type {
public:
    explicit ClassType(const std::string& name,
                      const std::vector<std::shared_ptr<Type>>& genericParams = {},
                      std::shared_ptr<ClassType> baseClass = nullptr,
                      const std::vector<std::shared_ptr<InterfaceType>>& interfaces = {})
        : Type(Kind::Class), name_(name), genericParams_(genericParams),
          baseClass_(baseClass), interfaces_(interfaces) {}

    const std::string& getName() const { return name_; }
    const std::vector<std::shared_ptr<Type>>& getGenericParams() const { return genericParams_; }
    std::shared_ptr<ClassType> getBaseClass() const { return baseClass_; }
    const std::vector<std::shared_ptr<InterfaceType>>& getInterfaces() const { return interfaces_; }

    void addField(const std::string& name, std::shared_ptr<Type> type) {
        fields_[name] = type;
    }

    std::shared_ptr<Type> getField(const std::string& name) const {
        auto it = fields_.find(name);
        return it != fields_.end() ? it->second : nullptr;
    }

private:
    std::string name_;
    std::vector<std::shared_ptr<Type>> genericParams_;
    std::shared_ptr<ClassType> baseClass_;
    std::vector<std::shared_ptr<InterfaceType>> interfaces_;
    std::unordered_map<std::string, std::shared_ptr<Type>> fields_;
};

class ErrorPropagationType : public Type {
public:
    explicit ErrorPropagationType(std::shared_ptr<Type> innerType)
        : Type(Kind::Error), innerType_(innerType) {}

    std::shared_ptr<Type> getInnerType() const { return innerType_; }

private:
    std::shared_ptr<Type> innerType_;
};

class NullableType : public Type {
public:
    explicit NullableType(std::shared_ptr<Type> innerType)
        : Type(Kind::Nullable), innerType_(innerType) {}

    std::shared_ptr<Type> getInnerType() const { return innerType_; }

    bool isNullable() const override { return true; }
    bool canBeNull() const override { return true; }
    std::shared_ptr<Type> makeNullable() override {
        return std::static_pointer_cast<Type>(shared_from_this());
    }

private:
    std::shared_ptr<Type> innerType_;
};

// Type constants are defined in types.cpp

} // namespace pryst
