#pragma once

#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "symbol_table.hpp"
#include "type_info.hpp"
#include "module_loader.hpp"
#include <memory>
#include <string>
#include <vector>

namespace pryst {

class SemanticAnalyzer : public PrystBaseVisitor {
public:
    SemanticAnalyzer();
    virtual ~SemanticAnalyzer() = default;

    // Program and declarations
    std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext* ctx) override;
    std::any visitModuleDecl(PrystParser::ModuleDeclContext* ctx) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext* ctx) override;
    std::any visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext* ctx) override;
    std::any visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext* ctx) override;
    std::any visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext* ctx) override;
    std::any visitImportPath(PrystParser::ImportPathContext* ctx) override;
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    std::any visitNamedFunction(PrystParser::NamedFunctionContext* ctx) override;
    std::any visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) override;
    std::any visitFunctionBody(PrystParser::FunctionBodyContext* ctx) override;
    std::any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    std::any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;

    // Parameters and types
    std::any visitParamList(PrystParser::ParamListContext* ctx) override;
    std::any visitParam(PrystParser::ParamContext* ctx) override;
    std::any visitParamTypeList(PrystParser::ParamTypeListContext* ctx) override;
    std::any visitFloatType(PrystParser::FloatTypeContext* ctx) override;
    std::any visitLambdaType(PrystParser::LambdaTypeContext* ctx) override;
    std::any visitArrayType(PrystParser::ArrayTypeContext* ctx) override;
    std::any visitStrType(PrystParser::StrTypeContext* ctx) override;
    std::any visitIntType(PrystParser::IntTypeContext* ctx) override;
    std::any visitVoidType(PrystParser::VoidTypeContext* ctx) override;
    std::any visitIdentifierType(PrystParser::IdentifierTypeContext* ctx) override;
    std::any visitFunctionType(PrystParser::FunctionTypeContext* ctx) override;
    std::any visitBoolType(PrystParser::BoolTypeContext* ctx) override;

    // Statements
    std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    std::any visitPrintStatement(PrystParser::PrintStatementContext* ctx) override;

    // Expressions
    std::any visitExpression(PrystParser::ExpressionContext* ctx) override;
    std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    std::any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    std::any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    std::any visitEquality(PrystParser::EqualityContext* ctx) override;
    std::any visitComparison(PrystParser::ComparisonContext* ctx) override;
    std::any visitAddition(PrystParser::AdditionContext* ctx) override;
    std::any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    std::any visitPostfix(PrystParser::PostfixContext* ctx) override;
    std::any visitSuffix(PrystParser::SuffixContext* ctx) override;
    std::any visitCallSuffix(PrystParser::CallSuffixContext* ctx) override;
    std::any visitMemberSuffix(PrystParser::MemberSuffixContext* ctx) override;
    std::any visitCall(PrystParser::CallContext* ctx) override;
    std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    std::any visitQualifiedIdentifier(PrystParser::QualifiedIdentifierContext* ctx) override;
    std::any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;
    std::any visitArguments(PrystParser::ArgumentsContext* ctx) override;
    std::any visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx) override;
    std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) override;
    std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) override;

private:
    SymbolTable symbolTable;
    ModuleLoader moduleLoader;
    std::string currentFunction;
    bool inLoop;
    std::vector<std::string> currentNamespace;
    std::string currentModule;

    std::string getExpressionType(antlr4::tree::ParseTree* ctx);
    bool areTypesCompatible(const std::string& expected, const std::string& actual);
    std::string resolveType(const std::string& type);
    void checkVariableUsage(const std::string& name, antlr4::tree::ParseTree* ctx);
};

} // namespace pryst
