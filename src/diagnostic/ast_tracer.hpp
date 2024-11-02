#pragma once

#include "antlr4-runtime.h"
#include "../generated/PrystBaseVisitor.h"
#include <iostream>
#include <string>

class ASTTracer : public PrystBaseVisitor {
public:
    virtual std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    virtual std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    virtual std::any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    virtual std::any visitExpression(PrystParser::ExpressionContext* ctx) override;
    virtual std::any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    virtual std::any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    virtual std::any visitEquality(PrystParser::EqualityContext* ctx) override;
    virtual std::any visitComparison(PrystParser::ComparisonContext* ctx) override;
    virtual std::any visitAddition(PrystParser::AdditionContext* ctx) override;
    virtual std::any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    virtual std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    virtual std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;

private:
    int indentLevel = 0;
    std::string getIndent() const { return std::string(indentLevel * 2, ' '); }
};
