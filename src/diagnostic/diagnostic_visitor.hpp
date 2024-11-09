#pragma once

#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "utils/logger.hpp"
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
    std::any visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext* ctx) override;
    std::any visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext* ctx) override;
    std::any visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext* ctx) override;
    std::any visitNamedFunction(PrystParser::NamedFunctionContext* ctx) override;
    std::any visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) override;
    std::any visitFunctionBody(PrystParser::FunctionBodyContext* ctx) override;

    // Variable declarations
    std::any visitInferredVariableDecl(PrystParser::InferredVariableDeclContext* ctx) override;
    std::any visitTypedVariableDecl(PrystParser::TypedVariableDeclContext* ctx) override;
    std::any visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext* ctx) override;
    std::any visitClassInferredVariableDecl(PrystParser::ClassInferredVariableDeclContext* ctx) override;
    std::any visitClassTypedVariableDecl(PrystParser::ClassTypedVariableDeclContext* ctx) override;
    std::any visitClassConstInferredDecl(PrystParser::ClassConstInferredDeclContext* ctx) override;
    std::any visitClassConstTypedDecl(PrystParser::ClassConstTypedDeclContext* ctx) override;

    // Class-related
    std::any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    std::any visitClassBody(PrystParser::ClassBodyContext* ctx) override;
    std::any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) override;
    std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;

    // Statements
    std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    std::any visitPrintStatement(PrystParser::PrintStatementContext* ctx) override;
    std::any visitTryStatement(PrystParser::TryStatementContext* ctx) override;
    std::any visitTryCatchStatement(PrystParser::TryCatchStatementContext* ctx) override;

    // Type casting
    std::any visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx) override;
    std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) override;

private:
    std::vector<std::string> currentNamespace;
    std::string currentModule;
    std::string currentFunction;
    bool inLoop;
    bool inTryBlock;
    std::vector<std::string> expectedReturnType;

    bool isNumericType(const std::string& type);
    std::string promoteTypes(const std::string& type1, const std::string& type2);
    bool areTypesCompatible(const std::string& expected, const std::string& actual);
    std::string getQualifiedName(const std::string& name);
    void enterScope();
    void exitScope();

    // Expressions
    std::any visitExpression(PrystParser::ExpressionContext* ctx) override;
    std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    std::any visitStringLiteral(PrystParser::StringLiteralContext* ctx) override;
    std::any visitInterpolatedString(PrystParser::InterpolatedStringContext* ctx) override;
    std::any visitSimpleString(PrystParser::SimpleStringContext* ctx) override;
    std::any visitStringPart(PrystParser::StringPartContext* ctx) override;
    std::any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    std::any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    std::any visitEquality(PrystParser::EqualityContext* ctx) override;
    std::any visitComparison(PrystParser::ComparisonContext* ctx) override;
    std::any visitAddition(PrystParser::AdditionContext* ctx) override;
    std::any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    std::any visitPostfix(PrystParser::PostfixContext* ctx) override;
    std::any visitSuffix(PrystParser::SuffixContext* ctx) override;
    std::any visitCallSuffix(PrystParser::CallSuffixContext* ctx) override;
    std::any visitMemberSuffix(PrystParser::MemberSuffixContext* ctx) override;
    std::any visitCall(PrystParser::CallContext* ctx) override;
    std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    std::any visitQualifiedIdentifier(PrystParser::QualifiedIdentifierContext* ctx) override;
    std::any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;
    std::any visitArguments(PrystParser::ArgumentsContext* ctx) override;

    // Types
    std::any visitType(PrystParser::TypeContext* ctx) override;
    std::any visitParamList(PrystParser::ParamListContext* ctx) override;
    std::any visitParam(PrystParser::ParamContext* ctx) override;
    std::any visitParamTypeList(PrystParser::ParamTypeListContext* ctx) override;

    void reportError(antlr4::ParserRuleContext* ctx, const std::string& message);
    void reportWarning(antlr4::ParserRuleContext* ctx, const std::string& message);
    std::string getLocation(antlr4::ParserRuleContext* ctx);
};

} // namespace pryst
