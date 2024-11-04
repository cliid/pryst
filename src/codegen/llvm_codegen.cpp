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
    : typeRegistry(TypeRegistry::getInstance()) {

    std::cerr << "DEBUG: Starting LLVMCodegen constructor" << std::endl;

    try {
        std::cerr << "DEBUG: Creating LLVMContext" << std::endl;
        context = std::make_unique<llvm::LLVMContext>();

        std::cerr << "DEBUG: Creating Module" << std::endl;
        module = std::make_unique<llvm::Module>("pryst", *context);

        std::cerr << "DEBUG: Creating TypeMetadata" << std::endl;
        typeMetadata = std::make_shared<TypeMetadata>(*context, *module);

        std::cerr << "DEBUG: Creating IRBuilder" << std::endl;
        builder = std::make_unique<llvm::IRBuilder<>>(*context);

        lastValue = nullptr;
        currentFunction = nullptr;
        printFunc = nullptr;

        std::cerr << "DEBUG: Initializing built-in functions" << std::endl;
        // Initialize built-in functions
        functions["printf"] = declarePrintf();
        functions["malloc"] = declareMalloc();
        functions["strlen"] = declareStrlen();
        functions["strcpy"] = declareStrcpy();
        functions["strcat"] = declareStrcat();
        functions["memcpy"] = declareMemcpy();

        std::cerr << "DEBUG: Declaring print functions" << std::endl;
        // Declare print functions for different types
        declarePrintFunctions();

        std::cerr << "DEBUG: Setting up default print function" << std::endl;
        // Set up the default print function for integers (most common case)
        auto it = functions.find("print.int");
        if (it != functions.end()) {
            printFunc = it->second;
            std::cerr << "DEBUG: Default print function initialized" << std::endl;
        } else {
            std::cerr << "ERROR: Failed to initialize default print function" << std::endl;
            throw std::runtime_error("Failed to initialize default print function");
        }

        std::cerr << "DEBUG: LLVMCodegen constructor completed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: Exception in LLVMCodegen constructor: " << e.what() << std::endl;
        throw;
    }
}

// Declare print functions for different types
void LLVMCodegen::declarePrintFunctions() {
    std::cerr << "DEBUG: Declaring print functions" << std::endl;

    // Print int function
    auto intType = llvm::Type::getInt32Ty(*context);
    std::vector<llvm::Type*> intPrintArgs = {intType};
    auto intPrintType = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), intPrintArgs, false);
    auto printIntFunc = llvm::Function::Create(intPrintType, llvm::Function::ExternalLinkage, "print.int", module.get());
    functions["print.int"] = printIntFunc;

    // Create print.int implementation
    auto printIntBlock = llvm::BasicBlock::Create(*context, "entry", printIntFunc);
    auto savedInsertPoint = builder->GetInsertBlock();
    builder->SetInsertPoint(printIntBlock);
    auto formatStr = builder->CreateGlobalString("%d\n", "int_format");
    auto formatPtr = builder->CreateBitCast(formatStr, llvm::Type::getInt8Ty(*context)->getPointerTo());
    std::vector<llvm::Value*> printfArgs;
    printfArgs.push_back(formatPtr);
    printfArgs.push_back(&*printIntFunc->arg_begin());
    builder->CreateCall(functions["printf"], printfArgs);
    builder->CreateRetVoid();
    builder->SetInsertPoint(savedInsertPoint);

    // Print float function
    auto floatType = llvm::Type::getDoubleTy(*context);
    std::vector<llvm::Type*> floatPrintArgs = {floatType};
    auto floatPrintType = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), floatPrintArgs, false);
    auto printFloatFunc = llvm::Function::Create(floatPrintType, llvm::Function::ExternalLinkage, "print.float", module.get());
    functions["print.float"] = printFloatFunc;

    // Create print.float implementation
    auto printFloatBlock = llvm::BasicBlock::Create(*context, "entry", printFloatFunc);
    savedInsertPoint = builder->GetInsertBlock();
    builder->SetInsertPoint(printFloatBlock);
    formatStr = builder->CreateGlobalString("%f\n", "float_format");
    formatPtr = builder->CreateBitCast(formatStr, llvm::Type::getInt8Ty(*context)->getPointerTo());
    printfArgs.clear();
    printfArgs.push_back(formatPtr);
    printfArgs.push_back(&*printFloatFunc->arg_begin());
    builder->CreateCall(functions["printf"], printfArgs);
    builder->CreateRetVoid();
    builder->SetInsertPoint(savedInsertPoint);

    // Print bool function
    auto boolType = llvm::Type::getInt1Ty(*context);
    std::vector<llvm::Type*> boolPrintArgs = {boolType};
    auto boolPrintType = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), boolPrintArgs, false);
    auto printBoolFunc = llvm::Function::Create(boolPrintType, llvm::Function::ExternalLinkage, "print.bool", module.get());
    functions["print.bool"] = printBoolFunc;

    // Create print.bool implementation
    auto printBoolBlock = llvm::BasicBlock::Create(*context, "entry", printBoolFunc);
    savedInsertPoint = builder->GetInsertBlock();
    builder->SetInsertPoint(printBoolBlock);
    auto trueStr = builder->CreateGlobalString("true\n", "true_str");
    auto falseStr = builder->CreateGlobalString("false\n", "false_str");
    auto truePtrCast = builder->CreateBitCast(trueStr, llvm::Type::getInt8Ty(*context)->getPointerTo());
    auto falsePtrCast = builder->CreateBitCast(falseStr, llvm::Type::getInt8Ty(*context)->getPointerTo());
    auto condition = &*printBoolFunc->arg_begin();
    auto selectedStr = builder->CreateSelect(condition, truePtrCast, falsePtrCast);
    printfArgs.clear();
    printfArgs.push_back(selectedStr);
    builder->CreateCall(functions["printf"], printfArgs);
    builder->CreateRetVoid();
    builder->SetInsertPoint(savedInsertPoint);

    // Print string function
    auto strType = typeRegistry.getStrType();
    auto llvmStrType = LLVMTypeRegistry::getInstance().getLLVMType(strType, module->getContext());
    std::vector<llvm::Type*> strPrintArgs = {llvmStrType};
    auto strPrintType = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), strPrintArgs, false);
    auto printStrFunc = llvm::Function::Create(strPrintType, llvm::Function::ExternalLinkage, "print.str", module.get());
    functions["print.str"] = printStrFunc;

    // Create print.str implementation
    auto printStrBlock = llvm::BasicBlock::Create(*context, "entry", printStrFunc);
    savedInsertPoint = builder->GetInsertBlock();
    builder->SetInsertPoint(printStrBlock);
    formatStr = builder->CreateGlobalString("%s\n", "str_format");
    formatPtr = builder->CreateBitCast(formatStr, llvm::Type::getInt8Ty(*context)->getPointerTo());
    printfArgs.clear();
    printfArgs.push_back(formatPtr);
    printfArgs.push_back(&*printStrFunc->arg_begin());
    builder->CreateCall(functions["printf"], printfArgs);
    builder->CreateRetVoid();
    builder->SetInsertPoint(savedInsertPoint);

    std::cerr << "DEBUG: Print functions declared and implemented successfully" << std::endl;
}

std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(PrystParser::ProgramContext* programCtx) {
    try {
        std::cerr << "DEBUG: Starting module generation" << std::endl;

        // Verify type system state
        std::cerr << "DEBUG: Verifying TypeRegistry state" << std::endl;
        if (!typeRegistry.getIntType() || !typeRegistry.getFloatType() || !typeRegistry.getStrType()) {
            throw std::runtime_error("TypeRegistry not properly initialized");
        }

        // Verify LLVMTypeRegistry
        std::cerr << "DEBUG: Verifying LLVMTypeRegistry state" << std::endl;
        auto& llvmTypeRegistry = LLVMTypeRegistry::getInstance();
        if (!llvmTypeRegistry.getLLVMType(typeRegistry.getIntType(), *context)) {
            throw std::runtime_error("LLVMTypeRegistry not properly initialized");
        }

        if (!programCtx) {
            throw std::runtime_error("Null program context");
        }

        // Update TypeMetadata with current context and module
        std::cerr << "DEBUG: Updating TypeMetadata with current context and module" << std::endl;
        typeMetadata->setContext(*context);
        typeMetadata->setModule(*module);

        std::cerr << "DEBUG: Creating main function" << std::endl;
        currentFunction = createMainFunction();
        if (!currentFunction) {
            throw std::runtime_error("Failed to create main function");
        }

        std::cerr << "DEBUG: Verifying function declarations" << std::endl;
        if (functions.empty() || !functions["print.int"]) {
            throw std::runtime_error("Print functions not properly initialized");
        }

        std::cerr << "DEBUG: Visiting program" << std::endl;
        visitProgram(programCtx);

        // Dump IR before verification
        std::cerr << "\n=== Pre-verification LLVM IR ===\n" << std::endl;
        std::string preVerifyIR;
        llvm::raw_string_ostream preVerifyStream(preVerifyIR);
        module->print(preVerifyStream, nullptr);
        std::cerr << preVerifyStream.str() << "\n=== End Pre-verification IR ===\n" << std::endl;

        std::cerr << "DEBUG: Verifying module" << std::endl;
        if (llvm::verifyModule(*module, &llvm::errs())) {
            throw std::runtime_error("Generated LLVM IR is invalid");
        }

        std::cerr << "\n=== Final Generated LLVM IR ===\n" << std::endl;
        std::string ir;
        llvm::raw_string_ostream irStream(ir);
        module->print(irStream, nullptr);
        std::cerr << irStream.str() << "\n=== End LLVM IR ===\n" << std::endl;

        std::cerr << "DEBUG: Module generation complete" << std::endl;
        return std::move(module);
    } catch (const std::exception& e) {
        std::cerr << "ERROR: Exception in generateModule: " << e.what() << std::endl;
        throw;
    }
}

llvm::Function* LLVMCodegen::createMainFunction() {
    std::cerr << "DEBUG: Creating main function" << std::endl;
    llvm::FunctionType* mainFuncType = llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), false);
    llvm::Function* mainFunc = llvm::Function::Create(mainFuncType, llvm::Function::ExternalLinkage, "main", module.get());

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", mainFunc);
    builder->SetInsertPoint(entryBlock);

    std::cerr << "DEBUG: Main function created successfully" << std::endl;
    return mainFunc;
}

// Program: Handles the entire program
std::any LLVMCodegen::visitProgram(PrystParser::ProgramContext* ctx) {
    std::cerr << "DEBUG: Starting program visit" << std::endl;

    // Create a new scope for the program
    pushScope();
    std::cerr << "DEBUG: Pushed global scope" << std::endl;

    try {
        // Visit all declarations in the program
        for (auto decl : ctx->declaration()) {
            std::cerr << "DEBUG: Visiting declaration: " << decl->getText() << std::endl;

            if (auto varDecl = dynamic_cast<PrystParser::VariableDeclContext*>(decl)) {
                std::cerr << "DEBUG: Processing variable declaration" << std::endl;
                visitVariableDecl(varDecl);  // Call visitVariableDecl directly
                std::cerr << "DEBUG: Variable declaration processed" << std::endl;
            } else if (auto stmt = dynamic_cast<PrystParser::StatementContext*>(decl)) {
                std::cerr << "DEBUG: Processing statement" << std::endl;
                if (auto exprStmt = dynamic_cast<PrystParser::ExprStatementContext*>(stmt)) {
                    std::cerr << "DEBUG: Processing expression statement" << std::endl;
                    visitExprStatement(exprStmt);
                    std::cerr << "DEBUG: Expression statement processed" << std::endl;
                } else {
                    std::cerr << "DEBUG: Processing other statement type" << std::endl;
                    visit(stmt);  // Handle other statement types
                    std::cerr << "DEBUG: Statement processed" << std::endl;
                }
            } else if (auto funcDecl = dynamic_cast<PrystParser::FunctionDeclContext*>(decl)) {
                std::cerr << "DEBUG: Processing function declaration" << std::endl;
                visit(funcDecl);
                std::cerr << "DEBUG: Function declaration processed" << std::endl;
            }

            std::cerr << "DEBUG: Declaration processed successfully" << std::endl;
        }

        // Create return 0 only if we're in the main function
        if (currentFunction && currentFunction->getName() == "main") {
            builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0));
            std::cerr << "DEBUG: Created return statement for main" << std::endl;
        }

        // Pop the program scope
        popScope();
        std::cerr << "DEBUG: Popped global scope" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "ERROR: Exception during program visit: " << e.what() << std::endl;
        throw;
    }

    return nullptr;
}

// Declaration: Dispatches to the appropriate declaration type
std::any LLVMCodegen::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    std::cerr << "DEBUG: Visiting declaration" << std::endl;
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
    std::cerr << "DEBUG: Visiting function declaration" << std::endl;
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
    std::cerr << "DEBUG: Visiting named function: " << funcName << std::endl;

    llvm::Type* returnType = getLLVMType(ctx->type()->getText());

    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;
    std::vector<TypeInfoPtr> paramTypeInfos;

    // Get return type info from registry
    auto& registry = TypeRegistry::getInstance();
    auto returnTypeInfo = registry.lookupType(ctx->type()->getText());
    if (!returnTypeInfo) {
        throw std::runtime_error("Unknown return type: " + ctx->type()->getText());
    }

    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            auto paramType = getLLVMType(param->type()->getText());
            auto paramTypeInfo = registry.lookupType(param->type()->getText());
            if (!paramTypeInfo) {
                throw std::runtime_error("Unknown parameter type: " + param->type()->getText());
            }
            paramTypes.push_back(paramType);
            paramNames.push_back(param->IDENTIFIER()->getText());
            paramTypeInfos.push_back(paramTypeInfo);
        }
    }

    llvm::FunctionType* funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    llvm::Function* function = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, funcName, module.get());

    // Create LLVM-specific function type info
    auto functionTypeInfo = std::make_shared<LLVMFunctionTypeInfo>(
        funcName, returnTypeInfo, paramTypeInfos, funcType);
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

    std::cerr << "DEBUG: Named function visit complete: " << funcName << std::endl;
    return nullptr;
}

// Variable Declaration: Handles variable declarations
std::any LLVMCodegen::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string typeName = ctx->type()->getText();
    std::cerr << "DEBUG: Creating variable " << varName << " of type " << typeName << std::endl;

    // Get type information from registry
    auto typeInfo = typeRegistry.lookupType(typeName);
    if (!typeInfo) {
        throw std::runtime_error("Unknown type: " + typeName);
    }

    // Get LLVM type through LLVMTypeRegistry
    auto& llvmTypeRegistry = LLVMTypeRegistry::getInstance();
    llvm::Type* varType = llvmTypeRegistry.getLLVMType(typeInfo, *context);
    if (!varType) {
        throw std::runtime_error("Failed to get LLVM type for: " + typeName);
    }

    std::cerr << "DEBUG: Creating alloca for variable" << std::endl;
    llvm::AllocaInst* alloca = createEntryBlockAlloca(currentFunction, varName, varType);

    // Register variable type information
    typeMetadata->addTypeInfo(alloca, typeInfo);

    if (ctx->expression()) {
        std::cerr << "DEBUG: Initializing variable with expression" << std::endl;
        visit(ctx->expression());
        if (!lastValue) {
            throw std::runtime_error("Expression evaluation failed for variable: " + varName);
        }
        builder->CreateStore(lastValue, alloca);
    } else {
        std::cerr << "DEBUG: Initializing variable with null value" << std::endl;
        builder->CreateStore(llvm::Constant::getNullValue(varType), alloca);
    }

    namedValues[varName] = alloca;
    std::cerr << "DEBUG: Variable declaration complete: " << varName << std::endl;
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
            size_t memberIndex = baseClassInfo->getMemberIndex(memberName);
            auto memberTypeInfo = baseClassInfo->getMemberTypeInfo(memberName);
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
    std::cerr << "DEBUG: Starting expression statement visit" << std::endl;
    std::cerr << "DEBUG: Expression text: " << ctx->expression()->getText() << std::endl;
    visit(ctx->expression());
    std::cerr << "DEBUG: Expression statement visit complete" << std::endl;
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
        if (!typeInfo || typeInfo->getKind() != TypeInfo::Kind::Class) {
            throw std::runtime_error("Expected class type in member access");
        }

        // Get class type info
        auto classInfo = std::dynamic_pointer_cast<LLVMClassTypeInfo>(typeInfo);
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
            if (!typeInfo || typeInfo->getKind() != TypeInfo::Kind::Class) {
                throw std::runtime_error("Expected class type in member access");
            }
            auto classInfo = std::dynamic_pointer_cast<LLVMClassTypeInfo>(typeInfo);
            if (!classInfo) {
                throw std::runtime_error("Failed to get LLVM class type info");
            }
            size_t memberOffset = classInfo->getMemberIndex(memberName);
            if (memberOffset == static_cast<size_t>(-1)) {
                throw std::runtime_error("Member '" + memberName + "' not found");
            }
            std::vector<llvm::Value*> indices = {
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), memberOffset)
            };
            operand = builder->CreateGEP(classInfo->getStructType(), operand, indices, "member.ptr");
            auto memberType = classInfo->getFieldType(memberName);
            if (!memberType) {
                throw std::runtime_error("Failed to get member type for: " + memberName);
            }
            operand = builder->CreateLoad(classInfo->getStructType(), operand, "member");
        }
    }

    // Handle increment/decrement
    if (!ctx->INCREMENT().empty()) {
        llvm::Value* one = llvm::ConstantInt::get(operand->getType(), 1);
        llvm::Value* newValue = builder->CreateAdd(operand, one, "postinctmp");
        // Store the incremented value back if possible
        if (auto* loadInst = llvm::dyn_cast<llvm::LoadInst>(operand)) {
            builder->CreateStore(newValue, loadInst->getPointerOperand());
        }
        lastValue = operand; // Return original value for postfix increment
    } else if (!ctx->DECREMENT().empty()) {
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
    auto* primary = ctx->primary();
    visit(primary);
    llvm::Value* callee = lastValue;

    // Handle function call in primary if it exists
    if (primary->IDENTIFIER() && primary->LPAREN()) {
        std::vector<llvm::Value*> args;
        if (primary->arguments()) {
            for (auto expr : primary->arguments()->expression()) {
                visit(expr);
                args.push_back(lastValue);
            }
        }

        // Handle built-in functions
        if (llvm::Function* functionCallee = llvm::dyn_cast<llvm::Function>(callee)) {
            std::string functionName = functionCallee->getName().str();

            if (functionName == "print") {
                std::cerr << "DEBUG: Handling print function call" << std::endl;
                // Get the type of the first argument
                if (!args.empty()) {
                    llvm::Value* arg = args[0];
                    if (!arg) {
                        throw std::runtime_error("Null argument passed to print function");
                    }

                    std::cerr << "DEBUG: Getting type info for print argument" << std::endl;
                    // Get type information from registry
                    auto typeInfo = typeMetadata->getTypeInfo(arg);
                    if (!typeInfo) {
                        throw std::runtime_error("Failed to get type info for print argument");
                    }

                    std::cerr << "DEBUG: Determining print function type" << std::endl;
                    // Determine print function based on type info
                    std::string printFuncName;
                    if (typeInfo == typeRegistry.getIntType()) {
                        printFuncName = "print.int";
                    } else if (typeInfo == typeRegistry.getFloatType()) {
                        printFuncName = "print.float";
                    } else if (typeInfo == typeRegistry.getBoolType()) {
                        printFuncName = "print.bool";
                    } else if (typeInfo == typeRegistry.getStrType()) {
                        printFuncName = "print.str";
                    }

                    if (printFuncName.empty()) {
                        throw std::runtime_error("Unsupported type for print function");
                    }

                    std::cerr << "DEBUG: Looking up print function: " << printFuncName << std::endl;
                    // Get or declare the print function
                    auto it = functions.find(printFuncName);
                    if (it != functions.end()) {
                        printFunc = it->second;
                    }
                    if (!printFunc) {
                        throw std::runtime_error("Print function not found: " + printFuncName);
                    }

                    std::cerr << "DEBUG: Creating function call" << std::endl;
                    std::vector<llvm::Value*> printArgs = {arg};
                    lastValue = builder->CreateCall(printFunc, printArgs, "printtmp");
                    std::cerr << "DEBUG: Print function call created successfully" << std::endl;
                } else {
                    throw std::runtime_error("Print function requires an argument");
                }
            } else {
                // Direct function call
                lastValue = builder->CreateCall(functionCallee, args, "calltmp");
            }
            callee = lastValue;
        }
    }

    // Handle DOT IDENTIFIER sequence
    for (size_t i = 0; i < ctx->DOT().size(); i++) {
        std::string memberName = ctx->IDENTIFIER()[i]->getText();
        auto typeInfo = typeMetadata->getTypeInfo(callee);

        if (!typeInfo || typeInfo->getKind() != TypeInfo::Kind::Class) {
            throw std::runtime_error("Expected class type in member access");
        }

        auto classInfo = std::dynamic_pointer_cast<LLVMClassTypeInfo>(typeInfo);
        if (!classInfo) {
            throw std::runtime_error("Failed to get LLVM class type info");
        }

        size_t memberIndex = classInfo->getMemberIndex(memberName);
        std::vector<llvm::Value*> indices = {
            llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0),
            llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), memberIndex)
        };

        callee = builder->CreateGEP(classInfo->getStructType(), callee, indices, "member.ptr");
        auto memberType = classInfo->getFieldType(memberName);
        if (!memberType) {
            throw std::runtime_error("Failed to get member type for: " + memberName);
        }
        callee = builder->CreateLoad(classInfo->getStructType(), callee, memberName.c_str());
        lastValue = callee;
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
        auto nullType = typeRegistry.getPointerType();
        lastValue = llvm::Constant::getNullValue(LLVMTypeRegistry::getInstance().getLLVMType(nullType, *context));
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
            llvm::AllocaInst* alloca = varIt->second;
            if (!alloca) {
                throw std::runtime_error("Variable " + name + " has null allocation");
            }
            auto typeInfo = typeMetadata->getTypeInfo(alloca);
            if (!typeInfo) {
                throw std::runtime_error("Variable " + name + " has null type info");
            }
            auto llvmType = LLVMTypeRegistry::getInstance().getLLVMType(typeInfo, *context);
            lastValue = builder->CreateLoad(llvmType, alloca, name.c_str());
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

    // Get class type info from registry
    auto classTypeInfo = typeMetadata->getClassTypeInfo(classType);
    if (!classTypeInfo) {
        throw std::runtime_error("Class type info not found for: " + className);
    }

    // Allocate memory for the object
    llvm::Function* mallocFunc = module->getFunction("malloc");
    if (!mallocFunc) {
        auto i8Type = llvm::Type::getInt8Ty(*context);
        llvm::FunctionType* mallocType = llvm::FunctionType::get(
            i8Type,
            { llvm::Type::getInt64Ty(*context) },
            false);
        mallocFunc = llvm::Function::Create(mallocType, llvm::Function::ExternalLinkage, "malloc", module.get());
    }

    llvm::Value* size = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context),
                                               module->getDataLayout().getTypeAllocSize(classType));
    llvm::Value* mem = builder->CreateCall(mallocFunc, {size}, "objmem");
    llvm::Value* obj = builder->CreateBitCast(mem, LLVMTypeRegistry::getInstance().getLLVMType(classTypeInfo, *context), "obj");

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
            auto memberTypeInfo = classInfo->getMemberTypeInfo(memberName);
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
    auto typeInfo = typeRegistry.lookupType(typeName);
    if (!typeInfo) {
        throw std::runtime_error("Unknown type: " + typeName);
    }
    return LLVMTypeRegistry::getInstance().getLLVMType(typeInfo, *context);
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
    auto returnTypeInfo = typeRegistry.lookupType(ctx->type() ? ctx->type()->getText() : "void");
    std::vector<TypeInfoPtr> paramTypeInfos;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypeInfos.push_back(typeRegistry.lookupType(param->type()->getText()));
        }
    }
    auto functionTypeInfo = std::make_shared<LLVMFunctionTypeInfo>(
        funcName, returnTypeInfo, paramTypeInfos, funcType);
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

// Printf function declaration
llvm::Function* LLVMCodegen::declarePrintf() {
    if (functions.find("printf") != functions.end()) {
        return functions["printf"];
    }

    // Create printf function type using our type system
    std::vector<llvm::Type*> paramTypes;
    paramTypes.push_back(llvm::Type::getInt8Ty(*context)->getPointerTo());  // Format string (i8*)
    llvm::FunctionType* printfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),  // Return type: int
        paramTypes,
        true  // varargs
    );

    // Create the function
    llvm::Function* printfFunc = llvm::Function::Create(
        printfType,
        llvm::Function::ExternalLinkage,
        "printf",
        module.get()
    );

    functions["printf"] = printfFunc;
    return printfFunc;
}

// Malloc function declaration
llvm::Function* LLVMCodegen::declareMalloc() {
    if (functions.find("malloc") != functions.end()) {
        return functions["malloc"];
    }

    std::cerr << "DEBUG: Declaring malloc function" << std::endl;

    // Create malloc function type
    // malloc takes a size_t (i64) parameter and returns an opaque pointer
    std::vector<llvm::Type*> paramTypes = {llvm::Type::getInt64Ty(*context)};  // size_t parameter

    // Use opaque pointer type directly since LLVM 20.0.0 treats all pointers as opaque
    llvm::FunctionType* mallocType = llvm::FunctionType::get(
        llvm::Type::getInt8Ty(*context),  // Return type: opaque pointer (i8)
        paramTypes,                        // Parameter types: size_t
        false                             // Not varargs
    );

    // Create the function
    llvm::Function* mallocFunc = llvm::Function::Create(
        mallocType,
        llvm::Function::ExternalLinkage,
        "malloc",
        module.get()
    );

    std::cerr << "DEBUG: Malloc function declared successfully" << std::endl;
    functions["malloc"] = mallocFunc;
    return mallocFunc;
}

// Call suffix implementation
std::any LLVMCodegen::visitCallSuffix(PrystParser::CallSuffixContext* ctx) {
    std::vector<llvm::Value*> args;
    if (ctx->arguments()) {
        for (auto expr : ctx->arguments()->expression()) {
            visit(expr);
            args.push_back(lastValue);
        }
    }
    return nullptr;
}

// Type conversion expression implementation
std::any LLVMCodegen::visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) {
    visit(ctx->expression());
    llvm::Value* value = lastValue;
    std::string targetType = ctx->type()->getText();

    // Get type information from registry
    auto& registry = TypeRegistry::getInstance();
    auto typeInfo = registry.lookupType(targetType);
    if (!typeInfo) {
        throw std::runtime_error("Unknown target type: " + targetType);
    }

    // Convert value to target type
    llvm::Type* llvmTargetType = getLLVMTypeFromTypeInfo(typeInfo);
    if (value->getType() == llvmTargetType) {
        lastValue = value;
        return nullptr;
    }

    // Handle numeric conversions
    if (TypeInfo::isNumericType(typeInfo)) {
        if (targetType == "int") {
            lastValue = builder->CreateFPToSI(value, llvm::Type::getInt32Ty(*context), "conv.int");
        } else if (targetType == "float") {
            lastValue = builder->CreateSIToFP(value, llvm::Type::getDoubleTy(*context), "conv.float");
        }
    } else if (targetType == "str") {
        lastValue = convertToString(value);
    } else {
        throw std::runtime_error("Unsupported type conversion to: " + targetType);
    }

    return nullptr;
}

// Class conversion expression implementation
std::any LLVMCodegen::visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) {
    visit(ctx->expression());
    llvm::Value* value = lastValue;
    std::string targetClassName = ctx->IDENTIFIER()->getText();

    // Get class type information
    auto& registry = TypeRegistry::getInstance();
    auto typeInfo = registry.lookupType(targetClassName);
    if (!typeInfo || typeInfo->getKind() != TypeInfo::Kind::Class) {
        throw std::runtime_error("Invalid target class type: " + targetClassName);
    }

    auto classInfo = std::dynamic_pointer_cast<ClassTypeInfo>(typeInfo);
    if (!classInfo) {
        throw std::runtime_error("Failed to get class info for: " + targetClassName);
    }

    // Check if conversion method exists
    std::string convMethodName = "c!" + targetClassName;
    auto sourceTypeInfo = typeMetadata->getTypeInfo(value);
    if (!sourceTypeInfo) {
        throw std::runtime_error("Failed to get source type info");
    }

    if (sourceTypeInfo->getKind() == TypeInfo::Kind::Class) {
        auto sourceClassInfo = std::dynamic_pointer_cast<ClassTypeInfo>(sourceTypeInfo);
        if (sourceClassInfo && sourceClassInfo->hasMethod(convMethodName)) {
            // Call conversion method
            std::vector<llvm::Value*> args;
            lastValue = generateMethodCall(value, convMethodName, args);
            return nullptr;
        }
    }

    throw std::runtime_error("No conversion method found from " + sourceTypeInfo->getName() + " to " + targetClassName);
}
// String conversion implementation
llvm::Value* LLVMCodegen::convertToString(llvm::Value* value) {
    if (!value) return nullptr;

    // Get type information from registry
    auto typeInfo = typeMetadata->getTypeInfo(value);
    if (!typeInfo) {
        throw std::runtime_error("Failed to get type info for string conversion");
    }

    llvm::Function* toStringFunc = declareToString();
    llvm::LLVMContext& context = module->getContext();

    if (typeInfo == typeRegistry.getIntType()) {
        // Convert integer to string
        std::vector<llvm::Value*> args = {value};
        return builder->CreateCall(toStringFunc, args, "int.to.str");
    } else if (typeInfo == typeRegistry.getFloatType()) {
        // Convert float to string
        std::vector<llvm::Value*> args = {value};
        return builder->CreateCall(toStringFunc, args, "float.to.str");
    } else if (typeInfo == typeRegistry.getStrType()) {
        return value;  // Already a string type
    }

    throw std::runtime_error("Unsupported type for string conversion");
}

// Method call implementation
llvm::Value* LLVMCodegen::generateMethodCall(llvm::Value* object, const std::string& methodName, const std::vector<llvm::Value*>& args) {
    if (!object) {
        throw std::runtime_error("Null object in method call");
    }

    // Get object's type info
    auto typeInfo = typeMetadata->getTypeInfo(object);
    if (!typeInfo || typeInfo->getKind() != TypeInfo::Kind::Class) {
        throw std::runtime_error("Method call on non-class type");
    }

    auto classInfo = std::dynamic_pointer_cast<ClassTypeInfo>(typeInfo);
    if (!classInfo) {
        throw std::runtime_error("Failed to get class info for method call");
    }

    // Find method in class
    if (!classInfo->hasMethod(methodName)) {
        throw std::runtime_error("Method '" + methodName + "' not found in class '" + classInfo->getName() + "'");
    }

    // Get method info and create function call
    auto methodInfo = classInfo->getMethod(methodName);
    if (!methodInfo) {
        throw std::runtime_error("Failed to get method info for: " + methodName);
    }

    auto methodFunction = module->getFunction(classInfo->getName() + "_" + methodName);
    if (!methodFunction) {
        throw std::runtime_error("Method function not found in module");
    }

    // Prepare arguments with 'this' pointer as first argument
    std::vector<llvm::Value*> callArgs = {object};
    callArgs.insert(callArgs.end(), args.begin(), args.end());

    // Generate the call
    return builder->CreateCall(methodFunction, callArgs, "method.call");
}

// String conversion helper functions
llvm::Function* LLVMCodegen::declareToString() {
    // Check if the function is already declared
    if (auto existingFunc = module->getFunction("toString")) {
        return existingFunc;
    }

    // Get the module's context
    llvm::LLVMContext& context = module->getContext();

    // Create function type using our type system
    auto strType = typeRegistry.getStrType();
    auto& moduleContext = module->getContext();
    auto llvmStrType = LLVMTypeRegistry::getInstance().getLLVMType(strType, moduleContext);
    std::vector<llvm::Type*> paramTypes = {llvmStrType};
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmStrType,  // Return type: string
        paramTypes,   // Parameter types
        false                     // Not variadic
    );

    // Declare the function
    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "toString",
        module.get()
    );

    return func;
}
