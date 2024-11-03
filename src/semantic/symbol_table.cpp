#include "symbol_table.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <regex>

SymbolTable::SymbolTable() {
    std::cout << "DEBUG: Initializing SymbolTable" << std::endl;
    pushScope();  // Initialize with global scope
}

void SymbolTable::pushScope() {
    scopes.push_back(Scope());
    std::cout << "DEBUG: Pushed scope, new level: " << getCurrentScopeLevel() << std::endl;
}

void SymbolTable::popScope() {
    if (scopes.empty()) {
        std::cout << "DEBUG: ERROR - Attempting to pop empty scope stack" << std::endl;
        throw std::runtime_error("Cannot pop empty scope stack");
    }
    if (scopes.size() == 1) {
        std::cout << "DEBUG: ERROR - Attempting to pop global scope" << std::endl;
        throw std::runtime_error("Cannot pop global scope");
    }

    // Remove variables declared in the current scope
    for (auto it = scopes.back().variables.begin(); it != scopes.back().variables.end();) {
        std::cout << "DEBUG: Removing variable '" << it->first << "' from scope " << getCurrentScopeLevel() << std::endl;
        it = scopes.back().variables.erase(it);
    }

    // Remove functions declared in the current scope
    for (auto it = scopes.back().functions.begin(); it != scopes.back().functions.end();) {
        std::cout << "DEBUG: Removing function '" << it->first << "' from scope " << getCurrentScopeLevel() << std::endl;
        it = scopes.back().functions.erase(it);
    }

    scopes.pop_back();
    std::cout << "DEBUG: Popped scope, new level: " << getCurrentScopeLevel() << std::endl;
}

size_t SymbolTable::getCurrentScopeLevel() const {
    return scopes.size() - 1;
}

bool SymbolTable::variableExists(const std::string& name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->variables.find(name) != it->variables.end()) {
            return true;
        }
    }
    return false;
}

bool SymbolTable::variableExistsInCurrentScope(const std::string& name) const {
    if (scopes.empty()) return false;
    return scopes.back().variables.find(name) != scopes.back().variables.end();
}

void SymbolTable::addVariable(const std::string& name, const std::string& type, bool isConst) {
    std::cout << "DEBUG: Adding variable '" << name << "' of type '" << type << "' to scope " << getCurrentScopeLevel() << std::endl;
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }

    VariableInfo info;
    info.type = type;
    info.isConst = isConst;
    info.scopeLevel = static_cast<int>(getCurrentScopeLevel());
    info.isFunctionType = isFunctionType(type);

    // Initialize functionInfo with empty vector instead of null
    info.functionInfo.paramTypes = std::vector<std::string>();
    info.functionInfo.returnType = "";
    info.functionInfo.scopeLevel = static_cast<int>(getCurrentScopeLevel());
    info.functionInfo.isAnonymous = false;
    info.functionInfo.hasExplicitReturnType = false;
    info.functionInfo.deducedReturnTypes.clear();

    if (info.isFunctionType) {
        auto [returnType, paramTypes] = parseFunctionType(type);
        info.functionInfo.returnType = returnType;
        info.functionInfo.paramTypes = std::move(paramTypes);
        info.functionInfo.hasExplicitReturnType = true;
    }

    scopes.back().variables[name] = info;
}

std::string SymbolTable::getVariableType(const std::string& name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto var = it->variables.find(name);
        if (var != it->variables.end()) {
            return var->second.type;
        }
    }
    throw std::runtime_error("Undefined variable: '" + name + "'");
}

std::unordered_map<std::string, SymbolTable::VariableInfo> SymbolTable::getCurrentScopeVariables() const {
    if (scopes.empty()) return {};
    std::unordered_map<std::string, VariableInfo> result;
    for (const auto& pair : scopes.back().variables) {
        result.insert(pair);
    }
    return result;
}

void SymbolTable::clearCurrentScopeVariables() {
    if (!scopes.empty()) {
        scopes.back().variables.clear();
    }
}

bool SymbolTable::functionExists(const std::string& name) const {
    if (scopes.empty()) return false;
    return scopes[0].functions.find(name) != scopes[0].functions.end() &&
           !scopes[0].functions.at(name).empty();
}

void SymbolTable::addFunction(const std::string& name, const std::string& returnType, const std::vector<std::string>& paramTypes) {
    std::cout << "DEBUG: Adding function '" << name << "' with return type '" << returnType << "' to scope " << getCurrentScopeLevel() << std::endl;
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    FunctionInfo info{returnType, paramTypes, static_cast<int>(getCurrentScopeLevel()), false, true, {}};
    scopes[0].functions[name].push_back(info);
}

std::vector<SymbolTable::FunctionInfo> SymbolTable::getAllFunctionOverloads(const std::string& name) const {
    if (scopes.empty() || !functionExists(name)) {
        return {};
    }
    return scopes[0].functions.at(name);
}

SymbolTable::FunctionInfo SymbolTable::getFunctionInfo(const std::string& name) const {
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto it = scopes[0].functions.find(name);
    if (it == scopes[0].functions.end() || it->second.empty()) {
        throw std::runtime_error("Undefined function: '" + name + "'");
    }
    return it->second[0];  // Return first overload by default
}

std::unordered_map<std::string, SymbolTable::FunctionInfo> SymbolTable::getCurrentScopeFunctions() const {
    if (scopes.empty()) {
        return {};
    }
    std::unordered_map<std::string, FunctionInfo> result;
    for (const auto& func : scopes.back().functions) {
        if (!func.second.empty()) {
            result[func.first] = func.second[0]; // Get first overload
        }
    }
    return result;
}

void SymbolTable::clearCurrentScopeFunctions() {
    if (!scopes.empty()) {
        scopes.back().functions.clear();
    }
}

bool SymbolTable::classExists(const std::string& name) const {
    if (scopes.empty()) return false;
    return scopes[0].classes.find(name) != scopes[0].classes.end();
}

void SymbolTable::addClass(const std::string& name, const std::string& parentClass) {
    std::cout << "DEBUG: Adding class '" << name << "' with parent '" << parentClass << "'" << std::endl;
    if (classExists(name)) {
        throw std::runtime_error("Class '" + name + "' already declared");
    }
    ClassInfo info;
    info.superClassName = parentClass;
    scopes[0].classes[name] = info;
}

SymbolTable::ClassInfo SymbolTable::getClassInfo(const std::string& name) const {
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto it = scopes[0].classes.find(name);
    if (it == scopes[0].classes.end()) {
        throw std::runtime_error("Undefined class: '" + name + "'");
    }
    return it->second;
}

bool SymbolTable::areTypesCompatible(const std::string& expected, const std::string& actual) const {
    if (expected == actual) return true;
    // Allow implicit conversion between numeric types
    if ((expected == "int" || expected == "float") && (actual == "int" || actual == "float")) {
        return true;
    }

    // Handle function type compatibility
    if (isFunctionType(expected) && isFunctionType(actual)) {
        auto [expectedReturn, expectedParams] = parseFunctionType(expected);
        auto [actualReturn, actualParams] = parseFunctionType(actual);

        if (!areTypesCompatible(expectedReturn, actualReturn)) return false;
        if (expectedParams.size() != actualParams.size()) return false;

        for (size_t i = 0; i < expectedParams.size(); ++i) {
            if (!areTypesCompatible(expectedParams[i], actualParams[i])) {
                return false;
            }
        }
        return true;
    }

    return false;
}

bool SymbolTable::findMatchingFunction(const std::string& name, const std::vector<std::string>& argTypes, FunctionInfo& outInfo) const {
    std::cout << "DEBUG: Finding matching function '" << name << "' with " << argTypes.size() << " arguments" << std::endl;
    if (!functionExists(name)) {
        std::cout << "DEBUG: Function '" << name << "' does not exist" << std::endl;
        return false;
    }

    auto overloads = getAllFunctionOverloads(name);
    for (const auto& func : overloads) {
        if (func.paramTypes.size() != argTypes.size()) {
            std::cout << "DEBUG: Skipping overload due to parameter count mismatch" << std::endl;
            continue;
        }

        bool match = true;
        for (size_t i = 0; i < argTypes.size(); ++i) {
            if (!areTypesCompatible(func.paramTypes[i], argTypes[i])) {
                std::cout << "DEBUG: Type mismatch at parameter " << i << ": expected " << func.paramTypes[i] << ", got " << argTypes[i] << std::endl;
                match = false;
                break;
            }
        }

        if (match) {
            std::cout << "DEBUG: Found matching function overload" << std::endl;
            outInfo = func;
            return true;
        }
    }

    std::cout << "DEBUG: No matching function overload found" << std::endl;
    return false;
}
bool SymbolTable::isFunctionType(const std::string& type) const {
    // Function type format: (param1Type,param2Type,...)->returnType
    return type.find("->") != std::string::npos;
}

std::pair<std::string, std::vector<std::string>> SymbolTable::parseFunctionType(const std::string& type) const {
    if (!isFunctionType(type)) {
        throw std::runtime_error("Not a function type: " + type);
    }

    // Split return type and parameter list
    size_t arrowPos = type.find("->");
    std::string paramListStr = type.substr(1, arrowPos - 2); // Remove parentheses
    std::string returnType = type.substr(arrowPos + 2);

    // Parse parameter types
    std::vector<std::string> paramTypes;
    if (!paramListStr.empty()) {
        std::istringstream ss(paramListStr);
        std::string paramType;
        while (std::getline(ss, paramType, ',')) {
            paramTypes.push_back(paramType);
        }
    }

    return {returnType, paramTypes};
}

// Add class with full class info
void SymbolTable::addClass(const std::string& name, const ClassInfo& info) {
    std::cout << "DEBUG: Adding class '" << name << "' with full class info" << std::endl;
    if (classExists(name)) {
        throw std::runtime_error("Class '" + name + "' already declared");
    }
    if (!scopes.empty()) {
        scopes[0].classes[name] = info;
    } else {
        throw std::runtime_error("No active scope when adding class: " + name);
    }
}
