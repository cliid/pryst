
// Generated from src/PrystParser.g4 by ANTLR 4.7.2

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
    virtual antlrcpp::Any visitProgram(PrystParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitModuleDecl(PrystParser::ModuleDeclContext *context) = 0;

    virtual antlrcpp::Any visitImportDecl(PrystParser::ImportDeclContext *context) = 0;

    virtual antlrcpp::Any visitImportPath(PrystParser::ImportPathContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(PrystParser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitErrorDecl(PrystParser::ErrorDeclContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDecl(PrystParser::FunctionDeclContext *context) = 0;

    virtual antlrcpp::Any visitParameters(PrystParser::ParametersContext *context) = 0;

    virtual antlrcpp::Any visitParameter(PrystParser::ParameterContext *context) = 0;

    virtual antlrcpp::Any visitDefaultParam(PrystParser::DefaultParamContext *context) = 0;

    virtual antlrcpp::Any visitBlock(PrystParser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitStatement(PrystParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitVarDecl(PrystParser::VarDeclContext *context) = 0;

    virtual antlrcpp::Any visitIdentifierList(PrystParser::IdentifierListContext *context) = 0;

    virtual antlrcpp::Any visitAssignment(PrystParser::AssignmentContext *context) = 0;

    virtual antlrcpp::Any visitIfStmt(PrystParser::IfStmtContext *context) = 0;

    virtual antlrcpp::Any visitWhileStmt(PrystParser::WhileStmtContext *context) = 0;

    virtual antlrcpp::Any visitForStmt(PrystParser::ForStmtContext *context) = 0;

    virtual antlrcpp::Any visitReturnStmt(PrystParser::ReturnStmtContext *context) = 0;

    virtual antlrcpp::Any visitTryStmt(PrystParser::TryStmtContext *context) = 0;

    virtual antlrcpp::Any visitBreakStmt(PrystParser::BreakStmtContext *context) = 0;

    virtual antlrcpp::Any visitContinueStmt(PrystParser::ContinueStmtContext *context) = 0;

    virtual antlrcpp::Any visitPrintStmt(PrystParser::PrintStmtContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStmt(PrystParser::ExpressionStmtContext *context) = 0;

    virtual antlrcpp::Any visitClassDecl(PrystParser::ClassDeclContext *context) = 0;

    virtual antlrcpp::Any visitInterfaceDecl(PrystParser::InterfaceDeclContext *context) = 0;

    virtual antlrcpp::Any visitInterfaceMember(PrystParser::InterfaceMemberContext *context) = 0;

    virtual antlrcpp::Any visitGenericParams(PrystParser::GenericParamsContext *context) = 0;

    virtual antlrcpp::Any visitGenericArgs(PrystParser::GenericArgsContext *context) = 0;

    virtual antlrcpp::Any visitClassMember(PrystParser::ClassMemberContext *context) = 0;

    virtual antlrcpp::Any visitOverloadParams(PrystParser::OverloadParamsContext *context) = 0;

    virtual antlrcpp::Any visitConstructorDecl(PrystParser::ConstructorDeclContext *context) = 0;

    virtual antlrcpp::Any visitConstructorBlock(PrystParser::ConstructorBlockContext *context) = 0;

    virtual antlrcpp::Any visitType(PrystParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitQualifiedType(PrystParser::QualifiedTypeContext *context) = 0;

    virtual antlrcpp::Any visitReturnType(PrystParser::ReturnTypeContext *context) = 0;

    virtual antlrcpp::Any visitNullableType(PrystParser::NullableTypeContext *context) = 0;

    virtual antlrcpp::Any visitBasicType(PrystParser::BasicTypeContext *context) = 0;

    virtual antlrcpp::Any visitArrayType(PrystParser::ArrayTypeContext *context) = 0;

    virtual antlrcpp::Any visitMapType(PrystParser::MapTypeContext *context) = 0;

    virtual antlrcpp::Any visitKeyType(PrystParser::KeyTypeContext *context) = 0;

    virtual antlrcpp::Any visitFunctionType(PrystParser::FunctionTypeContext *context) = 0;

    virtual antlrcpp::Any visitTypeList(PrystParser::TypeListContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentExpr(PrystParser::AssignmentExprContext *context) = 0;

    virtual antlrcpp::Any visitInstanceofExpr(PrystParser::InstanceofExprContext *context) = 0;

    virtual antlrcpp::Any visitCastExpr(PrystParser::CastExprContext *context) = 0;

    virtual antlrcpp::Any visitTypeofExpr(PrystParser::TypeofExprContext *context) = 0;

    virtual antlrcpp::Any visitAdditiveExpr(PrystParser::AdditiveExprContext *context) = 0;

    virtual antlrcpp::Any visitParenExpr(PrystParser::ParenExprContext *context) = 0;

    virtual antlrcpp::Any visitNullableChain(PrystParser::NullableChainContext *context) = 0;

    virtual antlrcpp::Any visitMethodCallExpr(PrystParser::MethodCallExprContext *context) = 0;

    virtual antlrcpp::Any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpr(PrystParser::PrimaryExprContext *context) = 0;

    virtual antlrcpp::Any visitLambdaExpr(PrystParser::LambdaExprContext *context) = 0;

    virtual antlrcpp::Any visitFunctionCallExpr(PrystParser::FunctionCallExprContext *context) = 0;

    virtual antlrcpp::Any visitMemberAccessExpr(PrystParser::MemberAccessExprContext *context) = 0;

    virtual antlrcpp::Any visitPostfixExpr(PrystParser::PostfixExprContext *context) = 0;

    virtual antlrcpp::Any visitConditionalExpr(PrystParser::ConditionalExprContext *context) = 0;

    virtual antlrcpp::Any visitLogicalAndExpr(PrystParser::LogicalAndExprContext *context) = 0;

    virtual antlrcpp::Any visitNullCoalesceExpr(PrystParser::NullCoalesceExprContext *context) = 0;

    virtual antlrcpp::Any visitRelationalExpr(PrystParser::RelationalExprContext *context) = 0;

    virtual antlrcpp::Any visitNullableMethodCallExpr(PrystParser::NullableMethodCallExprContext *context) = 0;

    virtual antlrcpp::Any visitLogicalOrExpr(PrystParser::LogicalOrExprContext *context) = 0;

    virtual antlrcpp::Any visitPrefixExpr(PrystParser::PrefixExprContext *context) = 0;

    virtual antlrcpp::Any visitConstructorExpr(PrystParser::ConstructorExprContext *context) = 0;

    virtual antlrcpp::Any visitNonNullAssertExpr(PrystParser::NonNullAssertExprContext *context) = 0;

    virtual antlrcpp::Any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext *context) = 0;

    virtual antlrcpp::Any visitEqualityExpr(PrystParser::EqualityExprContext *context) = 0;

    virtual antlrcpp::Any visitPrimary(PrystParser::PrimaryContext *context) = 0;

    virtual antlrcpp::Any visitStringInterpolation(PrystParser::StringInterpolationContext *context) = 0;

    virtual antlrcpp::Any visitChainedCall(PrystParser::ChainedCallContext *context) = 0;

    virtual antlrcpp::Any visitStringLiteral(PrystParser::StringLiteralContext *context) = 0;

    virtual antlrcpp::Any visitLambdaParams(PrystParser::LambdaParamsContext *context) = 0;

    virtual antlrcpp::Any visitArguments(PrystParser::ArgumentsContext *context) = 0;

    virtual antlrcpp::Any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext *context) = 0;

    virtual antlrcpp::Any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext *context) = 0;

    virtual antlrcpp::Any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext *context) = 0;

    virtual antlrcpp::Any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext *context) = 0;

    virtual antlrcpp::Any visitMapEntry(PrystParser::MapEntryContext *context) = 0;

    virtual antlrcpp::Any visitMapKey(PrystParser::MapKeyContext *context) = 0;

    virtual antlrcpp::Any visitErrorMember(PrystParser::ErrorMemberContext *context) = 0;


};

