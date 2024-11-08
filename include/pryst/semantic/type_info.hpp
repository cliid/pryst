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

protected:
    Kind kind;
    std::string name;
};

// Basic types (int, float, bool, etc.)
class BasicTypeInfo : public TypeInfo {
public:
    BasicTypeInfo(const std::string& name) : TypeInfo(Kind::Basic, name) {}
};

// Function types (for both named functions and lambdas)
class FunctionTypeInfo : public TypeInfo {
public:
    FunctionTypeInfo(const std::string& name, TypeInfoPtr returnType, std::vector<TypeInfoPtr> paramTypes)
        : TypeInfo(Kind::Function, name), returnType(returnType), paramTypes(paramTypes) {}

    TypeInfoPtr getReturnType() const { return returnType; }
    const std::vector<TypeInfoPtr>& getParamTypes() const { return paramTypes; }

private:
    TypeInfoPtr returnType;
    std::vector<TypeInfoPtr> paramTypes;
};

// Class types with methods and fields
class ClassTypeInfo : public TypeInfo {
public:
    ClassTypeInfo(const std::string& name) : TypeInfo(Kind::Class, name) {}
    
    void addMethod(const std::string& name, TypeInfoPtr methodType) {
        methods[name] = methodType;
    }
    
    void addField(const std::string& name, TypeInfoPtr fieldType) {
        fields[name] = fieldType;
    }

    const std::map<std::string, TypeInfoPtr>& getMethods() const { return methods; }
    const std::map<std::string, TypeInfoPtr>& getFields() const { return fields; }

private:
    std::map<std::string, TypeInfoPtr> methods;
    std::map<std::string, TypeInfoPtr> fields;
};

} // namespace pryst
