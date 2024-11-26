#include "web.hpp"

namespace pryst {
namespace runtime {
namespace web {

// Implementation of any non-inline methods would go here

std::string Request::getMethod() const {
    return method;
}

std::string Request::getPath() const {
    return path;
}

std::string Request::getHeaders() const {
    std::string result;
    for (const auto& [key, value] : headers) {
        result += key + ": " + value + "\n";
    }
    return result;
}

std::string Request::getBody() const {
    return body;
}

} // namespace web
} // namespace runtime
} // namespace pryst
