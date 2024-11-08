#include "llvm_codegen.hpp"
#include "utils/debug.hpp"
#include "../generated/PrystLexer.h"
#include "../generated/PrystParser.h"
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

// Constructor is defined in header

std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(PrystParser::ProgramContext* ctx) {
    // Initialize module components
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("pryst_module", *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
    typeRegistry = std::make_unique<LLVMTypeRegistry>(*context, *builder, *module);
    stringInterp = std::make_unique<codegen::StringInterpolation>(builder.get(), module.get(), typeRegistry.get());
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

llvm::Function* LLVMCodegen::declareMalloc() {
    if (auto* existingFunc = functions["malloc"]) return existingFunc;

    std::vector<llvm::Type*> mallocArgs = {
        llvm::Type::getInt64Ty(*context)
    };
    auto* mallocType = llvm::FunctionType::get(
        typeRegistry->createOpaquePointer(),  // Return type (void*)
        mallocArgs,
        false
    );

    auto* mallocFunc = llvm::Function::Create(
        mallocType,
        llvm::Function::ExternalLinkage,
        "malloc",
        module.get()
    );

    functions["malloc"] = mallocFunc;
    return mallocFunc;
}

std::any LLVMCodegen::visitStringLiteralRule(PrystParser::StringLiteralRuleContext *ctx) {
    PRYST_DEBUG("Visiting string literal");

    std::vector<llvm::Value*> values;
    std::string formatStr;

    // Process string parts (skip STRING_START and STRING_END tokens)
    for (size_t i = 1; i < ctx->children.size() - 1; i++) {
        auto child = ctx->children[i];

        // Check the type of the child using dynamic_cast
        if (auto content = dynamic_cast<antlr4::tree::TerminalNode*>(child)) {
            auto tokenType = content->getSymbol()->getType();
            if (tokenType == PrystParser::STRING_CONTENT) {
                formatStr += content->getText();
            } else if (tokenType == PrystParser::ESCAPE_SEQ) {
                formatStr += stringInterp->processEscapeSequence(content->getText());
            }
        } else if (auto interpCtx = dynamic_cast<PrystParser::ExpressionContext*>(child)) {
            // Handle interpolation expression
            auto exprValue = std::any_cast<llvm::Value*>(visit(interpCtx));
            values.push_back(exprValue);
            formatStr += "{}"; // Placeholder for interpolation
        }
    }

    // Generate final interpolated string
    return stringInterp->generateInterpolation(formatStr, values);
}

// Variable declaration visitors
std::any LLVMCodegen::visitInferredVariableDecl(PrystParser::InferredVariableDeclContext *ctx) {
    PRYST_DEBUG("Visiting inferred variable declaration");

    // Get variable name
    std::string varName = ctx->IDENTIFIER()->getText();

    // Visit the initializer expression
    auto initValue = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    // Infer type from the initializer
    llvm::Type* varType = initValue->getType();

    // Create allocation for the variable
    llvm::AllocaInst* alloca = createEntryBlockAlloca(currentFunction, varName, varType);

    // Store the initial value
    builder->CreateStore(initValue, alloca);

    // Add to symbol table
    namedValues[varName] = alloca;

    return alloca;
}

std::any LLVMCodegen::visitTypedVariableDecl(PrystParser::TypedVariableDeclContext *ctx) {
    PRYST_DEBUG("Visiting typed variable declaration");

    // Get variable name and type
    std::string varName = ctx->IDENTIFIER()->getText();
    llvm::Type* varType = std::any_cast<llvm::Type*>(visit(ctx->type()));

    // Create allocation
    llvm::AllocaInst* alloca = createEntryBlockAlloca(currentFunction, varName, varType);

    // If there's an initializer, handle it
    if (ctx->expression()) {
        auto initValue = std::any_cast<llvm::Value*>(visit(ctx->expression()));
        // Convert the initializer to the declared type if needed
        if (initValue->getType() != varType) {
            initValue = typeRegistry->convertValue(initValue, varType);
        }
        builder->CreateStore(initValue, alloca);
    }

    // Add to symbol table
    namedValues[varName] = alloca;

    return alloca;
}

std::any LLVMCodegen::visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext *ctx) {
    PRYST_DEBUG("Visiting uninitialized variable declaration");

    // Get variable name and type
    std::string varName = ctx->IDENTIFIER()->getText();
    llvm::Type* varType = std::any_cast<llvm::Type*>(visit(ctx->type()));

    // Create allocation
    llvm::AllocaInst* alloca = createEntryBlockAlloca(currentFunction, varName, varType);

    // Store a default value based on type
    auto defaultValue = typeRegistry->getDefaultValue(varType);
    builder->CreateStore(defaultValue, alloca);

    // Add to symbol table
    namedValues[varName] = alloca;

    return alloca;
}

} // namespace pryst
