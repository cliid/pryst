
// Generated from PrystLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PrystLexer : public antlr4::Lexer {
public:
  enum {
    PRINT = 1, CLASS = 2, EXTENDS = 3, ELSE = 4, FALSE = 5, FOR = 6, IF = 7, 
    NULL_ = 8, RETURN = 9, SUPER = 10, THIS = 11, TRUE = 12, WHILE = 13, 
    NEW = 14, CONVERT = 15, NAMESPACE = 16, MODULE = 17, IMPORT = 18, USING = 19, 
    LET = 20, FN = 21, CONST = 22, CONST_EXPR = 23, INT = 24, FLOAT = 25, 
    BOOL = 26, STR = 27, VOID = 28, LPAREN = 29, RPAREN = 30, LBRACE = 31, 
    RBRACE = 32, LBRACKET = 33, RBRACKET = 34, COMMA = 35, DOT = 36, MINUS = 37, 
    PLUS = 38, SEMICOLON = 39, SLASH = 40, STAR = 41, BANG = 42, EQUAL = 43, 
    GREATER = 44, LESS = 45, NOT_EQUAL = 46, EQUAL_EQUAL = 47, GREATER_EQUAL = 48, 
    LESS_EQUAL = 49, AND = 50, OR = 51, INCREMENT = 52, DECREMENT = 53, 
    PERCENT = 54, ARROW = 55, DOUBLE_COLON = 56, NUMBER = 57, IDENTIFIER = 58, 
    STRING_START = 59, COMMENT = 60, WS = 61, STRING_CONTENT = 62, ESCAPE_SEQ = 63, 
    INTERP_START = 64, STRING_END = 65
  };

  enum {
    IN_STRING = 1
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

