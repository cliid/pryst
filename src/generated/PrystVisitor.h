
// Generated from /home/ubuntu/pryst/Pryst.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PrystParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by PrystParser.
 */
class  PrystVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by PrystParser.
   */
    virtual std::any visitProgram(PrystParser::ProgramContext *context) = 0;

    virtual std::any visitDeclaration(PrystParser::DeclarationContext *context) = 0;

    virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *context) = 0;

    virtual std::any visitNamedFunction(PrystParser::NamedFunctionContext *context) = 0;

    virtual std::any visitLambdaFunction(PrystParser::LambdaFunctionContext *context) = 0;

    virtual std::any visitVariableDecl(PrystParser::VariableDeclContext *context) = 0;

    virtual std::any visitClassDeclaration(PrystParser::ClassDeclarationContext *context) = 0;

    virtual std::any visitClassBody(PrystParser::ClassBodyContext *context) = 0;

    virtual std::any visitClassVariableDecl(PrystParser::ClassVariableDeclContext *context) = 0;

    virtual std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext *context) = 0;

    virtual std::any visitParamList(PrystParser::ParamListContext *context) = 0;

    virtual std::any visitParam(PrystParser::ParamContext *context) = 0;

    virtual std::any visitType(PrystParser::TypeContext *context) = 0;

    virtual std::any visitExprStatement(PrystParser::ExprStatementContext *context) = 0;

    virtual std::any visitIfStatement(PrystParser::IfStatementContext *context) = 0;

    virtual std::any visitWhileStatement(PrystParser::WhileStatementContext *context) = 0;

    virtual std::any visitForStatement(PrystParser::ForStatementContext *context) = 0;

    virtual std::any visitReturnStatement(PrystParser::ReturnStatementContext *context) = 0;

    virtual std::any visitBlockStatement(PrystParser::BlockStatementContext *context) = 0;

    virtual std::any visitExpression(PrystParser::ExpressionContext *context) = 0;

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

    virtual std::any visitNewExpression(PrystParser::NewExpressionContext *context) = 0;

    virtual std::any visitArguments(PrystParser::ArgumentsContext *context) = 0;

    virtual std::any visitTypeCastExpr(PrystParser::TypeCastExprContext *context) = 0;

    virtual std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext *context) = 0;

    virtual std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext *context) = 0;


};

