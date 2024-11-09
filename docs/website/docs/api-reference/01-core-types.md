---
sidebar_position: 1
---

# Core Types

## Primitive Types

### int
Integer type representing whole numbers.

```pryst
let x: int = 42;

// Methods
static fn<int> parse(str value) throws ParseError
fn<str> toString() -> str
fn<float> toFloat() -> float
fn<int> abs() -> int
fn<int> max(int other) -> int
fn<int> min(int other) -> int
static fn<bool> isValid(str value) -> bool
```

### float
Floating-point type for decimal numbers.

```pryst
let pi: float = 3.14159;

// Methods
static fn<float> parse(str value) throws ParseError
fn<str> toString() -> str
fn<int> toInt() -> int
fn<str> toFixed(int decimals) -> str
fn<float> abs() -> float
fn<float> round() -> float
fn<float> ceil() -> float
fn<float> floor() -> float
static fn<bool> isValid(str value) -> bool
```

### bool
Boolean type representing true or false values.

```pryst
let isValid: bool = true;

// Methods
static fn<bool> parse(str value) throws ParseError
fn<str> toString() -> str
fn<bool> not() -> bool
fn<bool> and(bool other) -> bool
fn<bool> or(bool other) -> bool
static fn<bool> isValid(str value) -> bool
```

### str
String type for text data.

```pryst
let message: str = "Hello, World!";

// Methods
static fn<str> concat(str... parts) -> str
fn<str> substring(int start, int end) -> str
fn<str> trim() -> str
fn<str[]> split(str delimiter) -> str[]
fn<bool> startsWith(str prefix) -> bool
fn<bool> endsWith(str suffix) -> bool
fn<int> length() -> int
fn<int> indexOf(str substring) -> int
fn<str> replace(str oldStr, str newStr) -> str
fn<str> toLowerCase() -> str
fn<str> toUpperCase() -> str
static fn<bool> isValid(str value) -> bool
```

## Function Types

### Function Type Syntax

```pryst
// Basic function type
fn<ReturnType>(ParamType1, ParamType2, ...)

// Arrow syntax
(ParamType1, ParamType2, ...) -> ReturnType
```

### Examples

```pryst
// Function type that takes two ints and returns an int
fn<int>(int, int)

// Function type that takes no parameters and returns void
fn<void>()

// Higher-order function type
fn<fn<int>(int)>(int)
```

## Array Types

### Array Type Syntax

```pryst
// Basic array type
ElementType[]

// Multidimensional array type
ElementType[][]
```

### Examples

```pryst
// Array of integers
let numbers: int[] = [1, 2, 3];

// Array of strings
let names: str[] = ["Alice", "Bob"];

// 2D array of floats
let matrix: float[][] = [[1.0, 2.0], [3.0, 4.0]];
```

## Type Conversion Methods

### Primitive Type Conversions

```pryst
// int methods
int.parse(str): int
int.toString(): str

// float methods
float.parse(str): float
float.toString(): str

// bool methods
bool.parse(str): bool
bool.toString(): str
```

### Examples

```pryst
// String to int conversion
let num = int.parse("42");

// Int to string conversion
let str = num.toString();

// String to float conversion
let pi = float.parse("3.14159");
```

## Type Checking Methods

### Type Information

```pryst
// Get type information
typeof(value): Type

// Type checking
value instanceof Type: bool
```

### Examples

```pryst
let x = 42;
let type = typeof(x);  // Returns Type representing int
let isInt = x instanceof int;  // Returns true
```

## Type Inference

### Variable Type Inference

```pryst
// Type inference for primitive types
let x = 42;           // Inferred as int
let y = 3.14;         // Inferred as float
let z = "Hello";      // Inferred as str
let w = true;         // Inferred as bool

// Type inference with operations
let sum = x + 10;     // Inferred as int
let message = z + "!"; // Inferred as str
```

### Function Return Type Inference

```pryst
// Return type inference for functions
fn add(x: int, y: int) -> {
    return x + y;     // Return type inferred as int
}

fn getMessage() -> {
    return "Hello";   // Return type inferred as str
}
```

### Lambda Type Inference

```pryst
// Type inference in lambda expressions
let multiply = (x: int, y: int) -> x * y;  // Return type inferred as int
let greet = (name: str) -> "Hello, " + name; // Return type inferred as str
```

## Security Considerations

### Type Safety

```pryst
// Type safety prevents runtime errors
let x: int = "42";     // Compile error: Cannot assign str to int
let y = int.parse("42"); // Safe: Explicit conversion with error handling

// Null safety
let x: int = null;     // Compile error: int cannot be null
let y: int? = null;    // OK: int? is nullable int type
```

### Memory Safety

```pryst
// Automatic memory management
let arr: int[] = [1, 2, 3];  // Memory automatically managed
// No manual memory allocation/deallocation needed
```

## Error Handling

### Type Conversion Errors

```pryst
// Safe type conversion with error handling
try {
    let num = int.parse("invalid");
} catch (ParseError e) {
    // Handle parsing error
    print("Invalid number format");
}

// Safe array access
try {
    let arr = [1, 2, 3];
    let value = arr[5];  // Throws IndexOutOfBoundsError
} catch (IndexOutOfBoundsError e) {
    // Handle array bounds error
    print("Invalid array index");
}
```

### Null Safety

```pryst
// Null safety in action
fn processValue(x: int?) -> int {
    if (x == null) {
        return 0;  // Handle null case explicitly
    }
    return x + 1;  // x is guaranteed non-null here
}

// Optional chaining
let arr: int[]? = null;
let length = arr?.length() ?? 0;  // Safe access with fallback
```

## Next Steps

- Learn about [Standard Library Types](02-standard-library.md)
- Explore [Collection Types](03-collections.md)
- Understand [Custom Types](04-custom-types.md)
