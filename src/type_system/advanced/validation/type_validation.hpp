#pragma once

#include "../types.hpp"
#include "../type_registry.hpp"
#include <memory>
#include <vector>
#include <string>

using std::shared_ptr;
using std::vector;
using std::string;

namespace pryst {
namespace core {

class TypeValidation {
public:
    explicit TypeValidation(std::shared_ptr<TypeRegistry> registry);

    // Validate type compatibility
    bool validateCompatibility(
        std::shared_ptr<Type> source,
        std::shared_ptr<Type> target,
        bool allowImplicitConversion = false);

    // Validate function call arguments
    bool validateFunctionCall(
        const std::shared_ptr<FunctionType>& funcType,
        const std::vector<std::shared_ptr<Type>>& argTypes);

    // Validate generic type constraints
    bool validateGenericConstraints(
        const std::shared_ptr<GenericType>& genericType,
        const std::vector<std::shared_ptr<Type>>& typeArgs);

    // Advanced type validation methods
    bool validateUnionType(const shared_ptr<Type>& unionType);
    bool validateIntersectionType(const shared_ptr<Type>& intersectionType);
    bool validateParameterizedType(const shared_ptr<Type>& paramType);
    bool validateTypeParameter(const shared_ptr<Type>& typeParam);

    // Higher-kinded type validation
    bool validateHigherKindedType(
        const shared_ptr<Type>& higherKindedType,
        const shared_ptr<Type>& appliedType);

    // Recursive type validation
    bool validateRecursiveType(const shared_ptr<Type>& recursiveType);

private:
    shared_ptr<TypeRegistry> typeRegistry_;

    bool isImplicitlyConvertible(
        shared_ptr<Type> source,
        shared_ptr<Type> target);

    // Helper methods for advanced validation
    bool validateTypeConstraints(
        const shared_ptr<Type>& type,
        const shared_ptr<Type>& constraint);

    bool validateMethodCompatibility(
        const shared_ptr<Type>& type1,
        const shared_ptr<Type>& type2);
};

} // namespace core
} // namespace pryst
