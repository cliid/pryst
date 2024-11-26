#pragma once

// LLVM headers (order matters)
#include <llvm/Support/Casting.h>
#include <llvm/ADT/Optional.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/SmallString.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

// Standard library headers
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <iostream>

// Project headers
#include "types.hpp"
#include "error.hpp"
#include "error_type.hpp"

// Forward declarations
namespace pryst {
namespace runtime {
class RuntimeRegistry;
} // namespace runtime
} // namespace pryst

namespace pryst {
namespace types {

// String conversion utilities
inline std::string toStdString(llvm::StringRef ref) { return ref.str(); }

class TypeRegistry {
public:
    explicit TypeRegistry(llvm::LLVMContext& context);
    TypeRegistry(llvm::LLVMContext& context, runtime::RuntimeRegistry* runtimeRegistry);
    ~TypeRegistry() = default;

    void registerClass(const std::string& className,
                      const std::vector<std::pair<std::string, llvm::Type*>>& members);
    void registerClass(const std::string& className,
                      const std::vector<std::pair<std::string, llvm::Type*>>& members,
                      const std::string& baseClass);

    // Validate error method override
    void validateErrorMethodOverride(const std::string& className,
                                   const std::string& methodName,
                                   const std::shared_ptr<FunctionType>& method,
                                   const std::string& baseClass);

    // Error type registration and management
    std::shared_ptr<ErrorType> registerErrorType(const std::string& message, const std::string& errorType = "TypeError") {
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
        inheritance[derived] = base;
    }

    // Check if a class is an error type
    bool isErrorType(const std::string& className) const {
        auto type = getCachedType(className);
        return type && type->getKind() == types::Type::Kind::Error;
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

        auto errorTypePtr = std::static_pointer_cast<types::ErrorType>(errorType);
        auto chainedTypePtr = std::static_pointer_cast<types::ErrorType>(chainedType);

        if (!errorTypePtr->isAssignableTo(chainedTypePtr)) {
            throw core::Error("TypeError",
                "Invalid error chain: " + errorClass + " is not assignable to " + chainedClass);
        }
    }

    std::shared_ptr<Type> createErrorChainType(const std::string& errorClass,
                                             const std::string& chainedClass) {
        validateErrorChain(errorClass, chainedClass);
        return std::make_shared<ErrorPropagationType>(getCachedType(chainedClass));
    }

    // Register a new interface type
    void registerInterfaceType(std::shared_ptr<types::InterfaceType> interfaceType);

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
    std::shared_ptr<Type> getMemberPrystType(const std::string& className, const std::string& memberName);

    // Get function type by name
    std::shared_ptr<Type> getFunctionType(const std::string& functionName) const;

    // Convert LLVM type to Pryst Type
    std::shared_ptr<Type> convertLLVMTypeToType(llvm::Type* llvmType);

    // Convert Pryst Type to LLVM type
    llvm::Type* convertTypeToLLVMType(std::shared_ptr<Type> type);

    // Get LLVM type for a Pryst type
    llvm::Type* getLLVMType(std::shared_ptr<types::Type> type);

    // Check if a type is nullable
    bool isTypeNullable(llvm::Type* type) const;

    // Register a type as nullable
    void registerNullableType(const std::string& typeName);

    // Register a union type
    void registerUnionType(std::shared_ptr<UnionType> unionType) {
        if (!unionType) return;
        std::string typeName = unionType->toString();
        cacheType(typeName, unionType);
    }

    // Register an intersection type
    void registerIntersectionType(std::shared_ptr<IntersectionType> intersectionType) {
        if (!intersectionType) return;
        std::string typeName = intersectionType->toString();
        cacheType(typeName, intersectionType);
    }

    // Register a map type with key and value types
    std::shared_ptr<Type> registerMapType(const std::string& keyType, const std::string& valueType);

    // Register a function type
    std::shared_ptr<Type> registerFunctionType(const std::string& returnType,
                                             const std::vector<std::string>& paramTypes);

    // Register an array type
    std::shared_ptr<Type> registerArrayType(const std::string& elementType);

    // Get all members of a class
    const std::vector<std::pair<std::string, llvm::Type*>>& getClassMembers(const std::string& className) const;

    // Get the LLVM context
    llvm::LLVMContext& getContext();
    llvm::Type* getBoolType() const;

    // Cache management for Pryst types
    std::shared_ptr<types::Type> getCachedType(const std::string& typeName) const;
    void cacheType(const std::string& typeName, std::shared_ptr<types::Type> type);

    // Namespace management
    void registerNamespace(const std::string& ns);
    void registerNamespaceAlias(const std::string& alias, const std::string& target);
    bool isNamespaceRegistered(const std::string& ns) const;
    std::string resolveNamespace(const std::string& ns) const;
    std::vector<std::string> getRegisteredNamespaces() const;

    // Get all registered types
    const std::unordered_map<std::string, std::shared_ptr<types::Type>>& getAllTypes() const;

    // Check if a type is numeric (int or float)
    bool isNumericType(std::shared_ptr<types::Type> type) const;

    // Check if two types can be compared with relational operators (<, >, <=, >=)
    bool isComparable(std::shared_ptr<Type> type1, std::shared_ptr<Type> type2) const {
        if (!type1 || !type2) return false;

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
    bool isEquatable(std::shared_ptr<Type> type1, std::shared_ptr<Type> type2) const {
        if (!type1 || !type2) return false;

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
            auto error1 = std::static_pointer_cast<ErrorType>(type1);
            auto error2 = std::static_pointer_cast<ErrorType>(type2);
            return error1->isAssignableTo(error2) ||
                   isSubclassOf(error1->getErrorType(), error2->getErrorType());
        }
        if (type1->getKind() == Type::Kind::Null || type2->getKind() == Type::Kind::Null) {
            return true;
        }
        // Check inheritance relationship for class types
        if (type1->getKind() == Type::Kind::Class && type2->getKind() == Type::Kind::Class) {
            return isSubclassOf(type1->toString(), type2->toString()) ||
                   isSubclassOf(type2->toString(), type1->toString());
        }
        return false;
    }

    // Check if one type can be assigned to another
    bool isAssignable(std::shared_ptr<Type> from, std::shared_ptr<Type> to) const {
        if (from->getKind() == Type::Kind::Error && to->getKind() == Type::Kind::Error) {
            auto fromError = std::static_pointer_cast<ErrorType>(from);
            auto toError = std::static_pointer_cast<ErrorType>(to);
            return fromError->isAssignableTo(*toError);
        }
        return from->isAssignableTo(to);
    }

    // Get common numeric type between two numeric types
    std::shared_ptr<Type> getCommonNumericType(std::shared_ptr<Type> type1, std::shared_ptr<Type> type2) const;

private:
    llvm::LLVMContext& context_;
    runtime::RuntimeRegistry* runtimeRegistry_;
    std::unordered_map<std::string, llvm::StructType*> classTypes_;
    std::unordered_map<std::string, std::vector<std::pair<std::string, llvm::Type*>>> classMembers_;
    std::unordered_map<std::string, std::vector<llvm::Type*>> constructorParams_;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> memberIndices_;
    std::unordered_map<std::string, std::string> inheritance;
    std::unordered_map<std::string, std::shared_ptr<Type>> typeCache_;
    std::unordered_set<std::string> nullableTypes_;
    std::unordered_set<std::string> registeredNamespaces_;
    std::unordered_map<std::string, std::string> namespaceAliases_;
    std::unordered_map<std::string, llvm::Type*> llvmTypeMap_;
};

} // namespace types
