#pragma once

#include "PrystBaseVisitor.h"
#include "type_metadata.hpp"
#include "type_registry.hpp"
#include "class_info.hpp"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <memory>
#include <unordered_map>
#include <any>

class LLVMCodegen : public PrystBaseVisitor {
public:
    LLVMCodegen();
    std::unique_ptr<llvm::Module> generateModule(PrystParser::ProgramContext* programCtx);

    // Type metadata methods
    void addTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo);
    void addFunctionTypeInfo(llvm::Function* function, FunctionTypeInfoPtr typeInfo);
    void addClassTypeInfo(llvm::StructType* structType, ClassTypeInfoPtr typeInfo);
    TypeInfoPtr getTypeInfo(llvm::Value* value);
    FunctionTypeInfoPtr getFunctionTypeInfo(llvm::Function* function);
    ClassTypeInfoPtr getClassTypeInfo(llvm::StructType* structType);

    // Overrides for visiting different AST nodes
    std::any visitProgram(PrystParser::ProgramContext* ctx) override;
    std::any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    std::any visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) override;
    std::any visitNamedFunction(PrystParser::NamedFunctionContext* ctx) override;
    std::any visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) override;
    std::any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    std::any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    std::any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) override;
    std::any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;
    std::any visitParamList(PrystParser::ParamListContext* ctx) override;
    std::any visitParam(PrystParser::ParamContext* ctx) override;
    std::any visitType(PrystParser::TypeContext* ctx) override;
    std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    std::any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    std::any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    std::any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    std::any visitEquality(PrystParser::EqualityContext* ctx) override;
    std::any visitComparison(PrystParser::ComparisonContext* ctx) override;
    std::any visitAddition(PrystParser::AdditionContext* ctx) override;
    std::any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    std::any visitUnary(PrystParser::UnaryContext* ctx) override;
    std::any visitPostfix(PrystParser::PostfixContext* ctx) override;
    std::any visitCall(PrystParser::CallContext* ctx) override;
    std::any visitCallSuffix(PrystParser::CallSuffixContext* ctx) override;
    std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    std::any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;
    std::any visitArguments(PrystParser::ArgumentsContext* ctx) override;

private:
    TypeRegistry& typeRegistry;  // Type registry for managing type information
    std::shared_ptr<TypeMetadata> typeMetadata;
    std::unordered_map<std::string, llvm::FunctionType*> functionTypes;
    std::unordered_map<std::string, llvm::Function*> stringFunctions;  // For string utility functions
    std::unordered_map<std::string, llvm::Function*> functions;        // For general functions
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;

    // Symbol tables for variables and functions
    std::vector<std::unordered_map<std::string, llvm::AllocaInst*>> scopeStack;
    std::unordered_map<std::string, llvm::AllocaInst*> namedValues;

    // Class member tracking
    std::unordered_map<std::string, llvm::StructType*> classTypes;
    std::unordered_map<std::string, std::unordered_map<std::string, size_t>> memberIndices;
    std::unordered_map<std::string, std::string> classInheritance;  // Maps derived class to base class

    // Helper methods
    llvm::Type* getLLVMType(const std::string& typeName);
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, const std::string& varName, llvm::Type* type);
    size_t getMemberIndex(llvm::StructType* structType, const std::string& memberName);
    void addClassMember(const std::string& className, const std::string& memberName, size_t index);

    // Type conversion methods
    llvm::Value* convertToDouble(llvm::Value* value);
    llvm::Value* convertToInt(llvm::Value* value);
    llvm::Value* convertToString(llvm::Value* value);
    llvm::Value* convertFromString(llvm::Value* value, llvm::Type* targetType);

    // Type conversion visitor methods
    std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) override;
    std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) override;

    // Scope management
    void pushScope() { scopeStack.push_back({}); }
    void popScope() { if (!scopeStack.empty()) scopeStack.pop_back(); }
    bool verifyReturnTypes(llvm::Function* function, llvm::Type* returnType);
    std::vector<llvm::Type*> collectReturnTypes(llvm::Function* function);
    llvm::Type* deduceReturnType(const std::vector<llvm::Type*>& returnTypes);

    // Type metadata and reflection methods
    llvm::Value* generateGetType(llvm::Value* value);
    llvm::Value* generateIsInstance(llvm::Value* value, const std::string& typeName);
    void attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo);
    TypeInfoPtr getLLVMTypeInfo(llvm::Type* type);
    llvm::Type* getLLVMTypeFromTypeInfo(TypeInfoPtr typeInfo);
    bool isClassType(const std::string& typeName);
    ClassTypeInfo* getClassInfo(const std::string& className);
    llvm::Value* convertValue(llvm::Value* value, const std::string& targetType);
    llvm::Value* generateMethodCall(llvm::Value* object, const std::string& methodName, const std::vector<llvm::Value*>& args);

    // Function declarations
    llvm::Function* createMainFunction();
    llvm::Function* declarePrintf();
    llvm::Function* declareBoolToStr();
    llvm::Function* declareMalloc();
    void declarePrintFunctions();  // Added declaration for print functions

    // String utility functions
    llvm::Function* declareStrlen();
    llvm::Function* declareStrcpy();
    llvm::Function* declareStrcat();
    llvm::Function* declareMemcpy();

    // Type conversion functions
    llvm::Function* declareToString();
    llvm::Function* declareToInt();
    llvm::Function* declareToFloat();

    llvm::Value* lastValue;
    llvm::Function* currentFunction;
    llvm::Function* printFunc;  // For storing print function reference
};
