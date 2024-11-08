#include "module_loader.hpp"
#include "../utils/logger.hpp"
#include "../utils/debug.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>

ModuleLoader::ModuleLoader(std::shared_ptr<SymbolTable> symbolTable)
    : symbolTable(symbolTable) {
    initializeModuleSystem();
}

void ModuleLoader::initializeModuleSystem() {
    namespace fs = std::filesystem;

    // Create src/modules directory if it doesn't exist
    fs::path modulesDir = fs::path("src") / "modules";
    if (!fs::exists(modulesDir)) {
        fs::create_directories(modulesDir);
    }

    // Add src/modules to search paths
    addModuleSearchPath(modulesDir.string());

    // Initialize default search paths
    initializeSearchPaths();
}

void ModuleLoader::initializeSearchPaths() {
    // Add current directory
    searchPaths.push_back(".");

    // Add src/modules directory
    searchPaths.push_back("src/modules");
}

ModuleInfo ModuleLoader::loadModule(const std::string& modulePath) {
    PRYST_DEBUG("Attempting to load module: " + modulePath);

    // Check cache first
    if (isModuleLoaded(modulePath)) {
        PRYST_DEBUG("Module already loaded, retrieving from cache: " + modulePath);
        auto it = moduleCache.find(modulePath);
        if (it != moduleCache.end()) {
            return it->second;
        }
    }

    try {
        // Convert module path to filesystem path
        PRYST_DEBUG("Resolving module path: " + modulePath);
        std::string resolvedPath = resolveModulePath(modulePath, "");
        PRYST_DEBUG("Resolved path: " + resolvedPath);

        // Mark as loaded to prevent circular imports
        loadedModules[modulePath] = true;
        PRYST_DEBUG("Marked module as loaded: " + modulePath);

        // Parse the module file and get its info
        PRYST_DEBUG("Parsing module file: " + resolvedPath);
        ModuleInfo moduleInfo = parseModuleFile(resolvedPath);
        PRYST_DEBUG("Module file parsed successfully");

        // Set the qualified name based on the original module path
        moduleInfo.qualifiedName = modulePath.substr(0, modulePath.find("::"));
        PRYST_DEBUG("Set qualified name: " + moduleInfo.qualifiedName);

        // Register module functions with symbol table
        PRYST_DEBUG("Registering module functions with symbol table");
        for (const auto& [funcName, funcInfos] : moduleInfo.exportedFunctions) {
            for (const auto& funcInfo : funcInfos) {
                std::string qualifiedFuncName = modulePath + "::" + funcName;
                PRYST_DEBUG("Registering function: " + qualifiedFuncName);
                symbolTable->addFunction(qualifiedFuncName, funcInfo);
            }
        }

        // Store module info in cache
        PRYST_DEBUG("Storing module info in cache: " + modulePath);
        moduleCache[modulePath] = moduleInfo;

        return moduleInfo;
    } catch (const std::exception& e) {
        // Remove from loaded modules on failure
        loadedModules.erase(modulePath);
        PRYST_DEBUG("Failed to load module: " + modulePath + " - " + e.what());
        throw std::runtime_error("Failed to load module '" + modulePath + "': " + e.what());
    }
}

ModuleInfo ModuleLoader::parseModuleFile(const std::string& modulePath) {
    ModuleInfo moduleInfo;
    moduleInfo.qualifiedName = pathToQualifiedName(modulePath);

    // Read the module file
    std::ifstream file(modulePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open module file: " + modulePath);
    }

    std::string line;
    bool inModuleBlock = false;
    std::string currentModuleName;
    std::string currentFunctionName;
    std::string currentFunctionReturnType;
    bool inFunctionBlock = false;
    int braceCount = 0;

    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line.find("//") == 0) continue;

        // Check for module declaration
        if (line.find("module") == 0) {
            size_t nameStart = line.find_first_not_of(" \t", 6);
            size_t nameEnd = line.find("{");
            if (nameStart != std::string::npos && nameEnd != std::string::npos) {
                currentModuleName = line.substr(nameStart, nameEnd - nameStart);
                // Trim whitespace
                currentModuleName.erase(0, currentModuleName.find_first_not_of(" \t"));
                currentModuleName.erase(currentModuleName.find_last_not_of(" \t") + 1);
                inModuleBlock = true;
                braceCount++;
            }
        }
        // Check for function declaration inside module
        else if (inModuleBlock && line.find("fn") == 0) {
            size_t nameStart = line.find_first_not_of(" \t", 2);
            size_t paramStart = line.find("(");
            if (nameStart != std::string::npos && paramStart != std::string::npos) {
                currentFunctionName = line.substr(nameStart, paramStart - nameStart);
                // Trim whitespace
                currentFunctionName.erase(0, currentFunctionName.find_first_not_of(" \t"));
                currentFunctionName.erase(currentFunctionName.find_last_not_of(" \t") + 1);

                // Extract return type if specified
                size_t arrowPos = line.find("->");
                if (arrowPos != std::string::npos) {
                    size_t returnTypeStart = line.find_first_not_of(" \t", arrowPos + 2);
                    size_t returnTypeEnd = line.find_first_of(" \t{", returnTypeStart);
                    currentFunctionReturnType = line.substr(returnTypeStart, returnTypeEnd - returnTypeStart);
                } else {
                    currentFunctionReturnType = "void"; // Default return type
                }

                // Create function info
                auto funcInfo = std::make_shared<FunctionInfo>();
                funcInfo->returnType = currentFunctionReturnType;
                funcInfo->paramTypes = {}; // TODO: Parse parameter types
                funcInfo->hasExplicitReturnType = true;
                funcInfo->isAnonymous = false;
                funcInfo->scopeLevel = 0; // Module-level functions are at scope level 0
                moduleInfo.exportedFunctions[currentFunctionName].push_back(funcInfo);
                inFunctionBlock = true;
                if (line.find("{") != std::string::npos) braceCount++;
            }
        }
        // Track braces for block scope
        else {
            size_t openBrace = line.find("{");
            size_t closeBrace = line.find("}");
            if (openBrace != std::string::npos) braceCount++;
            if (closeBrace != std::string::npos) {
                braceCount--;
                if (braceCount == 0) inModuleBlock = false;
                else if (braceCount == 1) inFunctionBlock = false;
            }
        }
    }

    return moduleInfo;
}

std::string ModuleLoader::resolveModulePath(const std::string& importPath, const std::string& currentModulePath) {
    namespace fs = std::filesystem;

    // Convert namespace-qualified path (e.g., pryst::web) to filesystem path
    std::string pathName = importPath;
    size_t pos = 0;
    while ((pos = pathName.find("::")) != std::string::npos) {
        pathName.replace(pos, 2, std::string(1, fs::path::preferred_separator));
    }

    // If the import path is absolute, try to load directly
    if (fs::path(pathName).is_absolute()) {
        if (fs::exists(pathName + ".pst")) {
            return fs::absolute(pathName + ".pst").string();
        }
        throw std::runtime_error("Module not found: " + importPath);
    }

    // Get the directory of the current module
    fs::path currentDir = fs::path(currentModulePath).parent_path();

    // First, try relative to current module
    fs::path relativePath = currentDir / pathName;
    // Try direct .pst file
    if (fs::exists(relativePath.string() + ".pst")) {
        return fs::absolute(relativePath.string() + ".pst").string();
    }
    // Try module directory with server.pst
    if (fs::exists(relativePath.string() + "/server.pst")) {
        return fs::absolute(relativePath.string() + "/server.pst").string();
    }

    // Then try search paths
    for (const auto& searchPath : searchPaths) {
        fs::path fullPath = fs::path(searchPath) / pathName;
        // Try direct .pst file
        if (fs::exists(fullPath.string() + ".pst")) {
            return fs::absolute(fullPath.string() + ".pst").string();
        }
        // Try module directory with server.pst
        if (fs::exists(fullPath.string() + "/server.pst")) {
            return fs::absolute(fullPath.string() + "/server.pst").string();
        }
    }

    throw std::runtime_error("Module not found: " + importPath);
}

bool ModuleLoader::isModuleLoaded(const std::string& modulePath) const {
    return loadedModules.find(modulePath) != loadedModules.end();
}

void ModuleLoader::addModuleSearchPath(const std::string& searchPath) {
    if (std::find(searchPaths.begin(), searchPaths.end(), searchPath) == searchPaths.end()) {
        searchPaths.push_back(searchPath);
    }
}

std::string ModuleLoader::pathToQualifiedName(const std::string& path) const {
    namespace fs = std::filesystem;
    fs::path fsPath(path);

    // Remove extension and convert to qualified name
    std::string name = fsPath.stem().string();
    std::string dir = fsPath.parent_path().string();

    // Replace directory separators with ::
    size_t pos = dir.find("src/modules/");
    if (pos != std::string::npos) {
        dir = dir.substr(pos + 11); // Skip "src/modules/"
        std::replace(dir.begin(), dir.end(), '/', ':');
        return dir.empty() ? name : dir + "::" + name;
    }

    return name;
}

std::string ModuleLoader::findModuleFile(const std::string& moduleName) const {
    namespace fs = std::filesystem;
    PRYST_DEBUG("Finding module file for: " + moduleName);

    // Replace double colons with path separators
    std::string pathName = moduleName;
    size_t pos = 0;
    while ((pos = pathName.find("::")) != std::string::npos) {
        pathName.replace(pos, 2, std::string(1, fs::path::preferred_separator));
    }
    PRYST_DEBUG("Converted module path: " + pathName);

    // Try each search path
    for (const auto& searchPath : searchPaths) {
        PRYST_DEBUG("Trying search path: " + searchPath);

        // Try direct .pst file
        fs::path fullPath = fs::path(searchPath) / (pathName + ".pst");
        PRYST_DEBUG("Checking file: " + fullPath.string());
        if (fs::exists(fullPath)) {
            PRYST_DEBUG("Found module file: " + fullPath.string());
            return fs::absolute(fullPath).string();
        }

        // Try module directory with server.pst
        fs::path dirPath = fs::path(searchPath) / pathName;
        fs::path serverPath = dirPath / "server.pst";
        PRYST_DEBUG("Checking server file: " + serverPath.string());
        if (fs::exists(serverPath)) {
            PRYST_DEBUG("Found server module file: " + serverPath.string());
            return fs::absolute(serverPath).string();
        }
    }

    PRYST_DEBUG("Module not found: " + moduleName);
    throw std::runtime_error("Module not found: " + moduleName);
}

bool ModuleLoader::validateModuleStructure(const std::string& modulePath) const {
    namespace fs = std::filesystem;
    PRYST_DEBUG("Validating module structure for: " + modulePath);

    // Check if file exists
    if (!fs::exists(modulePath)) {
        PRYST_DEBUG("Module file does not exist: " + modulePath);
        return false;
    }

    // Check if file is readable
    std::ifstream file(modulePath);
    if (!file.is_open()) {
        PRYST_DEBUG("Cannot open module file: " + modulePath);
        return false;
    }

    std::string line;
    bool hasModuleDeclaration = false;
    bool inModuleBlock = false;
    int braceCount = 0;

    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line.find("//") == 0) continue;

        // Check for module declaration
        if (line.find("module") == 0) {
            if (hasModuleDeclaration) {
                PRYST_DEBUG("Multiple module declarations found in: " + modulePath);
                return false;
            }
            hasModuleDeclaration = true;
            inModuleBlock = true;
            braceCount++;
        }

        // Track braces for block scope
        size_t openBrace = line.find("{");
        size_t closeBrace = line.find("}");
        if (openBrace != std::string::npos) braceCount++;
        if (closeBrace != std::string::npos) {
            braceCount--;
            if (braceCount == 0) inModuleBlock = false;
        }
    }

    // Check if module structure is valid
    bool isValid = hasModuleDeclaration && braceCount == 0;
    PRYST_DEBUG("Module structure validation result for " + modulePath + ": " + (isValid ? "valid" : "invalid"));
    return isValid;
}
