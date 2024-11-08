#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include "types.hpp"
#include "symbol_table.hpp"

class ModuleLoader {
public:
    ModuleLoader(std::shared_ptr<SymbolTable> symbolTable);
    ~ModuleLoader() = default;

    // Load a module from a file path
    ModuleInfo loadModule(const std::string& modulePath);

    // Get the absolute path for a module based on import statement
    std::string resolveModulePath(const std::string& importPath, const std::string& currentModulePath);

    // Check if a module has been loaded
    bool isModuleLoaded(const std::string& modulePath) const;

    // Get the module's qualified name from its path
    std::string getModuleQualifiedName(const std::string& modulePath) const;

    // Add a module search path
    void addModuleSearchPath(const std::string& searchPath);

    // Get module info from cache
    ModuleInfo getModuleInfo(const std::string& qualifiedName) const;

    // Initialize module system
    void initializeModuleSystem();

    // Get all available modules in search paths
    std::vector<std::string> discoverModules() const;

    // Get module exports
    std::unordered_map<std::string, VariableInfo> getModuleExports(const std::string& qualifiedName) const;

    // Get module exported functions
    std::unordered_map<std::string, FunctionInfo> getModuleExportedFunctions(const std::string& qualifiedName) const;

    // Get module exported classes
    std::unordered_map<std::string, ClassInfo> getModuleExportedClasses(const std::string& qualifiedName) const;

private:
    // Map of module paths to their loaded status
    std::unordered_map<std::string, bool> loadedModules;

    // Module cache storing parsed module information
    std::unordered_map<std::string, ModuleInfo> moduleCache;

    // List of module search paths
    std::vector<std::string> searchPaths;

    // Symbol table reference
    std::shared_ptr<SymbolTable> symbolTable;

    // Convert file path to module qualified name
    std::string pathToQualifiedName(const std::string& path) const;

    // Find module file in search paths
    std::string findModuleFile(const std::string& moduleName) const;

    // Initialize default module search paths
    void initializeSearchPaths();

    // Parse module file and extract exports
    ModuleInfo parseModuleFile(const std::string& modulePath);

    // Validate module structure
    bool validateModuleStructure(const std::string& modulePath) const;
};
