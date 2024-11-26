
// Generated from /home/ubuntu/pryst-workspace/pryst-cpp/src/PrystParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "PrystParser.h"


namespace pryst {

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

    virtual std::any visitModuleDecl(PrystParser::ModuleDeclContext *context) = 0;

    virtual std::any visitImportDecl(PrystParser::ImportDeclContext *context) = 0;

    virtual std::any visitImportPath(PrystParser::ImportPathContext *context) = 0;

    virtual std::any visitDeclaration(PrystParser::DeclarationContext *context) = 0;

    virtual std::any visitErrorDecl(PrystParser::ErrorDeclContext *context) = 0;

    virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *context) = 0;

    virtual std::any visitParameters(PrystParser::ParametersContext *context) = 0;

    virtual std::any visitParameter(PrystParser::ParameterContext *context) = 0;

    virtual std::any visitDefaultParam(PrystParser::DefaultParamContext *context) = 0;

    virtual std::any visitLiteral(PrystParser::LiteralContext *context) = 0;

    virtual std::any visitBlock(PrystParser::BlockContext *context) = 0;

    virtual std::any visitStatement(PrystParser::StatementContext *context) = 0;

    virtual std::any visitVarDecl(PrystParser::VarDeclContext *context) = 0;

    virtual std::any visitIdentifierList(PrystParser::IdentifierListContext *context) = 0;

    virtual std::any visitAssignment(PrystParser::AssignmentContext *context) = 0;

    virtual std::any visitIfStmt(PrystParser::IfStmtContext *context) = 0;

    virtual std::any visitWhileStmt(PrystParser::WhileStmtContext *context) = 0;

    virtual std::any visitForStmt(PrystParser::ForStmtContext *context) = 0;

    virtual std::any visitReturnStmt(PrystParser::ReturnStmtContext *context) = 0;

    virtual std::any visitTryStmt(PrystParser::TryStmtContext *context) = 0;

    virtual std::any visitCatchClause(PrystParser::CatchClauseContext *context) = 0;

    virtual std::any visitBreakStmt(PrystParser::BreakStmtContext *context) = 0;

    virtual std::any visitContinueStmt(PrystParser::ContinueStmtContext *context) = 0;

    virtual std::any visitPrintStmt(PrystParser::PrintStmtContext *context) = 0;

    virtual std::any visitExpressionStmt(PrystParser::ExpressionStmtContext *context) = 0;

    virtual std::any visitClassDecl(PrystParser::ClassDeclContext *context) = 0;

    virtual std::any visitInterfaceDecl(PrystParser::InterfaceDeclContext *context) = 0;

    virtual std::any visitInterfaceMember(PrystParser::InterfaceMemberContext *context) = 0;

    virtual std::any visitGenericParams(PrystParser::GenericParamsContext *context) = 0;

    virtual std::any visitGenericArgs(PrystParser::GenericArgsContext *context) = 0;

    virtual std::any visitClassMember(PrystParser::ClassMemberContext *context) = 0;

    virtual std::any visitOverloadParams(PrystParser::OverloadParamsContext *context) = 0;

    virtual std::any visitConstructorDecl(PrystParser::ConstructorDeclContext *context) = 0;

    virtual std::any visitConstructorBlock(PrystParser::ConstructorBlockContext *context) = 0;

    virtual std::any visitType(PrystParser::TypeContext *context) = 0;

    virtual std::any visitTypeRest(PrystParser::TypeRestContext *context) = 0;

    virtual std::any visitPrimaryType(PrystParser::PrimaryTypeContext *context) = 0;

    virtual std::any visitQualifiedType(PrystParser::QualifiedTypeContext *context) = 0;

    virtual std::any visitReturnType(PrystParser::ReturnTypeContext *context) = 0;

    virtual std::any visitNullableType(PrystParser::NullableTypeContext *context) = 0;

    virtual std::any visitBasicType(PrystParser::BasicTypeContext *context) = 0;

    virtual std::any visitArrayType(PrystParser::ArrayTypeContext *context) = 0;

    virtual std::any visitMapType(PrystParser::MapTypeContext *context) = 0;

    virtual std::any visitKeyType(PrystParser::KeyTypeContext *context) = 0;

    virtual std::any visitFunctionType(PrystParser::FunctionTypeContext *context) = 0;

    virtual std::any visitTypeList(PrystParser::TypeListContext *context) = 0;

    virtual std::any visitAssignmentExpr(PrystParser::AssignmentExprContext *context) = 0;

    virtual std::any visitInstanceofExpr(PrystParser::InstanceofExprContext *context) = 0;

    virtual std::any visitCastExpr(PrystParser::CastExprContext *context) = 0;

    virtual std::any visitTypeofExpr(PrystParser::TypeofExprContext *context) = 0;

    virtual std::any visitAdditiveExpr(PrystParser::AdditiveExprContext *context) = 0;

    virtual std::any visitParenExpr(PrystParser::ParenExprContext *context) = 0;

    virtual std::any visitNullableChain(PrystParser::NullableChainContext *context) = 0;

    virtual std::any visitMethodCallExpr(PrystParser::MethodCallExprContext *context) = 0;

    virtual std::any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext *context) = 0;

    virtual std::any visitPrimaryExpr(PrystParser::PrimaryExprContext *context) = 0;

    virtual std::any visitLambdaExpr(PrystParser::LambdaExprContext *context) = 0;

    virtual std::any visitFunctionCallExpr(PrystParser::FunctionCallExprContext *context) = 0;

    virtual std::any visitMemberAccessExpr(PrystParser::MemberAccessExprContext *context) = 0;

    virtual std::any visitPostfixExpr(PrystParser::PostfixExprContext *context) = 0;

    virtual std::any visitConditionalExpr(PrystParser::ConditionalExprContext *context) = 0;

    virtual std::any visitLogicalAndExpr(PrystParser::LogicalAndExprContext *context) = 0;

    virtual std::any visitNullCoalesceExpr(PrystParser::NullCoalesceExprContext *context) = 0;

    virtual std::any visitRelationalExpr(PrystParser::RelationalExprContext *context) = 0;

    virtual std::any visitNullableMethodCallExpr(PrystParser::NullableMethodCallExprContext *context) = 0;

    virtual std::any visitLogicalOrExpr(PrystParser::LogicalOrExprContext *context) = 0;

    virtual std::any visitPrefixExpr(PrystParser::PrefixExprContext *context) = 0;

    virtual std::any visitConstructorExpr(PrystParser::ConstructorExprContext *context) = 0;

    virtual std::any visitNonNullAssertExpr(PrystParser::NonNullAssertExprContext *context) = 0;

    virtual std::any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext *context) = 0;

    virtual std::any visitEqualityExpr(PrystParser::EqualityExprContext *context) = 0;

    virtual std::any visitPrimary(PrystParser::PrimaryContext *context) = 0;

    virtual std::any visitStringInterpolation(PrystParser::StringInterpolationContext *context) = 0;

    virtual std::any visitChainedCall(PrystParser::ChainedCallContext *context) = 0;

    virtual std::any visitStringLiteral(PrystParser::StringLiteralContext *context) = 0;

    virtual std::any visitLambdaParams(PrystParser::LambdaParamsContext *context) = 0;

    virtual std::any visitArguments(PrystParser::ArgumentsContext *context) = 0;

    virtual std::any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext *context) = 0;

    virtual std::any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext *context) = 0;

    virtual std::any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext *context) = 0;

    virtual std::any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext *context) = 0;

    virtual std::any visitMapEntry(PrystParser::MapEntryContext *context) = 0;

    virtual std::any visitMapKey(PrystParser::MapKeyContext *context) = 0;

    virtual std::any visitErrorField(PrystParser::ErrorFieldContext *context) = 0;

    virtual std::any visitErrorMethod(PrystParser::ErrorMethodContext *context) = 0;

    virtual std::any visitErrorChainField(PrystParser::ErrorChainFieldContext *context) = 0;


};

}  // namespace pryst
