---
sidebar_position: 3
---

# Modules and Namespaces

Pryst implements a modern module system inspired by TypeScript, allowing for clean code organization and efficient dependency management.

## Module System

### Basic Module Structure

```pryst
// Define a module
module math {
    // Module contents
    fn pi() -> float {
        return 3.14159;
    }

    fn sqrt(float x) -> float {
        // Implementation
    }
}
```

### Nested Modules

```pryst
module graphics {
    module rendering {
        module shaders {
            // Deeply nested module
        }
    }
}
```

## Importing Modules

### Basic Imports

```pryst
// Import a specific module
import pryst::web;

// Import nested modules
import pryst::graphics::rendering;

// Import multiple modules
import pryst::math;
import pryst::utils::string;
```

### Using Declarations

```pryst
// Using namespace at file level
using namespace pryst;

// Using module at file level
using module web;

// Block-scoped using declarations
{
    using namespace math;
    using module vector;
    // Declarations only valid in this block
}
```

## Namespaces

### Declaring Namespaces

```pryst
namespace math {
    const pi = 3.14159;

    fn sqrt(float x) -> float {
        // Implementation
    }
}
```

### Nested Namespaces

```pryst
namespace graphics {
    namespace utils {
        class Color {
            // Color implementation
        }
    }
}
```

### Accessing Namespace Members

```pryst
// Fully qualified access
let pi = math::pi;
let color = graphics::utils::Color();

// Using declaration for shorter access
using namespace math;
let root = sqrt(16.0);
```

## Module Interface Files

Interface files (`.psti`) define the public API of a module:

```pryst
// math.psti - interface file
module math {
    // Public interface declarations
    fn sqrt(float x) -> float;
    fn pow(float base, float exp) -> float;

    // Forward declarations are allowed in interfaces
    declare fn complexCalculation(float x) -> float;
}

// math.pst - implementation
module math {
    // Implementation details
    fn sqrt(float x) -> float {
        // Implementation
    }

    fn pow(float base, float exp) -> float {
        // Implementation
    }

    // Must implement all interface declarations
    fn complexCalculation(float x) -> float {
        // Implementation
    }

    // Private function (not in interface)
    fn helper(float x) -> float {
        // Implementation
    }
}

### Type Checking Across Modules

When importing modules, Pryst enforces strict type checking:

```pryst
// graphics.psti
module graphics {
    class Color {
        fn toString() -> str;
    }
}

// main.pst
import graphics;

// Type checking ensures compatibility
let color = new graphics::Color();
str description = color.toString();  // Type checked against interface
```

### Forward Declarations in Modules

Forward declarations can span module boundaries:

```pryst
// parser.psti
module parser {
    declare fn parse(str input) -> ast::Node;
}

// ast.psti
module ast {
    class Node {
        // Node implementation
    }
}

// parser.pst
import ast;

module parser {
    fn parse(str input) -> ast::Node {
        // Implementation using ast::Node
    }
}
```

### Module Resolution Rules

1. **Import Resolution**
   - Modules are resolved relative to the project root
   - Interface files must match implementation files
   - Circular dependencies are not allowed

2. **Type Visibility**
   - Types declared in interfaces are public
   - Implementation-only types are private
   - Forward declarations must be resolved within the module system

3. **Implementation Requirements**
   - All interface members must be implemented
   - Implementation signatures must match exactly
   - Private members cannot be accessed outside the module

## Best Practices

1. **Module Organization**
   - One module per file
   - Module name should match file name
   - Use nested modules for logical grouping

2. **Namespace Usage**
   - Use namespaces for logical grouping
   - Keep namespace names descriptive
   - Avoid deeply nested namespaces

3. **Import Management**
   - Import only what you need
   - Use block-scoped using declarations
   - Prefer explicit imports over wildcard imports

## Common Patterns

### Factory Pattern

```pryst
module shapes {
    class Shape {
        // Base shape implementation
    }

    module factory {
        fn create(str type) -> Shape {
            // Factory implementation
        }
    }
}
```

### Service Pattern

```pryst
module services {
    class Logger {
        // Logger implementation
    }

    module provider {
        static Logger instance;

        fn get() -> Logger {
            // Service provider implementation
        }
    }
}
```

## Next Steps

- Learn about [Functions and Lambdas](04-functions.md)
- Explore [Classes and Objects](05-classes.md)
- Understand [Error Handling](06-error-handling.md)
