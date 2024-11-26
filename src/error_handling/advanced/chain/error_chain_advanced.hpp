#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>
#include "../../../include/error.hpp"

using std::vector;
using std::shared_ptr;
using std::string;
using std::unordered_map;

namespace pryst {
namespace core {

class ErrorChainAdvanced {
public:
    ErrorChainAdvanced();
    void addError(const shared_ptr<Error>& error);
    bool hasErrors() const;
    const vector<shared_ptr<Error>>& getErrors() const;
    void clear();

    // Advanced error chain operations
    void addErrorWithContext(const shared_ptr<Error>& error, const string& context);
    void mergeChain(const ErrorChainAdvanced& other);

    // Error transformation
    shared_ptr<Error> transformLastError(
        const std::function<shared_ptr<Error>(const shared_ptr<Error>&)>& transformer);

    // Error filtering and querying
    vector<shared_ptr<Error>> getErrorsByType(const string& errorType) const;
    vector<shared_ptr<Error>> getErrorsByContext(const string& context) const;

    // Chain manipulation
    void rollbackToCheckpoint();
    void createCheckpoint();

private:
    vector<shared_ptr<Error>> errorChain;
    vector<size_t> checkpoints;
    unordered_map<string, string> errorContexts;
};

} // namespace core
} // namespace pryst
