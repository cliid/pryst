#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace pryst {

// Forward declare TypeInfo class
class TypeInfo;

// Define TypeInfoPtr type alias
using TypeInfoPtr = std::shared_ptr<TypeInfo>;

class TypeInfo {
public:
    enum class Kind {
        Basic,
        Function,
        Class,
        Array,
        Pointer,
        Module
    };

    TypeInfo(Kind kind, const std::string& name) : kind(kind), name(name) {}
    virtual ~TypeInfo() = default;

    Kind getKind() const { return kind; }
    const std::string& getName() const { return name; }
    virtual std::string toString() const { return name; }
    virtual bool isConvertibleTo(const TypeInfoPtr& other) const = 0;

protected:
    Kind kind;
    std::string name;

    // Helper functions for type conversion
    static bool isNumericType(const TypeInfoPtr& type);
    static TypeInfoPtr getCommonNumericType(const TypeInfoPtr& t1, const TypeInfoPtr& t2);
};

// Basic types (int, float, bool, etc.)
class BasicTypeInfo : public TypeInfo {
public:
    BasicTypeInfo(const std::string& name) : TypeInfo(Kind::Basic, name) {}
    bool isConvertibleTo(const TypeInfoPtr& other) const override;
};

// Function types (for both named functions and lambdas)
class FunctionTypeInfo : public TypeInfo {
public:
    FunctionTypeInfo(const std::string& name, TypeInfoPtr returnType, std::vector<TypeInfoPtr> paramTypes)
        : TypeInfo(Kind::Function, name), returnType(returnType), paramTypes(paramTypes) {}

    TypeInfoPtr getReturnType() const { return returnType; }
    const std::vector<TypeInfoPtr>& getParamTypes() const { return paramTypes; }
    bool isConvertibleTo(const TypeInfoPtr& other) const override;

private:
    TypeInfoPtr returnType;
    std::vector<TypeInfoPtr> paramTypes;
};

// Class types with methods and fields
class ClassTypeInfo : public TypeInfo {
public:
    ClassTypeInfo(const std::string& name, std::shared_ptr<ClassTypeInfo> parent = nullptr)
        : TypeInfo(Kind::Class, name), parentClass(parent) {}

    void addMethod(const std::string& name, TypeInfoPtr methodType) {
        methods[name] = methodType;
    }

    void addField(const std::string& name, TypeInfoPtr fieldType) {
        fields[name] = fieldType;
    }

    const std::map<std::string, TypeInfoPtr>& getMethods() const { return methods; }
    const std::map<std::string, TypeInfoPtr>& getFields() const { return fields; }
    std::shared_ptr<ClassTypeInfo> getParent() const { return parentClass; }

    std::vector<std::pair<std::string, TypeInfoPtr>> getMembers() const {
        std::vector<std::pair<std::string, TypeInfoPtr>> result;
        for (const auto& [name, type] : fields) {
            result.push_back({name, type});
        }
        return result;
    }

    virtual TypeInfoPtr getMemberTypeInfo(const std::string& memberName) const {
        auto it = fields.find(memberName);
        if (it != fields.end()) {
            return it->second;
        }
        if (parentClass) {
            return parentClass->getMemberTypeInfo(memberName);
        }
        return nullptr;
    }

    bool isConvertibleTo(const TypeInfoPtr& other) const override {
        if (other->getKind() != Kind::Class) {
            return false;
        }
        auto otherClass = std::dynamic_pointer_cast<ClassTypeInfo>(other);
        if (!otherClass) {
            return false;
        }
        const ClassTypeInfo* current = this;
        while (current) {
            if (current->getName() == otherClass->getName()) {
                return true;
            }
            current = current->getParent().get();
        }
        return false;
    }

    std::string toString() const override {
        return "class " + name;
    }

private:
    std::map<std::string, TypeInfoPtr> methods;
    std::map<std::string, TypeInfoPtr> fields;
    std::shared_ptr<ClassTypeInfo> parentClass;
};

// Module types for handling module-level type information
class ModuleTypeInfo : public TypeInfo {
public:
    ModuleTypeInfo(const std::string& name) : TypeInfo(Kind::Module, name) {}

    void addType(const std::string& name, TypeInfoPtr type) {
        types[name] = type;
    }

    TypeInfoPtr getType(const std::string& name) const {
        auto it = types.find(name);
        return it != types.end() ? it->second : nullptr;
    }

    const std::map<std::string, TypeInfoPtr>& getTypes() const { return types; }

    bool isConvertibleTo(const TypeInfoPtr& other) const override {
        return other->getKind() == Kind::Module && getName() == other->getName();
    }

    std::string toString() const override {
        return "module " + name;
    }

private:
    std::map<std::string, TypeInfoPtr> types;
};

// Array types with size and element type information
class ArrayTypeInfo : public TypeInfo {
public:
    ArrayTypeInfo(const std::string& name, TypeInfoPtr elementType, size_t size)
        : TypeInfo(Kind::Array, name), elementType(elementType), size(size) {}

    TypeInfoPtr getElementType() const { return elementType; }
    size_t getSize() const { return size; }
    bool isConvertibleTo(const TypeInfoPtr& other) const override;

    std::string toString() const override {
        return elementType->toString() + "[" + std::to_string(size) + "]";
    }

private:
    TypeInfoPtr elementType;
    size_t size;
};

// Pointer types with pointee type information
class PointerTypeInfo : public TypeInfo {
public:
    PointerTypeInfo(const std::string& name, TypeInfoPtr pointeeType)
        : TypeInfo(Kind::Pointer, name), pointeeType(pointeeType) {}

    TypeInfoPtr getPointeeType() const { return pointeeType; }
    bool isConvertibleTo(const TypeInfoPtr& other) const override;

    std::string toString() const override {
        return pointeeType->toString() + "*";
    }

private:
    TypeInfoPtr pointeeType;
};

} // namespace pryst
