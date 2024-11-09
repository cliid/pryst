#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "semantic/symbol_table.hpp"

namespace pryst {
namespace semantic {

class ModuleLoader {
public:
    ModuleLoader(SymbolTable& symbolTable);

    // TypeScript-style module loading
    bool loadModule(const std::string& modulePath);
    bool importModule(const std::string& qualifiedName);

    // Block-level using declarations
    void addUsingDeclaration(const std::string& moduleName, bool isModule);
    void enterScope();
    void exitScope();

    // Interface compliance
    bool verifyInterfaceCompliance(const std::string& implementation,
                                 const std::string& interface);

    // Namespace resolution
    std::string resolveQualifiedName(const std::string& name);
    bool isNameVisible(const std::string& name);

private:
    SymbolTable& symbolTable;
    std::vector<std::unordered_map<std::string, bool>> scopeStack;
    std::unordered_map<std::string, std::string> moduleCache;

    std::string resolveModulePath(const std::string& qualifiedName);
    bool checkCircularDependency(const std::string& moduleName);
};

} // namespace semantic
} // namespace pryst
