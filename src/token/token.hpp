#pragma once
#include <string>

enum class TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    LEFT_BRACKET, RIGHT_BRACKET,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    INT, FLOAT, BOOL, STR, NULL_,
    FUNCTION, NEW,

    // End of file
    EOF_TOKEN
};

class Token {
public:
    Token(TokenType type, const std::string& lexeme, const std::string& literal, int line)
        : type(type), lexeme(lexeme), literal(literal), line(line) {}

    std::string toString() const {
        return "Token(type=" + std::to_string(static_cast<int>(type)) +
               ", lexeme='" + lexeme + "'" +
               ", literal='" + literal + "'" +
               ", line=" + std::to_string(line) + ")";
    }

    TokenType type;
    std::string lexeme;
    std::string literal;
    int line;
};
