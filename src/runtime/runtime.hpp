#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace pryst {
namespace core {

// Base class for runtime type information
struct RuntimeTypeInfo {
    const char* type_name;
    RuntimeTypeInfo* parent;

    RuntimeTypeInfo(const char* name, RuntimeTypeInfo* p = nullptr)
        : type_name(name), parent(p) {}
    virtual ~RuntimeTypeInfo() = default;
};

// Runtime type system for type information and inheritance
class RuntimeTypeSystem {
private:
    std::unordered_map<std::string, std::string> inheritance;
    std::unordered_set<std::string> nullableTypes;
    static RuntimeTypeSystem instance;

    RuntimeTypeSystem() = default;

public:
    static RuntimeTypeSystem& getInstance() {
        return instance;
    }

    void registerInheritance(const std::string& derived, const std::string& base) {
        inheritance[derived] = base;
    }

    const char* getSuperclass(const std::string& type) {
        // Handle nullable types by removing the '?' suffix
        std::string baseType = type;
        bool isNullable = false;
        if (!type.empty() && type.back() == '?') {
            baseType = type.substr(0, type.length() - 1);
            isNullable = true;
        }

        auto it = inheritance.find(baseType);
        if (it != inheritance.end()) {
            return isNullable ? (it->second + "?").c_str() : it->second.c_str();
        }
        return nullptr;
    }

    void registerNullableType(const std::string& type) {
        nullableTypes.insert(type);
    }

    bool isNullable(const std::string& type) const {
        return nullableTypes.find(type) != nullableTypes.end();
    }
};

} // namespace core
} // namespace pryst
