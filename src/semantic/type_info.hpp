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
        Array,
        Pointer
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

    bool isConvertibleTo(const TypeInfoPtr& other) const override;


    std::string toString() const override;
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

    bool isConvertibleTo(const TypeInfoPtr& other) const override;

    std::string toString() const override;

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

    const ClassTypeInfoPtr& getParent() const { return parent_; }

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

    bool isConvertibleTo(const TypeInfoPtr& other) const override;

    std::string toString() const override;

private:
    ClassTypeInfoPtr parent_;
    std::unordered_map<std::string, FunctionTypeInfoPtr> methods_;
    std::unordered_map<std::string, TypeInfoPtr> fields_;
};

// Type registry for managing type information
class TypeRegistry {
public:
    static TypeRegistry& getInstance();

    // Basic types
    TypeInfoPtr getIntType() { return getOrCreateBasicType("int"); }
    TypeInfoPtr getFloatType() { return getOrCreateBasicType("float"); }
    TypeInfoPtr getBoolType() { return getOrCreateBasicType("bool"); }
    TypeInfoPtr getStrType() { return getOrCreateBasicType("str"); }
    TypeInfoPtr getPointerType() { return getOrCreateBasicType("pointer"); }

    // Function types
    TypeInfoPtr getFunctionType(TypeInfoPtr returnType,
                              const std::vector<TypeInfoPtr>& paramTypes);

    // Class types
    ClassTypeInfoPtr createClassType(const std::string& name,
                                   ClassTypeInfoPtr parent = nullptr);

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

    TypeInfoPtr getOrCreateBasicType(const std::string& name);

    TypeInfoPtr registerType(TypeInfoPtr type);

    std::unordered_map<std::string, TypeInfoPtr> types_;
};

} // namespace pryst
