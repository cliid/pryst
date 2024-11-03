#include "module_loader.hpp"
#include <filesystem>
#include <stdexcept>
#include <algorithm>

ModuleLoader::ModuleLoader() {
    // Add current directory to search paths by default
    searchPaths.push_back(".");
}

bool ModuleLoader::loadModule(const std::string& modulePath) {
    if (isModuleLoaded(modulePath)) {
        return true;  // Already loaded
    }

    // Mark as loaded to prevent circular imports
    loadedModules[modulePath] = true;
    return true;
}

std::string ModuleLoader::resolveModulePath(const std::string& importPath, const std::string& currentModulePath) {
    namespace fs = std::filesystem;

    // If the import path is absolute, try to load directly
    if (fs::path(importPath).is_absolute()) {
        if (fs::exists(importPath)) {
            return fs::absolute(importPath).string();
        }
        throw std::runtime_error("Module not found: " + importPath);
    }

    // Get the directory of the current module
    fs::path currentDir = fs::path(currentModulePath).parent_path();

    // First, try relative to current module
    fs::path relativePath = currentDir / importPath;
    if (fs::exists(relativePath.string() + ".pst")) {
        return fs::absolute(relativePath.string() + ".pst").string();
    }

    // Then try search paths
    for (const auto& searchPath : searchPaths) {
        fs::path fullPath = fs::path(searchPath) / importPath;
        if (fs::exists(fullPath.string() + ".pst")) {
            return fs::absolute(fullPath.string() + ".pst").string();
        }
    }

    throw std::runtime_error("Module not found: " + importPath);
}

bool ModuleLoader::isModuleLoaded(const std::string& modulePath) const {
    return loadedModules.find(modulePath) != loadedModules.end();
}

std::string ModuleLoader::getModuleQualifiedName(const std::string& modulePath) const {
    return pathToQualifiedName(modulePath);
}

void ModuleLoader::addModuleSearchPath(const std::string& searchPath) {
    if (std::find(searchPaths.begin(), searchPaths.end(), searchPath) == searchPaths.end()) {
        searchPaths.push_back(searchPath);
    }
}

std::string ModuleLoader::pathToQualifiedName(const std::string& path) const {
    namespace fs = std::filesystem;

    // Remove extension and convert path separators to dots
    fs::path p(path);
    std::string name = p.stem().string();
    std::replace(name.begin(), name.end(), '/', '.');
    std::replace(name.begin(), name.end(), '\\', '.');

    return name;
}

std::string ModuleLoader::findModuleFile(const std::string& moduleName) const {
    namespace fs = std::filesystem;

    // Replace dots with path separators
    std::string pathName = moduleName;
    std::replace(pathName.begin(), pathName.end(), '.', fs::path::preferred_separator);

    // Try each search path
    for (const auto& searchPath : searchPaths) {
        fs::path fullPath = fs::path(searchPath) / (pathName + ".pst");
        if (fs::exists(fullPath)) {
            return fs::absolute(fullPath).string();
        }
    }

    throw std::runtime_error("Module not found: " + moduleName);
}
