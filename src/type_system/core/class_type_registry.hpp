#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "types.hpp"

namespace pryst {
namespace types {

class ClassTypeRegistry {
public:
    ClassTypeRegistry() = default;
    ~ClassTypeRegistry() = default;

    // Register a new class type
    void registerClass(const std::string& className, std::shared_ptr<types::ClassType> classType) {
        classTypes[className] = classType;
    }

    // Get the Type for a class
    std::shared_ptr<types::Type> getClassType(const std::string& className) {
        auto it = classTypes.find(className);
        if (it != classTypes.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Check if a class exists
    bool hasClass(const std::string& className) const {
        return classTypes.find(className) != classTypes.end();
    }

private:
    // Map of class names to their Type objects
    std::unordered_map<std::string, std::shared_ptr<types::ClassType>> classTypes;
};

} // namespace types
} // namespace pryst
