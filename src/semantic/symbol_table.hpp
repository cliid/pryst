#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "types.hpp"

class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable();
    void pushScope();
    void popScope();
    void enterScope() { pushScope(); }
    void exitScope() { popScope(); }
    size_t getCurrentScopeLevel() const;

    // Function-related methods
    void addFunction(const std::string& name, std::shared_ptr<FunctionInfo> funcInfo);
    void addFunction(const std::string& name, const std::string& returnType, const std::vector<std::string>& paramTypes);
    void addForwardDeclaration(const std::string& name, const std::string& returnType, const std::vector<std::string>& paramTypes, const std::string& location);
    void implementFunction(const std::string& name, const std::vector<std::string>& paramTypes);
    void addFunctionReference(const std::string& caller, const std::string& callee);
    bool validateFunctionReferences(const std::string& name, std::string& error) const;
    bool functionExists(const std::string& name) const;
    bool isForwardDeclared(const std::string& name) const;
    bool isImplemented(const std::string& name) const;
    std::vector<std::shared_ptr<FunctionInfo>> getAllFunctionOverloads(const std::string& name) const;
    std::shared_ptr<FunctionInfo> getFunctionInfo(const std::string& name) const;
    bool findMatchingFunction(const std::string& name, const std::vector<std::string>& argTypes, std::shared_ptr<FunctionInfo>& outInfo) const;
    std::shared_ptr<FunctionInfo> lookupFunction(const std::string& qualifiedName) const;

    // Variable-related methods
    void addVariable(const std::string& name, const std::string& type, bool isConst = false);
    bool variableExists(const std::string& name) const;
    bool variableExistsInCurrentScope(const std::string& name) const;
    std::string getVariableType(const std::string& name) const;
    std::unordered_map<std::string, VariableInfo> getCurrentScopeVariables() const;
    std::unordered_map<std::string, ClassInfo> getCurrentScopeClasses() const;
    void clearCurrentScopeVariables();

    // Variable capture and scope freezing methods
    void captureVariable(const std::string& name);
    void freezeScope();
    bool isVariableCaptured(const std::string& name) const;
    VariableInfo getCapturedVariable(const std::string& name) const;
    bool isScopeFrozen() const;
    void validateVariableAccess(const std::string& name) const;
    void markVariableCaptured(const std::string& name);
    VariableInfo getCapturedVariableInfo(const std::string& name) const;

    // Anonymous function and closure methods
    void beginAnonymousFunction();
    void endAnonymousFunction();

    // Function scope methods
    std::unordered_map<std::string, std::vector<std::shared_ptr<FunctionInfo>>> getCurrentScopeFunctions() const;
    void clearCurrentScopeFunctions();

    // Namespace-related methods
    void addNamespace(const std::string& name);
    void addNamespaceAlias(const std::string& alias, const std::string& qualifiedName);
    void importNamespace(const std::string& qualifiedName);
    void importAllFromNamespace(const std::string& qualifiedName);
    bool namespaceExists(const std::string& name) const;
    void importNamespaceSymbols(const NamespaceInfo& ns, std::shared_ptr<Scope>& targetScope);
    std::shared_ptr<NamespaceInfo> getNamespaceInfo(const std::string& name) const;
    std::string resolveNamespaceName(const std::string& name) const;
    std::unordered_map<std::string, std::shared_ptr<NamespaceInfo>> getCurrentScopeNamespaces() const;

    // Using declaration methods
    void addUsingDeclaration(UsingKind kind, const std::string& qualifiedName, bool isBlockLevel = false);
    void removeBlockLevelUsingDeclarations();
    bool hasUsingDeclaration(const std::string& qualifiedName, UsingKind kind) const;

    // Class-related methods
    void addClass(const std::string& name, const std::vector<std::string>& baseClasses = std::vector<std::string>());
    void addClass(const std::string& name, const ClassInfo& info);
    bool classExists(const std::string& name) const;
    bool isClassDefined(const std::string& name) const { return classExists(name); }
    bool isSubclassOf(const std::string& derived, const std::string& base) const;
    bool isMethodDefined(const std::string& className, const std::string& methodName) const;
    std::string getMethodReturnType(const std::string& className, const std::string& methodName,
                                  const std::vector<std::string>& argTypes) const;
    bool isClassDefinedInNamespace(const std::string& className, const std::string& namespaceName) const;
    ClassInfo getClassInfo(const std::string& name) const;

    // Module-related methods
    void addModule(const std::string& name, const ModuleInfo& info);
    void addModuleAlias(const std::string& alias, const std::string& qualifiedName);
    void importModule(const std::string& qualifiedName);
    void importAllFromModule(const std::string& qualifiedName);
    bool moduleExists(const std::string& name) const;
    ModuleInfo getModuleInfo(const std::string& name) const;
    std::string resolveModuleName(const std::string& name) const;
    std::vector<std::string> getCurrentScopeModules() const;

    // Module path and namespace tracking
    std::string getCurrentModule() const;
    void setCurrentModule(const std::string& moduleName);
    std::string getCurrentNamespacePath() const;
    void setCurrentNamespacePath(const std::string& namespacePath);
    void addImport(const std::string& qualifiedName);

private:
    void importNamespaceSymbols(const NamespaceInfo& ns, Scope& targetScope);
    void importModuleSymbols(const ModuleInfo& mod, const std::string& prefix, Scope& targetScope);
    void importAllFromNamespaceImpl(const std::string& qualifiedName, Scope& targetScope);
    void importAllFromModuleImpl(const std::string& qualifiedName, Scope& targetScope);
    bool resolveQualifiedName(const std::string& qualifiedName, std::shared_ptr<NamespaceInfo>& outNs) const;
    bool resolveFromNamespace(const std::shared_ptr<NamespaceInfo>& baseNs,
                            const std::vector<std::string>& parts,
                            std::shared_ptr<NamespaceInfo>& outNs) const;

    std::vector<std::shared_ptr<Scope>> scopes;
    std::string currentModule;
    std::string currentNamespacePath;
    std::vector<std::string> imports;
    bool areTypesCompatible(const std::string& expected, const std::string& actual) const;
    bool isFunctionType(const std::string& type) const;
    std::pair<std::string, std::vector<std::string>> parseFunctionType(const std::string& type) const;
    std::string createFunctionTypeString(const std::string& returnType, const std::vector<std::string>& paramTypes) const;
};
