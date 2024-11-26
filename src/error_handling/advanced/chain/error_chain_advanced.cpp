#include "error_chain_advanced.hpp"
#include "../../../type_system/advanced/type_registry.hpp"
#include "../../../type_system/advanced/types.hpp"

using std::vector;
using std::shared_ptr;

namespace pryst {
namespace core {

ErrorChainAdvanced::ErrorChainAdvanced() {}

void ErrorChainAdvanced::addError(const shared_ptr<Error>& error) {
    errorChain.push_back(error);
}

bool ErrorChainAdvanced::hasErrors() const {
    return !errorChain.empty();
}

const vector<shared_ptr<Error>>& ErrorChainAdvanced::getErrors() const {
    return errorChain;
}

void ErrorChainAdvanced::clear() {
    errorChain.clear();
}

void ErrorChainAdvanced::addErrorWithContext(const shared_ptr<Error>& error, const string& context) {
    errorChain.push_back(error);
    errorContexts[error->getId()] = context;
}

void ErrorChainAdvanced::mergeChain(const ErrorChainAdvanced& other) {
    errorChain.insert(errorChain.end(), other.errorChain.begin(), other.errorChain.end());
    errorContexts.insert(other.errorContexts.begin(), other.errorContexts.end());
}

shared_ptr<Error> ErrorChainAdvanced::transformLastError(
    const std::function<shared_ptr<Error>(const shared_ptr<Error>&)>& transformer) {
    if (errorChain.empty()) return nullptr;

    auto lastError = errorChain.back();
    auto transformedError = transformer(lastError);
    if (transformedError) {
        errorChain.back() = transformedError;
        if (errorContexts.count(lastError->getId())) {
            errorContexts[transformedError->getId()] = errorContexts[lastError->getId()];
            errorContexts.erase(lastError->getId());
        }
    }
    return transformedError;
}

vector<shared_ptr<Error>> ErrorChainAdvanced::getErrorsByType(const string& errorType) const {
    vector<shared_ptr<Error>> filtered;
    std::copy_if(errorChain.begin(), errorChain.end(), std::back_inserter(filtered),
        [&](const shared_ptr<Error>& error) {
            return error->getType() == errorType;
        });
    return filtered;
}

vector<shared_ptr<Error>> ErrorChainAdvanced::getErrorsByContext(const string& context) const {
    vector<shared_ptr<Error>> filtered;
    std::copy_if(errorChain.begin(), errorChain.end(), std::back_inserter(filtered),
        [&](const shared_ptr<Error>& error) {
            return errorContexts.count(error->getId()) && errorContexts.at(error->getId()) == context;
        });
    return filtered;
}

void ErrorChainAdvanced::createCheckpoint() {
    checkpoints.push_back(errorChain.size());
}

void ErrorChainAdvanced::rollbackToCheckpoint() {
    if (checkpoints.empty()) return;

    size_t checkpoint = checkpoints.back();
    checkpoints.pop_back();

    while (errorChain.size() > checkpoint) {
        auto error = errorChain.back();
        errorContexts.erase(error->getId());
        errorChain.pop_back();
    }
}

} // namespace core
} // namespace pryst
