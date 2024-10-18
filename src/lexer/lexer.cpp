#include "lexer.hpp"
#include <cctype>
#include <unordered_map>

static const std::unordered_map<std::string, TokenType> keywords = {
    {"int", TokenType::INT},
    {"float", TokenType::FLOAT},
    {"bool", TokenType::BOOL},
    {"str", TokenType::STR},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"for", TokenType::FOR},
    {"return", TokenType::RETURN},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"null", TokenType::NULL_},
    {"new", TokenType::NEW}
};

Lexer::Lexer(const std::string& source) : source(source) {}

std::vector<Token> Lexer::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.emplace_back(TokenType::EOF_TOKEN, "", "", line);
    return tokens;
}

bool Lexer::isAtEnd() const {
    return current >= source.length();
}

void Lexer::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case '[': addToken(TokenType::LEFT_BRACKET); break;
        case ']': addToken(TokenType::RIGHT_BRACKET); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace
            break;
        case '\n':
            line++;
            break;
        case '"': scanString(); break;
        default:
            if (isDigit(c)) {
                scanNumber();
            } else if (isAlpha(c)) {
                scanIdentifier();
            } else {
                // Error handling
                // For now, we'll just ignore unrecognized characters
            }
            break;
    }
}

char Lexer::advance() {
    return source[current++];
}

void Lexer::addToken(TokenType type) {
    addToken(type, "");
}

void Lexer::addToken(TokenType type, const std::string& literal) {
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
}

bool Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;
    current++;
    return true;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNext() const {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

void Lexer::scanString() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        // Error: Unterminated string
        return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

void Lexer::scanNumber() {
    while (isDigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(TokenType::NUMBER, source.substr(start, current - start));
}

void Lexer::scanIdentifier() {
    while (isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current - start);
    TokenType type = keywords.count(text) ? keywords.at(text) : TokenType::IDENTIFIER;
    addToken(type);
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Lexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}
