
// Generated from Pryst.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PrystVisitor.h"


/**
 * This class provides an empty implementation of PrystVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PrystBaseVisitor : public PrystVisitor {
public:

  virtual std::any visitProgram(PrystParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(PrystParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModuleDecl(PrystParser::ModuleDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportDecl(PrystParser::ImportDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportPath(PrystParser::ImportPathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamedFunction(PrystParser::NamedFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaFunction(PrystParser::LambdaFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionBody(PrystParser::FunctionBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInferredVariableDecl(PrystParser::InferredVariableDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedVariableDecl(PrystParser::TypedVariableDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDeclaration(PrystParser::ClassDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassBody(PrystParser::ClassBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassMemberDecl(PrystParser::ClassMemberDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassMemberInferredDecl(PrystParser::ClassMemberInferredDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassMemberConstInferredDecl(PrystParser::ClassMemberConstInferredDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassMemberConstTypedDecl(PrystParser::ClassMemberConstTypedDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassMemberFunctionDecl(PrystParser::ClassMemberFunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParamList(PrystParser::ParamListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParam(PrystParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParamTypeList(PrystParser::ParamTypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatType(PrystParser::FloatTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(PrystParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStrType(PrystParser::StrTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntType(PrystParser::IntTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVoidType(PrystParser::VoidTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierType(PrystParser::IdentifierTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionType(PrystParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolType(PrystParser::BoolTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprStatement(PrystParser::ExprStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(PrystParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(PrystParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(PrystParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(PrystParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStatement(PrystParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTryStmtWrapper(PrystParser::TryStmtWrapperContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrintStatement(PrystParser::PrintStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTryStatement(PrystParser::TryStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(PrystParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiteralRule(PrystParser::StringLiteralRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(PrystParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicOr(PrystParser::LogicOrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicAnd(PrystParser::LogicAndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEquality(PrystParser::EqualityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparison(PrystParser::ComparisonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddition(PrystParser::AdditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplication(PrystParser::MultiplicationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary(PrystParser::UnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostfix(PrystParser::PostfixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuffix(PrystParser::SuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallSuffix(PrystParser::CallSuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberSuffix(PrystParser::MemberSuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall(PrystParser::CallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary(PrystParser::PrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedIdentifier(PrystParser::QualifiedIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewExpression(PrystParser::NewExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(PrystParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeCastExpr(PrystParser::TypeCastExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

