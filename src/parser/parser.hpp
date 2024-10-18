#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include "../token/token.hpp"
#include "../ast/ast.hpp"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::unique_ptr<Program> parse();

private:
    const std::vector<Token>& tokens;
    size_t current;

    std::unique_ptr<Statement> declaration();
    std::unique_ptr<FunctionDeclaration> functionDeclaration();
    std::unique_ptr<VariableDeclaration> variableDeclaration();
    std::unique_ptr<Statement> statement();
    std::unique_ptr<ExpressionStatement> expressionStatement();
    std::unique_ptr<IfStatement> ifStatement();
    std::unique_ptr<WhileStatement> whileStatement();
    std::unique_ptr<ForStatement> forStatement();
    std::unique_ptr<ReturnStatement> returnStatement();
    std::unique_ptr<Block> block();
    std::unique_ptr<Expression> expression();
    std::unique_ptr<Expression> assignment();
    std::unique_ptr<Expression> logicOr();
    std::unique_ptr<Expression> logicAnd();
    std::unique_ptr<Expression> equality();
    std::unique_ptr<Expression> comparison();
    std::unique_ptr<Expression> addition();
    std::unique_ptr<Expression> multiplication();
    std::unique_ptr<Expression> unary();
    std::unique_ptr<Expression> postfix();
    std::unique_ptr<Expression> call();
    std::unique_ptr<Expression> primary();
    std::unique_ptr<NewExpression> newExpression();

    bool match(TokenType type);
    bool check(TokenType type) const;
    Token advance();
    Token peek() const;
    Token previous() const;
    bool isAtEnd() const;
    Token consume(TokenType type, const std::string& message);
    Token consume(std::initializer_list<TokenType> types, const std::string& message);
    std::runtime_error error(const Token& token, const std::string& message) const;
    void synchronize();
};
