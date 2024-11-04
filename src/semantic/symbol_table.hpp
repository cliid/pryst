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
        std::string returnType;  // Default initialize empty string
        std::vector<std::string> paramTypes;  // Default initialize empty vector
        int scopeLevel{0};  // Default initialize to 0
        bool isAnonymous{false};  // Default initialize to false
        bool hasExplicitReturnType{false};  // Default initialize to false
        std::vector<std::string> deducedReturnTypes;  // For type deduction

        // Default constructor with explicit initialization
        FunctionInfo() {
            std::cout << "DEBUG: FunctionInfo default constructor" << std::endl;
            std::cout << "DEBUG: returnType address: " << static_cast<void*>(&returnType) << std::endl;
        }

        // Constructor with all fields for aggregate initialization
        FunctionInfo(const std::string& rt, const std::vector<std::string>& pt, int sl, bool ia, bool het, const std::vector<std::string>& drt = {})
            : returnType(rt),
              paramTypes(pt),
              scopeLevel(sl),
              isAnonymous(ia),
              hasExplicitReturnType(het),
              deducedReturnTypes(drt) {
            std::cout << "DEBUG: FunctionInfo constructor - return type: '" << returnType
                      << "', params: " << paramTypes.size() << std::endl;
            std::cout << "DEBUG: returnType address: " << static_cast<void*>(&returnType) << std::endl;
        }

        // Copy constructor with explicit deep copy
        FunctionInfo(const FunctionInfo& other)
            : returnType(other.returnType),
              paramTypes(other.paramTypes),
              scopeLevel(other.scopeLevel),
              isAnonymous(other.isAnonymous),
              hasExplicitReturnType(other.hasExplicitReturnType),
              deducedReturnTypes(other.deducedReturnTypes) {
            std::cout << "DEBUG: FunctionInfo copy constructor - return type: '" << returnType
                      << "', params: " << paramTypes.size() << std::endl;
            std::cout << "DEBUG: returnType address: " << static_cast<void*>(&returnType) << std::endl;
        }

        // Move constructor
        FunctionInfo(FunctionInfo&& other) noexcept {
            std::cout << "DEBUG: FunctionInfo move constructor - START" << std::endl;
            std::cout << "DEBUG: this->returnType address: " << static_cast<void*>(&returnType) << std::endl;
            std::cout << "DEBUG: other.returnType address: " << static_cast<void*>(&other.returnType) << std::endl;

            returnType = std::move(other.returnType);
            paramTypes = std::move(other.paramTypes);
            scopeLevel = other.scopeLevel;
            isAnonymous = other.isAnonymous;
            hasExplicitReturnType = other.hasExplicitReturnType;
            deducedReturnTypes = std::move(other.deducedReturnTypes);

            std::cout << "DEBUG: FunctionInfo move constructor - END - return type: '" << returnType
                      << "', params: " << paramTypes.size() << std::endl;
        }

        // Copy assignment operator
        FunctionInfo& operator=(const FunctionInfo& other) {
            if (this != &other) {
                std::cout << "DEBUG: FunctionInfo copy assignment - START" << std::endl;
                std::cout << "DEBUG: this->returnType address: " << static_cast<void*>(&returnType) << std::endl;

                returnType = other.returnType;
                paramTypes = other.paramTypes;
                scopeLevel = other.scopeLevel;
                isAnonymous = other.isAnonymous;
                hasExplicitReturnType = other.hasExplicitReturnType;
                deducedReturnTypes = other.deducedReturnTypes;

                std::cout << "DEBUG: FunctionInfo copy assignment - END - return type: '" << returnType
                          << "', params: " << paramTypes.size() << std::endl;
            }
            return *this;
        }

        // Move assignment operator
        FunctionInfo& operator=(FunctionInfo&& other) noexcept {
            if (this != &other) {
                std::cout << "DEBUG: FunctionInfo move assignment - START" << std::endl;
                std::cout << "DEBUG: this->returnType address: " << static_cast<void*>(&returnType) << std::endl;
                std::cout << "DEBUG: other.returnType address: " << static_cast<void*>(&other.returnType) << std::endl;

                // Clear existing contents first
                returnType.clear();
                paramTypes.clear();
                deducedReturnTypes.clear();

                returnType = std::move(other.returnType);
                paramTypes = std::move(other.paramTypes);
                scopeLevel = other.scopeLevel;
                isAnonymous = other.isAnonymous;
                hasExplicitReturnType = other.hasExplicitReturnType;
                deducedReturnTypes = std::move(other.deducedReturnTypes);

                // Initialize moved-from object with empty strings
                other.returnType = std::string();
                other.paramTypes = std::vector<std::string>();
                other.deducedReturnTypes = std::vector<std::string>();

                std::cout << "DEBUG: FunctionInfo move assignment - END - return type: '" << returnType
                          << "', params: " << paramTypes.size() << std::endl;
            }
            return *this;
        }

        ~FunctionInfo() {
            std::cout << "DEBUG: FunctionInfo destructor - START - return type: '" << returnType
                      << "', params: " << paramTypes.size() << std::endl;
            // Clear strings explicitly before destruction
            returnType = std::string();
            for (auto& param : paramTypes) {
                param = std::string();
            }
            paramTypes.clear();
            for (auto& deduced : deducedReturnTypes) {
                deduced = std::string();
            }
            deducedReturnTypes.clear();
            std::cout << "DEBUG: FunctionInfo destructor - END" << std::endl;
        }
    };

    struct VariableInfo {
        std::string type;  // Default initialize empty string
        bool isConst{false};  // Default initialize to false
        int scopeLevel{0};  // Default initialize to 0
        bool isFunctionType{false};  // True if this is a function type variable
        FunctionInfo functionInfo;  // Used when isFunctionType is true

        // Default constructor ensures proper initialization
        VariableInfo()
            : type(std::string()),
              isConst(false),
              scopeLevel(0),
              isFunctionType(false),
              functionInfo() {}

        // Constructor for variable initialization
        VariableInfo(const std::string& t, bool ic = false, int sl = 0)
            : type(t),
              isConst(ic),
              scopeLevel(sl),
              isFunctionType(false),
              functionInfo() {}

        // Copy constructor ensures deep copy of strings
        VariableInfo(const VariableInfo& other)
            : type(std::string(other.type)),
              isConst(other.isConst),
              scopeLevel(other.scopeLevel),
              isFunctionType(other.isFunctionType),
              functionInfo(other.functionInfo) {}

        // Move constructor for efficiency
        VariableInfo(VariableInfo&& other) noexcept
            : type(std::move(other.type)),
              isConst(other.isConst),
              scopeLevel(other.scopeLevel),
              isFunctionType(other.isFunctionType),
              functionInfo(std::move(other.functionInfo)) {
            // Ensure moved-from strings are in valid state
            other.type = std::string();
            other.isConst = false;
            other.scopeLevel = 0;
            other.isFunctionType = false;
            other.functionInfo = FunctionInfo();
        }

        // Assignment operators
        VariableInfo& operator=(const VariableInfo& other) {
            if (this != &other) {
                type = std::string(other.type);
                isConst = other.isConst;
                scopeLevel = other.scopeLevel;
                isFunctionType = other.isFunctionType;
                functionInfo = other.functionInfo;
            }
            return *this;
        }

        VariableInfo& operator=(VariableInfo&& other) noexcept {
            if (this != &other) {
                type = std::move(other.type);
                isConst = other.isConst;
                scopeLevel = other.scopeLevel;
                isFunctionType = other.isFunctionType;
                functionInfo = std::move(other.functionInfo);
            }
            return *this;
        }

        // Destructor
        ~VariableInfo() = default;
    };

    struct ClassInfo {
        std::string superClassName{};  // Default initialize empty string
        std::unordered_map<std::string, VariableInfo> members{};  // Default initialize empty map
        std::unordered_map<std::string, FunctionInfo> methods{};  // Default initialize empty map

        // Default constructor ensures proper initialization
        ClassInfo() = default;

        // Copy constructor ensures deep copy
        ClassInfo(const ClassInfo& other) = default;

        // Move constructor for efficiency
        ClassInfo(ClassInfo&& other) noexcept = default;

        // Assignment operators
        ClassInfo& operator=(const ClassInfo& other) = default;
        ClassInfo& operator=(ClassInfo&& other) noexcept = default;

        // Destructor
        ~ClassInfo() = default;
    };

    struct ModuleInfo {
        std::string qualifiedName{};  // Default initialize empty string
        std::unordered_map<std::string, VariableInfo> exports{};  // Default initialize empty map
        std::unordered_map<std::string, FunctionInfo> exportedFunctions{};  // Default initialize empty map
        std::unordered_map<std::string, ClassInfo> exportedClasses{};  // Default initialize empty map

        // Default constructor ensures proper initialization
        ModuleInfo() = default;

        // Copy constructor ensures deep copy
        ModuleInfo(const ModuleInfo& other) = default;

        // Move constructor for efficiency
        ModuleInfo(ModuleInfo&& other) noexcept = default;

        // Assignment operators
        ModuleInfo& operator=(const ModuleInfo& other) = default;
        ModuleInfo& operator=(ModuleInfo&& other) noexcept = default;

        // Destructor
        ~ModuleInfo() = default;
    };

    SymbolTable();
    ~SymbolTable();
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
    void addClass(const std::string& name, const ClassInfo& info);
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
        std::map<std::string, std::vector<std::shared_ptr<FunctionInfo>>> functions;
        std::map<std::string, VariableInfo> variables;
        std::map<std::string, ClassInfo> classes;
        std::map<std::string, ModuleInfo> modules;
        std::map<std::string, std::string> moduleAliases;  // alias -> qualified name

        // Constructor
        Scope() {
            std::cout << "DEBUG: Creating new scope" << std::endl;
        }

        // Destructor with proper cleanup
        ~Scope() {
            std::cout << "DEBUG: Starting scope destruction" << std::endl;

            // Clear maps in a specific order
            std::cout << "DEBUG: Clearing module aliases" << std::endl;
            moduleAliases.clear();

            std::cout << "DEBUG: Clearing modules" << std::endl;
            modules.clear();

            std::cout << "DEBUG: Clearing variables" << std::endl;
            variables.clear();

            std::cout << "DEBUG: Clearing functions" << std::endl;
            // Clear each function vector first
            for (auto& pair : functions) {
                std::cout << "DEBUG: Clearing function '" << pair.first << "' with "
                          << pair.second.size() << " overloads" << std::endl;
                // Let vector handle its own cleanup
                pair.second.clear();
            }
            functions.clear();

            std::cout << "DEBUG: Clearing classes" << std::endl;
            classes.clear();

            std::cout << "DEBUG: Scope destruction complete" << std::endl;
        }

        // Delete copy constructor and assignment
        Scope(const Scope&) = delete;
        Scope& operator=(const Scope&) = delete;

        // Move constructor
        Scope(Scope&& other) noexcept
            : functions(std::move(other.functions)),
              variables(std::move(other.variables)),
              classes(std::move(other.classes)),
              modules(std::move(other.modules)),
              moduleAliases(std::move(other.moduleAliases)) {
            std::cout << "DEBUG: Moving scope with " << functions.size() << " function entries" << std::endl;
            // Clear the moved-from containers to ensure proper cleanup
            other.functions.clear();
            other.variables.clear();
            other.classes.clear();
            other.modules.clear();
            other.moduleAliases.clear();
        }

        // Move assignment
        Scope& operator=(Scope&& other) noexcept {
            if (this != &other) {
                functions = std::move(other.functions);
                variables = std::move(other.variables);
                classes = std::move(other.classes);
                modules = std::move(other.modules);
                moduleAliases = std::move(other.moduleAliases);
                std::cout << "DEBUG: Move assigning scope" << std::endl;
            }
            return *this;
        }
    };

    std::vector<Scope> scopes;
    bool areTypesCompatible(const std::string& expected, const std::string& actual) const;
    bool isFunctionType(const std::string& type) const;
    std::pair<std::string, std::vector<std::string>> parseFunctionType(const std::string& type) const;
    std::string createFunctionTypeString(const std::string& returnType, const std::vector<std::string>& paramTypes) const;
};
