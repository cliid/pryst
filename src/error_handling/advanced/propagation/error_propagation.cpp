#include "error_propagation.hpp"
#include <iostream>

using std::shared_ptr;
using std::vector;
using std::make_shared;

namespace pryst {
namespace core {

ErrorPropagation::ErrorPropagation(shared_ptr<TypeRegistry> registry)
    : typeRegistry_(registry) {}

shared_ptr<Type> ErrorPropagation::propagateError(
    shared_ptr<Type> sourceError,
    const vector<shared_ptr<Type>>& propagationPath) {

    if (!sourceError->isError()) {
        return make_shared<ErrorType>("InvalidSourceError");
    }

    for (const auto& error : propagationPath) {
        if (!error->isError()) {
            return make_shared<ErrorType>("InvalidPropagationPath");
        }
    }

    // Return the last error in the propagation path, or the source error if path is empty
    return propagationPath.empty() ? sourceError : propagationPath.back();
}

shared_ptr<Type> ErrorPropagation::propagateErrorThroughScope(
    shared_ptr<Type> error,
    const string& scopeName,
    bool propagateToParent) {

    if (!error->isError()) return nullptr;

    // Check if propagation is blocked by a barrier
    if (std::find(propagationBarriers_.begin(), propagationBarriers_.end(), scopeName)
        != propagationBarriers_.end()) {
        return error;
    }

    auto errorType = dynamic_pointer_cast<ErrorType>(error);
    return make_shared<ErrorType>(
        scopeName + "::" + errorType->getMessage()
    );
}

shared_ptr<Type> ErrorPropagation::propagateErrorWithTransform(
    shared_ptr<Type> error,
    const vector<shared_ptr<Type>>& path,
    const std::function<shared_ptr<Type>(shared_ptr<Type>)>& transformer) {

    if (!isValidPropagationPath(path)) return nullptr;

    auto currentError = error;
    for (const auto& contextType : path) {
        currentError = transformErrorForPropagation(currentError, contextType);
        if (transformer) {
            currentError = transformer(currentError);
        }
    }
    return currentError;
}

shared_ptr<Type> ErrorPropagation::propagateUnionError(
    shared_ptr<Type> unionError,
    const vector<shared_ptr<Type>>& path) {

    auto unionType = dynamic_pointer_cast<type_system::advanced::UnionType>(unionError);
    if (!unionType) return nullptr;

    vector<shared_ptr<Type>> propagatedErrors;
    for (const auto& error : unionType->getTypes()) {
        auto propagated = propagateError(error, path);
        if (propagated) propagatedErrors.push_back(propagated);
    }

    return make_shared<type_system::advanced::UnionType>(propagatedErrors);
}

void ErrorPropagation::addPropagationBarrier(const string& scopeName) {
    propagationBarriers_.push_back(scopeName);
}

void ErrorPropagation::removePropagationBarrier(const string& scopeName) {
    auto it = std::find(propagationBarriers_.begin(), propagationBarriers_.end(), scopeName);
    if (it != propagationBarriers_.end()) {
        propagationBarriers_.erase(it);
    }
}

bool ErrorPropagation::shouldPropagate(const string& fromScope, const string& toScope) const {
    return std::find(propagationBarriers_.begin(), propagationBarriers_.end(), fromScope)
           == propagationBarriers_.end();
}

bool ErrorPropagation::isValidPropagationPath(const vector<shared_ptr<Type>>& path) const {
    return std::all_of(path.begin(), path.end(),
        [](const shared_ptr<Type>& type) { return type != nullptr; });
}

shared_ptr<Type> ErrorPropagation::transformErrorForPropagation(
    shared_ptr<Type> error,
    shared_ptr<Type> contextType) {

    if (!error->isError()) return error;

    auto errorType = dynamic_pointer_cast<ErrorType>(error);
    auto context = contextType->toString();
    return make_shared<ErrorType>(
        context + " -> " + errorType->getMessage()
    );
}

} // namespace core
} // namespace pryst
