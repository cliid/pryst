---
sidebar_position: 1
---

# Introduction to Pryst

Pryst is a modern programming language that combines the performance of C++ with the elegance of TypeScript. It features strong static typing, first-class functions, and a powerful module system.

## Key Features

- **Strong Static Typing**: All types are checked at compile time
- **Modern Syntax**: Clean, expressive syntax with type inference
- **Module System**: TypeScript-style module management
- **First-class Functions**: Support for lambda expressions and closures
- **String Interpolation**: Seamless string formatting with `${expression}` syntax
- **Type Conversion**: Flexible type conversion system with class support
- **Error Handling**: C++-style try-catch mechanism

## Basic Syntax

### Variables and Constants

```pryst
// Type inference with 'let'
let x = 42;

// Explicit typing
int y = 23;

// Constants with type inference
const pi = 3.14159;

// Compile-time constants
const! maxSize = 1000;

// Constants with explicit type
const float epsilon = 0.00001;
```

### Functions

```pryst
// Arrow syntax for lambda functions
let add = (int x, int y) -> int {
    return x + y;
};

// Named functions
fn add(int x, int y) -> int {
    return x + y;
}

// Function with multiple parameters
fn multiply(int x, int y) -> int {
    return x * y;
}
```

### Modules and Imports

```pryst
// Importing modules
import pryst::web;
import pryst::math::vector;

// Using declarations
using namespace pryst;
using module web;

// Module definition
module math {
    fn sqrt(float x) -> float {
        // Implementation
    }
}

```

### String Interpolation

```pryst
let name = "World";
let count = 42;

// Simple identifier interpolation
print("Hello ${name}!");

// Expression interpolation
print("The answer is ${count * 2}");
```

### Type Conversion

```pryst
// Type conversion examples
int(someFloat)    // Convert float to int
str(someInt)      // Convert int to string
float(someInt)    // Convert int to float

// Class conversion using constructor
MyClass(someValue)    // Convert value to MyClass type
```

### Error Handling

```pryst
try {
    // Code that might throw
    riskyOperation();
} catch (Error e) {
    // Handle error
    print("Error: ${e}");
}
```

## Next Steps

- Learn about the [Type System](02-type-system.md)
- Explore [Modules and Namespaces](03-modules.md)
- Understand [Functions and Lambdas](04-functions.md)
- Master [Classes and Objects](05-classes.md)
