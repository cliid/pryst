# Type System Internals

## Overview

The Pryst type system implements strong static typing with type inference, leveraging LLVM 20.0.0's type system while maintaining additional type information for high-level language features.

## Type Representation

### Core Type System

```cpp
// Base type information
class TypeInfo {
protected:
    TypeKind kind;
    std::string name;
    bool isComplete;

public:
    virtual ~TypeInfo() = default;
    virtual llvm::Type* getLLVMType(llvm::LLVMContext& context) = 0;
    virtual bool isCompatibleWith(const TypeInfo* other) const = 0;
};

// Primitive type implementation
class PrimitiveTypeInfo : public TypeInfo {
private:
    size_t bitWidth;
    bool isFloatingPoint;

public:
    llvm::Type* getLLVMType(llvm::LLVMContext& context) override {
        if (isFloatingPoint) {
            return bitWidth == 32 ? llvm::Type::getFloatTy(context)
                                : llvm::Type::getDoubleTy(context);
        }
        return llvm::Type::getIntNTy(context, bitWidth);
    }
};

// Function type representation
class FunctionTypeInfo : public TypeInfo {
private:
    std::vector<TypeInfo*> parameterTypes;
    TypeInfo* returnType;

public:
    llvm::Type* getLLVMType(llvm::LLVMContext& context) override {
        std::vector<llvm::Type*> llvmParamTypes;
        for (auto* paramType : parameterTypes) {
            llvmParamTypes.push_back(paramType->getLLVMType(context));
        }
        return llvm::FunctionType::get(
            returnType->getLLVMType(context),
            llvmParamTypes,
            false
        );
    }
};
```

### LLVM Type Integration

```cpp
class TypeRegistry {
private:
    llvm::LLVMContext& context;
    std::unordered_map<std::string, std::unique_ptr<TypeInfo>> types;

public:
    // Type creation with LLVM 20.0.0 compatibility
    llvm::Type* createPointerType() {
        // Use opaque pointers in LLVM 20.0.0
        return llvm::PointerType::get(context, 0);
    }

    // Type lookup and registration
    TypeInfo* registerType(std::string name, std::unique_ptr<TypeInfo> type) {
        auto [it, inserted] = types.emplace(name, std::move(type));
        return it->second.get();
    }
};
```

## Type Inference

### Inference Engine

```cpp
class TypeInferenceEngine {
private:
    TypeRegistry& typeRegistry;
    std::unordered_map<Expression*, TypeInfo*> inferredTypes;

public:
    // Type inference for expressions
    TypeInfo* inferType(Expression* expr) {
        if (auto it = inferredTypes.find(expr); it != inferredTypes.end()) {
            return it->second;
        }

        TypeInfo* type = inferTypeImpl(expr);
        inferredTypes[expr] = type;
        return type;
    }

private:
    // Implementation-specific inference
    TypeInfo* inferTypeImpl(Expression* expr) {
        switch (expr->getKind()) {
            case ExprKind::Literal:
                return inferLiteralType(static_cast<LiteralExpr*>(expr));
            case ExprKind::Binary:
                return inferBinaryExprType(static_cast<BinaryExpr*>(expr));
            // ... other cases
        }
    }
};
```

### Type Constraints

```cpp
class TypeConstraint {
public:
    virtual ~TypeConstraint() = default;
    virtual bool isSatisfied(TypeInfo* type) const = 0;
    virtual std::string getMessage() const = 0;
};

// Subtype constraint
class SubtypeConstraint : public TypeConstraint {
private:
    TypeInfo* supertype;

public:
    bool isSatisfied(TypeInfo* type) const override {
        return type->isCompatibleWith(supertype);
    }
};

// Generic type constraint
class GenericConstraint : public TypeConstraint {
private:
    std::vector<TypeInfo*> bounds;

public:
    bool isSatisfied(TypeInfo* type) const override {
        return std::all_of(bounds.begin(), bounds.end(),
            [type](TypeInfo* bound) { return type->isCompatibleWith(bound); });
    }
};
```

## Type Checking

### Type Checker Implementation

```cpp
class TypeChecker {
private:
    TypeRegistry& typeRegistry;
    DiagnosticCollector& diagnostics;
    TypeInferenceEngine inferenceEngine;

public:
    // Type checking methods
    bool checkExpression(Expression* expr, TypeInfo* expectedType) {
        TypeInfo* actualType = inferenceEngine.inferType(expr);
        if (!actualType->isCompatibleWith(expectedType)) {
            diagnostics.reportError(
                formatTypeError(actualType, expectedType),
                expr->getLocation()
            );
            return false;
        }
        return true;
    }

    // Function type checking
    bool checkFunction(FunctionDecl* func) {
        // Check parameter types
        for (auto& param : func->getParameters()) {
            if (!checkParameter(param)) {
                return false;
            }
        }

        // Check return type
        TypeInfo* returnType = func->getReturnType();
        if (returnType) {
            return checkReturnStatements(func->getBody(), returnType);
        }

        return true;
    }
};
```

### Type Conversion

```cpp
class TypeConverter {
private:
    TypeRegistry& typeRegistry;
    llvm::IRBuilder<>& builder;

public:
    // Type conversion generation
    llvm::Value* convert(llvm::Value* value, TypeInfo* from, TypeInfo* to) {
        if (from->getKind() == TypeKind::Integer &&
            to->getKind() == TypeKind::Float) {
            return builder.CreateSIToFP(value, to->getLLVMType(builder.getContext()));
        }
        // ... other conversion cases
        return nullptr;
    }

    // Safe conversion checking
    bool canConvertSafely(TypeInfo* from, TypeInfo* to) {
        if (from->getKind() == TypeKind::Integer &&
            to->getKind() == TypeKind::Integer) {
            return getIntegerBitWidth(from) <= getIntegerBitWidth(to);
        }
        // ... other safety checks
        return false;
    }
};
```

## Generic Types

### Generic Type Implementation

```cpp
class GenericTypeInfo : public TypeInfo {
private:
    std::vector<TypeParameter> typeParameters;
    std::vector<TypeConstraint*> constraints;
    TypeInfo* erasedType;

public:
    // Type parameter management
    void addTypeParameter(const TypeParameter& param) {
        typeParameters.push_back(param);
    }

    // Constraint checking
    bool satisfiesConstraints(const std::vector<TypeInfo*>& typeArgs) const {
        if (typeArgs.size() != typeParameters.size()) {
            return false;
        }

        for (size_t i = 0; i < typeArgs.size(); ++i) {
            for (auto* constraint : constraints) {
                if (!constraint->isSatisfied(typeArgs[i])) {
                    return false;
                }
            }
        }
        return true;
    }
};
```

## Performance Optimizations

### Type Caching

```cpp
class TypeCache {
private:
    std::unordered_map<std::string, TypeInfo*> cache;
    std::mutex cacheMutex;

public:
    TypeInfo* getOrCreate(const std::string& key,
                         std::function<TypeInfo*()> creator) {
        std::lock_guard<std::mutex> lock(cacheMutex);
        auto it = cache.find(key);
        if (it != cache.end()) {
            return it->second;
        }
        TypeInfo* type = creator();
        cache[key] = type;
        return type;
    }
};
```

## Next Steps

- Explore [Code Generation Details](03-code-generation.md)
- Review [Module System Implementation](04-module-system.md)
- Understand [Error Handling Implementation](05-error-handling.md)
