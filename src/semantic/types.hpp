#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Forward declarations
class SymbolTable;
class ModuleLoader;
struct FunctionInfo;  // Forward declare FunctionInfo before VariableInfo

// Basic type information structures
struct VariableInfo {
    std::string type;
    bool isConst;
    int scopeLevel;
    bool isFunctionType;
    bool isCaptured;  // Track if variable is captured by a closure
    std::shared_ptr<FunctionInfo> functionInfo;  // Store function info for function variables

    VariableInfo() : isConst(false), scopeLevel(0), isFunctionType(false), isCaptured(false), functionInfo(nullptr) {}
    VariableInfo(const std::string& type, bool isConst, int scopeLevel)
        : type(type), isConst(isConst), scopeLevel(scopeLevel), isFunctionType(false), isCaptured(false), functionInfo(nullptr) {}
    VariableInfo(const std::string& type, bool isConst, int scopeLevel, std::shared_ptr<FunctionInfo> funcInfo)
        : type(type), isConst(isConst), scopeLevel(scopeLevel), isFunctionType(true), isCaptured(false), functionInfo(funcInfo) {}
};

struct FunctionInfo {
    std::string returnType;
    std::vector<std::string> paramTypes;
    int scopeLevel;
    bool isAnonymous;
    bool hasExplicitReturnType;
    std::vector<std::string> deducedReturnTypes;
    bool isForwardDeclaration;  // Track if this is just a declaration
    bool isImplemented;         // Track if implementation is provided
    std::vector<std::string> referencedFunctions;  // Track functions called within this function
    std::string declarationLocation;  // Track where the function was declared (file:line)

    // Default constructor
    FunctionInfo() : isForwardDeclaration(false), isImplemented(false) {}

    // Constructor with parameters
    FunctionInfo(
        const std::string& returnType,
        const std::vector<std::string>& paramTypes,
        int scopeLevel,
        bool isAnonymous = false,
        bool hasExplicitReturnType = false,
        const std::vector<std::string>& deducedReturnTypes = {},
        bool isForwardDecl = false,
        const std::string& declLocation = ""
    ) : returnType(returnType),
        paramTypes(paramTypes),
        scopeLevel(scopeLevel),
        isAnonymous(isAnonymous),
        hasExplicitReturnType(hasExplicitReturnType),
        deducedReturnTypes(deducedReturnTypes),
        isForwardDeclaration(isForwardDecl),
        isImplemented(!isForwardDecl),
        declarationLocation(declLocation) {}
};

struct ClassInfo {
    std::string superClassName;
    std::unordered_map<std::string, VariableInfo> members;
    std::unordered_map<std::string, std::vector<std::shared_ptr<FunctionInfo>>> methods;
};

// Forward declare ModuleInfo and NamespaceInfo before use
struct ModuleInfo;
struct NamespaceInfo;

// Define ModuleInfo after forward declaration
struct ModuleInfo {
    std::string qualifiedName;
    std::unordered_map<std::string, VariableInfo> exports;
    std::unordered_map<std::string, std::vector<std::shared_ptr<FunctionInfo>>> functions;
    std::unordered_map<std::string, std::vector<std::shared_ptr<FunctionInfo>>> exportedFunctions;
    std::unordered_map<std::string, ClassInfo> exportedClasses;
    std::unordered_map<std::string, std::shared_ptr<ModuleInfo>> modules;
    std::unordered_map<std::string, std::shared_ptr<NamespaceInfo>> namespaces;
    std::shared_ptr<NamespaceInfo> parentNamespace;

    ModuleInfo() = default;
    ModuleInfo(const std::string& name) : qualifiedName(name) {}
};

// Define NamespaceInfo after ModuleInfo is complete
struct NamespaceInfo {
    std::string qualifiedName;
    std::unordered_map<std::string, VariableInfo> variables;
    std::unordered_map<std::string, std::vector<std::shared_ptr<FunctionInfo>>> functions;
    std::unordered_map<std::string, ClassInfo> classes;
    std::unordered_map<std::string, std::shared_ptr<ModuleInfo>> modules;
    std::unordered_map<std::string, std::shared_ptr<NamespaceInfo>> subNamespaces;
};

// Using declaration types
enum class UsingKind {
    MODULE,
    NAMESPACE
};

struct UsingDeclaration {
    UsingKind kind;
    std::string qualifiedName;
    bool isBlockLevel;  // true if declared within a block scope

    UsingDeclaration(UsingKind k, const std::string& name, bool block = false)
        : kind(k), qualifiedName(name), isBlockLevel(block) {}
};

struct Scope {
    std::shared_ptr<Scope> parent;
    std::vector<std::shared_ptr<Scope>> children;
    std::unordered_map<std::string, VariableInfo> variables;
    std::unordered_map<std::string, std::vector<std::shared_ptr<FunctionInfo>>> functions;
    std::unordered_map<std::string, ClassInfo> classes;
    std::unordered_map<std::string, std::shared_ptr<ModuleInfo>> modules;
    std::unordered_map<std::string, std::shared_ptr<NamespaceInfo>> namespaces;
    std::unordered_map<std::string, std::string> moduleAliases;
    std::unordered_map<std::string, VariableInfo> capturedVariables;
    std::vector<UsingDeclaration> usingDeclarations;  // Track using declarations in this scope
    bool isGlobalScope;
    bool isFrozen;
    bool isAnonymousFunction;  // Added to track anonymous function scopes

    Scope() : isGlobalScope(false), isFrozen(false), isAnonymousFunction(false) {}
};
