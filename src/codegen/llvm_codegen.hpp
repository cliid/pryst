#pragma once

// ANTLR4 includes
#include <antlr4-runtime.h>
#include <tree/AbstractParseTreeVisitor.h>
#include <tree/ParseTreeVisitor.h>

// Generated ANTLR4 files - use relative paths since they're in our include path
#include "PrystParser.h"
#include "PrystVisitor.h"
#include "PrystBaseVisitor.h"

// Project includes
#include "type_metadata.hpp"

// LLVM includes
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Metadata.h>

// Standard library includes
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <any>

// Define antlrcpp namespace
namespace antlrcpp {
    using Any = std::any;
}

/**
 * LLVMCodegen class handles the translation of Pryst AST to LLVM IR
 * It inherits from PrystBaseVisitor to implement visitor methods for each AST node type
 */
class LLVMCodegen : public PrystBaseVisitor {
public:
    LLVMCodegen();
    std::unique_ptr<llvm::Module> generateModule(PrystParser::ProgramContext* programCtx);

    // Overrides for visiting different AST nodes
    antlrcpp::Any visitProgram(PrystParser::ProgramContext* ctx) override;
    antlrcpp::Any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    antlrcpp::Any visitNamedFunction(PrystParser::NamedFunctionContext* ctx) override;
    antlrcpp::Any visitAnonymousFunction(PrystParser::AnonymousFunctionContext* ctx) override;
    antlrcpp::Any visitTypedAnonymousFunction(PrystParser::TypedAnonymousFunctionContext* ctx) override;
    antlrcpp::Any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    antlrcpp::Any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    antlrcpp::Any visitClassBody(PrystParser::ClassBodyContext* ctx) override;
    antlrcpp::Any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) override;
    antlrcpp::Any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;
    antlrcpp::Any visitParamList(PrystParser::ParamListContext* ctx) override;
    antlrcpp::Any visitSimpleParam(PrystParser::SimpleParamContext* ctx) override;
    antlrcpp::Any visitFunctionParam(PrystParser::FunctionParamContext* ctx) override;
    antlrcpp::Any visitBasicType(PrystParser::BasicTypeContext* ctx) override;
    antlrcpp::Any visitArrayType(PrystParser::ArrayTypeContext* ctx) override;
    antlrcpp::Any visitFunctionType(PrystParser::FunctionTypeContext* ctx) override;
    antlrcpp::Any visitClassType(PrystParser::ClassTypeContext* ctx) override;
    antlrcpp::Any visitTypeList(PrystParser::TypeListContext* ctx) override;
    antlrcpp::Any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    antlrcpp::Any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    antlrcpp::Any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    antlrcpp::Any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    antlrcpp::Any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    antlrcpp::Any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    antlrcpp::Any visitExpression(PrystParser::ExpressionContext* ctx) override;
    antlrcpp::Any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    antlrcpp::Any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    antlrcpp::Any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    antlrcpp::Any visitEquality(PrystParser::EqualityContext* ctx) override;
    antlrcpp::Any visitComparison(PrystParser::ComparisonContext* ctx) override;
    antlrcpp::Any visitAddition(PrystParser::AdditionContext* ctx) override;
    antlrcpp::Any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    antlrcpp::Any visitUnary(PrystParser::UnaryContext* ctx) override;
    antlrcpp::Any visitPostfix(PrystParser::PostfixContext* ctx) override;
    antlrcpp::Any visitCall(PrystParser::CallContext* ctx) override;
    antlrcpp::Any visitLiteralExpr(PrystParser::LiteralExprContext* ctx) override;
    antlrcpp::Any visitThisExpr(PrystParser::ThisExprContext* ctx) override;
    antlrcpp::Any visitNumberExpr(PrystParser::NumberExprContext* ctx) override;
    antlrcpp::Any visitStringExpr(PrystParser::StringExprContext* ctx) override;
    antlrcpp::Any visitIdentifierExpr(PrystParser::IdentifierExprContext* ctx) override;
    antlrcpp::Any visitGroupExpr(PrystParser::GroupExprContext* ctx) override;
    antlrcpp::Any visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx) override;
    antlrcpp::Any visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) override;
    antlrcpp::Any visitSuperExpr(PrystParser::SuperExprContext* ctx) override;
    antlrcpp::Any visitNewExpr(PrystParser::NewExprContext* ctx) override;
    antlrcpp::Any visitAnonymousFunctionExpr(PrystParser::AnonymousFunctionExprContext* ctx) override;
    antlrcpp::Any visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) override;
    antlrcpp::Any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;
    antlrcpp::Any visitArguments(PrystParser::ArgumentsContext* ctx) override;

private:
    // Type metadata system
    std::unique_ptr<pryst::TypeMetadata> typeMetadata;

    std::unordered_map<std::string, llvm::FunctionType*> functionTypes;
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;

    // Symbol tables for variables and functions
    std::unordered_map<std::string, llvm::AllocaInst*> namedValues;
    std::unordered_map<std::string, llvm::Function*> functions;
    std::unordered_map<std::string, llvm::Function*> mathFunctions;  // For storing different versions of math functions
    std::unordered_map<std::string, llvm::Function*> stringFunctions;  // For storing string manipulation functions
    std::unordered_map<std::string, llvm::Function*> arrayFunctions;  // For storing array operations

    // Array type cache
    std::unordered_map<std::string, llvm::StructType*> arrayTypes;  // Cache for array types of different element types

    // Class member tracking
    std::unordered_map<std::string, llvm::StructType*> classTypes;
    std::unordered_map<std::string, std::unordered_map<std::string, size_t>> memberIndices;
    std::unordered_map<std::string, std::string> classInheritance;  // Maps derived class to base class

    // Helper methods
    llvm::Type* getLLVMType(const std::string& typeName);
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, const std::string& varName, llvm::Type* type);
    size_t getMemberIndex(llvm::StructType* structType, const std::string& memberName);
    void addClassMember(const std::string& className, const std::string& memberName, size_t index);

    // Type information helper methods
    void addTypeInfo(llvm::Value* value, pryst::TypeInfoPtr typeInfo);
    void addFunctionTypeInfo(llvm::Function* function, pryst::FunctionTypeInfoPtr typeInfo);
    void addClassTypeInfo(llvm::StructType* structType, pryst::ClassTypeInfoPtr typeInfo);
    pryst::TypeInfoPtr getTypeInfo(llvm::Value* value);
    pryst::FunctionTypeInfoPtr getFunctionTypeInfo(llvm::Function* function);
    pryst::ClassTypeInfoPtr getClassTypeInfo(llvm::StructType* structType);

    // Math function declarations
    llvm::Function* declareSqrt();
    llvm::Function* declarePow();
    llvm::Function* declareAbs();

    // String function declarations
    llvm::Function* declareStrlen();
    llvm::Function* declareStrcpy();
    llvm::Function* declareStrcat();
    llvm::Function* declareMemcpy();

    // Array operations
    llvm::Function* declareArrayNew();
    llvm::Function* declareArrayPush();
    llvm::Function* declareArrayPop();
    llvm::Function* declareArrayGet();
    llvm::Function* declareArraySet();
    llvm::Function* declareArrayLength();

    // Array helper methods
    llvm::StructType* getOrCreateArrayType(llvm::Type* elementType);
    llvm::Value* createArrayAlloc(llvm::Type* elementType, llvm::Value* size);
    llvm::Value* getArrayLength(llvm::Value* array);
    llvm::Value* getArrayBuffer(llvm::Value* array);

    // Type conversion helpers
    llvm::Value* convertToDouble(llvm::Value* value);
    llvm::Value* convertToInt(llvm::Value* value);
    llvm::Value* convertToFloat(llvm::Value* value);

    llvm::Value* lastValue;
    llvm::Function* currentFunction;

    llvm::Function* createMainFunction();
    llvm::Function* declarePrintf();

    // Reflection API
    void implementReflectionAPI();
    void implementTypeHelpers();
    std::string getTypeName(llvm::Value* value);
    llvm::Function* declareGetType();
    llvm::Function* declareIsInstance();
    void addReflectionFunctions();
};
