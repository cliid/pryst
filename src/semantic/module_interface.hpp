#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "module_types.hpp"

namespace pryst {

// Represents a module interface declaration
struct ModuleInterface {
    std::string name;
    std::vector<std::string> exportedTypes;
    std::unordered_map<std::string, FunctionSignature> exportedFunctions;
    std::unordered_map<std::string, ClassSignature> exportedClasses;
    std::vector<std::string> dependencies;
    bool isPublic;
};

class ModuleInterfaceManager {
public:
    ModuleInterfaceManager() = default;
    ~ModuleInterfaceManager() = default;

    // Register a module interface
    void registerInterface(const std::string& modulePath, const ModuleInterface& interface);

    // Check if a module has an interface
    bool hasInterface(const std::string& modulePath) const;

    // Get a module's interface
    ModuleInterface getInterface(const std::string& modulePath) const;

    // Validate a module implementation against its interface
    bool validateImplementation(const std::string& modulePath, const ModuleInfo& implementation) const;

    // Parse a module interface file (.psti)
    ModuleInterface parseInterfaceFile(const std::string& interfacePath);

private:
    // Map of module paths to their interfaces
    std::unordered_map<std::string, ModuleInterface> interfaces;

    // Helper methods for interface validation
    bool validateFunctionSignature(const FunctionSignature& signature, const FunctionInfo& implementation) const;
    bool validateClassSignature(const ClassSignature& signature, const ClassInfo& implementation) const;
    bool validateExportedTypes(const ModuleInterface& interface, const ModuleInfo& implementation) const;
};

} // namespace pryst
