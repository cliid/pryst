#pragma once

#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "symbol_table.hpp"
#include "type_info.hpp"
#include "module_loader.hpp"
#include <memory>
#include <string>
#include <vector>
#include <any>

namespace pryst {

class SemanticAnalyzer : public PrystBaseVisitor {
public:
    SemanticAnalyzer();
    virtual ~SemanticAnalyzer() = default;

    // Core visitor methods - exactly matching PrystBaseVisitor.h
    std::any visitProgram(PrystParser::ProgramContext *ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext *ctx) override;
    std::any visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext *ctx) override;
    std::any visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext *ctx) override;
    std::any visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext *ctx) override;
    std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext *ctx) override;
    std::any visitModuleDecl(PrystParser::ModuleDeclContext *ctx) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext *ctx) override;
    std::any visitImportPath(PrystParser::ImportPathContext *ctx) override;
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) override;
    
    // ... Additional visitor methods for expressions, statements, and types ...
    // (All other visitor methods from PrystBaseVisitor.h should be added here)

private:
    SymbolTable symbolTable;
    ModuleLoader moduleLoader;
    std::string currentFunction;
    bool inLoop;
    std::vector<std::string> currentNamespace;
    std::string currentModule;

    std::string getExpressionType(antlr4::tree::ParseTree* ctx);
    bool areTypesCompatible(const std::string& expected, const std::string& actual);
    std::string resolveType(const std::string& type);
    void checkVariableUsage(const std::string& name, antlr4::tree::ParseTree* ctx);
};

} // namespace pryst
