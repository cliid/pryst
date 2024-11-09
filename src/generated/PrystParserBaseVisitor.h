
// Generated from PrystParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PrystParserVisitor.h"


/**
 * This class provides an empty implementation of PrystParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PrystParserBaseVisitor : public PrystParserVisitor {
public:

  virtual std::any visitProgram(PrystParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(PrystParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsingDecl(PrystParser::UsingDeclContext *ctx) override {
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

  virtual std::any visitBlock(PrystParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDecl(PrystParser::VariableDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDecl(PrystParser::ClassDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassBody(PrystParser::ClassBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassMember(PrystParser::ClassMemberContext *ctx) override {
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

  virtual std::any visitType(PrystParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(PrystParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(PrystParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiteral(PrystParser::StringLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringPart(PrystParser::StringPartContext *ctx) override {
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

  virtual std::any visitNewExpr(PrystParser::NewExprContext *ctx) override {
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

  virtual std::any visitTryCatchStmt(PrystParser::TryCatchStmtContext *ctx) override {
    return visitChildren(ctx);
  }


};

