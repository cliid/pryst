#pragma once
#include "ast/ast.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

class SemanticAnalyzer : public ASTVisitor {
public:
    void analyze(Program& program);

    void visitProgram(Program& node) override;
    void visitFunctionDeclaration(FunctionDeclaration& node) override;
    void visitVariableDeclaration(VariableDeclaration& node) override;
    void visitClassDeclaration(ClassDeclaration& node) override;
    void visitBlock(Block& node) override;
    void visitExpressionStatement(ExpressionStatement& node) override;
    void visitIfStatement(IfStatement& node) override;
    void visitWhileStatement(WhileStatement& node) override;
    void visitForStatement(ForStatement& node) override;
    void visitReturnStatement(ReturnStatement& node) override;
    void visitBinaryExpression(BinaryExpression& node) override;
    void visitUnaryExpression(UnaryExpression& node) override;
    void visitLiteralExpression(LiteralExpression& node) override;
    void visitVariableExpression(VariableExpression& node) override;
    void visitCallExpression(CallExpression& node) override;
    void visitNewExpression(NewExpression& node) override;
    void visitAssignmentExpression(AssignmentExpression& node) override;
    void visitGroupingExpression(GroupingExpression& node) override;
    void visitParameter(Parameter& node) override;

    std::shared_ptr<Type> getType(const std::string& typeName) const;
    void checkTypes(const std::shared_ptr<Type>& expected, const std::shared_ptr<Type>& actual, const std::string& errorMessage) const;

private:
    SymbolTable symbolTable;
    const FunctionDeclaration* currentFunction = nullptr;
};
