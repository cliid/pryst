#pragma once

#include <string>
#include <vector>
#include <memory>
#include "error.hpp"

namespace pryst {
namespace core {

class ErrorHandler {
public:
    void reportError(const std::string& type, const std::string& message) {
        errors_.push_back(std::make_shared<core::Error>(type, message));
    }

    void reportError(std::shared_ptr<core::Error> error) {
        errors_.push_back(error);
    }

    bool hasErrors() const {
        return !errors_.empty();
    }

    const std::vector<std::shared_ptr<core::Error>>& getErrors() const {
        return errors_;
    }

    void clear() {
        errors_.clear();
    }

private:
    std::vector<std::shared_ptr<core::Error>> errors_;
};

} // namespace core
} // namespace pryst
