#pragma once

#include "generated/PrystParserBaseVisitor.h"
#include "generated/PrystParser.h"
#include "generated/PrystLexer.h"
#include "antlr4-runtime.h"
#include "types.hpp"
#include "type_registry.hpp"
#include "runtime/runtime_registry.hpp"
#include "llvm_type_converter.hpp"
#include "type_info.hpp"
#include "scope_manager.hpp"
#include "error_chain.hpp"
#include "type_inference.hpp"
#include "error_handling/advanced/propagation/error_propagation.hpp"
#include <llvm/IR/LLVMContext.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace pryst {

using std::string;
using std::vector;
using std::unordered_map;
using std::any;
using std::shared_ptr;
using runtime::RuntimeRegistry;

// Forward declarations for test classes
namespace testing {
    class PrystTestFixture;
}

class TypeChecker : public PrystParserBaseVisitor {
    friend class testing::PrystTestFixture;

protected:
    ScopeManager scopeManager_;
    TypeInference typeInference_;
    ErrorHandler& errorHandler_;
    any currentFunctionReturnType;
    any lastExpressionType;
    bool isInLoop;
    llvm::LLVMContext& context_;
    TypeRegistry& typeRegistry_;
    RuntimeRegistry& runtimeRegistry_;
    LLVMTypeConverter converter_;
    std::shared_ptr<ErrorPropagation> errorPropagation_;
    vector<string> errorPropagationBarriers_;

    void pushScope();
    void popScope();
    void initializeGlobalScope();
    void declareVariable(const std::string& name, std::any type);
    std::any lookupVariable(const std::string& name);
    std::any checkMemberAccess(std::any baseType, const std::string& member, bool isNullable);
    std::any getTypeFromTypeContext(PrystParser::TypeContext* ctx);
    std::any getTypeFromReturnTypeContext(PrystParser::ReturnTypeContext* ctx);
    std::any checkBinaryOp(const std::string& op, std::any left, std::any right);
    std::any checkUnaryOp(const std::string& op, std::any operand);
    std::any checkTypeCast(std::any targetType, std::any sourceType);
    std::any checkArrayAccess(std::any arrayType, std::any indexType);
    std::any checkArrayCreation(std::any elementType);
    std::any checkArrayAssignment(std::any targetArray, std::any sourceArray);
    std::any checkTypesMatch(std::any expectedType, std::any actualType, antlr4::ParserRuleContext* ctx);
    std::any inferReturnType(PrystParser::BlockContext* ctx);
    std::any getLambdaType(PrystParser::LambdaExprContext* ctx);
    std::any unwrapNullableType(std::any type);
    bool isNullableType(std::any type);
    std::any wrapAsNullable(std::any type);
    std::any propagateNullability(std::any sourceType, std::any targetType);
    bool isErrorType(std::shared_ptr<Type> type);
    bool validateErrorMethodSignature(const std::string& methodName,
                                    const std::shared_ptr<FunctionType>& method,
                                    const std::shared_ptr<Type>& baseType);
    std::shared_ptr<Type> createErrorChain(const std::shared_ptr<Type>& error,
                                         const std::shared_ptr<Type>& cause);

    // New advanced error handling methods
    std::shared_ptr<Type> propagateErrorThroughScope(
        std::shared_ptr<Type> error,
        const string& scopeName,
        bool propagateToParent = true);

    std::shared_ptr<Type> propagateErrorWithTransform(
        std::shared_ptr<Type> error,
        const vector<std::shared_ptr<Type>>& path,
        const std::function<std::shared_ptr<Type>(std::shared_ptr<Type>)>& transformer);

    std::shared_ptr<Type> handleUnionError(
        std::shared_ptr<Type> unionError,
        const vector<std::shared_ptr<Type>>& path);

    std::shared_ptr<Type> handleIntersectionError(
        std::shared_ptr<Type> intersectionError,
        const vector<std::shared_ptr<Type>>& path);

    void addErrorPropagationBarrier(const string& scopeName);
    void removeErrorPropagationBarrier(const string& scopeName);
    bool shouldPropagateError(const string& fromScope, const string& toScope) const;

public:
    TypeChecker(llvm::LLVMContext& context, TypeRegistry& typeRegistry, runtime::RuntimeRegistry& runtimeRegistry);
    bool isAssignable(std::any targetType, std::any sourceType);

    virtual ~TypeChecker() override {
        // No need for manual scope cleanup as ScopeManager handles it
    }

    // Visit methods for declarations
    std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    std::any visitVarDecl(PrystParser::VarDeclContext* ctx) override;
    std::any visitClassDecl(PrystParser::ClassDeclContext* ctx) override;
    std::any visitErrorDecl(PrystParser::ErrorDeclContext* ctx) override;
    std::any visitErrorField(PrystParser::ErrorFieldContext* ctx) override;
    std::any visitErrorMethod(PrystParser::ErrorMethodContext* ctx) override;
    std::any visitInterfaceDecl(PrystParser::InterfaceDeclContext* ctx) override;

    // Visit methods for statements
    std::any visitBlock(PrystParser::BlockContext* ctx) override;
    std::any visitIfStmt(PrystParser::IfStmtContext* ctx) override;
    std::any visitWhileStmt(PrystParser::WhileStmtContext* ctx) override;
    std::any visitForStmt(PrystParser::ForStmtContext* ctx) override;
    std::any visitReturnStmt(PrystParser::ReturnStmtContext* ctx) override;
    std::any visitBreakStmt(PrystParser::BreakStmtContext* ctx) override;
    std::any visitContinueStmt(PrystParser::ContinueStmtContext* ctx) override;
    std::any visitTryStmt(PrystParser::TryStmtContext* ctx) override;

    // Visit methods for expressions
    std::any visitPrimaryExpr(PrystParser::PrimaryExprContext* ctx) override;
    std::any visitParenExpr(PrystParser::ParenExprContext* ctx) override;
    std::any visitPrefixExpr(PrystParser::PrefixExprContext* ctx) override;
    std::any visitPostfixExpr(PrystParser::PostfixExprContext* ctx) override;
    std::any visitMethodCallExpr(PrystParser::MethodCallExprContext* ctx) override;
    std::any visitNullableMethodCallExpr(PrystParser::NullableMethodCallExprContext* ctx) override;
    std::any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext* ctx) override;
    std::any visitMemberAccessExpr(PrystParser::MemberAccessExprContext* ctx) override;
    std::any visitNullableChain(PrystParser::NullableChainContext* ctx) override;
    std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    std::any visitNullCoalesceExpr(PrystParser::NullCoalesceExprContext* ctx) override;
    std::any visitAdditiveExpr(PrystParser::AdditiveExprContext* ctx) override;
    std::any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext* ctx) override;
    std::any visitRelationalExpr(PrystParser::RelationalExprContext* ctx) override;
    std::any visitEqualityExpr(PrystParser::EqualityExprContext* ctx) override;
    std::any visitLogicalAndExpr(PrystParser::LogicalAndExprContext* ctx) override;
    std::any visitLogicalOrExpr(PrystParser::LogicalOrExprContext* ctx) override;
    std::any visitConditionalExpr(PrystParser::ConditionalExprContext* ctx) override;
    std::any visitAssignmentExpr(PrystParser::AssignmentExprContext* ctx) override;
    std::any visitCastExpr(PrystParser::CastExprContext* ctx) override;
    std::any visitLambdaExpr(PrystParser::LambdaExprContext* ctx) override;
    std::any visitInstanceofExpr(PrystParser::InstanceofExprContext* ctx) override;
    std::any visitTypeofExpr(PrystParser::TypeofExprContext* ctx) override;

    // Visit methods for literals and types
    std::any visitType(PrystParser::TypeContext* ctx) override;
    std::any visitBasicType(PrystParser::BasicTypeContext* ctx) override;
    std::any visitQualifiedType(PrystParser::QualifiedTypeContext* ctx) override;
    std::any visitArrayType(PrystParser::ArrayTypeContext* ctx) override;
    std::any visitMapType(PrystParser::MapTypeContext* ctx) override;
    std::any visitFunctionType(PrystParser::FunctionTypeContext* ctx) override;
    std::any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext* ctx) override;
    std::any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext* ctx) override;
    std::any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext* ctx) override;
    std::any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext* ctx) override;
    std::any visitMapEntry(PrystParser::MapEntryContext* ctx) override;
    std::any visitMapKey(PrystParser::MapKeyContext* ctx) override;
    std::any visitLambdaParams(PrystParser::LambdaParamsContext* ctx) override;
    std::any visitChainedCall(PrystParser::ChainedCallContext* ctx) override;
    std::any visitStringLiteral(PrystParser::StringLiteralContext* ctx) override;

    // Additional visitor methods for nullable types and type system
    std::any visitNullableType(PrystParser::NullableTypeContext* ctx) override;
    std::any visitUnionType(PrystParser::UnionTypeContext* ctx) override;
    std::any visitIntersectionType(PrystParser::IntersectionTypeContext* ctx) override;
    std::any visitKeyType(PrystParser::KeyTypeContext* ctx) override;
    std::any visitStringInterpolation(PrystParser::StringInterpolationContext* ctx) override;
    std::any visitIdentifierList(PrystParser::IdentifierListContext* ctx) override;

    // Additional visitor methods
    std::any visitImportPath(PrystParser::ImportPathContext* ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    std::any visitParameters(PrystParser::ParametersContext* ctx) override;
    std::any visitParameter(PrystParser::ParameterContext* ctx) override;
    std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    std::any visitExpressionStmt(PrystParser::ExpressionStmtContext* ctx) override;
    std::any visitArguments(PrystParser::ArgumentsContext* ctx) override;
    std::any visitConstructorExpr(PrystParser::ConstructorExprContext* ctx) override;
    std::any visitFunctionCallExpr(PrystParser::FunctionCallExprContext* ctx) override;
    std::any visitStatement(PrystParser::StatementContext* ctx) override;
    std::any visitImportDecl(PrystParser::ImportDeclContext* ctx) override;
    std::any visitNonNullAssertExpr(PrystParser::NonNullAssertExprContext* ctx) override;
    std::any visitGenericParams(PrystParser::GenericParamsContext* ctx) override;
    std::any visitGenericArgs(PrystParser::GenericArgsContext* ctx) override;
    std::any visitInterfaceMember(PrystParser::InterfaceMemberContext* ctx) override;
    std::any visitClassMember(PrystParser::ClassMemberContext* ctx) override;
    std::any visitErrorChainField(PrystParser::ErrorChainFieldContext* ctx) override;
    std::shared_ptr<Type> validateErrorChain(std::shared_ptr<Type> errorType, std::shared_ptr<Type> chainedType);
    bool isValidErrorChain(std::shared_ptr<Type> chainedType);
    std::any visitOverloadParams(PrystParser::OverloadParamsContext* ctx) override;
    std::any visitConstructorDecl(PrystParser::ConstructorDeclContext* ctx) override;
    std::any visitConstructorBlock(PrystParser::ConstructorBlockContext* ctx) override;
    std::any visitTypeList(PrystParser::TypeListContext* ctx) override;
};
} // namespace pryst
