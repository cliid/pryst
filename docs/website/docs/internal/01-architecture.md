# Pryst Compiler Architecture

## Overview

The Pryst compiler is built using LLVM 20.0.0 and ANTLR 4.13.2, implementing a modern compiler pipeline with strong type checking and efficient code generation. This document details the internal architecture and implementation decisions.

## Component Overview

```
pryst/
├── src/
│   ├── codegen/          # LLVM IR generation
│   ├── semantic/         # Type checking and analysis
│   ├── diagnostic/       # Error reporting
│   ├── utils/           # Shared utilities
│   └── runtime/         # Runtime support
```

## Core Components

### Type Registry

The TypeRegistry system manages all type information and handles LLVM 20.0.0's opaque pointer requirements:

```cpp
class TypeRegistry {
private:
    // Internal type storage
    std::unordered_map<std::string, std::unique_ptr<TypeInfo>> types;
    llvm::LLVMContext& context;

public:
    // Type creation and management
    llvm::Type* createPointerType();  // Creates opaque pointer type
    llvm::Type* getTypeFromTypeInfo(const TypeInfo& info);

    // Type registration
    void registerType(std::string name, std::unique_ptr<TypeInfo> type);
    TypeInfo* lookupType(const std::string& name);

    // Special type handling
    llvm::Type* getOpaquePointerType();
    bool isOpaquePointer(llvm::Type* type);
};
```

Key implementation notes:
- All pointers are treated as opaque in LLVM 20.0.0
- Type information is maintained separately from LLVM types
- Custom type resolution system for handling cross-module types

### Module System

The module system implements TypeScript-style module management:

```cpp
class ModuleLoader {
private:
    // Module cache and management
    std::unordered_map<std::string, std::shared_ptr<Module>> loadedModules;
    SymbolTable globalSymbols;
    std::vector<std::string> modulePath;

public:
    // Module loading and resolution
    std::shared_ptr<Module> loadModule(const std::string& name);
    void resolveImports(Module& module);

    // Symbol management
    bool resolveSymbol(const std::string& name, const std::string& currentModule);
    void registerExport(const std::string& name, Symbol symbol);
};
```

Implementation details:
- Modules are loaded lazily on first import
- Symbol resolution handles nested namespaces
- Cross-module type checking ensures type safety

### Semantic Analysis

The semantic analyzer performs type checking and validation:

```cpp
class SemanticAnalyzer {
private:
    TypeRegistry& typeRegistry;
    ModuleLoader& moduleLoader;
    ScopeManager scopeManager;
    DiagnosticCollector& diagnostics;

public:
    // Analysis methods
    void checkTypes(Expression* expr);
    void validateModuleImports(Module* module);
    void resolveTypeReferences(TypeInfo* type);

    // Scope handling
    void enterScope();
    void exitScope();
    void declareSymbol(const std::string& name, Symbol symbol);
};
```

Key features:
- Strong type checking across module boundaries
- Scope-based symbol resolution
- Forward declaration support

### Code Generation

The code generator produces LLVM IR:

```cpp
class LLVMCodeGenerator {
private:
    llvm::LLVMContext& context;
    std::unique_ptr<llvm::Module> module;
    TypeRegistry& typeRegistry;

public:
    // Code generation methods
    llvm::Value* generateExpression(Expression* expr);
    llvm::Function* generateFunction(FunctionDecl* func);

    // Type handling
    llvm::Type* getLLVMType(TypeInfo* type);
    llvm::Value* createAlloca(llvm::Type* type, const std::string& name);
};
```

Important considerations:
- LLVM 20.0.0 compatibility requires using opaque pointers
- No direct use of getPointerElementType() or similar deprecated APIs
- Efficient code generation strategies

## Type System Implementation

### Type Resolution

```cpp
class TypeResolver {
public:
    // Type inference and checking
    TypeInfo* inferType(Expression* expr);
    bool isCompatible(TypeInfo* source, TypeInfo* target);
    TypeInfo* getCommonType(TypeInfo* a, TypeInfo* b);

    // Type conversion
    bool canConvert(TypeInfo* from, TypeInfo* to);
    llvm::Value* generateConversion(llvm::Value* value, TypeInfo* from, TypeInfo* to);
};
```

Type system features:
- Strong static typing
- Type inference with constraints
- Safe type conversions

### Error Handling

```cpp
class DiagnosticCollector {
private:
    std::vector<Diagnostic> diagnostics;
    bool hasErrors;

public:
    // Error reporting
    void reportError(const std::string& message, SourceLocation loc);
    void reportWarning(const std::string& message, SourceLocation loc);

    // Error management
    bool hasAnyErrors() const;
    const std::vector<Diagnostic>& getDiagnostics() const;
};
```

Error handling features:
- Detailed error messages
- Source location tracking
- Multiple error collection

## Build System

The build system uses CMake with specific configurations:

```cmake
# CMake configuration
cmake_minimum_required(VERSION 3.10)
project(Pryst)

# LLVM configuration
set(LLVM_DIR "/usr/lib/llvm-20/cmake")
find_package(LLVM 20.0.0 REQUIRED CONFIG)

# ANTLR configuration
find_package(ANTLR REQUIRED)
set(ANTLR_JAR_LOCATION "/usr/share/java/antlr-4.13.2-complete.jar")

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

Build requirements:
- LLVM 20.0.0
- ANTLR 4.13.2
- CMake 3.10+

## Development Guidelines

### Code Style

```cpp
// Class naming
class PascalCase {};

// Function naming
void camelCase();

// Constants
const int UPPER_CASE = 42;

// Member variables
class Example {
    int m_memberVariable;
    std::string m_name;
};
```

### Error Handling Strategy

```cpp
// Error propagation
Result<Value*> processExpression(Expression* expr) {
    if (!expr) {
        return Result<Value*>::error("Null expression");
    }

    try {
        auto result = evaluateExpression(expr);
        return Result<Value*>::ok(result);
    } catch (const CompilerError& e) {
        return Result<Value*>::error(e.what());
    }
}
```

### Testing Approach

```cpp
// Unit test structure
void testTypeInference() {
    // Arrange
    TypeRegistry registry;
    auto expr = createTestExpression();

    // Act
    TypeInfo* type = registry.inferType(expr);

    // Assert
    ASSERT_EQ(type->getKind(), TypeKind::Integer);
    ASSERT_TRUE(type->isComplete());
}
```

## Performance Considerations

### Memory Management

```cpp
// Smart pointer usage
class Manager {
    std::unique_ptr<Resource> resource;
    std::shared_ptr<Cache> cache;

    void processResource() {
        // Resource automatically cleaned up
        resource = std::make_unique<Resource>();
        // Cache shared between components
        cache = std::make_shared<Cache>();
    }
};
```

### Optimization Strategies

```cpp
// LLVM optimization passes
void addOptimizationPasses(llvm::PassManager& pm) {
    // Essential optimizations
    pm.add(llvm::createPromoteMemoryToRegisterPass());
    pm.add(llvm::createInstructionCombiningPass());
    pm.add(llvm::createReassociatePass());

    // Advanced optimizations
    pm.add(llvm::createGVNPass());
    pm.add(llvm::createCFGSimplificationPass());
}
```

## Next Steps

- Review [Type System Internals](02-type-system-internals.md)
- Explore [Code Generation Details](03-code-generation.md)
- Understand [Module System Implementation](04-module-system.md)
