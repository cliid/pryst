#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "types.hpp"

namespace pryst {

// Represents a using declaration's scope and target
struct UsingDeclaration {
    std::string target;        // What is being imported (module or namespace)
    std::string alias;         // Optional alias for the import
    int scopeLevel;           // Block scope level
    bool isModule;            // true if module import, false if namespace
    std::string sourceFile;   // Source file where declaration appears
    int sourceLine;           // Line number in source file
};

class UsingDeclarationManager {
public:
    UsingDeclarationManager() = default;
    ~UsingDeclarationManager() = default;

    // Add a using declaration at the current scope
    void addUsingDeclaration(const std::string& target,
                           int scopeLevel,
                           bool isModule = true,
                           const std::string& alias = "",
                           const std::string& sourceFile = "",
                           int sourceLine = 0);

    // Remove using declarations at a specific scope level when exiting the block
    void removeUsingDeclarationsAtScope(int scopeLevel);

    // Check if a symbol is accessible through any active using declaration
    bool isSymbolAccessible(const std::string& symbol, int currentScope) const;

    // Get the fully qualified name for a symbol based on active using declarations
    std::string resolveQualifiedName(const std::string& symbol, int currentScope) const;

    // Get all active using declarations at a specific scope level
    std::vector<UsingDeclaration> getActiveDeclarations(int scopeLevel) const;

    // Clear all using declarations (useful for testing and cleanup)
    void clear();

private:
    // Map of scope levels to their using declarations
    std::unordered_map<int, std::vector<UsingDeclaration>> scopedDeclarations;

    // Helper to check if a declaration is active at a given scope
    bool isDeclarationActive(const UsingDeclaration& decl, int currentScope) const;

    // Helper to get all declarations that could affect a given scope
    std::vector<UsingDeclaration> getEffectiveDeclarations(int scopeLevel) const;
};

} // namespace pryst
