---
sidebar_position: 6
---

# Error Handling

Pryst implements a robust error handling system using try-catch mechanisms similar to C++, combined with modern features for better error management.

## Try-Catch Blocks

### Basic Error Handling

```pryst
try {
    // Code that might throw an error
    riskyOperation();
} catch (error) {
    // Handle the error
    print("Error occurred: ${error}");
}
```

### Multiple Catch Blocks

```pryst
try {
    // Risky code
    processData();
} catch (IOException error) {
    // Handle IO errors
    print("IO Error: ${error}");
} catch (ParseError error) {
    // Handle parsing errors
    print("Parse Error: ${error}");
} catch (error) {
    // Handle all other errors
    print("Unknown error: ${error}");
}
```

## Custom Errors

```pryst
class ValidationError {
    str message;
    int code;

    ValidationError(str message, int code) {
        this.message = message;
        this.code = code;
    }
}

fn validate(str input) -> void {
    if (input.length() == 0) {
        throw new ValidationError("Input cannot be empty", 400);
    }
}

## Error Propagation

### Function Error Handling

```pryst
fn processInput(str input) -> str {
    try {
        validate(input);
        return transform(input);
    } catch (error) {
        // Log error and re-throw
        print("Error processing input: ${error}");
        throw error;
    }
}
```

### Cleanup with Finally

```pryst
fn processFile(str filename) -> void {
    let file = null;
    try {
        file = openFile(filename);
        // Process file
    } catch (error) {
        print("Error: ${error}");
    } finally {
        if (file != null) {
            file.close();
        }
    }
}
```

## Best Practices

1. **Error Types**
   - Use specific error types for different scenarios
   - Include relevant error information
   - Keep error messages clear and actionable

2. **Error Handling**
   - Handle errors at appropriate levels
   - Avoid empty catch blocks
   - Clean up resources in finally blocks

3. **Error Propagation**
   - Document error conditions
   - Consider error recovery strategies
   - Log errors appropriately

## Common Patterns

### Result Type Pattern

```pryst
class Result<T> {
    T value;
    str error;
    bool success;

    static fn ok<T>(T value) -> Result<T> {
        let result = new Result<T>();
        result.value = value;
        result.success = true;
        return result;
    }

    static fn error<T>(str message) -> Result<T> {
        let result = new Result<T>();
        result.error = message;
        result.success = false;
        return result;
    }
}

// Using Result type
fn divide(int a, int b) -> Result<int> {
    if (b == 0) {
        return Result.error("Division by zero");
    }
    return Result.ok(a / b);
}
```

### Error Handler Pattern

```pryst
class ErrorHandler {
    fn handle(str error) -> void {
        // Log error
        print("Error: ${error}");

        // Notify monitoring system
        notify(error);

        // Take appropriate action
        if (isRecoverable(error)) {
            recover();
        } else {
            terminate();
        }
    }
}
```

## Next Steps

- Understand [Type Conversions](07-type-conversions.md)
- Explore [Reflection](08-reflection.md)
- Learn about [Memory Management](09-memory-management.md)
