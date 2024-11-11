#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include "generated/PrystParserBaseVisitor.h"
#include "generated/PrystParser.h"
#include "type_checker.hpp"
#include "type_registry.hpp"
#include <any>
#include <memory>
#include <string>
#include <unordered_map>

namespace pryst {

class LLVMCodeGen :
    public PrystParserBaseVisitor {
public:
    LLVMCodeGen(llvm::LLVMContext& context, llvm::Module& module, llvm::IRBuilder<>& builder, TypeRegistry& registry);
    ~LLVMCodeGen() = default;

    virtual std::any visitChildren(antlr4::tree::ParseTree* node) override {
        return node->accept(this);
    }

    virtual std::any defaultResult() override {
        return std::any();
    }

    virtual std::any aggregateResult(std::any aggregate, std::any nextResult) override {
        return nextResult;
    }

    // Base visitor method from AbstractParseTreeVisitor
    virtual std::any visit(antlr4::tree::ParseTree* tree) override {
        return tree->accept(this);
    }

    // Initialize a new module
    void initModule(const std::string& moduleName);

    // Visitor pattern implementation
    virtual std::any visitProgram(PrystParser::ProgramContext *context) override;
    virtual std::any visitImportDecl(PrystParser::ImportDeclContext *context) override;
    virtual std::any visitImportPath(PrystParser::ImportPathContext *context) override;
    virtual std::any visitDeclaration(PrystParser::DeclarationContext *context) override;
    virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *context) override;
    virtual std::any visitParameters(PrystParser::ParametersContext *context) override;
    virtual std::any visitParameter(PrystParser::ParameterContext *context) override;
    virtual std::any visitBlock(PrystParser::BlockContext *context) override;
    virtual std::any visitStatement(PrystParser::StatementContext *context) override;
    virtual std::any visitVarDecl(PrystParser::VarDeclContext *context) override;
    virtual std::any visitIdentifierList(PrystParser::IdentifierListContext *context) override;
    virtual std::any visitAssignment(PrystParser::AssignmentContext *context) override;
    virtual std::any visitIfStmt(PrystParser::IfStmtContext *context) override;
    virtual std::any visitWhileStmt(PrystParser::WhileStmtContext *context) override;
    virtual std::any visitForStmt(PrystParser::ForStmtContext *context) override;
    virtual std::any visitReturnStmt(PrystParser::ReturnStmtContext *context) override;
    virtual std::any visitTryStmt(PrystParser::TryStmtContext *context) override;
    virtual std::any visitBreakStmt(PrystParser::BreakStmtContext *context) override;
    virtual std::any visitContinueStmt(PrystParser::ContinueStmtContext *context) override;
    virtual std::any visitExpressionStmt(PrystParser::ExpressionStmtContext *context) override;
    virtual std::any visitClassDecl(PrystParser::ClassDeclContext *context) override;
    virtual std::any visitInterfaceDecl(PrystParser::InterfaceDeclContext *context) override;
    virtual std::any visitInterfaceMember(PrystParser::InterfaceMemberContext *context) override;
    virtual std::any visitGenericParams(PrystParser::GenericParamsContext *context) override;
    virtual std::any visitGenericArgs(PrystParser::GenericArgsContext *context) override;
    virtual std::any visitClassMember(PrystParser::ClassMemberContext *context) override;
    virtual std::any visitOverloadParams(PrystParser::OverloadParamsContext *context) override;
    virtual std::any visitConstructorDecl(PrystParser::ConstructorDeclContext *context) override;
    virtual std::any visitConstructorBlock(PrystParser::ConstructorBlockContext *context) override;
    virtual std::any visitType(PrystParser::TypeContext *context) override;
    virtual std::any visitBasicType(PrystParser::BasicTypeContext *context) override;
    virtual std::any visitArrayType(PrystParser::ArrayTypeContext *context) override;
    virtual std::any visitMapType(PrystParser::MapTypeContext *context) override;
    virtual std::any visitKeyType(PrystParser::KeyTypeContext *context) override;
    virtual std::any visitFunctionType(PrystParser::FunctionTypeContext *context) override;
    virtual std::any visitTypeList(PrystParser::TypeListContext *context) override;
    virtual std::any visitBuiltinFunctionCall(PrystParser::BuiltinFunctionCallContext *context) override;
    virtual std::any visitAssignmentExpr(PrystParser::AssignmentExprContext *context) override;
    virtual std::any visitLogicalAndExpr(PrystParser::LogicalAndExprContext *context) override;
    virtual std::any visitCastExpr(PrystParser::CastExprContext *context) override;
    virtual std::any visitAdditiveExpr(PrystParser::AdditiveExprContext *context) override;
    virtual std::any visitRelationalExpr(PrystParser::RelationalExprContext *context) override;
    virtual std::any visitParenExpr(PrystParser::ParenExprContext *context) override;
    virtual std::any visitLogicalOrExpr(PrystParser::LogicalOrExprContext *context) override;
    virtual std::any visitPrefixExpr(PrystParser::PrefixExprContext *context) override;
    virtual std::any visitMethodCallExpr(PrystParser::MethodCallExprContext *context) override;
    virtual std::any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext *context) override;
    virtual std::any visitPrimaryExpr(PrystParser::PrimaryExprContext *context) override;
    virtual std::any visitNullableMemberExpr(PrystParser::NullableMemberExprContext *context) override;
    virtual std::any visitLambdaExpr(PrystParser::LambdaExprContext *context) override;
    virtual std::any visitLambdaExprInline(PrystParser::LambdaExprInlineContext *context) override;
    virtual std::any visitMemberAccessExpr(PrystParser::MemberAccessExprContext *context) override;
    virtual std::any visitPostfixExpr(PrystParser::PostfixExprContext *context) override;
    virtual std::any visitConstructorExpr(PrystParser::ConstructorExprContext *context) override;
    virtual std::any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext *context) override;
    virtual std::any visitEqualityExpr(PrystParser::EqualityExprContext *context) override;
    virtual std::any visitConditionalExpr(PrystParser::ConditionalExprContext *context) override;
    virtual std::any visitPrimary(PrystParser::PrimaryContext *context) override;
    virtual std::any visitBuiltinFunction(PrystParser::BuiltinFunctionContext *context) override;
    virtual std::any visitChainedCall(PrystParser::ChainedCallContext *context) override;
    virtual std::any visitConstructorCall(PrystParser::ConstructorCallContext *context) override;
    virtual std::any visitFileOperation(PrystParser::FileOperationContext *context) override;
    virtual std::any visitStringLiteral(PrystParser::StringLiteralContext *context) override;
    virtual std::any visitLambdaParams(PrystParser::LambdaParamsContext *context) override;
    virtual std::any visitArguments(PrystParser::ArgumentsContext *context) override;
    virtual std::any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext *context) override;
    virtual std::any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext *context) override;
    virtual std::any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext *context) override;
    virtual std::any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext *context) override;
    virtual std::any visitMapEntry(PrystParser::MapEntryContext *context) override;
    virtual std::any visitMapKey(PrystParser::MapKeyContext *context) override;

    // Get the generated module
    llvm::Module& getModule() { return module; }

private:
    // LLVM context and builder
    llvm::LLVMContext& context;
    llvm::IRBuilder<>& builder;
    llvm::Module& module;

    // Type mapping
    std::map<std::string, llvm::Type*> typeMap;
    std::map<std::string, llvm::Value*> valueMap;
    TypeRegistry& typeRegistry;  // Reference to type registry for class information

    // Loop context for break/continue
    std::vector<std::pair<llvm::BasicBlock*, llvm::BasicBlock*>> loopStack;

    // Helper methods for type conversion
    llvm::Type* getLLVMType(std::shared_ptr<pryst::Type> type);
    std::shared_ptr<Type> getTypeFromTypeContext(PrystParser::TypeContext* ctx);
    llvm::Value* generateExpression(antlr4::ParserRuleContext* ctx);
    llvm::Value* generateStatement(antlr4::ParserRuleContext* ctx);

    // Helper methods for ANTLR vector access
    bool hasToken(const std::vector<antlr4::tree::TerminalNode*>& tokens) const {
        return !tokens.empty();
    }

    std::string getTokenText(const std::vector<antlr4::tree::TerminalNode*>& tokens, size_t index = 0) const {
        return tokens.size() > index ? tokens[index]->getText() : "";
    }

    // Single token handling
    bool hasToken(antlr4::tree::TerminalNode* token) const {
        return token != nullptr;
    }

    std::string getTokenText(antlr4::tree::TerminalNode* token) const {
        return token ? token->getText() : "";
    }

    bool hasContext(const std::vector<PrystParser::ArgumentsContext*>& contexts) const {
        return !contexts.empty();
    }

    template<typename T>
    bool hasContext(const std::vector<T*>& contexts) const {
        return !contexts.empty();
    }

    template<typename T>
    T* getContext(const std::vector<T*>& contexts, size_t index = 0) const {
        return contexts.size() > index ? contexts[index] : nullptr;
    }

    template<typename T>
    bool hasContext(T* context) const {
        return context != nullptr;
    }

    template<typename T>
    T* getContext(T* context) const {
        return context;
    }

    // Runtime support
    void initializeRuntime();
    llvm::Function* getOrCreateGCAlloc();
    llvm::Function* getOrCreateStringAlloc();
    llvm::Function* getOrCreateArrayAlloc();
    llvm::Function* getOrCreateMapAlloc();

    // Helper methods for binary operations
    llvm::Value* createAdd(llvm::Value* left, llvm::Value* right);
    llvm::Value* createSub(llvm::Value* left, llvm::Value* right);
    llvm::Value* createMul(llvm::Value* left, llvm::Value* right);
    llvm::Value* createDiv(llvm::Value* left, llvm::Value* right);
    llvm::Value* createMod(llvm::Value* left, llvm::Value* right);
    llvm::Value* createLT(llvm::Value* left, llvm::Value* right);
    llvm::Value* createGT(llvm::Value* left, llvm::Value* right);
    llvm::Value* createLE(llvm::Value* left, llvm::Value* right);
    llvm::Value* createGE(llvm::Value* left, llvm::Value* right);
    llvm::Value* createEQ(llvm::Value* left, llvm::Value* right);
    llvm::Value* createNEQ(llvm::Value* left, llvm::Value* right);
    llvm::Value* createAnd(llvm::Value* left, llvm::Value* right);
    llvm::Value* createOr(llvm::Value* left, llvm::Value* right);

    // Type conversion helpers
    llvm::Value* convertToFloat(llvm::Value* value);
    llvm::Value* convertType(llvm::Value* value, llvm::Type* targetType);

    // Member access helpers
    unsigned getMemberIndex(llvm::Type* classType, const std::string& memberName);
};

} // namespace pryst
