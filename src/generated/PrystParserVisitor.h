
// Generated from PrystParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PrystParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by PrystParser.
 */
class  PrystParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by PrystParser.
   */
    virtual std::any visitProgram(PrystParser::ProgramContext *context) = 0;

    virtual std::any visitDeclaration(PrystParser::DeclarationContext *context) = 0;

    virtual std::any visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext *context) = 0;

    virtual std::any visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext *context) = 0;

    virtual std::any visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext *context) = 0;

    virtual std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext *context) = 0;

    virtual std::any visitModuleDecl(PrystParser::ModuleDeclContext *context) = 0;

    virtual std::any visitImportDecl(PrystParser::ImportDeclContext *context) = 0;

    virtual std::any visitImportPath(PrystParser::ImportPathContext *context) = 0;

    virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *context) = 0;

    virtual std::any visitNamedFunction(PrystParser::NamedFunctionContext *context) = 0;

    virtual std::any visitLambdaFunction(PrystParser::LambdaFunctionContext *context) = 0;

    virtual std::any visitFunctionBody(PrystParser::FunctionBodyContext *context) = 0;

    virtual std::any visitInferredVariableDecl(PrystParser::InferredVariableDeclContext *context) = 0;

    virtual std::any visitInferredConstVariableDecl(PrystParser::InferredConstVariableDeclContext *context) = 0;

    virtual std::any visitTypedVariableDecl(PrystParser::TypedVariableDeclContext *context) = 0;

    virtual std::any visitTypedConstVariableDecl(PrystParser::TypedConstVariableDeclContext *context) = 0;

    virtual std::any visitConstExprVariableDecl(PrystParser::ConstExprVariableDeclContext *context) = 0;

    virtual std::any visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext *context) = 0;

    virtual std::any visitClassDeclaration(PrystParser::ClassDeclarationContext *context) = 0;

    virtual std::any visitClassBody(PrystParser::ClassBodyContext *context) = 0;

    virtual std::any visitClassMemberDecl(PrystParser::ClassMemberDeclContext *context) = 0;

    virtual std::any visitClassMemberInferredDecl(PrystParser::ClassMemberInferredDeclContext *context) = 0;

    virtual std::any visitClassMemberConstInferredDecl(PrystParser::ClassMemberConstInferredDeclContext *context) = 0;

    virtual std::any visitClassMemberConstTypedDecl(PrystParser::ClassMemberConstTypedDeclContext *context) = 0;

    virtual std::any visitClassMemberFunctionDecl(PrystParser::ClassMemberFunctionDeclContext *context) = 0;

    virtual std::any visitParamList(PrystParser::ParamListContext *context) = 0;

    virtual std::any visitParam(PrystParser::ParamContext *context) = 0;

    virtual std::any visitParamTypeList(PrystParser::ParamTypeListContext *context) = 0;

    virtual std::any visitFloatType(PrystParser::FloatTypeContext *context) = 0;

    virtual std::any visitLambdaType(PrystParser::LambdaTypeContext *context) = 0;

    virtual std::any visitArrayType(PrystParser::ArrayTypeContext *context) = 0;

    virtual std::any visitStrType(PrystParser::StrTypeContext *context) = 0;

    virtual std::any visitIntType(PrystParser::IntTypeContext *context) = 0;

    virtual std::any visitVoidType(PrystParser::VoidTypeContext *context) = 0;

    virtual std::any visitIdentifierType(PrystParser::IdentifierTypeContext *context) = 0;

    virtual std::any visitFunctionType(PrystParser::FunctionTypeContext *context) = 0;

    virtual std::any visitBoolType(PrystParser::BoolTypeContext *context) = 0;

    virtual std::any visitExprStatement(PrystParser::ExprStatementContext *context) = 0;

    virtual std::any visitIfStatement(PrystParser::IfStatementContext *context) = 0;

    virtual std::any visitWhileStatement(PrystParser::WhileStatementContext *context) = 0;

    virtual std::any visitForStatement(PrystParser::ForStatementContext *context) = 0;

    virtual std::any visitReturnStatement(PrystParser::ReturnStatementContext *context) = 0;

    virtual std::any visitBlockStatement(PrystParser::BlockStatementContext *context) = 0;

    virtual std::any visitPrintStatement(PrystParser::PrintStatementContext *context) = 0;

    virtual std::any visitTryStmt(PrystParser::TryStmtContext *context) = 0;

    virtual std::any visitTryStatement(PrystParser::TryStatementContext *context) = 0;

    virtual std::any visitCatchStatement(PrystParser::CatchStatementContext *context) = 0;

    virtual std::any visitExpression(PrystParser::ExpressionContext *context) = 0;

    virtual std::any visitStringLiteralExpr(PrystParser::StringLiteralExprContext *context) = 0;

    virtual std::any visitStringPart(PrystParser::StringPartContext *context) = 0;

    virtual std::any visitAssignment(PrystParser::AssignmentContext *context) = 0;

    virtual std::any visitLogicOr(PrystParser::LogicOrContext *context) = 0;

    virtual std::any visitLogicAnd(PrystParser::LogicAndContext *context) = 0;

    virtual std::any visitEquality(PrystParser::EqualityContext *context) = 0;

    virtual std::any visitComparison(PrystParser::ComparisonContext *context) = 0;

    virtual std::any visitAddition(PrystParser::AdditionContext *context) = 0;

    virtual std::any visitMultiplication(PrystParser::MultiplicationContext *context) = 0;

    virtual std::any visitUnary(PrystParser::UnaryContext *context) = 0;

    virtual std::any visitPostfix(PrystParser::PostfixContext *context) = 0;

    virtual std::any visitSuffix(PrystParser::SuffixContext *context) = 0;

    virtual std::any visitCallSuffix(PrystParser::CallSuffixContext *context) = 0;

    virtual std::any visitMemberSuffix(PrystParser::MemberSuffixContext *context) = 0;

    virtual std::any visitCall(PrystParser::CallContext *context) = 0;

    virtual std::any visitPrimary(PrystParser::PrimaryContext *context) = 0;

    virtual std::any visitQualifiedIdentifier(PrystParser::QualifiedIdentifierContext *context) = 0;

    virtual std::any visitNewExpression(PrystParser::NewExpressionContext *context) = 0;

    virtual std::any visitArguments(PrystParser::ArgumentsContext *context) = 0;

    virtual std::any visitTypeCastExpr(PrystParser::TypeCastExprContext *context) = 0;

    virtual std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext *context) = 0;

    virtual std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext *context) = 0;


};

