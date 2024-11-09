---
sidebar_position: 2
---

# Modules

## Module System Implementation

### Module Loader

The module loader handles resolution and loading of Pryst modules:

```cpp
class ModuleLoader {
    // Resolves module paths and loads module contents
    fn resolveModule(str modulePath) -> Module;

    // Handles interface file loading and validation
    fn loadInterface(str interfacePath) -> ModuleInterface;

    // Manages module dependencies
    fn validateDependencies(Module mod) -> bool;
}
```

### Interface Files (.psti)

Interface files define the public API of a module:

```pryst
// math.psti
module math {
    // Public type declarations
    class Vector2D;

    // Function declarations with full signatures
    fn<float> sqrt(float x);
    fn<Vector2D> normalize(Vector2D vec);

    // Forward declarations for cross-module references
    declare fn transform(graphics::Transform t) -> Vector2D;
}
```

### Type Registry Integration

Modules interact with the type registry for type checking and resolution:

```cpp
class ModuleTypeRegistry {
    // Register types from interface files
    fn registerInterfaceTypes(ModuleInterface interface);

    // Validate type compatibility across modules
    fn validateTypeCompatibility(Type declared, Type implemented) -> bool;

    // Handle forward-declared types
    fn resolveForwardDeclaration(str typeName, Module context) -> Type;
}
```

## Module Features

### Symbol Resolution

The module system implements hierarchical symbol resolution:

```cpp
class SymbolResolver {
    // Resolve fully qualified names
    fn resolveQualifiedName(str qualifiedName) -> Symbol;

    // Handle using declarations
    fn applyUsingDeclaration(str modulePath, Scope targetScope);

    // Manage symbol visibility
    fn checkSymbolVisibility(Symbol sym, Module from, Module to) -> bool;
}
```

### Forward Declarations

Forward declarations allow cross-module references:

```pryst
// parser.psti
module parser {
    // Forward declare type from another module
    declare class ast::Node;

    // Function using forward-declared type
    fn<ast::Node> parse(str input);
}

// Implementation must import the actual type
module parser {
    import ast;

    fn<ast::Node> parse(str input) -> ast::Node {
        // Implementation with actual ast::Node type
    }
}
```

### Type Checking

The module system enforces strict type checking:

```cpp
class ModuleTypeChecker {
    // Verify interface implementation
    fn validateImplementation(ModuleInterface iface, Module impl) -> bool;

    // Check type compatibility across modules
    fn checkTypeCompatibility(Type source, Type target) -> bool;

    // Validate forward declaration resolution
    fn validateForwardDeclarations(Module mod) -> bool;
}
```

## Best Practices

1. **Module Organization**
   - Keep related functionality together
   - Use meaningful namespace hierarchies
   - Maintain clear module boundaries

2. **Interface Design**
   - Define clear public APIs in .psti files
   - Document type constraints and requirements
   - Consider cross-module dependencies

3. **Type Safety**
   - Use explicit forward declarations
   - Validate type compatibility at module boundaries
   - Handle cross-module type resolution carefully

## Common Implementation Patterns

### Module Resolution

```cpp
// Example module resolution implementation
class ModuleResolver {
    // Find module by path
    fn findModule(str path) -> Module {
        // Search in project directories
        // Handle nested modules
        // Resolve dependencies
    }

    // Load and validate interface
    fn loadInterface(str path) -> ModuleInterface {
        // Parse .psti file
        // Extract public API
        // Validate declarations
    }
}
```

### Type Registration

```cpp
// Example type registration in modules
class ModuleTypeRegistrar {
    // Register module types
    fn registerTypes(Module mod) {
        // Add to type registry
        // Handle forward declarations
        // Validate type constraints
    }

    // Validate type compatibility
    fn validateTypes(Module mod) -> bool {
        // Check interface compliance
        // Verify type signatures
        // Ensure proper implementation
    }
}
```

## Next Steps

- Learn about [Error Handling](03-error-handling.md)
- Explore [Type System](04-type-system.md)
- Understand [Reflection API](05-reflection.md)
