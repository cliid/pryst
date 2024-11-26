#include "runtime_type_ops.hpp"
#include "runtime_registry.hpp"
#include "../error.hpp"
#include <cstring>
#include <iostream>

namespace pryst {
namespace runtime {

bool TypeOperations::isNullable(void* obj) {
    return !obj || RuntimeRegistry::getInstance().isNullable(obj);
}

bool TypeOperations::isArray(void* obj) {
    if (!obj) return false;
    const char* type = RuntimeRegistry::getInstance().getObjectType(obj);
    return type && strstr(type, "[]") != nullptr;
}

const char* TypeOperations::getBaseTypeName(void* obj) {
    return obj ? RuntimeRegistry::getInstance().getObjectType(obj) : "null";
}

std::string TypeOperations::getFullTypeName(void* obj) {
    std::string typeName = getBaseTypeName(obj);
    if (isArray(obj)) typeName += "[]";
    if (isNullable(obj)) typeName += "?";
    return typeName;
}

bool pryst_runtime_is_nullable(void* obj) {
    return TypeOperations::isNullable(obj);
}

bool pryst_runtime_instanceof(void* obj, const char* typeName) {
    if (!obj || !typeName) return false;
    const char* actualType = pryst_runtime_typeof(obj);
    if (!actualType) return false;
    if (strcmp(actualType, "null") == 0) return false;

    // Handle nullable types first
    bool isNullable = strstr(actualType, "?") != nullptr;
    bool isTypeNullable = strstr(typeName, "?") != nullptr;

    // Strip nullable markers for comparison
    std::string actualBase = isNullable ? std::string(actualType).substr(0, strlen(actualType) - 1) : actualType;
    std::string typeBase = isTypeNullable ? std::string(typeName).substr(0, strlen(typeName) - 1) : typeName;

    // Handle array types
    bool isArray = strstr(actualBase.c_str(), "[]") != nullptr;
    bool isTypeArray = strstr(typeBase.c_str(), "[]") != nullptr;
    if (isArray != isTypeArray) return false;

    // Strip array markers for comparison if both are arrays
    actualBase = isArray ? actualBase.substr(0, actualBase.length() - 2) : actualBase;
    typeBase = isTypeArray ? typeBase.substr(0, typeBase.length() - 2) : typeBase;

    return actualBase == typeBase ||
           RuntimeRegistry::getInstance().isSubclassOf(actualBase.c_str(), typeBase.c_str());
}

const char* pryst_runtime_typeof(void* obj) {
    if (!obj) return "null";

    // Get type information from RuntimeRegistry
    const char* type = RuntimeRegistry::getInstance().getObjectType(obj);
    if (!type) return "Object";

    // Handle nullable types
    if (RuntimeRegistry::getInstance().isNullable(obj)) {
        static std::string nullableType;
        nullableType = std::string(type);
        if (nullableType.back() != '?') {
            nullableType += "?";
        }
        return nullableType.c_str();
    }

    return type;
}

} // namespace runtime
} // namespace pryst
