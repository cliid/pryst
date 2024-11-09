# Module System Implementation

## Overview

The Pryst module system implements TypeScript-style module management with lazy loading, cross-module type checking, and namespace support. This document details the internal implementation of the module system.

## Core Components

### Module Representation

```cpp
class Module {
private:
    std::string name;
    std::string path;
    ModuleState state;
    std::vector<std::string> dependencies;

    // Symbol management
    SymbolTable exports;
    std::unordered_map<std::string, ImportInfo> imports;

    // Type information
    std::unordered_map<std::string, TypeInfo*> types;

public:
    // Module lifecycle
    void initialize();
    void load();
    void finalize();

    // Symbol management
    void addExport(const std::string& name, Symbol symbol);
    Symbol resolveImport(const std::string& name);

    // Type management
    void registerType(const std::string& name, TypeInfo* type);
    TypeInfo* lookupType(const std::string& name);
};
```

### Module Loader

```cpp
class ModuleLoader {
private:
    // Module management
    std::unordered_map<std::string, std::shared_ptr<Module>> loadedModules;
    std::vector<std::string> modulePath;

    // Symbol resolution
    SymbolTable globalSymbols;
    std::stack<std::string> loadingModules;  // For cycle detection

public:
    // Module loading
    std::shared_ptr<Module> loadModule(const std::string& name) {
        // Check for cycles
        if (std::find(loadingModules.begin(), loadingModules.end(), name)
            != loadingModules.end()) {
            throw ModuleError("Circular dependency detected");
        }

        // Check cache
        if (auto it = loadedModules.find(name); it != loadedModules.end()) {
            return it->second;
        }

        // Load new module
        loadingModules.push(name);
        auto module = std::make_shared<Module>(name);
        loadedModules[name] = module;

        module->load();
        loadDependencies(module);
        module->finalize();

        loadingModules.pop();
        return module;
    }

    // Dependency management
    void loadDependencies(std::shared_ptr<Module> module) {
        for (const auto& dep : module->getDependencies()) {
            auto depModule = loadModule(dep);
            module->addDependency(depModule);
        }
    }
};
```

## Symbol Resolution

### Symbol Table

```cpp
class SymbolTable {
private:
    struct Scope {
        std::unordered_map<std::string, Symbol> symbols;
        std::unordered_map<std::string, Using> usings;
        Scope* parent;
    };

    std::vector<Scope*> scopes;
    Scope* current;

public:
    // Scope management
    void enterScope() {
        auto newScope = new Scope{};
        newScope->parent = current;
        current = newScope;
        scopes.push_back(newScope);
    }

    void exitScope() {
        current = current->parent;
        delete scopes.back();
        scopes.pop_back();
    }

    // Symbol management
    void declare(const std::string& name, Symbol symbol) {
        current->symbols[name] = symbol;
    }

    Symbol lookup(const std::string& name) {
        for (auto scope = current; scope; scope = scope->parent) {
            // Check local symbols
            if (auto it = scope->symbols.find(name);
                it != scope->symbols.end()) {
                return it->second;
            }

            // Check using declarations
            for (const auto& [ns, using_] : scope->usings) {
                if (auto symbol = using_.lookup(name)) {
                    return symbol;
                }
            }
        }
        return Symbol{};  // Not found
    }
};
```

### Using Declaration Management

```cpp
class UsingDeclarationManager {
private:
    struct UsingInfo {
        std::string moduleName;
        std::string namespaceName;
        bool isWildcard;
    };

    std::vector<UsingInfo> activeUsings;
    ModuleLoader& moduleLoader;

public:
    // Using declaration handling
    void addUsing(const std::string& module,
                 const std::string& ns = "",
                 bool wildcard = false) {
        activeUsings.push_back({module, ns, wildcard});
    }

    Symbol resolveSymbol(const std::string& name) {
        for (const auto& using_ : activeUsings) {
            auto module = moduleLoader.getModule(using_.moduleName);
            if (using_.isWildcard) {
                if (auto symbol = module->lookupExport(name)) {
                    return symbol;
                }
            } else {
                if (auto symbol = module->lookupExport(
                        using_.namespaceName + "::" + name)) {
                    return symbol;
                }
            }
        }
        return Symbol{};
    }
};
```

## Cross-Module Type Checking

### Type Resolution

```cpp
class CrossModuleTypeResolver {
private:
    ModuleLoader& moduleLoader;
    TypeRegistry& typeRegistry;

public:
    // Type resolution across modules
    TypeInfo* resolveType(const std::string& name,
                         const std::string& currentModule) {
        // Check if type contains module qualification
        if (auto pos = name.find("::"); pos != std::string::npos) {
            auto moduleName = name.substr(0, pos);
            auto typeName = name.substr(pos + 2);

            auto module = moduleLoader.getModule(moduleName);
            return module->lookupType(typeName);
        }

        // Look in current module first
        auto currentModuleObj = moduleLoader.getModule(currentModule);
        if (auto type = currentModuleObj->lookupType(name)) {
            return type;
        }

        // Check imported modules
        for (const auto& import : currentModuleObj->getImports()) {
            auto importedModule = moduleLoader.getModule(import);
            if (auto type = importedModule->lookupType(name)) {
                return type;
            }
        }

        return nullptr;
    }
};
```

### Forward Declarations

```cpp
class ForwardDeclarationManager {
private:
    struct ForwardDecl {
        std::string name;
        TypeKind kind;
        std::vector<std::string> dependencies;
    };

    std::unordered_map<std::string, ForwardDecl> forwardDecls;
    ModuleLoader& moduleLoader;

public:
    // Forward declaration handling
    void addForwardDeclaration(const std::string& name,
                              TypeKind kind,
                              const std::vector<std::string>& deps) {
        forwardDecls[name] = {name, kind, deps};
    }

    bool resolveForwardDeclarations(Module* module) {
        bool allResolved = true;
        for (const auto& [name, decl] : forwardDecls) {
            bool canResolve = true;
            for (const auto& dep : decl.dependencies) {
                if (!moduleLoader.isTypeAvailable(dep)) {
                    canResolve = false;
                    break;
                }
            }

            if (canResolve) {
                module->finalizeType(name, decl.kind);
            } else {
                allResolved = false;
            }
        }
        return allResolved;
    }
};
```

## Module Interface Files

### Interface Parser

```cpp
class ModuleInterfaceParser {
private:
    ModuleLoader& moduleLoader;
    TypeRegistry& typeRegistry;

public:
    // Interface file parsing
    ModuleInterface parseInterface(const std::string& filename) {
        ModuleInterface interface;

        // Parse exports
        interface.exports = parseExports(filename);

        // Parse type declarations
        interface.types = parseTypes(filename);

        // Parse dependencies
        interface.dependencies = parseDependencies(filename);

        return interface;
    }

    // Validation
    bool validateImplementation(const ModuleInterface& interface,
                              const Module& implementation) {
        // Check all exports are implemented
        for (const auto& export_ : interface.exports) {
            if (!implementation.hasExport(export_.name)) {
                return false;
            }
        }

        // Check type compatibility
        for (const auto& type : interface.types) {
            auto implType = implementation.lookupType(type.name);
            if (!implType || !type.isCompatibleWith(implType)) {
                return false;
            }
        }

        return true;
    }
};
```

## Performance Considerations

### Module Caching

```cpp
class ModuleCache {
private:
    struct CacheEntry {
        std::shared_ptr<Module> module;
        std::filesystem::file_time_type lastModified;
    };

    std::unordered_map<std::string, CacheEntry> cache;

public:
    // Cache management
    std::shared_ptr<Module> getCachedModule(const std::string& name) {
        auto it = cache.find(name);
        if (it != cache.end()) {
            auto currentTime = std::filesystem::last_write_time(
                getModulePath(name));
            if (currentTime <= it->second.lastModified) {
                return it->second.module;
            }
        }
        return nullptr;
    }

    void cacheModule(const std::string& name,
                    std::shared_ptr<Module> module) {
        cache[name] = {
            module,
            std::filesystem::last_write_time(getModulePath(name))
        };
    }
};
```

### Lazy Loading

```cpp
class LazyModuleLoader {
private:
    ModuleCache& cache;
    std::unordered_map<std::string, ModuleInterface> interfaces;

public:
    // Lazy loading implementation
    std::shared_ptr<Module> getModule(const std::string& name) {
        // Check cache first
        if (auto cached = cache.getCachedModule(name)) {
            return cached;
        }

        // Load interface only initially
        if (interfaces.find(name) == interfaces.end()) {
            interfaces[name] = loadInterface(name);
        }

        // Only load full module when needed
        auto module = std::make_shared<Module>(name);
        module->loadFromInterface(interfaces[name]);
        cache.cacheModule(name, module);

        return module;
    }
};
```

## Next Steps

- Review [Error Handling Implementation](05-error-handling.md)
- Explore [Runtime Library Details](06-runtime-library.md)
- Understand [Reflection System](07-reflection-system.md)
