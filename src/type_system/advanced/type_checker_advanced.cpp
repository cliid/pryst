#include "type_checker.hpp"
#include "type.hpp"
#include <stdexcept>
#include <iostream>

namespace pryst {

std::shared_ptr<Type> TypeChecker::checkBinaryExpression(
    std::shared_ptr<Type> left,
    const std::string& op,
    std::shared_ptr<Type> right) {

    std::cout << "Debug [TypeChecker::checkBinaryExpression]: Checking " << left->toString()
              << " " << op << " " << right->toString() << std::endl;

    // Handle error propagation
    if (left->isError()) return left;
    if (right->isError()) return right;

    // Handle array access
    if (left->isArray() && op == "[]") {
        return checkArrayAccess(left, right);
    }

    // Handle string operations
    if (left->toString() == "String" || right->toString() == "String") {
        if (op == "+") {
            return typeRegistry_->getType("String");
        }
        return std::make_shared<pryst::ErrorType>("TypeError");
    }

    // Handle Boolean operations
    if (left->toString() == "Boolean" || right->toString() == "Boolean") {
        if (op == "&&" || op == "||") {
            return typeRegistry_->getType("Boolean");
        }
        return std::make_shared<pryst::ErrorType>("TypeError");
    }

    // Handle nullable types
    bool isNullable = left->isNullable() || right->isNullable();
    auto leftType = left->isNullable() ?
        std::dynamic_pointer_cast<NullableType>(left)->getBaseType() :
        left->toString();
    auto rightType = right->isNullable() ?
        std::dynamic_pointer_cast<NullableType>(right)->getBaseType() :
        right->toString();

    // Handle array assignment
    if (op == "=" && left->isArray() && right->isArray()) {
        return checkArrayAssignment(left, right);
    }

    // Handle arithmetic operators
    if (op == "+" || op == "-" || op == "*" || op == "/") {
        if (!left->isPrimitive() && !left->isNullable() ||
            !right->isPrimitive() && !right->isNullable()) {
            std::cout << "Debug [TypeChecker::checkBinaryExpression]: Type error in arithmetic" << std::endl;
            return std::make_shared<pryst::ErrorType>("TypeError");
        }
        // Type promotion hierarchy: Int -> Float -> Double
        std::string resultType = "Int";
        if (leftType == "Double" || rightType == "Double") {
            resultType = "Double";
        } else if (leftType == "Float" || rightType == "Float") {
            resultType = "Float";
        }
        return isNullable ?
            std::make_shared<NullableType>(resultType) :
            typeRegistry_->getType(resultType);
    }

    // Handle comparison operators
    if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") {
        // Allow comparisons between nullable and non-nullable of same base type
        auto leftBaseType = left->isNullable() ?
            std::dynamic_pointer_cast<NullableType>(left)->getBaseType() :
            left->toString();
        auto rightBaseType = right->isNullable() ?
            std::dynamic_pointer_cast<NullableType>(right)->getBaseType() :
            right->toString();

        if (leftBaseType != rightBaseType) {
            std::cout << "Debug [TypeChecker::checkBinaryExpression]: Type error in comparison" << std::endl;
            return std::make_shared<pryst::ErrorType>("TypeError");
        }
        return typeRegistry_->getType("Boolean");
    }

    std::cout << "Debug [TypeChecker::checkBinaryExpression]: Unsupported operation" << std::endl;
    return std::make_shared<pryst::ErrorType>("UnsupportedOperationError");
}

std::shared_ptr<Type> TypeChecker::checkUnaryExpression(
    const std::string& op,
    std::shared_ptr<Type> operand) {

    std::cout << "Debug [TypeChecker::checkUnaryExpression]: Checking " << op
              << " " << operand->toString() << std::endl;

    // Handle error propagation
    if (operand->isError()) return operand;

    // Handle negation
    if (op == "-" || op == "+") {
        if (!operand->isPrimitive()) {
            std::cout << "Debug [TypeChecker::checkUnaryExpression]: Type error in negation" << std::endl;
            return std::make_shared<pryst::ErrorType>("TypeError");
        }
        return operand;
    }

    // Handle logical not
    if (op == "!") {
        if (!operand->isPrimitive()) {
            std::cout << "Debug [TypeChecker::checkUnaryExpression]: Type error in logical not" << std::endl;
            return std::make_shared<pryst::ErrorType>("TypeError");
        }
        return typeRegistry_->getType("Boolean");
    }

    std::cout << "Debug [TypeChecker::checkUnaryExpression]: Unsupported operation" << std::endl;
    return std::make_shared<pryst::ErrorType>("UnsupportedOperationError");
}

std::shared_ptr<Type> TypeChecker::checkNestedErrorHandling(
    const std::vector<std::shared_ptr<Type>>& tryErrors,
    const std::vector<std::shared_ptr<Type>>& catchErrors) {

    std::cout << "Debug [TypeChecker::checkNestedErrorHandling]: Checking nested error handling" << std::endl;

    for (const auto& error : tryErrors) {
        if (!error->isError()) {
            return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
        }
    }

    for (const auto& error : catchErrors) {
        if (!error->isError()) {
            return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
        }
    }

    return typeRegistry_->getType("Boolean");
}

std::shared_ptr<Type> TypeChecker::checkErrorPropagation(
    std::shared_ptr<Type> sourceError,
    const std::vector<std::shared_ptr<Type>>& propagationPath) {

    std::cout << "Debug [TypeChecker::checkErrorPropagation]: Checking error propagation" << std::endl;

    if (!sourceError->isError()) {
        return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
    }

    for (const auto& error : propagationPath) {
        if (!error->isError()) {
            return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
        }
    }

    return sourceError;
}

std::shared_ptr<Type> TypeChecker::checkErrorInScope(std::shared_ptr<Type> error) {
    std::cout << "Debug [TypeChecker::checkErrorInScope]: Checking error in scope" << std::endl;

    // For error types, we validate that they are properly registered
    if (error->isError()) {
        // Check if this error type is registered in our type registry
        auto registeredType = typeRegistry_->getType(error->toString());
        if (registeredType && registeredType->isError()) {
            return registeredType;  // Return the registered error type
        }
    }

    return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
}

std::shared_ptr<Type> TypeChecker::transformError(
    std::shared_ptr<Type> sourceError,
    std::shared_ptr<Type> targetError) {

    std::cout << "Debug [TypeChecker::transformError]: Transforming error" << std::endl;

    if (!sourceError->isError() || !targetError->isError()) {
        return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
    }

    return targetError;
}

std::shared_ptr<Type> TypeChecker::validateErrorChain(
    const std::vector<std::shared_ptr<Type>>& errorChain) {

    std::cout << "Debug [TypeChecker::validateErrorChain]: Validating error chain" << std::endl;

    if (errorChain.empty()) {
        return std::make_shared<pryst::ErrorType>(std::string("EmptyChainError"));
    }

    for (size_t i = 0; i < errorChain.size(); ++i) {
        if (!errorChain[i]->isError()) {
            return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
        }
        for (size_t j = i + 1; j < errorChain.size(); ++j) {
            if (errorChain[i]->toString() == errorChain[j]->toString()) {
                return std::make_shared<pryst::ErrorType>(std::string("DuplicateErrorType"));
            }
        }
    }

    return typeRegistry_->getType("Boolean");
}

std::shared_ptr<Type> TypeChecker::inferExpressionType(
    const std::vector<std::shared_ptr<Type>>& types,
    const std::vector<std::string>& operators) {

    std::cout << "Debug [TypeChecker::inferExpressionType]: Inferring expression type" << std::endl;

    if (types.empty()) {
        return std::make_shared<pryst::ErrorType>(std::string("EmptyExpressionError"));
    }

    auto resultType = types[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        resultType = checkBinaryExpression(resultType, operators[i], types[i + 1]);
    }
    return resultType;
}

std::shared_ptr<Type> TypeChecker::inferGenericType(
    std::shared_ptr<Type> genericType,
    std::shared_ptr<Type> parameterType) {

    std::cout << "Debug [TypeChecker::inferGenericType]: Inferring generic type" << std::endl;

    if (!genericType->isClass()) {
        return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
    }

    std::string fullName = genericType->toString();
    std::string baseName = fullName.substr(0, fullName.find('<'));
    if (baseName.empty()) {
        baseName = fullName;  // If no '<' found, use the full name
    }
    return std::make_shared<GenericType>(baseName + "<" + parameterType->toString() + ">");
}

std::shared_ptr<Type> TypeChecker::inferLambdaReturnType(
    const std::vector<std::shared_ptr<Type>>& paramTypes,
    const std::vector<std::string>& bodyOperators) {

    std::cout << "Debug [TypeChecker::inferLambdaReturnType]: Inferring lambda return type" << std::endl;

    return inferExpressionType(paramTypes, bodyOperators);
}

std::shared_ptr<Type> TypeChecker::checkNullCoalescing(
    std::shared_ptr<Type> nullableType,
    std::shared_ptr<Type> defaultType) {

    std::cout << "Debug [TypeChecker::checkNullCoalescing]: Checking null coalescing" << std::endl;

    if (!nullableType->isNullable()) {
        return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
    }

    auto nullableBaseType = std::dynamic_pointer_cast<pryst::NullableType>(nullableType);
    if (nullableBaseType->getBaseType() != defaultType->toString()) {
        return std::make_shared<pryst::ErrorType>(std::string("TypeError"));
    }

    return defaultType;
}

std::shared_ptr<Type> TypeChecker::checkComplexExpression(
    const std::vector<std::shared_ptr<Type>>& types,
    const std::vector<std::string>& operators) {

    std::cout << "Debug [TypeChecker::checkComplexExpression]: Checking complex expression" << std::endl;

    return inferExpressionType(types, operators);
}

std::shared_ptr<Type> TypeChecker::checkArrayAccess(
    std::shared_ptr<Type> arrayType,
    std::shared_ptr<Type> indexType) {

    std::cout << "Debug [TypeChecker::checkArrayAccess]: Checking array access" << std::endl;

    if (!arrayType->isArray()) {
        return std::make_shared<ErrorType>("TypeError: Not an array type");
    }

    if (indexType->toString() != "Int") {
        return std::make_shared<ErrorType>("TypeError: Array index must be an integer");
    }

    return std::static_pointer_cast<ArrayType>(arrayType)->getElementType();
}

std::shared_ptr<Type> TypeChecker::checkArrayCreation(
    std::shared_ptr<Type> elementType) {

    std::cout << "Debug [TypeChecker::checkArrayCreation]: Creating array type" << std::endl;

    if (elementType->isError()) {
        return elementType;
    }
    return std::make_shared<ArrayType>(elementType);
}

std::shared_ptr<Type> TypeChecker::checkArrayAssignment(
    std::shared_ptr<Type> targetArray,
    std::shared_ptr<Type> sourceArray) {

    std::cout << "Debug [TypeChecker::checkArrayAssignment]: Checking array assignment" << std::endl;

    if (!targetArray->isArray() || !sourceArray->isArray()) {
        return std::make_shared<ErrorType>("TypeError: Both types must be arrays");
    }

    auto targetElemType = std::static_pointer_cast<ArrayType>(targetArray)->getElementType();
    auto sourceElemType = std::static_pointer_cast<ArrayType>(sourceArray)->getElementType();

    if (!areTypesCompatible(targetElemType, sourceElemType)) {
        return std::make_shared<ErrorType>("TypeError: Incompatible array types");
    }

    return targetArray;
}

} // namespace pryst
