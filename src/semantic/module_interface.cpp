#include "module_interface.hpp"
#include "../utils/logger.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace pryst {

void ModuleInterfaceManager::registerInterface(const std::string& modulePath, const ModuleInterface& interface) {
    interfaces[modulePath] = interface;
    PRYST_DEBUG("Registered interface for module: " + modulePath);
}

bool ModuleInterfaceManager::hasInterface(const std::string& modulePath) const {
    return interfaces.find(modulePath) != interfaces.end();
}

ModuleInterface ModuleInterfaceManager::getInterface(const std::string& modulePath) const {
    auto it = interfaces.find(modulePath);
    if (it == interfaces.end()) {
        throw std::runtime_error("No interface found for module: " + modulePath);
    }
    return it->second;
}

bool ModuleInterfaceManager::validateImplementation(
    const std::string& modulePath,
    const ModuleInfo& implementation
) const {
    PRYST_DEBUG("Validating implementation for module: " + modulePath);

    if (!hasInterface(modulePath)) {
        PRYST_DEBUG("No interface to validate against for module: " + modulePath);
        return true; // No interface means no validation needed
    }

    const auto& interface = getInterface(modulePath);

    // Validate exported types
    if (!validateExportedTypes(interface, implementation)) {
        PRYST_ERROR("Exported types validation failed for module: " + modulePath);
        return false;
    }

    // Validate exported functions
    for (const auto& [funcName, signature] : interface.exportedFunctions) {
        auto implFuncIt = implementation.exportedFunctions.find(funcName);
        if (implFuncIt == implementation.exportedFunctions.end()) {
            PRYST_ERROR("Required function not found in implementation: " + funcName);
            return false;
        }

        // Validate each function overload
        bool foundMatchingSignature = false;
        for (const auto& funcInfo : implFuncIt->second) {
            if (validateFunctionSignature(signature, *funcInfo)) {
                foundMatchingSignature = true;
                break;
            }
        }

        if (!foundMatchingSignature) {
            PRYST_ERROR("No matching signature found for function: " + funcName);
            return false;
        }
    }

    // Validate exported classes
    for (const auto& [className, signature] : interface.exportedClasses) {
        auto implClassIt = implementation.exportedClasses.find(className);
        if (implClassIt == implementation.exportedClasses.end()) {
            PRYST_ERROR("Required class not found in implementation: " + className);
            return false;
        }

        if (!validateClassSignature(signature, implClassIt->second)) {
            PRYST_ERROR("Class signature validation failed for: " + className);
            return false;
        }
    }

    PRYST_DEBUG("Implementation validation successful for module: " + modulePath);
    return true;
}

ModuleInterface ModuleInterfaceManager::parseInterfaceFile(const std::string& interfacePath) {
    PRYST_DEBUG("Parsing interface file: " + interfacePath);

    std::ifstream file(interfacePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open interface file: " + interfacePath);
    }

    ModuleInterface interface;
    std::string line;
    bool inInterfaceBlock = false;
    int braceCount = 0;

    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line.find("//") == 0) continue;

        // Parse interface declaration
        if (line.find("interface") == 0) {
            size_t nameStart = line.find_first_not_of(" \t", 9);
            size_t nameEnd = line.find("{");
            if (nameStart != std::string::npos && nameEnd != std::string::npos) {
                interface.name = line.substr(nameStart, nameEnd - nameStart);
                // Trim whitespace
                interface.name.erase(0, interface.name.find_first_not_of(" \t"));
                interface.name.erase(interface.name.find_last_not_of(" \t") + 1);
                inInterfaceBlock = true;
                braceCount++;
            }
        }
        // Parse function signatures
        else if (inInterfaceBlock && line.find("fn") == 0) {
            FunctionSignature sig;
            size_t nameStart = line.find_first_not_of(" \t", 2);
            size_t paramStart = line.find("(");
            if (nameStart != std::string::npos && paramStart != std::string::npos) {
                sig.name = line.substr(nameStart, paramStart - nameStart);
                sig.name.erase(0, sig.name.find_first_not_of(" \t"));
                sig.name.erase(sig.name.find_last_not_of(" \t") + 1);

                // Parse return type
                size_t arrowPos = line.find("->");
                if (arrowPos != std::string::npos) {
                    size_t returnTypeStart = line.find_first_not_of(" \t", arrowPos + 2);
                    size_t returnTypeEnd = line.find_first_of(" \t{", returnTypeStart);
                    sig.returnType = line.substr(returnTypeStart, returnTypeEnd - returnTypeStart);
                }

                // Parse parameters
                size_t paramEnd = line.find(")");
                std::string params = line.substr(paramStart + 1, paramEnd - paramStart - 1);
                std::istringstream paramStream(params);
                std::string param;
                while (std::getline(paramStream, param, ',')) {
                    size_t colonPos = param.find(":");
                    if (colonPos != std::string::npos) {
                        std::string paramName = param.substr(0, colonPos);
                        std::string paramType = param.substr(colonPos + 1);
                        // Trim whitespace
                        paramName.erase(0, paramName.find_first_not_of(" \t"));
                        paramName.erase(paramName.find_last_not_of(" \t") + 1);
                        paramType.erase(0, paramType.find_first_not_of(" \t"));
                        paramType.erase(paramType.find_last_not_of(" \t") + 1);
                        sig.parameters.push_back({paramName, paramType});
                    }
                }

                sig.isPublic = line.find("pub") != std::string::npos;
                sig.isAsync = line.find("async") != std::string::npos;

                interface.exportedFunctions[sig.name] = sig;
            }
        }
        // Parse class signatures
        else if (inInterfaceBlock && line.find("class") == 0) {
            ClassSignature sig;
            size_t nameStart = line.find_first_not_of(" \t", 5);
            size_t nameEnd = line.find_first_of(" \t{", nameStart);
            if (nameStart != std::string::npos) {
                sig.name = line.substr(nameStart, nameEnd - nameStart);
                sig.isPublic = line.find("pub") != std::string::npos;
                interface.exportedClasses[sig.name] = sig;
            }
        }

        // Track braces
        size_t openBrace = line.find("{");
        size_t closeBrace = line.find("}");
        if (openBrace != std::string::npos) braceCount++;
        if (closeBrace != std::string::npos) {
            braceCount--;
            if (braceCount == 0) inInterfaceBlock = false;
        }
    }

    PRYST_DEBUG("Successfully parsed interface file: " + interfacePath);
    return interface;
}

bool ModuleInterfaceManager::validateFunctionSignature(
    const FunctionSignature& signature,
    const FunctionInfo& implementation
) const {
    // Check return type
    if (signature.returnType != implementation.returnType) {
        PRYST_DEBUG("Return type mismatch for function: " + signature.name);
        return false;
    }

    // Check parameter count
    if (signature.parameters.size() != implementation.paramTypes.size()) {
        PRYST_DEBUG("Parameter count mismatch for function: " + signature.name);
        return false;
    }

    // Check parameter types
    for (size_t i = 0; i < signature.parameters.size(); i++) {
        if (signature.parameters[i].second != implementation.paramTypes[i]) {
            PRYST_DEBUG("Parameter type mismatch for function: " + signature.name);
            return false;
        }
    }

    return true;
}

bool ModuleInterfaceManager::validateClassSignature(
    const ClassSignature& signature,
    const ClassInfo& implementation
) const {
    // Check base classes
    for (const auto& baseClass : signature.baseClasses) {
        if (std::find(implementation.baseClasses.begin(),
                     implementation.baseClasses.end(),
                     baseClass) == implementation.baseClasses.end()) {
            PRYST_DEBUG("Missing base class in implementation: " + baseClass);
            return false;
        }
    }

    // Check properties
    for (const auto& [propName, propType] : signature.properties) {
        auto implPropIt = implementation.properties.find(propName);
        if (implPropIt == implementation.properties.end() ||
            implPropIt->second != propType) {
            PRYST_DEBUG("Property mismatch in implementation: " + propName);
            return false;
        }
    }

    // Check methods
    for (const auto& [methodName, methodSig] : signature.methods) {
        auto implMethodIt = implementation.methods.find(methodName);
        if (implMethodIt == implementation.methods.end() ||
            !validateFunctionSignature(methodSig, *implMethodIt->second)) {
            PRYST_DEBUG("Method mismatch in implementation: " + methodName);
            return false;
        }
    }

    return true;
}

bool ModuleInterfaceManager::validateExportedTypes(
    const ModuleInterface& interface,
    const ModuleInfo& implementation
) const {
    for (const auto& type : interface.exportedTypes) {
        if (std::find(implementation.exportedTypes.begin(),
                     implementation.exportedTypes.end(),
                     type) == implementation.exportedTypes.end()) {
            PRYST_DEBUG("Missing exported type in implementation: " + type);
            return false;
        }
    }
    return true;
}

} // namespace pryst
