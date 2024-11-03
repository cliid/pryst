#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include <iostream>
#include <mutex>
#include <stdexcept>

// Forward declarations
class TypeInfo;
class FunctionTypeInfo;
class ClassTypeInfo;
class TypeRegistry;

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

    // Helper functions for type checking
    static bool isNumericType(const TypeInfoPtr& type);
    static TypeInfoPtr getCommonNumericType(const TypeInfoPtr& t1, const TypeInfoPtr& t2);

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

    FunctionTypeInfoPtr getMethod(const std::string& name) const {
        auto it = methods_.find(name);
        if (it != methods_.end()) return it->second;
        return parent_ ? parent_->getMethod(name) : nullptr;
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
    static TypeRegistry& getInstance() {
        static std::mutex initMutex;
        std::lock_guard<std::mutex> lock(initMutex);

        std::cerr << "DEBUG: Getting TypeRegistry instance - START" << std::endl;
        static TypeRegistry* instance = nullptr;
        static bool initializing = false;

        if (!instance) {
            if (initializing) {
                throw std::runtime_error("Recursive TypeRegistry initialization detected");
            }

            initializing = true;
            std::cerr << "DEBUG: First time initialization of TypeRegistry instance" << std::endl;

            instance = new TypeRegistry();
            // Initialize basic types in a specific order
            instance->getOrCreateBasicType("int");
            std::cerr << "DEBUG: Int type initialized" << std::endl;

            instance->getOrCreateBasicType("float");
            std::cerr << "DEBUG: Float type initialized" << std::endl;

            instance->getOrCreateBasicType("bool");
            std::cerr << "DEBUG: Bool type initialized" << std::endl;

            instance->getOrCreateBasicType("str");
            std::cerr << "DEBUG: String type initialized" << std::endl;

            instance->getOrCreateBasicType("pointer");
            std::cerr << "DEBUG: Pointer type initialized" << std::endl;

            initializing = false;
            std::cerr << "DEBUG: Basic types initialization complete" << std::endl;
        } else {
            std::cerr << "DEBUG: Returning existing TypeRegistry instance" << std::endl;
        }

        std::cerr << "DEBUG: Getting TypeRegistry instance - END" << std::endl;
        return *instance;
    }

    // Basic types
    TypeInfoPtr getIntType() {
        std::cerr << "DEBUG: Getting int type - START" << std::endl;
        auto result = getOrCreateBasicType("int");
        std::cerr << "DEBUG: Getting int type - END" << std::endl;
        return result;
    }

    TypeInfoPtr getFloatType() {
        std::cerr << "DEBUG: Getting float type - START" << std::endl;
        auto result = getOrCreateBasicType("float");
        std::cerr << "DEBUG: Getting float type - END" << std::endl;
        return result;
    }

    TypeInfoPtr getBoolType() {
        std::cerr << "DEBUG: Getting bool type - START" << std::endl;
        auto result = getOrCreateBasicType("bool");
        std::cerr << "DEBUG: Getting bool type - END" << std::endl;
        return result;
    }

    TypeInfoPtr getStrType() {
        std::cerr << "DEBUG: Getting str type - START" << std::endl;
        auto result = getOrCreateBasicType("str");
        std::cerr << "DEBUG: Getting str type - END" << std::endl;
        return result;
    }

    TypeInfoPtr getPointerType() {
        std::cerr << "DEBUG: Getting pointer type - START" << std::endl;
        auto result = getOrCreateBasicType("pointer");
        std::cerr << "DEBUG: Getting pointer type - END" << std::endl;
        return result;
    }

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
        std::cerr << "DEBUG: TypeRegistry constructor - START" << std::endl;
        std::cerr << "DEBUG: TypeRegistry constructor - END" << std::endl;
    }

    TypeInfoPtr getOrCreateBasicType(const std::string& name) {
        std::cerr << "DEBUG: getOrCreateBasicType called for: " << name << std::endl;
        auto it = types_.find(name);
        if (it != types_.end()) {
            std::cerr << "DEBUG: Returning existing basic type: " << name << std::endl;
            return it->second;
        }
        std::cerr << "DEBUG: Creating new basic type: " << name << std::endl;
        auto type = std::make_shared<BasicTypeInfo>(name);
        types_[name] = type;
        std::cerr << "DEBUG: Successfully created basic type: " << name << std::endl;
        return type;
    }

    std::unordered_map<std::string, TypeInfoPtr> types_;
};
