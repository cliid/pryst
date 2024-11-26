
// Generated from src/PrystLexer.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  PrystLexer : public antlr4::Lexer {
public:
  enum {
    INTEGER = 1, FLOAT_LITERAL = 2, BOOLEAN = 3, INT = 4, FLOAT = 5, BOOL = 6, 
    STR = 7, VOID = 8, FN = 9, LET = 10, CONST = 11, CONST_EXPR = 12, CLASS = 13, 
    INTERFACE = 14, EXTENDS = 15, IMPLEMENTS = 16, RETURN = 17, IF = 18, 
    ELSE = 19, WHILE = 20, FOR = 21, IN = 22, IMPORT = 23, MODULE = 24, 
    TRY = 25, CATCH = 26, FINALLY = 27, AS = 28, BREAK = 29, CONTINUE = 30, 
    NEW = 31, MAP = 32, FROM = 33, THIS = 34, NULL_LIT = 35, INSTANCEOF = 36, 
    TYPEOF = 37, ERROR = 38, PRINT = 39, NULL_COALESCE = 40, PLUS = 41, 
    MINUS = 42, STAR = 43, SLASH = 44, PERCENT = 45, ASSIGN = 46, EQ = 47, 
    NEQ = 48, LT = 49, GT = 50, LE = 51, GE = 52, AND = 53, OR = 54, NOT = 55, 
    QUESTION_MARK = 56, COLON = 57, ARROW = 58, INC = 59, DEC = 60, LPAREN = 61, 
    RPAREN = 62, LBRACE = 63, RBRACE = 64, LBRACK = 65, RBRACK = 66, SEMICOLON = 67, 
    COMMA = 68, DOT = 69, DOUBLE_COLON = 70, IDENTIFIER = 71, STRING = 72, 
    STRING_START = 73, STRING_MIDDLE = 74, STRING_END = 75, WS = 76, COMMENT = 77, 
    BLOCK_COMMENT = 78, INVALID_CHAR = 79, INVALID_IDENTIFIER = 80, INTERP_WS = 81
  };

  enum {
    INTERPOLATION = 1
  };

  PrystLexer(antlr4::CharStream *input);
  ~PrystLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

