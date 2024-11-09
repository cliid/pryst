---
sidebar_position: 7
---

# Type Conversions

Pryst provides a flexible type conversion system that supports both implicit and explicit conversions while maintaining type safety.

## Basic Type Conversions

### Primitive Type Conversions

```pryst
// Numeric conversions
let i = 42;
let f = float(i);    // int to float
let i2 = int(f);     // float to int

// String conversions
let s = str(i);      // int to string
let s2 = str(f);     // float to string

// Boolean conversions
let b = bool(i);     // int to bool
let i3 = int(b);     // bool to int
```

### Cast Syntax

```pryst
// Alternative cast syntax
let f = (float) 42;    // int to float
let i = (int) 3.14;    // float to int
let s = (str) true;    // bool to string
```

## Class Conversions

### Constructor-Based Conversion

```pryst
class Vector2D {
    float x;
    float y;

    // Conversion constructor
    Vector2D(str s) {
        // Parse string format "x,y"
        let parts = s.split(",");
        this.x = float(parts[0]);
        this.y = float(parts[1]);
    }

    // Convert to string
    fn<str> toString() -> str {
        return "${x},${y}";
    }
}

// Using conversions
let v = Vector2D("1.0,2.0");    // String to Vector2D
let s = v.toString();           // Vector2D to string
```

### Explicit Cast Operators

```pryst
class Temperature {
    float celsius;

    Temperature(float celsius) {
        this.celsius = celsius;
    }

    // Cast operator for float
    fn<float> toFloat() -> float {
        return celsius;
    }

    // Cast operator for int
    fn<int> toInt() -> int {
        return int(celsius);
    }
}

// Using cast operators
let temp = new Temperature(25.5);
let f = float(temp);    // Uses toFloat()
let i = int(temp);      // Uses toInt()
```

## Type Safety

### Implicit Conversions

```pryst
// Safe implicit conversions
let i = 42;
let f = i + 3.14;    // int implicitly converted to float

// Unsafe implicit conversions (not allowed)
let f = 3.14;
let i: int = f;      // Error: Cannot implicitly convert float to int
```

### Type Checking

```pryst
fn<bool> isValidConversion<T, U>(T value) -> bool {
    try {
        let converted = U(value);
        return true;
    } catch {
        return false;
    }
}

// Using type checking
let canConvert = isValidConversion<float, int>(3.14);
```

## Best Practices

1. **Explicit vs Implicit**
   - Prefer explicit conversions for clarity
   - Use implicit conversions only for safe, obvious cases
   - Document conversion behavior

2. **Error Handling**
   - Handle conversion failures gracefully
   - Provide clear error messages
   - Validate input before conversion

3. **Performance**
   - Consider conversion costs
   - Cache converted values when appropriate
   - Use appropriate numeric types

## Common Patterns

### Safe Conversion Pattern

```pryst
class SafeConverter<T, U> {
    fn<Result<U>> convert(T value) -> Result<U> {
        try {
            return Result.ok(U(value));
        } catch (error) {
            return Result.error("Conversion failed: ${error}");
        }
    }
}

// Using safe converter
let converter = new SafeConverter<str, int>();
let result = converter.convert("123");
if (result.success) {
    print("Converted value: ${result.value}");
}
```

### Conversion Registry Pattern

```pryst
class ConversionRegistry {
    static map<str, fn<any>(any)> converters;

    static fn<void> register<T, U>(fn<U>(T) converter) {
        let key = "${typeof(T)}_${typeof(U)}";
        converters[key] = converter;
    }

    static fn<U> convert<T, U>(T value) -> U {
        let key = "${typeof(T)}_${typeof(U)}";
        if (converters.has(key)) {
            return converters[key](value);
        }
        throw "No converter registered for ${key}";
    }
}
```

## Next Steps

- Explore [Reflection](08-reflection.md)
- Learn about [Memory Management](09-memory-management.md)
- Understand [Advanced Features](10-advanced-features.md)
