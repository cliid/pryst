#pragma once

#include "antlr4-runtime.h"
#include "../generated/PrystParserBaseVisitor.h"
#include "../semantic/symbol_table.hpp"
#include <any>
#include <string>
#include <vector>

class DiagnosticVisitor : public PrystParserBaseVisitor {
public:
    explicit DiagnosticVisitor(SymbolTable& symbolTable);

    // Core visitor methods
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    std::any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    std::any visitBinary(PrystParser::BinaryContext* ctx) override;
    std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    std::any visitCall(PrystParser::CallContext* ctx) override;
    std::any visitVariable(PrystParser::VariableContext* ctx) override;
    std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;

    // Module and namespace support
    std::any visitModuleDecl(PrystParser::ModuleDeclContext* ctx) override;
    std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext* ctx) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext* ctx) override;
    std::any visitQualifiedIdentifier(PrystParser::QualifiedIdentifierContext* ctx) override;

private:
    SymbolTable& symbolTable;
    std::string currentFunction;
    std::string currentModule;
    std::vector<std::string> currentNamespace;

    // Helper methods
    bool isNumericType(const std::string& type);
    std::string promoteTypes(const std::string& type1, const std::string& type2);
    bool areTypesCompatible(const std::string& expected, const std::string& actual);
    void reportError(antlr4::ParserRuleContext* ctx, const std::string& message);
    void reportWarning(antlr4::ParserRuleContext* ctx, const std::string& message);
    std::string getSourceLocation(antlr4::ParserRuleContext* ctx);
};
