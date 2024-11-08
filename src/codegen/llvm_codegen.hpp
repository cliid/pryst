#pragma once

#include "../generated/PrystBaseVisitor.h"
#include "../generated/PrystParser.h"
#include "type_registry.hpp"
#include "type_metadata.hpp"
#include "type_utils.hpp"
#include "reflection_api.hpp"
#include "class_info.hpp"
#include "string_interpolation.hpp"
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

class LLVMCodegen : public PrystBaseVisitor, public ReflectionAPI {
public:
    LLVMCodegen() : context(std::make_unique<llvm::LLVMContext>()) {
        module = std::make_unique<llvm::Module>("pryst", *context);
        builder = std::make_unique<llvm::IRBuilder<>>(*context);
        typeRegistry = std::make_unique<LLVMTypeRegistry>(*context, *builder, *module);
        stringInterp = std::make_unique<codegen::StringInterpolation>();
    }
    virtual ~LLVMCodegen() = default;

    std::unique_ptr<llvm::Module> generateModule(PrystParser::ProgramContext* ctx);

    // Getter methods for private members
    llvm::LLVMContext* getContext() const { return context.get(); }
    llvm::Module* getModule() const { return module.get(); }
    llvm::IRBuilder<>* getBuilder() const { return builder.get(); }
    LLVMTypeRegistry& getTypeRegistry() const { return *typeRegistry; }
    void registerFunction(const std::string& name, llvm::Function* func) {
        module->getOrInsertFunction(name, func->getFunctionType());
    }

    // Type system methods
    llvm::Type* getLLVMTypeFromTypeInfo(TypeInfoPtr typeInfo);
    llvm::Type* getPointerType(llvm::Type* elementType);

    // Reflection API methods (implementing ReflectionAPI interface)
    llvm::Value* generateGetType(llvm::Value* value) override;
    llvm::Value* generateIsInstance(llvm::Value* value, const std::string& typeName) override;
    TypeInfoPtr getTypeInfo(llvm::Value* value) override;
    void attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) override;

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

    // Variable declarations
    std::any visitInferredVariableDecl(PrystParser::InferredVariableDeclContext *ctx) override;
    std::any visitTypedVariableDecl(PrystParser::TypedVariableDeclContext *ctx) override;
    std::any visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext *ctx) override;

    // Class members
    std::any visitClassDeclaration(PrystParser::ClassDeclarationContext *ctx) override;
    std::any visitClassBody(PrystParser::ClassBodyContext *ctx) override;
    std::any visitClassMemberDecl(PrystParser::ClassMemberDeclContext *ctx) override;
    std::any visitClassMemberInferredDecl(PrystParser::ClassMemberInferredDeclContext *ctx) override;
    std::any visitClassMemberConstInferredDecl(PrystParser::ClassMemberConstInferredDeclContext *ctx) override;
    std::any visitClassMemberConstTypedDecl(PrystParser::ClassMemberConstTypedDeclContext *ctx) override;
    std::any visitClassMemberFunctionDecl(PrystParser::ClassMemberFunctionDeclContext *ctx) override;

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
    std::any visitStringLiteralRule(PrystParser::StringLiteralRuleContext *ctx) override;

    // Statements
    std::any visitBlockStatement(PrystParser::BlockStatementContext *ctx) override;
    std::any visitExprStatement(PrystParser::ExprStatementContext *ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext *ctx) override;
    std::any visitWhileStatement(PrystParser::WhileStatementContext *ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext *ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext *ctx) override;
    std::any visitTryStmtWrapper(PrystParser::TryStmtWrapperContext *ctx) override;
    std::any visitPrintStatement(PrystParser::PrintStatementContext *ctx) override;

private:
    // Helper methods
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, const std::string& varName, llvm::Type* type);
    void declarePrintFunctions();

    // Builtin function declarations
    llvm::Function* declareMathSqrt();
    llvm::Function* declareMathPow();
    llvm::Function* declareMathAbs();
    llvm::Function* declareStrConcat();
    llvm::Function* declareStrSubstr();
    llvm::Function* declareBoolToStr();
    llvm::Function* declareIntToStr();
    llvm::Function* declareFloatToStr();

    // Private members
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<LLVMTypeRegistry> typeRegistry;
    std::unique_ptr<codegen::StringInterpolation> stringInterp;
    std::map<std::string, llvm::Value*> namedValues;
    llvm::Function* currentFunction;
};
} // namespace pryst
