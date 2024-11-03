#pragma once

#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

class DiagnosticVisitor : public PrystBaseVisitor {
public:
    DiagnosticVisitor() : indentLevel(0) {}

    virtual std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    virtual std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    virtual std::any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    virtual std::any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) override;
    virtual std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;
    virtual std::any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    virtual std::any visitExpression(PrystParser::ExpressionContext* ctx) override;
    virtual std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    virtual std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    virtual std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    virtual std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    virtual std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    virtual std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    virtual std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    virtual std::any visitCall(PrystParser::CallContext* ctx) override;
    virtual std::any visitCallSuffix(PrystParser::CallSuffixContext* ctx) override;
    virtual std::any visitMemberSuffix(PrystParser::MemberSuffixContext* ctx) override;
    virtual std::any visitSuffix(PrystParser::SuffixContext* ctx) override;
    virtual std::any visitPostfix(PrystParser::PostfixContext* ctx) override;
    virtual std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    virtual std::any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;

private:
    int indentLevel;
    std::string getIndent() const { return std::string(indentLevel * 2, ' '); }
    void printNode(const std::string& nodeName, const std::string& details = "") {
        std::cout << getIndent() << nodeName;
        if (!details.empty()) {
            std::cout << ": " << details;
        }
        std::cout << std::endl;
    }

    class ScopeGuard {
    public:
        ScopeGuard(int& level) : level_(level) { ++level_; }
        ~ScopeGuard() { --level_; }
    private:
        int& level_;
    };
};
