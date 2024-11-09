---
sidebar_position: 2
---

# Type System

Pryst features a robust type system that combines static typing with modern features like type inference, first-class functions, and safe type conversions.

## Basic Types

### Primitive Types

- `int`: Integer numbers
- `float`: Floating-point numbers
- `bool`: Boolean values (`true` or `false`)
- `str`: String values
- `void`: Represents no value
- `any`: Dynamic type for flexible typing

### Variable Declarations

Pryst supports two forms of variable declaration:

```pryst
// Type inference using 'let'
let x = 42;        // Inferred as int
let y = 3.14;      // Inferred as float
let z = "Hello";   // Inferred as str
let w = true;      // Inferred as bool

// Explicit type declaration
int a = 42;
float b = 3.14;
str c = "Hello";
bool d = true;
```

### Constants

Three forms of constant declarations:

```pryst
const pi = 3.14159;           // Type-inferred constant
const! maxSize = 1000;        // Compile-time constant
float const epsilon = 0.0001; // Typed constant
```

## Class Types

In Pryst, class names are directly used as types:

```pryst
class Person {
    str name;
    int age;
}

// Using Person directly as a type
Person alice = new Person("Alice", 30);
let bob = new Person("Bob", 25);  // Type inference works with classes too
```

## Functions as First-Class Citizens

Functions in Pryst are first-class citizens, supporting a consistent arrow syntax while maintaining strict type inference:

```pryst
// Function declarations using arrow syntax
let add = (int x, int y) -> int {
    return x + y;
};

// Lambda function with arrow syntax
let addLambda = (int x, int y) -> int {
    return x + y;
};

// Lambda with type inference
let multiply = (int x, int y) -> int {
    return x * y;
};

// Function type inference is strict
let operation = add;              // Type inferred as (int, int) -> int
let operations = [add, multiply]; // Type inferred as ((int, int) -> int)[]

// Mixed function array uses widened parameter types
let mixed = [
    (int x) -> int { return x + 1; },
    (float x) -> int { return int(x); }
]; // Type inferred as ((any*) -> int)[]

// Module function access
let pi = math::pi;               // Fully qualified access
let color = new graphics::utils::Color();

// Using declaration for shorter access
using namespace math;
let root = sqrt(16.0);
```

## Function Types and Forward Declarations

### Declaration Order and Type Checking

In Pryst, all functions must be declared before use. Since Pryst has no pointers or references, mutual recursion requires explicit forward declarations:

```pryst
// Forward declarations for mutual recursion
declare let isEven = (int n) -> bool;
declare let isOdd = (int n) -> bool;

// Implementations must match declarations exactly
let isEven = (int n) -> bool {
    if (n == 0) return true;
    return isOdd(n - 1);
};

let isOdd = (int n) -> bool {
    if (n == 0) return false;
    return isEven(n - 1);
};
```

### Type Checking Rules for Forward Declarations

1. **Signature Matching**
   - Return type must match exactly
   - Parameter types must match exactly
   - Parameter names may differ
   - Generic type parameters must match

2. **Implementation Requirements**
   - Every forward declaration must have exactly one implementation
   - Implementation must be in the same scope or module
   - No overloading of forward-declared functions

3. **Lambda Functions and Forward Declarations**
```pryst
// Forward declarations for mutually recursive lambdas
declare let foo = (int x, int y) -> int;
declare let bar = (int z) -> int;

// Lambda implementations
let foo = (int x, int y) -> int {
    return bar(x * y);
};

let bar = (int z) -> int {
    return foo(z, z - 1);
};
```

### Function Type Compatibility

Functions in Pryst follow these type compatibility rules:
1. Function types are invariant in parameter types
2. Function types are covariant in return type
3. Mixed function arrays use `((any*) -> ReturnType)[]` type
4. Forward-declared functions must maintain exact type matches
5. Lambda type inference follows the same rules as regular functions

Example of type compatibility:
```pryst
// Base class and derived class
class Animal {}
class Dog extends Animal {}

// Function type compatibility
let baseHandler = (Animal a) -> Animal { return a; };
let derivedHandler = (Dog d) -> Dog { return d; };

// Error: Parameter types must match exactly
baseHandler = derivedHandler;  // Type error

// OK: Return type can be more specific
let handler = (Dog d) -> Animal { return d; };
```

### Generic Functions

```pryst
// Generic class
class List<T> {
    T[] items;

    void add(T item) {
        // Implementation
    }
}

List<int> numbers = new List<int>();
List<str> names = new List<str>();

// Generic function
let first = <T>(T[] array) -> T {
    return array[0];
};
```

## Type Conversions

### Primitive Type Conversions

```pryst
// Constructor syntax (preferred)
let f = float(42);        // int to float;
let s = str(3.14);        // float to string;
let b = bool(1);          // int to bool;

// More constructor syntax examples
let i = int(3.14);        // float to int;
let str_val = str(true);  // bool to string;
```

### Class Conversions

```pryst
class Vector2D {
    float x;
    float y;

    // Constructor for conversion
    Vector2D(str s) {
        // Parse string to create vector
    }
}

```pryst
// Using constructor syntax consistently
let v = new Vector2D("1,2");     // Constructor with new;
let v2 = Vector2D("1,2");        // Constructor syntax for conversion;
```

## Type Safety

Pryst enforces strict type safety:

```pryst
let x = 42;
let y = "Hello";

// Error: Cannot add int and str
let z = x + y;  // Compilation error

// Must explicitly convert
let z = str(x) + y;  // OK: "42Hello"

// Using any type for dynamic typing
any dynamic = 42;
dynamic = "Hello";    // OK: any type can change
```

## Arrays and Collections

Array types use square bracket notation:

```pryst
// Array declarations
int[] numbers = [1, 2, 3];
str[] names = ["Alice", "Bob"];

// Multidimensional arrays
int[][] matrix = [[1, 2], [3, 4]];

// With type inference
let moreNumbers = [1, 2, 3];  // Inferred as int[]
```

## Next Steps

- Learn about [Modules and Namespaces](03-modules.md)
- Explore [Functions and Lambdas](04-functions.md)
- Understand [Classes and Objects](05-classes.md)
