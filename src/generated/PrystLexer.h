
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
    INCREMENT = 24, DECREMENT = 25, PERCENT = 26, CLASS = 27, EXTENDS = 28, 
    ELSE = 29, FALSE = 30, FOR = 31, IF = 32, NULL_ = 33, RETURN = 34, SUPER = 35, 
    THIS = 36, TRUE = 37, WHILE = 38, NEW = 39, INT = 40, FLOAT = 41, BOOL = 42, 
    STR = 43, NUMBER = 44, STRING = 45, IDENTIFIER = 46, COMMENT = 47, WS = 48
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

