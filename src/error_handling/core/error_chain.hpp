#pragma once

#include <memory>
#include <string>
#include <vector>
#include "error.hpp"
#include "error_type.hpp"
#include "types.hpp"

namespace pryst {
namespace core {

class ErrorChain {
public:
    void addError(std::shared_ptr<Error> error) {
        errors_.push_back(error);
    }

    const std::vector<std::shared_ptr<Error>>& getErrors() const {
        return errors_;
    }

    bool hasErrors() const {
        return !errors_.empty();
    }

    std::string toString() const {
        std::string result;
        for (const auto& error : errors_) {
            if (!result.empty()) result += "\n";
            result += error->getType() + ": " + error->getMessage();
        }
        return result;
    }

private:
    std::vector<std::shared_ptr<Error>> errors_;
};

class ErrorTransformation {
public:
    virtual ~ErrorTransformation() = default;
    virtual std::shared_ptr<Error> transform(const Error& error) = 0;
    virtual bool validateChain(const std::vector<std::shared_ptr<Type>>& chainedErrors) {
        if (chainedErrors.empty()) return true;

        // Validate that each error in the chain is compatible with the next
        for (size_t i = 0; i < chainedErrors.size() - 1; ++i) {
            auto currentError = std::dynamic_pointer_cast<ErrorType>(chainedErrors[i]);
            auto nextError = std::dynamic_pointer_cast<ErrorType>(chainedErrors[i + 1]);

            if (!currentError || !nextError || !currentError->isAssignableTo(nextError)) {
                return false;
            }
        }
        return true;
    }
};

class ErrorHandler {
public:
    void setTransformation(std::shared_ptr<ErrorTransformation> transformation) {
        transformation_ = transformation;
    }

    template<typename ContextType>
    void handleError(const Error& error, ContextType* ctx) {
        handleError(error);  // Delegate to the base handler
    }

    void handleError(const Error& error) {
        auto transformedError = transformation_
            ? transformation_->transform(error)
            : std::make_shared<Error>(error.getType(), error.getMessage());
        chain_.addError(transformedError);
    }

    void handleTypedError(const Error& error, const std::string& expectedType) {
        auto transformedError = transformation_
            ? transformation_->transform(error)
            : std::make_shared<Error>(error.getType(), error.getMessage());

        // Create error type for validation
        auto errorType = makeErrorType(error.getMessage(), error.getType());
        auto expectedErrorType = makeErrorType("", expectedType);

        if (!errorType->isAssignableTo(expectedErrorType)) {
            handleError(Error("TypeError",
                "Expected error of type '" + expectedType +
                "', got '" + error.getType() + "'"));
            return;
        }

        chain_.addError(transformedError);
    }

    bool validateErrorChain(const std::vector<std::shared_ptr<Type>>& chainedErrors) {
        return transformation_ ? transformation_->validateChain(chainedErrors) : true;
    }

    const ErrorChain& getChain() const {
        return chain_;
    }

private:
    ErrorChain chain_;
    std::shared_ptr<ErrorTransformation> transformation_;
};

} // namespace core
} // namespace pryst
