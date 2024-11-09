---
sidebar_position: 5
---

# Classes and Objects

Pryst supports object-oriented programming through a modern class system that combines the best features of C++ and TypeScript.

## Class Declaration

### Basic Class Structure

```pryst
class Point {
    // Properties
    float x;
    float y;

    // Constructor
    Point(float x, float y) {
        this.x = x;
        this.y = y;
    }

    // Methods
    fn distance(Point other) -> float {
        let dx = this.x - other.x;
        let dy = this.y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
}

### Inheritance

```pryst
class Shape {
    str name;

    Shape(str name) {
        this.name = name;
    }

    fn area() -> float {
        return 0.0;
    }
}

class Circle extends Shape {
    float radius;

    Circle(float radius) {
        super("circle");
        this.radius = radius;
    }

    fn area() -> float {
        return pi() * radius * radius;
    }
}

## Class Members

### Properties

```pryst
class Rectangle {
    // Public properties
    float width;
    float height;

    // Private properties with underscore convention
    float _area;

    // Constant property
    const str type = "rectangle";

    // Static property
    static int instanceCount = 0;
}
```

### Methods

```pryst
class Vector {
    float x;
    float y;

    // Instance method
    fn magnitude() -> float {
        return sqrt(x * x + y * y);
    }

    // Static method
    static zero() -> Vector {
        return new Vector(0, 0);
    }

    // Method with type parameters
    fn transform<T>((float, float) -> T transformer) -> T {
        return transformer(x, y);
    }
}
```

## Constructors and Initialization

```pryst
class Person {
    str name;
    int age;

    // Primary constructor
    Person(str name, int age) {
        this.name = name;
        this.age = age;
    }

    // Secondary constructor
    Person(str name) {
        this(name, 0);  // Call primary constructor
    }

    // Static factory method
    static fn create(str name) -> Person {
        return new Person(name);
    }
}

## Type Conversion

```pryst
class Temperature {
    float celsius;

    // Constructor-based conversion
    Temperature(int fahrenheit) {
        this.celsius = (fahrenheit - 32) * 5 / 9;
    }

    // Explicit conversion method
    fn toFahrenheit() -> int {
        return (int)(celsius * 9 / 5 + 32);
    }
}

// Using conversions
let temp = Temperature(98);  // From Fahrenheit
let fahrenheit = temp.toFahrenheit();
```

## Best Practices

1. **Class Design**
   - Keep classes focused and single-purpose
   - Use meaningful names
   - Follow consistent naming conventions

2. **Member Organization**
   - Group related properties and methods
   - Place constructors first
   - Order members by visibility

3. **Inheritance**
   - Favor composition over inheritance
   - Keep inheritance hierarchies shallow
   - Use meaningful base classes

## Common Patterns

### Builder Pattern

```pryst
class QueryBuilder {
    str[] conditions;

    fn where(str condition) -> QueryBuilder {
        conditions.push(condition);
        return this;
    }

    fn build() -> str {
        // Build and return query
    }
}
```

### Factory Pattern

```pryst
class ShapeFactory {
    static fn create(str type) -> Shape {
        if (type == "circle") {
            return new Circle(1.0);
        } else if (type == "rectangle") {
            return new Rectangle(1.0, 1.0);
        }
        return null;
    }
}
```

## Next Steps

- Learn about [Error Handling](06-error-handling.md)
- Understand [Type Conversions](07-type-conversions.md)
- Explore [Reflection](08-reflection.md)
