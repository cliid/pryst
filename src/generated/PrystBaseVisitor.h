
// Generated from /Users/cliid/dev/pryst/Pryst.g4 by ANTLR 4.13.2

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

  virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDecl(PrystParser::VariableDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDeclaration(PrystParser::ClassDeclarationContext *ctx) override {
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

  virtual std::any visitType(PrystParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(PrystParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStmt(PrystParser::ExpressionStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(PrystParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStmt(PrystParser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStmt(PrystParser::ForStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(PrystParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(PrystParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(PrystParser::ExpressionContext *ctx) override {
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

  virtual std::any visitCall(PrystParser::CallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallSuffix(PrystParser::CallSuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary(PrystParser::PrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewExpression(PrystParser::NewExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(PrystParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }


};

