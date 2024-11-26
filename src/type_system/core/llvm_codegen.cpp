// LLVM includes
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

// Standard includes
#include <memory>
#include <map>
#include <string>
#include <stdexcept>

// Project includes
#include "llvm_codegen.hpp"
#include "type_checker.hpp"
#include "types.hpp"
#include "type_registry.hpp"

// Use LLVM types explicitly in implementation
namespace pryst {

std::shared_ptr<Type> LLVMCodeGen::getTypeFromTypeContext(PrystParser::TypeContext* ctx) {
    if (!ctx) {
        llvm::errs() << "DEBUG: Null type context\n";
        return nullptr;
    }
    llvm::errs() << "DEBUG: Processing type context\n";

    // Handle nullable types first
    if (auto nullableTypeCtx = dynamic_cast<PrystParser::NullableTypeContext*>(ctx)) {
        llvm::errs() << "DEBUG: Processing nullable type\n";
        // Get the first child context which will be the inner type
        auto innerTypeCtx = nullableTypeCtx->children[0];
        if (auto typeCtx = dynamic_cast<PrystParser::TypeContext*>(innerTypeCtx)) {
            auto innerType = getTypeFromTypeContext(typeCtx);
            if (!innerType) {
                throw std::runtime_error("Failed to get inner type for nullable type");
            }
            return std::make_shared<NullableType>(innerType);
        }
        throw std::runtime_error("Invalid nullable type structure");
    }

    // Handle qualified types
    if (auto qualifiedTypeCtx = ctx->qualifiedType()) {
        llvm::errs() << "DEBUG: Processing qualified type\n";
        std::string fullName;
        for (size_t i = 0; i < qualifiedTypeCtx->IDENTIFIER().size(); ++i) {
            if (i > 0) fullName += "::";
            fullName += getTokenText(qualifiedTypeCtx->IDENTIFIER(i));
        }
        auto classType = classTypeRegistry.getClassType(fullName);
        if (!classType) {
            throw std::runtime_error("Unknown qualified type: " + fullName);
        }
        return classType;
    }

    // Handle basic types
    if (auto basicTypeCtx = dynamic_cast<PrystParser::BasicTypeContext*>(ctx->basicType())) {
        llvm::errs() << "DEBUG: Processing basic type\n";
        if (hasToken(basicTypeCtx->INT())) {
            llvm::errs() << "DEBUG: Found INT type\n";
            return INT_TYPE;
        }
        if (hasToken(basicTypeCtx->FLOAT())) {
            llvm::errs() << "DEBUG: Found FLOAT type\n";
            return FLOAT_TYPE;
        }
        if (hasToken(basicTypeCtx->BOOL())) {
            llvm::errs() << "DEBUG: Found BOOL type\n";
            return BOOL_TYPE;
        }
        if (hasToken(basicTypeCtx->STR())) {
            llvm::errs() << "DEBUG: Found STRING type\n";
            return STRING_TYPE;
        }
        if (auto identToken = basicTypeCtx->IDENTIFIER()) {
            auto className = getTokenText(identToken);
            llvm::errs() << "DEBUG: Processing class type: " << className << "\n";
            auto classType = classTypeRegistry.getClassType(className);
            if (!classType) {
                llvm::errs() << "DEBUG: Unknown class type: " << className << "\n";
                throw std::runtime_error("Unknown class type: " + className);
            }
            llvm::errs() << "DEBUG: Found class type: " << className << "\n";
            return classType;
        }
    }

    // Handle array types
    if (auto arrayTypeCtx = dynamic_cast<PrystParser::ArrayTypeContext*>(ctx->arrayType())) {
        llvm::errs() << "DEBUG: Processing array type\n";
        std::shared_ptr<Type> elementType;
        if (auto basicType = arrayTypeCtx->basicType()) {
            llvm::errs() << "DEBUG: Processing array basic element type\n";
            elementType = getTypeFromTypeContext(dynamic_cast<PrystParser::TypeContext*>(basicType));
        } else if (auto innerArrayType = arrayTypeCtx->arrayType()) {
            llvm::errs() << "DEBUG: Processing nested array type\n";
            elementType = getTypeFromTypeContext(dynamic_cast<PrystParser::TypeContext*>(innerArrayType));
        }
        if (!elementType) {
            llvm::errs() << "DEBUG: Invalid array element type\n";
            throw std::runtime_error("Invalid array element type");
        }
        llvm::errs() << "DEBUG: Created array type with element type: " << elementType->toString() << "\n";
        return std::make_shared<ArrayType>(elementType);
    }

    // Handle map types
    if (auto mapTypeCtx = ctx->mapType()) {
        llvm::errs() << "DEBUG: Processing map type\n";
        auto keyTypeCtx = mapTypeCtx->keyType();
        auto valueTypeCtx = mapTypeCtx->type();
        if (!keyTypeCtx || !valueTypeCtx) {
            llvm::errs() << "DEBUG: Map type missing key or value type\n";
            throw std::runtime_error("Map type must have both key and value types");
        }

        // Key type can only be string or int
        std::shared_ptr<Type> keyType;
        if (hasToken(keyTypeCtx->STR())) {
            llvm::errs() << "DEBUG: Map key type is string\n";
            keyType = STRING_TYPE;
        } else if (hasToken(keyTypeCtx->INT())) {
            llvm::errs() << "DEBUG: Map key type is int\n";
            keyType = INT_TYPE;
        } else {
            llvm::errs() << "DEBUG: Invalid map key type\n";
            throw std::runtime_error("Map key type must be string or int");
        }

        auto valueType = getTypeFromTypeContext(valueTypeCtx);
        llvm::errs() << "DEBUG: Created map type with key: " << keyType->toString()
                  << " and value: " << valueType->toString() << "\n";
        return std::make_shared<MapType>(keyType, valueType);
    }

    // Handle function types
    if (auto funcTypeCtx = ctx->functionType()) {
        llvm::errs() << "DEBUG: Processing function type\n";
        std::vector<std::shared_ptr<Type>> paramTypes;
        if (auto typeListCtx = funcTypeCtx->typeList()) {
            for (auto paramTypeCtx : typeListCtx->type()) {
                auto paramType = getTypeFromTypeContext(paramTypeCtx);
                llvm::errs() << "DEBUG: Added function parameter type: " << paramType->toString() << "\n";
                paramTypes.push_back(paramType);
            }
        }
        auto returnTypeCtx = funcTypeCtx->returnType();
        auto returnType = returnTypeCtx ? getTypeFromReturnTypeContext(returnTypeCtx) : VOID_TYPE;
        llvm::errs() << "DEBUG: Function return type: " << returnType->toString() << "\n";
        return std::make_shared<FunctionType>(returnType, paramTypes);
    }

    llvm::errs() << "DEBUG: Unknown type encountered\n";
    throw std::runtime_error("Unknown type");
}

std::shared_ptr<Type> LLVMCodeGen::getTypeFromReturnTypeContext(PrystParser::ReturnTypeContext* ctx) {
    if (!ctx) {
        return VOID_TYPE;  // Default to void if no return type specified
    }
    return getTypeFromTypeContext(ctx->type());
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
    auto i1Ty = llvm::Type::getInt1Ty(context);
    auto voidTy = llvm::Type::getVoidTy(context);

    // Initialize GC allocation function
    auto gcAllocType = llvm::FunctionType::get(i8PtrTy, {i64Ty}, false);
    module.getOrInsertFunction("GC_malloc", gcAllocType);

    // Initialize runtime type operations
    auto instanceofType = llvm::FunctionType::get(i1Ty, {i8PtrTy, i8PtrTy}, false);
    module.getOrInsertFunction("pryst_runtime_instanceof", instanceofType);

    auto typeofType = llvm::FunctionType::get(i8PtrTy, {i8PtrTy}, false);
    module.getOrInsertFunction("pryst_runtime_typeof", typeofType);

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
    llvm::Value* lastAlloca = nullptr;

    // Handle multiple identifiers in the declaration
    for (auto identifier : ctx->identifierList()->IDENTIFIER()) {
        auto alloca = builder.CreateAlloca(type, nullptr, identifier->getText());

        if (ctx->expression()) {
            auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
            builder.CreateStore(value, alloca);
        }

        valueMap[identifier->getText()] = alloca;
        lastAlloca = alloca;
    }

    return lastAlloca;
}

std::any LLVMCodeGen::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    std::vector<llvm::Type*> paramTypes;
    if (ctx->parameters()) {
        for (auto param : ctx->parameters()->parameter()) {
            auto paramType = getLLVMType(getTypeFromTypeContext(param->type()));
            paramTypes.push_back(paramType);
        }
    }

    auto returnTypeCtx = ctx->returnType();
    auto returnType = returnTypeCtx ?
        getLLVMType(getTypeFromReturnTypeContext(returnTypeCtx)) : llvm::Type::getVoidTy(context);

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
    auto identifierTokens = ctx->IDENTIFIER();
    if (identifierTokens.empty()) {
        throw std::runtime_error("Class declaration must have a name");
    }
    auto className = identifierTokens[0]->getText();
    std::vector<std::pair<std::string, llvm::Type*>> members;

    // Create class type for our type system
    auto classType = std::make_shared<ClassType>(className);

    // Process class members
    for (auto memberCtx : ctx->classMember()) {
        if (auto typeCtx = memberCtx->type()) {  // Get member type
            auto memberType = getTypeFromTypeContext(typeCtx);
            auto identToken = memberCtx->IDENTIFIER();
            if (!hasToken(identToken)) {
                throw std::runtime_error("Class member must have a name");
            }
            auto memberName = getTokenText(identToken);

            // Nullability is handled by the type system and expressions
            members.push_back(std::make_pair(memberName, getLLVMType(memberType)));
            classType->addField(memberName, memberType);
        }
    }

    // Create struct type for class
    auto structType = llvm::StructType::create(context, className);
    std::vector<llvm::Type*> memberTypes;
    for (const auto& member : members) {
        memberTypes.push_back(member.second);
    }
    structType->setBody(memberTypes);

    // Register class type in both registries
    classTypeRegistry.registerClass(className, classType);
    typeRegistry.registerClass(className, members);
    for (size_t i = 0; i < members.size(); ++i) {
        typeRegistry.registerMemberIndex(className, members[i].first, i);
    }

    // Process constructors
    for (auto ctorCtx : ctx->constructorDecl()) {
        std::vector<std::shared_ptr<Type>> paramTypes;
        std::vector<std::string> paramNames;

        if (auto paramsCtx = ctorCtx->parameters()) {
            for (auto paramCtx : paramsCtx->parameter()) {
                auto paramType = getTypeFromTypeContext(paramCtx->type());
                auto paramIdent = paramCtx->IDENTIFIER();
                if (!hasToken(paramIdent)) {
                    throw std::runtime_error("Constructor parameter must have a name");
                }
                paramNames.push_back(getTokenText(paramIdent));
                paramTypes.push_back(paramType);
            }
        }

        // Create constructor function type
        auto ctorType = llvm::FunctionType::get(
            structType->getPointerTo(),
            getLLVMTypes(paramTypes),
            false
        );

        // Create constructor function
        auto ctor = llvm::Function::Create(
            ctorType,
            llvm::Function::ExternalLinkage,
            className + "_constructor",
            module
        );

        // Set parameter names
        size_t idx = 0;
        for (auto& param : ctor->args()) {
            param.setName(paramNames[idx++]);
        }

        // Create entry block
        auto entryBlock = llvm::BasicBlock::Create(context, "entry", ctor);
        builder.SetInsertPoint(entryBlock);

        // Allocate instance
        auto instance = builder.CreateAlloca(structType);

        // Initialize members to null/default values
        for (size_t i = 0; i < members.size(); ++i) {
            auto memberPtr = builder.CreateStructGEP(structType, instance, i);
            builder.CreateStore(llvm::Constant::getNullValue(memberTypes[i]), memberPtr);
        }

        // Visit constructor block
        currentClass = className;
        currentInstance = instance;
        visit(ctorCtx->constructorBlock());
        currentClass.clear();
        currentInstance = nullptr;

        // Return instance
        builder.CreateRet(instance);
    }

    // Process methods
    for (auto memberCtx : ctx->classMember()) {
        if (memberCtx->block()) {  // This is a method
            auto methodIdent = memberCtx->IDENTIFIER();
            if (!methodIdent) {
                throw std::runtime_error("Method must have a name");
            }
            auto methodName = methodIdent->getText();
            std::vector<std::shared_ptr<Type>> paramTypes;
            std::vector<std::string> paramNames;

            // Add 'this' pointer as first parameter
            paramTypes.push_back(classType);
            paramNames.push_back("this");

            if (auto paramsCtx = memberCtx->parameters()) {
                for (auto paramCtx : paramsCtx->parameter()) {
                    auto paramType = getTypeFromTypeContext(paramCtx->type());
                    auto paramIdent = paramCtx->IDENTIFIER();
                    if (!paramIdent) {
                        throw std::runtime_error("Method parameter must have a name");
                    }
                    paramNames.push_back(paramIdent->getText());
                    paramTypes.push_back(paramType);
                }
            }

            // Get return type from returnType context
            std::shared_ptr<Type> returnType;
            if (auto returnTypeCtx = memberCtx->returnType()) {
                returnType = getTypeFromReturnTypeContext(returnTypeCtx);
            } else {
                returnType = VOID_TYPE;
            }

            // Create method function type
            auto methodType = llvm::FunctionType::get(
                getLLVMType(returnType),
                getLLVMTypes(paramTypes),
                false
            );

            // Create method function
            auto method = llvm::Function::Create(
                methodType,
                llvm::Function::ExternalLinkage,
                className + "_" + methodName,
                module
            );

            // Set parameter names
            size_t idx = 0;
            for (auto& param : method->args()) {
                param.setName(paramNames[idx++]);
            }

            // Create entry block
            auto entryBlock = llvm::BasicBlock::Create(context, "entry", method);
            builder.SetInsertPoint(entryBlock);

            // Set current function context
            currentFunction = method;
            currentClass = className;
            currentInstance = &*method->arg_begin();  // 'this' pointer

            // Visit method body
            visit(memberCtx->block());

            // Clear function context
            currentFunction = nullptr;
            currentClass.clear();
            currentInstance = nullptr;

            // Add return instruction if none exists
            if (!builder.GetInsertBlock()->getTerminator()) {
                if (returnType == VOID_TYPE) {
                    builder.CreateRetVoid();
                } else {
                    builder.CreateRet(llvm::Constant::getNullValue(getLLVMType(returnType)));
                }
            }
        }
    }

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

        visit(ctx->statement());

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
        } else if (ctx->expressionStmt()) {
            visit(ctx->expressionStmt());
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
        visit(ctx->statement());
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

    // Visit try block
    visit(ctx->block(0));

    // Visit catch blocks
    for (auto catchClause : ctx->catchClause()) {
        auto catchBlock = llvm::BasicBlock::Create(context, "catch");
        function->getBasicBlockList().push_back(catchBlock);
        builder.SetInsertPoint(catchBlock);

        // Create exception variable
        auto exceptionType = getLLVMType(getTypeFromTypeContext(catchClause->type()));
        auto exceptionVar = builder.CreateAlloca(exceptionType, nullptr, catchClause->IDENTIFIER()->getText());
        valueMap[catchClause->IDENTIFIER()->getText()] = exceptionVar;

        visit(catchClause->block());
    }

    // Handle finally block if present
    if (ctx->FINALLY()) {
        auto finallyBlock = llvm::BasicBlock::Create(context, "finally");
        function->getBasicBlockList().push_back(finallyBlock);
        builder.SetInsertPoint(finallyBlock);
        visit(ctx->block().back());
    }

    return nullptr;
}

std::any LLVMCodeGen::visitReturnStmt(PrystParser::ReturnStmtContext* ctx) {
    llvm::errs() << "DEBUG: Processing return statement\n";
    auto function = builder.GetInsertBlock()->getParent();
    auto returnType = function->getReturnType();

    if (ctx->expression()) {
        auto returnValue = std::any_cast<llvm::Value*>(visit(ctx->expression()));
        llvm::errs() << "DEBUG: Got expression value\n";

        if (returnValue->getType() != returnType) {
            llvm::errs() << "DEBUG: Type conversion needed\n";
            llvm::errs() << "DEBUG: Return type: ";
            returnType->print(llvm::errs());
            llvm::errs() << "\nDEBUG: Value type: ";
            returnValue->getType()->print(llvm::errs());
            llvm::errs() << "\n";

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

        llvm::errs() << "DEBUG: Creating return instruction\n";
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



std::any LLVMCodeGen::visitConstructorExpr(PrystParser::ConstructorExprContext* ctx) {
    std::string className = std::any_cast<std::shared_ptr<Type>>(visit(ctx->qualifiedType()))->toString();
    if (!typeRegistry.hasClass(className)) {
        throw std::runtime_error("Unknown class: " + className);
    }
    auto ctor = module.getFunction(className + "_constructor");
    if (!ctor) {
        throw std::runtime_error("Constructor not found for class: " + className);
    }

    std::vector<llvm::Value*> args;
    if (auto argsCtx = ctx->arguments()) {
        for (auto exprCtx : argsCtx->expression()) {
            args.push_back(std::any_cast<llvm::Value*>(visit(exprCtx)));
        }
    }
    return (llvm::Value*)builder.CreateCall(llvm::FunctionCallee(ctor), args);
}

std::any LLVMCodeGen::visitMemberAccessExpr(PrystParser::MemberAccessExprContext* ctx) {
    llvm::errs() << "DEBUG: Entering visitMemberAccessExpr\n";

    auto object = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    if (!object) {
        llvm::errs() << "DEBUG: Null object in member access\n";
        throw std::runtime_error("Null object in member access");
    }

    auto memberName = ctx->IDENTIFIER()->getText();
    llvm::errs() << "DEBUG: Accessing member: " << memberName << "\n";

    // Get object type
    auto objectType = object->getType();
    llvm::errs() << "DEBUG: Initial object type: ";
    objectType->print(llvm::errs());
    llvm::errs() << "\n";

    while (objectType->isPointerTy()) {
        objectType = objectType->getPointerElementType();
        llvm::errs() << "DEBUG: Dereferenced to type: ";
        objectType->print(llvm::errs());
        llvm::errs() << "\n";
    }

    if (auto structType = llvm::dyn_cast<llvm::StructType>(objectType)) {
        llvm::errs() << "DEBUG: Found struct type: " << structType->getName() << "\n";
        // Get member index from type registry
        auto memberIndex = typeRegistry.getMemberIndex(structType->getName().str(), memberName);
        if (memberIndex < 0) {
            llvm::errs() << "DEBUG: Member " << memberName << " not found in " << structType->getName() << "\n";
            throw std::runtime_error("Member " + memberName + " not found");
        }
        llvm::errs() << "DEBUG: Found member at index: " << memberIndex << "\n";

        // Get member value
        auto memberPtr = builder.CreateStructGEP(objectType, object, memberIndex);
        llvm::errs() << "DEBUG: Created GEP for member access\n";
        auto result = builder.CreateLoad(memberPtr->getType()->getPointerElementType(), memberPtr);
        llvm::errs() << "DEBUG: Successfully loaded member value\n";
        return result;
    }

    llvm::errs() << "DEBUG: Member access attempted on non-object type: ";
    objectType->print(llvm::errs());
    llvm::errs() << "\n";
    throw std::runtime_error("Member access on non-object type");
}

std::any LLVMCodeGen::visitNullableChain(PrystParser::NullableChainContext* ctx) {
    llvm::errs() << "DEBUG: Entering visitNullableChain\n";

    auto object = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    if (!object) {
        llvm::errs() << "DEBUG: Null object in nullable chain\n";
        throw std::runtime_error("Null object in nullable chain");
    }

    auto memberName = ctx->IDENTIFIER()->getText();
    llvm::errs() << "DEBUG: Accessing nullable member: " << memberName << "\n";

    // Create basic blocks for null checking
    auto function = builder.GetInsertBlock()->getParent();
    auto nullCheckBlock = llvm::BasicBlock::Create(context, "null_check", function);
    auto accessBlock = llvm::BasicBlock::Create(context, "member_access");
    auto continueBlock = llvm::BasicBlock::Create(context, "continue");

    llvm::errs() << "DEBUG: Created basic blocks for null checking\n";

    // Branch to null check
    builder.CreateBr(nullCheckBlock);
    builder.SetInsertPoint(nullCheckBlock);

    // Compare with null
    llvm::errs() << "DEBUG: Creating null comparison\n";
    auto isNull = builder.CreateICmpEQ(object,
        llvm::Constant::getNullValue(object->getType()),
        "is_null");

    builder.CreateCondBr(isNull, continueBlock, accessBlock);
    llvm::errs() << "DEBUG: Created conditional branch based on null check\n";

    // Member access block
    function->getBasicBlockList().push_back(accessBlock);
    builder.SetInsertPoint(accessBlock);

    // Get object type
    auto objectType = object->getType();
    llvm::errs() << "DEBUG: Initial object type: ";
    objectType->print(llvm::errs());
    llvm::errs() << "\n";

    while (objectType->isPointerTy()) {
        objectType = objectType->getPointerElementType();
        llvm::errs() << "DEBUG: Dereferenced to type: ";
        objectType->print(llvm::errs());
        llvm::errs() << "\n";
    }

    llvm::Value* memberValue = nullptr;
    if (auto structType = llvm::dyn_cast<llvm::StructType>(objectType)) {
        llvm::errs() << "DEBUG: Found struct type: " << structType->getName() << "\n";
        // Get member index from type registry
        auto memberIndex = typeRegistry.getMemberIndex(structType->getName().str(), memberName);
        if (memberIndex < 0) {
            llvm::errs() << "DEBUG: Member " << memberName << " not found in " << structType->getName() << "\n";
            throw std::runtime_error("Member " + memberName + " not found");
        }
        llvm::errs() << "DEBUG: Found member at index: " << memberIndex << "\n";

        // Get member value
        auto memberPtr = builder.CreateStructGEP(objectType, object, memberIndex);
        llvm::errs() << "DEBUG: Created GEP for member access\n";
        memberValue = builder.CreateLoad(memberPtr->getType()->getPointerElementType(), memberPtr);
        llvm::errs() << "DEBUG: Successfully loaded member value\n";
    } else {
        llvm::errs() << "DEBUG: Member access attempted on non-object type: ";
        objectType->print(llvm::errs());
        llvm::errs() << "\n";
        throw std::runtime_error("Member access on non-object type");
    }

    builder.CreateBr(continueBlock);
    llvm::errs() << "DEBUG: Created branch to continue block\n";

    // Continue block
    function->getBasicBlockList().push_back(continueBlock);
    builder.SetInsertPoint(continueBlock);

    // Create PHI node
    llvm::errs() << "DEBUG: Creating PHI node for nullable result\n";
    auto phi = builder.CreatePHI(memberValue->getType(), 2);
    phi->addIncoming(llvm::Constant::getNullValue(memberValue->getType()), nullCheckBlock);
    phi->addIncoming(memberValue, accessBlock);
    llvm::errs() << "DEBUG: Successfully created PHI node\n";

    return phi;
}

std::any LLVMCodeGen::visitMethodCallExpr(PrystParser::MethodCallExprContext* ctx) {
    auto object = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto methodName = ctx->IDENTIFIER()->getText();

    // Get object type
    auto objectType = object->getType();
    while (objectType->isPointerTy()) {
        objectType = objectType->getPointerElementType();
    }

    // Handle method call
    if (auto structType = llvm::dyn_cast<llvm::StructType>(objectType)) {
        std::string className = structType->getName().str();
        std::string fullMethodName = className + "_" + methodName;

        auto method = module.getFunction(fullMethodName);
        if (!method) {
            throw std::runtime_error("Method " + methodName + " not found in class " + className);
        }

        std::vector<llvm::Value*> args;
        args.push_back(object);  // 'this' pointer

        if (auto argsCtx = ctx->arguments()) {
            for (auto argCtx : argsCtx->expression()) {
                args.push_back(std::any_cast<llvm::Value*>(visit(argCtx)));
            }
        }

        return builder.CreateCall(llvm::FunctionCallee(method), args);
    }

    throw std::runtime_error("Method call on non-object type");
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
    auto operand = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    if (ctx->INC()) {
        // Handle increment
        auto one = llvm::ConstantInt::get(operand->getType(), 1);
        auto result = builder.CreateAdd(operand, one, "inc");
        // Store back to original location
        builder.CreateStore(result, operand);
        return operand;  // Return original value for postfix
    } else if (ctx->DEC()) {
        // Handle decrement
        auto one = llvm::ConstantInt::get(operand->getType(), 1);
        auto result = builder.CreateSub(operand, one, "dec");
        // Store back to original location
        builder.CreateStore(result, operand);
        return operand;  // Return original value for postfix
    }

    throw std::runtime_error("Unsupported postfix operator");
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
    if (!value) {
        llvm::errs() << "DEBUG: convertType called with null value\n";
        return nullptr;
    }

    auto sourceType = value->getType();
    llvm::errs() << "DEBUG: Converting from type: ";
    sourceType->print(llvm::errs());
    llvm::errs() << " to type: ";
    targetType->print(llvm::errs());
    llvm::errs() << "\n";

    if (sourceType == targetType) {
        llvm::errs() << "DEBUG: Source and target types are identical\n";
        return value;
    }

    if (sourceType->isIntegerTy() && targetType->isFloatingPointTy()) {
        llvm::errs() << "DEBUG: Converting integer to floating point\n";
        return builder.CreateSIToFP(value, targetType, "int2float");
    }

    if (sourceType->isFloatingPointTy() && targetType->isIntegerTy()) {
        llvm::errs() << "DEBUG: Converting floating point to integer\n";
        return builder.CreateFPToSI(value, targetType, "float2int");
    }

    if (sourceType->isIntegerTy() && targetType->isIntegerTy(1)) {
        llvm::errs() << "DEBUG: Converting integer to boolean\n";
        return builder.CreateICmpNE(value,
            llvm::Constant::getNullValue(sourceType), "int2bool");
    }

    if (sourceType->isIntegerTy(1) && targetType->isIntegerTy()) {
        llvm::errs() << "DEBUG: Converting boolean to integer\n";
        return builder.CreateZExt(value, targetType, "bool2int");
    }

    llvm::errs() << "DEBUG: Unsupported type conversion from ";
    sourceType->print(llvm::errs());
    llvm::errs() << " to ";
    targetType->print(llvm::errs());
    llvm::errs() << "\n";
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
    if (!type) {
        llvm::errs() << "DEBUG: getLLVMType called with null type\n";
        return llvm::Type::getVoidTy(context);
    }

    llvm::errs() << "DEBUG: Converting type kind: " << type->getKind() << "\n";

    switch (type->getKind()) {
        case Type::Kind::Int:
            llvm::errs() << "DEBUG: Converting Int type\n";
            return llvm::Type::getInt64Ty(context);
        case Type::Kind::Float:
            llvm::errs() << "DEBUG: Converting Float type\n";
            return llvm::Type::getDoubleTy(context);
        case Type::Kind::Bool:
            llvm::errs() << "DEBUG: Converting Bool type\n";
            return llvm::Type::getInt1Ty(context);
        case Type::Kind::String:
            llvm::errs() << "DEBUG: Converting String type\n";
            return llvm::Type::getInt8PtrTy(context);
        case Type::Kind::Void:
            llvm::errs() << "DEBUG: Converting Void type\n";
            return llvm::Type::getVoidTy(context);
        case Type::Kind::Array:
            llvm::errs() << "DEBUG: Attempting Array type conversion\n";
            if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(type)) {
                llvm::errs() << "DEBUG: Converting Array type\n";
                return llvm::Type::getInt8PtrTy(context);  // Arrays are opaque pointers
            }
            llvm::errs() << "DEBUG: Array type conversion failed\n";
            break;
        case Type::Kind::Map:
            llvm::errs() << "DEBUG: Attempting Map type conversion\n";
            if (auto mapType = std::dynamic_pointer_cast<MapType>(type)) {
                llvm::errs() << "DEBUG: Converting Map type\n";
                return llvm::Type::getInt8PtrTy(context);  // Maps are opaque pointers
            }
            llvm::errs() << "DEBUG: Map type conversion failed\n";
            break;
        case Type::Kind::Class:
            llvm::errs() << "DEBUG: Attempting Class type conversion\n";
            if (auto classType = std::dynamic_pointer_cast<ClassType>(type)) {
                llvm::errs() << "DEBUG: Converting Class type: " << classType->getName() << "\n";
                return llvm::Type::getInt8PtrTy(context);  // Classes are opaque pointers
            }
            llvm::errs() << "DEBUG: Class type conversion failed\n";
            break;
        case Type::Kind::Error:
            llvm::errs() << "DEBUG: Converting Error type\n";
            return llvm::Type::getInt8PtrTy(context);  // Error type is an opaque pointer
        case Type::Kind::Nullable:
            llvm::errs() << "DEBUG: Attempting Nullable type conversion\n";
            if (auto nullableType = std::dynamic_pointer_cast<NullableType>(type)) {
                llvm::errs() << "DEBUG: Converting Nullable type\n";
                auto innerLLVMType = getLLVMType(nullableType->getInnerType());
                if (innerLLVMType->isPointerTy()) {
                    llvm::errs() << "DEBUG: Inner type is already a pointer\n";
                    return innerLLVMType;
                }
                llvm::errs() << "DEBUG: Creating pointer type for non-pointer inner type\n";
                return llvm::PointerType::get(innerLLVMType, 0);
            }
            llvm::errs() << "DEBUG: Nullable type conversion failed\n";
            break;
        case Type::Kind::Null:
            llvm::errs() << "DEBUG: Converting Null type\n";
            return llvm::Type::getInt8PtrTy(context);
    }

    llvm::errs() << "DEBUG: Unknown type encountered\n";
    throw std::runtime_error("Unknown type");
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
    std::vector<std::pair<std::string, llvm::Type*>> parameters;

    // Get parameter types and names from lambdaParams
    if (ctx->lambdaParams()) {
        auto params = ctx->lambdaParams();
        for (size_t i = 0; i < params->IDENTIFIER().size(); ++i) {
            auto paramType = getLLVMType(getTypeFromTypeContext(params->type(i)));
            parameters.push_back({params->IDENTIFIER(i)->getText(), paramType});
        }
    }

    // Get return type from returnType context or expression
    llvm::Type* returnType;
    if (auto returnTypeCtx = ctx->returnType()) {
        returnType = getLLVMType(getTypeFromReturnTypeContext(returnTypeCtx));
    } else if (ctx->expression()) {
        auto exprType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
        returnType = getLLVMType(exprType);
    } else {
        returnType = llvm::Type::getVoidTy(context);
    }

    // Create function type
    std::vector<llvm::Type*> paramTypes;
    for (const auto& param : parameters) {
        paramTypes.push_back(param.second);
    }
    auto funcType = llvm::FunctionType::get(returnType, paramTypes, false);

    // Create function
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
        "lambda", module);

    // Create entry block
    auto entry = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);

    // Add parameters to value map
    auto argIt = func->arg_begin();
    for (const auto& [paramName, _] : parameters) {
        valueMap[paramName] = argIt++;
    }

    // Generate lambda body
    if (ctx->block()) {
        visit(ctx->block());
    } else if (ctx->expression()) {
        auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
        builder.CreateRet(value);
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

// Implementation of instanceof expression
std::any LLVMCodeGen::visitInstanceofExpr(PrystParser::InstanceofExprContext* ctx) {
    // Get the object being checked
    auto object = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    // Get the type name being checked against
    auto typeCtx = ctx->type();
    auto checkType = getTypeFromTypeContext(typeCtx);

    // Get runtime instanceof function
    auto instanceofFn = module.getFunction("pryst_runtime_instanceof");
    if (!instanceofFn) {
        throw std::runtime_error("Runtime instanceof function not found");
    }

    // Create type string constant
    auto typeStr = builder.CreateGlobalStringPtr(checkType->toString(), "type_str");

    // Call runtime instanceof function
    std::vector<llvm::Value*> args = {object, typeStr};
    return builder.CreateCall(llvm::FunctionCallee(instanceofFn), args, "instanceof_result");
}

// Implementation of typeof expression
std::any LLVMCodeGen::visitTypeofExpr(PrystParser::TypeofExprContext* ctx) {
    // Get the object
    auto object = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    // Get runtime typeof function
    auto typeofFn = module.getFunction("pryst_runtime_typeof");
    if (!typeofFn) {
        throw std::runtime_error("Runtime typeof function not found");
    }

    // Call runtime typeof function
    std::vector<llvm::Value*> args = {object};
    return builder.CreateCall(llvm::FunctionCallee(typeofFn), args, "typeof_result");
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

std::string LLVMCodeGen::getTokenText(antlr4::tree::TerminalNode* node) {
    if (!node) return "";
    return node->getText();
}

bool LLVMCodeGen::hasToken(antlr4::tree::TerminalNode* node) {
    return node != nullptr;
}

bool LLVMCodeGen::hasContext(antlr4::tree::ParseTree* ctx) {
    return ctx != nullptr;
}

antlr4::ParserRuleContext* LLVMCodeGen::getContext(antlr4::tree::ParseTree* ctx) {
    if (!ctx) throw std::runtime_error("Null context");
    return dynamic_cast<antlr4::ParserRuleContext*>(ctx);
}

std::vector<llvm::Type*> LLVMCodeGen::getLLVMTypes(const std::vector<std::shared_ptr<Type>>& types) {
    std::vector<llvm::Type*> llvmTypes;
    for (const auto& type : types) {
        llvmTypes.push_back(getLLVMType(type));
    }
    return llvmTypes;
}

// Helper method implementations
llvm::Type* LLVMCodeGen::createArrayType(llvm::Type* elementType) {
    // Create array wrapper type with metadata
    auto arrayStructTy = llvm::StructType::create(context, "array");
    std::vector<llvm::Type*> elements = {
        llvm::Type::getInt32Ty(context),  // length
        llvm::PointerType::get(elementType, 0)  // data pointer
    };
    arrayStructTy->setBody(elements);
    return arrayStructTy;
}

llvm::Type* LLVMCodeGen::createMapType(llvm::Type* keyType, llvm::Type* valueType) {
    // Create map wrapper type with metadata
    auto mapStructTy = llvm::StructType::create(context, "map");
    std::vector<llvm::Type*> elements = {
        llvm::Type::getInt32Ty(context),  // size
        llvm::PointerType::get(  // entries array
            llvm::StructType::create(context, {keyType, valueType}),
            0
        )
    };
    mapStructTy->setBody(elements);
    return mapStructTy;
}

llvm::Type* LLVMCodeGen::createNullableType(llvm::Type* baseType) {
    // Create nullable wrapper type with metadata
    auto nullableStructTy = llvm::StructType::create(context, "nullable");
    std::vector<llvm::Type*> elements = {
        llvm::Type::getInt1Ty(context),  // hasValue flag
        baseType  // actual value
    };
    nullableStructTy->setBody(elements);
    return nullableStructTy;
}

// Visitor method implementations
std::any LLVMCodeGen::visitIdentifierList(PrystParser::IdentifierListContext* ctx) {
    std::vector<std::string> identifiers;
    for (auto id : ctx->IDENTIFIER()) {
        identifiers.push_back(id->getText());
    }
    return identifiers;
}

std::any LLVMCodeGen::visitInterfaceDecl(PrystParser::InterfaceDeclContext* ctx) {
    // TODO: Implement interface code generation
    return nullptr;
}

std::any LLVMCodeGen::visitClassMember(PrystParser::ClassMemberContext* ctx) {
    if (auto typeCtx = ctx->type()) {
        auto memberType = getLLVMType(getTypeFromTypeContext(typeCtx));
        auto memberName = ctx->IDENTIFIER()->getText();

        // Handle const members
        bool isConst = ctx->CONST() != nullptr || ctx->CONST_EXPR() != nullptr;

        // Add to class layout
        auto structTy = llvm::StructType::getTypeByName(context, "class." + currentClass);
        if (!structTy) {
            throw std::runtime_error("Class type not found: " + currentClass);
        }

        // Store member info for later use
        memberTypes[currentClass + "." + memberName] = memberType;
        memberIndices[currentClass + "." + memberName] = memberTypes.size() - 1;
    }
    return nullptr;
}

std::any LLVMCodeGen::visitConstructorDecl(PrystParser::ConstructorDeclContext* ctx) {
    auto className = currentClass;
    auto constructorName = "constructor." + className;

    // Create function type for constructor
    std::vector<llvm::Type*> paramTypes;
    paramTypes.push_back(llvm::PointerType::get(context, 0)); // this pointer

    if (ctx->parameters()) {
        auto params = std::any_cast<std::vector<llvm::Type*>>(visit(ctx->parameters()));
        paramTypes.insert(paramTypes.end(), params.begin(), params.end());
    }

    auto constructorType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context),
        paramTypes,
        false
    );

    // Create constructor function
    auto constructor = llvm::Function::Create(
        constructorType,
        llvm::Function::ExternalLinkage,
        constructorName,
        module
    );

    // Create entry block
    auto entry = llvm::BasicBlock::Create(context, "entry", constructor);
    builder.SetInsertPoint(entry);

    // Store current function for the constructor block visitor
    currentFunction = constructor;

    if (ctx->constructorBlock()) {
        visit(ctx->constructorBlock());
    }

    builder.CreateRetVoid();
    return constructor;
}

std::any LLVMCodeGen::visitConstructorBlock(PrystParser::ConstructorBlockContext* ctx) {
    // Handle member initializations and statements
    for (auto stmt : ctx->statement()) {
        // Check for this.identifier assignments
        if (auto assignStmt = dynamic_cast<PrystParser::AssignmentContext*>(stmt)) {
            auto lhs = assignStmt->expression(0);
            if (auto memberAccess = dynamic_cast<PrystParser::MemberAccessExprContext*>(lhs)) {
                auto thisExpr = memberAccess->expression();
                if (thisExpr->getText() == "this") {
                    auto memberName = memberAccess->IDENTIFIER()->getText();
                    auto value = std::any_cast<llvm::Value*>(visit(assignStmt->expression(1)));

                    // Get member index from class layout
                    auto idx = memberIndices[currentClass + "." + memberName];
                    auto memberPtr = builder.CreateStructGEP(
                        nullptr,  // Use nullptr for opaque pointers
                        currentInstance,
                        idx,
                        "member." + memberName
                    );
                    builder.CreateStore(value, memberPtr);
                    continue;
                }
            }
        }
        visit(stmt);
    }
    return nullptr;
}

std::any LLVMCodeGen::visitBasicType(PrystParser::BasicTypeContext* ctx) {
    if (ctx->INT()) return llvm::Type::getInt32Ty(context);
    if (ctx->FLOAT()) return llvm::Type::getFloatTy(context);
    if (ctx->BOOL()) return llvm::Type::getInt1Ty(context);
    if (ctx->STR()) return llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0);
    if (ctx->IDENTIFIER()) {
        // Handle class types
        auto className = ctx->IDENTIFIER()->getText();
        auto structTy = llvm::StructType::getTypeByName(context, "class." + className);
        if (!structTy) {
            throw std::runtime_error("Unknown class type: " + className);
        }
        return llvm::PointerType::get(structTy, 0);
    }
    return nullptr;
}

std::any LLVMCodeGen::visitQualifiedType(PrystParser::QualifiedTypeContext* ctx) {
    std::string typeName = ctx->getText();
    auto structTy = llvm::StructType::getTypeByName(context, "class." + typeName);
    if (!structTy) {
        throw std::runtime_error("Unknown class type: " + typeName);
    }
    return llvm::PointerType::get(structTy, 0);
}

std::any LLVMCodeGen::visitArrayType(PrystParser::ArrayTypeContext* ctx) {
    auto elementType = std::any_cast<llvm::Type*>(visit(ctx->basicType()));
    return createArrayType(elementType);
}

std::any LLVMCodeGen::visitMapType(PrystParser::MapTypeContext* ctx) {
    llvm::Type* keyType;
    if (ctx->keyType()->STR()) {
        keyType = llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0);
    } else {
        keyType = llvm::Type::getInt32Ty(context);
    }

    auto valueType = std::any_cast<llvm::Type*>(visit(ctx->type()));
    return createMapType(keyType, valueType);
}

std::any LLVMCodeGen::visitFunctionType(PrystParser::FunctionTypeContext* ctx) {
    auto returnTypeCtx = ctx->returnType();
    auto returnType = getLLVMType(getTypeFromReturnTypeContext(returnTypeCtx));
    std::vector<llvm::Type*> paramTypes;

    if (auto typeList = ctx->typeList()) {
        for (auto paramType : typeList->type()) {
            paramTypes.push_back(std::any_cast<llvm::Type*>(visit(paramType)));
        }
    }

    return llvm::FunctionType::get(returnType, paramTypes, false);
}

} // namespace pryst
