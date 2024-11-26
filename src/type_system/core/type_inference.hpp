#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <sstream>
#include "types.hpp"
#include "error_chain.hpp"
#include "error_handler.hpp"

namespace pryst {

class TypeInference {
public:
    // Core type inference methods
    std::shared_ptr<Type> inferType(const std::string& expr, const std::unordered_map<std::string, std::shared_ptr<Type>>& context);

    // Nullable type handling
    std::shared_ptr<Type> makeNullable(std::shared_ptr<Type> type);
    bool isNullableCompatible(std::shared_ptr<Type> from, std::shared_ptr<Type> to);

    // Function type inference
    std::shared_ptr<Type> inferFunctionType(
        const std::vector<std::shared_ptr<Type>>& paramTypes,
        std::shared_ptr<Type> returnType
    );

    // Error handling
    ErrorHandler& getErrorHandler() { return errorHandler_; }
    const ErrorHandler& getErrorHandler() const { return errorHandler_; }

    // Type compatibility checking
    bool isCompatible(std::shared_ptr<Type> from, std::shared_ptr<Type> to);

    // Binary operation inference
    std::shared_ptr<Type> inferBinaryOperation(
        std::shared_ptr<Type> leftType,
        std::shared_ptr<Type> rightType,
        const std::string& op,
        void* ctx
    );

    // Type checking methods
    bool isBoolean(std::shared_ptr<Type> type) {
        return type->getKind() == Type::Kind::Bool;
    }

    bool isIterable(std::shared_ptr<Type> type) {
        return type->getKind() == Type::Kind::Array;
    }

    std::shared_ptr<Type> getIterableElementType(std::shared_ptr<Type> type) {
        if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(type)) {
            return arrayType->getElementType();
        }
        return nullptr;
    }

    // Error validation methods
    bool validateErrorMethodOverride(const std::string& errorClassName,
                                   const std::string& methodName,
                                   std::shared_ptr<Type> methodType,
                                   const std::string& baseClass);
    bool validateErrorChain(std::shared_ptr<Type> chainType);
    bool validateErrorTransformation(std::shared_ptr<Type> fromType, std::shared_ptr<Type> toType);
    bool validateErrorChainField(const std::string& fieldName, std::shared_ptr<Type> fieldType);
    bool isErrorType(std::shared_ptr<Type> type);
    bool isErrorChainType(std::shared_ptr<Type> type);

    // Additional type creation methods
    std::shared_ptr<Type> createMapType(std::shared_ptr<Type> keyType, std::shared_ptr<Type> valueType) {
        return std::make_shared<MapType>(keyType, valueType);
    }

    std::shared_ptr<Type> createArrayType(std::shared_ptr<Type> elementType) {
        return std::make_shared<ArrayType>(elementType);
    }

    // Additional nullable type methods
    bool isNullable(std::shared_ptr<Type> type) {
        return type && type->getKind() == Type::Kind::Nullable;
    }

    std::shared_ptr<Type> unwrapNullable(std::shared_ptr<Type> type) {
        if (auto nullableType = std::dynamic_pointer_cast<NullableType>(type)) {
            return nullableType->getInnerType();
        }
        return type;
    }

    // Type assignment compatibility
    bool isAssignable(std::shared_ptr<Type> target, std::shared_ptr<Type> source) {
        return isCompatible(source, target);
    }

private:
    ErrorHandler errorHandler_;

    // Helper methods
    bool isImplicitlyConvertible(std::shared_ptr<Type> from, std::shared_ptr<Type> to);
    std::shared_ptr<Type> findCommonType(std::shared_ptr<Type> t1, std::shared_ptr<Type> t2);
};

} // namespace pryst
