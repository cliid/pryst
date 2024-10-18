#pragma once
#include "../token/token.hpp"
#include <string>
#include <vector>

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> scanTokens();

private:
    const std::string& source;
    std::vector<Token> tokens;
    size_t start = 0;
    size_t current = 0;
    size_t line = 1;

    bool isAtEnd() const;
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, const std::string& literal);
    bool match(char expected);
    char peek() const;
    char peekNext() const;
    void scanString();
    void scanNumber();
    void scanIdentifier();
    static bool isDigit(char c);
    static bool isAlpha(char c);
    static bool isAlphaNumeric(char c);
};
