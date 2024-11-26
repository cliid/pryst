#pragma once

// Standard library headers
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <iostream>

// LLVM headers
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"

// Project headers - Core types
#include "core/types.hpp"
#include "core/error.hpp"
#include "core/error_type.hpp"

// Project headers - Runtime
#include "runtime/core/runtime_registry.hpp"

namespace pryst {
namespace core {

class TypeRegistry {
public:
    // Basic constructor for temporary initialization
    explicit TypeRegistry(llvm::LLVMContext& context);
    // Full constructor with RuntimeRegistry
    TypeRegistry(llvm::LLVMContext& context, runtime::RuntimeRegistry& runtimeRegistry);
    ~TypeRegistry() = default;

    // Register a new class type with its members
    void registerClass(const std::string& className,
                      const std::vector<std::pair<std::string, llvm::Type*>>& members);
    void registerClass(const std::string& className,
                      const std::vector<std::pair<std::string, llvm::Type*>>& members,
                      const std::string& baseClass);

    // Validate error method override
    void validateErrorMethodOverride(const std::string& className,
                                   const std::string& methodName,
                                   const std::shared_ptr<core::FunctionType>& method,
                                   const std::string& baseClass);

    // Error type registration and management
    std::shared_ptr<core::ErrorType> registerErrorType(const std::string& message, const std::string& errorType = "TypeError") {
        auto type = makeErrorType(message, errorType);
        cacheType(errorType, type);
        return type;
    }

    void registerErrorHierarchy(const std::string& derived, const std::string& base) {
        auto derivedType = getCachedType(derived);
        auto baseType = getCachedType(base);

        if (!derivedType || !baseType ||
            !derivedType->isError() || !baseType->isError()) {
            throw core::Error("TypeError", "Both types must be error types");
        }
        inheritance_[derived] = base;
    }

    // Check if a class is an error type
    bool isErrorType(const std::string& className) const {
        auto type = getCachedType(className);
        return type && type->getKind() == Type::Kind::Error;
    }

    // Error chain validation and creation
    void validateErrorChain(const std::string& errorClass,
                          const std::string& chainedClass) {
        auto errorType = getCachedType(errorClass);
        auto chainedType = getCachedType(chainedClass);

        if (!errorType || !chainedType ||
            !errorType->isError() || !chainedType->isError()) {
            throw core::Error("TypeError", "Both types in error chain must be error types");
        }

        auto errorTypePtr = std::static_pointer_cast<core::ErrorType>(errorType);
        auto chainedTypePtr = std::static_pointer_cast<core::ErrorType>(chainedType);

        if (!errorTypePtr->isAssignableTo(chainedTypePtr)) {
            throw core::Error("TypeError",
                "Invalid error chain: " + errorClass + " is not assignable to " + chainedClass);
        }
    }

    std::shared_ptr<core::Type> createErrorChainType(const std::string& errorClass,
                                           const std::string& chainedClass) {
        validateErrorChain(errorClass, chainedClass);
        return std::make_shared<core::ErrorPropagationType>(getCachedType(chainedClass));
    }

    // Register a new interface type
    void registerInterfaceType(std::shared_ptr<core::InterfaceType> interfaceType);

    // Register interface implementation
    void registerInterfaceImplementation(const std::string& className, const std::string& interfaceName);

    // Check if a class implements an interface
    bool implementsInterface(const std::string& className, const std::string& interfaceName) const;

    // Register inheritance relationship
    void registerInheritance(const std::string& derived, const std::string& base);

    // Check if derived class inherits from base class
    bool isSubclassOf(const std::string& derived, const std::string& base) const;

    // Get the LLVM type for a class
    llvm::StructType* getClassType(const std::string& className);

    // Get the index of a member within a class
    int getMemberIndex(const std::string& className, const std::string& memberName);

    // Register a member index for a class
    void registerMemberIndex(const std::string& className, const std::string& memberName, int index);

    // Register a constructor for a class
    void registerConstructor(const std::string& className, const std::vector<llvm::Type*>& paramTypes);

    // Check if a class has a constructor
    bool hasConstructor(const std::string& className) const;

    // Get constructor parameter types
    const std::vector<llvm::Type*>& getConstructorParams(const std::string& className);

    // Check if a class exists
    bool hasClass(const std::string& className) const;

    // Get member type by index
    llvm::Type* getMemberType(const std::string& className, int index);

    // Get member type by name
    std::shared_ptr<core::Type> getMemberPrystType(const std::string& className, const std::string& memberName);

    // Get function type by name
    std::shared_ptr<core::Type> getFunctionType(const std::string& functionName) const;

    // Convert LLVM type to Pryst Type
    std::shared_ptr<core::Type> convertLLVMTypeToType(llvm::Type* llvmType);

    // Convert Pryst Type to LLVM type
    llvm::Type* convertTypeToLLVMType(std::shared_ptr<core::Type> type);

    // Get LLVM type for a Pryst type
    llvm::Type* getLLVMType(std::shared_ptr<core::Type> type);

    // Check if a type is nullable
    bool isTypeNullable(llvm::Type* type) const;

    // Register a type as nullable
    void registerNullableType(const std::string& typeName);

    // Register a union type
    void registerUnionType(std::shared_ptr<core::UnionType> unionType) {
        std::string typeName = unionType->toString();
        cacheType(typeName, unionType);
    }

    // Register an intersection type
    void registerIntersectionType(std::shared_ptr<core::IntersectionType> intersectionType) {
        std::string typeName = intersectionType->toString();
        cacheType(typeName, intersectionType);
    }

    // Register a map type with key and value types
    std::shared_ptr<core::Type> registerMapType(const std::string& keyType, const std::string& valueType);

    // Register a function type
    std::shared_ptr<core::Type> registerFunctionType(const std::string& returnType,
                                                   const std::vector<std::string>& paramTypes);

    // Register an array type
    std::shared_ptr<core::Type> registerArrayType(const std::string& elementType);

    // Get all members of a class
    const std::vector<std::pair<std::string, llvm::Type*>>& getClassMembers(const std::string& className) const;

    // Get the LLVM context
    llvm::LLVMContext& getContext();
    llvm::Type* getBoolType() const;

    // Cache management for Pryst types
    std::shared_ptr<core::Type> getCachedType(const std::string& typeName) const;
    void cacheType(const std::string& typeName, std::shared_ptr<core::Type> type);

    // Namespace management
    void registerNamespace(const std::string& ns);
    void registerNamespaceAlias(const std::string& alias, const std::string& target);
    bool isNamespaceRegistered(const std::string& ns) const;
    std::string resolveNamespace(const std::string& ns) const;
    std::vector<std::string> getRegisteredNamespaces() const;

    // Get all registered types
    const std::unordered_map<std::string, std::shared_ptr<core::Type>>& getAllTypes() const;

    // Check if a type is numeric (int or float)
    bool isNumericType(std::shared_ptr<core::Type> type) const;

    // Check if two types can be compared with relational operators (<, >, <=, >=)
    bool isComparable(std::shared_ptr<core::Type> type1, std::shared_ptr<core::Type> type2) const {
        // Numeric types are comparable with each other
        if (isNumericType(type1) && isNumericType(type2)) {
            return true;
        }
        // Same types are comparable if they're strings
        if (type1->toString() == "string" && type2->toString() == "string") {
            return true;
        }
        return false;
    }

    // Check if two types can be compared for equality (==, !=)
    bool isEquatable(std::shared_ptr<core::Type> type1, std::shared_ptr<core::Type> type2) const {
        // All numeric types are equatable with each other
        if (isNumericType(type1) && isNumericType(type2)) {
            return true;
        }
        // Same types are always equatable
        if (type1->toString() == type2->toString()) {
            return true;
        }
        // Error types are only equatable with other error types
        if (type1->isError() && type2->isError()) {
            auto error1 = std::static_pointer_cast<core::ErrorType>(type1);
            auto error2 = std::static_pointer_cast<core::ErrorType>(type2);
            return error1->isAssignableTo(error2) ||
                   isSubclassOf(error1->getErrorType(), error2->getErrorType());
        }
        if (type1->getKind() == core::Type::Kind::Null || type2->getKind() == core::Type::Kind::Null) {
            return true;
        }
        // Check inheritance relationship for class types
        if (type1->getKind() == core::Type::Kind::Class && type2->getKind() == core::Type::Kind::Class) {
            return isSubclassOf(type1->toString(), type2->toString()) ||
                   isSubclassOf(type2->toString(), type1->toString());
        }
        return false;
    }

    // Check if two types can be combined in a union type
    bool areTypesUnionable(std::shared_ptr<core::Type> type1, std::shared_ptr<core::Type> type2) const {
        // Allow union of same types
        if (type1->toString() == type2->toString()) {
            return true;
        }

        // Allow union of numeric types
        if (isNumericType(type1) && isNumericType(type2)) {
            return true;
        }

        // Allow union with null type
        if (type1->getKind() == core::Type::Kind::Null || type2->getKind() == core::Type::Kind::Null) {
            return true;
        }

        // Allow union of related class types through inheritance
        if (type1->getKind() == core::Type::Kind::Class && type2->getKind() == core::Type::Kind::Class) {
            return isSubclassOf(type1->toString(), type2->toString()) ||
                   isSubclassOf(type2->toString(), type1->toString());
        }

        // Allow union of error types if they share a common error hierarchy
        if (type1->isError() && type2->isError()) {
            auto error1 = std::static_pointer_cast<core::ErrorType>(type1);
            auto error2 = std::static_pointer_cast<core::ErrorType>(type2);
            return error1->isAssignableTo(error2) || error2->isAssignableTo(error1);
        }

        return false;
    }

    // Check if two types can be combined in an intersection type
    bool areTypesIntersectable(std::shared_ptr<core::Type> type1, std::shared_ptr<core::Type> type2) const {
        // Allow intersection of same types
        if (type1->toString() == type2->toString()) {
            return true;
        }

        // Allow intersection of numeric types
        if (isNumericType(type1) && isNumericType(type2)) {
            return true;
        }

        // Don't allow intersection with null type
        if (type1->getKind() == core::Type::Kind::Null || type2->getKind() == core::Type::Kind::Null) {
            return false;
        }

        // Allow intersection of related class types through inheritance
        if (type1->getKind() == core::Type::Kind::Class && type2->getKind() == core::Type::Kind::Class) {
            return isSubclassOf(type1->toString(), type2->toString()) ||
                   isSubclassOf(type2->toString(), type1->toString());
        }

        // Allow intersection of error types if they share a common error hierarchy
        if (type1->isError() && type2->isError()) {
            auto error1 = std::static_pointer_cast<core::ErrorType>(type1);
            auto error2 = std::static_pointer_cast<core::ErrorType>(type2);
            return error1->isAssignableTo(error2) || error2->isAssignableTo(error1);
        }

        return false;
    }

    // Check if one type can be assigned to another
    bool isAssignable(std::shared_ptr<core::Type> from, std::shared_ptr<core::Type> to) const {
        if (from->getKind() == core::Type::Kind::Error && to->getKind() == core::Type::Kind::Error) {
            auto fromError = std::static_pointer_cast<core::ErrorType>(from);
            auto toError = std::static_pointer_cast<core::ErrorType>(to);
            return fromError->isAssignableTo(*toError);
        }
        return from->isAssignableTo(to);
    }

    // Get common numeric type between two numeric types
    std::shared_ptr<core::Type> getCommonNumericType(std::shared_ptr<core::Type> type1, std::shared_ptr<core::Type> type2) const;

private:
    llvm::LLVMContext& context_;
    runtime::RuntimeRegistry& runtime_registry_;  // Reference to RuntimeRegistry
    // Map of class names to their LLVM struct types
    std::unordered_map<std::string, llvm::StructType*> class_types_;

    // Map of class names to their member information (LLVM types)
    std::unordered_map<std::string, std::vector<std::pair<std::string, llvm::Type*>>> class_member_info_;

    // Map of class names to their member information (Pryst types)
    std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<core::Type>>> converted_member_types_;

    // Map of class names to their constructor parameter types
    std::unordered_map<std::string, std::vector<llvm::Type*>> constructor_params_;

    // Map of class names to their base class
    std::unordered_map<std::string, std::string> inheritance_;

    // Map of class names to their implemented interfaces
    std::unordered_map<std::string, std::unordered_set<std::string>> interface_implementations_;

    // Cache for converted Pryst types
    std::unordered_map<std::string, std::shared_ptr<core::Type>> type_cache_;

    // Map of primitive type names to their methods
    std::unordered_map<std::string, std::unordered_map<std::string, llvm::FunctionType*>> primitive_methods_;

    // Set of registered namespaces
    std::unordered_set<std::string> registered_namespaces_;

    // Map of namespace aliases to their targets
    std::unordered_map<std::string, std::string> namespace_aliases_;

    // Initialize primitive type methods
    void registerPrimitiveMethods();

    // Get methods for a primitive type
    const std::unordered_map<std::string, llvm::FunctionType*>& getPrimitiveMethods(const std::string& typeName) const;

    // Set of types that can be null
    std::unordered_set<std::string> nullableTypes_;
};

} // namespace pryst
