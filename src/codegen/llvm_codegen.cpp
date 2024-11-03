#include "llvm_codegen.hpp"
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/Support/Casting.h>
#include "semantic/type_info.hpp"
#include <stdexcept>
#include <iostream>

// Helper function implementations
size_t LLVMCodegen::getMemberIndex(llvm::StructType* structType, const std::string& memberName) {
    std::string className = structType->getName().str();
    auto& members = memberIndices[className];
    auto it = members.find(memberName);
    if (it != members.end()) {
        return it->second;
    }

    // Check superclass members if this class extends another
    for (const auto& pair : classInheritance) {
        if (pair.first == className) {
            auto superClassType = llvm::StructType::getTypeByName(*context, pair.second);
            if (superClassType) {
                try {
                    return getMemberIndex(superClassType, memberName);
                } catch (const std::runtime_error&) {
                    // Continue searching if not found in this superclass
                }
            }
        }
    }
    throw std::runtime_error("Member not found: " + memberName);
}

void LLVMCodegen::addClassMember(const std::string& className, const std::string& memberName, size_t index) {
    memberIndices[className][memberName] = index;
}

LLVMCodegen::LLVMCodegen()
    : context(std::make_unique<llvm::LLVMContext>()),
      module(std::make_unique<llvm::Module>("pryst", *context)),
      builder(std::make_unique<llvm::IRBuilder<>>(*context)),
      lastValue(nullptr),
      currentFunction(nullptr) {}

std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(PrystParser::ProgramContext* programCtx) {
    currentFunction = createMainFunction();
    visitProgram(programCtx);
    if (llvm::verifyModule(*module, &llvm::errs())) {
        throw std::runtime_error("Generated LLVM IR is invalid");
    }
    return std::move(module);
}

llvm::Function* LLVMCodegen::createMainFunction() {
    llvm::FunctionType* mainFuncType = llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), false);
    llvm::Function* mainFunc = llvm::Function::Create(mainFuncType, llvm::Function::ExternalLinkage, "main", module.get());

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", mainFunc);
    builder->SetInsertPoint(entryBlock);

    // Add return 0 statement
    builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0));

    return mainFunc;
}

// Program: Handles the entire program
std::any LLVMCodegen::visitProgram(PrystParser::ProgramContext* ctx) {
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return nullptr;
}

// Declaration: Dispatches to the appropriate declaration type
std::any LLVMCodegen::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    if (ctx->functionDecl()) {
        visit(ctx->functionDecl());
    } else if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->classDeclaration()) {
        visit(ctx->classDeclaration());
    } else {
        visit(ctx->statement());
    }
    return nullptr;
}

// Function Declaration: Dispatches to the appropriate function type
std::any LLVMCodegen::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    if (auto namedFunc = dynamic_cast<PrystParser::NamedFunctionContext*>(ctx)) {
        return visitNamedFunction(namedFunc);
    } else if (auto lambdaFunc = dynamic_cast<PrystParser::LambdaFunctionContext*>(ctx)) {
        return visitLambdaFunction(lambdaFunc);
    }
    return nullptr;
}

// Named Function: Handles regular function declarations
std::any LLVMCodegen::visitNamedFunction(PrystParser::NamedFunctionContext* ctx) {
    std::string funcName = ctx->IDENTIFIER()->getText();
    llvm::Type* returnType = getLLVMType(ctx->type()->getText());

    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;

    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(getLLVMType(param->type()->getText()));
            paramNames.push_back(param->IDENTIFIER()->getText());
        }
    }

    llvm::FunctionType* funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    llvm::Function* function = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, funcName, module.get());

    // Create function type info
    auto functionTypeInfo = std::make_shared<FunctionTypeInfo>(funcName, funcType);
    typeMetadata->addFunctionTypeInfo(function, functionTypeInfo);

    // Create a new basic block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(bb);

    // Save the current function
    llvm::Function* oldFunction = currentFunction;
    currentFunction = function;

    // Create a new scope for function parameters
    pushScope();

    // Create allocas for parameters
    if (ctx->paramList()) {
        size_t idx = 0;
        for (auto& arg : function->args()) {
            std::string paramName = paramNames[idx++];
            llvm::AllocaInst* alloca = createEntryBlockAlloca(function, paramName, arg.getType());
            builder->CreateStore(&arg, alloca);
            scopeStack.back()[paramName] = alloca;
        }
    }

    // Visit function body
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Add implicit return if needed
    if (!builder->GetInsertBlock()->getTerminator()) {
        if (returnType->isVoidTy()) {
            builder->CreateRetVoid();
        } else {
            builder->CreateRet(llvm::Constant::getNullValue(returnType));
        }
    }

    // Verify the function
    if (llvm::verifyFunction(*function, &llvm::errs())) {
        throw std::runtime_error("Function verification failed for function: " + funcName);
    }

    popScope();
    currentFunction = oldFunction;
    functions[funcName] = function;

    return nullptr;
}

// Variable Declaration: Handles variable declarations
std::any LLVMCodegen::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    std::string varName = ctx->IDENTIFIER()->getText();
    llvm::Type* varType = getLLVMType(ctx->type()->getText());

    llvm::AllocaInst* alloca = createEntryBlockAlloca(currentFunction, varName, varType);

    if (ctx->expression()) {
        visit(ctx->expression());
        builder->CreateStore(lastValue, alloca);
    } else {
        builder->CreateStore(llvm::Constant::getNullValue(varType), alloca);
    }

    namedValues[varName] = alloca;
    return nullptr;
}

// Class Declaration: Handles class declarations
std::any LLVMCodegen::visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) {
    std::string className = ctx->IDENTIFIER(0)->getText();

    // Build complete inheritance chain from base to derived
    std::vector<std::string> inheritanceChain;
    std::string immediateBase;
    if (ctx->IDENTIFIER().size() > 1) {
        immediateBase = ctx->IDENTIFIER(1)->getText();
        std::string currentClass = immediateBase;
        while (!currentClass.empty()) {
            inheritanceChain.push_back(currentClass);
            auto it = classInheritance.find(currentClass);
            if (it == classInheritance.end()) break;
            currentClass = it->second;
        }
        std::reverse(inheritanceChain.begin(), inheritanceChain.end());
    }

    // First pass: collect all member types and names in order
    std::vector<llvm::Type*> orderedTypes;
    std::vector<std::string> orderedNames;
    std::unordered_map<std::string, size_t> memberOffsets;
    size_t currentOffset = 0;

    // Add base class members first
    for (const auto& baseClass : inheritanceChain) {
        auto baseType = llvm::StructType::getTypeByName(*context, baseClass);
        if (!baseType) {
            throw std::runtime_error("Base class not found: " + baseClass);
        }

        // Add base class members in order
        auto& baseMembers = memberIndices[baseClass];
        std::vector<std::pair<std::string, size_t>> sortedMembers(baseMembers.begin(), baseMembers.end());
        std::sort(sortedMembers.begin(), sortedMembers.end(),
                 [](const auto& a, const auto& b) { return a.second < b.second; });

        // Get type information from registry
        auto& registry = TypeRegistry::getInstance();
        auto baseClassInfo = typeMetadata->getClassTypeInfo(baseType);
        if (!baseClassInfo) {
            throw std::runtime_error("Class type info not found for: " + baseClass);
        }

        for (const auto& [memberName, baseIndex] : sortedMembers) {
            auto memberTypeInfo = baseClassInfo->getMemberType(memberName);
            if (!memberTypeInfo) {
                throw std::runtime_error("Member type info not found for: " + memberName + " in class " + baseClass);
            }
            orderedTypes.push_back(getLLVMTypeFromTypeInfo(memberTypeInfo));
            orderedNames.push_back(memberName);
            memberOffsets[memberName] = currentOffset++;
        }
    }

    // Add class's own members
    auto bodyCtx = ctx->classBody();
    if (bodyCtx) {
        for (auto memberCtx : bodyCtx->classMember()) {
            if (auto varDecl = dynamic_cast<PrystParser::ClassVariableDeclContext*>(memberCtx)) {
                std::string memberName = varDecl->IDENTIFIER()->getText();
                llvm::Type* memberType = getLLVMType(varDecl->type()->getText());
                orderedTypes.push_back(memberType);
                orderedNames.push_back(memberName);
                memberOffsets[memberName] = currentOffset++;
            } else if (auto funcDecl = dynamic_cast<PrystParser::ClassFunctionDeclContext*>(memberCtx)) {
                visit(funcDecl);
            }
        }
    }

    // Create the struct type with ordered members
    llvm::StructType* classType = llvm::StructType::create(*context, orderedTypes, className);
    classTypes[className] = classType;

    // Store member indices in order
    memberIndices[className] = memberOffsets;

    // Record immediate base class relationship
    if (!immediateBase.empty()) {
        classInheritance[className] = immediateBase;
    }

    return nullptr;
}

// Class Variable Declaration: Handles class member variables
std::any LLVMCodegen::visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) {
    std::string memberName = ctx->IDENTIFIER()->getText();
    llvm::Type* memberType = getLLVMType(ctx->type()->getText());

    if (ctx->expression()) {
        visit(ctx->expression());
    }
    return nullptr;
}

// Class Function Declaration: Handles class member functions
std::any LLVMCodegen::visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) {
    std::string funcName = ctx->IDENTIFIER()->getText();
    llvm::Type* returnType = getLLVMType(ctx->type()->getText());

    // Save the current named values
    std::unordered_map<std::string, llvm::AllocaInst*> oldNamedValues = namedValues;

    // Visit the function body declarations
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Restore the named values
    namedValues = oldNamedValues;
    return nullptr;
}

// Parameter List: Handled in function declaration
std::any LLVMCodegen::visitParamList(PrystParser::ParamListContext* ctx) {
    return nullptr;
}

// Parameter: Handled in function declaration
std::any LLVMCodegen::visitParam(PrystParser::ParamContext* ctx) {
    return nullptr;
}

// Type: Returns the LLVM type
std::any LLVMCodegen::visitType(PrystParser::TypeContext* ctx) {
    return getLLVMType(ctx->getText());
}

// Expression Statement: Evaluates an expression
std::any LLVMCodegen::visitExprStatement(PrystParser::ExprStatementContext* ctx) {
    visit(ctx->expression());
    return nullptr;
}

// If Statement: Handles if statements
std::any LLVMCodegen::visitIfStatement(PrystParser::IfStatementContext* ctx) {
    visit(ctx->expression());
    llvm::Value* condValue = lastValue;

    // Convert condition to a bool by comparing non-equality with zero
    condValue = builder->CreateICmpNE(condValue, llvm::ConstantInt::get(condValue->getType(), 0), "ifcond");

    llvm::Function* function = builder->GetInsertBlock()->getParent();

    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(*context, "then", function);
    llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(*context, "else");
    llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(*context, "ifcont");

    if (ctx->ELSE()) {
        builder->CreateCondBr(condValue, thenBlock, elseBlock);
    } else {
        builder->CreateCondBr(condValue, thenBlock, mergeBlock);
    }

    // Emit then block
    builder->SetInsertPoint(thenBlock);
    visit(ctx->statement(0));
    if (!builder->GetInsertBlock()->getTerminator()) {
        builder->CreateBr(mergeBlock);
    }

    // Emit else block
    if (ctx->ELSE()) {
        elseBlock->insertInto(function);
        builder->SetInsertPoint(elseBlock);
        visit(ctx->statement(1));
        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateBr(mergeBlock);
        }
    }

    // Emit merge block
    mergeBlock->insertInto(function);
    builder->SetInsertPoint(mergeBlock);

    return nullptr;
}

// While Statement: Handles while loops
std::any LLVMCodegen::visitWhileStatement(PrystParser::WhileStatementContext* ctx) {
    llvm::Function* function = builder->GetInsertBlock()->getParent();

    llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(*context, "whilecond", function);
    llvm::BasicBlock* loopBlock = llvm::BasicBlock::Create(*context, "whilebody");
    llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(*context, "whileend");

    builder->CreateBr(condBlock);

    builder->SetInsertPoint(condBlock);
    visit(ctx->expression());
    llvm::Value* condValue = lastValue;
    condValue = builder->CreateICmpNE(condValue, llvm::ConstantInt::get(condValue->getType(), 0), "whilecond");
    builder->CreateCondBr(condValue, loopBlock, afterBlock);

    builder->SetInsertPoint(loopBlock);
    visit(ctx->statement());
    if (!builder->GetInsertBlock()->getTerminator()) {
        builder->CreateBr(condBlock);
    }

    builder->SetInsertPoint(afterBlock);

    return nullptr;
}

// For Statement: Handles for loops
std::any LLVMCodegen::visitForStatement(PrystParser::ForStatementContext* ctx) {
    llvm::Function* function = builder->GetInsertBlock()->getParent();

    llvm::BasicBlock* preHeaderBlock = builder->GetInsertBlock();
    llvm::BasicBlock* loopBlock = llvm::BasicBlock::Create(*context, "forloop", function);
    llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(*context, "forend");

    // Handle initializer
    if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->expression().size() > 0) {
        visit(ctx->expression(0));
    }

    // Initial branch to loop block
    builder->CreateBr(loopBlock);

    // Start of loop block
    builder->SetInsertPoint(loopBlock);

    // Loop condition
    if (ctx->expression().size() > 1) {
        visit(ctx->expression(1));
        llvm::Value* condValue = lastValue;
        condValue = builder->CreateICmpNE(condValue, llvm::ConstantInt::get(condValue->getType(), 0), "forcond");
        llvm::BasicBlock* bodyBlock = llvm::BasicBlock::Create(*context, "forbody", function);
        builder->CreateCondBr(condValue, bodyBlock, afterBlock);

        // Loop body
        builder->SetInsertPoint(bodyBlock);
        visit(ctx->statement());

        // Loop increment
        if (ctx->expression().size() > 2) {
            visit(ctx->expression(2));
        }

        // Jump back to loop block
        builder->CreateBr(loopBlock);
    } else {
        // If no condition, treat as infinite loop
        visit(ctx->statement());

        // Loop increment
        if (ctx->expression().size() > 2) {
            visit(ctx->expression(2));
        }

        // Jump back to loop block
        builder->CreateBr(loopBlock);
    }

    // After loop
    builder->SetInsertPoint(afterBlock);

    return nullptr;
}

// Return Statement: Handles return statements
std::any LLVMCodegen::visitReturnStatement(PrystParser::ReturnStatementContext* ctx) {
    if (ctx->expression()) {
        visit(ctx->expression());
        builder->CreateRet(lastValue);
    } else {
        builder->CreateRetVoid();
    }
    return nullptr;
}

// Block: Handles a block of statements
std::any LLVMCodegen::visitBlockStatement(PrystParser::BlockStatementContext* ctx) {
    // Save the current named values
    std::unordered_map<std::string, llvm::AllocaInst*> oldNamedValues = namedValues;

    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Restore the named values
    namedValues = oldNamedValues;
    return nullptr;
}

// Expression: Handles expressions
// Assignment: Handles both direct variable assignments and member access assignments
std::any LLVMCodegen::visitAssignment(PrystParser::AssignmentContext* ctx) {
    std::cerr << "DEBUG: Starting visitAssignment" << std::endl;
    std::cerr << "DEBUG: Assignment context text: " << ctx->getText() << std::endl;

    llvm::Value* varAddress;

    // Handle call.DOT IDENTIFIER = expr case
    if (ctx->call() && ctx->DOT()) {
        std::cerr << "DEBUG: Handling call.DOT IDENTIFIER assignment" << std::endl;
        visit(ctx->call());
        llvm::Value* object = lastValue;

        if (!object) {
            throw std::runtime_error("Object is null in member assignment");
        }

        std::string typeStr;
        llvm::raw_string_ostream rso(typeStr);

        // Print initial object type
        object->getType()->print(rso);
        rso.flush();
        std::cerr << "DEBUG: Initial object type: " << typeStr << std::endl;

        // Get the object pointer for member access
        if (auto* loadInst = llvm::dyn_cast<llvm::LoadInst>(object)) {
            std::cerr << "DEBUG: Converting load instruction to pointer operand" << std::endl;
            object = loadInst->getPointerOperand();
            typeStr.clear();
            object->getType()->print(rso);
            rso.flush();
            std::cerr << "DEBUG: After load conversion type: " << typeStr << std::endl;
        }

        // Get type information from registry
        auto& registry = TypeRegistry::getInstance();
        auto typeInfo = typeMetadata->getTypeInfo(object);
        if (!typeInfo || typeInfo->getKind() != pryst::TypeKind::Class) {
            throw std::runtime_error("Expected class type in member access");
        }

        // Get class type info
        auto classInfo = std::dynamic_pointer_cast<pryst::ClassTypeInfo>(typeInfo);
        if (!classInfo) {
            throw std::runtime_error("Failed to get class type info");
        }

        // Get the class name and member name
        std::string className = classInfo->getClassName();
        std::string memberName = ctx->IDENTIFIER()->getText();
        std::cerr << "DEBUG: Looking for member '" << memberName << "' in class '" << className << "'" << std::endl;

        // Find member in class hierarchy using TypeMetadata
        size_t memberOffset = classInfo->getMemberIndex(memberName);
        if (memberOffset == static_cast<size_t>(-1)) {
            throw std::runtime_error("Member '" + memberName + "' not found in class '" + className + "' or its base classes");
        }
        std::cerr << "DEBUG: Found member at offset " << memberOffset << std::endl;

        // Create GEP instruction to get member address
        std::vector<llvm::Value*> indices = {
            llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
            llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), memberOffset)
        };
        varAddress = builder->CreateGEP(classInfo->getLLVMType(), object, indices, "member.ptr");
    } else {
        // Handle simple IDENTIFIER = expr case
        std::cerr << "DEBUG: Handling simple assignment" << std::endl;
        auto it = namedValues.find(ctx->IDENTIFIER()->getText());
        if (it == namedValues.end()) {
            throw std::runtime_error("Undefined variable: " + ctx->IDENTIFIER()->getText());
        }
        varAddress = it->second;
    }

    // Handle the assignment expression
    std::cerr << "DEBUG: Visiting expression for assignment" << std::endl;
    visit(ctx->expression());
    llvm::Value* exprValue = lastValue;

    if (!exprValue) {
        throw std::runtime_error("Invalid expression value in assignment");
    }

    builder->CreateStore(exprValue, varAddress);
    lastValue = exprValue;
    std::cerr << "DEBUG: Assignment completed" << std::endl;
    return nullptr;
}

// Logical OR: Handles logical OR operations
std::any LLVMCodegen::visitLogicOr(PrystParser::LogicOrContext* ctx) {
    if (ctx->logicAnd().size() == 1) {
        visit(ctx->logicAnd(0));
        return nullptr;
    }

    llvm::Function* function = builder->GetInsertBlock()->getParent();
    if (!function) {
        throw std::runtime_error("Invalid function context in logical OR");
    }

    llvm::BasicBlock* lhsBlock = builder->GetInsertBlock();
    llvm::BasicBlock* rhsBlock = llvm::BasicBlock::Create(*context, "lor.rhs", function);
    llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(*context, "lor.merge", function);

    // Evaluate LHS
    visit(ctx->logicAnd(0));
    llvm::Value* lhsValue = lastValue;
    if (!lhsValue) {
        throw std::runtime_error("Invalid left-hand side in logical OR");
    }
    lhsValue = builder->CreateICmpNE(lhsValue, llvm::ConstantInt::get(lhsValue->getType(), 0), "lor.lhs");
    builder->CreateCondBr(lhsValue, mergeBlock, rhsBlock);

    // Evaluate RHS
    builder->SetInsertPoint(rhsBlock);
    visit(ctx->logicAnd(1));
    llvm::Value* rhsValue = lastValue;
    if (!rhsValue) {
        throw std::runtime_error("Invalid right-hand side in logical OR");
    }
    rhsValue = builder->CreateICmpNE(rhsValue, llvm::ConstantInt::get(rhsValue->getType(), 0), "lor.rhs");
    builder->CreateBr(mergeBlock);
    // Merge results
    builder->SetInsertPoint(mergeBlock);
    llvm::PHINode* phiNode = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "lor.result");
    phiNode->addIncoming(llvm::ConstantInt::getTrue(*context), lhsBlock);
    phiNode->addIncoming(rhsValue, rhsBlock);

    lastValue = phiNode;
    return nullptr;
}

// Logical AND: Handles logical AND operations
std::any LLVMCodegen::visitLogicAnd(PrystParser::LogicAndContext* ctx) {
    if (ctx->equality().size() == 1) {
        visit(ctx->equality(0));
        return nullptr;
    }

    // Implement short-circuit evaluation
    llvm::Function* function = builder->GetInsertBlock()->getParent();

    llvm::BasicBlock* lhsBlock = builder->GetInsertBlock();
    llvm::BasicBlock* rhsBlock = llvm::BasicBlock::Create(*context, "land.rhs", function);
    llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(*context, "land.merge", function);

    // Evaluate LHS
    visit(ctx->equality(0));
    llvm::Value* lhsValue = lastValue;
    lhsValue = builder->CreateICmpNE(lhsValue, llvm::ConstantInt::get(lhsValue->getType(), 0), "land.lhs");

    builder->CreateCondBr(lhsValue, rhsBlock, mergeBlock);

    // Evaluate RHS
    builder->SetInsertPoint(rhsBlock);
    visit(ctx->equality(1));
    llvm::Value* rhsValue = lastValue;
    rhsValue = builder->CreateICmpNE(rhsValue, llvm::ConstantInt::get(rhsValue->getType(), 0), "land.rhs");
    builder->CreateBr(mergeBlock);

    // Merge results
    builder->SetInsertPoint(mergeBlock);
    llvm::PHINode* phiNode = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "land.result");
    phiNode->addIncoming(llvm::ConstantInt::getFalse(*context), lhsBlock);
    phiNode->addIncoming(rhsValue, rhsBlock);

    lastValue = phiNode;
    return nullptr;
}

// Equality: Handles equality comparisons
std::any LLVMCodegen::visitEquality(PrystParser::EqualityContext* ctx) {
    visit(ctx->comparison(0));
    llvm::Value* left = lastValue;

    for (size_t i = 1; i < ctx->comparison().size(); ++i) {
        visit(ctx->comparison(i));
        llvm::Value* right = lastValue;

        if (ctx->EQUAL_EQUAL(i - 1)) {
            if (left->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFCmpOEQ(left, right, "eqtmp");
            } else {
                lastValue = builder->CreateICmpEQ(left, right, "eqtmp");
            }
        } else if (ctx->NOT_EQUAL(i - 1)) {
            if (left->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFCmpONE(left, right, "neqtmp");
            } else {
                lastValue = builder->CreateICmpNE(left, right, "neqtmp");
            }
        }
        left = lastValue;
    }

    return nullptr;
}

// Comparison: Handles comparison operations
std::any LLVMCodegen::visitComparison(PrystParser::ComparisonContext* ctx) {
    visit(ctx->addition(0));
    llvm::Value* left = lastValue;

    for (size_t i = 1; i < ctx->addition().size(); ++i) {
        visit(ctx->addition(i));
        llvm::Value* right = lastValue;

        if (ctx->LESS(i - 1)) {
            lastValue = builder->CreateICmpSLT(left, right, "lttmp");
        } else if (ctx->LESS_EQUAL(i - 1)) {
            lastValue = builder->CreateICmpSLE(left, right, "letmp");
        } else if (ctx->GREATER(i - 1)) {
            lastValue = builder->CreateICmpSGT(left, right, "gttmp");
        } else if (ctx->GREATER_EQUAL(i - 1)) {
            lastValue = builder->CreateICmpSGE(left, right, "getmp");
        }
        left = lastValue;
    }

    return nullptr;
}

// Addition/Subtraction: Handles addition and subtraction
std::any LLVMCodegen::visitAddition(PrystParser::AdditionContext* ctx) {
    visit(ctx->multiplication(0));
    llvm::Value* left = lastValue;

    for (size_t i = 1; i < ctx->multiplication().size(); ++i) {
        visit(ctx->multiplication(i));
        llvm::Value* right = lastValue;

        if (ctx->PLUS(i - 1)) {
            if (left->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFAdd(left, right, "addtmp");
            } else {
                lastValue = builder->CreateAdd(left, right, "addtmp");
            }
        } else if (ctx->MINUS(i - 1)) {
            if (left->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFSub(left, right, "subtmp");
            } else {
                lastValue = builder->CreateSub(left, right, "subtmp");
            }
        }
        left = lastValue;
    }

    return nullptr;
}

// Multiplication/Division: Handles multiplication and division
std::any LLVMCodegen::visitMultiplication(PrystParser::MultiplicationContext* ctx) {
    visit(ctx->unary(0));
    llvm::Value* left = lastValue;

    for (size_t i = 1; i < ctx->unary().size(); ++i) {
        visit(ctx->unary(i));
        llvm::Value* right = lastValue;

        if (ctx->STAR(i - 1)) {
            if (left->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFMul(left, right, "multmp");
            } else {
                lastValue = builder->CreateMul(left, right, "multmp");
            }
        } else if (ctx->SLASH(i - 1)) {
            if (left->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFDiv(left, right, "divtmp");
            } else {
                lastValue = builder->CreateSDiv(left, right, "divtmp");
            }
        } else if (ctx->PERCENT(i - 1)) {
            if (left->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFRem(left, right, "modtmp");
            } else {
                lastValue = builder->CreateSRem(left, right, "modtmp");
            }
        }
        left = lastValue;
    }

    return nullptr;
}

// Unary: Handles unary operations
std::any LLVMCodegen::visitUnary(PrystParser::UnaryContext* ctx) {
    if (ctx->postfix()) {
        visit(ctx->postfix());
    } else if (ctx->unary()) {
        visit(ctx->unary());
        llvm::Value* operand = lastValue;

        if (ctx->MINUS()) {
            if (operand->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFNeg(operand, "negtmp");
            } else {
                lastValue = builder->CreateNeg(operand, "negtmp");
            }
        } else if (ctx->BANG()) {
            lastValue = builder->CreateNot(operand, "nottmp");
        } else if (ctx->INCREMENT()) {
            llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
            lastValue = builder->CreateAdd(operand, one, "inctmp");
            // Store the incremented value back if possible
            // This requires access to the variable's address
            throw std::runtime_error("Prefix increment not fully implemented");
        } else if (ctx->DECREMENT()) {
            llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
            lastValue = builder->CreateSub(operand, one, "dectmp");
            // Store the decremented value back if possible
            // This requires access to the variable's address
            throw std::runtime_error("Prefix decrement not fully implemented");
        }
    }
    return nullptr;
}

// Postfix: Handles postfix operations
std::any LLVMCodegen::visitPostfix(PrystParser::PostfixContext* ctx) {
    visit(ctx->primary());
    llvm::Value* operand = lastValue;

    // Handle suffixes (call or member access)
    for (auto suffix : ctx->suffix()) {
        if (auto callSuffix = suffix->callSuffix()) {
            // Handle function call
            std::vector<llvm::Value*> args;
            if (callSuffix->arguments()) {
                for (auto expr : callSuffix->arguments()->expression()) {
                    visit(expr);
                    args.push_back(lastValue);
                }
            }
            // Create function call
            if (auto* func = llvm::dyn_cast<llvm::Function>(operand)) {
                operand = builder->CreateCall(func, args, "calltmp");
            } else {
                throw std::runtime_error("Called value is not a function");
            }
        } else if (auto memberSuffix = suffix->memberSuffix()) {
            // Handle member access
            std::string memberName = memberSuffix->IDENTIFIER()->getText();
            auto typeInfo = typeMetadata->getTypeInfo(operand);
            if (!typeInfo || typeInfo->getKind() != pryst::TypeKind::Class) {
                throw std::runtime_error("Expected class type in member access");
            }
            auto classInfo = std::dynamic_pointer_cast<pryst::ClassTypeInfo>(typeInfo);
            if (!classInfo) {
                throw std::runtime_error("Failed to get class type info");
            }
            size_t memberOffset = classInfo->getMemberIndex(memberName);
            if (memberOffset == static_cast<size_t>(-1)) {
                throw std::runtime_error("Member '" + memberName + "' not found");
            }
            std::vector<llvm::Value*> indices = {
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), memberOffset)
            };
            operand = builder->CreateGEP(classInfo->getLLVMType(), operand, indices, "member.ptr");
            operand = builder->CreateLoad(classInfo->getMemberType(memberName), operand, "member");
        }
    }

    // Handle increment/decrement
    if (ctx->INCREMENT()) {
        llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
        llvm::Value* newValue = builder->CreateAdd(operand, one, "postinctmp");
        // Store the incremented value back if possible
        if (auto* loadInst = llvm::dyn_cast<llvm::LoadInst>(operand)) {
            builder->CreateStore(newValue, loadInst->getPointerOperand());
        }
        lastValue = operand; // Return original value for postfix increment
    } else if (ctx->DECREMENT()) {
        llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
        llvm::Value* newValue = builder->CreateSub(operand, one, "postdectmp");
        // Store the decremented value back if possible
        if (auto* loadInst = llvm::dyn_cast<llvm::LoadInst>(operand)) {
            builder->CreateStore(newValue, loadInst->getPointerOperand());
        }
        lastValue = operand; // Return original value for postfix decrement
    } else {
        lastValue = operand;
    }

    return nullptr;
}


// Function Call and Member Access: Handles function calls and member access
std::any LLVMCodegen::visitCall(PrystParser::CallContext* ctx) {
    std::cerr << "DEBUG: Starting visitCall" << std::endl;

    // Visit the primary expression first
    visit(ctx->primary());
    llvm::Value* callee = lastValue;

    // Handle function calls in sequence
    for (size_t i = 0; i < ctx->LPAREN().size(); i++) {
        std::cerr << "DEBUG: Handling function call" << std::endl;

        // Process arguments
        std::vector<llvm::Value*> args;
        if (ctx->arguments(i)) {
            for (auto expr : ctx->arguments(i)->expression()) {
                visit(expr);
                args.push_back(lastValue);
            }
        }

        // Handle built-in functions
        if (llvm::Function* functionCallee = llvm::dyn_cast<llvm::Function>(callee)) {
            std::string functionName = functionCallee->getName().str();

            if (functionName == "print") {
                // Handle the print function
                llvm::Function* printfFunc = declarePrintf();
                llvm::Value* formatStr = builder->CreateGlobalString("%s\n");
                args.insert(args.begin(), formatStr);
                lastValue = builder->CreateCall(printfFunc, args, "calltmp");
            } else {
                // Direct function call
                lastValue = builder->CreateCall(functionCallee, args, "calltmp");
            }
        } else {
            // Check if callee is a function using type metadata
            auto typeInfo = typeMetadata->getTypeInfo(callee);
            if (!typeInfo || !typeInfo->isFunction()) {
                throw std::runtime_error("Called value is not a function");
            }

            // Get function name from primary if available
            std::string functionName;
            if (auto* primary = ctx->primary()) {
                if (primary->IDENTIFIER()) {
                    functionName = primary->IDENTIFIER()->getText();
                }
            }

            // Create a function type matching the callee's type
            llvm::FunctionType* funcType = functionTypes[functionName];
            if (!funcType) {
                throw std::runtime_error("Unknown function: " + functionName);
            }

            lastValue = builder->CreateCall(funcType, callee, args, "calltmp");
        }

        // Update callee for potential chained function calls
        callee = lastValue;
    }

    return nullptr;
}
// Primary: Handles primary expressions
std::any LLVMCodegen::visitPrimary(PrystParser::PrimaryContext* ctx) {
    if (ctx->TRUE()) {
        lastValue = llvm::ConstantInt::getTrue(*context);
    } else if (ctx->FALSE()) {
        lastValue = llvm::ConstantInt::getFalse(*context);
    } else if (ctx->NULL_()) {
        lastValue = llvm::ConstantPointerNull::get(llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(*context)));
    } else if (ctx->NUMBER()) {
        std::string numStr = ctx->NUMBER()->getText();
        if (numStr.find('.') != std::string::npos) {
            lastValue = llvm::ConstantFP::get(*context, llvm::APFloat(std::stod(numStr)));
        } else {
            lastValue = llvm::ConstantInt::get(*context, llvm::APInt(32, std::stoll(numStr), true));
        }
    } else if (ctx->STRING()) {
        std::string str = ctx->STRING()->getText();
        str = str.substr(1, str.length() - 2); // Remove quotes
        lastValue = builder->CreateGlobalString(str, "str");
    } else if (ctx->IDENTIFIER()) {
        std::string name = ctx->IDENTIFIER()->getText();

        // Check if it's a variable
        auto varIt = namedValues.find(name);
        if (varIt != namedValues.end()) {
            lastValue = builder->CreateLoad(varIt->second->getAllocatedType(), varIt->second, name.c_str());
        }
        // Check if it's a function
        else if (functions.find(name) != functions.end()) {
            lastValue = functions[name];
        } else {
            throw std::runtime_error("Unknown identifier: " + name);
        }
    } else if (ctx->LPAREN()) {
        visit(ctx->expression());
    } else if (ctx->SUPER()) {
        // Handle 'super' keyword (not implemented)
        throw std::runtime_error("'super' keyword not implemented");
    } else if (ctx->newExpression()) {
        visit(ctx->newExpression());
    }

    return nullptr;
}

// New Expression: Handles object instantiation
std::any LLVMCodegen::visitNewExpression(PrystParser::NewExpressionContext* ctx) {
    std::string className = ctx->IDENTIFIER()->getText();
    llvm::StructType* classType = llvm::StructType::getTypeByName(*context, className);
    if (!classType) {
        throw std::runtime_error("Unknown class: " + className);
    }

    // Use getUnqual for LLVM 20.0.0 compatibility
    llvm::Type* classPtrType = llvm::PointerType::getUnqual(classType);

    // Allocate memory for the object
    llvm::Function* mallocFunc = module->getFunction("malloc");
    if (!mallocFunc) {
        llvm::FunctionType* mallocType = llvm::FunctionType::get(
            llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(*context)),
            { llvm::Type::getInt64Ty(*context) },
            false);
        mallocFunc = llvm::Function::Create(mallocType, llvm::Function::ExternalLinkage, "malloc", module.get());
    }

    llvm::Value* size = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context),
                                               module->getDataLayout().getTypeAllocSize(classType));
    llvm::Value* mem = builder->CreateCall(mallocFunc, {size}, "objmem");
    llvm::Value* obj = builder->CreateBitCast(mem, classPtrType, "obj");

    // Build inheritance chain from base to derived
    std::vector<std::string> inheritanceChain;
    std::string currentClass = className;
    while (!currentClass.empty()) {
        inheritanceChain.insert(inheritanceChain.begin(), currentClass);
        auto it = classInheritance.find(currentClass);
        if (it == classInheritance.end()) break;
        currentClass = it->second;
    }

    // Initialize members following inheritance chain
    for (const auto& cls : inheritanceChain) {
        auto classIt = memberIndices.find(cls);
        if (classIt == memberIndices.end()) continue;

        // Get all members for this class and sort by offset
        std::vector<std::pair<std::string, size_t>> sortedMembers(classIt->second.begin(), classIt->second.end());
        std::sort(sortedMembers.begin(), sortedMembers.end(),
                 [](const auto& a, const auto& b) { return a.second < b.second; });

        // Get the struct type for this class
        auto classStructType = llvm::StructType::getTypeByName(*context, cls);
        if (!classStructType) continue;

        // Get class type info
        auto classInfo = typeMetadata->getClassTypeInfo(classStructType);
        if (!classInfo) {
            throw std::runtime_error("Class type info not found for: " + cls);
        }

        // Initialize members in order of their offsets
        for (const auto& [memberName, offset] : sortedMembers) {
            // Get member type from class type info
            auto memberTypeInfo = classInfo->getMemberType(memberName);
            if (!memberTypeInfo) {
                throw std::runtime_error("Member type info not found: " + memberName);
            }
            llvm::Type* memberType = getLLVMTypeFromTypeInfo(memberTypeInfo);

            // Create GEP using the derived class type but with correct offset
            std::vector<llvm::Value*> indices = {
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), offset)
            };
            llvm::Value* memberPtr = builder->CreateGEP(classType, obj, indices, "member.ptr");
            builder->CreateStore(llvm::Constant::getNullValue(memberType), memberPtr);
        }
    }

    // Optionally, call constructor (not implemented)

    lastValue = obj;
    return nullptr;
}

// Arguments: Not directly used
std::any LLVMCodegen::visitArguments(PrystParser::ArgumentsContext* ctx) {
    return nullptr;
}

// Helper method to get LLVM type from type name
llvm::Type* LLVMCodegen::getLLVMType(const std::string& typeName) {
    if (typeName == "int") {
        return llvm::Type::getInt32Ty(*context);
    } else if (typeName == "float") {
        return llvm::Type::getDoubleTy(*context);
    } else if (typeName == "bool") {
        return llvm::Type::getInt1Ty(*context);
    } else if (typeName == "str") {
        return llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(*context));
    } else {
        // Assume it's a user-defined class type
        llvm::StructType* structType = llvm::StructType::getTypeByName(*context, typeName);
        if (structType) {
            return llvm::PointerType::getUnqual(structType);  // Use getUnqual for LLVM 20.0.0
        } else {
            throw std::runtime_error("Unknown type: " + typeName);
        }
    }
}

// Helper method to create an alloca in the entry block of the function
llvm::AllocaInst* LLVMCodegen::createEntryBlockAlloca(llvm::Function* function, const std::string& varName, llvm::Type* type) {
    llvm::IRBuilder<> tmpBuilder(&function->getEntryBlock(), function->getEntryBlock().begin());
    return tmpBuilder.CreateAlloca(type, nullptr, varName);
}

// Lambda Function: Handles anonymous function declarations
std::any LLVMCodegen::visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) {
    static int lambdaCount = 0;
    std::string funcName = "lambda_" + std::to_string(lambdaCount++);

    // Get return type, default to void if not specified
    llvm::Type* returnType = ctx->type()
        ? getLLVMType(ctx->type()->getText())
        : llvm::Type::getVoidTy(*context);

    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;

    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(getLLVMType(param->type()->getText()));
            paramNames.push_back(param->IDENTIFIER()->getText());
        }
    }

    llvm::FunctionType* funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    llvm::Function* function = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, funcName, module.get());

    // Create function type info
    auto functionTypeInfo = std::make_shared<FunctionTypeInfo>(funcName, funcType);
    typeMetadata->addFunctionTypeInfo(function, functionTypeInfo);

    // Create a new basic block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(bb);

    // Save the current function
    llvm::Function* oldFunction = currentFunction;
    currentFunction = function;

    // Create a new scope for function parameters
    pushScope();

    // Create allocas for parameters
    if (ctx->paramList()) {
        size_t idx = 0;
        for (auto& arg : function->args()) {
            std::string paramName = paramNames[idx++];
            llvm::AllocaInst* alloca = createEntryBlockAlloca(function, paramName, arg.getType());
            builder->CreateStore(&arg, alloca);
            scopeStack.back()[paramName] = alloca;
        }
    }

    // Visit function body
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Add implicit return if needed
    if (!builder->GetInsertBlock()->getTerminator()) {
        if (returnType->isVoidTy()) {
            builder->CreateRetVoid();
        } else {
            builder->CreateRet(llvm::Constant::getNullValue(returnType));
        }
    }

    // Verify the function
    if (llvm::verifyFunction(*function, &llvm::errs())) {
        throw std::runtime_error("Function verification failed for lambda function: " + funcName);
    }

    popScope();
    currentFunction = oldFunction;
    functions[funcName] = function;

    lastValue = function;
    return nullptr;
}
