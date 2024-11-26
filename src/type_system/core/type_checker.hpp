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
#include <memory>
#include <string>
#include <vector>

// ANTLR4 headers
#include "generated/PrystParserBaseVisitor.h"
#include "generated/PrystParser.h"
#include "generated/PrystLexer.h"
#include "antlr4-runtime.h"

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

// Project headers
#include "type_system/core/types.hpp"
#include "type_system/core/type_registry.hpp"
#include "runtime/core/runtime_registry.hpp"
#include "type_system/core/llvm_type_converter.hpp"
#include "type_system/core/type_info.hpp"
#include "type_system/core/scope_manager.hpp"
#include "error_handling/core/error.hpp"
#include "error_handling/core/error_handler.hpp"
#include "error_handling/core/error_chain.hpp"
#include "type_system/core/type_inference.hpp"

namespace pryst {
namespace core {

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
    std::shared_ptr<Type> currentFunctionReturnType;
    std::shared_ptr<Type> lastExpressionType;
    bool isInLoop;
    llvm::LLVMContext& context_;
    TypeRegistry& typeRegistry_;
    RuntimeRegistry& runtimeRegistry_;
    LLVMTypeConverter converter_;

    void pushScope();
    void popScope();
    void initializeGlobalScope();
    void declareVariable(const std::string& name, std::shared_ptr<Type> type);
    std::shared_ptr<Type> lookupVariable(const std::string& name);
    std::shared_ptr<Type> checkMemberAccess(std::shared_ptr<Type> baseType,
                                                  const std::string& member,
                                                  bool isNullable);
    std::shared_ptr<Type> getTypeFromTypeContext(PrystParser::TypeContext* ctx);
    std::shared_ptr<Type> getTypeFromReturnTypeContext(PrystParser::ReturnTypeContext* ctx);
    std::shared_ptr<Type> checkBinaryOp(const std::string& op,
                                              std::shared_ptr<Type> left,
                                              std::shared_ptr<Type> right);
    std::shared_ptr<Type> checkUnaryOp(const std::string& op,
                                             std::shared_ptr<Type> operand);
    std::shared_ptr<Type> checkTypeCast(std::shared_ptr<Type> targetType,
                                              std::shared_ptr<Type> sourceType);
    std::shared_ptr<Type> checkArrayAccess(std::shared_ptr<Type> arrayType,
                                                 std::shared_ptr<Type> indexType);
    std::shared_ptr<Type> checkArrayCreation(std::shared_ptr<Type> elementType);
    std::shared_ptr<Type> checkArrayAssignment(std::shared_ptr<Type> targetArray,
                                                     std::shared_ptr<Type> sourceArray);
    std::shared_ptr<Type> checkTypesMatch(std::shared_ptr<Type> expectedType,
                                                std::shared_ptr<Type> actualType,
                                                antlr4::ParserRuleContext* ctx);
    std::shared_ptr<Type> inferReturnType(PrystParser::BlockContext* ctx);
    std::shared_ptr<Type> getLambdaType(PrystParser::LambdaExprContext* ctx);
    std::shared_ptr<Type> unwrapNullableType(std::shared_ptr<Type> type);
    bool isNullableType(std::shared_ptr<Type> type);
    std::shared_ptr<Type> wrapAsNullable(std::shared_ptr<Type> type);
    std::shared_ptr<Type> propagateNullability(std::shared_ptr<Type> sourceType,
                                                     std::shared_ptr<Type> targetType);
    bool isErrorType(std::shared_ptr<Type> type);
    bool validateErrorMethodSignature(const std::string& methodName,
                                  const std::shared_ptr<FunctionType>& method,
                                  const std::shared_ptr<Type>& baseType);
    std::shared_ptr<Type> createErrorChain(const std::shared_ptr<Type>& error,
                                       const std::shared_ptr<Type>& cause);
    std::shared_ptr<Type> propagateErrorThroughScope(const std::shared_ptr<Type>& error,
                                                   const std::string& context);
    std::shared_ptr<Type> propagateErrorWithTransform(const std::shared_ptr<Type>& error,
                                                    std::function<std::string(const std::string&)> transformer);
    std::shared_ptr<Type> propagateUnionTypeError(const std::shared_ptr<Type>& first,
                                                 const std::shared_ptr<Type>& second) {
        if (first->getKind() == Type::Kind::Error) {
            return first;
        }
        if (second->getKind() == Type::Kind::Error) {
            return second;
        }
        return std::make_shared<ErrorType>("Invalid union type: " + first->toString() + " | " + second->toString());
    }

    std::shared_ptr<Type> propagateIntersectionTypeError(const std::shared_ptr<Type>& first,
                                                        const std::shared_ptr<Type>& second) {
        if (first->getKind() == Type::Kind::Error) {
            return first;
        }
        if (second->getKind() == Type::Kind::Error) {
            return second;
        }
        return std::make_shared<ErrorType>("Invalid intersection type: " + first->toString() + " & " + second->toString());
    }

public:
    TypeChecker(llvm::LLVMContext& context, TypeRegistry& typeRegistry, RuntimeRegistry& runtimeRegistry, ErrorHandler& errorHandler)
        : context_(context),
          typeRegistry_(typeRegistry),
          runtimeRegistry_(runtimeRegistry),
          errorHandler_(errorHandler),
          isInLoop(false) {}

    bool isAssignable(std::shared_ptr<Type> targetType, std::shared_ptr<Type> sourceType);

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

    std::shared_ptr<Type> visitType(const TypeContext* ctx) override {
        auto firstType = visit(ctx->primaryType());
        if (firstType->getKind() == Type::Kind::Error) {
            return firstType;
        }

        std::shared_ptr<Type> resultType = firstType;
        for (const auto* rest : ctx->typeRest()) {
            auto secondType = visit(rest->primaryType());

            if (rest->PIPE()) {
                resultType = propagateUnionTypeError(resultType, secondType);
            } else if (rest->AMP()) {
                resultType = propagateIntersectionTypeError(resultType, secondType);
            }

            if (resultType->getKind() == Type::Kind::Error) {
                break;
            }
        }

        return resultType;
    }

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
    std::any visitType(PrystParser::TypeContext* ctx) override {
        auto firstType = visit(ctx->primaryType());
        auto restTypes = ctx->typeRest();

        std::shared_ptr<Type> resultType = std::any_cast<std::shared_ptr<Type>>(firstType);
        for (const auto* rest : restTypes) {
            if (rest->PIPE()) {
                auto secondType = std::any_cast<std::shared_ptr<Type>>(visit(rest->primaryType()));
                auto unionType = std::make_shared<UnionType>(resultType, secondType);
                typeRegistry_.registerUnionType(unionType);
                resultType = unionType;
            } else if (rest->AMP()) {
                auto secondType = std::any_cast<std::shared_ptr<Type>>(visit(rest->primaryType()));
                auto intersectionType = std::make_shared<IntersectionType>(resultType, secondType);
                typeRegistry_.registerIntersectionType(intersectionType);
                resultType = intersectionType;
            }
        }
        return resultType;
    }
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
    std::any visitTypeRest(PrystParser::TypeRestContext* ctx) override;
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

} // namespace core
} // namespace pryst
