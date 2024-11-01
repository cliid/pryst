#include "llvm_codegen.hpp"
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/Support/Casting.h>
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

// Function Declaration: Handles function declarations
std::any LLVMCodegen::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    std::string funcName = ctx->IDENTIFIER()->getText();
    llvm::Type* returnType = getLLVMType(ctx->type()->getText());

    std::vector<llvm::Type*> paramTypes;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(getLLVMType(param->type()->getText()));
        }
    }

    llvm::FunctionType* funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, funcName, module.get());
    functionTypes[funcName] = funcType;

    // Set the names for all arguments
    unsigned idx = 0;
    if (ctx->paramList()) {
        for (auto& arg : func->args()) {
            std::string paramName = ctx->paramList()->param(idx)->IDENTIFIER()->getText();
            arg.setName(paramName);
            idx++;
        }
    }

    // Create a new basic block to start insertion into
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Save the current function
    llvm::Function* oldFunction = currentFunction;
    currentFunction = func;

    // Clear the namedValues map for the new function scope
    namedValues.clear();

    // Create allocas for arguments and store them
    idx = 0;
    for (auto& arg : func->args()) {
        llvm::AllocaInst* alloca = createEntryBlockAlloca(func, arg.getName().str(), arg.getType());
        builder->CreateStore(&arg, alloca);
        namedValues[arg.getName().str()] = alloca;
        idx++;
    }

    // Visit the function body
    visit(ctx->block());

    // Ensure the function has a return statement
    if (!builder->GetInsertBlock()->getTerminator()) {
        if (returnType->isVoidTy()) {
            builder->CreateRetVoid();
        } else {
            builder->CreateRet(llvm::Constant::getNullValue(returnType));
        }
    }

    // Verify the function
    if (llvm::verifyFunction(*func, &llvm::errs())) {
        throw std::runtime_error("Function verification failed for function: " + funcName);
    }

    // Restore the old function
    currentFunction = oldFunction;

    // Add the function to the functions map
    functions[funcName] = func;

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

    // Handle optional superclass
    std::vector<llvm::Type*> memberTypes;
    std::vector<std::string> memberNames;
    size_t memberIndex = 0;
    size_t baseOffset = 0;

    // Build inheritance chain from base to derived
    std::vector<std::string> inheritanceChain;
    if (ctx->IDENTIFIER().size() > 1) {
        std::string currentClass = ctx->IDENTIFIER(1)->getText();
        while (!currentClass.empty()) {
            inheritanceChain.insert(inheritanceChain.begin(), currentClass);
            auto it = classInheritance.find(currentClass);
            if (it == classInheritance.end()) break;
            currentClass = it->second;
        }
    }

    // Process members from base class to derived
    for (const auto& baseClass : inheritanceChain) {
        auto baseType = llvm::StructType::getTypeByName(*context, baseClass);
        if (!baseType) {
            throw std::runtime_error("Base class not found: " + baseClass);
        }

        // Record inheritance relationship
        classInheritance[className] = baseClass;

        // Copy base class members and their indices
        for (unsigned i = 0; i < baseType->getNumElements(); i++) {
            memberTypes.push_back(baseType->getElementType(i));
            // Get member name from base class's memberIndices
            for (const auto& pair : memberIndices[baseClass]) {
                if (pair.second == i) {
                    memberNames.push_back(pair.first);
                    addClassMember(className, pair.first, memberIndex++);
                    break;
                }
            }
        }
        baseOffset += baseType->getNumElements();
    }

    // Add class's own members
    for (auto memberCtx : ctx->classMember()) {
        if (memberCtx->variableDecl()) {
            auto varDecl = memberCtx->variableDecl();
            llvm::Type* memberType = getLLVMType(varDecl->type()->getText());
            memberTypes.push_back(memberType);
            std::string memberName = varDecl->IDENTIFIER()->getText();
            memberNames.push_back(memberName);
            addClassMember(className, memberName, memberIndex++);
        } else if (memberCtx->functionDecl()) {
            visit(memberCtx->functionDecl());
        }
    }

    // Create the struct type for the class
    llvm::StructType* classType = llvm::StructType::create(*context, memberTypes, className);
    classTypes[className] = classType;

    return nullptr;
}

// Class Member: Handles class members
std::any LLVMCodegen::visitClassMember(PrystParser::ClassMemberContext* ctx) {
    if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->functionDecl()) {
        visit(ctx->functionDecl());
    }
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

// Statement: Dispatches to the appropriate statement type
std::any LLVMCodegen::visitStatement(PrystParser::StatementContext* ctx) {
    if (ctx->expressionStmt()) {
        visit(ctx->expressionStmt());
    } else if (ctx->ifStmt()) {
        visit(ctx->ifStmt());
    } else if (ctx->whileStmt()) {
        visit(ctx->whileStmt());
    } else if (ctx->forStmt()) {
        visit(ctx->forStmt());
    } else if (ctx->returnStmt()) {
        visit(ctx->returnStmt());
    } else if (ctx->block()) {
        visit(ctx->block());
    } else {
        throw std::runtime_error("Unexpected statement type");
    }
    return nullptr;
}

// Expression Statement: Evaluates an expression
std::any LLVMCodegen::visitExpressionStmt(PrystParser::ExpressionStmtContext* ctx) {
    visit(ctx->expression());
    return nullptr;
}

// If Statement: Handles if statements
std::any LLVMCodegen::visitIfStmt(PrystParser::IfStmtContext* ctx) {
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
std::any LLVMCodegen::visitWhileStmt(PrystParser::WhileStmtContext* ctx) {
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
std::any LLVMCodegen::visitForStmt(PrystParser::ForStmtContext* ctx) {
    llvm::Function* function = builder->GetInsertBlock()->getParent();

    llvm::BasicBlock* preHeaderBlock = builder->GetInsertBlock();
    llvm::BasicBlock* loopBlock = llvm::BasicBlock::Create(*context, "forloop", function);
    llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(*context, "forend");

    // Handle initializer
    if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->expressionStmt()) {
        visit(ctx->expressionStmt());
    }

    // Initial branch to loop block
    builder->CreateBr(loopBlock);

    // Start of loop block
    builder->SetInsertPoint(loopBlock);

    // Loop condition
    if (ctx->expression().size() > 0) {
        visit(ctx->expression(0));
        llvm::Value* condValue = lastValue;
        condValue = builder->CreateICmpNE(condValue, llvm::ConstantInt::get(condValue->getType(), 0), "forcond");
        llvm::BasicBlock* bodyBlock = llvm::BasicBlock::Create(*context, "forbody", function);
        builder->CreateCondBr(condValue, bodyBlock, afterBlock);

        // Loop body
        builder->SetInsertPoint(bodyBlock);
        visit(ctx->statement());

        // Loop increment
        if (ctx->expression().size() > 1) {
            visit(ctx->expression(1));
        }

        // Jump back to loop block
        builder->CreateBr(loopBlock);
    } else {
        // If no condition, treat as infinite loop
        visit(ctx->statement());

        // Loop increment
        if (ctx->expression().size() > 1) {
            visit(ctx->expression(1));
        }

        // Jump back to loop block
        builder->CreateBr(loopBlock);
    }

    // After loop
    builder->SetInsertPoint(afterBlock);

    return nullptr;
}

// Return Statement: Handles return statements
std::any LLVMCodegen::visitReturnStmt(PrystParser::ReturnStmtContext* ctx) {
    if (ctx->expression()) {
        visit(ctx->expression());
        builder->CreateRet(lastValue);
    } else {
        builder->CreateRetVoid();
    }
    return nullptr;
}

// Block: Handles a block of statements
std::any LLVMCodegen::visitBlock(PrystParser::BlockContext* ctx) {
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
std::any LLVMCodegen::visitExpression(PrystParser::ExpressionContext* ctx) {
    if (ctx->assignment()) {
        visit(ctx->assignment());
    } else {
        visit(ctx->logicOr());
    }
    return nullptr;
}

// Assignment: Handles assignments
std::any LLVMCodegen::visitAssignment(PrystParser::AssignmentContext* ctx) {
    std::string varName;
    llvm::Value* varAddress;

    if (ctx->call()) {
        // Handle member assignments
        visit(ctx->call());
        llvm::Value* object = lastValue;

        // Get the member offset
        auto memberName = ctx->call()->callSuffix().back()->IDENTIFIER()->getText();
        if (!object->getType()->isPointerTy()) {
            throw std::runtime_error("Expected pointer type in member assignment");
        }
        auto ptrType = llvm::cast<llvm::PointerType>(object->getType());
        auto elementType = ptrType->getContainedType(0);
        auto structType = llvm::dyn_cast<llvm::StructType>(elementType);
        if (!structType) {
            throw std::runtime_error("Expected identifier in member assignment");
        }

        // Find member in class hierarchy
        size_t memberIndex;
        llvm::StructType* memberOwnerType = structType;
        std::string currentClass = structType->getName().str();
        size_t baseOffset = 0;

        try {
            memberIndex = getMemberIndex(structType, memberName);
        } catch (const std::runtime_error&) {
            // If not found in current class, check base classes
            while (true) {
                auto it = classInheritance.find(currentClass);
                if (it == classInheritance.end()) {
                    throw std::runtime_error("Member not found: " + memberName);
                }
                currentClass = it->second;
                auto baseType = llvm::StructType::getTypeByName(*context, currentClass);
                if (!baseType) {
                    throw std::runtime_error("Base class not found: " + currentClass);
                }
                try {
                    memberIndex = getMemberIndex(baseType, memberName);
                    memberOwnerType = baseType;
                    break;
                } catch (const std::runtime_error&) {
                    baseOffset += baseType->getNumElements();
                    continue;
                }
            }
        }

        // Create GEP instruction to get member address
        std::vector<llvm::Value*> indices = {
            llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
            llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), memberIndex + baseOffset)
        };
        varAddress = builder->CreateGEP(structType, object, indices, "member.addr");
    } else {
        varName = ctx->IDENTIFIER()->getText();
        auto it = namedValues.find(varName);
        if (it == namedValues.end()) {
            throw std::runtime_error("Undefined variable: " + varName);
        }
        varAddress = it->second;
    }

    visit(ctx->expression());
    llvm::Value* exprValue = lastValue;

    builder->CreateStore(exprValue, varAddress);
    lastValue = exprValue;
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

    if (ctx->INCREMENT()) {
        llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
        llvm::Value* newValue = builder->CreateAdd(operand, one, "postinctmp");
        // Store the incremented value back if possible
        // This requires access to the variable's address
        throw std::runtime_error("Postfix increment not fully implemented");
    } else if (ctx->DECREMENT()) {
        llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
        llvm::Value* newValue = builder->CreateSub(operand, one, "postdectmp");
        // Store the decremented value back if possible
        // This requires access to the variable's address
        throw std::runtime_error("Postfix decrement not fully implemented");
    }

    return nullptr;
}


// Function Call and Member Access: Handles function calls and member access
std::any LLVMCodegen::visitCall(PrystParser::CallContext* ctx) {
    // Start by visiting the primary
    visit(ctx->primary());
    llvm::Value* callee = lastValue;

    // Process each callSuffix
    for (auto suffixCtx : ctx->callSuffix()) {
        if (suffixCtx->LPAREN()) {
            // Function call
            std::vector<llvm::Value*> args;

            if (suffixCtx->arguments()) {
                for (auto expr : suffixCtx->arguments()->expression()) {
                    visit(expr);
                    args.push_back(lastValue);
                }
            }

            std::string functionName = ctx->primary()->getText();
            if (functionName == "print") {
                // Handle the print function
                llvm::Function* printfFunc = declarePrintf();
                llvm::Value* formatStr = builder->CreateGlobalString("%s\n");
                args.insert(args.begin(), formatStr);
                lastValue = builder->CreateCall(printfFunc, args, "calltmp");
            } else {
                // Attempt to cast callee to a Function*
                llvm::Function* functionCallee = llvm::dyn_cast<llvm::Function>(callee);

                if (functionCallee) {
                    // Direct function call
                    lastValue = builder->CreateCall(functionCallee, args, "calltmp");
                } else {
                    // Assume callee is a function pointer
                    if (!callee->getType()->isPointerTy()) {
                        throw std::runtime_error("Called value is not a function or function pointer");
                    }
                    // Create a function type matching the callee's type
                    std::string calleeName = ctx->primary()->getText();
                    llvm::FunctionType* funcType = functionTypes[calleeName];

                    if (!funcType) {
                        throw std::runtime_error("Unknown function: " + calleeName);
                    }

                    lastValue = builder->CreateCall(funcType, callee, args, "calltmp");
                }
            }
        } else if (suffixCtx->DOT()) {
            // Member access
            std::string memberName = suffixCtx->IDENTIFIER()->getText();

            // Get the struct type from the object
            if (!callee->getType()->isPointerTy()) {
                throw std::runtime_error("Cannot access member of non-pointer type");
            }
            auto ptrType = llvm::cast<llvm::PointerType>(callee->getType());
            auto elementType = ptrType->getContainedType(0);
            auto structType = llvm::dyn_cast<llvm::StructType>(elementType);
            if (!structType) {
                throw std::runtime_error("Cannot access member of non-object type");
            }

            // Find member in class hierarchy
            size_t memberIndex;
            llvm::StructType* memberOwnerType = structType;
            std::string currentClass = structType->getName().str();
            size_t baseOffset = 0;

            try {
                memberIndex = getMemberIndex(structType, memberName);
            } catch (const std::runtime_error&) {
                // If not found in current class, check base classes
                while (true) {
                    auto it = classInheritance.find(currentClass);
                    if (it == classInheritance.end()) {
                        throw std::runtime_error("Member not found: " + memberName);
                    }
                    currentClass = it->second;
                    auto baseType = llvm::StructType::getTypeByName(*context, currentClass);
                    if (!baseType) {
                        throw std::runtime_error("Base class not found: " + currentClass);
                    }
                    try {
                        memberIndex = getMemberIndex(baseType, memberName);
                        memberOwnerType = baseType;
                        break;
                    } catch (const std::runtime_error&) {
                        baseOffset += baseType->getNumElements();
                        continue;
                    }
                }
            }

            // Create GEP instruction to get member address
            std::vector<llvm::Value*> indices = {
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), memberIndex + baseOffset)
            };
            lastValue = builder->CreateGEP(structType, callee, indices, "member.ptr");
            auto memberType = memberOwnerType->getElementType(memberIndex);
            lastValue = builder->CreateLoad(memberType, lastValue, "member");
        } else if (suffixCtx->LBRACKET()) {
            // Array indexing (not implemented)
            throw std::runtime_error("Array indexing not implemented");
        }
    }

    return nullptr;
}

// Call Suffix: Not directly used
std::any LLVMCodegen::visitCallSuffix(PrystParser::CallSuffixContext* ctx) {
    return nullptr;
}

// Primary: Handles primary expressions
std::any LLVMCodegen::visitPrimary(PrystParser::PrimaryContext* ctx) {
    if (ctx->TRUE()) {
        lastValue = llvm::ConstantInt::getTrue(*context);
    } else if (ctx->FALSE()) {
        lastValue = llvm::ConstantInt::getFalse(*context);
    } else if (ctx->NULL_()) {
        lastValue = llvm::ConstantPointerNull::get(llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0));
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

    llvm::Type* classPtrType = classType->getPointerTo();

    // Allocate memory for the object
    llvm::Function* mallocFunc = module->getFunction("malloc");
    if (!mallocFunc) {
        llvm::FunctionType* mallocType = llvm::FunctionType::get(
            llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
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
    size_t memberOffset = 0;
    for (const auto& cls : inheritanceChain) {
        auto type = llvm::StructType::getTypeByName(*context, cls);
        if (!type) continue;

        // Initialize members for this class
        for (unsigned i = 0; i < type->getNumElements(); i++) {
            llvm::Type* memberType = type->getElementType(i);
            std::vector<llvm::Value*> indices = {
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), memberOffset + i)
            };
            llvm::Value* memberPtr = builder->CreateGEP(classType, obj, indices, "member.ptr");
            builder->CreateStore(llvm::Constant::getNullValue(memberType), memberPtr);
        }
        memberOffset += type->getNumElements();
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
        return llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0);
    } else {
        // Assume it's a user-defined class type
        llvm::StructType* structType = llvm::StructType::getTypeByName(*context, typeName);
        if (structType) {
            return structType->getPointerTo();
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
