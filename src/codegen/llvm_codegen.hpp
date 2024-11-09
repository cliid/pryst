#pragma once

#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "../semantic/module_loader.hpp"
#include "../semantic/symbol_table.hpp"
#include "type_registry.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <memory>
#include <string>
#include <vector>

namespace pryst {

class LLVMCodegen : public PrystBaseVisitor {
public:
    LLVMCodegen();
    std::unique_ptr<llvm::Module> generateModule(PrystParser::ProgramContext* ctx);

    // Program structure
    std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext* ctx) override;
    std::any visitModuleDecl(PrystParser::ModuleDeclContext* ctx) override;
    std::any visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext* ctx) override;
    std::any visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext* ctx) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext* ctx) override;
    std::any visitImportPath(PrystParser::ImportPathContext* ctx) override;
    std::any visitUsingDecl(PrystParser::UsingDeclContext* ctx) override;
    std::any visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext* ctx) override;

    // Functions and lambdas
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    std::any visitFunctionBody(PrystParser::FunctionBodyContext* ctx) override;
    std::any visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) override;
    std::any visitNamedFunction(PrystParser::NamedFunctionContext* ctx) override;
    std::any visitParamList(PrystParser::ParamListContext* ctx) override;
    std::any visitParam(PrystParser::ParamContext* ctx) override;

    // Types
    std::any visitIntType(PrystParser::IntTypeContext* ctx) override;
    std::any visitFloatType(PrystParser::FloatTypeContext* ctx) override;
    std::any visitBoolType(PrystParser::BoolTypeContext* ctx) override;
    std::any visitStrType(PrystParser::StrTypeContext* ctx) override;
    std::any visitVoidType(PrystParser::VoidTypeContext* ctx) override;
    std::any visitArrayType(PrystParser::ArrayTypeContext* ctx) override;
    std::any visitFunctionType(PrystParser::FunctionTypeContext* ctx) override;
    std::any visitIdentifierType(PrystParser::IdentifierTypeContext* ctx) override;

    // Expressions
    std::any visitAddition(PrystParser::AdditionContext* ctx) override;
    std::any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    std::any visitComparison(PrystParser::ComparisonContext* ctx) override;
    std::any visitEquality(PrystParser::EqualityContext* ctx) override;
    std::any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    std::any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    std::any visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx) override;
    std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) override;
    std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) override;

    // Statements
    std::any visitPrintStatement(PrystParser::PrintStatementContext* ctx) override;
    std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    std::any visitTryStatement(PrystParser::TryStatementContext* ctx) override;
    std::any visitTryCatchStatement(PrystParser::TryCatchStatementContext* ctx) override;

    // Classes and objects
    std::any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    std::any visitClassBody(PrystParser::ClassBodyContext* ctx) override;
    std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;
    std::any visitClassTypedVariableDecl(PrystParser::ClassTypedVariableDeclContext* ctx) override;
    std::any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;

    // Member access and calls
    std::any visitCall(PrystParser::CallContext* ctx) override;
    std::any visitCallSuffix(PrystParser::CallSuffixContext* ctx) override;
    std::any visitMemberSuffix(PrystParser::MemberSuffixContext* ctx) override;
    std::any visitPostfix(PrystParser::PostfixContext* ctx) override;
    std::any visitSuffix(PrystParser::SuffixContext* ctx) override;
    std::any visitArguments(PrystParser::ArgumentsContext* ctx) override;

    // Variables and assignments
    std::any visitInferredVariableDecl(PrystParser::InferredVariableDeclContext* ctx) override;
    std::any visitTypedVariableDecl(PrystParser::TypedVariableDeclContext* ctx) override;
    std::any visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext* ctx) override;
    std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;

    // String handling
    std::any visitSimpleString(PrystParser::SimpleStringContext* ctx) override;
    std::any visitStringContent(PrystParser::StringContentContext* ctx) override;
    std::any visitEscapeSeq(PrystParser::EscapeSeqContext* ctx) override;

    // Qualified identifiers
    std::any visitQualifiedIdentifier(PrystParser::QualifiedIdentifierContext* ctx) override;

private:
    void declarePrintFunctions();
    void declareTypeConversionFunctions();
    void declareMathFunctions();

    // Add declarations for builtin functions
    llvm::Function* declareBoolToStr();
    llvm::Function* declareIntToStr();
    llvm::Function* declareFloatToStr();
    llvm::Function* declareStrToBool();
    llvm::Function* declareStrToInt();
    llvm::Function* declareStrToFloat();

    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    TypeRegistry typeRegistry;
    SymbolTable symbolTable;
    ModuleLoader moduleLoader;

    std::string currentFunction;
    std::string currentModule;
    std::vector<std::string> currentNamespace;
    int lambdaCounter = 0;
};

} // namespace pryst
