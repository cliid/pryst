#pragma once

#include "PrystBaseVisitor.h"
#include <antlr4-runtime/support/Any.h>
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
    antlrcpp::Any visitProgram(PrystParser::ProgramContext* ctx) override;
    antlrcpp::Any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    antlrcpp::Any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    antlrcpp::Any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    antlrcpp::Any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    antlrcpp::Any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) override;
    antlrcpp::Any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;
    antlrcpp::Any visitParamList(PrystParser::ParamListContext* ctx) override;
    antlrcpp::Any visitParam(PrystParser::ParamContext* ctx) override;
    antlrcpp::Any visitType(PrystParser::TypeContext* ctx) override;
    antlrcpp::Any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    antlrcpp::Any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    antlrcpp::Any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    antlrcpp::Any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    antlrcpp::Any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    antlrcpp::Any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    antlrcpp::Any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    antlrcpp::Any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    antlrcpp::Any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    antlrcpp::Any visitEquality(PrystParser::EqualityContext* ctx) override;
    antlrcpp::Any visitComparison(PrystParser::ComparisonContext* ctx) override;
    antlrcpp::Any visitAddition(PrystParser::AdditionContext* ctx) override;
    antlrcpp::Any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    antlrcpp::Any visitUnary(PrystParser::UnaryContext* ctx) override;
    antlrcpp::Any visitPostfix(PrystParser::PostfixContext* ctx) override;
    antlrcpp::Any visitCall(PrystParser::CallContext* ctx) override;
    antlrcpp::Any visitCallSuffix(PrystParser::CallSuffixContext* ctx) override;
    antlrcpp::Any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    antlrcpp::Any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;
    antlrcpp::Any visitArguments(PrystParser::ArgumentsContext* ctx) override;

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
    llvm::Function* declareBoolToStr();
};
