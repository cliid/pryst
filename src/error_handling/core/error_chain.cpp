#include "error_chain.hpp"
#include "error_type.hpp"
#include <sstream>

namespace pryst {

class DefaultErrorTransformation : public ErrorTransformation {
public:
    std::shared_ptr<Error> transform(const Error& error) override {
        // Default implementation just passes through the error
        return std::make_shared<Error>(error.getType(), error.what());
    }

    bool validateChain(const std::vector<std::shared_ptr<Type>>& chainedErrors) override {
        // Validate that all types in the chain are error types
        for (const auto& type : chainedErrors) {
            if (type->getKind() != TypeKind::Error) {
                return false;
            }
        }
        return true;
    }
};

// Factory function for creating error transformations
std::shared_ptr<ErrorTransformation> createDefaultTransformation() {
    return std::make_shared<DefaultErrorTransformation>();
}

// Helper function to create type errors with proper formatting
std::shared_ptr<Error> createTypeError(const std::string& expected, const std::string& actual) {
    std::stringstream ss;
    ss << "Type mismatch: expected '" << expected << "', got '" << actual << "'";
    return std::make_shared<Error>("TypeError", ss.str());
}

// Helper function to create null safety errors
std::shared_ptr<Error> createNullSafetyError(const std::string& varName) {
    std::stringstream ss;
    ss << "Null safety violation: variable '" << varName << "' may be null";
    return std::make_shared<Error>("NullSafetyError", ss.str());
}

// Helper function to create error chain validation errors
std::shared_ptr<Error> createErrorChainValidationError(const std::string& invalidType) {
    std::stringstream ss;
    ss << "Invalid error chain: type '" << invalidType << "' is not an error type";
    return std::make_shared<Error>("ErrorChainValidationError", ss.str());
}

} // namespace pryst
