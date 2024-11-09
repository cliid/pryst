---
sidebar_position: 1
---

# Type System

## Type Registry Implementation

### Core Type Management

The type registry manages all types in the Pryst system:

```cpp
class TypeRegistry {
    // Register basic types
    fn registerPrimitiveType(str name, TypeInfo info);

    // Handle class and custom types
    fn registerClassType(str name, ClassInfo info);

    // Manage function types
    fn registerFunctionType(FunctionTypeInfo info) -> Type;

    // Resolve type references
    fn resolveType(str qualifiedName) -> Type;
}
```

### Type Information

Type metadata and information handling:

```cpp
class TypeInfo {
    str name;
    TypeCategory category;
    bool isConst;
    Vector<Type> templateParams;

    // Type compatibility checking
    fn isCompatibleWith(Type other) -> bool;

    // Type conversion validation
    fn canConvertTo(Type target) -> bool;
}
```

## Type System Features

### Type Checking

The type checker enforces type safety:

```cpp
class TypeChecker {
    // Validate assignment compatibility
    fn checkAssignment(Type target, Type source) -> bool;

    // Function call type checking
    fn validateFunctionCall(FunctionType func, Vector<Type> args) -> bool;

    // Template type validation
    fn validateTemplateArguments(Type template, Vector<Type> args) -> bool;
}
```

### Type Conversion

Type conversion handling:

```cpp
class TypeConverter {
    // Handle primitive type conversions
    fn convertPrimitive(Type source, Type target, Value val) -> Value;

    // Class type conversions
    fn convertClass(Type source, Type target, Value val) -> Value;

    // Check conversion costs
    fn getConversionCost(Type source, Type target) -> int;
}
```

### Forward Declaration Resolution

Handling forward-declared types:

```cpp
class ForwardTypeResolver {
    // Resolve forward declarations
    fn resolveForwardType(str name, Module context) -> Type;

    // Validate forward declaration usage
    fn validateForwardUsage(Type forwardType, Type actualType) -> bool;

    // Track unresolved forward declarations
    fn trackUnresolvedType(str name, Module context);
}
```

## Type Categories

### Primitive Types

Built-in type handling:

```cpp
enum PrimitiveTypeKind {
    Int,
    Float,
    Bool,
    Str,
    Void,
    Any
}

class PrimitiveType : Type {
    PrimitiveTypeKind kind;

    // Type-specific operations
    fn getDefaultValue() -> Value;
    fn validateOperation(Operation op) -> bool;
}
```

### Function Types

Function type representation:

```cpp
class FunctionType : Type {
    Type returnType;
    Vector<Type> parameterTypes;
    bool isVariadic;

    // Function type compatibility
    fn isCallCompatible(Vector<Type> argTypes) -> bool;

    // Type inference for lambda expressions
    fn inferFromLambda(LambdaExpression expr) -> FunctionType;
}
```

### Class Types

Class type management:

```cpp
class ClassType : Type {
    str name;
    Vector<MemberInfo> members;
    Vector<MethodInfo> methods;
    Optional<ClassType> baseClass;

    // Member lookup and access
    fn findMember(str name) -> Optional<MemberInfo>;
    fn findMethod(str name) -> Optional<MethodInfo>;

    // Inheritance checking
    fn isSubclassOf(ClassType other) -> bool;
}
```

## Best Practices

1. **Type Safety**
   - Always validate type compatibility before conversions
   - Use explicit type annotations for clarity
   - Handle forward declarations carefully

2. **Type Registration**
   - Register types early in module loading
   - Maintain clear type ownership boundaries
   - Document type dependencies

3. **Performance**
   - Cache type resolution results
   - Optimize common type conversions
   - Minimize dynamic type checks

## Common Implementation Patterns

### Type Resolution

```cpp
// Example type resolution implementation
class TypeResolver {
    // Resolve type references
    fn resolveTypeReference(str name, Context ctx) -> Type {
        // Handle qualified names
        // Resolve forward declarations
        // Check type visibility
    }

    // Handle template instantiation
    fn instantiateTemplate(Type template, Vector<Type> args) -> Type {
        // Validate template arguments
        // Create new type instance
        // Register instantiated type
    }
}
```

### Type Conversion Chain

```cpp
// Example type conversion implementation
class ConversionChain {
    // Build conversion sequence
    fn buildConversionSequence(Type source, Type target) -> Vector<Conversion> {
        // Find conversion path
        // Calculate conversion costs
        // Validate conversion safety
    }

    // Apply conversions
    fn applyConversions(Value val, Vector<Conversion> conversions) -> Value {
        // Execute conversion steps
        // Validate intermediate results
        // Handle conversion failures
    }
}
```

## Next Steps

- Learn about [Modules](02-modules.md)
- Explore [Error Handling](03-error-handling.md)
- Understand [Reflection API](04-reflection.md)
