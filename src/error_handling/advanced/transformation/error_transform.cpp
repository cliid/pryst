#include "error_transform.hpp"
#include <iostream>

using std::shared_ptr;
using std::string;
using std::make_shared;
using std::dynamic_pointer_cast;

namespace pryst {
namespace core {

ErrorTransform::ErrorTransform(shared_ptr<TypeRegistry> registry)
    : typeRegistry_(registry) {}

shared_ptr<Type> ErrorTransform::transformError(
    shared_ptr<Type> sourceError,
    shared_ptr<Type> targetError) {

    if (!sourceError->isError() || !targetError->isError()) {
        return make_shared<ErrorType>("InvalidTransformationTypes");
    }

    // Create a new error type that combines information from both errors
    auto sourceErrorType = dynamic_pointer_cast<ErrorType>(sourceError);
    auto targetErrorType = dynamic_pointer_cast<ErrorType>(targetError);

    return make_shared<ErrorType>(
        targetErrorType->getMessage() + " (Caused by: " + sourceErrorType->getMessage() + ")"
    );
}

shared_ptr<Type> ErrorTransform::transformToCustomError(
    shared_ptr<Type> sourceError,
    const string& customErrorType) {

    if (!sourceError->isError()) {
        return make_shared<ErrorType>("InvalidSourceError");
    }

    auto sourceErrorType = dynamic_pointer_cast<ErrorType>(sourceError);
    return make_shared<ErrorType>(
        customErrorType + " (Original: " + sourceErrorType->getMessage() + ")"
    );
}

shared_ptr<Type> ErrorTransform::transformErrorWithContext(
    shared_ptr<Type> sourceError,
    shared_ptr<Type> targetError,
    const string& context) {

    if (!isCompatibleErrorType(sourceError, targetError)) {
        return make_shared<ErrorType>("IncompatibleErrorTypes");
    }

    auto transformed = transformError(sourceError, targetError);
    auto errorType = dynamic_pointer_cast<ErrorType>(transformed);
    return make_shared<ErrorType>(
        context + ": " + errorType->getMessage()
    );
}

shared_ptr<Type> ErrorTransform::chainErrorTransformation(
    const vector<shared_ptr<Type>>& errorChain,
    shared_ptr<Type> targetError) {

    if (errorChain.empty()) return targetError;

    auto result = targetError;
    for (auto it = errorChain.rbegin(); it != errorChain.rend(); ++it) {
        result = transformError(*it, result);
    }
    return result;
}

shared_ptr<Type> ErrorTransform::transformUnionError(
    shared_ptr<Type> unionError,
    const std::function<shared_ptr<Type>(shared_ptr<Type>)>& transformer) {

    auto unionType = dynamic_pointer_cast<type_system::advanced::UnionType>(unionError);
    if (!unionType) return nullptr;

    vector<shared_ptr<Type>> transformedErrors;
    for (const auto& error : unionType->getTypes()) {
        auto transformed = transformer(error);
        if (transformed) transformedErrors.push_back(transformed);
    }

    return mergeErrorTypes(transformedErrors);
}

bool ErrorTransform::isCompatibleErrorType(shared_ptr<Type> source, shared_ptr<Type> target) {
    return source && target && source->isError() && target->isError();
}

shared_ptr<Type> ErrorTransform::mergeErrorTypes(const vector<shared_ptr<Type>>& errors) {
    if (errors.empty()) return nullptr;
    if (errors.size() == 1) return errors[0];

    string mergedMessage;
    for (const auto& error : errors) {
        auto errorType = dynamic_pointer_cast<ErrorType>(error);
        if (!mergedMessage.empty()) mergedMessage += " | ";
        mergedMessage += errorType->getMessage();
    }

    return make_shared<ErrorType>(mergedMessage);
}

} // namespace core
} // namespace pryst
