#pragma once

#include <string>
#include <memory>

namespace pryst {
namespace core {

class Error : public std::exception {
public:
    Error(const std::string& msg) : type_("Error"), message_(msg) {}
    Error(const std::string& type, const std::string& msg) : type_(type), message_(msg) {}

    const std::string& getMessage() const { return message_; }
    const std::string& getType() const { return type_; }
    const char* what() const noexcept override {
        cached_what_ = type_ + ": " + message_;
        return cached_what_.c_str();
    }

    std::shared_ptr<Error> chain(const std::string& msg) const {
        return std::make_shared<Error>(type_, msg + ": " + message_);
    }

    std::shared_ptr<Error> transform(const std::string& newType) const {
        return std::make_shared<Error>(newType, message_);
    }

private:
    std::string type_;
    std::string message_;
    mutable std::string cached_what_;  // Cache for what() string
};

} // namespace core
} // namespace pryst
