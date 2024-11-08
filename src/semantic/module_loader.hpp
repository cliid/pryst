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
    explicit ModuleLoader(std::shared_ptr<SymbolTable> symbolTable);
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

    // Block-level scope management
    void enterScope();
    void exitScope();

    // Using declarations
    void addUsingDeclaration(const std::string& moduleName, bool isModule);

    // Get module exports
    std::unordered_map<std::string, VariableInfo> getModuleExports(const std::string& qualifiedName) const;

    // Get module exported functions
    std::unordered_map<std::string, FunctionInfo> getModuleExportedFunctions(const std::string& qualifiedName) const;

    // Get module exported classes
    std::unordered_map<std::string, ClassInfo> getModuleExportedClasses(const std::string& qualifiedName) const;

    // Interface compliance
    bool verifyInterfaceCompliance(const std::string& implementation, const std::string& interface);

    // Namespace resolution
    std::string resolveQualifiedName(const std::string& name);
    bool isNameVisible(const std::string& name);

private:
    // Map of module paths to their loaded status
    std::unordered_map<std::string, bool> loadedModules;

    // Module cache storing parsed module information
    std::unordered_map<std::string, ModuleInfo> moduleCache;

    // List of module search paths
    std::vector<std::string> searchPaths;

    // Symbol table reference
    std::shared_ptr<SymbolTable> symbolTable;

    // Scope stack for block-level using declarations
    std::vector<std::unordered_map<std::string, bool>> scopeStack;

    // Helper methods
    std::string pathToQualifiedName(const std::string& path) const;
    std::string findModuleFile(const std::string& moduleName) const;
    void initializeSearchPaths();
    ModuleInfo parseModuleFile(const std::string& modulePath);
    bool validateModuleStructure(const std::string& modulePath) const;
    bool checkCircularDependency(const std::string& moduleName);
};
