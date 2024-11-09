#pragma once

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <memory>
#include <string>
#include <vector>

namespace pryst {

class TypeInfo;
using TypeInfoPtr = std::shared_ptr<TypeInfo>;

// Base class for all type information
class TypeInfo {
public:
    virtual ~TypeInfo() = default;
    virtual llvm::Type* getLLVMType() const = 0;
    virtual std::string getName() const = 0;
    virtual bool isConvertibleTo(const TypeInfo* other) const = 0;
    virtual bool isBasicType() const { return false; }
    virtual bool isClassType() const { return false; }
    virtual bool isFunctionType() const { return false; }
};

// Basic types (int, float, bool, etc.)
class BasicTypeInfo : public TypeInfo {
public:
    BasicTypeInfo(llvm::Type* type, const std::string& name)
        : type(type), name(name) {}

    llvm::Type* getLLVMType() const override { return type; }
    std::string getName() const override { return name; }
    bool isConvertibleTo(const TypeInfo* other) const override;
    bool isBasicType() const override { return true; }

private:
    llvm::Type* type;
    std::string name;
};

// Class types
class ClassTypeInfo : public TypeInfo {
public:
    ClassTypeInfo(llvm::StructType* type, const std::string& name)
        : type(type), name(name) {}

    llvm::Type* getLLVMType() const override { return type; }
    std::string getName() const override { return name; }
    bool isConvertibleTo(const TypeInfo* other) const override;
    bool isClassType() const override { return true; }

    void addMethod(const std::string& name, TypeInfoPtr returnType,
                  const std::vector<TypeInfoPtr>& paramTypes);
    void addField(const std::string& name, TypeInfoPtr fieldType);

private:
    llvm::StructType* type;
    std::string name;
    std::unordered_map<std::string, std::pair<TypeInfoPtr, std::vector<TypeInfoPtr>>> methods;
    std::unordered_map<std::string, TypeInfoPtr> fields;
};

// Function types
class FunctionTypeInfo : public TypeInfo {
public:
    FunctionTypeInfo(llvm::FunctionType* type, TypeInfoPtr returnType,
                    const std::vector<TypeInfoPtr>& paramTypes)
        : type(type), returnType(returnType), paramTypes(paramTypes) {}

    llvm::Type* getLLVMType() const override { return type; }
    std::string getName() const override;
    bool isConvertibleTo(const TypeInfo* other) const override;
    bool isFunctionType() const override { return true; }

    TypeInfoPtr getReturnType() const { return returnType; }
    const std::vector<TypeInfoPtr>& getParamTypes() const { return paramTypes; }

private:
    llvm::FunctionType* type;
    TypeInfoPtr returnType;
    std::vector<TypeInfoPtr> paramTypes;
};

} // namespace pryst
