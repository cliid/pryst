#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <ostream>
#include <iostream>
#include <any>

// Forward declarations to avoid LLVM conflicts
namespace llvm {
    class Type;
    class LLVMContext;
}

namespace pryst {

// Ensure our type system is properly namespaced
namespace types {

class Type;
class ErrorType;
class UnionType;
class IntersectionType;
class PrimitiveType;
class ArrayType;
class MapType;
class FunctionType;
class ClassType;
class InterfaceType;
class NullableType;
class GenericType;
class TypeChecker;

// External type declarations
extern std::shared_ptr<Type> INT_TYPE;
extern std::shared_ptr<Type> FLOAT_TYPE;
extern std::shared_ptr<Type> BOOL_TYPE;
extern std::shared_ptr<Type> STRING_TYPE;
extern std::shared_ptr<Type> VOID_TYPE;
extern std::shared_ptr<Type> ERROR_TYPE;
extern std::shared_ptr<Type> NULL_TYPE;
extern std::shared_ptr<Type> ANY_TYPE;

class Type : public std::enable_shared_from_this<Type> {
public:
    enum class Kind {
        Int, Float, Bool, String, Void,
        Array, Map, Function, Class, Interface,
        Error, Any, Nullable, Generic, MetaType,
        Null, Union, Intersection
    };

    explicit Type(Kind kind) : kind_(kind) {}
    virtual ~Type() = default;
    virtual Kind getKind() const { return kind_; }
    virtual std::string toString() const;
    virtual bool isAssignableTo(const std::shared_ptr<Type>& other) const;
    virtual bool isInstanceOf(const std::shared_ptr<Type>& other) const {
        return this->isAssignableTo(other);
    }

    struct TypeCompare {
        bool operator()(const std::shared_ptr<Type>& a, const std::shared_ptr<Type>& b) const {
            return a->toString() < b->toString();
        }
    };

    virtual bool isArray() const { return kind_ == Kind::Array; }
    virtual bool isBasicType() const {
        return kind_ == Kind::Int || kind_ == Kind::Float ||
               kind_ == Kind::Bool || kind_ == Kind::String;
    }
    virtual bool isVoidType() const { return kind_ == Kind::Void; }
    virtual bool isNullable() const { return kind_ == Kind::Nullable || kind_ == Kind::Null; }
    virtual bool canBeNull() const { return isNullable(); }
    virtual bool isClassType() const { return kind_ == Kind::Class; }
    virtual bool isFunction() const { return false; }
    virtual bool isError() const { return kind_ == Kind::Error; }
    virtual bool isUnion() const { return kind_ == Kind::Union; }
    virtual bool isIntersection() const { return kind_ == Kind::Intersection; }
    virtual bool isGenericConstraint() const { return false; }

    virtual std::shared_ptr<Type> makeNullable() {
        if (isNullable()) return std::static_pointer_cast<Type>(shared_from_this());
        auto nullable = std::make_shared<NullableType>(std::static_pointer_cast<Type>(shared_from_this()));
        return std::static_pointer_cast<Type>(nullable);
    }

    virtual std::shared_ptr<Type> makeUnion(const std::shared_ptr<Type>& other) {
        std::vector<std::shared_ptr<Type>> types{shared_from_this(), other};
        return std::static_pointer_cast<Type>(std::make_shared<UnionType>(types));
    }

    virtual std::shared_ptr<Type> makeIntersection(const std::shared_ptr<Type>& other) {
        std::vector<std::shared_ptr<Type>> types{shared_from_this(), other};
        return std::static_pointer_cast<Type>(std::make_shared<IntersectionType>(types));
    }

    virtual bool isAssignableTo(const std::shared_ptr<Type>& other) const {
        if (kind_ == Kind::Null && other->isNullable()) {
            return true;  // null can be assigned to any nullable type
        }
        if (other->getKind() == Kind::Any) {
            return true;  // Any type can be assigned to ANY_TYPE
        }
        if (other->isUnion()) {
            auto unionType = std::static_pointer_cast<UnionType>(other);
            for (const auto& type : unionType->getTypes()) {
                if (isAssignableTo(type)) return true;
            }
            return false;
        }
        if (other->isIntersection()) {
            auto intersectionType = std::static_pointer_cast<IntersectionType>(other);
            for (const auto& type : intersectionType->getTypes()) {
                if (!isAssignableTo(type)) return false;
            }
            return true;
        }
        return kind_ == other->getKind();
    }

    virtual bool canConvertTo(const std::shared_ptr<Type>& other) const {
        if (kind_ == Kind::Null && other->isNullable()) {
            return true;
        }
        if (other->getKind() == Kind::Any || kind_ == Kind::Any) {
            return true;  // ANY_TYPE can convert to/from any type
        }
        if (other->isUnion()) {
            auto unionType = std::static_pointer_cast<UnionType>(other);
            return std::any_of(unionType->getTypes().begin(), unionType->getTypes().end(),
                [this](const auto& type) { return this->canConvertTo(type); });
        }
        if (other->isIntersection()) {
            auto intersectionType = std::static_pointer_cast<IntersectionType>(other);
            return std::all_of(intersectionType->getTypes().begin(), intersectionType->getTypes().end(),
                [this](const auto& type) { return this->canConvertTo(type); });
        }
        return kind_ == other->getKind();
    }

    virtual void addMethod(const std::string& name, std::shared_ptr<Type> returnType,
                         const std::vector<std::shared_ptr<Type>>& paramTypes = {}) {
        auto functionType = std::make_shared<FunctionType>(returnType, paramTypes);
        methods_[name] = std::static_pointer_cast<Type>(functionType);
    }

    virtual std::shared_ptr<Type> getMethod(const std::string& name) const {
        auto it = methods_.find(name);
        return it != methods_.end() ? it->second : nullptr;
    }

    virtual std::vector<std::string> getAvailableMethods() const {
        std::vector<std::string> methodNames;
        for (const auto& method : methods_) {
            methodNames.push_back(method.first);
        }
        return methodNames;
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
            case Kind::Any: return "any";
            case Kind::Union: return "union";
            case Kind::Intersection: return "intersection";
            default: return "unknown";
        }
    }

protected:
    Kind kind_;
    std::unordered_map<std::string, std::shared_ptr<Type>> methods_;
};

class ErrorType : public Type {
public:
    ErrorType(const std::string& message, const std::string& errorType = "TypeError")
        : message_(message), errorType_(errorType) {}

    Kind getKind() const override { return Kind::Error; }
    const std::string& getMessage() const { return message_; }
    const std::string& getErrorType() const { return errorType_; }
    bool isError() const { return true; }

    std::shared_ptr<ErrorType> chain(const std::string& message) const {
        return std::make_shared<ErrorType>(message + ": " + message_, errorType_);
    }

    std::shared_ptr<ErrorType> transform(const std::string& newType) const {
        return std::make_shared<ErrorType>(message_, newType);
    }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (auto otherError = std::dynamic_pointer_cast<ErrorType>(other)) {
            return errorType_ == otherError->getErrorType() || isSubtypeOf(*otherError);
        }
        return false;
    }

    bool isSubtypeOf(const ErrorType& other) const {
        return errorType_ == other.getErrorType();
    }

    std::string toString() const override {
        return "error<" + errorType_ + ">: " + message_;
    }

private:
    std::string message_;
    std::string errorType_;
};

class UnionType : public Type {
public:
    UnionType(const std::vector<std::shared_ptr<Type>>& types)
        : Type(Kind::Union), types_(types) {}
    UnionType(std::shared_ptr<Type> first, std::shared_ptr<Type> second)
        : Type(Kind::Union) {
        types_.push_back(first);
        types_.push_back(second);
    }

    Kind getKind() const override { return Kind::Union; }
    const std::vector<std::shared_ptr<Type>>& getTypes() const { return types_; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (auto unionType = std::dynamic_pointer_cast<UnionType>(other)) {
            for (const auto& type : unionType->getTypes()) {
                if (isAssignableTo(type)) return true;
            }
            return false;
        }
        if (auto intersectionType = std::dynamic_pointer_cast<IntersectionType>(other)) {
            return isAssignableTo(intersectionType->getFirst()) && isAssignableTo(intersectionType->getSecond());
        }
        return std::all_of(types_.begin(), types_.end(),
                          [&other](const auto& type) { return type->isAssignableTo(other); });
    }

    std::string toString() const override {
        std::string result;
        for (size_t i = 0; i < types_.size(); ++i) {
            if (i > 0) result += " | ";
            result += types_[i]->toString();
        }
        return result;
    }

private:
    std::vector<std::shared_ptr<Type>> types_;
};

class IntersectionType : public Type {
public:
    IntersectionType(const std::vector<std::shared_ptr<Type>>& types)
        : Type(Kind::Intersection), types_(types) {}
    IntersectionType(std::shared_ptr<Type> first, std::shared_ptr<Type> second)
        : Type(Kind::Intersection) {
        types_.push_back(first);
        types_.push_back(second);
    }

    Kind getKind() const override { return Kind::Intersection; }
    const std::vector<std::shared_ptr<Type>>& getTypes() const { return types_; }
    std::shared_ptr<Type> getFirst() const { return types_[0]; }
    std::shared_ptr<Type> getSecond() const { return types_[1]; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (auto intersectionType = std::dynamic_pointer_cast<IntersectionType>(other)) {
            return isAssignableTo(intersectionType->getFirst()) &&
                   isAssignableTo(intersectionType->getSecond());
        }
        return std::all_of(types_.begin(), types_.end(),
                          [&other](const auto& type) { return type->isAssignableTo(other); });
    }

    std::string toString() const override {
        std::string result;
        for (size_t i = 0; i < types_.size(); ++i) {
            if (i > 0) result += " & ";
            result += types_[i]->toString();
        }
        return result;
    }

private:
    std::vector<std::shared_ptr<Type>> types_;
};

class PrimitiveType : public Type {
public:
    explicit PrimitiveType(Kind kind) : Type(kind) {}
};

class ArrayType : public Type {
public:
    explicit ArrayType(std::shared_ptr<Type> elementType)
        : Type(Kind::Array), elementType_(elementType) {
        // Add array methods
        addMethod("length", INT_TYPE);
        addMethod("get", elementType, {INT_TYPE});
        addMethod("set", VOID_TYPE, {INT_TYPE, elementType});
    }

    std::shared_ptr<Type> getElementType() const { return elementType_; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (auto otherArray = std::dynamic_pointer_cast<ArrayType>(other)) {
            return elementType_->isAssignableTo(otherArray->getElementType());
        }
        return Type::isAssignableTo(other);
    }

    bool canConvertTo(const std::shared_ptr<Type>& other) const override {
        if (auto otherArray = std::dynamic_pointer_cast<ArrayType>(other)) {
            return elementType_->canConvertTo(otherArray->getElementType());
        }
        return Type::canConvertTo(other);
    }

    std::string toString() const override {
        return elementType_->toString() + "[]";
    }

private:
    std::shared_ptr<Type> elementType_;
};

class MapType : public Type {
public:
    MapType(std::shared_ptr<Type> keyType, std::shared_ptr<Type> valueType)
        : Type(Kind::Map) {
        std::cout << "Debug [MapType]: Creating map type with key=" << keyType->toString()
                  << " value=" << valueType->toString() << std::endl;

        // Use global type constants for primitive types
        switch(keyType->getKind()) {
            case Kind::String:
                keyType_ = STRING_TYPE;
                break;
            case Kind::Int:
                keyType_ = INT_TYPE;
                break;
            case Kind::Float:
                keyType_ = FLOAT_TYPE;
                break;
            case Kind::Bool:
                keyType_ = BOOL_TYPE;
                break;
            case Kind::Array:
                if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(keyType)) {
                    keyType_ = std::make_shared<ArrayType>(arrayType->getElementType());
                }
                break;
            case Kind::Map:
                if (auto mapType = std::dynamic_pointer_cast<MapType>(keyType)) {
                    keyType_ = std::make_shared<MapType>(mapType->getKeyType(), mapType->getValueType());
                }
                break;
            default:
                keyType_ = keyType;  // For other types, keep original reference
        }

        switch(valueType->getKind()) {
            case Kind::String:
                valueType_ = STRING_TYPE;
                break;
            case Kind::Int:
                valueType_ = INT_TYPE;
                break;
            case Kind::Float:
                valueType_ = FLOAT_TYPE;
                break;
            case Kind::Bool:
                valueType_ = BOOL_TYPE;
                break;
            case Kind::Array:
                if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(valueType)) {
                    valueType_ = std::make_shared<ArrayType>(arrayType->getElementType());
                }
                break;
            case Kind::Map:
                if (auto mapType = std::dynamic_pointer_cast<MapType>(valueType)) {
                    valueType_ = std::make_shared<MapType>(mapType->getKeyType(), mapType->getValueType());
                }
                break;
            default:
                valueType_ = valueType;  // For other types, keep original reference
        }
    }

    std::shared_ptr<Type> getKeyType() const { return keyType_; }
    std::shared_ptr<Type> getValueType() const { return valueType_; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (auto otherMap = std::dynamic_pointer_cast<MapType>(other)) {
            return keyType_->isAssignableTo(otherMap->getKeyType()) &&
                   valueType_->isAssignableTo(otherMap->getValueType());
        }
        return Type::isAssignableTo(other);
    }

    bool canConvertTo(const std::shared_ptr<Type>& other) const override {
        if (auto otherMap = std::dynamic_pointer_cast<MapType>(other)) {
            return keyType_->canConvertTo(otherMap->getKeyType()) &&
                   valueType_->canConvertTo(otherMap->getValueType());
        }
        return Type::canConvertTo(other);
    }

    std::string toString() const override {
        return "Map<" + keyType_->toString() + ", " + valueType_->toString() + ">";
    }

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
    const std::vector<std::shared_ptr<Type>>& getParameterTypes() const { return paramTypes_; }
    bool isArrowSyntax() const { return isArrowSyntax_; }

    bool isFunction() const override { return true; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (auto otherFunc = std::dynamic_pointer_cast<FunctionType>(other)) {
            return isCompatibleWith(otherFunc);
        }
        return Type::isAssignableTo(other);
    }

    bool canConvertTo(const std::shared_ptr<Type>& other) const override {
        if (auto otherFunc = std::dynamic_pointer_cast<FunctionType>(other)) {
            return isCompatibleWith(otherFunc);
        }
        return Type::canConvertTo(other);
    }

    std::string toString() const override {
        std::string result = "fn";
        if (!isArrowSyntax_) {
            result += "<" + returnType_->toString() + ">";
        }
        result += "(";
        for (size_t i = 0; i < paramTypes_.size(); ++i) {
            if (i > 0) result += ", ";
            result += paramTypes_[i]->toString();
        }
        result += ")";
        if (isArrowSyntax_) {
            result += " -> " + returnType_->toString();
        }
        return result;
    }

    // Check if this function type is compatible with another (for method overriding)
    bool isCompatibleWith(const std::shared_ptr<FunctionType>& other) const {
        if (!other) return false;

        // Return type must be covariant (same type or more specific)
        if (!returnType_->isInstanceOf(other->getReturnType())) {
            return false;
        }

        // Parameter types must be contravariant (same type or more general)
        const auto& otherParams = other->getParameterTypes();
        if (paramTypes_.size() != otherParams.size()) {
            return false;
        }

        for (size_t i = 0; i < paramTypes_.size(); ++i) {
            if (!otherParams[i]->isInstanceOf(paramTypes_[i])) {
                return false;
            }
        }

        return true;
    }

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

    void setBaseType(std::shared_ptr<Type> baseType) {
        if (auto classType = std::dynamic_pointer_cast<ClassType>(baseType)) {
            baseClass_ = classType;
        }
    }

    void addField(const std::string& name, std::shared_ptr<Type> type) {
        fields_[name] = type;
    }

    std::shared_ptr<Type> getField(const std::string& name) const {
        auto it = fields_.find(name);
        return it != fields_.end() ? it->second : nullptr;
    }

    void addMethod(const std::string& name, std::shared_ptr<Type> returnType,
                  const std::vector<std::shared_ptr<Type>>& paramTypes = {}) override {
        auto functionType = std::make_shared<FunctionType>(returnType, paramTypes);
        methods_[name] = std::static_pointer_cast<Type>(functionType);
    }

    bool isInstanceOf(const std::shared_ptr<Type>& other) const override;

    std::vector<std::string> getAvailableMembers() const {
        std::vector<std::string> members;
        for (const auto& field : fields_) {
            members.push_back(field.first);
        }
        return members;
    }

    std::string toString() const override {
        return name_;
    }

private:
    std::string name_;
    std::vector<std::shared_ptr<Type>> genericParams_;
    std::shared_ptr<ClassType> baseClass_;
    std::vector<std::shared_ptr<InterfaceType>> interfaces_;
    std::unordered_map<std::string, std::shared_ptr<Type>> fields_;
};

class InterfaceType : public Type {
public:
    explicit InterfaceType(const std::string& name)
        : Type(Kind::Interface), name_(name) {}

    const std::string& getName() const { return name_; }

    void addMethod(const std::string& name, std::shared_ptr<Type> returnType,
                  const std::vector<std::shared_ptr<Type>>& paramTypes = {}) override {
        auto functionType = std::make_shared<FunctionType>(returnType, paramTypes);
        methods_[name] = std::static_pointer_cast<Type>(functionType);
    }

    std::string toString() const override {
        return name_;
    }

private:
    std::string name_;
    std::unordered_map<std::string, std::shared_ptr<Type>> methods_;
};

class ErrorPropagationType : public Type {
public:
    explicit ErrorPropagationType(std::shared_ptr<Type> innerType)
        : Type(Kind::Error), innerType_(innerType) {}

    std::shared_ptr<Type> getInnerType() const { return innerType_; }

    bool isError() const override { return true; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (auto errorType = std::dynamic_pointer_cast<ErrorPropagationType>(other)) {
            return innerType_->isAssignableTo(errorType->getInnerType());
        }
        return false;
    }

    std::string toString() const override {
        return "error<" + innerType_->toString() + ">";
    }

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

    std::shared_ptr<Type> getField(const std::string& name) const {
        if (auto classType = std::dynamic_pointer_cast<ClassType>(innerType_)) {
            auto field = classType->getField(name);
            if (field) {
                return field->makeNullable();
            }
        }
        return nullptr;
    }

    std::shared_ptr<Type> getMethod(const std::string& name) const override {
        // First check if the method exists in our own methods map
        auto it = methods_.find(name);
        if (it != methods_.end()) {
            return it->second;
        }
        // If not found, delegate to inner type
        auto innerMethod = innerType_->getMethod(name);
        if (innerMethod) {
            // Make the return type nullable since this is a nullable type
            return innerMethod->makeNullable();
        }
        return nullptr;
    }

    void addMethod(const std::string& name, std::shared_ptr<Type> returnType,
                  const std::vector<std::shared_ptr<Type>>& paramTypes = {}) override {
        // Add method to inner type instead of this wrapper
        innerType_->addMethod(name, returnType, paramTypes);
    }

    std::vector<std::string> getAvailableMethods() const override {
        // Combine methods from both this type and inner type
        auto methods = Type::getAvailableMethods();
        auto innerMethods = innerType_->getAvailableMethods();
        methods.insert(methods.end(), innerMethods.begin(), innerMethods.end());
        return methods;
    }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (other->isNullable()) {
            if (kind_ == Kind::Null) {
                return true;  // null can be assigned to any nullable type
            }
            auto otherNullable = std::static_pointer_cast<NullableType>(other);
            return innerType_->isAssignableTo(otherNullable->getInnerType());
        }
        return false;  // Cannot assign nullable type to non-nullable type
    }

    bool canConvertTo(const std::shared_ptr<Type>& other) const override {
        if (other->isNullable()) {
            if (kind_ == Kind::Null) {
                return true;  // null can be converted to any nullable type
            }
            auto otherNullable = std::static_pointer_cast<NullableType>(other);
            return innerType_->canConvertTo(otherNullable->getInnerType());
        }
        return false;  // Cannot convert nullable type to non-nullable type
    }

    std::string toString() const override {
        return innerType_->toString() + "?";
    }

    std::shared_ptr<Type> propagateNull(const std::shared_ptr<Type>& chainedType) const {
        return chainedType->makeNullable();
    }

private:
    std::shared_ptr<Type> innerType_;
};

class UnionType : public Type {
public:
    UnionType(const std::vector<std::shared_ptr<Type>>& types)
        : Type(Kind::Union), types_(types) {}

    bool satisfiesConstraint(const std::shared_ptr<Type>& type) const;

    bool isGenericConstraint() const override { return true; }

    const std::vector<std::shared_ptr<Type>>& getTypes() const { return types_; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        // A value of union type can be assigned to a target type if any of its constituent types can be assigned
        for (const auto& type : types_) {
            if (type->isAssignableTo(other)) {
                return true;
            }
        }
        return false;
    }

    bool canConvertTo(const std::shared_ptr<Type>& other) const override {
        // A union type can be converted to another type if any of its constituent types can be converted
        for (const auto& type : types_) {
            if (type->canConvertTo(other)) {
                return true;
            }
        }
        return false;
    }

    std::string toString() const override {
        std::string result;
        for (size_t i = 0; i < types_.size(); ++i) {
            if (i > 0) result += " | ";
            result += types_[i]->toString();
        }
        return result;
    }

private:
    std::vector<std::shared_ptr<Type>> types_;
};

class IntersectionType : public Type {
public:
    IntersectionType(const std::vector<std::shared_ptr<Type>>& types)
        : Type(Kind::Intersection), types_(types) {}

    bool satisfiesConstraint(const std::shared_ptr<Type>& type) const;

    bool isGenericConstraint() const override { return true; }

    const std::vector<std::shared_ptr<Type>>& getTypes() const { return types_; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        // An intersection type is assignable to another type if all of its constituent types are assignable
        for (const auto& type : types_) {
            if (!type->isAssignableTo(other)) {
                return false;
            }
        }
        return true;
    }

    bool canConvertTo(const std::shared_ptr<Type>& other) const override {
        // An intersection type can be converted to another type if any of its constituent types can be converted
        for (const auto& type : types_) {
            if (type->canConvertTo(other)) {
                return true;
            }
        }
        return false;
    }

    std::string toString() const override {
        std::string result;
        for (size_t i = 0; i < types_.size(); ++i) {
            if (i > 0) result += " & ";
            result += types_[i]->toString();
        }
        return result;
    }

private:
    std::vector<std::shared_ptr<Type>> types_;
};

class GenericType : public Type {
public:
    GenericType(const std::string& name, std::shared_ptr<Type> constraint = nullptr)
        : Type(Kind::Generic), name_(name), constraint_(constraint) {}

    const std::string& getName() const { return name_; }
    std::shared_ptr<Type> getConstraint() const { return constraint_; }

    bool isAssignableTo(const std::shared_ptr<Type>& other) const override {
        if (constraint_) {
            if (constraint_->isUnion()) {
                auto unionType = std::static_pointer_cast<UnionType>(constraint_);
                return unionType->satisfiesConstraint(other);
            }
            if (constraint_->isIntersection()) {
                auto intersectionType = std::static_pointer_cast<IntersectionType>(constraint_);
                return intersectionType->satisfiesConstraint(other);
            }
            return other->isInstanceOf(constraint_);
        }
        return true;  // No constraint means any type is allowed
    }

    std::string toString() const override {
        if (constraint_) {
            return name_ + " extends " + constraint_->toString();
        }
        return name_;
    }

private:
    std::string name_;
    std::shared_ptr<Type> constraint_;
};

inline llvm::raw_ostream& operator<<(llvm::raw_ostream& os, const Type::Kind& kind) {
    switch(kind) {
        case Type::Kind::Int: return os << "Int";
        case Type::Kind::Float: return os << "Float";
        case Type::Kind::Bool: return os << "Bool";
        case Type::Kind::String: return os << "String";
        case Type::Kind::Void: return os << "Void";
        case Type::Kind::Array: return os << "Array";
        case Type::Kind::Map: return os << "Map";
        case Type::Kind::Function: return os << "Function";
        case Type::Kind::Class: return os << "Class";
        case Type::Kind::Interface: return os << "Interface";
        case Type::Kind::Error: return os << "Error";
        case Type::Kind::Any: return os << "Any";
        case Type::Kind::Nullable: return os << "Nullable";
        case Type::Kind::Generic: return os << "Generic";
        case Type::Kind::Null: return os << "Null";
        case Type::Kind::Union: return os << "Union";
        case Type::Kind::Intersection: return os << "Intersection";
        default: return os << "Unknown";
    }
}

inline std::ostream& operator<<(std::ostream& os, const Type::Kind& kind) {
    switch(kind) {
        case Type::Kind::Int: return os << "Int";
        case Type::Kind::Float: return os << "Float";
        case Type::Kind::Bool: return os << "Bool";
        case Type::Kind::String: return os << "String";
        case Type::Kind::Void: return os << "Void";
        case Type::Kind::Array: return os << "Array";
        case Type::Kind::Map: return os << "Map";
        case Type::Kind::Function: return os << "Function";
        case Type::Kind::Class: return os << "Class";
        case Type::Kind::Interface: return os << "Interface";
        case Type::Kind::Error: return os << "Error";
        case Type::Kind::Any: return os << "Any";
        case Type::Kind::Nullable: return os << "Nullable";
        case Type::Kind::Generic: return os << "Generic";
        case Type::Kind::Null: return os << "Null";
        case Type::Kind::Union: return os << "Union";
        case Type::Kind::Intersection: return os << "Intersection";
        default: return os << "Unknown";
    }
}

// Implement Type::isInstanceOf
inline bool Type::isInstanceOf(const std::shared_ptr<Type>& other) const {
    if (kind_ == other->getKind()) return true;

    if (other->isUnion()) {
        auto unionType = std::static_pointer_cast<UnionType>(other);
        auto nonConstThis = std::const_pointer_cast<Type>(shared_from_this());
        return unionType->satisfiesConstraint(nonConstThis);
    }

    if (other->isIntersection()) {
        auto intersectionType = std::static_pointer_cast<IntersectionType>(other);
        auto nonConstThis = std::const_pointer_cast<Type>(shared_from_this());
        return intersectionType->satisfiesConstraint(nonConstThis);
    }

    if (kind_ == Kind::Nullable) {
        auto nullableType = std::static_pointer_cast<NullableType>(shared_from_this());
        return nullableType->getInnerType()->isInstanceOf(other);
    }

    return false;
}

// Implement ClassType::isInstanceOf
inline bool ClassType::isInstanceOf(const std::shared_ptr<Type>& other) const {
    if (!other) return false;
    if (Type::isInstanceOf(other)) return true;

    if (other->isUnion()) {
        auto unionType = std::static_pointer_cast<UnionType>(other);
        auto nonConstThis = std::const_pointer_cast<Type>(shared_from_this());
        return unionType->satisfiesConstraint(nonConstThis);
    }

    if (other->isIntersection()) {
        auto intersectionType = std::static_pointer_cast<IntersectionType>(other);
        auto nonConstThis = std::const_pointer_cast<Type>(shared_from_this());
        return intersectionType->satisfiesConstraint(nonConstThis);
    }

    if (auto otherClass = std::dynamic_pointer_cast<ClassType>(other)) {
        // Check base class hierarchy
        for (auto current = baseClass_; current; current = current->getBaseClass()) {
            if (current->getName() == otherClass->getName()) return true;
        }

        // Check interfaces
        for (const auto& interface : interfaces_) {
            if (interface->getName() == otherClass->getName()) {
                return true;
            }
        }
    } else if (auto otherInterface = std::dynamic_pointer_cast<InterfaceType>(other)) {
        return name_ == otherInterface->getName();
    }
    return false;
}

// Type constants are defined in types.cpp

} // namespace pryst
