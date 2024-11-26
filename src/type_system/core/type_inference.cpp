#include "type_inference.hpp"
#include <sstream>

namespace pryst {

std::shared_ptr<Type> TypeInference::inferType(
    const std::string& expr,
    const std::unordered_map<std::string, std::shared_ptr<Type>>& context
) {
    // Look up variable in context
    auto it = context.find(expr);
    if (it != context.end()) {
        return it->second;
    }

    // Handle error case
    std::stringstream ss;
    ss << "Cannot infer type for expression: " << expr;
    errorHandler_.handleError(Error("TypeError", ss.str()));
    return std::make_shared<ErrorType>("UnknownType");
}

std::shared_ptr<Type> TypeInference::makeNullable(std::shared_ptr<Type> type) {
    if (type->isNullable()) {
        return type;
    }
    return std::make_shared<NullableType>(type->toString());
}

bool TypeInference::isNullableCompatible(std::shared_ptr<Type> from, std::shared_ptr<Type> to) {
    if (!to->isNullable() && from->isNullable()) {
        errorHandler_.handleError(Error("NullSafetyError",
            "Cannot assign nullable type to non-nullable type"));
        return false;
    }
    return true;
}

std::shared_ptr<Type> TypeInference::inferFunctionType(
    const std::vector<std::shared_ptr<Type>>& paramTypes,
    std::shared_ptr<Type> returnType
) {
    // Validate parameter types
    for (const auto& paramType : paramTypes) {
        if (paramType->isError()) {
            return std::make_shared<ErrorType>("InvalidFunctionType");
        }
    }

    // Validate return type
    if (returnType->isError()) {
        return std::make_shared<ErrorType>("InvalidFunctionType");
    }

    return std::make_shared<FunctionType>(paramTypes, returnType);
}

bool TypeInference::isCompatible(std::shared_ptr<Type> from, std::shared_ptr<Type> to) {
    // Handle null safety
    if (!isNullableCompatible(from, to)) {
        return false;
    }

    // Handle primitive types
    if (from->isPrimitive() && to->isPrimitive()) {
        return isImplicitlyConvertible(from, to);
    }

    // Handle function types
    if (from->isFunction() && to->isFunction()) {
        auto fromFunc = std::static_pointer_cast<FunctionType>(from);
        auto toFunc = std::static_pointer_cast<FunctionType>(to);

        // Check parameter count
        if (fromFunc->getParameterTypes().size() != toFunc->getParameterTypes().size()) {
            errorHandler_.handleError(Error("TypeError", "Function parameter count mismatch"));
            return false;
        }

        // Check parameter types
        for (size_t i = 0; i < fromFunc->getParameterTypes().size(); ++i) {
            if (!isCompatible(fromFunc->getParameterTypes()[i], toFunc->getParameterTypes()[i])) {
                return false;
            }
        }

        // Check return type
        return isCompatible(fromFunc->getReturnType(), toFunc->getReturnType());
    }

    // Handle array types
    if (from->isArray() && to->isArray()) {
        auto fromArray = std::static_pointer_cast<ArrayType>(from);
        auto toArray = std::static_pointer_cast<ArrayType>(to);
        return isCompatible(fromArray->getElementType(), toArray->getElementType());
    }

    return from->toString() == to->toString();
}

bool TypeInference::isImplicitlyConvertible(std::shared_ptr<Type> from, std::shared_ptr<Type> to) {
    // Implement basic type conversion rules
    // For now, only allow identical types
    return from->toString() == to->toString();
}

std::shared_ptr<Type> TypeInference::findCommonType(std::shared_ptr<Type> t1, std::shared_ptr<Type> t2) {
    if (t1->toString() == t2->toString()) {
        return t1;
    }

    // If one is nullable and the other isn't, result is nullable
    if (t1->isNullable() || t2->isNullable()) {
        if (t1->isNullable() && !t2->isNullable()) {
            return t1;
        }
        if (!t1->isNullable() && t2->isNullable()) {
            return t2;
        }
    }

    // If no common type found, return error type
    errorHandler_.handleError(Error("TypeError",
        "No common type found between " + t1->toString() + " and " + t2->toString()));
    return std::make_shared<ErrorType>("NoCommonType");
}

std::shared_ptr<Type> TypeInference::inferBinaryOperation(
    std::shared_ptr<Type> leftType,
    std::shared_ptr<Type> rightType,
    const std::string& op,
    void* ctx
) {
    // Handle arithmetic operators
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
        if (leftType->getKind() == Type::Kind::Int && rightType->getKind() == Type::Kind::Int) {
            return std::make_shared<PrimitiveType>(Type::Kind::Int);
        }
        if ((leftType->getKind() == Type::Kind::Float || leftType->getKind() == Type::Kind::Int) &&
            (rightType->getKind() == Type::Kind::Float || rightType->getKind() == Type::Kind::Int)) {
            return std::make_shared<PrimitiveType>(Type::Kind::Float);
        }
        errorHandler_.handleError(Error("TypeError", "Invalid operands for arithmetic operation"));
        return std::make_shared<ErrorType>("InvalidOperands");
    }

    // Handle comparison operators
    if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") {
        if (isCompatible(leftType, rightType) || isCompatible(rightType, leftType)) {
            return std::make_shared<PrimitiveType>(Type::Kind::Bool);
        }
        errorHandler_.handleError(Error("TypeError", "Cannot compare incompatible types"));
        return std::make_shared<ErrorType>("IncomparableTypes");
    }

    // Handle logical operators
    if (op == "&&" || op == "||") {
        if (leftType->getKind() == Type::Kind::Bool && rightType->getKind() == Type::Kind::Bool) {
            return std::make_shared<PrimitiveType>(Type::Kind::Bool);
        }
        errorHandler_.handleError(Error("TypeError", "Logical operators require boolean operands"));
        return std::make_shared<ErrorType>("NonBooleanOperands");
    }

    errorHandler_.handleError(Error("TypeError", "Unknown binary operator: " + op));
    return std::make_shared<ErrorType>("UnknownOperator");
}

bool TypeInference::validateErrorMethodOverride(
    const std::string& errorClassName,
    const std::string& methodName,
    std::shared_ptr<Type> methodType,
    const std::string& baseClass
) {
    if (!methodType->isFunction()) {
        errorHandler_.handleError(Error("TypeError", "Method type must be a function type"));
        return false;
    }
    return true;  // TODO: Implement full override validation
}

bool TypeInference::validateErrorChain(std::shared_ptr<Type> chainType) {
    if (!chainType->isErrorChain()) {
        errorHandler_.handleError(Error("TypeError", "Type must be an error chain"));
        return false;
    }
    auto errorChain = std::static_pointer_cast<ErrorChainType>(chainType);
    return std::all_of(errorChain->getChainedErrors().begin(),
                      errorChain->getChainedErrors().end(),
                      [this](const auto& error) { return error->isError(); });
}

bool TypeInference::validateErrorTransformation(std::shared_ptr<Type> fromType, std::shared_ptr<Type> toType) {
    if (!fromType->isError() || !toType->isError()) {
        errorHandler_.handleError(Error("TypeError", "Both types must be error types for transformation"));
        return false;
    }
    return true;
}

bool TypeInference::validateErrorChainField(const std::string& fieldName, std::shared_ptr<Type> fieldType) {
    if (!fieldType->isErrorChain()) {
        errorHandler_.handleError(Error("TypeError", "Field '" + fieldName + "' must be an error chain type"));
        return false;
    }
    return validateErrorChain(fieldType);
}

bool TypeInference::isErrorChainType(std::shared_ptr<Type> type) {
    return type->isErrorChain();
}

bool TypeInference::isErrorType(std::shared_ptr<Type> type) {
    return type->isError() || type->isErrorChain();
}

std::shared_ptr<Type> TypeInference::inferErrorChainType(
    const std::string& errorType,
    const std::vector<std::shared_ptr<Type>>& chainedErrors
) {
    // Validate all chained errors are error types
    for (const auto& error : chainedErrors) {
        if (!error->isError()) {
            errorHandler_.handleError(Error("TypeError",
                "Invalid error chain: non-error type in chain"));
            return std::make_shared<ErrorType>("InvalidErrorChain");
        }
    }
    return std::make_shared<ErrorChainType>(errorType, chainedErrors);
}

std::shared_ptr<Type> TypeInference::transformErrorType(
    std::shared_ptr<Type> sourceError,
    const std::string& targetErrorType
) {
    if (!sourceError->isError()) {
        errorHandler_.handleError(Error("TypeError",
            "Cannot transform non-error type to error type"));
        return std::make_shared<ErrorType>("InvalidErrorTransformation");
    }
    return std::make_shared<ErrorType>(targetErrorType);
}

} // namespace pryst
