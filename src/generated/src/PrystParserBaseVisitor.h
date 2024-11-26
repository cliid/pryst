
// Generated from src/PrystParser.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "PrystParserVisitor.h"


/**
 * This class provides an empty implementation of PrystParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PrystParserBaseVisitor : public PrystParserVisitor {
public:

  virtual antlrcpp::Any visitProgram(PrystParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitModuleDecl(PrystParser::ModuleDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImportDecl(PrystParser::ImportDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImportPath(PrystParser::ImportPathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclaration(PrystParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitErrorDecl(PrystParser::ErrorDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameters(PrystParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter(PrystParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefaultParam(PrystParser::DefaultParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(PrystParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(PrystParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDecl(PrystParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifierList(PrystParser::IdentifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignment(PrystParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStmt(PrystParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileStmt(PrystParser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForStmt(PrystParser::ForStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturnStmt(PrystParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTryStmt(PrystParser::TryStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreakStmt(PrystParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContinueStmt(PrystParser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrintStmt(PrystParser::PrintStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionStmt(PrystParser::ExpressionStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassDecl(PrystParser::ClassDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterfaceDecl(PrystParser::InterfaceDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterfaceMember(PrystParser::InterfaceMemberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGenericParams(PrystParser::GenericParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGenericArgs(PrystParser::GenericArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassMember(PrystParser::ClassMemberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOverloadParams(PrystParser::OverloadParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstructorDecl(PrystParser::ConstructorDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstructorBlock(PrystParser::ConstructorBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(PrystParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQualifiedType(PrystParser::QualifiedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturnType(PrystParser::ReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNullableType(PrystParser::NullableTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBasicType(PrystParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayType(PrystParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMapType(PrystParser::MapTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitKeyType(PrystParser::KeyTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionType(PrystParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeList(PrystParser::TypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignmentExpr(PrystParser::AssignmentExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstanceofExpr(PrystParser::InstanceofExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCastExpr(PrystParser::CastExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeofExpr(PrystParser::TypeofExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdditiveExpr(PrystParser::AdditiveExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParenExpr(PrystParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNullableChain(PrystParser::NullableChainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMethodCallExpr(PrystParser::MethodCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExpr(PrystParser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLambdaExpr(PrystParser::LambdaExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionCallExpr(PrystParser::FunctionCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemberAccessExpr(PrystParser::MemberAccessExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPostfixExpr(PrystParser::PostfixExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConditionalExpr(PrystParser::ConditionalExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogicalAndExpr(PrystParser::LogicalAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNullCoalesceExpr(PrystParser::NullCoalesceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelationalExpr(PrystParser::RelationalExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNullableMethodCallExpr(PrystParser::NullableMethodCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogicalOrExpr(PrystParser::LogicalOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrefixExpr(PrystParser::PrefixExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstructorExpr(PrystParser::ConstructorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonNullAssertExpr(PrystParser::NonNullAssertExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEqualityExpr(PrystParser::EqualityExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimary(PrystParser::PrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringInterpolation(PrystParser::StringInterpolationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitChainedCall(PrystParser::ChainedCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringLiteral(PrystParser::StringLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLambdaParams(PrystParser::LambdaParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArguments(PrystParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMapEntry(PrystParser::MapEntryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMapKey(PrystParser::MapKeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitErrorMember(PrystParser::ErrorMemberContext *ctx) override {
    return visitChildren(ctx);
  }


};

