
// Generated from /Users/cliid/dev/pryst/Pryst.g4 by ANTLR 4.13.1

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

    virtual std::any visitVariableDecl(PrystParser::VariableDeclContext *context) = 0;

    virtual std::any visitClassDeclaration(PrystParser::ClassDeclarationContext *context) = 0;

    virtual std::any visitClassMember(PrystParser::ClassMemberContext *context) = 0;

    virtual std::any visitParamList(PrystParser::ParamListContext *context) = 0;

    virtual std::any visitParam(PrystParser::ParamContext *context) = 0;

    virtual std::any visitType(PrystParser::TypeContext *context) = 0;

    virtual std::any visitStatement(PrystParser::StatementContext *context) = 0;

    virtual std::any visitExpressionStmt(PrystParser::ExpressionStmtContext *context) = 0;

    virtual std::any visitIfStmt(PrystParser::IfStmtContext *context) = 0;

    virtual std::any visitWhileStmt(PrystParser::WhileStmtContext *context) = 0;

    virtual std::any visitForStmt(PrystParser::ForStmtContext *context) = 0;

    virtual std::any visitReturnStmt(PrystParser::ReturnStmtContext *context) = 0;

    virtual std::any visitBlock(PrystParser::BlockContext *context) = 0;

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

    virtual std::any visitCall(PrystParser::CallContext *context) = 0;

    virtual std::any visitCallSuffix(PrystParser::CallSuffixContext *context) = 0;

    virtual std::any visitPrimary(PrystParser::PrimaryContext *context) = 0;

    virtual std::any visitNewExpression(PrystParser::NewExpressionContext *context) = 0;

    virtual std::any visitArguments(PrystParser::ArgumentsContext *context) = 0;


};

