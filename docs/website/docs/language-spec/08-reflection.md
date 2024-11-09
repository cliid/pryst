---
sidebar_position: 8
---

# Reflection

Pryst provides a powerful reflection API that allows for runtime type inspection and manipulation, similar to Java's reflection capabilities but with static type safety.

## Type Information

### Basic Type Inspection

```pryst
// Get type information
let type = typeof(someVariable);
print("Type name: ${type.name}");
print("Is primitive: ${type.isPrimitive}");
print("Is class: ${type.isClass}");

// Check type relationships
let isSubtype = type.isSubtypeOf(otherType);
let canAssign = type.isAssignableFrom(otherType);
```

### Class Reflection

```pryst
class Person {
    str name;
    int age;

    Person(str name, int age) {
        this.name = name;
        this.age = age;
    }

    fn<void> greet() {
        print("Hello, I'm ${name}");
    }
}

// Get class information
let personType = typeof(Person);
let methods = personType.getMethods();
let fields = personType.getFields();
let constructors = personType.getConstructors();

// Print class structure
for (let method in methods) {
    print("Method: ${method.name}");
    print("Return type: ${method.returnType}");
    print("Parameters: ${method.parameters}");
}
```

## Dynamic Access

### Property Access

```pryst
fn<any> getProperty(any object, str propertyName) -> any {
    let type = typeof(object);
    let property = type.getProperty(propertyName);
    if (property != null) {
        return property.getValue(object);
    }
    return null;
}

fn<void> setProperty(any object, str propertyName, any value) {
    let type = typeof(object);
    let property = type.getProperty(propertyName);
    if (property != null) {
        property.setValue(object, value);
    }
}
```

### Method Invocation

```pryst
fn<any> invokeMethod(any object, str methodName, any[] args) -> any {
    let type = typeof(object);
    let method = type.getMethod(methodName);
    if (method != null) {
        return method.invoke(object, args);
    }
    return null;
}
```

## Type Creation

### Dynamic Instance Creation

```pryst
fn<any> createInstance(Type type, any[] constructorArgs) -> any {
    let constructor = type.getConstructor(constructorArgs);
    if (constructor != null) {
        return constructor.newInstance(constructorArgs);
    }
    return null;
}
```

## Best Practices

1. **Performance Considerations**
   - Cache reflection results when possible
   - Use reflection judiciously
   - Consider compile-time alternatives

2. **Type Safety**
   - Validate types before operations
   - Handle reflection errors appropriately
   - Document reflection usage

3. **Security**
   - Control access to reflection capabilities
   - Validate input when using reflection
   - Consider security implications

## Common Patterns

### Type Registry Pattern

```pryst
class TypeRegistry {
    static map<str, Type> types;

    static fn<void> register(str name, Type type) {
        types[name] = type;
    }

    static fn<Type> getType(str name) -> Type {
        return types[name];
    }

    static fn<any> createInstance(str name) -> any {
        let type = getType(name);
        if (type != null) {
            return type.createInstance();
        }
        return null;
    }
}
```

### Property Observer Pattern

```pryst
class PropertyObserver {
    fn<void> observe(any object, str propertyName, fn<void>(any, any) callback) {
        let type = typeof(object);
        let property = type.getProperty(propertyName);

        if (property != null) {
            property.addObserver((oldValue, newValue) -> {
                callback(oldValue, newValue);
            });
        }
    }
}
```

## Next Steps

- Learn about [Memory Management](09-memory-management.md)
- Understand [Advanced Features](10-advanced-features.md)
- Explore [Standard Library](11-standard-library.md)
