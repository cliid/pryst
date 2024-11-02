#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>

namespace pryst {

// Forward declarations
class TypeInfo;
class FunctionTypeInfo;
class ClassTypeInfo;

using TypeInfoPtr = std::shared_ptr<TypeInfo>;
using FunctionTypeInfoPtr = std::shared_ptr<FunctionTypeInfo>;
using ClassTypeInfoPtr = std::shared_ptr<ClassTypeInfo>;

// Base class for all type information
class TypeInfo {
public:
    enum class Kind {
        Basic,
        Function,
        Class,
        Array
    };

    TypeInfo(Kind kind, const std::string& name) : kind_(kind), name_(name) {}
    virtual ~TypeInfo() = default;

    Kind getKind() const { return kind_; }
    const std::string& getName() const { return name_; }

    // Type conversion and checking
    virtual bool isConvertibleTo(const TypeInfoPtr& other) const = 0;
    virtual std::string toString() const = 0;

    // Reflection support
    virtual bool hasMethod(const std::string& name) const { return false; }
    virtual bool hasField(const std::string& name) const { return false; }
    virtual TypeInfoPtr getMethodType(const std::string& name) const { return nullptr; }
    virtual TypeInfoPtr getFieldType(const std::string& name) const { return nullptr; }

protected:
    Kind kind_;
    std::string name_;
};

// Basic types (int, float, bool, str)
class BasicTypeInfo : public TypeInfo {
public:
    BasicTypeInfo(const std::string& name) : TypeInfo(Kind::Basic, name) {}

    bool isConvertibleTo(const TypeInfoPtr& other) const override {
        if (other->getKind() != Kind::Basic) return false;

        // Allow numeric conversions
        if ((name_ == "int" || name_ == "float") &&
            (other->getName() == "int" || other->getName() == "float")) {
            return true;
        }

        // Allow conversion to string
        if (other->getName() == "str") return true;

        return name_ == other->getName();
    }

    std::string toString() const override {
        return name_;
    }
};

// Function type information
class FunctionTypeInfo : public TypeInfo {
public:
    FunctionTypeInfo(TypeInfoPtr returnType,
                    std::vector<TypeInfoPtr> paramTypes)
        : TypeInfo(Kind::Function, "fn"),
          returnType_(returnType),
          paramTypes_(std::move(paramTypes)) {}

    const TypeInfoPtr& getReturnType() const { return returnType_; }
    const std::vector<TypeInfoPtr>& getParamTypes() const { return paramTypes_; }

    bool isConvertibleTo(const TypeInfoPtr& other) const override {
        if (other->getKind() != Kind::Function) return false;
        auto otherFn = std::static_pointer_cast<FunctionTypeInfo>(other);

        // Check return type compatibility
        if (!returnType_->isConvertibleTo(otherFn->returnType_)) return false;

        // Check parameter types compatibility
        if (paramTypes_.size() != otherFn->paramTypes_.size()) return false;
        for (size_t i = 0; i < paramTypes_.size(); ++i) {
            if (!paramTypes_[i]->isConvertibleTo(otherFn->paramTypes_[i])) {
                return false;
            }
        }
        return true;
    }

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

// Class type information
class ClassTypeInfo : public TypeInfo {
public:
    ClassTypeInfo(const std::string& name,
                 ClassTypeInfoPtr parent = nullptr)
        : TypeInfo(Kind::Class, name),
          parent_(parent) {}

    void addMethod(const std::string& name, FunctionTypeInfoPtr type) {
        methods_[name] = type;
    }

    void addField(const std::string& name, TypeInfoPtr type) {
        fields_[name] = type;
    }

    bool hasMethod(const std::string& name) const override {
        return methods_.find(name) != methods_.end() ||
               (parent_ && parent_->hasMethod(name));
    }

    bool hasField(const std::string& name) const override {
        return fields_.find(name) != fields_.end() ||
               (parent_ && parent_->hasField(name));
    }

    TypeInfoPtr getMethodType(const std::string& name) const override {
        auto it = methods_.find(name);
        if (it != methods_.end()) return it->second;
        return parent_ ? parent_->getMethodType(name) : nullptr;
    }

    TypeInfoPtr getFieldType(const std::string& name) const override {
        auto it = fields_.find(name);
        if (it != fields_.end()) return it->second;
        return parent_ ? parent_->getFieldType(name) : nullptr;
    }

    bool isConvertibleTo(const TypeInfoPtr& other) const override {
        if (other->getKind() != Kind::Class) return false;
        auto otherClass = std::static_pointer_cast<ClassTypeInfo>(other);

        // Check if this class is the same as or inherits from the other class
        const ClassTypeInfo* current = this;
        while (current) {
            if (current->getName() == otherClass->getName()) return true;
            current = current->parent_.get();
        }
        return false;
    }

    std::string toString() const override {
        return name_;
    }

private:
    ClassTypeInfoPtr parent_;
    std::unordered_map<std::string, FunctionTypeInfoPtr> methods_;
    std::unordered_map<std::string, TypeInfoPtr> fields_;
};

// Type registry for managing type information
class TypeRegistry {
public:
    static TypeRegistry& getInstance() {
        static TypeRegistry instance;
        return instance;
    }

    // Basic types
    TypeInfoPtr getIntType() { return getOrCreateBasicType("int"); }
    TypeInfoPtr getFloatType() { return getOrCreateBasicType("float"); }
    TypeInfoPtr getBoolType() { return getOrCreateBasicType("bool"); }
    TypeInfoPtr getStrType() { return getOrCreateBasicType("str"); }

    // Function types
    TypeInfoPtr getFunctionType(TypeInfoPtr returnType,
                              const std::vector<TypeInfoPtr>& paramTypes) {
        auto fnType = std::make_shared<FunctionTypeInfo>(returnType, paramTypes);
        return registerType(fnType);
    }

    // Class types
    ClassTypeInfoPtr createClassType(const std::string& name,
                                   ClassTypeInfoPtr parent = nullptr) {
        auto classType = std::make_shared<ClassTypeInfo>(name, parent);
        types_[name] = classType;
        return classType;
    }

    TypeInfoPtr lookupType(const std::string& name) {
        auto it = types_.find(name);
        return it != types_.end() ? it->second : nullptr;
    }

private:
    TypeRegistry() {
        // Register basic types
        getIntType();
        getFloatType();
        getBoolType();
        getStrType();
    }

    TypeInfoPtr getOrCreateBasicType(const std::string& name) {
        auto it = types_.find(name);
        if (it != types_.end()) return it->second;

        auto type = std::make_shared<BasicTypeInfo>(name);
        types_[name] = type;
        return type;
    }

    TypeInfoPtr registerType(TypeInfoPtr type) {
        types_[type->toString()] = type;
        return type;
    }

    std::unordered_map<std::string, TypeInfoPtr> types_;
};

} // namespace pryst
