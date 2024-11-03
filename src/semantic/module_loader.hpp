#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <filesystem>

class ModuleLoader {
public:
    ModuleLoader();

    // Load a module from a file path
    bool loadModule(const std::string& modulePath);

    // Get the absolute path for a module based on import statement
    std::string resolveModulePath(const std::string& importPath, const std::string& currentModulePath);

    // Check if a module has been loaded
    bool isModuleLoaded(const std::string& modulePath) const;

    // Get the module's qualified name from its path
    std::string getModuleQualifiedName(const std::string& modulePath) const;

    // Add a module search path
    void addModuleSearchPath(const std::string& searchPath);

private:
    // Map of module paths to their loaded status
    std::unordered_map<std::string, bool> loadedModules;

    // List of module search paths
    std::vector<std::string> searchPaths;

    // Convert file path to module qualified name
    std::string pathToQualifiedName(const std::string& path) const;

    // Find module file in search paths
    std::string findModuleFile(const std::string& moduleName) const;
};
