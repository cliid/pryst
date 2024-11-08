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

LLVMCodegen::LLVMCodegen() {
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("pryst_module", *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
    typeRegistry = std::make_unique<LLVMTypeRegistry>(*context, builder.get(), module.get());
    stringInterp = std::make_unique<codegen::StringInterpolation>(builder.get(), module.get(), typeRegistry.get());
    currentFunction = nullptr;
}

std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(PrystParser::ProgramContext* ctx) {
    // Reset module for new generation
    module = std::make_unique<llvm::Module>("pryst_module", *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
    typeRegistry = std::make_unique<LLVMTypeRegistry>(*context, builder.get(), module.get());
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

std::any LLVMCodegen::visitStringInterpolation(PrystParser::StringInterpolationContext *ctx) {
    PRYST_DEBUG("Visiting string interpolation");

    // Get the format string
    std::string formatStr = ctx->STRING_LITERAL()->getText();
    // Remove quotes from string literal
    formatStr = formatStr.substr(1, formatStr.length() - 2);

    // Collect all expressions and their format specifiers
    std::vector<llvm::Value*> values;
    for (size_t i = 0; i < ctx->expression().size(); i++) {
        auto expr = ctx->expression(i);
        auto formatSpec = ctx->formatSpecifier(i);

        // Visit expression to get LLVM value
        auto exprValue = std::any_cast<llvm::Value*>(visit(expr));

        // Parse format specifier if present
        codegen::FormatSpecifier format;
        if (formatSpec) {
            std::string specStr = formatSpec->getText();
            auto parsedFormat = stringInterp->parseFormatSpec(specStr);
            if (parsedFormat) {
                format = *parsedFormat;
            }
        }

        // Generate formatted value
        auto formattedValue = stringInterp->generateFormattedValue(
            exprValue, format, expr->getText());
        values.push_back(formattedValue);
    }

    // Generate final interpolated string
    return stringInterp->generateInterpolation(formatStr, values);
}

std::any LLVMCodegen::visitFormatSpecifier(PrystParser::FormatSpecifierContext *ctx) {
    PRYST_DEBUG("Visiting format specifier");
    // Format specifiers are handled within visitStringInterpolation
    return std::any();
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
