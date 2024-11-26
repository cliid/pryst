
// Generated from /home/ubuntu/pryst-workspace/pryst-cpp/src/PrystParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "PrystParserVisitor.h"


namespace pryst {

/**
 * This class provides an empty implementation of PrystParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PrystParserBaseVisitor : public PrystParserVisitor {
public:

  virtual std::any visitProgram(PrystParser::ProgramContext *ctx) override {
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

  virtual std::any visitDeclaration(PrystParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitErrorDecl(PrystParser::ErrorDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameters(PrystParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(PrystParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefaultParam(PrystParser::DefaultParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(PrystParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(PrystParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(PrystParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(PrystParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierList(PrystParser::IdentifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(PrystParser::AssignmentContext *ctx) override {
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

  virtual std::any visitTryStmt(PrystParser::TryStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCatchClause(PrystParser::CatchClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStmt(PrystParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStmt(PrystParser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrintStmt(PrystParser::PrintStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStmt(PrystParser::ExpressionStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDecl(PrystParser::ClassDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterfaceDecl(PrystParser::InterfaceDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterfaceMember(PrystParser::InterfaceMemberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericParams(PrystParser::GenericParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericArgs(PrystParser::GenericArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassMember(PrystParser::ClassMemberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOverloadParams(PrystParser::OverloadParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstructorDecl(PrystParser::ConstructorDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstructorBlock(PrystParser::ConstructorBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(PrystParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeRest(PrystParser::TypeRestContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryType(PrystParser::PrimaryTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedType(PrystParser::QualifiedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnType(PrystParser::ReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullableType(PrystParser::NullableTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicType(PrystParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(PrystParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapType(PrystParser::MapTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyType(PrystParser::KeyTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionType(PrystParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeList(PrystParser::TypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentExpr(PrystParser::AssignmentExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInstanceofExpr(PrystParser::InstanceofExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCastExpr(PrystParser::CastExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeofExpr(PrystParser::TypeofExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpr(PrystParser::AdditiveExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(PrystParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullableChain(PrystParser::NullableChainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodCallExpr(PrystParser::MethodCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpr(PrystParser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaExpr(PrystParser::LambdaExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCallExpr(PrystParser::FunctionCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberAccessExpr(PrystParser::MemberAccessExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostfixExpr(PrystParser::PostfixExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalExpr(PrystParser::ConditionalExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpr(PrystParser::LogicalAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullCoalesceExpr(PrystParser::NullCoalesceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpr(PrystParser::RelationalExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullableMethodCallExpr(PrystParser::NullableMethodCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpr(PrystParser::LogicalOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefixExpr(PrystParser::PrefixExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstructorExpr(PrystParser::ConstructorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonNullAssertExpr(PrystParser::NonNullAssertExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpr(PrystParser::EqualityExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary(PrystParser::PrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringInterpolation(PrystParser::StringInterpolationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChainedCall(PrystParser::ChainedCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiteral(PrystParser::StringLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaParams(PrystParser::LambdaParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(PrystParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapEntry(PrystParser::MapEntryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapKey(PrystParser::MapKeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitErrorField(PrystParser::ErrorFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitErrorMethod(PrystParser::ErrorMethodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitErrorChainField(PrystParser::ErrorChainFieldContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace pryst
