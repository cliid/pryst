# Error Handling

## Overview

Pryst provides comprehensive error handling mechanisms, combining traditional try-catch blocks with modern Result types for explicit error handling. The system ensures type safety while providing flexible error management options.

## Basic Error Handling

### Try-Catch Blocks

```pryst
// Basic try-catch
try {
    let result = riskyOperation();
} catch (NetworkError e) {
    print("Network error: ${e.message}");
} catch (ValidationError e) {
    print("Validation error: ${e.message}");
} catch {
    print("Unknown error occurred");
}

// Multiple error types
try {
    processData();
} catch (IOException | NetworkError e) {
    print("IO or Network error: ${e.message}");
} catch {
    print("Other error occurred");
}
```

### Result Type

```pryst
// Using Result type
fn divide(int x, int y) -> Result<int> {
    if (y == 0) {
        return Result.error("Division by zero");
    }
    return Result.ok(x / y);
}

// Working with Results
let result = divide(10, 2);
if (result.isOk()) {
    print("Result: ${result.unwrap()}");
} else {
    print("Error: ${result.getError()}");
}

// Chaining Results
let final = divide(10, 2)
    .map((x) -> x * 2)
    .flatMap((x) -> divide(x, 3));
```

## Custom Error Types

```pryst
// Defining custom errors
class ValidationError : Error {
    str field;

    ValidationError(str message, str field) {
        super(message);
        this.field = field;
    }
}

// Using custom errors
fn validateAge(int age) -> Result<void> {
    if (age < 0) {
        return Result.error(new ValidationError("Age cannot be negative", "age"));
    }
    if (age > 150) {
        return Result.error(new ValidationError("Age seems unrealistic", "age"));
    }
    return Result.ok();
}
```

## Error Propagation

### Using Result Chain

```pryst
// Error propagation with Results
fn processUser(str input) -> Result<User> {
    return parseInput(input)
        .flatMap((data) -> validateData(data))
        .flatMap((valid) -> createUser(valid));
}

// Using the Result
let result = processUser(input);
match (result) {
    Ok(user) -> print("User created: ${user.name}"),
    Error(e) -> print("Error: ${e.message}")
}
```

### Cross-Module Error Handling

```pryst
// Module-specific errors
module auth {
    class AuthError : Error {
        AuthError(str message) {
            super(message);
        }
    }

    fn authenticate() -> Result<User> {
        // Implementation
    }
}

// Using module errors
import auth;

fn secureOperation() -> Result<void> {
    try {
        let result = auth::authenticate();
        match (result) {
            Ok(user) -> processUser(user),
            Error(e) -> Result.error(e)
        }
    } catch (auth::AuthError e) {
        return Result.error(e);
    }
}
```

## Best Practices

### Error Type Hierarchy

```pryst
// Base error types
class AppError : Error {
    int code;

    AppError(str message, int code) {
        super(message);
        this.code = code;
    }
}

// Specific error types
class DatabaseError : AppError {
    DatabaseError(str message) {
        super(message, 5000);
    }
}

class NetworkError : AppError {
    NetworkError(str message) {
        super(message, 4000);
    }
}
```

### Error Recovery Patterns

```pryst
// Fallback values
fn getData() -> int {
    try {
        return fetchData();
    } catch {
        return -1;  // Default value
    }
}

// Retry logic
fn retryOperation(fn<void> -> Result<T> operation, int maxAttempts) -> Result<T> {
    for (int i = 0; i < maxAttempts; i++) {
        let result = operation();
        if (result.isOk()) {
            return result;
        }
    }
    return Result.error("Max retry attempts reached");
}
```

### Resource Cleanup

```pryst
// Using finally blocks
fn processFile(str path) {
    let file = null;
    try {
        file = openFile(path);
        processData(file);
    } catch (IOException e) {
        print("Error: ${e.message}");
    } finally {
        if (file != null) {
            file.close();
        }
    }
}
```

## Common Patterns

### Optional Chaining

```pryst
// Safe navigation
let value = user?.profile?.settings?.theme ?? "default";

// Combining with error handling
try {
    let theme = user?.getTheme() ?? defaultTheme;
} catch (ThemeError e) {
    print("Error loading theme: ${e.message}");
}
```

### Error Logging

```pryst
// Structured error logging
fn logError(Error e) {
    log.error("Error occurred", {
        type: e.type,
        message: e.message,
        stack: e.stackTrace,
        timestamp: getCurrentTime()
    });
}
```

## Next Steps

- Learn about [Classes and Objects](05-classes.md)
- Explore [Reflection](06-reflection.md)
- Understand [Testing](07-testing.md)
