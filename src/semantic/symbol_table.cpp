#include "symbol_table.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <regex>
#include "logger.hpp"
#include "../utils/debug.hpp"

// Constructor and destructor
SymbolTable::SymbolTable() {
    PRYST_DEBUG("Initializing SymbolTable");
    pushScope();  // Initialize with global scope
    scopes.back()->isGlobalScope = true;
}

SymbolTable::~SymbolTable() {
    while (!scopes.empty()) {
        popScope();
    }
}

// Core scope management
void SymbolTable::pushScope() {
    PRYST_DEBUG("Pushing new scope");
    auto newScope = std::make_shared<Scope>();
    newScope->isGlobalScope = scopes.empty();
    newScope->isFrozen = false;

    if (!scopes.empty()) {
        newScope->parent = scopes.back();
        scopes.back()->children.push_back(newScope);
        PRYST_DEBUG("Set parent scope: " + std::to_string(reinterpret_cast<uintptr_t>(scopes.back().get())));
        PRYST_DEBUG("Added to parent's children list, new child count: " + std::to_string(scopes.back()->children.size()));
    }

    scopes.push_back(newScope);
    PRYST_DEBUG("Pushed scope, new level: " + std::to_string(getCurrentScopeLevel()));
}

void SymbolTable::popScope() {
    if (scopes.empty()) {
        throw std::runtime_error("No scope to pop");
    }

    auto currentScope = scopes.back();
    PRYST_DEBUG("Popping scope at level " + std::to_string(getCurrentScopeLevel()) +
                ", scope address: " + std::to_string(reinterpret_cast<uintptr_t>(currentScope.get())));

    // Clean up block-level using declarations
    removeBlockLevelUsingDeclarations();

    // Clean up captured variables
    for (const auto& [name, varInfo] : currentScope->variables) {
        if (varInfo.isCaptured) {
            auto parentScope = currentScope->parent;
            PRYST_DEBUG("Cleaning up captured variable: " + name);
            while (parentScope) {
                auto it = parentScope->variables.find(name);
                if (it != parentScope->variables.end()) {
                    it->second.isCaptured = false;
                    size_t parentLevel = 0;
                    auto temp = parentScope;
                    while (temp->parent) {
                        parentLevel++;
                        temp = temp->parent;
                    }
                    PRYST_DEBUG("Uncaptured variable " + name + " in parent scope at level " +
                               std::to_string(parentLevel));
                }
                parentScope = parentScope->parent;
            }
        }
    }

    // Remove from parent's children list
    if (currentScope->parent) {
        PRYST_DEBUG("Removing scope from parent's children list, parent address: " +
                    std::to_string(reinterpret_cast<uintptr_t>(currentScope->parent.get())));
        auto& siblings = currentScope->parent->children;
        siblings.erase(std::remove(siblings.begin(), siblings.end(), currentScope), siblings.end());
    }

    // Clear relationships
    PRYST_DEBUG("Clearing scope relationships");
    currentScope->parent.reset();
    currentScope->children.clear();
    scopes.pop_back();

    PRYST_DEBUG("Popped scope, new level: " + std::to_string(getCurrentScopeLevel()));
}

size_t SymbolTable::getCurrentScopeLevel() const {
    return scopes.size() - 1;
}

// Variable management
void SymbolTable::addVariable(const std::string& name, const std::string& type, bool isConst) {
    PRYST_DEBUG("Adding variable '" + name + "' of type '" + type + "' to scope " + std::to_string(getCurrentScopeLevel()));
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    if (variableExistsInCurrentScope(name)) {
        throw std::runtime_error("Variable already declared in current scope: " + name);
    }

    VariableInfo info;
    info.type = type;
    info.isConst = isConst;
    info.scopeLevel = static_cast<int>(getCurrentScopeLevel());
    info.isCaptured = false;

    // Check if this is a function type (either fn<...> or lambda)
    info.isFunctionType = isFunctionType(type);
    PRYST_DEBUG("Checking if type '" + type + "' is a function type: " + (info.isFunctionType ? "true" : "false"));

    if (info.isFunctionType) {
        try {
            PRYST_DEBUG("Parsing function type: " + type);
            auto [returnType, paramTypes] = parseFunctionType(type);
            PRYST_DEBUG("Parsed return type: " + returnType);
            PRYST_DEBUG("Parsed param types count: " + std::to_string(paramTypes.size()));

            info.functionInfo = std::make_shared<FunctionInfo>();
            info.functionInfo->returnType = returnType;
            info.functionInfo->paramTypes = paramTypes;
            info.functionInfo->scopeLevel = static_cast<int>(getCurrentScopeLevel());
            info.functionInfo->isAnonymous = false;
            info.functionInfo->hasExplicitReturnType = true;

            PRYST_DEBUG("Successfully created function info for variable: " + name);
        } catch (const std::exception& e) {
            PRYST_DEBUG("Error parsing function type: " + std::string(e.what()));
            throw std::runtime_error("Invalid function type format: " + type + " (" + e.what() + ")");
        }
    }

    scopes.back()->variables[name] = info;
}

bool SymbolTable::variableExists(const std::string& name) const {
    if (scopes.empty()) return false;
    auto scope = scopes.back();
    while (scope) {
        if (scope->variables.find(name) != scope->variables.end()) {
            return true;
        }
        scope = scope->parent;
    }
    return false;
}

bool SymbolTable::variableExistsInCurrentScope(const std::string& name) const {
    if (scopes.empty()) return false;
    return scopes.back()->variables.find(name) != scopes.back()->variables.end();
}

std::string SymbolTable::getVariableType(const std::string& name) const {
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto scope = scopes.back();
    while (scope) {
        auto it = scope->variables.find(name);
        if (it != scope->variables.end()) {
            return it->second.type;
        }
        scope = scope->parent;
    }
    throw std::runtime_error("Undefined variable: " + name);
}

std::unordered_map<std::string, VariableInfo> SymbolTable::getCurrentScopeVariables() const {
    if (scopes.empty()) return {};
    return scopes.back()->variables;
}


void SymbolTable::clearCurrentScopeVariables() {
    if (!scopes.empty()) {
        scopes.back()->variables.clear();
        PRYST_DEBUG("Cleared variables in current scope");
    }
}

// Variable capture and scope freezing
void SymbolTable::captureVariable(const std::string& name) {
    PRYST_DEBUG("Capturing variable: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    auto scope = scopes.back();
    bool found = false;

    // Look for the variable in parent scopes
    while (scope->parent) {
        scope = scope->parent;
        auto it = scope->variables.find(name);
        if (it != scope->variables.end()) {
            it->second.isCaptured = true;
            found = true;
            // Copy to current scope's captured variables
            scopes.back()->capturedVariables[name] = it->second;
            break;
        }
    }

    if (!found) {
        throw std::runtime_error("Cannot capture undefined variable: " + name);
    }
}

void SymbolTable::freezeScope() {
    PRYST_DEBUG("Freezing current scope");
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    scopes.back()->isFrozen = true;
}

bool SymbolTable::isVariableCaptured(const std::string& name) const {
    if (scopes.empty()) return false;
    auto scope = scopes.back();
    while (scope) {
        auto it = scope->variables.find(name);
        if (it != scope->variables.end()) {
            return it->second.isCaptured;
        }
        scope = scope->parent;
    }
    return false;
}

VariableInfo SymbolTable::getCapturedVariable(const std::string& name) const {
    PRYST_DEBUG("Getting captured variable: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto scope = scopes.back();
    auto it = scope->capturedVariables.find(name);
    if (it != scope->capturedVariables.end()) {
        return it->second;
    }
    throw std::runtime_error("Captured variable not found: " + name);
}

bool SymbolTable::isScopeFrozen() const {
    PRYST_DEBUG("Checking if current scope is frozen");
    if (scopes.empty()) return false;
    return scopes.back()->isFrozen;
}

void SymbolTable::validateVariableAccess(const std::string& name) const {
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    auto currentScope = scopes.back();
    if (!currentScope->isFrozen) {
        return;  // Access allowed in unfrozen scope
    }

    // Check if the variable is captured in the current scope
    if (currentScope->capturedVariables.find(name) != currentScope->capturedVariables.end()) {
        return;  // Access allowed for captured variables
    }

    // Check if the variable is declared in the current scope
    if (currentScope->variables.find(name) != currentScope->variables.end()) {
        return;  // Access allowed for variables in current scope
    }

    throw std::runtime_error("Cannot access non-captured variable '" + name + "' in frozen scope");
}

// Function-related methods
void SymbolTable::addFunction(const std::string& name, std::shared_ptr<FunctionInfo> funcInfo) {
    PRYST_DEBUG("Adding function: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    // Check if this is implementing a forward declaration
    auto existingOverloads = getAllFunctionOverloads(name);
    for (auto& existing : existingOverloads) {
        if (existing->isForwardDeclaration &&
            existing->returnType == funcInfo->returnType &&
            existing->paramTypes == funcInfo->paramTypes) {
            existing->isForwardDeclaration = false;
            existing->isImplemented = true;
            return;
        }
    }

    scopes.back()->functions[name].push_back(funcInfo);
}

void SymbolTable::addFunction(const std::string& name, const std::string& returnType, const std::vector<std::string>& paramTypes) {
    auto funcInfo = std::make_shared<FunctionInfo>();
    funcInfo->returnType = returnType;
    funcInfo->paramTypes = paramTypes;
    funcInfo->scopeLevel = static_cast<int>(getCurrentScopeLevel());
    funcInfo->isAnonymous = false;
    funcInfo->hasExplicitReturnType = true;
    funcInfo->isForwardDeclaration = false;
    funcInfo->isImplemented = true;
    addFunction(name, funcInfo);
}

bool SymbolTable::functionExists(const std::string& name) const {
    PRYST_DEBUG("Checking if function exists: " + name);
    if (scopes.empty()) return false;

    // Check if it's a qualified name (contains ::)
    size_t pos = name.find("::");
    if (pos != std::string::npos) {
        std::string prefix = name.substr(0, pos);
        std::string funcName = name.substr(pos + 2);

        // Try to find in modules
        if (moduleExists(prefix)) {
            auto moduleInfo = getModuleInfo(prefix);
            // Check both regular and exported functions
            return moduleInfo.functions.find(funcName) != moduleInfo.functions.end() ||
                   moduleInfo.exportedFunctions.find(funcName) != moduleInfo.exportedFunctions.end();
        }

        // Try to find in namespaces
        if (namespaceExists(prefix)) {
            auto nsInfo = getNamespaceInfo(prefix);
            return nsInfo->functions.find(funcName) != nsInfo->functions.end();
        }

        return false;
    }

    // Regular function lookup
    auto scope = scopes.back();
    while (scope) {
        if (scope->functions.find(name) != scope->functions.end() &&
            !scope->functions.at(name).empty()) {
            return true;
        }
        scope = scope->parent;
    }
    return false;
}

std::vector<std::shared_ptr<FunctionInfo>> SymbolTable::getAllFunctionOverloads(const std::string& name) const {
    PRYST_DEBUG("Getting all function overloads for: " + name);
    if (scopes.empty()) return {};

    // Check if it's a qualified name (contains ::)
    size_t pos = name.find("::");
    if (pos != std::string::npos) {
        std::string prefix = name.substr(0, pos);
        std::string funcName = name.substr(pos + 2);

        // Try to find in modules
        if (moduleExists(prefix)) {
            auto moduleInfo = getModuleInfo(prefix);
            // Check exported functions first
            auto exportedIt = moduleInfo.exportedFunctions.find(funcName);
            if (exportedIt != moduleInfo.exportedFunctions.end()) {
                return exportedIt->second;
            }
            // Then check regular functions
            auto regularIt = moduleInfo.functions.find(funcName);
            if (regularIt != moduleInfo.functions.end()) {
                return regularIt->second;
            }
        }

        // Try to find in namespaces
        if (namespaceExists(prefix)) {
            auto nsInfo = getNamespaceInfo(prefix);
            auto it = nsInfo->functions.find(funcName);
            if (it != nsInfo->functions.end()) {
                return it->second;
            }
        }

        return {};
    }

    // Regular function lookup
    auto scope = scopes.back();
    while (scope) {
        auto it = scope->functions.find(name);
        if (it != scope->functions.end()) {
            return it->second;
        }
        scope = scope->parent;
    }
    return {};
}

std::shared_ptr<FunctionInfo> SymbolTable::getFunctionInfo(const std::string& name) const {
    auto overloads = getAllFunctionOverloads(name);
    if (overloads.empty()) {
        throw std::runtime_error("Function not found: " + name);
    }
    return overloads.front();
}

bool SymbolTable::findMatchingFunction(const std::string& name, const std::vector<std::string>& argTypes, std::shared_ptr<FunctionInfo>& outInfo) const {
    PRYST_DEBUG("Finding matching function '" + name + "' with " + std::to_string(argTypes.size()) + " arguments");
    auto overloads = getAllFunctionOverloads(name);
    for (const auto& func : overloads) {
        if (func->paramTypes.size() == argTypes.size()) {
            bool match = true;
            for (size_t i = 0; i < argTypes.size(); ++i) {
                if (!areTypesCompatible(func->paramTypes[i], argTypes[i])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                outInfo = func;
                return true;
            }
        }
    }
    return false;
}

std::unordered_map<std::string, std::vector<std::shared_ptr<FunctionInfo>>> SymbolTable::getCurrentScopeFunctions() const {
    if (scopes.empty()) return {};
    return scopes.back()->functions;
}

void SymbolTable::clearCurrentScopeFunctions() {
    if (!scopes.empty()) {
        scopes.back()->functions.clear();
        PRYST_DEBUG("Cleared functions in current scope");
    }
}

// Forward declaration and function reference methods
void SymbolTable::addForwardDeclaration(const std::string& name, const std::string& returnType,
                                      const std::vector<std::string>& paramTypes, const std::string& location) {
    PRYST_DEBUG("Adding forward declaration for function: " + name);
    auto funcInfo = std::make_shared<FunctionInfo>();
    funcInfo->returnType = returnType;
    funcInfo->paramTypes = paramTypes;
    funcInfo->scopeLevel = static_cast<int>(getCurrentScopeLevel());
    funcInfo->isAnonymous = false;
    funcInfo->hasExplicitReturnType = true;
    funcInfo->isForwardDeclaration = true;
    funcInfo->isImplemented = false;
    funcInfo->declarationLocation = location;
    addFunction(name, funcInfo);
}

void SymbolTable::implementFunction(const std::string& name, const std::vector<std::string>& paramTypes) {
    PRYST_DEBUG("Implementing previously declared function: " + name);
    auto overloads = getAllFunctionOverloads(name);
    for (auto& func : overloads) {
        if (func->isForwardDeclaration && func->paramTypes == paramTypes) {
            func->isForwardDeclaration = false;
            func->isImplemented = true;
            return;
        }
    }
    throw std::runtime_error("No matching forward declaration found for function: " + name);
}

void SymbolTable::addFunctionReference(const std::string& caller, const std::string& callee) {
    PRYST_DEBUG("Adding function reference: " + caller + " -> " + callee);
    auto callerOverloads = getAllFunctionOverloads(caller);
    if (callerOverloads.empty()) {
        throw std::runtime_error("Caller function not found: " + caller);
    }

    // Add reference to the most recently added overload
    auto& callerInfo = callerOverloads.back();
    callerInfo->referencedFunctions.push_back(callee);
}

bool SymbolTable::validateFunctionReferences(const std::string& name, std::string& error) const {
    PRYST_DEBUG("Validating function references for: " + name);
    auto overloads = getAllFunctionOverloads(name);
    if (overloads.empty()) {
        error = "Function not found: " + name;
        return false;
    }

    for (const auto& func : overloads) {
        for (const auto& ref : func->referencedFunctions) {
            auto refOverloads = getAllFunctionOverloads(ref);
            if (refOverloads.empty()) {
                error = "Referenced function not found: " + ref;
                return false;
            }

            bool hasImplementation = false;
            for (const auto& refFunc : refOverloads) {
                if (refFunc->isImplemented) {
                    hasImplementation = true;
                    break;
                }
            }

            if (!hasImplementation) {
                error = "Referenced function has no implementation: " + ref;
                return false;
            }
        }
    }
    return true;
}

bool SymbolTable::isForwardDeclared(const std::string& name) const {
    auto overloads = getAllFunctionOverloads(name);
    for (const auto& func : overloads) {
        if (func->isForwardDeclaration) {
            return true;
        }
    }
    return false;
}

bool SymbolTable::isImplemented(const std::string& name) const {
    auto overloads = getAllFunctionOverloads(name);
    for (const auto& func : overloads) {
        if (func->isImplemented) {
            return true;
        }
    }
    return false;
}

// Class-related methods
void SymbolTable::addClass(const std::string& name, const std::string& parentClass) {
    PRYST_DEBUG("Adding class: " + name + (parentClass.empty() ? "" : " with parent: " + parentClass));
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    ClassInfo classInfo;
    classInfo.superClassName = parentClass;
    if (!parentClass.empty()) {
        if (!classExists(parentClass)) {
            throw std::runtime_error("Parent class not found: " + parentClass);
        }
    }

    scopes.back()->classes[name] = classInfo;
}

void SymbolTable::addClass(const std::string& name, const ClassInfo& info) {
    PRYST_DEBUG("Adding class with info: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    scopes.back()->classes[name] = info;
}

bool SymbolTable::classExists(const std::string& name) const {
    if (scopes.empty()) return false;
    auto scope = scopes.back();
    while (scope) {
        if (scope->classes.find(name) != scope->classes.end()) {
            return true;
        }
        scope = scope->parent;
    }
    return false;
}

ClassInfo SymbolTable::getClassInfo(const std::string& name) const {
    PRYST_DEBUG("Getting class info for: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto scope = scopes.back();
    while (scope) {
        auto it = scope->classes.find(name);
        if (it != scope->classes.end()) {
            return it->second;
        }
        scope = scope->parent;
    }
    throw std::runtime_error("Class not found: " + name);
}

// Helper methods
bool SymbolTable::areTypesCompatible(const std::string& expected, const std::string& actual) const {
    PRYST_DEBUG("Checking type compatibility: expected=" + expected + ", actual=" + actual);

    // Strip const from types for comparison
    std::string expectedBase = expected;
    std::string actualBase = actual;
    bool expectedConst = false;
    bool actualConst = false;

    // Handle const types
    if (expectedBase.substr(0, 6) == "const ") {
        expectedConst = true;
        expectedBase = expectedBase.substr(6);
    }
    if (actualBase.substr(0, 6) == "const ") {
        actualConst = true;
        actualBase = actualBase.substr(6);
    }

    // Direct match after const stripping
    if (expectedBase == actualBase) {
        // If expected is const, actual must also be const
        return !expectedConst || actualConst;
    }

    // Allow implicit conversion between numeric types
    if ((expectedBase == "int" || expectedBase == "float") &&
        (actualBase == "int" || actualBase == "float")) {
        // If expected is const, actual must also be const
        return !expectedConst || actualConst;
    }

    // Handle function type compatibility
    if (isFunctionType(expectedBase) && isFunctionType(actualBase)) {
        auto [expectedReturn, expectedParams] = parseFunctionType(expectedBase);
        auto [actualReturn, actualParams] = parseFunctionType(actualBase);

        if (!areTypesCompatible(expectedReturn, actualReturn)) {
            PRYST_DEBUG("Function return types not compatible");
            return false;
        }

        if (expectedParams.size() != actualParams.size()) {
            PRYST_DEBUG("Function parameter counts don't match");
            return false;
        }

        for (size_t i = 0; i < expectedParams.size(); ++i) {
            if (!areTypesCompatible(expectedParams[i], actualParams[i])) {
                PRYST_DEBUG("Function parameter types not compatible at index " + std::to_string(i));
                return false;
            }
        }

        return !expectedConst || actualConst;
    }

    // Handle class inheritance
    if (classExists(expectedBase) && classExists(actualBase)) {
        auto currentClass = actualBase;
        while (!currentClass.empty()) {
            if (currentClass == expectedBase) {
                return !expectedConst || actualConst;
            }
            currentClass = getClassInfo(currentClass).superClassName;
        }
        PRYST_DEBUG("Class types not compatible through inheritance");
        return false;
    }

    PRYST_DEBUG("Types not compatible");
    return false;
}

bool SymbolTable::isFunctionType(const std::string& type) const {
    PRYST_DEBUG("Checking if type is function type: " + type);
    // Check for fn<ReturnType> format
    if (type.find("fn<") == 0) {
        PRYST_DEBUG("Found fn<ReturnType> format");
        return true;
    }
    // Check for lambda format (params) -> ReturnType
    if (type.find("->") != std::string::npos) {
        PRYST_DEBUG("Found lambda function format");
        return true;
    }
    return false;
}

std::pair<std::string, std::vector<std::string>> SymbolTable::parseFunctionType(const std::string& type) const {
    PRYST_DEBUG("Parsing function type: " + type);
    std::string returnType;
    std::vector<std::string> paramTypes;

    try {
        if (type.find("fn<") == 0) {
            // Parse fn<ReturnType>(ParamType1, ParamType2, ...)
            size_t returnTypeStart = type.find('<') + 1;
            size_t returnTypeEnd = type.find('>');
            if (returnTypeStart == std::string::npos || returnTypeEnd == std::string::npos) {
                throw std::runtime_error("Invalid function type format: missing angle brackets");
            }

            returnType = type.substr(returnTypeStart, returnTypeEnd - returnTypeStart);
            returnType = returnType.substr(returnType.find_first_not_of(" \t"), returnType.find_last_not_of(" \t") + 1);

            size_t paramListStart = type.find('(', returnTypeEnd);
            size_t paramListEnd = type.find(')', paramListStart);
            if (paramListStart == std::string::npos || paramListEnd == std::string::npos) {
                throw std::runtime_error("Invalid function type format: missing parentheses");
            }

            std::string paramListStr = type.substr(paramListStart + 1, paramListEnd - paramListStart - 1);
            if (!paramListStr.empty()) {
                std::istringstream ss(paramListStr);
                std::string paramType;
                while (std::getline(ss, paramType, ',')) {
                    paramType = paramType.substr(paramType.find_first_not_of(" \t"), paramType.find_last_not_of(" \t") + 1);
                    paramTypes.push_back(paramType);
                }
            }
        } else if (type.find("->") != std::string::npos) {
            // Parse (ParamType1, ParamType2) -> ReturnType format
            size_t arrowPos = type.find("->");
            size_t paramListStart = type.find('(');
            size_t paramListEnd = type.find(')');

            if (paramListStart == std::string::npos || paramListEnd == std::string::npos) {
                throw std::runtime_error("Invalid lambda type format: missing parentheses");
            }

            // Get return type after ->
            returnType = type.substr(arrowPos + 2);
            returnType = returnType.substr(returnType.find_first_not_of(" \t"), returnType.find_last_not_of(" \t") + 1);

            // Get parameter types
            std::string paramListStr = type.substr(paramListStart + 1, paramListEnd - paramListStart - 1);
            if (!paramListStr.empty()) {
                std::istringstream ss(paramListStr);
                std::string paramType;
                while (std::getline(ss, paramType, ',')) {
                    paramType = paramType.substr(paramType.find_first_not_of(" \t"), paramType.find_last_not_of(" \t") + 1);
                    paramTypes.push_back(paramType);
                }
            }
        } else {
            throw std::runtime_error("Not a function type: " + type);
        }

        PRYST_DEBUG("Parsed return type: " + returnType);
        for (const auto& param : paramTypes) {
            PRYST_DEBUG("Parsed parameter type: " + param);
        }
        return {returnType, paramTypes};
    } catch (const std::exception& e) {
        PRYST_DEBUG("Error parsing function type: " + std::string(e.what()));
        throw;
    }
}

std::string SymbolTable::createFunctionTypeString(const std::string& returnType, const std::vector<std::string>& paramTypes) const {
    std::string result = "(";
    for (size_t i = 0; i < paramTypes.size(); ++i) {
        if (i > 0) result += ", ";
        result += paramTypes[i];
    }
    result += ") -> " + returnType;
    return result;
}

// Module management methods
void SymbolTable::addModule(const std::string& name, const ModuleInfo& info) {
    PRYST_DEBUG("Adding module: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto moduleInfo = std::make_shared<ModuleInfo>(info);
    scopes.back()->modules[name] = moduleInfo;
}

bool SymbolTable::moduleExists(const std::string& name) const {
    PRYST_DEBUG("Checking if module exists: " + name);
    if (scopes.empty()) return false;
    auto scope = scopes.back();
    while (scope) {
        if (scope->modules.find(name) != scope->modules.end()) {
            return true;
        }
        scope = scope->parent;
    }
    return false;
}

ModuleInfo SymbolTable::getModuleInfo(const std::string& name) const {
    PRYST_DEBUG("Getting module info for: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto scope = scopes.back();
    while (scope) {
        auto it = scope->modules.find(name);
        if (it != scope->modules.end()) {
            return *it->second;
        }
        scope = scope->parent;
    }
    throw std::runtime_error("Module not found: " + name);
}

void SymbolTable::addModuleAlias(const std::string& alias, const std::string& qualifiedName) {
    PRYST_DEBUG("Adding module alias: " + alias + " -> " + qualifiedName);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    scopes.back()->moduleAliases[alias] = qualifiedName;
}

std::string SymbolTable::resolveModuleName(const std::string& name) const {
    PRYST_DEBUG("Resolving module name: " + name);
    if (scopes.empty()) return name;
    auto scope = scopes.back();
    while (scope) {
        auto it = scope->moduleAliases.find(name);
        if (it != scope->moduleAliases.end()) {
            return it->second;
        }
        scope = scope->parent;
    }
    return name;
}

void SymbolTable::importModule(const std::string& qualifiedName) {
    PRYST_DEBUG("Importing module: " + qualifiedName);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    if (!moduleExists(qualifiedName)) {
        throw std::runtime_error("Module not found: " + qualifiedName);
    }
    auto moduleInfo = getModuleInfo(qualifiedName);
    importModuleSymbols(moduleInfo, "", *scopes.back());
}

void SymbolTable::importAllFromModule(const std::string& qualifiedName) {
    PRYST_DEBUG("Importing all from module: " + qualifiedName);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    importAllFromModuleImpl(qualifiedName, *scopes.back());
}

void SymbolTable::importModuleSymbols(const ModuleInfo& mod, const std::string& prefix, Scope& targetScope) {
    std::string actualPrefix = prefix.empty() ? "" : prefix + "::";
    PRYST_DEBUG("Importing module symbols with prefix: '" + actualPrefix + "'");

    // Import functions
    for (const auto& [name, funcInfos] : mod.functions) {
        std::string qualifiedName = actualPrefix + name;
        PRYST_DEBUG("Processing function import: " + qualifiedName);
        for (const auto& funcInfo : funcInfos) {
            if (functionExists(qualifiedName)) {
                PRYST_DEBUG("Function already exists: " + qualifiedName);
                throw std::runtime_error("Function '" + qualifiedName + "' already exists");
            }
            PRYST_DEBUG("Adding function to scope: " + qualifiedName);
            addFunction(qualifiedName, funcInfo);
        }
    }

    // Import classes
    for (const auto& [name, classInfo] : mod.exportedClasses) {
        std::string qualifiedName = actualPrefix + name;
        PRYST_DEBUG("Processing class import: " + qualifiedName);
        if (classExists(qualifiedName)) {
            PRYST_DEBUG("Class already exists: " + qualifiedName);
            throw std::runtime_error("Class '" + qualifiedName + "' already exists");
        }
        PRYST_DEBUG("Adding class to scope: " + qualifiedName);
        addClass(qualifiedName, classInfo);
    }
}

void SymbolTable::importAllFromModuleImpl(const std::string& qualifiedName, Scope& targetScope) {
    if (!moduleExists(qualifiedName)) {
        throw std::runtime_error("Module not found: " + qualifiedName);
    }
    auto moduleInfo = getModuleInfo(qualifiedName);
    importModuleSymbols(moduleInfo, "", targetScope);
}

// Namespace management methods
void SymbolTable::addNamespace(const std::string& name) {
    PRYST_DEBUG("Adding namespace: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto namespaceInfo = std::make_shared<NamespaceInfo>();
    namespaceInfo->qualifiedName = name;
    scopes.back()->namespaces[name] = namespaceInfo;
}

void SymbolTable::addNamespaceAlias(const std::string& alias, const std::string& qualifiedName) {
    PRYST_DEBUG("Adding namespace alias: " + alias + " -> " + qualifiedName);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    scopes.back()->moduleAliases[alias] = qualifiedName;
}

bool SymbolTable::namespaceExists(const std::string& name) const {
    PRYST_DEBUG("Checking if namespace exists: " + name);
    if (scopes.empty()) return false;
    auto scope = scopes.back();
    while (scope) {
        if (scope->namespaces.find(name) != scope->namespaces.end()) {
            return true;
        }
        scope = scope->parent;
    }
    return false;
}

std::shared_ptr<NamespaceInfo> SymbolTable::getNamespaceInfo(const std::string& name) const {
    PRYST_DEBUG("Getting namespace info for: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto scope = scopes.back();
    while (scope) {
        auto it = scope->namespaces.find(name);
        if (it != scope->namespaces.end()) {
            return it->second;
        }
        scope = scope->parent;
    }
    throw std::runtime_error("Namespace not found: " + name);
}

// Using declaration methods
void SymbolTable::addUsingDeclaration(UsingKind kind, const std::string& qualifiedName, bool isBlockLevel) {
    PRYST_DEBUG("Adding using declaration: kind=" + std::to_string(static_cast<int>(kind)) +
                ", name=" + qualifiedName + ", blockLevel=" + (isBlockLevel ? "true" : "false"));
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    // Create the using declaration
    UsingDeclaration decl(kind, qualifiedName, isBlockLevel);

    // Add to current scope
    scopes.back()->usingDeclarations.push_back(decl);
}

bool SymbolTable::hasUsingDeclaration(const std::string& qualifiedName, UsingKind kind) const {
    PRYST_DEBUG("Checking for using declaration: " + qualifiedName);
    if (scopes.empty()) return false;

    auto scope = scopes.back();
    while (scope) {
        for (const auto& decl : scope->usingDeclarations) {
            if (decl.qualifiedName == qualifiedName && decl.kind == kind) {
                return true;
            }
        }
        scope = scope->parent;
    }
    return false;
}

void SymbolTable::importNamespace(const std::string& qualifiedName) {
    PRYST_DEBUG("Importing namespace: " + qualifiedName);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    if (!namespaceExists(qualifiedName)) {
        throw std::runtime_error("Namespace not found: " + qualifiedName);
    }
    auto namespaceInfo = getNamespaceInfo(qualifiedName);
    importNamespaceSymbols(*namespaceInfo, *scopes.back());
}

void SymbolTable::importAllFromNamespace(const std::string& qualifiedName) {
    PRYST_DEBUG("Importing all from namespace: " + qualifiedName);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    importAllFromNamespaceImpl(qualifiedName, *scopes.back());
}

void SymbolTable::importNamespaceSymbols(const NamespaceInfo& ns, Scope& targetScope) {
    // Import functions
    for (const auto& [name, funcInfos] : ns.functions) {
        if (functionExists(name)) {
            throw std::runtime_error("Function '" + name + "' already exists");
        }
        for (const auto& funcInfo : funcInfos) {
            addFunction(name, funcInfo);
        }
    }

    // Import classes
    for (const auto& [name, classInfo] : ns.classes) {
        if (classExists(name)) {
            throw std::runtime_error("Class '" + name + "' already exists");
        }
        addClass(name, classInfo);
    }

    // Import variables
    for (const auto& [name, varInfo] : ns.variables) {
        if (variableExists(name)) {
            throw std::runtime_error("Variable '" + name + "' already exists");
        }
        addVariable(name, varInfo.type, varInfo.isConst);
    }
}

void SymbolTable::importAllFromNamespaceImpl(const std::string& qualifiedName, Scope& targetScope) {
    if (!namespaceExists(qualifiedName)) {
        throw std::runtime_error("Namespace not found: " + qualifiedName);
    }
    auto namespaceInfo = getNamespaceInfo(qualifiedName);
    importNamespaceSymbols(*namespaceInfo, targetScope);
}

std::string SymbolTable::resolveNamespaceName(const std::string& name) const {
    PRYST_DEBUG("Resolving namespace name: " + name);
    if (scopes.empty()) return name;
    auto scope = scopes.back();
    while (scope) {
        auto it = scope->moduleAliases.find(name);
        if (it != scope->moduleAliases.end()) {
            return it->second;
        }
        scope = scope->parent;
    }
    return name;
}

bool SymbolTable::resolveQualifiedName(const std::string& qualifiedName, std::shared_ptr<NamespaceInfo>& outNs) const {
    PRYST_DEBUG("Resolving qualified name: " + qualifiedName);
    std::vector<std::string> parts;
    std::string part;
    std::istringstream stream(qualifiedName);

    // Split by :: instead of just :
    std::string temp;
    while (std::getline(stream, temp, ':')) {
        if (!temp.empty()) {
            if (temp[0] == ':' && !part.empty()) {
                parts.push_back(part);
                part.clear();
            } else {
                part += temp;
            }
        }
    }
    if (!part.empty()) {
        parts.push_back(part);
    }

    PRYST_DEBUG("Split qualified name into parts: " + std::to_string(parts.size()));
    if (parts.empty()) return false;

    auto currentScope = scopes.back();
    std::shared_ptr<NamespaceInfo> currentNs;

    // First try to resolve using any active using declarations
    while (currentScope) {
        for (const auto& usingDecl : currentScope->usingDeclarations) {
            if (usingDecl.kind == UsingKind::NAMESPACE) {
                auto baseNs = getNamespaceInfo(usingDecl.qualifiedName);
                if (resolveFromNamespace(baseNs, parts, outNs)) {
                    return true;
                }
            }
        }
        currentScope = currentScope->parent;
    }

    // If not found through using declarations, try absolute path
    currentScope = scopes.back();
    for (size_t i = 0; i < parts.size(); ++i) {
        bool found = false;
        while (currentScope) {
            auto it = currentScope->namespaces.find(parts[i]);
            if (it != currentScope->namespaces.end()) {
                currentNs = it->second;
                found = true;
                break;
            }
            currentScope = currentScope->parent;
        }
        if (!found) {
            PRYST_DEBUG("Failed to resolve part: " + parts[i]);
            return false;
        }
        if (i < parts.size() - 1) {
            auto subNs = currentNs->subNamespaces.find(parts[i + 1]);
            if (subNs == currentNs->subNamespaces.end()) {
                PRYST_DEBUG("Failed to find sub-namespace: " + parts[i + 1]);
                return false;
            }
            currentNs = subNs->second;
        }
    }

    outNs = currentNs;
    return true;
}

void SymbolTable::markVariableCaptured(const std::string& name) {
    PRYST_DEBUG("Marking variable as captured: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    auto currentScope = scopes.back();
    bool found = false;

    // Look for the variable in parent scopes
    while (currentScope->parent && !found) {
        currentScope = currentScope->parent;
        auto it = currentScope->variables.find(name);
        if (it != currentScope->variables.end()) {
            PRYST_DEBUG("Found variable to capture in parent scope");
            it->second.isCaptured = true;
            found = true;

            // Add to capturedVariables in the closure scope
            auto closureScope = scopes.back();
            closureScope->capturedVariables[name] = it->second;
            closureScope->capturedVariables[name].isConst = true; // Freeze captured variables
        }
    }

    if (!found) {
        throw std::runtime_error("Cannot capture undefined variable: " + name);
    }
}

void SymbolTable::beginAnonymousFunction() {
    PRYST_DEBUG("Beginning anonymous function scope");
    pushScope();
    scopes.back()->isAnonymousFunction = true;
}

void SymbolTable::endAnonymousFunction() {
    PRYST_DEBUG("Ending anonymous function scope");
    if (scopes.empty() || !scopes.back()->isAnonymousFunction) {
        throw std::runtime_error("No anonymous function scope to end");
    }
    popScope();
}

std::shared_ptr<FunctionInfo> SymbolTable::lookupFunction(const std::string& name) const {
    PRYST_DEBUG("Looking up function: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    auto scope = scopes.back();
    while (scope) {
        auto it = scope->functions.find(name);
        if (it != scope->functions.end() && !it->second.empty()) {
            return it->second.front();  // Return first overload
        }
        scope = scope->parent;
    }
    throw std::runtime_error("Function not found: " + name);
}

std::unordered_map<std::string, ClassInfo> SymbolTable::getCurrentScopeClasses() const {
    PRYST_DEBUG("Getting current scope classes");
    if (scopes.empty()) {
        return {};
    }
    return scopes.back()->classes;
}

// Module path and namespace tracking
std::string SymbolTable::getCurrentModule() const {
    return currentModule;
}

void SymbolTable::setCurrentModule(const std::string& moduleName) {
    currentModule = moduleName;
}

void SymbolTable::removeBlockLevelUsingDeclarations() {
    if (scopes.empty()) return;

    auto& currentScope = scopes.back();
    auto it = currentScope->usingDeclarations.begin();
    while (it != currentScope->usingDeclarations.end()) {
        if (it->isBlockLevel) {
            it = currentScope->usingDeclarations.erase(it);
        } else {
            ++it;
        }
    }
}

bool SymbolTable::resolveFromNamespace(
    const std::shared_ptr<NamespaceInfo>& baseNs,
    const std::vector<std::string>& parts,
    std::shared_ptr<NamespaceInfo>& outNs) const {

    if (!baseNs) return false;

    std::shared_ptr<NamespaceInfo> currentNs = baseNs;
    for (size_t i = 0; i < parts.size(); ++i) {
        const auto& part = parts[i];
        auto it = currentNs->subNamespaces.find(part);
        if (it == currentNs->subNamespaces.end()) {
            return false;
        }
        currentNs = it->second;
    }

    outNs = currentNs;
    return true;
}



std::string SymbolTable::getCurrentNamespacePath() const {
    return currentNamespacePath;
}

void SymbolTable::setCurrentNamespacePath(const std::string& namespacePath) {
    currentNamespacePath = namespacePath;
}

void SymbolTable::addImport(const std::string& qualifiedName) {
    imports.push_back(qualifiedName);
}

std::vector<std::string> SymbolTable::getCurrentScopeModules() const {
    std::vector<std::string> result;
    if (!scopes.empty()) {
        for (const auto& [name, _] : scopes.back()->modules) {
            result.push_back(name);
        }
    }
    return result;
}

VariableInfo SymbolTable::getCapturedVariableInfo(const std::string& name) const {
    PRYST_DEBUG("Getting captured variable info for: " + name);
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    auto scope = scopes.back();
    while (scope) {
        // First check if the variable is captured in the current scope
        auto capturedIt = scope->capturedVariables.find(name);
        if (capturedIt != scope->capturedVariables.end()) {
            PRYST_DEBUG("Found captured variable in scope");
            return capturedIt->second;
        }

        // Then check if it's a regular variable that's marked as captured
        auto varIt = scope->variables.find(name);
        if (varIt != scope->variables.end() && varIt->second.isCaptured) {
            PRYST_DEBUG("Found captured regular variable in scope");
            return varIt->second;
        }

        scope = scope->parent;
    }

    PRYST_DEBUG("No captured variable found with name: " + name);
    return VariableInfo(); // Return empty info if not found
}
