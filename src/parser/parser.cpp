#include "parser.hpp"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

std::unique_ptr<Program> Parser::parse() {
    auto program = std::make_unique<Program>();
    while (!isAtEnd()) {
        program->declarations.push_back(declaration());
    }
    return program;
}

std::unique_ptr<Statement> Parser::declaration() {
    try {
        if (match(TokenType::FUNCTION)) return functionDeclaration();
        if (match(TokenType::INT) || match(TokenType::FLOAT) || 
            match(TokenType::BOOL) || match(TokenType::STR)) {
            return variableDeclaration();
        }
        return statement();
    } catch (const std::runtime_error& error) {
        synchronize();
        return nullptr;
    }
}

std::unique_ptr<FunctionDeclaration> Parser::functionDeclaration() {
    Token name = consume(TokenType::IDENTIFIER, "Expect function name.");
    consume(TokenType::LEFT_PAREN, "Expect '(' after function name.");
    std::vector<std::pair<std::string, std::string>> parameters;
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            if (parameters.size() >= 255) {
                throw error(peek(), "Can't have more than 255 parameters.");
            }
            Token type = consume({TokenType::INT, TokenType::FLOAT, TokenType::BOOL, TokenType::STR}, "Expect parameter type.");
            Token param = consume(TokenType::IDENTIFIER, "Expect parameter name.");
            parameters.emplace_back(type.lexeme, param.lexeme);
        } while (match(TokenType::COMMA));
    }
    consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");
    consume(TokenType::LEFT_BRACE, "Expect '{' before function body.");
    auto body = block();
    return std::make_unique<FunctionDeclaration>(name.lexeme, std::move(parameters), "void", std::move(body));
}

std::unique_ptr<VariableDeclaration> Parser::variableDeclaration() {
    Token type = previous();
    Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
    
    std::unique_ptr<Expression> initializer = nullptr;
    if (match(TokenType::EQUAL)) {
        initializer = expression();
    }
    
    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
    return std::make_unique<VariableDeclaration>(type.lexeme, name.lexeme, std::move(initializer));
}

std::unique_ptr<Statement> Parser::statement() {
    if (match(TokenType::IF)) return ifStatement();
    if (match(TokenType::WHILE)) return whileStatement();
    if (match(TokenType::FOR)) return forStatement();
    if (match(TokenType::RETURN)) return returnStatement();
    if (match(TokenType::LEFT_BRACE)) return block();
    return expressionStatement();
}

std::unique_ptr<Expression> Parser::expression() {
    return assignment();
}

std::unique_ptr<Expression> Parser::assignment() {
    auto expr = logicOr();
    
    if (match(TokenType::EQUAL)) {
        Token equals = previous();
        auto value = assignment();
        
        if (auto* varExpr = dynamic_cast<VariableExpression*>(expr.get())) {
            return std::make_unique<AssignmentExpression>(varExpr->name, std::move(value));
        }
        
        throw error(equals, "Invalid assignment target.");
    }
    
    return expr;
}

std::unique_ptr<Expression> Parser::primary() {
    if (match(TokenType::NEW)) {
        return newExpression();
    }
    if (match(TokenType::FALSE)) return std::make_unique<LiteralExpression>("false", "bool");
    if (match(TokenType::TRUE)) return std::make_unique<LiteralExpression>("true", "bool");
    if (match(TokenType::NULL_)) return std::make_unique<LiteralExpression>("null", "null");
    
    if (match(TokenType::NUMBER)) {
        return std::make_unique<LiteralExpression>(previous().lexeme, "number");
    }
    
    if (match(TokenType::STRING)) {
        return std::make_unique<LiteralExpression>(previous().lexeme, "string");
    }
    
    if (match(TokenType::IDENTIFIER)) {
        return std::make_unique<VariableExpression>(previous().lexeme);
    }
    
    if (match(TokenType::LEFT_PAREN)) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_unique<GroupingExpression>(std::move(expr));
    }
    
    throw error(peek(), "Expect expression.");
}

std::unique_ptr<NewExpression> Parser::newExpression() {
    Token className = consume(TokenType::IDENTIFIER, "Expect class name after 'new'.");
    consume(TokenType::LEFT_PAREN, "Expect '(' after class name.");

    std::vector<std::unique_ptr<Expression>> arguments;
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            arguments.push_back(expression());
        } while (match(TokenType::COMMA));
    }

    consume(TokenType::RIGHT_PAREN, "Expect ')' after arguments.");

    return std::make_unique<NewExpression>(className.lexeme, std::move(arguments));
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::previous() const {
    return tokens[current - 1];
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::EOF_TOKEN;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    throw error(peek(), message);
}

Token Parser::consume(std::initializer_list<TokenType> types, const std::string& message) {
    for (TokenType type : types) {
        if (check(type)) return advance();
    }
    throw error(peek(), message);
}

std::runtime_error Parser::error(const Token& token, const std::string& message) const {
    // TODO: Implement proper error handling
    return std::runtime_error(message);
}

void Parser::synchronize() {
    advance();

    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON) return;

        switch (peek().type) {
            case TokenType::CLASS:
            case TokenType::FUNCTION:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::RETURN:
                return;
            default:
                break;
        }

        advance();
    }
}
