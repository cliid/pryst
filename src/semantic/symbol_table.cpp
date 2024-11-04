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

    std::cout << "DEBUG: Starting scope cleanup. Current sizes - Variables: " << scopes.back().variables.size()
              << ", Functions: " << scopes.back().functions.size()
              << ", Classes: " << scopes.back().classes.size()
              << ", Modules: " << scopes.back().modules.size() << std::endl;

    // Remove variables declared in the current scope
    for (auto it = scopes.back().variables.begin(); it != scopes.back().variables.end();) {
        std::cout << "DEBUG: Cleaning up variable '" << it->first << "' of type '" << it->second.type
                  << "' from scope " << getCurrentScopeLevel() << std::endl;

        // Clear FunctionInfo contents before erasing
        if (it->second.isFunctionType) {
            std::cout << "DEBUG: Cleaning up function info for variable '" << it->first << "'" << std::endl;
            it->second.functionInfo.paramTypes.clear();
            it->second.functionInfo.deducedReturnTypes.clear();
            it->second.functionInfo.returnType.clear();
        }

        // Clear the variable's type string
        it->second.type.clear();

        it = scopes.back().variables.erase(it);
    }

    // Remove functions declared in the current scope
    for (auto it = scopes.back().functions.begin(); it != scopes.back().functions.end();) {
        std::cout << "DEBUG: Removing function '" << it->first << "' with "
                  << it->second.size() << " overloads from scope " << getCurrentScopeLevel() << std::endl;

        // Clear each function overload's contents before erasing
        for (auto& funcInfo : it->second) {
            std::cout << "DEBUG: Cleaning up function overload" << std::endl;
            if (funcInfo) {
                funcInfo->paramTypes.clear();
                funcInfo->deducedReturnTypes.clear();
                funcInfo->returnType.clear();
            }
        }

        // Clear the vector of function overloads
        it->second.clear();
        it = scopes.back().functions.erase(it);
    }

    // Remove classes declared in the current scope
    for (auto it = scopes.back().classes.begin(); it != scopes.back().classes.end();) {
        std::cout << "DEBUG: Cleaning up class '" << it->first << "' from scope " << getCurrentScopeLevel() << std::endl;
        // Clear class info contents
        it->second.superClassName.clear();
        it->second.members.clear();
        it->second.methods.clear();
        it = scopes.back().classes.erase(it);
    }

    scopes.pop_back();
    std::cout << "DEBUG: Popped scope, new level: " << getCurrentScopeLevel()
              << ", remaining scopes: " << scopes.size() << std::endl;
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

    // Create VariableInfo with explicit construction
    auto [it, inserted] = scopes.back().variables.try_emplace(name, VariableInfo(type, isConst, static_cast<int>(getCurrentScopeLevel())));
    if (!inserted) {
        throw std::runtime_error("Variable '" + name + "' already exists in current scope");
    }

    // Set function type info if needed
    if (isFunctionType(type)) {
        auto [returnType, paramTypes] = parseFunctionType(type);
        it->second.isFunctionType = true;
        it->second.functionInfo = FunctionInfo(
            returnType,
            paramTypes,
            static_cast<int>(getCurrentScopeLevel()),
            false,
            true
        );
    }
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

    // Create FunctionInfo with explicit initialization
    auto info = std::make_shared<FunctionInfo>(returnType, paramTypes, static_cast<int>(getCurrentScopeLevel()), false, true, std::vector<std::string>{});

    // Ensure the functions map for this name exists and is properly initialized
    auto& globalScope = scopes[0];
    auto it = globalScope.functions.find(name);
    if (it == globalScope.functions.end()) {
        // Initialize with reserved capacity for expected overloads
        std::vector<std::shared_ptr<FunctionInfo>> overloads;
        overloads.reserve(4);  // Reserve space for typical number of overloads
        globalScope.functions.emplace(name, std::move(overloads));
        it = globalScope.functions.find(name);
    }

    // Add the function info to the vector
    std::cout << "DEBUG: Adding function overload to vector (size before: " << it->second.size() << ")" << std::endl;
    it->second.push_back(std::move(info));
    std::cout << "DEBUG: Function added successfully (size after: " << it->second.size() << ")" << std::endl;
}

std::vector<SymbolTable::FunctionInfo> SymbolTable::getAllFunctionOverloads(const std::string& name) const {
    if (scopes.empty() || !functionExists(name)) {
        return {};
    }
    std::vector<FunctionInfo> result;
    for (const auto& ptr : scopes[0].functions.at(name)) {
        result.push_back(*ptr);  // Dereference shared_ptr to get FunctionInfo
    }
    return result;
}

SymbolTable::FunctionInfo SymbolTable::getFunctionInfo(const std::string& name) const {
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    auto it = scopes[0].functions.find(name);
    if (it == scopes[0].functions.end() || it->second.empty()) {
        throw std::runtime_error("Undefined function: '" + name + "'");
    }
    return *(it->second[0]);  // Dereference shared_ptr to get FunctionInfo
}

std::unordered_map<std::string, SymbolTable::FunctionInfo> SymbolTable::getCurrentScopeFunctions() const {
    if (scopes.empty()) {
        return {};
    }
    std::unordered_map<std::string, FunctionInfo> result;
    for (const auto& func : scopes.back().functions) {
        if (!func.second.empty()) {
            result[func.first] = *(func.second[0]); // Dereference shared_ptr to get first overload
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

    const auto& funcVec = scopes[0].functions.at(name);
    for (const auto& funcPtr : funcVec) {
        if (funcPtr->paramTypes.size() != argTypes.size()) {
            std::cout << "DEBUG: Skipping overload due to parameter count mismatch" << std::endl;
            continue;
        }

        bool match = true;
        for (size_t i = 0; i < argTypes.size(); ++i) {
            if (!areTypesCompatible(funcPtr->paramTypes[i], argTypes[i])) {
                std::cout << "DEBUG: Type mismatch at parameter " << i << ": expected " << funcPtr->paramTypes[i] << ", got " << argTypes[i] << std::endl;
                match = false;
                break;
            }
        }

        if (match) {
            std::cout << "DEBUG: Found matching function overload" << std::endl;
            outInfo = *funcPtr;  // Dereference shared_ptr to get FunctionInfo
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

SymbolTable::~SymbolTable() {
    std::cout << "DEBUG: Starting SymbolTable destruction" << std::endl;

    // Clear all scopes except global scope first
    while (scopes.size() > 1) {
        try {
            popScope();
        } catch (const std::exception& e) {
            std::cerr << "DEBUG: Error during scope cleanup: " << e.what() << std::endl;
        }
    }

    // Clean up global scope manually since we can't pop it
    if (!scopes.empty()) {
        std::cout << "DEBUG: Cleaning up global scope" << std::endl;
        auto& globalScope = scopes[0];

        std::cout << "DEBUG: Clearing module aliases" << std::endl;
        globalScope.moduleAliases.clear();

        std::cout << "DEBUG: Clearing modules" << std::endl;
        globalScope.modules.clear();

        std::cout << "DEBUG: Clearing variables" << std::endl;
        globalScope.variables.clear();

        // Clear functions with detailed debugging
        std::cout << "DEBUG: Starting function cleanup" << std::endl;
        std::cout << "DEBUG: Number of function entries: " << globalScope.functions.size() << std::endl;

        // First pass: just print information about what we have
        for (const auto& funcPair : globalScope.functions) {
            std::cout << "DEBUG: Found function '" << funcPair.first << "' with "
                      << funcPair.second.size() << " overloads" << std::endl;
            for (size_t i = 0; i < funcPair.second.size(); ++i) {
                const auto& func = funcPair.second[i];
                std::cout << "DEBUG:   Overload " << i << ": return type='" << (*func).returnType
                          << "', params=" << (*func).paramTypes.size() << std::endl;
            }
        }

        // Clear each function vector individually, handling each element
        std::cout << "DEBUG: Clearing function vectors individually" << std::endl;
        for (auto& funcPair : globalScope.functions) {
            std::cout << "DEBUG: Clearing function '" << funcPair.first << "'" << std::endl;
            // Clear each element's contents first
            for (auto& func : funcPair.second) {
                std::cout << "DEBUG: Clearing function element with return type '" << (*func).returnType << "'" << std::endl;
                (*func).paramTypes.clear();
                (*func).deducedReturnTypes.clear();
                (*func).returnType.clear();
            }
            // Now clear the vector itself
            funcPair.second.clear();
            std::cout << "DEBUG: Vector cleared, size is now " << funcPair.second.size() << std::endl;
        }

        // Now clear the map itself
        std::cout << "DEBUG: Clearing functions map" << std::endl;
        globalScope.functions.clear();
        std::cout << "DEBUG: Map cleared, size is now " << globalScope.functions.size() << std::endl;

        std::cout << "DEBUG: Clearing classes" << std::endl;
        globalScope.classes.clear();
    }

    // Finally clear the scopes vector itself
    std::cout << "DEBUG: Clearing scopes vector" << std::endl;
    scopes.clear();
    std::cout << "DEBUG: SymbolTable destruction complete" << std::endl;
}
