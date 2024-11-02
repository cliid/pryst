#pragma once

#include <antlr4-runtime.h>
#include <tree/AbstractParseTreeVisitor.h>
#include <tree/ParseTreeVisitor.h>
#include "PrystParser.h"
#include "PrystVisitor.h"
#include "PrystBaseVisitor.h"
#include <any>

namespace antlrcpp {
    using Any = std::any;
}

// Visitor method declarations for LLVMCodegen
antlrcpp::Any visitProgram(PrystParser::ProgramContext* ctx);
antlrcpp::Any visitDeclaration(PrystParser::DeclarationContext* ctx);
antlrcpp::Any visitNamedFunction(PrystParser::NamedFunctionContext* ctx);
antlrcpp::Any visitAnonymousFunction(PrystParser::AnonymousFunctionContext* ctx);
antlrcpp::Any visitTypedAnonymousFunction(PrystParser::TypedAnonymousFunctionContext* ctx);
antlrcpp::Any visitVariableDecl(PrystParser::VariableDeclContext* ctx);
antlrcpp::Any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx);
antlrcpp::Any visitClassBody(PrystParser::ClassBodyContext* ctx);
antlrcpp::Any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx);
antlrcpp::Any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx);
antlrcpp::Any visitParamList(PrystParser::ParamListContext* ctx);
antlrcpp::Any visitSimpleParam(PrystParser::SimpleParamContext* ctx);
antlrcpp::Any visitFunctionParam(PrystParser::FunctionParamContext* ctx);
antlrcpp::Any visitBasicType(PrystParser::BasicTypeContext* ctx);
antlrcpp::Any visitArrayType(PrystParser::ArrayTypeContext* ctx);
antlrcpp::Any visitFunctionType(PrystParser::FunctionTypeContext* ctx);
antlrcpp::Any visitClassType(PrystParser::ClassTypeContext* ctx);
antlrcpp::Any visitTypeList(PrystParser::TypeListContext* ctx);
antlrcpp::Any visitExprStatement(PrystParser::ExprStatementContext* ctx);
antlrcpp::Any visitIfStatement(PrystParser::IfStatementContext* ctx);
antlrcpp::Any visitWhileStatement(PrystParser::WhileStatementContext* ctx);
antlrcpp::Any visitForStatement(PrystParser::ForStatementContext* ctx);
antlrcpp::Any visitReturnStatement(PrystParser::ReturnStatementContext* ctx);
antlrcpp::Any visitBlockStatement(PrystParser::BlockStatementContext* ctx);
antlrcpp::Any visitExpression(PrystParser::ExpressionContext* ctx);
antlrcpp::Any visitAssignment(PrystParser::AssignmentContext* ctx);
antlrcpp::Any visitLogicOr(PrystParser::LogicOrContext* ctx);
antlrcpp::Any visitLogicAnd(PrystParser::LogicAndContext* ctx);
antlrcpp::Any visitEquality(PrystParser::EqualityContext* ctx);
antlrcpp::Any visitComparison(PrystParser::ComparisonContext* ctx);
antlrcpp::Any visitAddition(PrystParser::AdditionContext* ctx);
antlrcpp::Any visitMultiplication(PrystParser::MultiplicationContext* ctx);
antlrcpp::Any visitUnary(PrystParser::UnaryContext* ctx);
antlrcpp::Any visitPostfix(PrystParser::PostfixContext* ctx);
antlrcpp::Any visitCall(PrystParser::CallContext* ctx);
antlrcpp::Any visitLiteralExpr(PrystParser::LiteralExprContext* ctx);
antlrcpp::Any visitThisExpr(PrystParser::ThisExprContext* ctx);
antlrcpp::Any visitNumberExpr(PrystParser::NumberExprContext* ctx);
antlrcpp::Any visitStringExpr(PrystParser::StringExprContext* ctx);
antlrcpp::Any visitIdentifierExpr(PrystParser::IdentifierExprContext* ctx);
antlrcpp::Any visitGroupExpr(PrystParser::GroupExprContext* ctx);
antlrcpp::Any visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx);
antlrcpp::Any visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx);
antlrcpp::Any visitSuperExpr(PrystParser::SuperExprContext* ctx);
antlrcpp::Any visitNewExpr(PrystParser::NewExprContext* ctx);
antlrcpp::Any visitAnonymousFunctionExpr(PrystParser::AnonymousFunctionExprContext* ctx);
antlrcpp::Any visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx);
antlrcpp::Any visitNewExpression(PrystParser::NewExpressionContext* ctx);
antlrcpp::Any visitArguments(PrystParser::ArgumentsContext* ctx);
