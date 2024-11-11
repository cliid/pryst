#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <memory>
#include <map>
#include <string>
#include <stdexcept>
#include "llvm_codegen.hpp"
#include "type_checker.hpp"
#include "types.hpp"
#include "type_registry.hpp"

namespace pryst {

std::shared_ptr<Type> LLVMCodeGen::getTypeFromTypeContext(PrystParser::TypeContext* ctx) {
    if (!ctx) return VOID_TYPE;

    auto basicTypeCtx = ctx->basicType();
    if (basicTypeCtx) {
        if (basicTypeCtx->VOID()) return VOID_TYPE;
        if (basicTypeCtx->INT()) return INT_TYPE;
        if (basicTypeCtx->FLOAT()) return FLOAT_TYPE;
        if (basicTypeCtx->BOOL()) return BOOL_TYPE;
        if (basicTypeCtx->STR()) return STRING_TYPE;
        if (basicTypeCtx->IDENTIFIER()) {
            return std::make_shared<ClassType>(basicTypeCtx->IDENTIFIER()->getText());
        }
    }

    // Handle array types
    auto arrayTypeCtx = ctx->arrayType();
    if (arrayTypeCtx) {
        auto elementTypeCtx = arrayTypeCtx->type();
        if (elementTypeCtx) {
            auto elementType = getTypeFromTypeContext(elementTypeCtx);
            return std::make_shared<ArrayType>(elementType);
        }
    }

    // Handle map types
    auto mapTypeCtx = ctx->mapType();
    if (mapTypeCtx) {
        auto keyTypeCtx = mapTypeCtx->keyType();
        auto valueTypeCtx = mapTypeCtx->type();
        if (keyTypeCtx && valueTypeCtx) {
            auto keyType = keyTypeCtx->STR() ? STRING_TYPE : INT_TYPE;
            auto valueType = getTypeFromTypeContext(valueTypeCtx);
            return std::make_shared<MapType>(keyType, valueType);
        }
    }

    return ERROR_TYPE;
}

LLVMCodeGen::LLVMCodeGen(llvm::LLVMContext& context, llvm::Module& module, llvm::IRBuilder<>& builder, TypeRegistry& registry)
    : context(context),
      module(module),
      builder(builder),
      typeRegistry(registry) {
    initializeRuntime();
}

void LLVMCodeGen::initModule(const std::string& moduleName) {
    initializeRuntime();
}

void LLVMCodeGen::initializeRuntime() {
    auto i8PtrTy = llvm::Type::getInt8PtrTy(context);
    auto i64Ty = llvm::Type::getInt64Ty(context);
    auto voidTy = llvm::Type::getVoidTy(context);

    // Initialize GC allocation function
    auto gcAllocType = llvm::FunctionType::get(i8PtrTy, {i64Ty}, false);
    module.getOrInsertFunction("GC_malloc", gcAllocType);

    // Initialize String allocation and operations
    auto stringAllocType = llvm::FunctionType::get(i8PtrTy, {i64Ty}, false);
    module.getOrInsertFunction("String_alloc", stringAllocType);

    auto stringLengthType = llvm::FunctionType::get(i64Ty, {i8PtrTy}, false);
    module.getOrInsertFunction("String_length", stringLengthType);

    auto stringConcatType = llvm::FunctionType::get(i8PtrTy, {i8PtrTy, i8PtrTy}, false);
    module.getOrInsertFunction("String_concat", stringConcatType);

    // Initialize Array allocation and operations
    auto arrayAllocType = llvm::FunctionType::get(i8PtrTy, {i64Ty}, false);
    module.getOrInsertFunction("Array_alloc", arrayAllocType);

    auto arrayGrowType = llvm::FunctionType::get(voidTy, {i8PtrTy, i64Ty}, false);
    module.getOrInsertFunction("Array_grow", arrayGrowType);

    auto arrayGetType = llvm::FunctionType::get(i8PtrTy, {i8PtrTy, i64Ty}, false);
    module.getOrInsertFunction("Array_get", arrayGetType);

    auto arraySetType = llvm::FunctionType::get(voidTy, {i8PtrTy, i64Ty, i8PtrTy}, false);
    module.getOrInsertFunction("Array_set", arraySetType);

    auto arrayLengthType = llvm::FunctionType::get(i64Ty, {i8PtrTy}, false);
    module.getOrInsertFunction("Array_length", arrayLengthType);

    // Initialize Map allocation and operations
    auto mapAllocType = llvm::FunctionType::get(i8PtrTy, {}, false);
    module.getOrInsertFunction("Map_alloc", mapAllocType);

    auto mapGetType = llvm::FunctionType::get(i8PtrTy, {i8PtrTy, i8PtrTy}, false);
    module.getOrInsertFunction("Map_get", mapGetType);

    auto mapSetType = llvm::FunctionType::get(voidTy, {i8PtrTy, i8PtrTy, i8PtrTy}, false);
    module.getOrInsertFunction("Map_set", mapSetType);

    auto mapHasType = llvm::FunctionType::get(llvm::Type::getInt1Ty(context), {i8PtrTy, i8PtrTy}, false);
    module.getOrInsertFunction("Map_has", mapHasType);

    auto mapRemoveType = llvm::FunctionType::get(voidTy, {i8PtrTy, i8PtrTy}, false);
    module.getOrInsertFunction("Map_remove", mapRemoveType);

    auto mapKeysType = llvm::FunctionType::get(i8PtrTy, {i8PtrTy}, false);
    module.getOrInsertFunction("Map_keys", mapKeysType);

    auto mapValuesType = llvm::FunctionType::get(i8PtrTy, {i8PtrTy}, false);
    module.getOrInsertFunction("Map_values", mapValuesType);

    auto mapLengthType = llvm::FunctionType::get(i64Ty, {i8PtrTy}, false);
    module.getOrInsertFunction("Map_length", mapLengthType);
}

llvm::Function* LLVMCodeGen::getOrCreateGCAlloc() {
    return module.getFunction("GC_malloc");
}


llvm::Function* LLVMCodeGen::getOrCreateStringAlloc() {
    return module.getFunction("String_alloc");
}

llvm::Function* LLVMCodeGen::getOrCreateArrayAlloc() {
    return module.getFunction("Array_alloc");
}

llvm::Function* LLVMCodeGen::getOrCreateMapAlloc() {
    return module.getFunction("Map_alloc");
}

// Visitor pattern implementation
std::any LLVMCodeGen::visitProgram(PrystParser::ProgramContext* ctx) {
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return nullptr;
}

std::any LLVMCodeGen::visitVarDecl(PrystParser::VarDeclContext* ctx) {
    auto type = getLLVMType(getTypeFromTypeContext(ctx->type()));

    auto alloca = builder.CreateAlloca(type, nullptr, ctx->IDENTIFIER()->getText());

    if (ctx->expression()) {
        auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
        builder.CreateStore(value, alloca);
    }

    valueMap[ctx->IDENTIFIER()->getText()] = alloca;
    return alloca;
}

std::any LLVMCodeGen::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    std::vector<llvm::Type*> paramTypes;
    if (ctx->parameters()) {
        for (auto param : ctx->parameters()->parameter()) {
            auto paramType = getLLVMType(getTypeFromTypeContext(param->type()));
            paramTypes.push_back(paramType);
        }
    }

    auto returnType = !ctx->type().empty() ?
        getLLVMType(getTypeFromTypeContext(ctx->type(0))) :
        llvm::Type::getVoidTy(context);

    auto funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                                   ctx->IDENTIFIER()->getText(), module);

    auto entry = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);

    // Add parameters to value map
    if (ctx->parameters()) {
        auto argIt = func->arg_begin();
        for (auto param : ctx->parameters()->parameter()) {
            valueMap[param->IDENTIFIER()->getText()] = argIt++;
        }
    }

    visit(ctx->block());

    if (!builder.GetInsertBlock()->getTerminator()) {
        if (returnType->isVoidTy()) {
            builder.CreateRetVoid();
        } else {
            builder.CreateRet(llvm::Constant::getNullValue(returnType));
        }
    }

    return func;
}

std::any LLVMCodeGen::visitClassDecl(PrystParser::ClassDeclContext* ctx) {
    auto identifiers = ctx->IDENTIFIER();
    if (!hasToken(identifiers)) {
        throw std::runtime_error("Class declaration requires a name");
    }
    std::string className = getTokenText(identifiers);
    std::vector<std::pair<std::string, llvm::Type*>> members;

    // Handle field declarations
    auto types = ctx->type();
    for (size_t i = 0; i < types.size(); i++) {
        auto type = getLLVMType(getTypeFromTypeContext(types[i]));
        auto memberName = getTokenText(identifiers, i + 1);  // +1 to skip class name
        members.push_back({memberName, type});
    }

    // Register class with type registry
    typeRegistry.registerClass(className, members);
    auto classType = typeRegistry.getClassType(className);

    std::string ctorName = className + "_constructor";
    auto ctorType = llvm::FunctionType::get(classType->getPointerTo(), {}, false);
    auto ctor = llvm::Function::Create(ctorType, llvm::Function::ExternalLinkage,
                                   ctorName, module);

    auto entry = llvm::BasicBlock::Create(context, "entry", ctor);
    builder.SetInsertPoint(entry);

    // Allocate instance
    auto allocFn = getOrCreateGCAlloc();
    auto sizeOfClass = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context),
        module.getDataLayout().getTypeAllocSize(classType));
    std::vector<llvm::Value*> allocArgs = {sizeOfClass};
    auto instance = builder.CreateCall(llvm::FunctionCallee(allocFn), allocArgs, "instance");
    auto typedInstance = builder.CreateBitCast(instance, classType->getPointerTo());

    // Initialize fields to null/zero
    for (size_t i = 0; i < members.size(); i++) {
        auto memberPtr = builder.CreateStructGEP(classType, typedInstance, i,
            members[i].first + "_ptr");
        builder.CreateStore(llvm::Constant::getNullValue(members[i].second), memberPtr);
    }

    // Handle method declarations
    for (auto method : ctx->functionDecl()) {
        std::vector<llvm::Type*> paramTypes;
        paramTypes.push_back(classType->getPointerTo());  // 'this' pointer

        if (hasContext(method->parameters())) {
            for (auto param : getContext(method->parameters())->parameter()) {
                paramTypes.push_back(getLLVMType(Type::fromString(param->type()->getText())));
            }
        }

        auto returnType = !method->type().empty() ?
            getLLVMType(getTypeFromTypeContext(method->type(0))) :
            llvm::Type::getVoidTy(context);

        auto methodType = llvm::FunctionType::get(returnType, paramTypes, false);
        auto methodFunc = llvm::Function::Create(methodType, llvm::Function::ExternalLinkage,
            className + "_" + getTokenText(method->IDENTIFIER()), module);

        auto methodEntry = llvm::BasicBlock::Create(context, "entry", methodFunc);
        builder.SetInsertPoint(methodEntry);

        // Set up 'this' pointer and parameters
        auto thisArg = methodFunc->arg_begin();
        valueMap["this"] = thisArg;

        auto argIt = methodFunc->arg_begin() + 1;
        if (hasContext(method->parameters())) {
            for (auto param : getContext(method->parameters())->parameter()) {
                valueMap[getTokenText(param->IDENTIFIER())] = argIt++;
            }
        }

        visit(method->block());

        if (!builder.GetInsertBlock()->getTerminator()) {
            if (returnType->isVoidTy()) {
                builder.CreateRetVoid();
            } else {
                builder.CreateRet(llvm::Constant::getNullValue(returnType));
            }
        }
    }

    // Return from constructor
    builder.SetInsertPoint(entry);
    builder.CreateRet(typedInstance);

    return nullptr;
}

std::any LLVMCodeGen::visitIfStmt(PrystParser::IfStmtContext* ctx) {
    auto condition = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    if (!condition->getType()->isIntegerTy(1)) {
        condition = builder.CreateICmpNE(condition,
            llvm::Constant::getNullValue(condition->getType()), "ifcond");
    }

    auto function = builder.GetInsertBlock()->getParent();

    auto thenBlock = llvm::BasicBlock::Create(context, "then", function);
    auto mergeBlock = llvm::BasicBlock::Create(context, "ifcont");

    bool hasElse = ctx->ELSE() != nullptr;
    auto elseBlock = hasElse ? llvm::BasicBlock::Create(context, "else") : mergeBlock;

    builder.CreateCondBr(condition, thenBlock, elseBlock);

    // Generate then block
    builder.SetInsertPoint(thenBlock);
    if (ctx->statement().size() > 0) {
        visit(ctx->statement(0));
    }
    if (!builder.GetInsertBlock()->getTerminator()) {
        builder.CreateBr(mergeBlock);
    }

    // Generate else block if it exists
    if (hasElse) {
        function->getBasicBlockList().push_back(elseBlock);
        builder.SetInsertPoint(elseBlock);
        if (ctx->statement().size() > 1) {
            visit(ctx->statement(1));
        }
        if (!builder.GetInsertBlock()->getTerminator()) {
            builder.CreateBr(mergeBlock);
        }
    }

    function->getBasicBlockList().push_back(mergeBlock);
    builder.SetInsertPoint(mergeBlock);

    return nullptr;
}

std::any LLVMCodeGen::visitWhileStmt(PrystParser::WhileStmtContext* ctx) {
    auto function = builder.GetInsertBlock()->getParent();

    auto condBlock = llvm::BasicBlock::Create(context, "whilecond", function);
    auto loopBlock = llvm::BasicBlock::Create(context, "whileloop");
    auto afterBlock = llvm::BasicBlock::Create(context, "whilecont");

    // Push loop context for break/continue
    loopStack.push_back({condBlock, afterBlock});

    builder.CreateBr(condBlock);

    builder.SetInsertPoint(condBlock);
    auto condition = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    if (!condition->getType()->isIntegerTy(1)) {
        condition = builder.CreateICmpNE(condition,
            llvm::Constant::getNullValue(condition->getType()), "whilecond");
    }

    builder.CreateCondBr(condition, loopBlock, afterBlock);

    function->getBasicBlockList().push_back(loopBlock);
    builder.SetInsertPoint(loopBlock);
    visit(ctx->statement());
    if (!builder.GetInsertBlock()->getTerminator()) {
        builder.CreateBr(condBlock);
    }

    // Pop loop context
    loopStack.pop_back();

    function->getBasicBlockList().push_back(afterBlock);
    builder.SetInsertPoint(afterBlock);

    return nullptr;
}

std::any LLVMCodeGen::visitForStmt(PrystParser::ForStmtContext* ctx) {
    auto function = builder.GetInsertBlock()->getParent();

    if (ctx->type()) {  // For-in loop
        auto iterableExpr = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
        auto itemType = getLLVMType(getTypeFromTypeContext(ctx->type()));

        auto initBlock = llvm::BasicBlock::Create(context, "forinit", function);
        auto condBlock = llvm::BasicBlock::Create(context, "forcond");
        auto loopBlock = llvm::BasicBlock::Create(context, "forloop");
        auto afterBlock = llvm::BasicBlock::Create(context, "forcont");

        // Push loop context for break/continue
        loopStack.push_back({condBlock, afterBlock});

        builder.CreateBr(initBlock);
        builder.SetInsertPoint(initBlock);
        auto iterator = builder.CreateAlloca(llvm::Type::getInt64Ty(context), nullptr, "iterator");
        builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 0), iterator);

        function->getBasicBlockList().push_back(condBlock);
        builder.SetInsertPoint(condBlock);
        auto currentIdx = builder.CreateLoad(llvm::Type::getInt64Ty(context), iterator, "idx");
        auto lengthFn = module.getFunction("Array_length");
        std::vector<llvm::Value*> lengthArgs;
        lengthArgs.push_back(iterableExpr);
        auto length = builder.CreateCall(llvm::FunctionCallee(lengthFn), lengthArgs, "length");
        auto condition = builder.CreateICmpSLT(currentIdx, length, "forcond");

        builder.CreateCondBr(condition, loopBlock, afterBlock);

        function->getBasicBlockList().push_back(loopBlock);
        builder.SetInsertPoint(loopBlock);

        auto item = builder.CreateAlloca(itemType, nullptr, ctx->IDENTIFIER()->getText());
        auto getFn = module.getFunction("Array_get");
        std::vector<llvm::Value*> getArgs;
        getArgs.push_back(iterableExpr);
        getArgs.push_back(currentIdx);
        auto currentItem = builder.CreateCall(llvm::FunctionCallee(getFn), getArgs, "item");
        builder.CreateStore(currentItem, item);
        valueMap[ctx->IDENTIFIER()->getText()] = item;

        visit(ctx->block());

        auto nextIdx = builder.CreateAdd(currentIdx,
            llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 1), "nextidx");
        builder.CreateStore(nextIdx, iterator);

        if (!builder.GetInsertBlock()->getTerminator()) {
            builder.CreateBr(condBlock);
        }

        // Pop loop context
        loopStack.pop_back();

    } else {  // C-style for loop
        auto initBlock = llvm::BasicBlock::Create(context, "forinit", function);
        auto condBlock = llvm::BasicBlock::Create(context, "forcond");
        auto loopBlock = llvm::BasicBlock::Create(context, "forloop");
        auto incrBlock = llvm::BasicBlock::Create(context, "forincr");
        auto afterBlock = llvm::BasicBlock::Create(context, "forcont");

        // Push loop context for break/continue
        loopStack.push_back({condBlock, afterBlock});

        // Initialize
        builder.CreateBr(initBlock);
        builder.SetInsertPoint(initBlock);
        if (ctx->varDecl()) {
            visit(ctx->varDecl());
        }
        builder.CreateBr(condBlock);

        // Condition
        function->getBasicBlockList().push_back(condBlock);
        builder.SetInsertPoint(condBlock);
        llvm::Value* condition;
        if (ctx->expression().size() > 0) {
            condition = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
            if (!condition->getType()->isIntegerTy(1)) {
                condition = builder.CreateICmpNE(condition,
                    llvm::Constant::getNullValue(condition->getType()), "forcond");
            }
        } else {
            // If condition is omitted, use true
            condition = llvm::ConstantInt::getTrue(context);
        }
        builder.CreateCondBr(condition, loopBlock, afterBlock);

        // Loop body
        function->getBasicBlockList().push_back(loopBlock);
        builder.SetInsertPoint(loopBlock);
        visit(ctx->block());
        if (!builder.GetInsertBlock()->getTerminator()) {
            builder.CreateBr(incrBlock);
        }

        // Increment
        function->getBasicBlockList().push_back(incrBlock);
        builder.SetInsertPoint(incrBlock);
        if (ctx->expression().size() > 1) {
            visit(ctx->expression(1));
        }
        builder.CreateBr(condBlock);

        // Pop loop context
        loopStack.pop_back();

        function->getBasicBlockList().push_back(afterBlock);
        builder.SetInsertPoint(afterBlock);
    }

    return nullptr;
}

std::any LLVMCodeGen::visitTryStmt(PrystParser::TryStmtContext* ctx) {
    auto function = builder.GetInsertBlock()->getParent();

    auto tryBlock = llvm::BasicBlock::Create(context, "try", function);
    auto catchBlock = llvm::BasicBlock::Create(context, "catch");
    auto continueBlock = llvm::BasicBlock::Create(context, "trycont");

    auto personality = module.getOrInsertFunction("__gxx_personality_v0",
        llvm::FunctionType::get(llvm::Type::getInt32Ty(context), true));

    auto ehException = llvm::StructType::create(context, "struct.Exception");
    auto ehExceptionPtr = llvm::PointerType::getUnqual(ehException);

    builder.CreateBr(tryBlock);
    builder.SetInsertPoint(tryBlock);

    auto exceptionVar = builder.CreateAlloca(ehExceptionPtr, nullptr, "exception");
    valueMap[ctx->IDENTIFIER()->getText()] = exceptionVar;

    // Visit the try block
    visit(ctx->statement(0));
    if (!builder.GetInsertBlock()->getTerminator()) {
        builder.CreateBr(continueBlock);
    }

    function->getBasicBlockList().push_back(catchBlock);
    builder.SetInsertPoint(catchBlock);

    // Visit the catch block
    visit(ctx->statement(1));
    if (!builder.GetInsertBlock()->getTerminator()) {
        builder.CreateBr(continueBlock);
    }

    function->getBasicBlockList().push_back(continueBlock);
    builder.SetInsertPoint(continueBlock);

    return nullptr;
}

std::any LLVMCodeGen::visitReturnStmt(PrystParser::ReturnStmtContext* ctx) {
    auto function = builder.GetInsertBlock()->getParent();
    auto returnType = function->getReturnType();

    if (ctx->expression()) {
        auto returnValue = std::any_cast<llvm::Value*>(visit(ctx->expression()));

        if (returnValue->getType() != returnType) {
            if (returnType->isFloatingPointTy() && returnValue->getType()->isIntegerTy()) {
                returnValue = builder.CreateSIToFP(returnValue, returnType, "conv");
            } else if (returnType->isIntegerTy() && returnValue->getType()->isFloatingPointTy()) {
                returnValue = builder.CreateFPToSI(returnValue, returnType, "conv");
            } else if (returnType->isPointerTy() && returnValue->getType()->isPointerTy()) {
                returnValue = builder.CreateBitCast(returnValue, returnType, "conv");
            } else {
                throw std::runtime_error("Invalid return type conversion");
            }
        }

        builder.CreateRet(returnValue);
    } else {
        if (!returnType->isVoidTy()) {
            throw std::runtime_error("Non-void function must return a value");
        }
        builder.CreateRetVoid();
    }

    return nullptr;
}

std::any LLVMCodeGen::visitPrimaryExpr(PrystParser::PrimaryExprContext* ctx) {
    return visit(ctx->primary());
}

std::any LLVMCodeGen::visitBuiltinFunctionCall(PrystParser::BuiltinFunctionCallContext* ctx) {
    auto funcName = getTokenText(ctx->IDENTIFIER());
    auto callee = module.getFunction(funcName);
    if (!callee) {
        throw std::runtime_error("Unknown builtin function: " + funcName);
    }

    std::vector<llvm::Value*> args;
    if (hasContext(ctx->arguments())) {
        for (auto arg : getContext(ctx->arguments())->expression()) {
            args.push_back(std::any_cast<llvm::Value*>(visit(arg)));
        }
    }

    return (llvm::Value*)builder.CreateCall(llvm::FunctionCallee(callee), args);
}

std::any LLVMCodeGen::visitConstructorExpr(PrystParser::ConstructorExprContext* ctx) {
    std::string className = getTokenText(ctx->IDENTIFIER());
    if (!typeRegistry.hasClass(className)) {
        throw std::runtime_error("Unknown class: " + className);
    }
    auto ctor = module.getFunction(className + "_constructor");
    if (!ctor) {
        throw std::runtime_error("Constructor not found for class: " + className);
    }

    std::vector<llvm::Value*> args;
    if (hasContext(ctx->arguments())) {
        for (auto arg : getContext(ctx->arguments())->expression()) {
            args.push_back(std::any_cast<llvm::Value*>(visit(arg)));
        }
    }
    return (llvm::Value*)builder.CreateCall(llvm::FunctionCallee(ctor), args);
}

std::any LLVMCodeGen::visitMemberAccessExpr(PrystParser::MemberAccessExprContext* ctx) {
    auto base = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto memberName = getTokenText(ctx->IDENTIFIER());
    auto className = base->getType()->getPointerElementType()->getStructName().str();
    auto classType = typeRegistry.getClassType(className);
    auto memberIdx = typeRegistry.getMemberIndex(className, memberName);
    return builder.CreateStructGEP(classType, base, memberIdx, memberName + "_ptr");
}

std::any LLVMCodeGen::visitNullableMemberExpr(PrystParser::NullableMemberExprContext* ctx) {
    auto base = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto memberName = getTokenText(ctx->IDENTIFIER());

    // Create basic blocks for null check
    auto function = builder.GetInsertBlock()->getParent();
    auto nullCheck = llvm::BasicBlock::Create(context, "null_check", function);
    auto notNull = llvm::BasicBlock::Create(context, "not_null");
    auto merge = llvm::BasicBlock::Create(context, "merge");

    // Check if base is null
    auto isNull = builder.CreateICmpEQ(base, llvm::Constant::getNullValue(base->getType()));
    builder.CreateCondBr(isNull, merge, notNull);

    // Handle non-null case
    function->getBasicBlockList().push_back(notNull);
    builder.SetInsertPoint(notNull);
    auto className = base->getType()->getPointerElementType()->getStructName().str();
    auto classType = typeRegistry.getClassType(className);
    auto memberIdx = typeRegistry.getMemberIndex(className, memberName);
    auto result = builder.CreateStructGEP(classType, base, memberIdx, memberName + "_ptr");
    builder.CreateBr(merge);

    // Merge point
    function->getBasicBlockList().push_back(merge);
    builder.SetInsertPoint(merge);
    auto phi = builder.CreatePHI(result->getType(), 2);
    phi->addIncoming(llvm::Constant::getNullValue(result->getType()), builder.GetInsertBlock());
    phi->addIncoming(result, notNull);

    return phi;
}

std::any LLVMCodeGen::visitMethodCallExpr(PrystParser::MethodCallExprContext* ctx) {
    auto base = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto methodName = getTokenText(ctx->IDENTIFIER());
    auto className = base->getType()->getPointerElementType()->getStructName().str();
    auto callee = module.getFunction(className + "_" + methodName);

    if (!callee) {
        throw std::runtime_error("Unknown method: " + methodName);
    }

    std::vector<llvm::Value*> args;
    args.push_back(base);  // this pointer
    if (hasContext(ctx->arguments())) {
        for (auto arg : getContext(ctx->arguments())->expression()) {
            args.push_back(std::any_cast<llvm::Value*>(visit(arg)));
        }
    }
    return (llvm::Value*)builder.CreateCall(llvm::FunctionCallee(callee), args);
}

std::any LLVMCodeGen::visitArrayAccessExpr(PrystParser::ArrayAccessExprContext* ctx) {
    auto array = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto index = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));
    auto getFn = module.getFunction("Array_get");
    std::vector<llvm::Value*> args = {array, index};
    return (llvm::Value*)builder.CreateCall(llvm::FunctionCallee(getFn), args);
}

std::any LLVMCodeGen::visitCastExpr(PrystParser::CastExprContext* ctx) {
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto targetType = getLLVMType(getTypeFromTypeContext(ctx->type()));
    return convertType(value, targetType);
}

std::any LLVMCodeGen::visitParenExpr(PrystParser::ParenExprContext* ctx) {
    return visit(ctx->expression());
}

std::any LLVMCodeGen::visitPrefixExpr(PrystParser::PrefixExprContext* ctx) {
    auto operand = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    if (ctx->NOT()) {
        if (!operand->getType()->isIntegerTy(1)) {
            operand = builder.CreateICmpNE(operand,
                llvm::Constant::getNullValue(operand->getType()), "tobool");
        }
        return (llvm::Value*)builder.CreateNot(operand, "nottmp");
    }

    if (ctx->MINUS()) {
        if (operand->getType()->isFloatingPointTy()) {
            return (llvm::Value*)builder.CreateFNeg(operand, "negtmp");
        }
        return (llvm::Value*)builder.CreateNeg(operand, "negtmp");
    }

    throw std::runtime_error("Unsupported prefix operator");
}

std::any LLVMCodeGen::visitPostfixExpr(PrystParser::PostfixExprContext* ctx) {
    if (ctx->expression()) {
        auto base = std::any_cast<llvm::Value*>(visit(ctx->expression()));

        // Member access
        if (ctx->DOT() && ctx->IDENTIFIER() && !ctx->LPAREN()) {
            auto memberName = ctx->IDENTIFIER()->getText();
            auto className = base->getType()->getPointerElementType()->getStructName().str();
            auto classType = typeRegistry.getClassType(className);
            auto memberIdx = typeRegistry.getMemberIndex(className, memberName);
            return builder.CreateStructGEP(classType, base, memberIdx, memberName + "_ptr");
        }

        // Array access
        if (ctx->LBRACK()) {
            auto index = std::any_cast<llvm::Value*>(visit(ctx->expression()));
            auto getFn = module.getFunction("Array_get");
            std::vector<llvm::Value*> args;
            args.push_back(base);
            args.push_back(index);
            return (llvm::Value*)builder.CreateCall(llvm::FunctionCallee(getFn), args);
        }

        // Method call
        if (ctx->DOT() && ctx->IDENTIFIER() && ctx->LPAREN()) {
            auto methodName = ctx->IDENTIFIER()->getText();
            auto className = base->getType()->getPointerElementType()->getStructName().str();
            auto callee = module.getFunction(className + "_" + methodName);

            if (!callee) {
                throw std::runtime_error("Unknown method: " + methodName);
            }

            std::vector<llvm::Value*> args;
            args.push_back(base);  // this pointer
            if (ctx->arguments()) {
                for (auto arg : ctx->arguments()->expression()) {
                    args.push_back(std::any_cast<llvm::Value*>(visit(arg)));
                }
            }
            return (llvm::Value*)builder.CreateCall(llvm::FunctionCallee(callee), args);
        }
    }

    // Function call
    if (ctx->IDENTIFIER() && ctx->LPAREN()) {
        auto funcName = ctx->IDENTIFIER()->getText();
        auto callee = module.getFunction(funcName);
        if (!callee) {
            throw std::runtime_error("Unknown function: " + funcName);
        }

        std::vector<llvm::Value*> args;
        if (ctx->arguments()) {
            for (auto arg : ctx->arguments()->expression()) {
                args.push_back(std::any_cast<llvm::Value*>(visit(arg)));
            }
        }

        return (llvm::Value*)builder.CreateCall(llvm::FunctionCallee(callee), args);
    }

    throw std::runtime_error("Unsupported postfix expression");
}

std::any LLVMCodeGen::visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext* ctx) {
    auto left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

    if (ctx->STAR()) return createMul(left, right);
    if (ctx->SLASH()) return createDiv(left, right);
    if (ctx->PERCENT()) return createMod(left, right);

    throw std::runtime_error("Unknown multiplicative operator");
}

std::any LLVMCodeGen::visitAdditiveExpr(PrystParser::AdditiveExprContext* ctx) {
    auto left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

    if (ctx->PLUS()) return createAdd(left, right);
    if (ctx->MINUS()) return createSub(left, right);

    throw std::runtime_error("Unknown additive operator");
}

std::any LLVMCodeGen::visitRelationalExpr(PrystParser::RelationalExprContext* ctx) {
    auto left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

    if (ctx->LT()) return createLT(left, right);
    if (ctx->GT()) return createGT(left, right);
    if (ctx->LE()) return createLE(left, right);
    if (ctx->GE()) return createGE(left, right);

    throw std::runtime_error("Unknown relational operator");
}

std::any LLVMCodeGen::visitEqualityExpr(PrystParser::EqualityExprContext* ctx) {
    auto left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

    if (ctx->EQ()) return createEQ(left, right);
    if (ctx->NEQ()) return createNEQ(left, right);

    throw std::runtime_error("Unknown equality operator");
}

std::any LLVMCodeGen::visitLogicalAndExpr(PrystParser::LogicalAndExprContext* ctx) {
    auto left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));
    return createAnd(left, right);
}

std::any LLVMCodeGen::visitLogicalOrExpr(PrystParser::LogicalOrExprContext* ctx) {
    auto left = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto right = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));
    return createOr(left, right);
}

std::any LLVMCodeGen::visitConditionalExpr(PrystParser::ConditionalExprContext* ctx) {
    auto condition = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));

    // Create basic blocks
    auto function = builder.GetInsertBlock()->getParent();
    auto thenBlock = llvm::BasicBlock::Create(context, "then", function);
    auto elseBlock = llvm::BasicBlock::Create(context, "else");
    auto mergeBlock = llvm::BasicBlock::Create(context, "merge");

    if (!condition->getType()->isIntegerTy(1)) {
        condition = builder.CreateICmpNE(condition,
            llvm::Constant::getNullValue(condition->getType()), "cond");
    }
    builder.CreateCondBr(condition, thenBlock, elseBlock);

    // Then block
    builder.SetInsertPoint(thenBlock);
    auto thenValue = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));
    builder.CreateBr(mergeBlock);
    thenBlock = builder.GetInsertBlock();

    // Else block
    function->getBasicBlockList().push_back(elseBlock);
    builder.SetInsertPoint(elseBlock);
    auto elseValue = std::any_cast<llvm::Value*>(visit(ctx->expression(2)));
    builder.CreateBr(mergeBlock);
    elseBlock = builder.GetInsertBlock();

    // Merge block
    function->getBasicBlockList().push_back(mergeBlock);
    builder.SetInsertPoint(mergeBlock);
    auto phi = builder.CreatePHI(thenValue->getType(), 2, "condtmp");
    phi->addIncoming(thenValue, thenBlock);
    phi->addIncoming(elseValue, elseBlock);

    return phi;
}

std::any LLVMCodeGen::visitAssignmentExpr(PrystParser::AssignmentExprContext* ctx) {
    auto target = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

    if (target->getType() != value->getType()) {
        value = convertType(value, target->getType());
    }

    builder.CreateStore(value, target);
    return value;
}

llvm::Value* LLVMCodeGen::createAdd(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFAdd(left, right, "addtmp");
    }
    return builder.CreateAdd(left, right, "addtmp");
}

llvm::Value* LLVMCodeGen::createSub(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFSub(left, right, "subtmp");
    }
    return builder.CreateSub(left, right, "subtmp");
}

llvm::Value* LLVMCodeGen::createMul(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFMul(left, right, "multmp");
    }
    return builder.CreateMul(left, right, "multmp");
}

llvm::Value* LLVMCodeGen::createDiv(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFDiv(left, right, "divtmp");
    }
    return builder.CreateSDiv(left, right, "divtmp");
}

llvm::Value* LLVMCodeGen::createMod(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFRem(left, right, "modtmp");
    }
    return builder.CreateSRem(left, right, "modtmp");
}

llvm::Value* LLVMCodeGen::createLT(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFCmpOLT(left, right, "lttmp");
    }
    return builder.CreateICmpSLT(left, right, "lttmp");
}

llvm::Value* LLVMCodeGen::createGT(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFCmpOGT(left, right, "gttmp");
    }
    return builder.CreateICmpSGT(left, right, "gttmp");
}

llvm::Value* LLVMCodeGen::createLE(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFCmpOLE(left, right, "letmp");
    }
    return builder.CreateICmpSLE(left, right, "letmp");
}

llvm::Value* LLVMCodeGen::createGE(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFCmpOGE(left, right, "getmp");
    }
    return builder.CreateICmpSGE(left, right, "getmp");
}

llvm::Value* LLVMCodeGen::createEQ(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFCmpOEQ(left, right, "eqtmp");
    }
    return builder.CreateICmpEQ(left, right, "eqtmp");
}

llvm::Value* LLVMCodeGen::createNEQ(llvm::Value* left, llvm::Value* right) {
    if (left->getType()->isFloatingPointTy() || right->getType()->isFloatingPointTy()) {
        left = convertToFloat(left);
        right = convertToFloat(right);
        return builder.CreateFCmpONE(left, right, "neqtmp");
    }
    return builder.CreateICmpNE(left, right, "neqtmp");
}

llvm::Value* LLVMCodeGen::createAnd(llvm::Value* left, llvm::Value* right) {
    if (!left->getType()->isIntegerTy(1)) {
        left = builder.CreateICmpNE(left,
            llvm::Constant::getNullValue(left->getType()), "tobool");
    }
    if (!right->getType()->isIntegerTy(1)) {
        right = builder.CreateICmpNE(right,
            llvm::Constant::getNullValue(right->getType()), "tobool");
    }
    return builder.CreateAnd(left, right, "andtmp");
}

llvm::Value* LLVMCodeGen::createOr(llvm::Value* left, llvm::Value* right) {
    if (!left->getType()->isIntegerTy(1)) {
        left = builder.CreateICmpNE(left,
            llvm::Constant::getNullValue(left->getType()), "tobool");
    }
    if (!right->getType()->isIntegerTy(1)) {
        right = builder.CreateICmpNE(right,
            llvm::Constant::getNullValue(right->getType()), "tobool");
    }
    return builder.CreateOr(left, right, "ortmp");
}

llvm::Value* LLVMCodeGen::convertToFloat(llvm::Value* value) {
    if (value->getType()->isFloatingPointTy()) {
        return value;
    }
    if (value->getType()->isIntegerTy()) {
        return builder.CreateSIToFP(value, llvm::Type::getDoubleTy(context), "tofloat");
    }
    throw std::runtime_error("Cannot convert type to float");
}

llvm::Value* LLVMCodeGen::convertType(llvm::Value* value, llvm::Type* targetType) {
    auto sourceType = value->getType();

    if (sourceType == targetType) {
        return value;
    }

    if (sourceType->isIntegerTy() && targetType->isFloatingPointTy()) {
        return builder.CreateSIToFP(value, targetType, "int2float");
    }

    if (sourceType->isFloatingPointTy() && targetType->isIntegerTy()) {
        return builder.CreateFPToSI(value, targetType, "float2int");
    }

    if (sourceType->isIntegerTy() && targetType->isIntegerTy(1)) {
        return builder.CreateICmpNE(value,
            llvm::Constant::getNullValue(sourceType), "int2bool");
    }

    if (sourceType->isIntegerTy(1) && targetType->isIntegerTy()) {
        return builder.CreateZExt(value, targetType, "bool2int");
    }

    throw std::runtime_error("Unsupported type conversion");
}

std::any LLVMCodeGen::visitPrimary(PrystParser::PrimaryContext* ctx) {
    if (hasToken(ctx->INTEGER())) {
        return (llvm::Value*)llvm::ConstantInt::get(llvm::Type::getInt64Ty(context),
            std::stoll(getTokenText(ctx->INTEGER())), true);
    }

    if (hasToken(ctx->FLOAT_LITERAL())) {
        return (llvm::Value*)llvm::ConstantFP::get(llvm::Type::getDoubleTy(context),
            std::stod(getTokenText(ctx->FLOAT_LITERAL())));
    }

    if (hasToken(ctx->STRING())) {
        std::string str = getTokenText(ctx->STRING());
        str = str.substr(1, str.length() - 2);  // Remove quotes
        auto stringConstant = builder.CreateGlobalStringPtr(str, "str");
        auto allocFn = getOrCreateStringAlloc();
        std::vector<llvm::Value*> allocArgs = {
            llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), str.length())
        };
        auto stringAlloc = builder.CreateCall(llvm::FunctionCallee(allocFn), allocArgs, "stralloc");

        builder.CreateMemCpy(stringAlloc, llvm::MaybeAlign(1),
            stringConstant, llvm::MaybeAlign(1),
            str.length());

        return (llvm::Value*)stringAlloc;
    }

    if (hasToken(ctx->BOOLEAN())) {
        return (llvm::Value*)llvm::ConstantInt::get(llvm::Type::getInt1Ty(context),
            getTokenText(ctx->BOOLEAN()) == "true");
    }

    if (hasToken(ctx->IDENTIFIER())) {
        auto it = valueMap.find(getTokenText(ctx->IDENTIFIER()));
        if (it == valueMap.end()) {
            throw std::runtime_error("Unknown variable: " + getTokenText(ctx->IDENTIFIER()));
        }
        return (llvm::Value*)builder.CreateLoad(it->second->getType()->getPointerElementType(),
            it->second, getTokenText(ctx->IDENTIFIER()));
    }

    if (hasContext(ctx->arrayLiteral())) {
        return visit(getContext(ctx->arrayLiteral()));
    }

    if (hasContext(ctx->mapLiteral())) {
        return visit(getContext(ctx->mapLiteral()));
    }

    throw std::runtime_error("Unsupported primary expression");
}

llvm::Type* LLVMCodeGen::getLLVMType(std::shared_ptr<Type> type) {
    if (!type) return llvm::Type::getVoidTy(context);

    switch (type->getKind()) {
        case Type::Kind::Int:
            return llvm::Type::getInt64Ty(context);
        case Type::Kind::Float:
            return llvm::Type::getDoubleTy(context);
        case Type::Kind::Bool:
            return llvm::Type::getInt1Ty(context);
        case Type::Kind::String:
            return llvm::Type::getInt8PtrTy(context);
        case Type::Kind::Void:
            return llvm::Type::getVoidTy(context);
        case Type::Kind::Array:
            if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(type)) {
                return llvm::Type::getInt8PtrTy(context);  // Arrays are opaque pointers
            }
            break;
        case Type::Kind::Map:
            if (auto mapType = std::dynamic_pointer_cast<MapType>(type)) {
                return llvm::Type::getInt8PtrTy(context);  // Maps are opaque pointers
            }
            break;
        case Type::Kind::Class:
            if (auto classType = std::dynamic_pointer_cast<ClassType>(type)) {
                return llvm::Type::getInt8PtrTy(context);  // Classes are opaque pointers
            }
            break;
        case Type::Kind::Error:
            return llvm::Type::getInt8PtrTy(context);  // Error type is an opaque pointer
    }

    return llvm::Type::getVoidTy(context);  // Default fallback
}

std::any LLVMCodeGen::visitBlock(PrystParser::BlockContext* ctx) {
    for (auto stmt : ctx->statement()) {
        visit(stmt);
    }
    return nullptr;
}

std::any LLVMCodeGen::visitStatement(PrystParser::StatementContext* ctx) {
    if (ctx->varDecl()) return visit(ctx->varDecl());
    if (ctx->ifStmt()) return visit(ctx->ifStmt());
    if (ctx->whileStmt()) return visit(ctx->whileStmt());
    if (ctx->forStmt()) return visit(ctx->forStmt());
    if (ctx->tryStmt()) return visit(ctx->tryStmt());
    if (ctx->returnStmt()) return visit(ctx->returnStmt());
    if (ctx->expressionStmt()) return visit(ctx->expressionStmt());
    if (ctx->breakStmt()) return visit(ctx->breakStmt());
    if (ctx->continueStmt()) return visit(ctx->continueStmt());

    throw std::runtime_error("Unsupported statement type");
}

std::any LLVMCodeGen::visitType(PrystParser::TypeContext* ctx) {
    // This method is used during type checking phase
    // For code generation, we use getLLVMType instead
    return nullptr;
}

std::any LLVMCodeGen::visitLambdaExpr(PrystParser::LambdaExprContext* ctx) {
    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;

    // Get parameter types and names
    auto params = ctx->lambdaParams();
    std::vector<std::pair<std::string, llvm::Type*>> parameters;

    if (params) {
        for (size_t i = 0; i < params->IDENTIFIER().size(); ++i) {
            auto paramType = getLLVMType(getTypeFromTypeContext(params->type(i)));
            parameters.push_back({params->IDENTIFIER(i)->getText(), paramType});
        }
    }

    // Get return type
    llvm::Type* returnType = ctx->type() ?
        getLLVMType(getTypeFromTypeContext(ctx->type())) :
        llvm::Type::getVoidTy(context);

    // Create function type and function
    std::vector<llvm::Type*> paramTypes;
    for (const auto& param : parameters) {
        paramTypes.push_back(param.second);
    }
    auto funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
        "lambda", module);

    // Create entry block
    auto entry = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);

    // Add parameters to value map
    auto argIt = func->arg_begin();
    for (const auto& paramName : paramNames) {
        valueMap[paramName] = argIt++;
    }

    // Generate lambda body
    if (hasContext(ctx->block())) {
        visit(getContext(ctx->block()));
    } else if (ctx->expr()) {
        auto result = std::any_cast<llvm::Value*>(visit(ctx->expr()));
        if (returnType->isVoidTy()) {
            builder.CreateRetVoid();
        } else {
            builder.CreateRet(result);
        }
    }

    // Add terminator if needed
    if (!builder.GetInsertBlock()->getTerminator()) {
        if (returnType->isVoidTy()) {
            builder.CreateRetVoid();
        } else {
            builder.CreateRet(llvm::Constant::getNullValue(returnType));
        }
    }

    return (llvm::Value*)func;
}

std::any LLVMCodeGen::visitExpressionStmt(PrystParser::ExpressionStmtContext* ctx) {
    if (ctx->expression()) {
        return visit(ctx->expression());
    }
    return nullptr;
}

std::any LLVMCodeGen::visitBreakStmt(PrystParser::BreakStmtContext* ctx) {
    auto function = builder.GetInsertBlock()->getParent();
    auto& blocks = function->getBasicBlockList();
    auto* afterBlock = &blocks.back();
    builder.CreateBr(afterBlock);
    return nullptr;
}

std::any LLVMCodeGen::visitContinueStmt(PrystParser::ContinueStmtContext* ctx) {
    auto function = builder.GetInsertBlock()->getParent();
    auto& blocks = function->getBasicBlockList();
    auto* condBlock = &blocks.front();
    builder.CreateBr(condBlock);
    return nullptr;
}

std::any LLVMCodeGen::visitImportDecl(PrystParser::ImportDeclContext* ctx) {
    return nullptr;
}

std::any LLVMCodeGen::visitImportPath(PrystParser::ImportPathContext* ctx) {
    return nullptr;
}

std::any LLVMCodeGen::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    if (ctx->functionDecl()) return visit(ctx->functionDecl());
    if (ctx->classDecl()) return visit(ctx->classDecl());
    if (ctx->varDecl()) return visit(ctx->varDecl());
    return nullptr;
}

std::any LLVMCodeGen::visitParameters(PrystParser::ParametersContext* ctx) {
    std::vector<llvm::Value*> params;
    for (auto param : ctx->parameter()) {
        params.push_back(std::any_cast<llvm::Value*>(visit(param)));
    }
    return params;
}

std::any LLVMCodeGen::visitParameter(PrystParser::ParameterContext* ctx) {
    auto type = getLLVMType(getTypeFromTypeContext(ctx->type()));
    auto param = builder.CreateAlloca(type, nullptr, ctx->IDENTIFIER()->getText());
    valueMap[ctx->IDENTIFIER()->getText()] = param;
    return param;
}

std::any LLVMCodeGen::visitAssignment(PrystParser::AssignmentContext* ctx) {
    auto target = std::any_cast<llvm::Value*>(visit(ctx->expression(0)));
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression(1)));

    if (target->getType() != value->getType()) {
        if (target->getType()->isFloatingPointTy() && value->getType()->isIntegerTy()) {
            value = builder.CreateSIToFP(value, target->getType(), "conv");
        } else if (target->getType()->isIntegerTy() && value->getType()->isFloatingPointTy()) {
            value = builder.CreateFPToSI(value, target->getType(), "conv");
        }
    }

    builder.CreateStore(value, target);
    return value;
}

std::any LLVMCodeGen::visitArguments(PrystParser::ArgumentsContext* ctx) {
    std::vector<llvm::Value*> args;
    for (auto arg : ctx->expression()) {
        args.push_back(std::any_cast<llvm::Value*>(visit(arg)));
    }
    return args;
}

std::any LLVMCodeGen::visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext* ctx) {
    auto arrayAlloc = getOrCreateArrayAlloc();
    auto size = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 0);
    std::vector<llvm::Value*> allocArgs = {size};
    auto array = builder.CreateCall(llvm::FunctionCallee(arrayAlloc), allocArgs, "array");
    return array;
}

std::any LLVMCodeGen::visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext* ctx) {
    auto arrayAlloc = getOrCreateArrayAlloc();
    auto size = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), ctx->expression().size());
    std::vector<llvm::Value*> allocArgs = {size};
    auto array = builder.CreateCall(llvm::FunctionCallee(arrayAlloc), allocArgs, "array");

    auto arraySet = module.getFunction("Array_set");
    for (size_t i = 0; i < ctx->expression().size(); i++) {
        auto value = std::any_cast<llvm::Value*>(visit(ctx->expression(i)));
        auto idx = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), i);
        std::vector<llvm::Value*> setArgs = {array, idx, value};
        builder.CreateCall(llvm::FunctionCallee(arraySet), setArgs);
    }

    return array;
}

std::any LLVMCodeGen::visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext* ctx) {
    auto mapAlloc = getOrCreateMapAlloc();
    auto map = builder.CreateCall(llvm::FunctionCallee(mapAlloc), {}, "map");
    return map;
}

std::any LLVMCodeGen::visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext* ctx) {
    auto mapAlloc = getOrCreateMapAlloc();
    auto map = builder.CreateCall(llvm::FunctionCallee(mapAlloc), {}, "map");

    auto mapSet = module.getFunction("Map_set");
    for (auto entry : ctx->mapEntry()) {
        llvm::Value* key = nullptr;
        if (entry->STRING()) {
            key = std::any_cast<llvm::Value*>(visit(entry->STRING()));
        } else if (entry->INTEGER()) {
            key = std::any_cast<llvm::Value*>(visit(entry->INTEGER()));
        }
        auto value = std::any_cast<llvm::Value*>(visit(entry->expression()));
        std::vector<llvm::Value*> setArgs;
        setArgs.push_back(map);
        setArgs.push_back(key);
        setArgs.push_back(value);
        builder.CreateCall(llvm::FunctionCallee(mapSet), setArgs);
    }

    return map;
}

std::any LLVMCodeGen::visitMapEntry(PrystParser::MapEntryContext* ctx) {
    llvm::Value* key;
    if (hasToken(ctx->STRING())) {
        std::string str = getTokenText(ctx->STRING());
        str = str.substr(1, str.length() - 2);  // Remove quotes
        key = builder.CreateGlobalStringPtr(str, "str");
    } else if (hasToken(ctx->INTEGER())) {
        key = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context),
            std::stoll(getTokenText(ctx->INTEGER())), true);
    } else {
        throw std::runtime_error("Map keys must be strings or integers");
    }

    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    return std::make_pair(key, value);
}

unsigned LLVMCodeGen::getMemberIndex(llvm::Type* classType, const std::string& memberName) {
    if (!classType->isStructTy()) {
        throw std::runtime_error("Type is not a class type");
    }

    auto className = classType->getStructName().str();
    return typeRegistry.getMemberIndex(className, memberName);
}

} // namespace pryst
