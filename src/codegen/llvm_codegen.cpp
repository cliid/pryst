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
      currentFunction(nullptr),
      typeMetadata(std::make_unique<pryst::TypeMetadata>(*context, *module)) {

    // Initialize reflection API
    implementReflectionAPI();
    implementTypeHelpers();

    // Add printf declaration to the module
    std::vector<llvm::Type*> printfArgs;
    printfArgs.push_back(llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0));
    llvm::FunctionType* printfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        printfArgs,
        true  // varargs
    );
    llvm::Function::Create(
        printfType,
        llvm::Function::ExternalLinkage,
        "printf",
        module.get()
    );

    // Register print function
    std::vector<llvm::Type*> printArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)
    };
    llvm::FunctionType* printFuncType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*context),
        printArgs,
        false
    );
    llvm::Function* printFunc = llvm::Function::Create(
        printFuncType,
        llvm::Function::ExternalLinkage,
        "print",
        module.get()
    );
    functions["print"] = printFunc;
    functionTypes["print"] = printFuncType;

    // Register string manipulation functions
    std::vector<llvm::Type*> lengthArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)
    };
    llvm::FunctionType* lengthFuncType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        lengthArgs,
        false
    );
    llvm::Function* lengthFunc = llvm::Function::Create(
        lengthFuncType,
        llvm::Function::ExternalLinkage,
        "length",
        module.get()
    );
    functions["length"] = lengthFunc;
    functionTypes["length"] = lengthFuncType;

    std::vector<llvm::Type*> substringArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        llvm::Type::getInt32Ty(*context),
        llvm::Type::getInt32Ty(*context)
    };
    llvm::FunctionType* substringFuncType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        substringArgs,
        false
    );
    llvm::Function* substringFunc = llvm::Function::Create(
        substringFuncType,
        llvm::Function::ExternalLinkage,
        "substring",
        module.get()
    );
    functions["substring"] = substringFunc;
    functionTypes["substring"] = substringFuncType;

    std::vector<llvm::Type*> concatArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)
    };
    llvm::FunctionType* concatFuncType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        concatArgs,
        false
    );
    llvm::Function* concatFunc = llvm::Function::Create(
        concatFuncType,
        llvm::Function::ExternalLinkage,
        "concat",
        module.get()
    );
    functions["concat"] = concatFunc;
    functionTypes["concat"] = concatFuncType;

    // Register math functions
    std::vector<llvm::Type*> sqrtArgs = {
        llvm::Type::getDoubleTy(*context)
    };
    llvm::FunctionType* sqrtFuncType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),
        sqrtArgs,
        false
    );
    llvm::Function* sqrtFunc = llvm::Function::Create(
        sqrtFuncType,
        llvm::Function::ExternalLinkage,
        "sqrt",
        module.get()
    );
    functions["sqrt"] = sqrtFunc;
    functionTypes["sqrt"] = sqrtFuncType;

    std::vector<llvm::Type*> powArgs = {
        llvm::Type::getDoubleTy(*context),
        llvm::Type::getDoubleTy(*context)
    };
    llvm::FunctionType* powFuncType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),
        powArgs,
        false
    );
    llvm::Function* powFunc = llvm::Function::Create(
        powFuncType,
        llvm::Function::ExternalLinkage,
        "pow",
        module.get()
    );
    functions["pow"] = powFunc;
    functionTypes["pow"] = powFuncType;

    std::vector<llvm::Type*> absArgs = {
        llvm::Type::getDoubleTy(*context)
    };
    llvm::FunctionType* absFuncType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),
        absArgs,
        false
    );
    llvm::Function* absFunc = llvm::Function::Create(
        absFuncType,
        llvm::Function::ExternalLinkage,
        "abs",
        module.get()
    );
    functions["abs"] = absFunc;
    functionTypes["abs"] = absFuncType;

    // Register array functions
    std::vector<llvm::Type*> arrayNewArgs = {
        llvm::Type::getInt32Ty(*context)  // initial capacity
    };
    llvm::FunctionType* arrayNewType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        arrayNewArgs,
        false
    );
    llvm::Function* arrayNewFunc = llvm::Function::Create(
        arrayNewType,
        llvm::Function::ExternalLinkage,
        "array_new",
        module.get()
    );
    arrayFunctions["array_new"] = arrayNewFunc;
}

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
antlrcpp::Any LLVMCodegen::visitProgram(PrystParser::ProgramContext* ctx) {
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return antlrcpp::Any();
}

// Declaration: Dispatches to the appropriate declaration type
antlrcpp::Any LLVMCodegen::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    if (ctx->functionDecl()) {
        visit(ctx->functionDecl());
    } else if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->classDeclaration()) {
        visit(ctx->classDeclaration());
    } else {
        visit(ctx->statement());
    }
    return antlrcpp::Any();
}

// Function Declaration: Handles function declarations
antlrcpp::Any LLVMCodegen::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
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

    // Save the current named values
    std::unordered_map<std::string, llvm::AllocaInst*> oldNamedValues = namedValues;

    // Visit the function body declarations
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Restore the named values
    namedValues = oldNamedValues;

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

    return antlrcpp::Any();
}

// Variable Declaration: Handles variable declarations
antlrcpp::Any LLVMCodegen::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    std::string varName = ctx->IDENTIFIER()->getText();
    llvm::Type* varType = getLLVMType(ctx->type()->getText());

    llvm::AllocaInst* alloca = createEntryBlockAlloca(currentFunction, varName, varType);

    if (ctx->expression()) {
        visit(ctx->expression());
        builder->CreateStore(lastValue, alloca);
    } else {
        builder->CreateStore(llvm::Constant::getNullValue(varType), alloca);
    }

    // Add type metadata for reflection
    auto typeInfo = std::make_shared<pryst::TypeInfo>(ctx->type()->getText());
    addTypeInfo(alloca, typeInfo);

    namedValues[varName] = alloca;
    return antlrcpp::Any();
}

// Class Declaration: Handles class declarations
antlrcpp::Any LLVMCodegen::visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) {
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

    // Create class type info for reflection
    auto classInfo = std::make_shared<pryst::ClassTypeInfo>(className);
    if (!immediateBase.empty()) {
        auto baseType = llvm::StructType::getTypeByName(*context, immediateBase);
        if (!baseType) {
            throw std::runtime_error("Base class not found: " + immediateBase);
        }
        auto baseInfo = typeMetadata->getClassTypeInfo(baseType);
        if (!baseInfo) {
            throw std::runtime_error("Base class type info not found: " + immediateBase);
        }
        classInfo = std::make_shared<pryst::ClassTypeInfo>(className, baseInfo);
    }

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

        for (const auto& [memberName, baseIndex] : sortedMembers) {
            orderedTypes.push_back(baseType->getElementType(baseIndex));
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
                std::string memberTypeName = varDecl->type()->getText();
                llvm::Type* memberType = getLLVMType(memberTypeName);
                orderedTypes.push_back(memberType);
                orderedNames.push_back(memberName);
                memberOffsets[memberName] = currentOffset++;

                // Add member to class type info
                auto memberTypeInfo = std::make_shared<pryst::BasicTypeInfo>(memberTypeName);
                classInfo->addField(memberName, memberTypeInfo);
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

    // Add type metadata for reflection
    typeMetadata->addClassTypeInfo(classType, classInfo);

    return antlrcpp::Any();
}

// Class Variable Declaration: Handles class member variables
antlrcpp::Any LLVMCodegen::visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) {
    std::string memberName = ctx->IDENTIFIER()->getText();
    std::string memberTypeName = ctx->type()->getText();
    llvm::Type* memberType = getLLVMType(memberTypeName);

    // Add type metadata for reflection
    auto typeInfo = std::make_shared<pryst::BasicTypeInfo>(memberTypeName);
    if (lastValue) {
        typeMetadata->addTypeInfo(lastValue, typeInfo);
    }

    if (ctx->expression()) {
        visit(ctx->expression());
    }
    return antlrcpp::Any();
}

// Class Function Declaration: Handles class member functions
antlrcpp::Any LLVMCodegen::visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) {
    std::string funcName = ctx->IDENTIFIER()->getText();
    std::string returnTypeName = ctx->type()->getText();
    llvm::Type* returnType = getLLVMType(returnTypeName);

    // Create function type info for reflection
    auto returnTypeInfo = std::make_shared<pryst::BasicTypeInfo>(returnTypeName);
    std::vector<TypeInfoPtr> paramTypeInfos;

    // Add parameter information
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            std::string paramName = param->IDENTIFIER()->getText();
            std::string paramType = param->type()->getText();
            paramTypeInfos.push_back(std::make_shared<pryst::BasicTypeInfo>(paramType));
        }
    }

    auto funcTypeInfo = std::make_shared<pryst::FunctionTypeInfo>(returnTypeInfo, paramTypeInfos);

    // Save the current named values
    std::unordered_map<std::string, llvm::AllocaInst*> oldNamedValues = namedValues;

    // Visit the function body declarations
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Add function type metadata for reflection
    if (currentFunction) {
        typeMetadata->addFunctionTypeInfo(currentFunction, funcTypeInfo);
    }

    // Restore the named values
    namedValues = oldNamedValues;
    return antlrcpp::Any();
}

// Parameter List: Handled in function declaration
antlrcpp::Any LLVMCodegen::visitParamList(PrystParser::ParamListContext* ctx) {
    return antlrcpp::Any();
}

// Parameter: Handled in function declaration
antlrcpp::Any LLVMCodegen::visitParam(PrystParser::ParamContext* ctx) {
    return antlrcpp::Any();
}

// Type: Returns the LLVM type
antlrcpp::Any LLVMCodegen::visitType(PrystParser::TypeContext* ctx) {
    return getLLVMType(ctx->getText());
}

// Expression Statement: Evaluates an expression
antlrcpp::Any LLVMCodegen::visitExprStatement(PrystParser::ExprStatementContext* ctx) {
    visit(ctx->expression());
    return antlrcpp::Any();
}

// If Statement: Handles if statements
antlrcpp::Any LLVMCodegen::visitIfStatement(PrystParser::IfStatementContext* ctx) {
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

    return antlrcpp::Any();
}

// While Statement: Handles while loops
antlrcpp::Any LLVMCodegen::visitWhileStatement(PrystParser::WhileStatementContext* ctx) {
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

    return antlrcpp::Any();
}

// For Statement: Handles for loops
antlrcpp::Any LLVMCodegen::visitForStatement(PrystParser::ForStatementContext* ctx) {
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

    return antlrcpp::Any();
}

// Return Statement: Handles return statements
antlrcpp::Any LLVMCodegen::visitReturnStatement(PrystParser::ReturnStatementContext* ctx) {
    if (ctx->expression()) {
        visit(ctx->expression());
        builder->CreateRet(lastValue);
    } else {
        builder->CreateRetVoid();
    }
    return antlrcpp::Any();
}

// Block: Handles a block of statements
antlrcpp::Any LLVMCodegen::visitBlockStatement(PrystParser::BlockStatementContext* ctx) {
    // Save the current named values
    std::unordered_map<std::string, llvm::AllocaInst*> oldNamedValues = namedValues;

    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    // Restore the named values
    namedValues = oldNamedValues;
    return antlrcpp::Any();
}

// Expression: Handles expressions
antlrcpp::Any LLVMCodegen::visitExpression(PrystParser::ExpressionContext* ctx) {
    if (ctx->assignment()) {
        visit(ctx->assignment());
    } else if (ctx->logicOr()) {
        visit(ctx->logicOr());
    }
    return antlrcpp::Any();
}

// Assignment: Handles both direct variable assignments and member access assignments
antlrcpp::Any LLVMCodegen::visitAssignment(PrystParser::AssignmentContext* ctx) {
    std::cerr << "DEBUG: Starting visitAssignment" << std::endl;
    std::cerr << "DEBUG: Assignment context text: " << ctx->getText() << std::endl;

    llvm::Value* varAddress;

    // Handle primary.IDENTIFIER = expr case
    if (ctx->primary()) {
        std::cerr << "DEBUG: Handling primary.IDENTIFIER assignment" << std::endl;
        visit(ctx->primary());
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

        // Ensure we have a pointer type
        if (!object->getType()->isPointerTy()) {
            throw std::runtime_error("Expected pointer type in member access");
        }

        auto ptrType = llvm::cast<llvm::PointerType>(object->getType());
        auto elementType = ptrType->getContainedType(0);

        // If element type is a pointer (e.g., from function return), load it
        if (elementType->isPointerTy()) {
            object = builder->CreateLoad(elementType, object, "obj.load");
            ptrType = llvm::cast<llvm::PointerType>(object->getType());
            elementType = ptrType->getContainedType(0);
        }

        auto structType = llvm::dyn_cast<llvm::StructType>(elementType);
        if (!structType) {
            throw std::runtime_error("Cannot access member of non-object type");
        }

        // Find member in class hierarchy
        std::string className = structType->getName().str();
        std::string memberName = ctx->IDENTIFIER()->getText();
        std::cerr << "DEBUG: Looking for member '" << memberName << "' in class '" << className << "'" << std::endl;

        auto classIt = memberIndices.find(className);
        if (classIt == memberIndices.end()) {
            throw std::runtime_error("Class not found: " + className);
        }

        bool memberFound = false;
        size_t memberOffset = 0;
        auto memberIt = classIt->second.find(memberName);

        if (memberIt != classIt->second.end()) {
            memberFound = true;
            memberOffset = memberIt->second;
            std::cerr << "DEBUG: Found member directly in class at offset " << memberOffset << std::endl;
        } else {
            // Search base classes
            std::string searchClass = className;
            while (!memberFound) {
                auto inheritIt = classInheritance.find(searchClass);
                if (inheritIt == classInheritance.end()) break;
                searchClass = inheritIt->second;
                auto baseClassIt = memberIndices.find(searchClass);
                if (baseClassIt == memberIndices.end()) {
                    throw std::runtime_error("Base class not found: " + searchClass);
                }
                memberIt = baseClassIt->second.find(memberName);
                if (memberIt != baseClassIt->second.end()) {
                    memberFound = true;
                    memberOffset = memberIt->second;
                    std::cerr << "DEBUG: Found member in base class at offset " << memberOffset << std::endl;
                    break;
                }
            }
        }

        if (!memberFound) {
            throw std::runtime_error("Member '" + memberName + "' not found in class '" + className + "' or its base classes");
        }

        // Create GEP instruction to get member address
        std::vector<llvm::Value*> indices = {
            llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
            llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), memberOffset)
        };
        varAddress = builder->CreateGEP(structType, object, indices, "member.ptr");
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
    return antlrcpp::Any();
}

// Logical OR: Handles logical OR operations
antlrcpp::Any LLVMCodegen::visitLogicOr(PrystParser::LogicOrContext* ctx) {
    if (ctx->logicAnd().size() == 1) {
        visit(ctx->logicAnd(0));
        // Add type metadata for reflection
        auto typeInfo = std::make_shared<pryst::BasicTypeInfo>("bool");
        typeMetadata->addTypeInfo(lastValue, typeInfo);
        return antlrcpp::Any();
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
    // Add type metadata for reflection
    auto typeInfo = std::make_shared<pryst::BasicTypeInfo>("bool");
    typeMetadata->addTypeInfo(lastValue, typeInfo);
    return antlrcpp::Any();
}

// Logical AND: Handles logical AND operations
antlrcpp::Any LLVMCodegen::visitLogicAnd(PrystParser::LogicAndContext* ctx) {
    if (ctx->equality().size() == 1) {
        visit(ctx->equality(0));
        // Add type metadata for reflection
        auto typeInfo = std::make_shared<pryst::BasicTypeInfo>("bool");
        typeMetadata->addTypeInfo(lastValue, typeInfo);
        return antlrcpp::Any();
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
    // Add type metadata for reflection
    auto typeInfo = std::make_shared<pryst::BasicTypeInfo>("bool");
    typeMetadata->addTypeInfo(lastValue, typeInfo);
    return antlrcpp::Any();
}

// Equality: Handles equality comparisons
antlrcpp::Any LLVMCodegen::visitEquality(PrystParser::EqualityContext* ctx) {
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
        // Add type metadata for reflection
        auto typeInfo = std::make_shared<pryst::BasicTypeInfo>("bool");
        typeMetadata->addTypeInfo(lastValue, typeInfo);
        left = lastValue;
    }

    return antlrcpp::Any();
}
// Comparison: Handles comparison operations
antlrcpp::Any LLVMCodegen::visitComparison(PrystParser::ComparisonContext* ctx) {
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
        // Add type metadata for reflection
        auto typeInfo = std::make_shared<pryst::BasicTypeInfo>("bool");
        typeMetadata->addTypeInfo(lastValue, typeInfo);
        left = lastValue;
    }

    return antlrcpp::Any();
}

// Addition/Subtraction: Handles addition and subtraction
antlr4::Any LLVMCodegen::visitAddition(PrystParser::AdditionContext* ctx) {
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
        // Add type metadata for reflection
        auto typeInfo = std::make_shared<pryst::TypeInfo>(left->getType()->isFloatingPointTy() ? "float" : "int");
        addTypeInfo(lastValue, typeInfo);
        left = lastValue;
    }

    return antlr4::Any();
}

// Multiplication/Division: Handles multiplication and division
antlr4::Any LLVMCodegen::visitMultiplication(PrystParser::MultiplicationContext* ctx) {
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
        // Add type metadata for reflection
        auto typeInfo = std::make_shared<pryst::TypeInfo>(left->getType()->isFloatingPointTy() ? "float" : "int");
        addTypeInfo(lastValue, typeInfo);
        left = lastValue;
    }

    return antlr4::Any();
}

// Unary: Handles unary operations
antlr4::Any LLVMCodegen::visitUnary(PrystParser::UnaryContext* ctx) {
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
            // Add type metadata for reflection
            auto typeInfo = std::make_shared<pryst::TypeInfo>(operand->getType()->isFloatingPointTy() ? "float" : "int");
            addTypeInfo(lastValue, typeInfo);
        } else if (ctx->BANG()) {
            lastValue = builder->CreateNot(operand, "nottmp");
            // Add type metadata for reflection
            auto typeInfo = std::make_shared<pryst::TypeInfo>("bool");
            addTypeInfo(lastValue, typeInfo);
        } else if (ctx->INCREMENT()) {
            llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
            lastValue = builder->CreateAdd(operand, one, "inctmp");
            // Add type metadata for reflection
            auto typeInfo = std::make_shared<pryst::TypeInfo>("int");
            addTypeInfo(lastValue, typeInfo);
            // Store the incremented value back if possible
            // This requires access to the variable's address
            throw std::runtime_error("Prefix increment not fully implemented");
        } else if (ctx->DECREMENT()) {
            llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
            lastValue = builder->CreateSub(operand, one, "dectmp");
            // Add type metadata for reflection
            auto typeInfo = std::make_shared<pryst::TypeInfo>("int");
            addTypeInfo(lastValue, typeInfo);
            // Store the decremented value back if possible
            // This requires access to the variable's address
            throw std::runtime_error("Prefix decrement not fully implemented");
        }
    }
    return antlr4::Any();
}

// Postfix: Handles postfix operations
antlr4::Any LLVMCodegen::visitPostfix(PrystParser::PostfixContext* ctx) {
    visit(ctx->primary());
    llvm::Value* operand = lastValue;

    if (ctx->INCREMENT()) {
        llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
        llvm::Value* newValue = builder->CreateAdd(operand, one, "postinctmp");
        // Add type metadata for reflection
        auto typeInfo = std::make_shared<pryst::TypeInfo>("int");
        addTypeInfo(newValue, typeInfo);
        // Store the incremented value back if possible
        // This requires access to the variable's address
        throw std::runtime_error("Postfix increment not fully implemented");
    } else if (ctx->DECREMENT()) {
        llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
        llvm::Value* newValue = builder->CreateSub(operand, one, "postdectmp");
        // Add type metadata for reflection
        auto typeInfo = std::make_shared<pryst::TypeInfo>("int");
        addTypeInfo(newValue, typeInfo);
        // Store the decremented value back if possible
        // This requires access to the variable's address
        throw std::runtime_error("Postfix decrement not fully implemented");
    }

    return antlr4::Any();
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
                // Handle the print function with type-specific format strings
                llvm::Function* printfFunc = module->getFunction("printf");
                if (!printfFunc) {
                    throw std::runtime_error("printf function not found in module");
                }

                if (args.empty()) {
                    throw std::runtime_error("print function requires one argument");
                }

                llvm::Value* arg = args[0];
                llvm::Value* formatStr;

                if (arg->getType()->isIntegerTy()) {
                    formatStr = builder->CreateGlobalString("%d\n", "int_fmt");
                } else if (arg->getType()->isDoubleTy()) {
                    formatStr = builder->CreateGlobalString("%f\n", "float_fmt");
                } else if (arg->getType()->isPointerTy()) {
                    // For now, treat all pointers as string pointers (i8*)
                    // We'll add more pointer type support when implementing arrays
                    formatStr = builder->CreateGlobalString("%s\n", "str_fmt");
                } else {
                    throw std::runtime_error("Unsupported type for print function");
                }

                std::vector<llvm::Value*> printfArgs = {formatStr, arg};
                lastValue = builder->CreateCall(printfFunc, printfArgs, "printtmp");
            } else if (functionName == "sqrt") {
                if (args.empty()) throw std::runtime_error("sqrt function requires one argument");
                llvm::Value* arg = args[0];
                if (arg->getType()->isIntegerTy()) {
                    arg = builder->CreateSIToFP(arg, llvm::Type::getDoubleTy(*context), "inttodouble");
                }
                lastValue = builder->CreateCall(functionCallee, {arg}, "sqrttmp");
            } else if (functionName == "pow") {
                if (args.size() != 2) throw std::runtime_error("pow function requires two arguments");
                llvm::Value* base = args[0];
                llvm::Value* exp = args[1];
                if (base->getType()->isIntegerTy()) {
                    base = builder->CreateSIToFP(base, llvm::Type::getDoubleTy(*context), "inttodouble");
                }
                if (exp->getType()->isIntegerTy()) {
                    exp = builder->CreateSIToFP(exp, llvm::Type::getDoubleTy(*context), "inttodouble");
                }
                lastValue = builder->CreateCall(functionCallee, {base, exp}, "powtmp");
            } else if (functionName == "abs") {
                if (args.empty()) throw std::runtime_error("abs function requires one argument");
                llvm::Value* arg = args[0];
                if (arg->getType()->isIntegerTy()) {
                    llvm::Function* absFunc = llvm::Intrinsic::getOrInsertDeclaration(
                        module.get(), llvm::Intrinsic::abs,
                        {llvm::Type::getInt32Ty(*context)}
                    );
                    llvm::Value* isPoison = llvm::ConstantInt::getFalse(*context);
                    lastValue = builder->CreateCall(absFunc, {arg, isPoison}, "abstmp");
                } else {
                    if (!arg->getType()->isDoubleTy()) {
                        arg = builder->CreateFPExt(arg, llvm::Type::getDoubleTy(*context), "fpext");
                    }
                    llvm::Function* fabsFunc = llvm::Intrinsic::getOrInsertDeclaration(
                        module.get(), llvm::Intrinsic::fabs,
                        {llvm::Type::getDoubleTy(*context)}
                    );
                    lastValue = builder->CreateCall(fabsFunc, {arg}, "abstmp");
                }
            } else if (functionName == "length") {
                if (args.empty()) throw std::runtime_error("length function requires one argument");
                llvm::Value* arg = args[0];
                if (!arg->getType()->isPointerTy()) {
                    throw std::runtime_error("length function requires string argument");
                }
                // Get strlen function
                llvm::Function* strlenFunc = module->getFunction("strlen");
                if (!strlenFunc) {
                    llvm::FunctionType* strlenType = llvm::FunctionType::get(
                        llvm::Type::getInt64Ty(*context),
                        {llvm::Type::getInt8PtrTy(*context)},
                        false
                    );
                    strlenFunc = llvm::Function::Create(
                        strlenType,
                        llvm::Function::ExternalLinkage,
                        "strlen",
                        module.get()
                    );
                }
                lastValue = builder->CreateCall(strlenFunc, {arg}, "strlentmp");
            } else if (functionName == "substring") {
                if (args.size() != 3) throw std::runtime_error("substring function requires three arguments: string, start, length");
                llvm::Value* str = args[0];
                llvm::Value* start = args[1];
                llvm::Value* length = args[2];

                if (!str->getType()->isPointerTy()) {
                    throw std::runtime_error("First argument of substring must be a string");
                }
                if (!start->getType()->isIntegerTy() || !length->getType()->isIntegerTy()) {
                    throw std::runtime_error("Start and length arguments of substring must be integers");
                }

                // Get malloc function
                llvm::Function* mallocFunc = module->getFunction("malloc");
                if (!mallocFunc) {
                    llvm::FunctionType* mallocType = llvm::FunctionType::get(
                        llvm::Type::getInt8PtrTy(*context),
                        {llvm::Type::getInt64Ty(*context)},
                        false
                    );
                    mallocFunc = llvm::Function::Create(
                        mallocType,
                        llvm::Function::ExternalLinkage,
                        "malloc",
                        module.get()
                    );
                }

                // Allocate memory for the substring (length + 1 for null terminator)
                llvm::Value* lengthPlusOne = builder->CreateAdd(
                    builder->CreateIntCast(length, llvm::Type::getInt64Ty(*context), false),
                    llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 1),
                    "substrlength"
                );
                llvm::Value* newStr = builder->CreateCall(mallocFunc, {lengthPlusOne}, "substrmem");

                // Get strncpy function
                llvm::Function* strncpyFunc = module->getFunction("strncpy");
                if (!strncpyFunc) {
                    llvm::FunctionType* strncpyType = llvm::FunctionType::get(
                        llvm::Type::getInt8PtrTy(*context),
                        {llvm::Type::getInt8PtrTy(*context), llvm::Type::getInt8PtrTy(*context), llvm::Type::getInt64Ty(*context)},
                        false
                    );
                    strncpyFunc = llvm::Function::Create(
                        strncpyType,
                        llvm::Function::ExternalLinkage,
                        "strncpy",
                        module.get()
                    );
                }

                // Calculate source pointer (str + start)
                llvm::Value* sourcePtr = builder->CreateGEP(
                    llvm::Type::getInt8Ty(*context),
                    str,
                    start,
                    "sourceptr"
                );

                // Copy the substring
                builder->CreateCall(strncpyFunc, {
                    newStr,
                    sourcePtr,
                    builder->CreateIntCast(length, llvm::Type::getInt64Ty(*context), false)
                }, "strncpytmp");

                // Null terminate the string
                llvm::Value* nullTermPtr = builder->CreateGEP(
                    llvm::Type::getInt8Ty(*context),
                    newStr,
                    length,
                    "nulltermptr"
                );
                builder->CreateStore(
                    llvm::ConstantInt::get(llvm::Type::getInt8Ty(*context), 0),
                    nullTermPtr
                );

                lastValue = newStr;
            } else if (functionName == "concat") {
                if (args.size() != 2) throw std::runtime_error("concat function requires two string arguments");
                llvm::Value* str1 = args[0];
                llvm::Value* str2 = args[1];

                if (!str1->getType()->isPointerTy() || !str2->getType()->isPointerTy()) {
                    throw std::runtime_error("Both arguments of concat must be strings");
                }

                // Get strlen function if not already available
                llvm::Function* strlenFunc = module->getFunction("strlen");
                if (!strlenFunc) {
                    llvm::FunctionType* strlenType = llvm::FunctionType::get(
                        llvm::Type::getInt64Ty(*context),
                        {llvm::Type::getInt8PtrTy(*context)},
                        false
                    );
                    strlenFunc = llvm::Function::Create(
                        strlenType,
                        llvm::Function::ExternalLinkage,
                        "strlen",
                        module.get()
                    );
                }

                // Get lengths of both strings
                llvm::Value* len1 = builder->CreateCall(strlenFunc, {str1}, "len1tmp");
                llvm::Value* len2 = builder->CreateCall(strlenFunc, {str2}, "len2tmp");

                // Calculate total length needed
                llvm::Value* totalLen = builder->CreateAdd(
                    builder->CreateAdd(len1, len2),
                    llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 1),
                    "totallen"
                );

                // Get malloc function if not already available
                llvm::Function* mallocFunc = module->getFunction("malloc");
                if (!mallocFunc) {
                    llvm::FunctionType* mallocType = llvm::FunctionType::get(
                        llvm::Type::getInt8PtrTy(*context),
                        {llvm::Type::getInt64Ty(*context)},
                        false
                    );
                    mallocFunc = llvm::Function::Create(
                        mallocType,
                        llvm::Function::ExternalLinkage,
                        "malloc",
                        module.get()
                    );
                }

                // Allocate memory for concatenated string
                llvm::Value* newStr = builder->CreateCall(mallocFunc, {totalLen}, "concatmem");

                // Get strcpy function
                llvm::Function* strcpyFunc = module->getFunction("strcpy");
                if (!strcpyFunc) {
                    llvm::FunctionType* strcpyType = llvm::FunctionType::get(
                        llvm::Type::getInt8PtrTy(*context),
                        {llvm::Type::getInt8PtrTy(*context), llvm::Type::getInt8PtrTy(*context)},
                        false
                    );
                    strcpyFunc = llvm::Function::Create(
                        strcpyType,
                        llvm::Function::ExternalLinkage,
                        "strcpy",
                        module.get()
                    );
                }

                // Get strcat function
                llvm::Function* strcatFunc = module->getFunction("strcat");
                if (!strcatFunc) {
                    llvm::FunctionType* strcatType = llvm::FunctionType::get(
                        llvm::Type::getInt8PtrTy(*context),
                        {llvm::Type::getInt8PtrTy(*context), llvm::Type::getInt8PtrTy(*context)},
                        false
                    );
                    strcatFunc = llvm::Function::Create(
                        strcatType,
                        llvm::Function::ExternalLinkage,
                        "strcat",
                        module.get()
                    );
                }

                // Copy first string
                builder->CreateCall(strcpyFunc, {newStr, str1}, "strcpytmp");
                // Concatenate second string
                builder->CreateCall(strcatFunc, {newStr, str2}, "strcattmp");

                lastValue = newStr;
            } else {
                lastValue = builder->CreateCall(functionCallee, args, "calltmp");
            }
        } else {
            // Assume callee is a function pointer
            if (!callee->getType()->isPointerTy()) {
                throw std::runtime_error("Called value is not a function or function pointer");
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

        // Initialize members in order of their offsets
        for (const auto& [memberName, offset] : sortedMembers) {
            // Use the class's own struct type to get member type
            llvm::Type* memberType = classStructType->getElementType(offset);

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
        return llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0);
    } else if (typeName.substr(0, 6) == "array<" && typeName.back() == '>') {
        // Handle array types like array<int>, array<float>, etc.
        std::string elementTypeName = typeName.substr(6, typeName.length() - 7);
        llvm::Type* elementType = getLLVMType(elementTypeName);
        return getOrCreateArrayType(elementType);
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

// Array Implementation
llvm::StructType* LLVMCodegen::getOrCreateArrayType(llvm::Type* elementType) {
    // Create type name based on element type
    std::string typeName = "array.";
    if (elementType->isIntegerTy()) {
        typeName += "int";
    } else if (elementType->isDoubleTy()) {
        typeName += "float";
    } else if (elementType->isPointerTy() &&
               elementType->getPointerElementType()->isIntegerTy(8)) {
        typeName += "str";
    } else {
        throw std::runtime_error("Unsupported array element type");
    }

    // Return cached type if it exists
    if (auto* existingType = arrayTypes[typeName]) {
        return existingType;
    }

    // Create new array type: { T*, i32, i32 } representing { buffer, length, capacity }
    std::vector<llvm::Type*> members = {
        llvm::PointerType::get(elementType, 0),  // buffer
        llvm::Type::getInt32Ty(*context),        // length
        llvm::Type::getInt32Ty(*context)         // capacity
    };

    auto* arrayType = llvm::StructType::create(*context, members, typeName);
    arrayTypes[typeName] = arrayType;
    return arrayType;
}

llvm::Value* LLVMCodegen::createArrayAlloc(llvm::Type* elementType, llvm::Value* size) {
    // Get or create array type
    llvm::StructType* arrayType = getOrCreateArrayType(elementType);

    // Allocate array struct
    llvm::Value* arrayStruct = builder->CreateAlloca(arrayType, nullptr, "array");

    // Calculate buffer size (size * sizeof(elementType))
    llvm::Value* elementSize = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context),
        module->getDataLayout().getTypeAllocSize(elementType));
    llvm::Value* bufferSize = builder->CreateMul(
        builder->CreateZExt(size, llvm::Type::getInt64Ty(*context)),
        elementSize,
        "buffersize"
    );

    // Get malloc function
    llvm::Function* mallocFunc = module->getFunction("malloc");
    if (!mallocFunc) {
        llvm::FunctionType* mallocType = llvm::FunctionType::get(
            llvm::Type::getInt8PtrTy(*context),
            {llvm::Type::getInt64Ty(*context)},
            false
        );
        mallocFunc = llvm::Function::Create(
            mallocType,
            llvm::Function::ExternalLinkage,
            "malloc",
            module.get()
        );
    }

    // Allocate buffer
    llvm::Value* buffer = builder->CreateCall(mallocFunc, {bufferSize}, "arraybuffer");
    buffer = builder->CreateBitCast(buffer,
        llvm::PointerType::get(elementType, 0),
        "typedbuffer"
    );

    // Store buffer pointer
    llvm::Value* bufferPtr = builder->CreateStructGEP(arrayType, arrayStruct, 0);
    builder->CreateStore(buffer, bufferPtr);

    // Store length (initially 0)
    llvm::Value* lengthPtr = builder->CreateStructGEP(arrayType, arrayStruct, 1);
    builder->CreateStore(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0), lengthPtr);

    // Store capacity
    llvm::Value* capacityPtr = builder->CreateStructGEP(arrayType, arrayStruct, 2);
    builder->CreateStore(size, capacityPtr);

    return arrayStruct;
}

llvm::Value* LLVMCodegen::getArrayLength(llvm::Value* array) {
    llvm::StructType* arrayType = llvm::cast<llvm::StructType>(
        array->getType()->getPointerElementType()
    );
    llvm::Value* lengthPtr = builder->CreateStructGEP(arrayType, array, 1);
    return builder->CreateLoad(llvm::Type::getInt32Ty(*context), lengthPtr);
}

llvm::Value* LLVMCodegen::getArrayBuffer(llvm::Value* array) {
    llvm::StructType* arrayType = llvm::cast<llvm::StructType>(
        array->getType()->getPointerElementType()
    );
    llvm::Value* bufferPtr = builder->CreateStructGEP(arrayType, array, 0);
    return builder->CreateLoad(
        llvm::PointerType::get(arrayType->getElementType(0)->getPointerElementType(), 0),
        bufferPtr
    );
}

// Helper function to declare malloc
llvm::Function* LLVMCodegen::declareMalloc() {
    // Return existing function if already declared
    if (auto* existingFunc = module->getFunction("malloc")) {
        return existingFunc;
    }

    // Create malloc function type: void* malloc(size_t)
    llvm::FunctionType* mallocType = llvm::FunctionType::get(
        llvm::Type::getInt8PtrTy(*context),
        {llvm::Type::getInt64Ty(*context)},
        false
    );

    // Create and return the function declaration
    return llvm::Function::Create(
        mallocType,
        llvm::Function::ExternalLinkage,
        "malloc",
        module.get()
    );
}

// Array push operation implementation
llvm::Function* LLVMCodegen::declareArrayPush() {
    if (auto* existingFunc = arrayFunctions["array_push"]) return existingFunc;

    // Setup function and blocks
    std::vector<llvm::Type*> pushArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        llvm::Type::getInt32Ty(*context)
    };
    auto* pushFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getVoidTy(*context), pushArgs, false),
        llvm::Function::ExternalLinkage,
        "array_push",
        module.get()
    );

    auto* entry = llvm::BasicBlock::Create(*context, "entry", pushFunc);
    auto* resizeBlock = llvm::BasicBlock::Create(*context, "resize", pushFunc);
    auto* pushBlock = llvm::BasicBlock::Create(*context, "push", pushFunc);

    // Entry block: Cast array and check capacity
    builder->SetInsertPoint(entry);
    auto args = pushFunc->arg_begin();
    llvm::Value* array = builder->CreateBitCast(args++,
        getOrCreateArrayType(llvm::Type::getInt32Ty(*context))->getPointerTo());
    llvm::Value* value = args;

    llvm::Value* length = getArrayLength(array);
    llvm::Value* buffer = getArrayBuffer(array);
    llvm::Value* capacity = builder->CreateLoad(
        llvm::Type::getInt32Ty(*context),
        builder->CreateStructGEP(array->getType()->getPointerElementType(), array, 2)
    );

    builder->CreateCondBr(
        builder->CreateICmpEQ(length, capacity),
        resizeBlock,
        pushBlock
    );

    // Resize block: Double capacity and reallocate
    builder->SetInsertPoint(resizeBlock);
    llvm::Value* newCapacity = builder->CreateMul(
        capacity,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 2)
    );

    llvm::Value* elementSize = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context),
        module->getDataLayout().getTypeAllocSize(llvm::Type::getInt32Ty(*context)));
    llvm::Value* newBuffer = builder->CreateCall(
        declareMalloc(),
        {builder->CreateMul(
            builder->CreateZExt(newCapacity, llvm::Type::getInt64Ty(*context)),
            elementSize
        )}
    );
    newBuffer = builder->CreateBitCast(newBuffer,
        llvm::PointerType::get(llvm::Type::getInt32Ty(*context), 0)
    );

    // Copy old data and update array
    builder->CreateMemCpy(
        newBuffer, llvm::MaybeAlign(4),
        buffer, llvm::MaybeAlign(4),
        builder->CreateMul(
            builder->CreateZExt(length, llvm::Type::getInt64Ty(*context)),
            elementSize
        )
    );

    builder->CreateStore(newBuffer,
        builder->CreateStructGEP(array->getType()->getPointerElementType(), array, 0));
    builder->CreateStore(newCapacity,
        builder->CreateStructGEP(array->getType()->getPointerElementType(), array, 2));

    // Update buffer for push block
    buffer = newBuffer;
    builder->CreateBr(pushBlock);

    // Push block: Add element and increment length
    builder->SetInsertPoint(pushBlock);

    // Get pointer to element position
    llvm::Value* elementPtr = builder->CreateGEP(
        llvm::Type::getInt32Ty(*context),
        buffer,
        length,
        "element.ptr"
    );

    // Store the value
    builder->CreateStore(value, elementPtr);

    // Increment length
    llvm::Value* newLength = builder->CreateAdd(
        length,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 1),
        "new.length"
    );
    builder->CreateStore(newLength,
        builder->CreateStructGEP(array->getType()->getPointerElementType(), array, 1)
    );

    builder->CreateRetVoid();
    arrayFunctions["array_push"] = pushFunc;
    return pushFunc;
}
// Array pop operation implementation
llvm::Function* LLVMCodegen::declareArrayPop() {
    if (auto* existingFunc = arrayFunctions["array_pop"]) return existingFunc;

    // Create function type for array_pop(array*) -> T
    std::vector<llvm::Type*> popArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)  // array pointer
    };
    auto* popType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),  // Return type (we'll create overloads for different types)
        popArgs,
        false
    );

    // Create function
    auto* popFunc = llvm::Function::Create(
        popType,
        llvm::Function::ExternalLinkage,
        "array_pop",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", popFunc);
    auto* emptyCheck = llvm::BasicBlock::Create(*context, "empty_check", popFunc);
    auto* popBlock = llvm::BasicBlock::Create(*context, "pop", popFunc);
    auto* errorBlock = llvm::BasicBlock::Create(*context, "error", popFunc);

    // Entry block: Cast array and get length
    builder->SetInsertPoint(entry);
    auto* array = builder->CreateBitCast(popFunc->arg_begin(),
        getOrCreateArrayType(llvm::Type::getInt32Ty(*context))->getPointerTo());

    // Get array length and buffer
    auto* length = getArrayLength(array);
    auto* buffer = getArrayBuffer(array);

    // Check if array is empty
    auto* isEmpty = builder->CreateICmpEQ(
        length,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0)
    );
    builder->CreateCondBr(isEmpty, errorBlock, popBlock);

    // Error block: Return 0 or throw error
    builder->SetInsertPoint(errorBlock);
    builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0));

    // Pop block: Get last element and decrement length
    builder->SetInsertPoint(popBlock);
    auto* newLength = builder->CreateSub(
        length,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 1),
        "new.length"
    );

    // Get last element
    auto* lastElementPtr = builder->CreateGEP(
        llvm::Type::getInt32Ty(*context),
        buffer,
        newLength,
        "last.element.ptr"
    );
    auto* lastElement = builder->CreateLoad(
        llvm::Type::getInt32Ty(*context),
        lastElementPtr,
        "last.element"
    );

    // Update length
    builder->CreateStore(newLength,
        builder->CreateStructGEP(array->getType()->getPointerElementType(), array, 1)
    );

    // Return the popped value
    builder->CreateRet(lastElement);

    arrayFunctions["array_pop"] = popFunc;
    return popFunc;
}
// Array get operation implementation
llvm::Function* LLVMCodegen::declareArrayGet() {
    if (auto* existingFunc = arrayFunctions["array_get"]) return existingFunc;

    // Create function type for array_get(array*, i32) -> T
    std::vector<llvm::Type*> getArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // array pointer
        llvm::Type::getInt32Ty(*context)                             // index
    };
    auto* getType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),  // Return type (we'll create overloads for different types)
        getArgs,
        false
    );

    // Create function
    auto* getFunc = llvm::Function::Create(
        getType,
        llvm::Function::ExternalLinkage,
        "array_get",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", getFunc);
    auto* validIndex = llvm::BasicBlock::Create(*context, "valid_index", getFunc);
    auto* errorBlock = llvm::BasicBlock::Create(*context, "error", getFunc);

    // Entry block: Cast array and check index bounds
    builder->SetInsertPoint(entry);
    auto args = getFunc->arg_begin();
    auto* array = builder->CreateBitCast(args++,
        getOrCreateArrayType(llvm::Type::getInt32Ty(*context))->getPointerTo());
    auto* index = args;

    // Get array length and buffer
    auto* length = getArrayLength(array);
    auto* buffer = getArrayBuffer(array);

    // Check if index is within bounds
    auto* isValidIndex = builder->CreateICmpULT(
        index,
        length,
        "is_valid_index"
    );
    builder->CreateCondBr(isValidIndex, validIndex, errorBlock);

    // Error block: Return 0 or throw error
    builder->SetInsertPoint(errorBlock);
    builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0));

    // Valid index block: Get element at index
    builder->SetInsertPoint(validIndex);
    auto* elementPtr = builder->CreateGEP(
        llvm::Type::getInt32Ty(*context),
        buffer,
        index,
        "element.ptr"
    );
    auto* element = builder->CreateLoad(
        llvm::Type::getInt32Ty(*context),
        elementPtr,
        "element"
    );

    // Return the element
    builder->CreateRet(element);

    arrayFunctions["array_get"] = getFunc;
    return getFunc;
}
// Array set operation implementation
llvm::Function* LLVMCodegen::declareArraySet() {
    if (auto* existingFunc = arrayFunctions["array_set"]) return existingFunc;

    // Create function type for array_set(array*, i32, T)
    std::vector<llvm::Type*> setArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // array pointer
        llvm::Type::getInt32Ty(*context),                            // index
        llvm::Type::getInt32Ty(*context)                             // value
    };
    auto* setType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*context),  // Return type (void)
        setArgs,
        false
    );

    // Create function
    auto* setFunc = llvm::Function::Create(
        setType,
        llvm::Function::ExternalLinkage,
        "array_set",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", setFunc);
    auto* validIndex = llvm::BasicBlock::Create(*context, "valid_index", setFunc);
    auto* errorBlock = llvm::BasicBlock::Create(*context, "error", setFunc);

    // Entry block: Cast array and check index bounds
    builder->SetInsertPoint(entry);
    auto args = setFunc->arg_begin();
    auto* array = builder->CreateBitCast(args++,
        getOrCreateArrayType(llvm::Type::getInt32Ty(*context))->getPointerTo());
    auto* index = args++;
    auto* value = args;

    // Get array length and buffer
    auto* length = getArrayLength(array);
    auto* buffer = getArrayBuffer(array);

    // Check if index is within bounds
    auto* isValidIndex = builder->CreateICmpULT(
        index,
        length,
        "is_valid_index"
    );
    builder->CreateCondBr(isValidIndex, validIndex, errorBlock);

    // Error block: Return without doing anything
    builder->SetInsertPoint(errorBlock);
    builder->CreateRetVoid();

    // Valid index block: Set element at index
    builder->SetInsertPoint(validIndex);
    auto* elementPtr = builder->CreateGEP(
        llvm::Type::getInt32Ty(*context),
        buffer,
        index,
        "element.ptr"
    );
    builder->CreateStore(value, elementPtr);
    builder->CreateRetVoid();

    arrayFunctions["array_set"] = setFunc;
    return setFunc;
}
// File I/O operations implementation

// Read file operation
llvm::Function* LLVMCodegen::declareFileRead() {
    if (auto* existingFunc = functions["read_file"]) return existingFunc;

    // Create function type for read_file(filename: str) -> str
    std::vector<llvm::Type*> readArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)  // filename (string)
    };
    auto* readType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // Return type (string)
        readArgs,
        false
    );

    // Create function
    auto* readFunc = llvm::Function::Create(
        readType,
        llvm::Function::ExternalLinkage,
        "read_file",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", readFunc);
    auto* readBlock = llvm::BasicBlock::Create(*context, "read", readFunc);
    auto* errorBlock = llvm::BasicBlock::Create(*context, "error", readFunc);

    // Entry block: Open file
    builder->SetInsertPoint(entry);
    auto* filename = readFunc->arg_begin();

    // Declare fopen
    std::vector<llvm::Type*> fopenArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // filename
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)   // mode
    };
    auto* fopenType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // FILE*
        fopenArgs,
        false
    );
    auto* fopen = module->getOrInsertFunction("fopen", fopenType);

    // Open file in read mode
    auto* mode = builder->CreateGlobalStringPtr("r", "read_mode");
    auto* file = builder->CreateCall(fopen, {filename, mode}, "file");

    // Check if file opened successfully
    auto* isFileNull = builder->CreateICmpEQ(
        file,
        llvm::ConstantPointerNull::get(llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)),
        "is_file_null"
    );
    builder->CreateCondBr(isFileNull, errorBlock, readBlock);

    // Error block: Return empty string
    builder->SetInsertPoint(errorBlock);
    auto* emptyStr = builder->CreateGlobalStringPtr("", "empty_str");
    builder->CreateRet(emptyStr);

    // Read block: Read file contents
    builder->SetInsertPoint(readBlock);

    // Get file size using fseek and ftell
    std::vector<llvm::Type*> fseekArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // FILE*
        llvm::Type::getInt64Ty(*context),                            // offset
        llvm::Type::getInt32Ty(*context)                             // whence
    };
    auto* fseekType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        fseekArgs,
        false
    );
    auto* fseek = module->getOrInsertFunction("fseek", fseekType);

    std::vector<llvm::Type*> ftellArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)  // FILE*
    };
    auto* ftellType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        ftellArgs,
        false
    );
    auto* ftell = module->getOrInsertFunction("ftell", ftellType);

    // Seek to end
    builder->CreateCall(fseek, {
        file,
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 0),
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 2)  // SEEK_END
    });

    // Get size
    auto* size = builder->CreateCall(ftell, {file}, "file_size");

    // Seek back to start
    builder->CreateCall(fseek, {
        file,
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 0),
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0)  // SEEK_SET
    });

    // Allocate buffer
    auto* buffer = builder->CreateCall(
        declareMalloc(),
        {builder->CreateAdd(
            size,
            llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 1)  // +1 for null terminator
        )},
        "buffer"
    );

    // Read file
    std::vector<llvm::Type*> freadArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // buffer
        llvm::Type::getInt64Ty(*context),                            // size
        llvm::Type::getInt64Ty(*context),                            // count
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)   // FILE*
    };
    auto* freadType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        freadArgs,
        false
    );
    auto* fread = module->getOrInsertFunction("fread", freadType);

    builder->CreateCall(fread, {
        buffer,
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 1),  // size = 1 byte
        size,                                                          // count = file size
        file
    });

    // Null terminate
    auto* endPtr = builder->CreateGEP(
        llvm::Type::getInt8Ty(*context),
        buffer,
        size,
        "end_ptr"
    );
    builder->CreateStore(
        llvm::ConstantInt::get(llvm::Type::getInt8Ty(*context), 0),
        endPtr
    );

    // Close file
    std::vector<llvm::Type*> fcloseArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)  // FILE*
    };
    auto* fcloseType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        fcloseArgs,
        false
    );
    auto* fclose = module->getOrInsertFunction("fclose", fcloseType);
    builder->CreateCall(fclose, {file});

    // Return buffer
    builder->CreateRet(buffer);

    functions["read_file"] = readFunc;
    return readFunc;
}

// Write file operation
llvm::Function* LLVMCodegen::declareFileWrite() {
    if (auto* existingFunc = functions["write_file"]) return existingFunc;

    // Create function type for write_file(filename: str, content: str) -> bool
    std::vector<llvm::Type*> writeArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // filename
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)   // content
    };
    auto* writeType = llvm::FunctionType::get(
        llvm::Type::getInt1Ty(*context),  // Return type (bool)
        writeArgs,
        false
    );

    // Create function
    auto* writeFunc = llvm::Function::Create(
        writeType,
        llvm::Function::ExternalLinkage,
        "write_file",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", writeFunc);
    auto* writeBlock = llvm::BasicBlock::Create(*context, "write", writeFunc);
    auto* errorBlock = llvm::BasicBlock::Create(*context, "error", writeFunc);

    // Entry block: Open file
    builder->SetInsertPoint(entry);
    auto args = writeFunc->arg_begin();
    auto* filename = args++;
    auto* content = args;

    // Declare fopen
    std::vector<llvm::Type*> fopenArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // filename
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)   // mode
    };
    auto* fopenType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // FILE*
        fopenArgs,
        false
    );
    auto* fopen = module->getOrInsertFunction("fopen", fopenType);

    // Open file in write mode
    auto* mode = builder->CreateGlobalStringPtr("w", "write_mode");
    auto* file = builder->CreateCall(fopen, {filename, mode}, "file");

    // Check if file opened successfully
    auto* isFileNull = builder->CreateICmpEQ(
        file,
        llvm::ConstantPointerNull::get(llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)),
        "is_file_null"
    );
    builder->CreateCondBr(isFileNull, errorBlock, writeBlock);

    // Error block: Return false
    builder->SetInsertPoint(errorBlock);
    builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context), 0));

    // Write block: Write content to file
    builder->SetInsertPoint(writeBlock);

    // Get content length using strlen
    std::vector<llvm::Type*> strlenArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)  // str
    };
    auto* strlenType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        strlenArgs,
        false
    );
    auto* strlen = module->getOrInsertFunction("strlen", strlenType);
    auto* contentLen = builder->CreateCall(strlen, {content}, "content_len");

    // Write content
    std::vector<llvm::Type*> fwriteArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // buffer
        llvm::Type::getInt64Ty(*context),                            // size
        llvm::Type::getInt64Ty(*context),                            // count
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)   // FILE*
    };
    auto* fwriteType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        fwriteArgs,
        false
    );
    auto* fwrite = module->getOrInsertFunction("fwrite", fwriteType);

    auto* bytesWritten = builder->CreateCall(fwrite, {
        content,
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 1),  // size = 1 byte
        contentLen,                                                     // count = content length
        file
    }, "bytes_written");

    // Close file
    std::vector<llvm::Type*> fcloseArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)  // FILE*
    };
    auto* fcloseType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        fcloseArgs,
        false
    );
    auto* fclose = module->getOrInsertFunction("fclose", fcloseType);
    builder->CreateCall(fclose, {file});

    // Return true if bytes written equals content length
    auto* success = builder->CreateICmpEQ(bytesWritten, contentLen, "success");
    builder->CreateRet(success);

    functions["write_file"] = writeFunc;
    return writeFunc;
}

// Append to file operation
llvm::Function* LLVMCodegen::declareFileAppend() {
    if (auto* existingFunc = functions["append_file"]) return existingFunc;

    // Create function type for append_file(filename: str, content: str) -> bool
    std::vector<llvm::Type*> appendArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // filename
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)   // content
    };
    auto* appendType = llvm::FunctionType::get(
        llvm::Type::getInt1Ty(*context),  // Return type (bool)
        appendArgs,
        false
    );

    // Create function
    auto* appendFunc = llvm::Function::Create(
        appendType,
        llvm::Function::ExternalLinkage,
        "append_file",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", appendFunc);
    auto* appendBlock = llvm::BasicBlock::Create(*context, "append", appendFunc);
    auto* errorBlock = llvm::BasicBlock::Create(*context, "error", appendFunc);

    // Entry block: Open file
    builder->SetInsertPoint(entry);
    auto args = appendFunc->arg_begin();
    auto* filename = args++;
    auto* content = args;

    // Declare fopen
    std::vector<llvm::Type*> fopenArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // filename
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)   // mode
    };
    auto* fopenType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // FILE*
        fopenArgs,
        false
    );
    auto* fopen = module->getOrInsertFunction("fopen", fopenType);

    // Open file in append mode
    auto* mode = builder->CreateGlobalStringPtr("a", "append_mode");
    auto* file = builder->CreateCall(fopen, {filename, mode}, "file");

    // Check if file opened successfully
    auto* isFileNull = builder->CreateICmpEQ(
        file,
        llvm::ConstantPointerNull::get(llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)),
        "is_file_null"
    );
    builder->CreateCondBr(isFileNull, errorBlock, appendBlock);

    // Error block: Return false
    builder->SetInsertPoint(errorBlock);
    builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context), 0));

    // Append block: Append content to file
    builder->SetInsertPoint(appendBlock);

    // Get content length using strlen
    std::vector<llvm::Type*> strlenArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)  // str
    };
    auto* strlenType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        strlenArgs,
        false
    );
    auto* strlen = module->getOrInsertFunction("strlen", strlenType);
    auto* contentLen = builder->CreateCall(strlen, {content}, "content_len");

    // Write content
    std::vector<llvm::Type*> fwriteArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),  // buffer
        llvm::Type::getInt64Ty(*context),                            // size
        llvm::Type::getInt64Ty(*context),                            // count
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)   // FILE*
    };
    auto* fwriteType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        fwriteArgs,
        false
    );
    auto* fwrite = module->getOrInsertFunction("fwrite", fwriteType);

    auto* bytesWritten = builder->CreateCall(fwrite, {
        content,
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 1),  // size = 1 byte
        contentLen,                                                     // count = content length
        file
    }, "bytes_written");

    // Close file
    std::vector<llvm::Type*> fcloseArgs = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)  // FILE*
    };
    auto* fcloseType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        fcloseArgs,
        false
    );
    auto* fclose = module->getOrInsertFunction("fclose", fcloseType);
    builder->CreateCall(fclose, {file});

    // Return true if bytes written equals content length
    auto* success = builder->CreateICmpEQ(bytesWritten, contentLen, "success");
    builder->CreateRet(success);

    functions["append_file"] = appendFunc;
    return appendFunc;
}
// Type conversion operations implementation

// toString operation
llvm::Function* LLVMCodegen::declareToString() {
    if (auto* existingFunc = functions["toString"]) return existingFunc;

    // Create function type for toString(value: any) -> str
    std::vector<llvm::Type*> toStrArgs = {
        llvm::Type::getInt8PtrTy(*context)  // Generic pointer type for any value
    };
    auto* toStrType = llvm::FunctionType::get(
        llvm::Type::getInt8PtrTy(*context),  // Return type (string)
        toStrArgs,
        false
    );

    // Create function
    auto* toStrFunc = llvm::Function::Create(
        toStrType,
        llvm::Function::ExternalLinkage,
        "toString",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", toStrFunc);
    auto* intCase = llvm::BasicBlock::Create(*context, "int_case", toStrFunc);
    auto* floatCase = llvm::BasicBlock::Create(*context, "float_case", toStrFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context, "bool_case", toStrFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context, "default_case", toStrFunc);

    // Entry block: Check value type
    builder->SetInsertPoint(entry);
    auto* value = toStrFunc->arg_begin();

    // Allocate buffer for result
    auto* buffer = builder->CreateCall(
        declareMalloc(),
        {llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 64)},  // 64 bytes should be enough
        "buffer"
    );

    // Declare sprintf
    std::vector<llvm::Type*> sprintfArgs = {
        llvm::Type::getInt8PtrTy(*context),  // buffer
        llvm::Type::getInt8PtrTy(*context),  // format
        llvm::Type::getInt8PtrTy(*context)   // value
    };
    auto* sprintfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        sprintfArgs,
        true  // varargs
    );
    auto* sprintf = module->getOrInsertFunction("sprintf", sprintfType);

    // Convert based on type
    auto* valueType = value->getType();
    if (valueType == llvm::Type::getInt32Ty(*context)) {
        builder->CreateBr(intCase);
    } else if (valueType == llvm::Type::getDoubleTy(*context)) {
        builder->CreateBr(floatCase);
    } else if (valueType == llvm::Type::getInt1Ty(*context)) {
        builder->CreateBr(boolCase);
    } else {
        builder->CreateBr(defaultCase);
    }

    // Int case: Convert int to string
    builder->SetInsertPoint(intCase);
    auto* intFormat = builder->CreateGlobalStringPtr("%d", "int_format");
    builder->CreateCall(sprintf, {buffer, intFormat, value});
    builder->CreateRet(buffer);

    // Float case: Convert float to string
    builder->SetInsertPoint(floatCase);
    auto* floatFormat = builder->CreateGlobalStringPtr("%.6f", "float_format");
    builder->CreateCall(sprintf, {buffer, floatFormat, value});
    builder->CreateRet(buffer);

    // Bool case: Convert bool to string
    builder->SetInsertPoint(boolCase);
    auto* trueStr = builder->CreateGlobalStringPtr("true", "true_str");
    auto* falseStr = builder->CreateGlobalStringPtr("false", "false_str");
    auto* boolStr = builder->CreateSelect(value, trueStr, falseStr, "bool_str");
    builder->CreateRet(boolStr);

    // Default case: Return empty string
    builder->SetInsertPoint(defaultCase);
    auto* emptyStr = builder->CreateGlobalStringPtr("", "empty_str");
    builder->CreateRet(emptyStr);

    functions["toString"] = toStrFunc;
    return toStrFunc;
}

// toInt operation
llvm::Function* LLVMCodegen::declareToInt() {
    if (auto* existingFunc = functions["toInt"]) return existingFunc;

    // Create function type for toInt(value: any) -> int
    std::vector<llvm::Type*> toIntArgs = {
        llvm::Type::getInt8PtrTy(*context)  // Generic pointer type for any value
    };
    auto* toIntType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),  // Return type (int)
        toIntArgs,
        false
    );

    // Create function
    auto* toIntFunc = llvm::Function::Create(
        toIntType,
        llvm::Function::ExternalLinkage,
        "toInt",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", toIntFunc);
    auto* strCase = llvm::BasicBlock::Create(*context, "str_case", toIntFunc);
    auto* floatCase = llvm::BasicBlock::Create(*context, "float_case", toIntFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context, "bool_case", toIntFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context, "default_case", toIntFunc);

    // Entry block: Check value type
    builder->SetInsertPoint(entry);
    auto* value = toIntFunc->arg_begin();

    // Convert based on type
    auto* valueType = value->getType();
    if (valueType == llvm::Type::getInt8PtrTy(*context)) {
        builder->CreateBr(strCase);
    } else if (valueType == llvm::Type::getDoubleTy(*context)) {
        builder->CreateBr(floatCase);
    } else if (valueType == llvm::Type::getInt1Ty(*context)) {
        builder->CreateBr(boolCase);
    } else {
        builder->CreateBr(defaultCase);
    }

    // String case: Convert string to int using atoi
    builder->SetInsertPoint(strCase);
    std::vector<llvm::Type*> atoiArgs = {
        llvm::Type::getInt8PtrTy(*context)  // str
    };
    auto* atoiType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        atoiArgs,
        false
    );
    auto* atoi = module->getOrInsertFunction("atoi", atoiType);
    auto* intVal = builder->CreateCall(atoi, {value}, "int_val");
    builder->CreateRet(intVal);

    // Float case: Convert float to int by truncation
    builder->SetInsertPoint(floatCase);
    auto* intVal2 = builder->CreateFPToSI(value, llvm::Type::getInt32Ty(*context), "int_val");
    builder->CreateRet(intVal2);

    // Bool case: Convert bool to int (true = 1, false = 0)
    builder->SetInsertPoint(boolCase);
    auto* intVal3 = builder->CreateZExt(value, llvm::Type::getInt32Ty(*context), "int_val");
    builder->CreateRet(intVal3);

    // Default case: Return 0
    builder->SetInsertPoint(defaultCase);
    builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0));

    functions["toInt"] = toIntFunc;
    return toIntFunc;
}

// toFloat operation
llvm::Function* LLVMCodegen::declareToFloat() {
    if (auto* existingFunc = functions["toFloat"]) return existingFunc;

    // Create function type for toFloat(value: any) -> float
    std::vector<llvm::Type*> toFloatArgs = {
        llvm::Type::getInt8PtrTy(*context)  // Generic pointer type for any value
    };
    auto* toFloatType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),  // Return type (float)
        toFloatArgs,
        false
    );

    // Create function
    auto* toFloatFunc = llvm::Function::Create(
        toFloatType,
        llvm::Function::ExternalLinkage,
        "toFloat",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", toFloatFunc);
    auto* strCase = llvm::BasicBlock::Create(*context, "str_case", toFloatFunc);
    auto* intCase = llvm::BasicBlock::Create(*context, "int_case", toFloatFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context, "bool_case", toFloatFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context, "default_case", toFloatFunc);

    // Entry block: Check value type
    builder->SetInsertPoint(entry);
    auto* value = toFloatFunc->arg_begin();

    // Convert based on type
    auto* valueType = value->getType();
    if (valueType == llvm::Type::getInt8PtrTy(*context)) {
        builder->CreateBr(strCase);
    } else if (valueType == llvm::Type::getInt32Ty(*context)) {
        builder->CreateBr(intCase);
    } else if (valueType == llvm::Type::getInt1Ty(*context)) {
        builder->CreateBr(boolCase);
    } else {
        builder->CreateBr(defaultCase);
    }

    // String case: Convert string to float using atof
    builder->SetInsertPoint(strCase);
    std::vector<llvm::Type*> atofArgs = {
        llvm::Type::getInt8PtrTy(*context)  // str
    };
    auto* atofType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),
        atofArgs,
        false
    );
    auto* atof = module->getOrInsertFunction("atof", atofType);
    auto* floatVal = builder->CreateCall(atof, {value}, "float_val");
    builder->CreateRet(floatVal);

    // Int case: Convert int to float
    builder->SetInsertPoint(intCase);
    auto* floatVal2 = builder->CreateSIToFP(value, llvm::Type::getDoubleTy(*context), "float_val");
    builder->CreateRet(floatVal2);


    // Bool case: Convert bool to float (true = 1.0, false = 0.0)
    builder->SetInsertPoint(boolCase);
    auto* intVal = builder->CreateZExt(value, llvm::Type::getInt32Ty(*context), "int_val");
    auto* floatVal3 = builder->CreateSIToFP(intVal, llvm::Type::getDoubleTy(*context), "float_val");
    builder->CreateRet(floatVal3);

    // Default case: Return 0.0
    builder->SetInsertPoint(defaultCase);
    builder->CreateRet(llvm::ConstantFP::get(llvm::Type::getDoubleTy(*context), 0.0));

    functions["toFloat"] = toFloatFunc;
    return toFloatFunc;
}
