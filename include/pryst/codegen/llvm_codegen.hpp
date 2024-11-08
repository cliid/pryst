#pragma once

// Include ANTLR headers first
#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "../generated/PrystLexer.h"

// Then include LLVM headers
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

// Include project headers
#include "type_registry.hpp"
#include "class_info.hpp"
#include "utils/debug.hpp"
#include <memory>
#include <string>
#include <map>
#include <any>

namespace pryst {

class LLVMCodegen : public PrystBaseVisitor {
public:
    LLVMCodegen();
    virtual ~LLVMCodegen() = default;

    // Module generation
    std::unique_ptr<llvm::Module> generateModule(PrystParser::ProgramContext* ctx);

    // Visitor methods - Part 1 (Declaration-related)
    std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    std::any visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext* ctx) override;
    std::any visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext* ctx) override;
    std::any visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext* ctx) override;
    std::any visitNamespaceDecl(PrystParser::NamespaceDeclContext* ctx) override;
    std::any visitModuleDecl(PrystParser::ModuleDeclContext* ctx) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext* ctx) override;
    std::any visitImportPath(PrystParser::ImportPathContext* ctx) override;
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    std::any visitNamedFunction(PrystParser::NamedFunctionContext* ctx) override;
    std::any visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) override;
    std::any visitFunctionBody(PrystParser::FunctionBodyContext* ctx) override;
    std::any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    std::any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    std::any visitClassBody(PrystParser::ClassBodyContext* ctx) override;
    std::any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) override;
    std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;
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

    // Visitor methods - Part 2 (Statement-related)
    std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    std::any visitPrintStatement(PrystParser::PrintStatementContext* ctx) override;
    std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;

    // Visitor methods - Part 3 (Expression-related)
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
    std::any visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx) override;
    std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) override;
    std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) override;
private:
    // Helper methods
    void declarePrintFunctions();
    llvm::Function* getFunctionProto(const std::string& name, llvm::FunctionType* type);
    llvm::Value* getVariableValue(const std::string& name);
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, const std::string& varName, llvm::Type* type);
    void createBasicBlock(const std::string& name);
    llvm::Value* createCastInstruction(llvm::Value* value, llvm::Type* destType, bool isSigned = true);

    // Member variables
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    LLVMTypeRegistry typeRegistry;
    std::map<std::string, llvm::Value*> namedValues;
    llvm::Function* currentFunction;
    std::map<std::string, llvm::Function*> printFunctions;
    std::vector<std::string> currentNamespace;
    std::string currentModule;
};

} // namespace pryst
