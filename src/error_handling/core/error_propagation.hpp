#pragma once

#include <functional>
#include <memory>
#include <string>
#include "error.hpp"

namespace pryst {
namespace core {

template<typename T>
std::shared_ptr<T> propagateErrorThroughScope(const std::string& errorType, const std::string& message) {
    throw Error(errorType, message);
    return nullptr;
}

template<typename T>
std::shared_ptr<T> propagateErrorWithTransform(
    std::function<std::shared_ptr<T>()> operation,
    const std::string& errorContext
) {
    try {
        return operation();
    } catch (const Error& e) {
        throw Error(e.getType(), errorContext + ": " + e.what());
    } catch (const std::exception& e) {
        throw Error("RuntimeError", errorContext + ": " + e.what());
    }
    return nullptr;
}

template<typename T>
std::shared_ptr<T> propagateErrorWithScope(
    std::function<std::shared_ptr<T>()> operation,
    const std::string& scope,
    const std::string& errorContext
) {
    try {
        return operation();
    } catch (const Error& e) {
        throw Error(e.getType(), scope + ": " + errorContext + ": " + e.what());
    } catch (const std::exception& e) {
        throw Error("RuntimeError", scope + ": " + errorContext + ": " + e.what());
    }
    return nullptr;
}

} // namespace core
} // namespace pryst
