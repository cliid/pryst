#pragma once

#include "antlr4-runtime.h"
#include "tree/AbstractParseTreeVisitor.h"
#include "tree/ParseTreeVisitor.h"
#include "generated/PrystParserBaseVisitor.h"
#include "generated/PrystParser.h"
#include "types.hpp"
#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>

namespace pryst {

class TypeChecker :
    public PrystParserBaseVisitor {
public:
    TypeChecker();

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

    // Visitor pattern implementation matching grammar rules
    std::any visitProgram(PrystParser::ProgramContext* context) override;
    std::any visitExpression(PrystParser::ExpressionContext* context) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext* context) override;
    std::any visitImportPath(PrystParser::ImportPathContext* context) override;
    std::any visitDeclaration(PrystParser::DeclarationContext* context) override;
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* context) override;
    std::any visitParameters(PrystParser::ParametersContext* context) override;
    std::any visitParameter(PrystParser::ParameterContext* context) override;
    std::any visitBlock(PrystParser::BlockContext* context) override;
    std::any visitStatement(PrystParser::StatementContext* context) override;
    std::any visitVarDecl(PrystParser::VarDeclContext* context) override;
    std::any visitIdentifierList(PrystParser::IdentifierListContext* context) override;
    std::any visitAssignment(PrystParser::AssignmentContext* context) override;
    std::any visitIfStmt(PrystParser::IfStmtContext* context) override;
    std::any visitWhileStmt(PrystParser::WhileStmtContext* context) override;
    std::any visitForStmt(PrystParser::ForStmtContext* context) override;
    std::any visitReturnStmt(PrystParser::ReturnStmtContext* context) override;
    std::any visitTryStmt(PrystParser::TryStmtContext* context) override;
    std::any visitBreakStmt(PrystParser::BreakStmtContext* context) override;
    std::any visitContinueStmt(PrystParser::ContinueStmtContext* context) override;
    std::any visitExpressionStmt(PrystParser::ExpressionStmtContext* context) override;
    std::any visitClassDecl(PrystParser::ClassDeclContext* context) override;
    std::any visitInterfaceDecl(PrystParser::InterfaceDeclContext* context) override;
    std::any visitInterfaceMember(PrystParser::InterfaceMemberContext* context) override;
    std::any visitGenericParams(PrystParser::GenericParamsContext* context) override;
    std::any visitGenericArgs(PrystParser::GenericArgsContext* context) override;
    std::any visitClassMember(PrystParser::ClassMemberContext* context) override;
    std::any visitConstructorDecl(PrystParser::ConstructorDeclContext* context) override;
    std::any visitConstructorBlock(PrystParser::ConstructorBlockContext* context) override;
    std::any visitType(PrystParser::TypeContext* context) override;
    std::any visitBasicType(PrystParser::BasicTypeContext* context) override;
    std::any visitArrayType(PrystParser::ArrayTypeContext* context) override;
    std::any visitMapType(PrystParser::MapTypeContext* context) override;
    std::any visitKeyType(PrystParser::KeyTypeContext* context) override;
    std::any visitFunctionType(PrystParser::FunctionTypeContext* context) override;
    std::any visitTypeList(PrystParser::TypeListContext* context) override;
    std::any visitPrimaryExpr(PrystParser::PrimaryExprContext* context) override;
    std::any visitBuiltinFunctionCall(PrystParser::BuiltinFunctionCallContext* context) override;
    std::any visitConstructorExpr(PrystParser::ConstructorExprContext* context) override;
    std::any visitMemberAccessExpr(PrystParser::MemberAccessExprContext* context) override;
    std::any visitNullableMemberExpr(PrystParser::NullableMemberExprContext* context) override;
    std::any visitMethodCallExpr(PrystParser::MethodCallExprContext* context) override;
    std::any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext* context) override;
    std::any visitCastExpr(PrystParser::CastExprContext* context) override;
    std::any visitParenExpr(PrystParser::ParenExprContext* context) override;
    std::any visitPrefixExpr(PrystParser::PrefixExprContext* context) override;
    std::any visitPostfixExpr(PrystParser::PostfixExprContext* context) override;
    std::any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext* context) override;
    std::any visitAdditiveExpr(PrystParser::AdditiveExprContext* context) override;
    std::any visitRelationalExpr(PrystParser::RelationalExprContext* context) override;
    std::any visitEqualityExpr(PrystParser::EqualityExprContext* context) override;
    std::any visitLogicalAndExpr(PrystParser::LogicalAndExprContext* context) override;
    std::any visitLogicalOrExpr(PrystParser::LogicalOrExprContext* context) override;
    std::any visitConditionalExpr(PrystParser::ConditionalExprContext* context) override;
    std::any visitAssignmentExpr(PrystParser::AssignmentExprContext* context) override;
    std::any visitLambdaExpr(PrystParser::LambdaExprContext* context) override;
    std::any visitLambdaExprInline(PrystParser::LambdaExprInlineContext* context) override;
    std::any visitPrimary(PrystParser::PrimaryContext* context) override;
    std::any visitArguments(PrystParser::ArgumentsContext* context) override;
    std::any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext* context) override;
    std::any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext* context) override;
    std::any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext* context) override;
    std::any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext* context) override;
    std::any visitMapEntry(PrystParser::MapEntryContext* context) override;
    std::any visitFileOperation(PrystParser::FileOperationContext* context) override;
    std::any visitMapKey(PrystParser::MapKeyContext* context) override;
    std::any visitBuiltinFunction(PrystParser::BuiltinFunctionContext* context) override;
    std::any visitChainedCall(PrystParser::ChainedCallContext* context) override;
    std::any visitConstructorCall(PrystParser::ConstructorCallContext* context) override;
    std::any visitStringLiteral(PrystParser::StringLiteralContext* context) override;
    std::any visitLambdaParams(PrystParser::LambdaParamsContext* context) override;

private:
    std::map<std::string, std::shared_ptr<Type>> symbolTable;
    std::vector<std::map<std::string, std::shared_ptr<Type>>> scopeStack;
    std::map<std::string, std::vector<std::string>> interfaceMethods;
    std::map<std::string, std::vector<std::string>> interfaceInheritance;
    std::map<std::string, std::vector<std::string>> classImplements;
    std::map<std::string, std::shared_ptr<Type>> functionTypes;

    void pushScope();
    void popScope();
    void declareVariable(const std::string& name, std::shared_ptr<Type> type);
    std::shared_ptr<Type> lookupVariable(const std::string& name);

    // Type checking helpers
    bool isAssignable(std::shared_ptr<Type> target, std::shared_ptr<Type> source);
    bool implementsInterface(const std::string& className, const std::string& interfaceName);
    std::shared_ptr<Type> createFunctionType(const std::string& returnType, const std::vector<std::string>& paramTypes);
    bool isInterfaceMethod(const std::string& interfaceName, const std::string& methodName);
    void registerInterfaceMethod(const std::string& interfaceName, const std::string& methodName);
    void addInterfaceInheritance(const std::string& interface, const std::string& parent);
    void addClassImplements(const std::string& className, const std::string& interfaceName);

    // Type checking operations
    std::shared_ptr<Type> checkMemberAccess(std::shared_ptr<Type> baseType, const std::string& memberName, bool isNullable);
    std::shared_ptr<Type> checkArrayAccess(std::shared_ptr<Type> arrayType, std::shared_ptr<Type> indexType);
    std::shared_ptr<Type> getTypeFromTypeContext(PrystParser::TypeContext* ctx);
    std::shared_ptr<Type> checkBinaryOp(const std::string& op, std::shared_ptr<Type> left, std::shared_ptr<Type> right);
    std::shared_ptr<Type> checkUnaryOp(const std::string& op, std::shared_ptr<Type> operand);
    std::shared_ptr<Type> checkTypeCast(std::shared_ptr<Type> targetType, std::shared_ptr<Type> sourceType);
    std::shared_ptr<Type> inferReturnType(PrystParser::BlockContext* ctx);
    std::shared_ptr<Type> getLambdaType(PrystParser::LambdaExprContext* ctx);
};

} // namespace pryst
