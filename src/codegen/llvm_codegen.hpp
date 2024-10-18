// src/codegen/llvm_codegen.hpp
#pragma once

#include "ast/ast.hpp"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <unordered_map>
#include <string>
#include <memory>

class LLVMCodegen : public ASTVisitor {
public:
    LLVMCodegen();

    // Generates the LLVM module for the given program
    std::unique_ptr<llvm::Module> generateModule(Program& program);

    // Visitor methods for AST nodes
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

private:
    // LLVM context
    std::unique_ptr<llvm::LLVMContext> context;

    // The module where code will be generated
    std::unique_ptr<llvm::Module> module;

    // IRBuilder for generating LLVM instructions
    std::unique_ptr<llvm::IRBuilder<>> builder;

    // Symbol table mapping variable names to LLVM values
    std::unordered_map<std::string, llvm::Value*> namedValues;

    // Holds the last computed value
    llvm::Value* lastValue;

    // Helper method to get the LLVM type corresponding to a type name
    llvm::Type* getLLVMType(const std::string& typeName);
};
