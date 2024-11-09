# Code Generation

## Overview

The Pryst compiler generates LLVM IR using LLVM 20.0.0, with special consideration for opaque pointers and modern optimization strategies. This document details the code generation implementation and best practices.

## LLVM Integration

### Core Components

```cpp
class LLVMCodeGenerator {
private:
    llvm::LLVMContext& context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    TypeRegistry& typeRegistry;

    // Symbol tables
    std::map<std::string, llvm::Value*> namedValues;
    std::map<std::string, llvm::Function*> functions;

public:
    // Main generation methods
    llvm::Value* generateExpression(Expression* expr);
    llvm::Function* generateFunction(FunctionDecl* func);
    llvm::Value* generateStatement(Statement* stmt);
};
```

### LLVM 20.0.0 Compatibility

```cpp
class LLVMTypeGenerator {
private:
    llvm::LLVMContext& context;
    TypeRegistry& typeRegistry;

public:
    // Opaque pointer creation
    llvm::Type* createPointerType() {
        // LLVM 20.0.0: All pointers are opaque
        return llvm::PointerType::get(context, 0);
    }

    // Array type creation
    llvm::Type* createArrayType(llvm::Type* elementType, uint64_t size) {
        return llvm::ArrayType::get(elementType, size);
    }

    // Function type creation
    llvm::FunctionType* createFunctionType(
        llvm::Type* returnType,
        const std::vector<llvm::Type*>& paramTypes
    ) {
        return llvm::FunctionType::get(returnType, paramTypes, false);
    }
};
```

## Expression Generation

### Expression Visitor

```cpp
class ExpressionGenerator : public ExprVisitor {
private:
    LLVMCodeGenerator& codegen;
    llvm::IRBuilder<>& builder;

public:
    // Literal generation
    llvm::Value* visitIntegerLiteral(IntegerLiteral* expr) override {
        return llvm::ConstantInt::get(
            builder.getContext(),
            llvm::APInt(32, expr->getValue(), true)
        );
    }

    // Binary operation generation
    llvm::Value* visitBinaryExpr(BinaryExpr* expr) override {
        llvm::Value* left = generateExpression(expr->getLeft());
        llvm::Value* right = generateExpression(expr->getRight());

        switch (expr->getOperator()) {
            case BinaryOp::Add:
                return builder.CreateAdd(left, right, "addtmp");
            case BinaryOp::Sub:
                return builder.CreateSub(left, right, "subtmp");
            // ... other operations
        }
    }
};
```

### Memory Operations

```cpp
class MemoryManager {
private:
    llvm::IRBuilder<>& builder;
    TypeRegistry& typeRegistry;

public:
    // Allocation
    llvm::Value* createAlloca(llvm::Function* function,
                             llvm::Type* type,
                             const std::string& name) {
        llvm::IRBuilder<> tempBuilder(
            &function->getEntryBlock(),
            function->getEntryBlock().begin()
        );
        return tempBuilder.CreateAlloca(type, nullptr, name);
    }

    // Load/Store operations
    llvm::Value* createLoad(llvm::Value* ptr, const std::string& name) {
        // LLVM 20.0.0: Use opaque pointers
        return builder.CreateLoad(ptr->getType(), ptr, name);
    }

    llvm::Value* createStore(llvm::Value* value, llvm::Value* ptr) {
        return builder.CreateStore(value, ptr);
    }
};
```

## Control Flow Generation

### Basic Blocks

```cpp
class ControlFlowGenerator {
private:
    llvm::IRBuilder<>& builder;
    llvm::Function* currentFunction;

public:
    // Conditional generation
    llvm::Value* generateIf(IfStmt* stmt) {
        llvm::Value* condition = generateExpression(stmt->getCondition());

        llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(
            builder.getContext(), "then", currentFunction);
        llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(
            builder.getContext(), "else");
        llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(
            builder.getContext(), "ifcont");

        builder.CreateCondBr(condition, thenBB, elseBB);

        // Generate then block
        builder.SetInsertPoint(thenBB);
        llvm::Value* thenValue = generateStatement(stmt->getThenBranch());
        builder.CreateBr(mergeBB);

        // Generate else block
        currentFunction->getBasicBlockList().push_back(elseBB);
        builder.SetInsertPoint(elseBB);
        llvm::Value* elseValue = generateStatement(stmt->getElseBranch());
        builder.CreateBr(mergeBB);

        // Continue in merge block
        currentFunction->getBasicBlockList().push_back(mergeBB);
        builder.SetInsertPoint(mergeBB);

        return nullptr;
    }
};
```

### Loop Generation

```cpp
class LoopGenerator {
private:
    llvm::IRBuilder<>& builder;
    llvm::Function* currentFunction;

public:
    // While loop generation
    llvm::Value* generateWhile(WhileStmt* stmt) {
        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(
            builder.getContext(), "cond", currentFunction);
        llvm::BasicBlock* loopBB = llvm::BasicBlock::Create(
            builder.getContext(), "loop");
        llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(
            builder.getContext(), "afterloop");

        builder.CreateBr(condBB);

        // Generate condition
        builder.SetInsertPoint(condBB);
        llvm::Value* condition = generateExpression(stmt->getCondition());
        builder.CreateCondBr(condition, loopBB, afterBB);

        // Generate loop body
        currentFunction->getBasicBlockList().push_back(loopBB);
        builder.SetInsertPoint(loopBB);
        generateStatement(stmt->getBody());
        builder.CreateBr(condBB);

        // Continue after loop
        currentFunction->getBasicBlockList().push_back(afterBB);
        builder.SetInsertPoint(afterBB);

        return nullptr;
    }
};
```

## Optimization

### Pass Management

```cpp
class OptimizationManager {
private:
    llvm::Module& module;
    llvm::PassBuilder passBuilder;

public:
    void runOptimizationPasses() {
        llvm::LoopAnalysisManager LAM;
        llvm::FunctionAnalysisManager FAM;
        llvm::CGSCCAnalysisManager CGAM;
        llvm::ModuleAnalysisManager MAM;

        // Register analyses
        passBuilder.registerModuleAnalyses(MAM);
        passBuilder.registerCGSCCAnalyses(CGAM);
        passBuilder.registerFunctionAnalyses(FAM);
        passBuilder.registerLoopAnalyses(LAM);
        passBuilder.crossRegisterProxies(LAM, FAM, CGAM, MAM);

        // Create optimization pipeline
        llvm::ModulePassManager MPM =
            passBuilder.buildPerModuleDefaultPipeline(
                llvm::OptimizationLevel::O2
            );

        // Run passes
        MPM.run(module, MAM);
    }
};
```

### Custom Optimizations

```cpp
class CustomOptimizer {
private:
    llvm::Module& module;

public:
    void optimizeModule() {
        // Constant folding
        for (auto& F : module) {
            for (auto& BB : F) {
                for (auto& I : BB) {
                    if (auto* binOp = llvm::dyn_cast<llvm::BinaryOperator>(&I)) {
                        optimizeBinaryOp(binOp);
                    }
                }
            }
        }
    }

private:
    void optimizeBinaryOp(llvm::BinaryOperator* binOp) {
        if (auto* constLeft = llvm::dyn_cast<llvm::ConstantInt>(
                binOp->getOperand(0))) {
            if (auto* constRight = llvm::dyn_cast<llvm::ConstantInt>(
                    binOp->getOperand(1))) {
                // Perform constant folding
                optimizeConstants(binOp, constLeft, constRight);
            }
        }
    }
};
```

## Runtime Support

### Runtime Library Integration

```cpp
class RuntimeSupport {
private:
    llvm::Module& module;
    llvm::IRBuilder<>& builder;

public:
    // String operations
    llvm::Value* generateStringConcat(llvm::Value* left, llvm::Value* right) {
        llvm::Function* concatFn = module.getFunction("pryst_string_concat");
        if (!concatFn) {
            concatFn = createStringConcatFunction();
        }
        return builder.CreateCall(concatFn, {left, right}, "concat");
    }

    // Memory management
    llvm::Value* generateGC_Alloc(llvm::Type* type, size_t size) {
        llvm::Function* allocFn = module.getFunction("pryst_gc_alloc");
        if (!allocFn) {
            allocFn = createGCAllocFunction();
        }
        return builder.CreateCall(allocFn, {
            llvm::ConstantInt::get(builder.getInt64Ty(), size)
        }, "gcalloc");
    }
};
```

## Debug Information

### Debug Info Generation

```cpp
class DebugInfoGenerator {
private:
    llvm::Module& module;
    llvm::IRBuilder<>& builder;
    std::unique_ptr<llvm::DIBuilder> debugBuilder;

public:
    void generateDebugInfo(const SourceLocation& loc) {
        if (!debugBuilder) {
            return;
        }

        llvm::DIFile* file = debugBuilder->createFile(
            loc.getFileName(),
            loc.getDirectory()
        );

        builder.SetCurrentDebugLocation(
            llvm::DILocation::get(
                builder.getContext(),
                loc.getLine(),
                loc.getColumn(),
                file
            )
        );
    }
};
```

## Next Steps

- Review [Module System Implementation](04-module-system.md)
- Understand [Error Handling Implementation](05-error-handling.md)
- Explore [Runtime Library Details](06-runtime-library.md)
