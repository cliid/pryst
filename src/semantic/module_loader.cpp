#include "semantic/module_loader.hpp"
#include <stdexcept>
#include <filesystem>

namespace pryst {
namespace semantic {

ModuleLoader::ModuleLoader(SymbolTable& symbolTable) : symbolTable(symbolTable) {
    scopeStack.push_back({});
}

bool ModuleLoader::loadModule(const std::string& modulePath) {
    if (moduleCache.find(modulePath) != moduleCache.end()) {
        return true;
    }
    moduleCache[modulePath] = modulePath;
    return true;
}

bool ModuleLoader::importModule(const std::string& qualifiedName) {
    return loadModule(resolveModulePath(qualifiedName));
}

void ModuleLoader::addUsingDeclaration(const std::string& moduleName, bool isModule) {
    if (!scopeStack.empty()) {
        scopeStack.back()[moduleName] = isModule;
    }
}

void ModuleLoader::enterScope() {
    scopeStack.push_back({});
}

void ModuleLoader::exitScope() {
    if (scopeStack.size() > 1) {
        scopeStack.pop_back();
    }
}

std::string ModuleLoader::resolveModulePath(const std::string& qualifiedName) {
    std::string path = qualifiedName;
    std::replace(path.begin(), path.end(), ':', '/');
    return "modules/" + path + ".pst";
}

} // namespace semantic
} // namespace pryst
