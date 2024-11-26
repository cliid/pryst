#pragma once

#include "../types/advanced_types.hpp"
#include "../../../include/type_registry.hpp"
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::vector;
using std::string;
using std::unordered_map;

namespace pryst {
namespace core {

class TypeInference {
public:
    explicit TypeInference(shared_ptr<TypeRegistry> registry);

    // Infer type from expression context
    shared_ptr<Type> inferType(
        const vector<shared_ptr<Type>>& contextTypes,
        const vector<string>& operators);

    // Infer return type from function body
    shared_ptr<Type> inferFunctionReturnType(
        const vector<shared_ptr<Type>>& bodyExprTypes);

    // Advanced type inference methods
    shared_ptr<Type> inferUnionType(const vector<shared_ptr<Type>>& types);
    shared_ptr<Type> inferIntersectionType(const vector<shared_ptr<Type>>& types);
    shared_ptr<Type> inferParameterizedType(
        const string& baseType,
        const vector<shared_ptr<Type>>& typeArgs);

    // Infer generic type parameters
    vector<shared_ptr<Type>> inferGenericParameters(
        const shared_ptr<Type>& genericType,
        const shared_ptr<Type>& concreteType);

    // Higher-kinded type inference methods
    shared_ptr<Type> inferHigherKindedType(
        const shared_ptr<Type>& higherKindedType,
        const shared_ptr<Type>& concreteType);

    shared_ptr<Type> inferMonadicOperation(
        const shared_ptr<Type>& monadType,
        const shared_ptr<Type>& valueType,
        const string& operation);

    shared_ptr<Type> inferRecursiveType(
        const shared_ptr<Type>& baseType);

    shared_ptr<Type> inferMethodCall(
        const shared_ptr<Type>& targetType,
        const string& methodName,
        const vector<shared_ptr<Type>>& argTypes);

    shared_ptr<Type> inferBinaryOperation(
        const shared_ptr<Type>& leftType,
        const shared_ptr<Type>& rightType,
        const string& op);

private:
    shared_ptr<TypeRegistry> typeRegistry_;
    unordered_map<string, shared_ptr<Type>> typeCache_;

    shared_ptr<Type> inferFromBinaryOp(
        shared_ptr<Type> left,
        shared_ptr<Type> right,
        const string& op);

    // Helper methods for advanced type inference
    bool isCompatibleForUnion(const shared_ptr<Type>& type1,
                             const shared_ptr<Type>& type2) const;
    bool isCompatibleForIntersection(const shared_ptr<Type>& type1,
                                   const shared_ptr<Type>& type2) const;

    // Additional helper methods for higher-kinded types
    bool isValidHigherKindedType(const shared_ptr<Type>& type) const;
    bool isValidMonadicOperation(const string& operation) const;
    shared_ptr<Type> applyTypeConstructor(
        const shared_ptr<Type>& constructor,
        const shared_ptr<Type>& argument);
};

} // namespace core
} // namespace pryst
