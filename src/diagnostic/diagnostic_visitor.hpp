#pragma once

#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "../utils/logger.hpp"
#include <memory>
#include <string>
#include <vector>
#include <any>

namespace pryst {

class DiagnosticVisitor : public PrystBaseVisitor {
public:
    DiagnosticVisitor();
    virtual ~DiagnosticVisitor() = default;

    // Program and declarations
    std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext* ctx) override;
    std::any visitModuleDecl(PrystParser::ModuleDeclContext* ctx) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext* ctx) override;
    std::any visitUsingDecl(PrystParser::UsingDeclContext* ctx) override;
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    std::any visitClassDecl(PrystParser::ClassDeclContext* ctx) override;
    std::any visitMethodDecl(PrystParser::MethodDeclContext* ctx) override;
    std::any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;

    // Statements
    std::any visitBlock(PrystParser::BlockContext* ctx) override;
    std::any visitExpressionStmt(PrystParser::ExpressionStmtContext* ctx) override;
    std::any visitIfStmt(PrystParser::IfStmtContext* ctx) override;
    std::any visitWhileStmt(PrystParser::WhileStmtContext* ctx) override;
    std::any visitReturnStmt(PrystParser::ReturnStmtContext* ctx) override;
    std::any visitPrintStmt(PrystParser::PrintStmtContext* ctx) override;

    // Expressions
    std::any visitBinary(PrystParser::BinaryContext* ctx) override;
    std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    std::any visitMemberAccess(PrystParser::MemberAccessContext* ctx) override;
    std::any visitVariable(PrystParser::VariableContext* ctx) override;
    std::any visitCall(PrystParser::CallContext* ctx) override;
    std::any visitLiteral(PrystParser::LiteralContext* ctx) override;
    std::any visitStringInterpolation(PrystParser::StringInterpolationContext* ctx) override;
    std::any visitTypeCast(PrystParser::TypeCastContext* ctx) override;
    std::any visitLambda(PrystParser::LambdaContext* ctx) override;

    // Types
    std::any visitType(PrystParser::TypeContext* ctx) override;
    std::any visitTypeParameters(PrystParser::TypeParametersContext* ctx) override;
    std::any visitTypeArguments(PrystParser::TypeArgumentsContext* ctx) override;

private:
    std::vector<std::string> currentNamespace;
    std::string currentModule;
    std::string currentFunction;
    bool inLoop;

    void reportError(antlr4::ParserRuleContext* ctx, const std::string& message);
    void reportWarning(antlr4::ParserRuleContext* ctx, const std::string& message);
    std::string getLocation(antlr4::ParserRuleContext* ctx);
};

} // namespace pryst
