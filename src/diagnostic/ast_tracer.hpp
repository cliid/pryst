#pragma once

#include "antlr4-runtime.h"
#include "../generated/PrystParserBaseVisitor.h"
#include "../generated/PrystParser.h"
#include <iostream>
#include <string>
#include <any>

class ASTTracer : public PrystParserVisitor {
public:
    virtual std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    virtual std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    virtual std::any visitInferredVariableDecl(PrystParser::InferredVariableDeclContext* ctx) override;
    virtual std::any visitTypedVariableDecl(PrystParser::TypedVariableDeclContext* ctx) override;
    virtual std::any visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext* ctx) override;
    virtual std::any visitClassInferredVariableDecl(PrystParser::ClassInferredVariableDeclContext* ctx) override;
    virtual std::any visitClassTypedVariableDecl(PrystParser::ClassTypedVariableDeclContext* ctx) override;
    virtual std::any visitClassConstInferredDecl(PrystParser::ClassConstInferredDeclContext* ctx) override;
    virtual std::any visitClassConstTypedDecl(PrystParser::ClassConstTypedDeclContext* ctx) override;
    virtual std::any visitExpression(PrystParser::ExpressionContext* ctx) override;
    virtual std::any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    virtual std::any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    virtual std::any visitEquality(PrystParser::EqualityContext* ctx) override;
    virtual std::any visitComparison(PrystParser::ComparisonContext* ctx) override;
    virtual std::any visitAddition(PrystParser::AdditionContext* ctx) override;
    virtual std::any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    virtual std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    virtual std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    virtual std::any visitNamedFunction(PrystParser::NamedFunctionContext* ctx) override;
    virtual std::any visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) override;
    virtual std::any visitParenthesizedCast(PrystParser::ParenthesizedCastContext* ctx) override;
    virtual std::any visitConstructorCast(PrystParser::ConstructorCastContext* ctx) override;
    virtual std::any visitSimpleString(PrystParser::SimpleStringContext* ctx) override;

private:
    int indentLevel = 0;
    std::string getIndent() const { return std::string(indentLevel * 2, ' '); }
};
