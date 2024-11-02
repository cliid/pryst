#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>

class SymbolTable {
public:
    struct FunctionInfo {
        std::string returnType;
        std::vector<std::string> paramTypes;
        int scopeLevel;
        bool isAnonymous;
        bool hasExplicitReturnType;
        std::vector<std::string> deducedReturnTypes;  // For type deduction
    };

    struct VariableInfo {
        std::string type;
        bool isConst;
        int scopeLevel;
        bool isFunctionType;  // True if this is a function type variable
        FunctionInfo functionInfo;  // Used when isFunctionType is true
    };

    struct ClassInfo {
        std::string superClassName;
        std::unordered_map<std::string, VariableInfo> members;
        std::unordered_map<std::string, FunctionInfo> methods;
    };

    struct ModuleInfo {
        std::string qualifiedName;
        std::unordered_map<std::string, VariableInfo> exports;
        std::unordered_map<std::string, FunctionInfo> exportedFunctions;
        std::unordered_map<std::string, ClassInfo> exportedClasses;
    };

    SymbolTable();
    void pushScope();
    void popScope();
    size_t getCurrentScopeLevel() const;

    // Function-related methods
    void addFunction(const std::string& name, const std::string& returnType, const std::vector<std::string>& paramTypes);
    bool functionExists(const std::string& name) const;
    std::vector<FunctionInfo> getAllFunctionOverloads(const std::string& name) const;
    FunctionInfo getFunctionInfo(const std::string& name) const;
    bool findMatchingFunction(const std::string& name, const std::vector<std::string>& argTypes, FunctionInfo& outInfo) const;

    // Variable-related methods
    void addVariable(const std::string& name, const std::string& type, bool isConst = false);
    bool variableExists(const std::string& name) const;
    bool variableExistsInCurrentScope(const std::string& name) const;
    std::string getVariableType(const std::string& name) const;
    std::unordered_map<std::string, VariableInfo> getCurrentScopeVariables() const;
    void clearCurrentScopeVariables();

    // Function scope methods
    std::unordered_map<std::string, FunctionInfo> getCurrentScopeFunctions() const;
    void clearCurrentScopeFunctions();

    // Class-related methods
    void addClass(const std::string& name, const std::string& parentClass = "");
    bool classExists(const std::string& name) const;
    ClassInfo getClassInfo(const std::string& name) const;

    // Module-related methods
    void addModule(const std::string& name, const ModuleInfo& info);
    void addModuleAlias(const std::string& alias, const std::string& qualifiedName);
    void importModule(const std::string& qualifiedName);
    void importAllFromModule(const std::string& qualifiedName);
    bool moduleExists(const std::string& name) const;
    ModuleInfo getModuleInfo(const std::string& name) const;
    std::string resolveModuleName(const std::string& name) const;

private:
    struct Scope {
        std::map<std::string, std::vector<FunctionInfo>> functions;
        std::map<std::string, VariableInfo> variables;
        std::map<std::string, ClassInfo> classes;
        std::map<std::string, ModuleInfo> modules;
        std::map<std::string, std::string> moduleAliases;  // alias -> qualified name
    };

    std::vector<Scope> scopes;
    bool areTypesCompatible(const std::string& expected, const std::string& actual) const;
    bool isFunctionType(const std::string& type) const;
    std::pair<std::string, std::vector<std::string>> parseFunctionType(const std::string& type) const;
    std::string createFunctionTypeString(const std::string& returnType, const std::vector<std::string>& paramTypes) const;
};
