
// Generated from /home/ubuntu/pryst/PrystLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PrystLexer : public antlr4::Lexer {
public:
  enum {
    PRINT = 1, CLASS = 2, EXTENDS = 3, ELSE = 4, FALSE = 5, FOR = 6, IF = 7, 
    NULL_ = 8, RETURN = 9, SUPER = 10, THIS = 11, TRUE = 12, WHILE = 13, 
    NEW = 14, CONVERT = 15, NAMESPACE = 16, MODULE = 17, IMPORT = 18, USING = 19, 
    LET = 20, FN = 21, CONST = 22, CONST_EXPR = 23, TRY = 24, CATCH = 25, 
    INT = 26, FLOAT = 27, BOOL = 28, STR = 29, VOID = 30, LPAREN = 31, RPAREN = 32, 
    LBRACE = 33, RBRACE = 34, LBRACKET = 35, RBRACKET = 36, COMMA = 37, 
    DOT = 38, MINUS = 39, PLUS = 40, SEMICOLON = 41, SLASH = 42, STAR = 43, 
    BANG = 44, EQUAL = 45, GREATER = 46, LESS = 47, NOT_EQUAL = 48, EQUAL_EQUAL = 49, 
    GREATER_EQUAL = 50, LESS_EQUAL = 51, AND = 52, OR = 53, INCREMENT = 54, 
    DECREMENT = 55, PERCENT = 56, ARROW = 57, DOUBLE_COLON = 58, NUMBER = 59, 
    IDENTIFIER = 60, STRING_START = 61, COMMENT = 62, WS = 63, STRING_CONTENT = 64, 
    ESCAPE_SEQ = 65, INTERP_START = 66, STRING_END = 67
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

