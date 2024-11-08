
// Generated from Pryst.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PrystLexer : public antlr4::Lexer {
public:
  enum {
    LPAREN = 1, RPAREN = 2, LBRACE = 3, RBRACE = 4, LBRACKET = 5, RBRACKET = 6, 
    COMMA = 7, DOT = 8, MINUS = 9, PLUS = 10, SEMICOLON = 11, SLASH = 12, 
    STAR = 13, BANG = 14, EQUAL = 15, GREATER = 16, LESS = 17, NOT_EQUAL = 18, 
    EQUAL_EQUAL = 19, GREATER_EQUAL = 20, LESS_EQUAL = 21, AND = 22, OR = 23, 
    INCREMENT = 24, DECREMENT = 25, PERCENT = 26, ARROW = 27, DOUBLE_COLON = 28, 
    PRINT = 29, CLASS = 30, EXTENDS = 31, ELSE = 32, FALSE = 33, FOR = 34, 
    IF = 35, NULL_ = 36, RETURN = 37, SUPER = 38, THIS = 39, TRUE = 40, 
    WHILE = 41, NEW = 42, CONVERT = 43, NAMESPACE = 44, MODULE = 45, IMPORT = 46, 
    USING = 47, LET = 48, FN = 49, CONST = 50, CONST_EXPR = 51, TRY = 52, 
    CATCH = 53, INT = 54, FLOAT = 55, BOOL = 56, STR = 57, VOID = 58, NUMBER = 59, 
    STRING = 60, IDENTIFIER = 61, COMMENT = 62, WS = 63
  };

  explicit PrystLexer(antlr4::CharStream *input);

  ~PrystLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

