# Getting Started with Pryst

## Overview

Pryst is a modern programming language that combines the elegance of TypeScript with the performance of C++. It features strong static typing, module support, and powerful error handling capabilities.

## Installation

```bash
# Clone the repository
git clone https://github.com/cliid/pryst
cd pryst

# Build the project
./build.sh
```

## Language Basics

### Variables and Types

```pryst
// Type inference
let x = 42;              // int
let pi = 3.14159;       // float
let name = "Alice";     // str
let active = true;      // bool

// Explicit typing
int y = 10;
float radius = 5.0;
str message = "Hello";
bool isValid = false;

// Constants
const MAX_SIZE = 100;           // Inferred type
const PI = 3.14159;            // Inferred type
const! COMPILE_TIME = 42;      // Compile-time constant
```

### Functions

```pryst
// Arrow syntax for function types
fn add(int a, int b) -> int {
    return a + b;
}

// Type inference for return type
fn multiply(int x, int y) {
    return x * y;
}

// Lambda functions with arrow syntax
let square = (int x) -> int { return x * x; };
let double = (x) -> { return x * 2; };
```

### Classes and Objects

```pryst
class Point {
    float x;
    float y;

    Point(float x, float y) {
        this.x = x;
        this.y = y;
    }

    fn distance(Point other) -> float {
        let dx = this.x - other.x;
        let dy = this.y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
}

// Creating objects using 'new'
let p1 = new Point(0.0, 0.0);
let p2 = new Point(3.0, 4.0);
let dist = p1.distance(p2);
```

### Modules and Imports

```pryst
// Importing modules
import math::geometry;
import utils::strings;

// Using declarations for shorter access
using namespace math;
let area = calculateArea(5.0);

// Fully qualified access
let color = new graphics::utils::Color(255, 0, 0);
```

### Error Handling

```pryst
// Try-catch blocks
try {
    let result = riskyOperation();
} catch (NetworkError e) {
    print("Network error: ${e.message}");
} catch (ValidationError e) {
    print("Validation error: ${e.message}");
} catch {
    print("Unknown error occurred");
}

// Result type for error handling
fn divide(int x, int y) -> Result<int> {
    if (y == 0) {
        return Result.error("Division by zero");
    }
    return Result.ok(x / y);
}
```

### String Interpolation

```pryst
let name = "Alice";
let age = 30;
print("Hello, ${name}! You are ${age} years old.");

// Expression interpolation
let x = 10;
let y = 20;
print("Sum of ${x} and ${y} is ${x + y}");
```

## Type System Highlights

- Strong static typing with type inference
- First-class functions with type safety
- Generic types with constraints
- Module-aware type resolution
- Safe type conversions

## Best Practices

1. Use type inference for local variables
2. Prefer arrow syntax for lambda functions
3. Use explicit typing for function parameters
4. Leverage the module system for code organization
5. Handle errors appropriately using try-catch or Result

## Next Steps

- Learn about the [Type System](02-type-system.md)
- Explore [Modules](03-modules.md)
- Understand [Error Handling](04-error-handling.md)
- Read about [Classes and Objects](05-classes.md)
