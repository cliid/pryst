#pragma once

#include <string>
#include <map>
#include <any>

namespace pryst {
namespace utils {

std::string jsonStringify(const std::map<std::string, std::any>& data);

} // namespace utils
} // namespace pryst
