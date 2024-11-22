#pragma once

#include "scope_manager.hpp"
#include "type_registry.hpp"
#include "type.hpp"
#include <memory>
#include <string>
#include <vector>

namespace pryst {

class TypeChecker {
public:
    explicit TypeChecker(std::shared_ptr<TypeRegistry> registry)
        : scopeManager_(registry), typeRegistry_(registry) {
        typeRegistry_->registerType("Boolean", std::make_shared<PrimitiveType>("Boolean"));
    }

    void pushScope() {
        scopeManager_.pushScope();
    }

    void popScope() {
        scopeManager_.popScope();
    }

    void declareVariable(const std::string& name, std::shared_ptr<Type> type) {
        scopeManager_.declareVariable(name, type);
    }

    std::shared_ptr<Type> lookupVariable(const std::string& name) const {
        return scopeManager_.lookupVariable(name);
    }

    bool isErrorType(const std::string& typeName) const {
        return typeRegistry_->isErrorType(typeName);
    }

    void registerType(const std::string& name, std::shared_ptr<Type> type) {
        typeRegistry_->registerType(name, type);
    }

    // Add methods for type checking expressions and statements here
    std::shared_ptr<Type> checkArrayAccess(std::shared_ptr<Type> arrayType, std::shared_ptr<Type> indexType);
    std::shared_ptr<Type> checkArrayCreation(std::shared_ptr<Type> elementType);
    std::shared_ptr<Type> checkArrayAssignment(std::shared_ptr<Type> targetArray, std::shared_ptr<Type> sourceArray);

    std::shared_ptr<Type> checkBinaryExpression(std::shared_ptr<Type> left,
                                               const std::string& op,
                                               std::shared_ptr<Type> right);

    std::shared_ptr<Type> checkUnaryExpression(const std::string& op,
                                              std::shared_ptr<Type> operand);

    // Error handling methods
    std::shared_ptr<Type> checkNestedErrorHandling(
        const std::vector<std::shared_ptr<Type>>& tryErrors,
        const std::vector<std::shared_ptr<Type>>& catchErrors);

    std::shared_ptr<Type> checkErrorPropagation(
        std::shared_ptr<Type> sourceError,
        const std::vector<std::shared_ptr<Type>>& propagationPath);

    std::shared_ptr<Type> checkErrorInScope(std::shared_ptr<Type> error);

    std::shared_ptr<Type> transformError(
        std::shared_ptr<Type> sourceError,
        std::shared_ptr<Type> targetError);

    std::shared_ptr<Type> validateErrorChain(
        const std::vector<std::shared_ptr<Type>>& errorChain);

    // Type inference methods
    std::shared_ptr<Type> inferExpressionType(
        const std::vector<std::shared_ptr<Type>>& types,
        const std::vector<std::string>& operators);

    std::shared_ptr<Type> inferGenericType(
        std::shared_ptr<Type> genericType,
        std::shared_ptr<Type> parameterType);

    std::shared_ptr<Type> inferLambdaReturnType(
        const std::vector<std::shared_ptr<Type>>& paramTypes,
        const std::vector<std::string>& bodyOperators);

    std::shared_ptr<Type> checkNullCoalescing(
        std::shared_ptr<Type> nullableType,
        std::shared_ptr<Type> defaultType);

    std::shared_ptr<Type> checkComplexExpression(
        const std::vector<std::shared_ptr<Type>>& types,
        const std::vector<std::string>& operators);

    bool areTypesCompatible(std::shared_ptr<Type> type1, std::shared_ptr<Type> type2) {
        if (type1->toString() == type2->toString()) return true;

        if (type1->isFunction() && type2->isFunction()) {
            auto func1 = std::static_pointer_cast<FunctionType>(type1);
            auto func2 = std::static_pointer_cast<FunctionType>(type2);

            if (func1->getParameterTypes().size() != func2->getParameterTypes().size()) {
                return false;
            }

            for (size_t i = 0; i < func1->getParameterTypes().size(); i++) {
                if (!areTypesCompatible(func1->getParameterTypes()[i], func2->getParameterTypes()[i])) {
                    return false;
                }
            }

            return areTypesCompatible(func1->getReturnType(), func2->getReturnType());
        }

        return false;
    }

    std::shared_ptr<Type> resolveOverload(
        const std::string& funcName,
        const std::vector<std::shared_ptr<Type>>& argTypes) {
        auto funcType = lookupVariable(funcName);
        if (!funcType || !funcType->isFunction()) {
            return std::make_shared<ErrorType>("TypeError");
        }

        auto func = std::static_pointer_cast<FunctionType>(funcType);
        if (func->getParameterTypes().size() != argTypes.size()) {
            return std::make_shared<ErrorType>("ArgumentCountMismatch");
        }

        for (size_t i = 0; i < argTypes.size(); i++) {
            if (!areTypesCompatible(func->getParameterTypes()[i], argTypes[i])) {
                return std::make_shared<ErrorType>("ArgumentTypeMismatch");
            }
        }

        return func->getReturnType();
    }

private:
    ScopeManager scopeManager_;
    std::shared_ptr<TypeRegistry> typeRegistry_;
};

} // namespace pryst
