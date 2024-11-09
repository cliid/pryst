---
sidebar_position: 4
---

# Functions and Lambdas

Pryst provides a flexible and powerful function system that supports both traditional named functions and modern lambda expressions.

## Function Declarations

### Basic Functions

```pryst
// Basic function with return type
fn add(int x, int y) -> int {
    return x + y;
}

// Function with arrow syntax
fn multiply(int x, int y) -> int {
    return x * y;
}

// Void function
fn printMessage(str message) -> void {
    print(message);
}

### Forward Declarations

Pryst supports forward declarations to enable mutual recursion and better code organization:

```pryst
// Forward declaration
declare fn fibonacci(int n) -> int;

// Implementation
fn fibonacci(int n) -> int {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
```

### Mutual Recursion

Forward declarations enable mutual recursion between functions:

```pryst
declare fn isEven(int n) -> bool;
declare fn isOdd(int n) -> bool;

fn isEven(int n) -> bool {
    if (n == 0) return true;
    return isOdd(n - 1);
}

fn isOdd(int n) -> bool {
    if (n == 0) return false;
    return isEven(n - 1);
}
```

Important rules for forward declarations:
- Functions must be declared before use
- Forward declarations must be at the top level of a scope
- Implementation must match the forward declaration exactly
- No function hoisting is supported

### Type Inference

```pryst
// Return type inference
fn calculate(float x, float y) {
    return x * y;  // Returns float
}

// Parameter type inference with let
fn process(let x, let y) {
    // Types inferred from context
}
```

## Lambda Functions

### Basic Lambda Syntax

```pryst
// Lambda with type inference (preferred style)
(x, y) -> x + y

// Lambda with explicit types (when needed)
(int x, int y) -> int {
    return x + y;
}

// Multi-line lambda with type inference
(x, y) -> {
    let result = x * y;
    return result;
}
```

### Capturing Variables

```pryst
let multiplier = 2;

// Capture by reference
let double = (x) -> x * multiplier;

// Explicit capture list
let triple = [multiplier](x) -> x * multiplier;
```

## Function Types

### Declaring Function Types

```pryst
// Function type declarations
let callback: (int, int) -> int;

// Arrow syntax for function types
let operation: (int, int) -> int;

// Higher-order function type
let higherOrder: (int) -> ((int) -> int);
```

### Using Function Types

```pryst
// Function as parameter
fn processItems(int[] items, (int) -> void processor) -> void {
    for (let item in items) {
        processor(item);
    }
}

// Function as return value
fn makeMultiplier(int factor) -> ((int) -> int) {
    return (x) -> x * factor;  // Return type inferred from context
}
```

## Generic Functions

```pryst
// Generic function declaration
fn map<T>(T[] array, (T) -> T transformer) -> T[] {
    let result: T[] = [];
    for (let item in array) {
        result.push(transformer(item));
    }
    return result;
}

// Using generic functions
let numbers = [1, 2, 3];
let doubled = map(numbers, (x) -> x * 2);  // Type inference handles the rest
```

## Function Overloading

```pryst
// Overloaded functions
fn process(int value) -> int {
    return value * 2;
}

fn process(float value) -> float {
    return value * 2.0;
}

fn process(str value) -> str {
    return value + value;
}
```

## Best Practices

1. **Function Naming**
   - Use descriptive verb-noun combinations
   - Follow camelCase convention
   - Be consistent with naming patterns

2. **Parameter Design**
   - Keep parameter count low
   - Use meaningful parameter names
   - Consider using option objects for many parameters

3. **Lambda Usage**
   - Use type inference by default for lambdas
   - Add explicit types only when necessary for clarity
   - Keep lambdas focused and concise
   - Be mindful of variable capture scope

4. **Forward Declarations**
   - Use forward declarations for mutual recursion
   - Place declarations at the top of their scope
   - Ensure implementation matches declaration exactly
   - Document dependencies between mutually recursive functions

## Common Patterns

### Callback Pattern

```pryst
fn fetchData(str url, (str) -> void onSuccess, (str) -> void onError) -> void {
    try {
        let data = // fetch implementation
        onSuccess(data);
    } catch (error) {
        onError(error);
    }
}
```

### Builder Pattern

```pryst
class QueryBuilder {
    fn where((str) -> bool predicate) -> QueryBuilder {
        // Implementation
        return this;
    }

    fn orderBy((str, str) -> int comparator) -> QueryBuilder {
        // Implementation
        return this;
    }
}
```

## Next Steps

- Explore [Classes and Objects](05-classes.md)
- Learn about [Error Handling](06-error-handling.md)
- Understand [Type Conversions](07-type-conversions.md)
