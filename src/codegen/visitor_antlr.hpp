#pragma once

#include "visitor_base.hpp"
#include "../generated/PrystParserBaseVisitor.h"
#include <any>
#include <llvm/IR/Type.h>
#include <unordered_map>
#include <string>

class VisitorANTLR : public PrystParserVisitor, public VisitorBase {
public:
    VisitorANTLR() = default;
    virtual ~VisitorANTLR() = default;

    // Member tracking
    std::unordered_map<std::string, std::unordered_map<std::string, size_t>> classMembers;

    // Helper methods
    size_t getMemberIndex(llvm::StructType* structType, const std::string& memberName);
    void addClassMember(const std::string& className, const std::string& memberName, size_t index);

    // ANTLR visitor methods that need RTTI
    virtual std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    virtual std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    virtual std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    virtual std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    virtual std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    virtual std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    virtual std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    virtual std::any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    virtual std::any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    virtual std::any visitEquality(PrystParser::EqualityContext* ctx) override;
    virtual std::any visitComparison(PrystParser::ComparisonContext* ctx) override;
    virtual std::any visitAddition(PrystParser::AdditionContext* ctx) override;
    virtual std::any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    virtual std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    virtual std::any visitPostfix(PrystParser::PostfixContext* ctx) override;
    virtual std::any visitCall(PrystParser::CallContext* ctx) override;
};
