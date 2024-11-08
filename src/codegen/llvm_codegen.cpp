#include "llvm_codegen.hpp"
#include "utils/debug.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <string>

namespace pryst {



std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(PrystParser::ProgramContext* ctx) {
    // Reset module for new generation
    module = std::make_unique<llvm::Module>("pryst_module", *context);
    builder->SetInsertPoint(llvm::BasicBlock::Create(*context));

    declarePrintFunctions();
    visitProgram(ctx);

    // Verify module
    std::string errorInfo;
    llvm::raw_string_ostream errorStream(errorInfo);
    if (llvm::verifyModule(*module, &errorStream)) {
        PRYST_ERROR("Module verification failed: " + errorInfo);
        return nullptr;
    }
    return std::move(module);
}

std::any LLVMCodegen::visitProgram(PrystParser::ProgramContext *ctx) {
    PRYST_DEBUG("Visiting program");
    for (auto decl : ctx->declaration()) {
        visitDeclaration(decl);
    }
    return std::any();
}

std::any LLVMCodegen::visitDeclaration(PrystParser::DeclarationContext *ctx) {
    PRYST_DEBUG("Visiting declaration");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext *ctx) {
    PRYST_DEBUG("Visiting global using declaration");
    return std::any();
}

std::any LLVMCodegen::visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext *ctx) {
    PRYST_DEBUG("Visiting block scoped namespace declaration");
    return std::any();
}

std::any LLVMCodegen::visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext *ctx) {
    PRYST_DEBUG("Visiting block scoped module declaration");
    return std::any();
}

std::any LLVMCodegen::visitNamespaceDecl(PrystParser::NamespaceDeclContext *ctx) {
    PRYST_DEBUG("Visiting namespace declaration");
    return std::any();
}

std::any LLVMCodegen::visitModuleDecl(PrystParser::ModuleDeclContext *ctx) {
    PRYST_DEBUG("Visiting module declaration");
    return std::any();
}

std::any LLVMCodegen::visitImportDecl(PrystParser::ImportDeclContext *ctx) {
    PRYST_DEBUG("Visiting import declaration");
    return std::any();
}

std::any LLVMCodegen::visitImportPath(PrystParser::ImportPathContext *ctx) {
    PRYST_DEBUG("Visiting import path");
    return std::any();
}

llvm::AllocaInst* LLVMCodegen::createEntryBlockAlloca(llvm::Function* function,
    const std::string& varName, llvm::Type* type) {
    llvm::IRBuilder<> tmpBuilder(&function->getEntryBlock(),
        function->getEntryBlock().begin());
    return tmpBuilder.CreateAlloca(type, nullptr, varName);
}

void LLVMCodegen::declarePrintFunctions() {
    // Print function declarations will be implemented in subsequent updates
}

// Type system implementations
llvm::Type* LLVMCodegen::getPointerType(llvm::Type* elementType) {
    // In LLVM 20.0.0, all pointers are opaque i8*
    return llvm::Type::getInt8Ty(*context);
}

llvm::Type* LLVMCodegen::getLLVMTypeFromTypeInfo(TypeInfoPtr typeInfo) {
    if (!typeInfo) {
        throw std::runtime_error("Invalid type info");
    }
    return ::pryst::getLLVMTypeFromTypeInfo(typeInfo, *context);
}

// Class member visitor implementations
std::any LLVMCodegen::visitClassTypedVariableDecl(PrystParser::ClassTypedVariableDeclContext *ctx) {
    PRYST_DEBUG("Visiting class typed variable declaration");
    // Get the type
    auto typeCtx = ctx->type();
    llvm::Type* varType = std::any_cast<llvm::Type*>(visit(typeCtx));

    // Get the variable name
    std::string varName = ctx->IDENTIFIER()->getText();

    // Get the initialization value
    llvm::Value* initValue = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    // Create alloca for the class member
    llvm::AllocaInst* alloca = createEntryBlockAlloca(currentFunction, varName, varType);

    // Store the initial value
    builder->CreateStore(initValue, alloca);

    // Add to symbol table
    namedValues[varName] = alloca;

    return std::any();
}

std::any LLVMCodegen::visitClassInferredVariableDecl(PrystParser::ClassInferredVariableDeclContext *ctx) {
    PRYST_DEBUG("Visiting class inferred variable declaration");
    // Get the variable name
    std::string varName = ctx->IDENTIFIER()->getText();

    // Get the initialization value and infer type
    llvm::Value* initValue = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    llvm::Type* varType = initValue->getType();

    // Create alloca for the class member
    llvm::AllocaInst* alloca = createEntryBlockAlloca(currentFunction, varName, varType);

    // Store the initial value
    builder->CreateStore(initValue, alloca);

    // Add to symbol table
    namedValues[varName] = alloca;

    return std::any();
}

std::any LLVMCodegen::visitClassConstInferredDecl(PrystParser::ClassConstInferredDeclContext *ctx) {
    PRYST_DEBUG("Visiting class const inferred declaration");
    // Get the variable name
    std::string varName = ctx->IDENTIFIER()->getText();

    // Get the initialization value and infer type
    llvm::Value* initValue = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    llvm::Type* varType = initValue->getType();

    // Create constant value
    llvm::GlobalVariable* constVar = new llvm::GlobalVariable(
        *module,
        varType,
        true, // isConstant
        llvm::GlobalValue::PrivateLinkage,
        llvm::dyn_cast<llvm::Constant>(initValue),
        varName
    );

    // Add to symbol table
    namedValues[varName] = constVar;

    return std::any();
}

std::any LLVMCodegen::visitClassConstTypedDecl(PrystParser::ClassConstTypedDeclContext *ctx) {
    PRYST_DEBUG("Visiting class const typed declaration");
    // Get the type
    auto typeCtx = ctx->type();
    llvm::Type* varType = std::any_cast<llvm::Type*>(visit(typeCtx));

    // Get the variable name
    std::string varName = ctx->IDENTIFIER()->getText();

    // Get the initialization value
    llvm::Value* initValue = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    // Create constant value
    llvm::GlobalVariable* constVar = new llvm::GlobalVariable(
        *module,
        varType,
        true, // isConstant
        llvm::GlobalValue::PrivateLinkage,
        llvm::dyn_cast<llvm::Constant>(initValue),
        varName
    );

    // Add to symbol table
    namedValues[varName] = constVar;

    return std::any();
}

std::any LLVMCodegen::visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext *ctx) {
    PRYST_DEBUG("Visiting class function declaration");
    // Get function name
    std::string funcName = ctx->IDENTIFIER()->getText();

    // Get return type
    auto returnTypeCtx = ctx->type();
    llvm::Type* returnType = std::any_cast<llvm::Type*>(visit(returnTypeCtx));

    // Get parameter types
    std::vector<llvm::Type*> paramTypes;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            auto paramType = std::any_cast<llvm::Type*>(visit(param->type()));
            paramTypes.push_back(paramType);
        }
    }

    // Create function type
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        returnType,
        paramTypes,
        false // isVarArg
    );

    // Create function
    llvm::Function* function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        funcName,
        module.get()
    );

    // Create basic block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(bb);

    // Save the current function
    llvm::Function* parentFunction = currentFunction;
    currentFunction = function;

    // Visit function body
    visit(ctx->functionBody());

    // Restore the parent function
    currentFunction = parentFunction;

    return std::any();
}

} // namespace pryst
