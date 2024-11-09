# Pryst API Reference

## Core Types

### Primitive Types

```pryst
// Integer types
i8    // 8-bit signed integer
i16   // 16-bit signed integer
i32   // 32-bit signed integer
i64   // 64-bit signed integer

// Unsigned integer types
u8    // 8-bit unsigned integer
u16   // 16-bit unsigned integer
u32   // 32-bit unsigned integer
u64   // 64-bit unsigned integer

// Floating point types
f32   // 32-bit floating point
f64   // 64-bit floating point

// Other primitive types
bool  // Boolean type
str   // String type
void  // Void type
```

### Type Conversion Functions

```pryst
// Numeric conversions
int(value)    // Convert to i32
float(value)  // Convert to f64
bool(value)   // Convert to boolean

// String conversions
str(value)    // Convert to string
```

## Functions

### Function Declaration

```pryst
// Arrow syntax for lambda functions
let add = (int x, int y) -> int {
    return x + y;
}

// Named function declaration
fn multiply(int x, int y) -> int {
    return x * y;
}
```

### Function Types

```pryst
// Function type declaration
type BinaryOp = fn<int>(int, int);

// Function with type annotation
let divide: fn<int>(int, int) = (int x, int y) -> int {
    return x / y;
};
```

## Modules

### Module Declaration

```pryst
module math {
    // Public exports
    export fn add(int x, int y) -> int {
        return x + y;
    }

    // Private functions
    fn helper() -> void {
        // Implementation
    }
}
```

### Module Import

```pryst
// Full module import
import math;

// Namespace import
import graphics::utils;

// Using declaration
using namespace math;
using module graphics::utils;
```

## Error Handling

### Try-Catch Mechanism

```pryst
try {
    let result = riskyOperation();
} catch (Error e) {
    handleError(e);
} finally {
    cleanup();
}
```

### Result Type

```pryst
// Result type usage
let result: Result<int, Error> = computeValue();

// Result handling
if (result.isOk()) {
    let value = result.unwrap();
} else {
    let error = result.unwrapErr();
}
```

## Classes

### Class Declaration

```pryst
class Person {
    // Properties
    string name;
    int age;

    // Constructor
    init(string name, int age) {
        this.name = name;
        this.age = age;
    }

    // Methods
    fn getName() -> string {
        return this.name;
    }

    fn setAge(int newAge) -> void {
        this.age = newAge;
    }
}
```

### Inheritance

```pryst
class Employee extends Person {
    // Additional properties
    string department;

    // Constructor with super call
    init(string name, int age, string department) {
        super(name, age);
        this.department = department;
    }
}
```

## Type System

### Generic Types

```pryst
// Generic class
class Container<T> {
    T value;

    init(T value) {
        this.value = value;
    }

    fn getValue() -> T {
        return this.value;
    }
}

// Generic function
fn map<T, U>(T value, fn<U>(T) transformer) -> U {
    return transformer(value);
}
```

### Type Constraints

```pryst
// Interface definition
interface Comparable {
    fn compareTo(Self other) -> int;
}

// Constrained generic type
class SortedList<T: Comparable> {
    fn add(T item) -> void {
        // Implementation using compareTo
    }
}
```

## Reflection

### Type Information

```pryst
// Get type information
let type = typeof(value);

// Type checking
if (type.is<int>()) {
    // Handle integer type
}

// Type properties
let name = type.getName();
let methods = type.getMethods();
```

### Method Invocation

```pryst
// Dynamic method call
let obj = new MyClass();
let method = typeof(obj).getMethod("process");
method.invoke(obj, [arg1, arg2]);
```

## String Interpolation

### Basic Interpolation

```pryst
let name = "World";
let greeting = "Hello, ${name}!";
```

### Expression Interpolation

```pryst
let x = 10;
let y = 20;
let result = "Sum: ${x + y}";
```

## Memory Management

### Variable Declaration

```pryst
// Stack allocation
let stackVar = 42;

// Heap allocation
let heapObj = new MyClass();
```

### Resource Management

```pryst
// Using block for automatic cleanup
using (let file = File.open("data.txt")) {
    // File is automatically closed after block
    file.write("Hello");
}
```

## Built-in Functions

### IO Operations

```pryst
// Console output
print("Hello");
println("World");

// File operations
let content = readFile("input.txt");
writeFile("output.txt", content);
```

### Collection Operations

```pryst
// Array operations
let arr = [1, 2, 3];
arr.push(4);
arr.pop();

// Map operations
let map = {"key": "value"};
map.set("newKey", "newValue");
let value = map.get("key");
```

## Next Steps

- Review [Language Specification](../language-spec/01-introduction.md)
- Explore [User Guide](../user-guide/01-getting-started.md)
- Read [Internal Documentation](../internal/01-architecture.md)
