#pragma once

#include "PrystBaseVisitor.h"
#include "module_loader.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <any>
#include <memory>

using ModuleLoader = pryst::ModuleLoader;

// SymbolTable manages variables, functions, and classes with scope handling
class SymbolTable {
public:
    // Information about variables
    struct VariableInfo {
        std::string type;
        int scopeLevel;
    };

    // Information about functions
    struct FunctionInfo {
        std::string returnType;
        std::vector<std::string> paramTypes;
        int scopeLevel;  // Added scopeLevel
    };

    // Information about classes
    struct ClassInfo {
        std::string superClassName; // Empty if no superclass
        std::unordered_map<std::string, VariableInfo> members;
        std::unordered_map<std::string, FunctionInfo> methods;
    };

    SymbolTable();

    // Scope management
    void pushScope();
    void popScope();
    int getCurrentScopeLevel() const;  // Added getter for currentScopeLevel

    // Variable management
    bool variableExists(const std::string& name) const;
    bool variableExistsInCurrentScope(const std::string& name) const;
    void addVariable(const std::string& name, const std::string& type, bool isConst = false);
    std::string getVariableType(const std::string& name) const;
    std::unordered_map<std::string, VariableInfo> getCurrentScopeVariables() const;
    void clearCurrentScopeVariables();

    // Function management
    bool functionExists(const std::string& name) const;
    void addFunction(const std::string& name, const std::string& returnType, const std::vector<std::string>& paramTypes);
    FunctionInfo getFunctionInfo(const std::string& name) const;
    std::unordered_map<std::string, FunctionInfo> getCurrentScopeFunctions() const;
    void clearCurrentScopeFunctions();

    // Class management
    bool classExists(const std::string& name) const;
    void addClass(const std::string& name, const ClassInfo& classInfo);
    ClassInfo getClassInfo(const std::string& name) const;

private:
    int currentScopeLevel;
    std::unordered_map<std::string, VariableInfo> variables;
    std::unordered_map<std::string, std::vector<FunctionInfo>> functions;
    std::unordered_map<std::string, ClassInfo> classes;
};

// SemanticAnalyzer performs semantic analysis on the AST
class SemanticAnalyzer : public PrystBaseVisitor {
public:
    SemanticAnalyzer();

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
    std::any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    std::any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    std::any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    std::any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    std::any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    std::any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
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
    std::any visitCall(PrystParser::CallContext* ctx) override;
    std::any visitCallSuffix(PrystParser::CallSuffixContext* ctx) override;
    std::any visitPrimary(PrystParser::PrimaryContext* ctx) override;
    std::any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;

private:
    SymbolTable symbolTable;
    std::string currentFunction;
    std::shared_ptr<ModuleLoader> moduleLoader;
    std::any currentCallType;  // Stores the type between visitCall and visitCallSuffix calls

    // Helper method for type checking
    void checkTypes(const std::string& expected, const std::string& actual, const std::string& errorMessage);

    // Helper methods for class member access
    std::string getMemberVariableType(const std::string& className, const std::string& memberName);
    SymbolTable::FunctionInfo getMemberFunctionInfo(const std::string& className, const std::string& methodName);
};
