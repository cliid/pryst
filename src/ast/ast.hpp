#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

// Forward declarations of all AST classes
class ASTVisitor;
class ASTNode;
class Expression;
class Statement;
class Program;
class FunctionDeclaration;
class VariableDeclaration;
class Block;
class ExpressionStatement;
class IfStatement;
class WhileStatement;
class ForStatement;
class ReturnStatement;
class BinaryExpression;
class UnaryExpression;
class LiteralExpression;
class VariableExpression;
class CallExpression;
class NewExpression;
class ClassDeclaration;
class AssignmentExpression;
class GroupingExpression;
class Parameter;

// Type classes
class Type;
class IntType;
class FloatType;
class BoolType;
class StrType;
class VoidType;
class ObjectType;

// SymbolTable class
class SymbolTable;

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};

// Base class for expressions
class Expression : public ASTNode {
public:
    virtual std::shared_ptr<Type> getType() const = 0;
    virtual void setType(std::shared_ptr<Type> type) = 0;
};

// Base class for statements
class Statement : public ASTNode {};

// Program node
class Program : public ASTNode {
public:
    std::vector<std::unique_ptr<Statement>> declarations;
    void accept(ASTVisitor& visitor) override;
};

class Parameter : public ASTNode {
public:
    std::string type;
    std::string name;

    Parameter(std::string type, std::string name)
        : type(std::move(type)), name(std::move(name)) {}

    void accept(ASTVisitor& visitor) override;
};

// Function declaration node
class FunctionDeclaration : public Statement {
public:
    std::string name;
    std::vector<Parameter> parameters;
    std::string returnType;
    std::unique_ptr<Statement> body;

    FunctionDeclaration(std::string name, std::vector<Parameter> parameters, std::string returnType, std::unique_ptr<Statement> body)
        : name(std::move(name)), parameters(std::move(parameters)), returnType(std::move(returnType)), body(std::move(body)) {}

    void accept(ASTVisitor& visitor) override;
};

// Variable declaration node
class VariableDeclaration : public Statement {
public:
    std::string type;
    std::string name;
    std::unique_ptr<Expression> initializer;

    VariableDeclaration(std::string type, std::string name, std::unique_ptr<Expression> initializer)
        : type(std::move(type)), name(std::move(name)), initializer(std::move(initializer)) {}

    void accept(ASTVisitor& visitor) override;
};

// Block node
class Block : public Statement {
public:
    std::vector<std::unique_ptr<Statement>> statements;

    Block(std::vector<std::unique_ptr<Statement>> statements)
        : statements(std::move(statements)) {}

    void accept(ASTVisitor& visitor) override;
};

// Expression statement node
class ExpressionStatement : public Statement {
public:
    std::unique_ptr<Expression> expression;

    ExpressionStatement(std::unique_ptr<Expression> expression)
        : expression(std::move(expression)) {}

    void accept(ASTVisitor& visitor) override;
};

// If statement node
class IfStatement : public Statement {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> thenBranch;
    std::unique_ptr<Statement> elseBranch;

    IfStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> thenBranch, std::unique_ptr<Statement> elseBranch)
        : condition(std::move(condition)), thenBranch(std::move(thenBranch)), elseBranch(std::move(elseBranch)) {}

    void accept(ASTVisitor& visitor) override;
};

// While statement node
class WhileStatement : public Statement {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> body;

    WhileStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> body)
        : condition(std::move(condition)), body(std::move(body)) {}

    void accept(ASTVisitor& visitor) override;
};

// For statement node
class ForStatement : public Statement {
public:
    std::unique_ptr<Statement> initializer;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> increment;
    std::unique_ptr<Statement> body;

    ForStatement(std::unique_ptr<Statement> initializer, std::unique_ptr<Expression> condition, std::unique_ptr<Expression> increment, std::unique_ptr<Statement> body)
        : initializer(std::move(initializer)), condition(std::move(condition)), increment(std::move(increment)), body(std::move(body)) {}

    void accept(ASTVisitor& visitor) override;
};

// Return statement node
class ReturnStatement : public Statement {
public:
    std::unique_ptr<Expression> value;

    ReturnStatement(std::unique_ptr<Expression> value)
        : value(std::move(value)) {}

    void accept(ASTVisitor& visitor) override;
};

// Binary expression node
class BinaryExpression : public Expression {
public:
    std::unique_ptr<Expression> left;
    std::string op;
    std::unique_ptr<Expression> right;

    BinaryExpression(std::unique_ptr<Expression> left, std::string op, std::unique_ptr<Expression> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    void accept(ASTVisitor& visitor) override;
};

// Unary expression node
class UnaryExpression : public Expression {
public:
    std::string op;
    std::unique_ptr<Expression> operand;

    UnaryExpression(std::string op, std::unique_ptr<Expression> operand)
        : op(std::move(op)), operand(std::move(operand)) {}

    void accept(ASTVisitor& visitor) override;
};

// Literal expression node
class LiteralExpression : public Expression {
public:
    std::string value;
    std::string type;
    std::shared_ptr<Type> exprType;

    LiteralExpression(const std::string& value, const std::string& type)
        : value(value), type(type) {}

    std::shared_ptr<Type> getType() const override {
        return exprType;
    }

    void setType(std::shared_ptr<Type> type) override {
        exprType = type;
    }

    void accept(ASTVisitor& visitor) override;
};

// Variable expression node
class VariableExpression : public Expression {
public:
    std::string name;
    std::shared_ptr<Type> exprType;
    
    VariableExpression(const std::string& name) : name(name) {}

    std::shared_ptr<Type> getType() const override {
        return exprType;
    }

    void setType(std::shared_ptr<Type> type) override {
        exprType = type;
    }

    void accept(ASTVisitor& visitor) override;
};

// Call expression node
class CallExpression : public Expression {
public:
    std::string callee;
    std::vector<std::unique_ptr<Expression>> arguments;
    std::shared_ptr<Type> exprType;

    std::shared_ptr<Type> getType() const override {
        return exprType;
    }

    void setType(std::shared_ptr<Type> type) override {
        exprType = type;
    }

    void accept(ASTVisitor& visitor) override;
};

// New expression node
class NewExpression : public Expression {
public:
    std::string className;
    std::vector<std::unique_ptr<Expression>> arguments;
    std::shared_ptr<Type> exprType;

    NewExpression(const std::string& className, std::vector<std::unique_ptr<Expression>> arguments)
        : className(className), arguments(std::move(arguments)) {}

    std::shared_ptr<Type> getType() const override {
        return exprType;
    }

    void setType(std::shared_ptr<Type> type) override {
        exprType = type;
    }

    void accept(ASTVisitor& visitor) override;
};

// Class declaration node
class ClassDeclaration : public Statement {
public:
    std::string name;
    std::vector<std::unique_ptr<VariableDeclaration>> fields;
    std::vector<std::unique_ptr<FunctionDeclaration>> methods;

    ClassDeclaration(std::string name, std::vector<std::unique_ptr<VariableDeclaration>> fields, std::vector<std::unique_ptr<FunctionDeclaration>> methods)
        : name(std::move(name)), fields(std::move(fields)), methods(std::move(methods)) {}

    void accept(ASTVisitor& visitor) override;
};

// Assignment expression node
class AssignmentExpression : public Expression {
public:
    std::string name;
    std::unique_ptr<Expression> value;
    std::shared_ptr<Type> exprType;

    AssignmentExpression(const std::string& name, std::unique_ptr<Expression> value)
        : name(name), value(std::move(value)) {}

    std::shared_ptr<Type> getType() const override {
        return exprType;
    }

    void setType(std::shared_ptr<Type> type) override {
        exprType = type;
    }

    void accept(ASTVisitor& visitor) override;
};

// Grouping expression node
class GroupingExpression : public Expression {
public:
    std::unique_ptr<Expression> expression;
    std::shared_ptr<Type> exprType;

    GroupingExpression(std::unique_ptr<Expression> expression)
        : expression(std::move(expression)) {}

    std::shared_ptr<Type> getType() const override {
        return exprType;
    }

    void setType(std::shared_ptr<Type> type) override {
        exprType = type;
    }

    void accept(ASTVisitor& visitor) override;
};

// ASTVisitor interface
class ASTVisitor {
public:
    virtual void visitProgram(Program& node) = 0;
    virtual void visitFunctionDeclaration(FunctionDeclaration& node) = 0;
    virtual void visitVariableDeclaration(VariableDeclaration& node) = 0;
    virtual void visitBlock(Block& node) = 0;
    virtual void visitExpressionStatement(ExpressionStatement& node) = 0;
    virtual void visitIfStatement(IfStatement& node) = 0;
    virtual void visitWhileStatement(WhileStatement& node) = 0;
    virtual void visitForStatement(ForStatement& node) = 0;
    virtual void visitReturnStatement(ReturnStatement& node) = 0;
    virtual void visitBinaryExpression(BinaryExpression& node) = 0;
    virtual void visitUnaryExpression(UnaryExpression& node) = 0;
    virtual void visitLiteralExpression(LiteralExpression& node) = 0;
    virtual void visitVariableExpression(VariableExpression& node) = 0;
    virtual void visitCallExpression(CallExpression& node) = 0;
    virtual void visitNewExpression(NewExpression& node) = 0;
    virtual void visitClassDeclaration(ClassDeclaration& node) = 0;
    virtual void visitAssignmentExpression(AssignmentExpression& node) = 0;
    virtual void visitGroupingExpression(GroupingExpression& node) = 0;
    virtual void visitParameter(Parameter& node) = 0;
};

// Type classes
class Type {
public:
    virtual ~Type() = default;
    virtual std::string getName() const = 0;
};

class IntType : public Type {
public:
    std::string getName() const override { return "int"; }
};

class FloatType : public Type {
public:
    std::string getName() const override { return "float"; }
};

class BoolType : public Type {
public:
    std::string getName() const override { return "bool"; }
};

class StrType : public Type {
public:
    std::string getName() const override { return "str"; }
};

class VoidType : public Type {
public:
    std::string getName() const override { return "void"; }
};

class ObjectType : public Type {
public:
    explicit ObjectType(const std::string& className) : className(className) {}
    std::string getName() const override { return className; }
private:
    std::string className;
};

// SymbolTable class
class SymbolTable {
public:
    void define(const std::string& name, std::shared_ptr<Type> type);
    std::shared_ptr<Type> lookup(const std::string& name) const;
    void enterScope();
    void exitScope();
    void defineClass(const std::string& name, const ClassDeclaration* classDecl);
    const ClassDeclaration* lookupClass(const std::string& name) const;

private:
    std::vector<std::unordered_map<std::string, std::shared_ptr<Type>>> scopes;
    std::unordered_map<std::string, const ClassDeclaration*> classes;
};
