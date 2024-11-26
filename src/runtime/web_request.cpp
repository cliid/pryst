#include "web_request.hpp"
#include <nlohmann/json.hpp>
#include <sstream>

namespace pryst {
namespace runtime {
namespace web {

Request::Request(const std::string& body) : body_(body) {}

std::map<std::string, std::any> Request::json() {
    std::map<std::string, std::any> result;
    try {
        nlohmann::json j = nlohmann::json::parse(body_);
        for (auto& [key, value] : j.items()) {
            if (value.is_string()) {
                result[key] = value.get<std::string>();
            } else if (value.is_number_integer()) {
                result[key] = value.get<int>();
            } else if (value.is_number_float()) {
                result[key] = value.get<float>();
            } else if (value.is_boolean()) {
                result[key] = value.get<bool>();
            }
        }
    } catch (const nlohmann::json::exception& e) {
        throw ValidationError("Invalid JSON format", "body", "json_parse");
    }
    return result;
}

} // namespace web
} // namespace runtime
} // namespace pryst
