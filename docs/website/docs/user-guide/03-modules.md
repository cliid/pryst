# Modules

## Overview

Pryst's module system provides a powerful way to organize code and manage dependencies. It supports nested namespaces, visibility control, and flexible import mechanisms.

## Module Basics

### Creating Modules

```pryst
// math/geometry.pst
module math::geometry {
    const PI = 3.14159;

    fn calculateArea(float radius) -> float {
        return PI * radius * radius;
    }

    fn calculatePerimeter(float radius) -> float {
        return 2.0 * PI * radius;
    }
}

// graphics/color.pst
module graphics::utils {
    class Color {
        int r;
        int g;
        int b;

        Color(int r, int g, int b) {
            this.r = r;
            this.g = g;
            this.b = b;
        }

        fn toHex() -> str {
            return "#${r:02x}${g:02x}${b:02x}";
        }
    }
}
```

### Importing Modules

```pryst
// Importing specific modules
import math::geometry;
import graphics::utils;

// Using declarations
using namespace math;
let area = calculateArea(5.0);

// Fully qualified access
let color = new graphics::utils::Color(255, 0, 0);
```

## Module Features

### Nested Namespaces

```pryst
// Defining nested modules
module app::utils::strings {
    fn capitalize(str text) -> str {
        // Implementation
    }
}

module app::utils::numbers {
    fn format(float value, int decimals) -> str {
        // Implementation
    }
}

// Using nested modules
import app::utils::strings;
import app::utils::numbers;

let text = strings::capitalize("hello");
let formatted = numbers::format(3.14159, 2);
```

### Visibility Control

```pryst
module math {
    // Public - accessible from outside
    public fn add(int a, int b) -> int {
        return a + b;
    }

    // Private - only accessible within module
    private fn validate(int x) -> bool {
        return x >= 0;
    }

    // Internal - accessible within the same package
    internal class Helper {
        // Implementation
    }
}
```

### Module Interfaces

```pryst
// geometry.psti (interface file)
interface math::geometry {
    fn calculateArea(float radius) -> float;
    fn calculatePerimeter(float radius) -> float;
}

// geometry.pst (implementation)
module math::geometry {
    const PI = 3.14159;

    fn calculateArea(float radius) -> float {
        return PI * radius * radius;
    }

    fn calculatePerimeter(float radius) -> float {
        return 2.0 * PI * radius;
    }
}
```

## Best Practices

### Module Organization

```pryst
// Recommended module structure
module company::project::feature {
    // Public interface
    public class API {
        // Public methods
    }

    // Internal implementation
    internal class Implementation {
        // Internal details
    }

    // Private helpers
    private fn helperFunction() {
        // Helper code
    }
}
```

### Import Management

```pryst
// Preferred import style
import math::geometry;          // Import specific module
import graphics::utils::Color;  // Import specific type

// Block-level using declarations
fn someFunction() {
    using namespace math;
    // math functions available without qualification
    let area = calculateArea(5.0);
}
```

### Forward Declarations

```pryst
// Forward declaring types
declare class Future;
declare fn process(Future value) -> int;

// Forward declaring modules
declare module utils::async;
```

## Common Patterns

### Module Initialization

```pryst
module app::config {
    // Module initialization code
    init {
        loadConfiguration();
        setupDefaults();
    }

    private fn loadConfiguration() {
        // Load config
    }

    private fn setupDefaults() {
        // Setup defaults
    }
}
```

### Cross-Module Communication

```pryst
// events.pst
module app::events {
    class EventBus {
        // Event handling implementation
    }
}

// subscriber.pst
module app::subscriber {
    import app::events;

    class Subscriber {
        events::EventBus bus;

        fn onEvent(str event) {
            // Handle event
        }
    }
}
```

## Next Steps

- Explore [Error Handling](04-error-handling.md)
- Learn about [Classes and Objects](05-classes.md)
- Understand [Reflection](06-reflection.md)
