#pragma once

#include "scope_manager.hpp"
#include "type_registry.hpp"
#include "type.hpp"
#include <memory>
#include <string>
#include <vector>

using std::shared_ptr;
using std::string;
using std::vector;
using std::make_shared;
using std::static_pointer_cast;

namespace pryst {
namespace core {

class TypeCheckerAdvanced {
public:
    explicit TypeCheckerAdvanced(shared_ptr<TypeRegistry> registry)
        : scopeManager_(registry), typeRegistry_(registry) {
        typeRegistry_->registerType("Boolean", make_shared<PrimitiveType>("Boolean"));
    }

    void pushScope() {
        scopeManager_.pushScope();
    }

    void popScope() {
        scopeManager_.popScope();
    }

    void declareVariable(const string& name, shared_ptr<Type> type) {
        scopeManager_.declareVariable(name, type);
    }

    shared_ptr<Type> lookupVariable(const string& name) const {
        return scopeManager_.lookupVariable(name);
    }

    bool isErrorType(const string& typeName) const {
        return typeRegistry_->isErrorType(typeName);
    }

    void registerType(const string& name, shared_ptr<Type> type) {
        typeRegistry_->registerType(name, type);
    }

    // Add methods for type checking expressions and statements here
    shared_ptr<Type> checkArrayAccess(shared_ptr<Type> arrayType, shared_ptr<Type> indexType);
    shared_ptr<Type> checkArrayCreation(shared_ptr<Type> elementType);
    shared_ptr<Type> checkArrayAssignment(shared_ptr<Type> targetArray, shared_ptr<Type> sourceArray);

    shared_ptr<Type> checkBinaryExpression(shared_ptr<Type> left,
                                               const string& op,
                                               shared_ptr<Type> right);

    shared_ptr<Type> checkUnaryExpression(const string& op,
                                              shared_ptr<Type> operand);

    // Error handling methods
    shared_ptr<Type> checkNestedErrorHandling(
        const vector<shared_ptr<Type>>& tryErrors,
        const vector<shared_ptr<Type>>& catchErrors);

    shared_ptr<Type> checkErrorPropagation(
        shared_ptr<Type> sourceError,
        const vector<shared_ptr<Type>>& propagationPath);

    shared_ptr<Type> checkErrorInScope(shared_ptr<Type> error);

    shared_ptr<Type> transformError(
        shared_ptr<Type> sourceError,
        shared_ptr<Type> targetError);

    shared_ptr<Type> validateErrorChain(
        const vector<shared_ptr<Type>>& errorChain);

    // Type inference methods
    shared_ptr<Type> inferExpressionType(
        const vector<shared_ptr<Type>>& types,
        const vector<string>& operators);

    shared_ptr<Type> inferGenericType(
        shared_ptr<Type> genericType,
        shared_ptr<Type> parameterType);

    shared_ptr<Type> inferLambdaReturnType(
        const vector<shared_ptr<Type>>& paramTypes,
        const vector<string>& bodyOperators);

    shared_ptr<Type> checkNullCoalescing(
        shared_ptr<Type> nullableType,
        shared_ptr<Type> defaultType);

    shared_ptr<Type> checkComplexExpression(
        const vector<shared_ptr<Type>>& types,
        const vector<string>& operators);

    bool areTypesCompatible(shared_ptr<Type> type1, shared_ptr<Type> type2) {
        if (type1->toString() == type2->toString()) return true;

        if (type1->isFunction() && type2->isFunction()) {
            auto func1 = static_pointer_cast<FunctionType>(type1);
            auto func2 = static_pointer_cast<FunctionType>(type2);

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

    shared_ptr<Type> resolveOverload(
        const string& funcName,
        const vector<shared_ptr<Type>>& argTypes) {
        auto funcType = lookupVariable(funcName);
        if (!funcType || !funcType->isFunction()) {
            return make_shared<ErrorType>("TypeError");
        }

        auto func = static_pointer_cast<FunctionType>(funcType);
        if (func->getParameterTypes().size() != argTypes.size()) {
            return make_shared<ErrorType>("ArgumentCountMismatch");
        }

        for (size_t i = 0; i < argTypes.size(); i++) {
            if (!areTypesCompatible(func->getParameterTypes()[i], argTypes[i])) {
                return make_shared<ErrorType>("ArgumentTypeMismatch");
            }
        }

        return func->getReturnType();
    }

private:
    ScopeManager scopeManager_;
    shared_ptr<TypeRegistry> typeRegistry_;
};

} // namespace core
} // namespace pryst
