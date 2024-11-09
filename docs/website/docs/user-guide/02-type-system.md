# Type System

## Overview

Pryst features a strong, static type system that combines compile-time safety with flexible type inference. The type system supports both primitive types and user-defined types, with comprehensive support for generics and type conversions.

## Primitive Types

```pryst
// Integer types
int x = 42;
int8 small = 127;
int16 medium = 32767;
int32 large = 2147483647;
int64 huge = 9223372036854775807;

// Floating-point types
float f = 3.14159;
float32 f32 = 3.14;
float64 f64 = 3.14159265359;

// Other primitives
bool flag = true;
str text = "Hello";
char c = 'A';
```

## Type Inference

```pryst
// Local variable type inference
let x = 42;              // Inferred as int
let pi = 3.14159;       // Inferred as float
let name = "Alice";     // Inferred as str
let active = true;      // Inferred as bool

// Function return type inference
fn add(int a, int b) {
    return a + b;       // Return type inferred as int
}

// Lambda type inference
let double = (x) -> { return x * 2; };  // Parameter and return types inferred
```

## Type Conversions

```pryst
// Implicit conversions (safe)
int x = 42;
float y = x;            // int to float is safe

// Explicit conversions required
float f = 3.14;
int i = int(f);         // Explicit conversion required
str s = str(i);         // Converting to string

// Class conversions
class Point2D {
    float x;
    float y;
}

class Point3D {
    float x;
    float y;
    float z;

    // Conversion constructor
    Point3D(Point2D p) {
        this.x = p.x;
        this.y = p.y;
        this.z = 0.0;
    }
}

let p2d = new Point2D(1.0, 2.0);
let p3d = new Point3D(p2d);    // Using conversion constructor
```

## Generic Types

```pryst
// Generic class
class Box<T> {
    T value;

    Box(T value) {
        this.value = value;
    }

    fn get() -> T {
        return this.value;
    }
}

// Using generic types
let intBox = new Box<int>(42);
let strBox = new Box<str>("Hello");

// Generic function
fn swap<T>(T a, T b) -> (T, T) {
    return (b, a);
}

// Type constraints
fn sum<T: Number>(T a, T b) -> T {
    return a + b;
}
```

## Function Types

```pryst
// Function type declarations
fn<int, int> -> int callback;              // Function type variable
fn<str> -> void printer;                   // Function taking string, returning void

// Using function types
callback = (int x) -> int { return x * 2; };
printer = (str msg) -> void { print(msg); };

// Higher-order functions
fn apply(fn<int> -> int f, int value) -> int {
    return f(value);
}
```

## Type Safety Features

### Null Safety

```pryst
// Optional types
int? nullable = null;
str? optional = "Hello";

// Safe access
if (optional != null) {
    print(optional);
}

// Elvis operator
let length = optional?.length ?? 0;
```

### Type Assertions

```pryst
// Type checking
if (value is int) {
    let number = value as int;
    print("Got number: ${number}");
}

// Safe casting
let result = value as? int;  // Returns null if cast fails
```

## Best Practices

1. Use type inference for local variables when types are obvious
2. Explicitly declare types for function parameters and class members
3. Prefer explicit conversions over implicit ones for clarity
4. Use generic constraints to enforce type requirements
5. Leverage the type system for compile-time safety

## Common Patterns

### Type-Safe Collections

```pryst
// Generic collections
let numbers = new List<int>();
let nameMap = new Map<str, Person>();

// Type-safe iteration
for (int num in numbers) {
    print(num);
}
```

### Type-Safe Error Handling

```pryst
// Result type for error handling
fn divide(int x, int y) -> Result<int> {
    if (y == 0) {
        return Result.error("Division by zero");
    }
    return Result.ok(x / y);
}

// Using Results
let result = divide(10, 2);
if (result.isOk()) {
    print("Result: ${result.unwrap()}");
}
```

## Next Steps

- Learn about [Modules](03-modules.md)
- Explore [Classes and Objects](05-classes.md)
- Understand [Error Handling](04-error-handling.md)
