#pragma once

#include "../generated/PrystParserBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "type_registry.hpp"
#include "type_metadata.hpp"
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

// Forward declarations
class TypeMetadata;

class LLVMCodegen : public PrystParserBaseVisitor {
public:
    LLVMCodegen() {
        initializeModule();
    }
    virtual ~LLVMCodegen() = default;

    // Public accessors
    llvm::LLVMContext* getContext() const { return context_.get(); }
    llvm::Module* getModule() const { return module_.get(); }
    llvm::IRBuilder<>* getBuilder() const { return builder_.get(); }
    LLVMTypeRegistry* getTypeRegistry() const { return typeRegistry_.get(); }
    void registerFunction(const std::string& name, llvm::Function* func) {
        module_->getOrInsertFunction(name, func->getFunctionType());
    }

    // Reflection API methods
    llvm::Value* generateGetType(llvm::Value* value);
    llvm::Value* generateIsInstance(llvm::Value* value, const std::string& typeName);
    TypeInfoPtr getTypeInfo(llvm::Value* value) const;
    void attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo);
    llvm::Type* getLLVMTypeFromTypeInfo(TypeInfoPtr typeInfo) const;

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
    std::any visitUsingDecl(PrystParser::GlobalUsingDeclContext *ctx) override;
    std::any visitStringLiteral(PrystParser::StringLiteralContext *ctx) override;
    std::any visitStringPart(PrystParser::StringPartContext *ctx) override;
    std::any visitTryCatchStatement(PrystParser::TryCatchStatementContext *ctx) override;

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
    std::any visitClassVariableDecl(PrystParser::ClassVariableDeclContext *ctx) override;
    std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext *ctx) override;

    // Type conversions
    std::any visitTypeCastExpr(PrystParser::TypeCastExprContext *ctx) override;
    std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext *ctx) override;
    std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext *ctx) override;

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
    std::any visitTryCatchStatement(PrystParser::TryCatchStatementContext *ctx) override;
    std::any visitPrintStatement(PrystParser::PrintStatementContext *ctx) override;

private:
    // Helper methods
    void initializeModule();
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, const std::string& varName, llvm::Type* type);
    void declarePrintFunctions();

    // Built-in function declarations
    llvm::Function* declareBoolToStr();
    llvm::Function* declareIntToStr();
    llvm::Function* declareFloatToStr();
    llvm::Function* declareMathSqrt();
    llvm::Function* declareMathPow();
    llvm::Function* declareMathAbs();
    llvm::Function* declareStrConcat();
    llvm::Function* declareStrSubstr();
    llvm::Function* declareToString();
    llvm::Function* declareToInt();
    llvm::Function* declareToFloat();
    llvm::Function* declareMalloc();

    // Private members
    std::unique_ptr<llvm::LLVMContext> context_;
    std::unique_ptr<llvm::Module> module_;
    std::unique_ptr<llvm::IRBuilder<>> builder_;
    std::unique_ptr<LLVMTypeRegistry> typeRegistry_;
    std::unique_ptr<TypeMetadata> typeMetadata_;
    std::map<std::string, llvm::Value*> namedValues_;
    std::map<std::string, llvm::Function*> functions_;
    std::string currentNamespace_;
    std::string currentModule_;
    std::set<std::string> importedModules_;
    llvm::Function* currentFunction_;
    llvm::Function* getTypeIdFunc_;
};

} // namespace pryst
