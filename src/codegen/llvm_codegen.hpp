#pragma once

#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "type_registry.hpp"
#include "class_info.hpp"
#include "utils/debug.hpp"
#include <memory>
#include <string>
#include <map>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

namespace pryst {

class LLVMCodegen : public PrystBaseVisitor {
public:
    LLVMCodegen() : typeRegistry(nullptr) {}
    virtual ~LLVMCodegen() = default;

    std::unique_ptr<llvm::Module> generateModule(PrystParser::ProgramContext* ctx);

    // Program structure and declarations
    std::any visitProgram(PrystParser::ProgramContext *ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext *ctx) override;
    std::any visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext *ctx) override;
    std::any visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext *ctx) override;
    std::any visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext *ctx) override;
    std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext *ctx) override;
    std::any visitModuleDecl(PrystParser::ModuleDeclContext *ctx) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext *ctx) override;
    std::any visitImportPath(PrystParser::ImportPathContext *ctx) override;

    // Functions and Classes
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) override;
    std::any visitNamedFunction(PrystParser::NamedFunctionContext *ctx) override;
    std::any visitLambdaFunction(PrystParser::LambdaFunctionContext *ctx) override;
    std::any visitFunctionBody(PrystParser::FunctionBodyContext *ctx) override;
    std::any visitParamList(PrystParser::ParamListContext *ctx) override;
    std::any visitParam(PrystParser::ParamContext *ctx) override;
    std::any visitParamTypeList(PrystParser::ParamTypeListContext *ctx) override;
    std::any visitClassDeclaration(PrystParser::ClassDeclarationContext *ctx) override;
    std::any visitClassBody(PrystParser::ClassBodyContext *ctx) override;
    std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext *ctx) override;
    std::any visitClassMemberDecl(PrystParser::ClassMemberDeclContext *ctx) override;

    // Expressions
    std::any visitExpression(PrystParser::ExpressionContext *ctx) override;
    std::any visitAssignment(PrystParser::AssignmentContext *ctx) override;
    std::any visitLogicOr(PrystParser::LogicOrContext *ctx) override;
    std::any visitLogicAnd(PrystParser::LogicAndContext *ctx) override;
    std::any visitEquality(PrystParser::EqualityContext *ctx) override;
    std::any visitComparison(PrystParser::ComparisonContext *ctx) override;
    std::any visitAddition(PrystParser::AdditionContext *ctx) override;
    std::any visitMultiplication(PrystParser::MultiplicationContext *ctx) override;
    std::any visitUnary(PrystParser::UnaryContext *ctx) override;
    std::any visitPostfix(PrystParser::PostfixContext *ctx) override;
    std::any visitCall(PrystParser::CallContext *ctx) override;
    std::any visitPrimary(PrystParser::PrimaryContext *ctx) override;

    // Statements
    std::any visitBlockStatement(PrystParser::BlockStatementContext *ctx) override;
    std::any visitExprStatement(PrystParser::ExprStatementContext *ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext *ctx) override;
    std::any visitWhileStatement(PrystParser::WhileStatementContext *ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext *ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext *ctx) override;
    std::any visitTryStatement(PrystParser::TryStatementContext *ctx) override;
    std::any visitPrintStatement(PrystParser::PrintStatementContext *ctx) override;

private:
    // Helper methods
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, const std::string& varName, llvm::Type* type);
    void declarePrintFunctions();

    // Private members
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<LLVMTypeRegistry> typeRegistry;
    std::map<std::string, llvm::Value*> namedValues;
    llvm::Function* currentFunction;
};

} // namespace pryst
