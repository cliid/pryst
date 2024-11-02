#pragma once

#include "PrystBaseVisitor.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <memory>
#include <unordered_map>

class LLVMCodegen : public PrystBaseVisitor {
public:
    LLVMCodegen();
    std::unique_ptr<llvm::Module> generateModule(PrystParser::ProgramContext* programCtx);

    // Overrides for visiting different AST nodes
    std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    std::any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    std::any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    std::any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) override;
    std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;
    std::any visitParamList(PrystParser::ParamListContext* ctx) override;
    std::any visitParam(PrystParser::ParamContext* ctx) override;
    std::any visitType(PrystParser::TypeContext* ctx) override;
    std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    std::any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    std::any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    std::any visitEquality(PrystParser::EqualityContext* ctx) override;
    std::any visitComparison(PrystParser::ComparisonContext* ctx) override;
    std::any visitAddition(PrystParser::AdditionContext* ctx) override;
    std::any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    std::any visitPostfix(PrystParser::PostfixContext* ctx) override;
    std::any visitCall(PrystParser::CallContext* ctx) override;
    std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    std::any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;
    std::any visitArguments(PrystParser::ArgumentsContext* ctx) override;

private:
    std::unordered_map<std::string, llvm::FunctionType*> functionTypes;
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;

    // Symbol tables for variables and functions
    std::unordered_map<std::string, llvm::AllocaInst*> namedValues;
    std::unordered_map<std::string, llvm::Function*> functions;

    // Class member tracking
    std::unordered_map<std::string, llvm::StructType*> classTypes;
    std::unordered_map<std::string, std::unordered_map<std::string, size_t>> memberIndices;
    std::unordered_map<std::string, std::string> classInheritance;  // Maps derived class to base class

    // Helper methods
    llvm::Type* getLLVMType(const std::string& typeName);
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, const std::string& varName, llvm::Type* type);
    size_t getMemberIndex(llvm::StructType* structType, const std::string& memberName);
    void addClassMember(const std::string& className, const std::string& memberName, size_t index);

    llvm::Value* lastValue;
    llvm::Function* currentFunction;

    llvm::Function* createMainFunction();
    llvm::Function* declarePrintf();
};
