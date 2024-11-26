#pragma once

// LLVM headers (order matters)
#include <llvm/Support/Casting.h>
#include <llvm/ADT/Optional.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

// Standard library headers
#include <string>
#include <unordered_map>
#include <memory>
#include <any>

// Project headers
#include "generated/PrystParserBaseVisitor.h"
#include "generated/PrystParser.h"
#include "type_system/type_checker.hpp"
#include "type_system/core/type_registry.hpp"
#include "type_system/core/class_type_registry.hpp"

// Use LLVM namespace explicitly to avoid conflicts
using llvm::Type;
using llvm::Value;
using llvm::Function;
using llvm::BasicBlock;
using llvm::IRBuilder;
using llvm::Module;
using llvm::LLVMContext;
using llvm::StringRef;
using llvm::SmallVector;
using llvm::SmallString;
using llvm::cast;
using llvm::dyn_cast;
using llvm::isa;

namespace pryst {
namespace core {

class LLVMCodeGen : public PrystParserBaseVisitor {
private:
    llvm::LLVMContext& context;
    llvm::Module& module;
    llvm::IRBuilder<>& builder;
    TypeRegistry& typeRegistry;
    ClassTypeRegistry classTypeRegistry;
    std::unordered_map<std::string, llvm::Value*> valueMap;
    std::vector<std::pair<llvm::BasicBlock*, llvm::BasicBlock*>> loopStack;
    llvm::Function* currentFunction;
    std::string currentClass;
    llvm::Value* currentInstance;
    std::unordered_map<std::string, llvm::Type*> memberTypes;
    std::unordered_map<std::string, size_t> memberIndices;

    // Helper methods
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
    llvm::Value* convertToFloat(llvm::Value* value);
    llvm::Value* convertType(llvm::Value* value, llvm::Type* targetType);
    llvm::Type* getLLVMType(std::shared_ptr<Type> type);
    std::vector<llvm::Type*> getLLVMTypes(const std::vector<std::shared_ptr<Type>>& types);
    std::shared_ptr<Type> getTypeFromTypeContext(PrystParser::TypeContext* ctx);
    std::shared_ptr<Type> getTypeFromReturnTypeContext(PrystParser::ReturnTypeContext* ctx);
    llvm::Function* getOrCreateStringAlloc();
    llvm::Function* getOrCreateArrayAlloc();
    llvm::Function* getOrCreateMapAlloc();
    llvm::Function* getOrCreateGCAlloc();
    void initializeRuntime();
    std::string getTokenText(antlr4::tree::TerminalNode* node);
    bool hasToken(antlr4::tree::TerminalNode* node);
    bool hasContext(antlr4::tree::ParseTree* node);
    antlr4::ParserRuleContext* getContext(antlr4::tree::ParseTree* node);
    unsigned getMemberIndex(llvm::Type* classType, const std::string& memberName);
    virtual std::any visitPrimary(PrystParser::PrimaryContext* ctx);

    // Type creation helpers
    llvm::Type* createArrayType(llvm::Type* elementType);
    llvm::Type* createMapType(llvm::Type* keyType, llvm::Type* valueType);
    llvm::Type* createNullableType(llvm::Type* baseType);

public:
    LLVMCodeGen(llvm::LLVMContext& context, llvm::Module& module, llvm::IRBuilder<>& builder, TypeRegistry& registry)
        : context(context), module(module), builder(builder), typeRegistry(registry) {}
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

    virtual std::any visit(antlr4::tree::ParseTree* tree) override {
        return tree->accept(this);
    }

    void initModule(const std::string& moduleName);

    // Program structure
    virtual std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    virtual std::any visitImportDecl(PrystParser::ImportDeclContext* ctx) override;
    virtual std::any visitImportPath(PrystParser::ImportPathContext* ctx) override;
    virtual std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    virtual std::any visitParameters(PrystParser::ParametersContext* ctx) override;
    virtual std::any visitParameter(PrystParser::ParameterContext* ctx) override;
    virtual std::any visitBlock(PrystParser::BlockContext* ctx) override;

    // Statements
    virtual std::any visitStatement(PrystParser::StatementContext* ctx) override;
    virtual std::any visitVarDecl(PrystParser::VarDeclContext* ctx) override;
    virtual std::any visitIdentifierList(PrystParser::IdentifierListContext* ctx) override;
    virtual std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    virtual std::any visitIfStmt(PrystParser::IfStmtContext* ctx) override;
    virtual std::any visitWhileStmt(PrystParser::WhileStmtContext* ctx) override;
    virtual std::any visitForStmt(PrystParser::ForStmtContext* ctx) override;
    virtual std::any visitReturnStmt(PrystParser::ReturnStmtContext* ctx) override;
    virtual std::any visitTryStmt(PrystParser::TryStmtContext* ctx) override;
    virtual std::any visitBreakStmt(PrystParser::BreakStmtContext* ctx) override;
    virtual std::any visitContinueStmt(PrystParser::ContinueStmtContext* ctx) override;
    virtual std::any visitExpressionStmt(PrystParser::ExpressionStmtContext* ctx) override;

    // Types
    virtual std::any visitType(PrystParser::TypeContext* ctx) override;
    virtual std::any visitBasicType(PrystParser::BasicTypeContext* ctx) override;
    virtual std::any visitQualifiedType(PrystParser::QualifiedTypeContext* ctx) override;
    virtual std::any visitArrayType(PrystParser::ArrayTypeContext* ctx) override;
    virtual std::any visitMapType(PrystParser::MapTypeContext* ctx) override;
    virtual std::any visitFunctionType(PrystParser::FunctionTypeContext* ctx) override;

    // Expressions
    virtual std::any visitPrimaryExpr(PrystParser::PrimaryExprContext* ctx) override;
    virtual std::any visitConstructorExpr(PrystParser::ConstructorExprContext* ctx) override;
    virtual std::any visitMemberAccessExpr(PrystParser::MemberAccessExprContext* ctx) override;
    virtual std::any visitNullableChain(PrystParser::NullableChainContext* ctx) override;
    virtual std::any visitMethodCallExpr(PrystParser::MethodCallExprContext* ctx) override;
    virtual std::any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext* ctx) override;
    virtual std::any visitCastExpr(PrystParser::CastExprContext* ctx) override;
    virtual std::any visitParenExpr(PrystParser::ParenExprContext* ctx) override;
    virtual std::any visitPrefixExpr(PrystParser::PrefixExprContext* ctx) override;
    virtual std::any visitPostfixExpr(PrystParser::PostfixExprContext* ctx) override;
    virtual std::any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext* ctx) override;
    virtual std::any visitAdditiveExpr(PrystParser::AdditiveExprContext* ctx) override;
    virtual std::any visitRelationalExpr(PrystParser::RelationalExprContext* ctx) override;
    virtual std::any visitEqualityExpr(PrystParser::EqualityExprContext* ctx) override;
    virtual std::any visitLogicalAndExpr(PrystParser::LogicalAndExprContext* ctx) override;
    virtual std::any visitLogicalOrExpr(PrystParser::LogicalOrExprContext* ctx) override;
    virtual std::any visitConditionalExpr(PrystParser::ConditionalExprContext* ctx) override;
    virtual std::any visitAssignmentExpr(PrystParser::AssignmentExprContext* ctx) override;
    virtual std::any visitLambdaExpr(PrystParser::LambdaExprContext* ctx) override;
    virtual std::any visitInstanceofExpr(PrystParser::InstanceofExprContext* ctx) override;
    virtual std::any visitTypeofExpr(PrystParser::TypeofExprContext* ctx) override;

    // Class-related
    virtual std::any visitClassDecl(PrystParser::ClassDeclContext* ctx) override;
    virtual std::any visitInterfaceDecl(PrystParser::InterfaceDeclContext* ctx) override;
    virtual std::any visitClassMember(PrystParser::ClassMemberContext* ctx) override;
    virtual std::any visitConstructorDecl(PrystParser::ConstructorDeclContext* ctx) override;
    virtual std::any visitConstructorBlock(PrystParser::ConstructorBlockContext* ctx) override;

    // Literals and arguments
    virtual std::any visitArguments(PrystParser::ArgumentsContext* ctx) override;
    virtual std::any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext* ctx) override;
    virtual std::any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext* ctx) override;
    virtual std::any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext* ctx) override;
    virtual std::any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext* ctx) override;
    virtual std::any visitMapEntry(PrystParser::MapEntryContext* ctx) override;
};

} // namespace core
} // namespace pryst
