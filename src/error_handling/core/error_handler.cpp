#include "error_chain.hpp"
#include "error_type.hpp"
#include "type_registry.hpp"
#include <sstream>

namespace pryst {
namespace core {

class TypedErrorHandler : public ErrorHandler {
public:
    explicit TypedErrorHandler(TypeRegistry& registry) : registry_(registry) {}

    void handleTypedError(const Error& error, const std::string& expectedType) override {
        auto errorType = makeErrorType(error.getMessage(), error.getType());
        auto expectedErrorType = makeErrorType("", expectedType);

        if (!errorType->isAssignableTo(expectedErrorType)) {
            auto chainedError = error.chain("Error type mismatch: expected '" +
                expectedType + "', got '" + error.getType() + "'")
                ->transform("TypeError");
            handleError(*chainedError);
            return;
        }

        handleError(error);
    }

private:
    TypeRegistry& registry_;
};

// Factory function for creating typed error handlers
inline std::shared_ptr<ErrorHandler> createTypedErrorHandler(TypeRegistry& registry) {
    return std::make_shared<TypedErrorHandler>(registry);
}

} // namespace core
} // namespace pryst
