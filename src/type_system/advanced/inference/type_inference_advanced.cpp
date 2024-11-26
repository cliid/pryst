#include "type_inference_advanced.hpp"
#include "../types/advanced_types.hpp"
#include <algorithm>

using std::shared_ptr;
using std::vector;
using std::string;
using std::dynamic_pointer_cast;
using std::max;

namespace pryst {
namespace core {

TypeInference::TypeInference(shared_ptr<TypeRegistry> registry)
    : typeRegistry_(registry) {}

shared_ptr<Type> TypeInference::inferType(
    const vector<shared_ptr<Type>>& contextTypes,
    const vector<string>& operators) {

    if (contextTypes.empty()) {
        return nullptr;
    }

    // Start with the first type
    auto resultType = contextTypes[0];

    // Apply operators sequentially
    for (size_t i = 1; i < contextTypes.size() && i-1 < operators.size(); ++i) {
        resultType = inferFromBinaryOp(resultType, contextTypes[i], operators[i-1]);
    }

    return resultType;
}

shared_ptr<Type> TypeInference::inferFunctionReturnType(
    const vector<shared_ptr<Type>>& bodyExprTypes) {

    if (bodyExprTypes.empty()) {
        return typeRegistry_->getVoidType();
    }

    // Return type is the type of the last expression in the body
    return bodyExprTypes.back();
}

vector<shared_ptr<Type>> TypeInference::inferGenericParameters(
    const shared_ptr<Type>& genericType,
    const shared_ptr<Type>& concreteType) {

    vector<shared_ptr<Type>> params;

    // Handle parameterized types
    if (auto paramType = dynamic_pointer_cast<type_system::advanced::ParameterizedType>(concreteType)) {
        return paramType->getTypeArguments();
    }

    // Handle higher-kinded types
    if (auto higherKinded = dynamic_pointer_cast<type_system::advanced::HigherKindedType>(genericType)) {
        // Extract type parameters based on the higher-kinded type structure
        return params; // Placeholder for actual implementation
    }

    return params;
}

shared_ptr<Type> TypeInference::inferMethodCall(
    const shared_ptr<Type>& targetType,
    const string& methodName,
    const vector<shared_ptr<Type>>& argTypes) {

    // Handle intersection types
    if (auto intersection = dynamic_pointer_cast<type_system::advanced::IntersectionType>(targetType)) {
        for (const auto& component : intersection->getTypes()) {
            if (auto interface = dynamic_pointer_cast<InterfaceType>(component)) {
                // Check if method exists in interface
                if (interface->hasMethod(methodName)) {
                    return interface->getMethodReturnType(methodName, argTypes);
                }
            }
        }
    }

    // Handle union types
    if (auto union_ = dynamic_pointer_cast<type_system::advanced::UnionType>(targetType)) {
        vector<shared_ptr<Type>> resultTypes;
        for (const auto& type : union_->getTypes()) {
            auto result = inferMethodCall(type, methodName, argTypes);
            if (result) resultTypes.push_back(result);
        }
        return inferUnionType(resultTypes);
    }

    return nullptr;
}

shared_ptr<Type> TypeInference::inferUnionType(
    const vector<shared_ptr<Type>>& types) {

    if (types.empty()) {
        return nullptr;
    }

    // Remove duplicates and normalize types
    vector<shared_ptr<Type>> normalizedTypes;
    for (const auto& type : types) {
        bool shouldAdd = true;
        // If this is already a union type, flatten it
        if (auto unionType = dynamic_pointer_cast<type_system::advanced::UnionType>(type)) {
            for (const auto& innerType : unionType->getTypes()) {
                if (std::find_if(normalizedTypes.begin(), normalizedTypes.end(),
                    [&](const auto& t) { return t->equals(innerType); }) == normalizedTypes.end()) {
                    normalizedTypes.push_back(innerType);
                }
            }
            shouldAdd = false;
        }
        if (shouldAdd && std::find_if(normalizedTypes.begin(), normalizedTypes.end(),
            [&](const auto& t) { return t->equals(type); }) == normalizedTypes.end()) {
            normalizedTypes.push_back(type);
        }
    }

    // If we only have one type after normalization, return it directly
    if (normalizedTypes.size() == 1) {
        return normalizedTypes[0];
    }

    return std::make_shared<type_system::advanced::UnionType>(normalizedTypes);
}

shared_ptr<Type> TypeInference::inferParameterizedType(
    const string& baseType,
    const vector<shared_ptr<Type>>& typeArgs) {

    // Validate base type exists in registry
    if (!typeRegistry_->hasType(baseType)) {
        return nullptr;
    }

    vector<shared_ptr<Type>> resolvedArgs;
    for (const auto& arg : typeArgs) {
        // Handle nested parameterized types
        if (auto paramType = dynamic_pointer_cast<type_system::advanced::ParameterizedType>(arg)) {
            auto resolved = inferParameterizedType(paramType->getName(), paramType->getTypeArguments());
            if (resolved) resolvedArgs.push_back(resolved);
        }
        // Handle type parameters with constraints
        else if (auto typeParam = dynamic_pointer_cast<TypeParameter>(arg)) {
            if (typeParam->hasConstraint()) {
                auto constraint = typeParam->getConstraint();
                if (isCompatibleForIntersection(constraint, arg)) {
                    resolvedArgs.push_back(arg);
                }
            } else {
                resolvedArgs.push_back(arg);
            }
        }
        else {
            resolvedArgs.push_back(arg);
        }
    }

    return std::make_shared<type_system::advanced::ParameterizedType>(baseType, resolvedArgs);
}

} // namespace core
} // namespace pryst

    return std::make_shared<type_system::advanced::UnionType>(normalizedTypes);
}

shared_ptr<Type> TypeInference::inferIntersectionType(
    const vector<shared_ptr<Type>>& types) {

    if (types.empty()) {
        return nullptr;
    }

    // Remove duplicates and normalize types
    vector<shared_ptr<Type>> normalizedTypes;
    for (const auto& type : types) {
        bool shouldAdd = true;
        // If this is already an intersection type, flatten it
        if (auto intersectionType = dynamic_pointer_cast<type_system::advanced::IntersectionType>(type)) {
            for (const auto& innerType : intersectionType->getTypes()) {
                if (std::find_if(normalizedTypes.begin(), normalizedTypes.end(),
                    [&](const auto& t) { return t->equals(innerType); }) == normalizedTypes.end()) {
                    normalizedTypes.push_back(innerType);
                }
            }
            shouldAdd = false;
        }
        // Check for interface compatibility
        if (shouldAdd && std::find_if(normalizedTypes.begin(), normalizedTypes.end(),
            [&](const auto& t) { return isCompatibleForIntersection(t, type); }) == normalizedTypes.end()) {
            normalizedTypes.push_back(type);
        }
    }

    // If we only have one type after normalization, return it directly
    if (normalizedTypes.size() == 1) {
        return normalizedTypes[0];
    }

    return std::make_shared<type_system::advanced::IntersectionType>(normalizedTypes);
}

    return std::make_shared<type_system::advanced::UnionType>(normalizedTypes);
}
                vector<shared_ptr<Type>> resultParams;
                for (size_t i = 0; i < leftParam->getTypeArguments().size(); ++i) {
                    auto paramResult = inferBinaryOperation(
                        leftParam->getTypeArguments()[i],
                        rightParam->getTypeArguments()[i],
                        op
                    );
                    if (paramResult) resultParams.push_back(paramResult);
                }
                result = std::make_shared<type_system::advanced::ParameterizedType>(
                    leftParam->getName(),
                    resultParams
                );
            }
        }
    }

shared_ptr<Type> TypeInference::inferRecursiveType(
    const shared_ptr<Type>& baseType) {

    if (auto paramType = dynamic_pointer_cast<type_system::advanced::ParameterizedType>(baseType)) {
        auto typeArgs = paramType->getTypeArguments();
        // Handle self-referential type parameters
        for (auto& arg : typeArgs) {
            if (arg->equals(baseType)) {
                arg = paramType;
            }
        }
        return std::make_shared<type_system::advanced::ParameterizedType>(
            paramType->getName(),
            typeArgs
        );
    }
    return baseType;
}

shared_ptr<Type> TypeInference::inferFromBinaryOp(
    shared_ptr<Type> left,
    shared_ptr<Type> right,
    const string& op) {

    // Cache lookup
    string cacheKey = left->toString() + op + right->toString();
    if (typeCache_.find(cacheKey) != typeCache_.end()) {
        return typeCache_[cacheKey];
    }

    shared_ptr<Type> result;

    // Handle union types in binary operations
    if (auto leftUnion = dynamic_pointer_cast<type_system::advanced::UnionType>(left)) {
        vector<shared_ptr<Type>> resultTypes;
        for (const auto& leftType : leftUnion->getTypes()) {
            auto subResult = inferFromBinaryOp(leftType, right, op);
            if (subResult) resultTypes.push_back(subResult);
        }
        result = inferUnionType(resultTypes);
    }
    // Handle intersection types
    else if (auto leftIntersection = dynamic_pointer_cast<type_system::advanced::IntersectionType>(left)) {
        vector<shared_ptr<Type>> resultTypes;
        for (const auto& leftType : leftIntersection->getTypes()) {
            auto subResult = inferFromBinaryOp(leftType, right, op);
            if (subResult) resultTypes.push_back(subResult);
        }
        result = inferIntersectionType(resultTypes);
    }
    else {
        // Arithmetic operators
        if (op == "+" || op == "-" || op == "*" || op == "/") {
            if (left->isPrimitive() && right->isPrimitive()) {
                result = max(left, right, [](auto a, auto b) {
                    return a->getSize() < b->getSize();
                });
            }
        }
        // Comparison operators
        else if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") {
            result = typeRegistry_->getBoolType();
        }
        // Logical operators
        else if (op == "&&" || op == "||") {
            result = typeRegistry_->getBoolType();
        }
    }

    if (result) {
        typeCache_[cacheKey] = result;
    }

    return result;
}

bool TypeInference::isValidHigherKindedType(const shared_ptr<Type>& type) const {
    return dynamic_pointer_cast<type_system::advanced::HigherKindedType>(type) != nullptr;
}

bool TypeInference::isValidMonadicOperation(const string& operation) const {
    return operation == "bind" || operation == "return";
}

shared_ptr<Type> TypeInference::applyTypeConstructor(
    const shared_ptr<Type>& constructor,
    const shared_ptr<Type>& argument) {

    if (auto hkt = dynamic_pointer_cast<type_system::advanced::HigherKindedType>(constructor)) {
        return std::make_shared<type_system::advanced::ParameterizedType>(
            hkt->getName(),
            vector<shared_ptr<Type>>{argument}
        );
    }
    return nullptr;
}

} // namespace core
} // namespace pryst
