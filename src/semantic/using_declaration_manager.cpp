#include "using_declaration_manager.hpp"
#include "../utils/logger.hpp"
#include <algorithm>

namespace pryst {

void UsingDeclarationManager::addUsingDeclaration(
    const std::string& target,
    int scopeLevel,
    bool isModule,
    const std::string& alias,
    const std::string& sourceFile,
    int sourceLine
) {
    UsingDeclaration decl{
        target,
        alias,
        scopeLevel,
        isModule,
        sourceFile,
        sourceLine
    };
    scopedDeclarations[scopeLevel].push_back(decl);
    PRYST_DEBUG("Added using declaration for " + target + " at scope level " + std::to_string(scopeLevel));
}

void UsingDeclarationManager::removeUsingDeclarationsAtScope(int scopeLevel) {
    scopedDeclarations.erase(scopeLevel);
    PRYST_DEBUG("Removed using declarations at scope level " + std::to_string(scopeLevel));
}

bool UsingDeclarationManager::isSymbolAccessible(const std::string& symbol, int currentScope) const {
    auto declarations = getEffectiveDeclarations(currentScope);
    for (const auto& decl : declarations) {
        std::string qualifiedSymbol = decl.target + "::" + symbol;
        if (isDeclarationActive(decl, currentScope)) {
            return true;
        }
    }
    return false;
}

std::string UsingDeclarationManager::resolveQualifiedName(const std::string& symbol, int currentScope) const {
    auto declarations = getEffectiveDeclarations(currentScope);
    for (const auto& decl : declarations) {
        if (isDeclarationActive(decl, currentScope)) {
            // If symbol starts with alias, replace with target
            if (!decl.alias.empty() && symbol.find(decl.alias) == 0) {
                return decl.target + symbol.substr(decl.alias.length());
            }
            // Otherwise, try to qualify the symbol
            return decl.target + "::" + symbol;
        }
    }
    return symbol;
}

std::vector<UsingDeclaration> UsingDeclarationManager::getActiveDeclarations(int scopeLevel) const {
    return getEffectiveDeclarations(scopeLevel);
}

void UsingDeclarationManager::clear() {
    scopedDeclarations.clear();
    PRYST_DEBUG("Cleared all using declarations");
}

bool UsingDeclarationManager::isDeclarationActive(const UsingDeclaration& decl, int currentScope) const {
    return decl.scopeLevel <= currentScope;
}

std::vector<UsingDeclaration> UsingDeclarationManager::getEffectiveDeclarations(int scopeLevel) const {
    std::vector<UsingDeclaration> effective;
    for (const auto& [level, declarations] : scopedDeclarations) {
        if (level <= scopeLevel) {
            effective.insert(effective.end(), declarations.begin(), declarations.end());
        }
    }
    return effective;
}

} // namespace pryst
