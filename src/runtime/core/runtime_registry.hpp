#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "../../error_handling/core/error.hpp"
#include "../../type_system/core/type_registry.hpp"

namespace pryst {
namespace runtime {

struct ClassMethod {
    std::string name;
    void* func;
    std::vector<std::string> paramTypes;
    std::string returnType;

    ClassMethod(const std::string& n, void* f, const std::vector<std::string>& params, const std::string& ret)
        : name(n), func(f), paramTypes(params), returnType(ret) {}
};

struct ClassType {
    std::string name;
    std::string fullName;
    llvm::StructType* llvmType;
    std::vector<ClassMethod> methods;
    const ClassType* baseClass;  // Track inheritance
    bool isInterface;  // Flag to indicate if this is an interface
    std::vector<const ClassType*> implementedInterfaces;  // Track implemented interfaces

    ClassType() : llvmType(nullptr), baseClass(nullptr), isInterface(false), implementedInterfaces() {}
    ClassType(const std::string& fullName)
        : name(fullName.substr(fullName.find_last_of(':') + 1)),
          fullName(fullName),
          llvmType(nullptr),
          baseClass(nullptr),
          isInterface(false),
          implementedInterfaces() {}
    ClassType(const std::string& name, const std::string& fullName)
        : name(name),
          fullName(fullName),
          llvmType(nullptr),
          baseClass(nullptr),
          isInterface(false),
          implementedInterfaces() {}
};

class RuntimeRegistry {
private:
    std::unordered_map<std::string, void*> functions;
    std::unordered_map<std::string, ClassType> classes;
    llvm::Module* module;
    core::TypeRegistry* typeRegistry;  // Change to pointer to allow nullptr initially
    std::unordered_map<std::string, bool> nullableTypes;  // Track nullable types
    static RuntimeRegistry* instance;

public:
    static RuntimeRegistry& getInstance() {
        if (!instance) throw core::Error("RuntimeRegistry instance not initialized");
        return *instance;
    }
    static void setInstance(RuntimeRegistry* reg) { instance = reg; }
    RuntimeRegistry(llvm::Module* mod);
    ~RuntimeRegistry() { if (instance == this) instance = nullptr; }
    void setTypeRegistry(core::TypeRegistry* registry);  // Method to set TypeRegistry later

    void registerFunction(const std::string& name, void* func);
    void* getFunction(const std::string& name);
    void registerType(const std::string& name, const std::string& fullName);
    void registerInheritance(const std::string& derived, const std::string& base);  // Add inheritance relationship
    void registerNullableType(const std::string& typeName);  // Register a type as nullable

    void registerClass(const std::string& name, const std::string& fullName, llvm::StructType* type, bool isInterface = false);
    void registerClassMethod(const std::string& className, const ClassMethod& method);
    void setBaseClass(const std::string& derivedClass, const std::string& baseClass);
    void implementInterface(const std::string& className, const std::string& interfaceName);
    const ClassType* getClass(const std::string& name) const;
    bool hasClass(const std::string& name) const;
    bool isSubclassOf(const char* derivedType, const char* baseType) const;
    const char* getObjectType(void* obj) const;
    bool isNullable(void* obj) const;
    bool implementsInterface(const std::string& typeName, const std::string& interfaceName) const;
    bool isInterface(const std::string& typeName) const;
    bool isArray(const std::string& typeName) const;
    bool isPrimitive(const std::string& typeName) const;
    std::string getTypeKind(const std::string& typeName) const;
    llvm::Module* getModule() const { return module; }
    core::TypeRegistry* getTypeRegistry() const { return typeRegistry; }  // Change to pointer return type

    // Register all runtime functions and types
    void registerBuiltins();
    void registerWebTypes();
}; // End of RuntimeRegistry
} // namespace runtime
} // namespace pryst
