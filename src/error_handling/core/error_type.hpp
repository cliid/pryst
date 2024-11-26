#pragma once

#include "../../type_system/core/type.hpp"
#include "error.hpp"

namespace pryst {
namespace core {

// Factory function for creating error types
inline std::shared_ptr<types::ErrorType> makeErrorType(const std::string& message, const std::string& errorType = "TypeError") {
    return std::make_shared<types::ErrorType>(message, errorType);
}

} // namespace core
} // namespace pryst
