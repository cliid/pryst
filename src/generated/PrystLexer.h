
// Generated from /home/ubuntu/pryst-workspace/pryst-cpp/src/PrystLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"


namespace pryst {


class  PrystLexer : public antlr4::Lexer {
public:
  enum {
    INTEGER = 1, FLOAT_LITERAL = 2, BOOLEAN = 3, INT = 4, FLOAT = 5, BOOL = 6, 
    STR = 7, VOID = 8, FN = 9, LET = 10, CONST = 11, CONST_EXPR = 12, CLASS = 13, 
    INTERFACE = 14, EXTENDS = 15, IMPLEMENTS = 16, RETURN = 17, IF = 18, 
    ELSE = 19, WHILE = 20, FOR = 21, IN = 22, IMPORT = 23, MODULE = 24, 
    TRY = 25, CATCH = 26, FINALLY = 27, AS = 28, BREAK = 29, CONTINUE = 30, 
    NEW = 31, MAP = 32, FROM = 33, THIS = 34, NULL_LIT = 35, INSTANCEOF = 36, 
    TYPEOF = 37, ERROR = 38, CHAIN = 39, PRINT = 40, NULL_COALESCE = 41, 
    PLUS = 42, MINUS = 43, STAR = 44, SLASH = 45, PERCENT = 46, ASSIGN = 47, 
    EQ = 48, NEQ = 49, LT = 50, GT = 51, LE = 52, GE = 53, AND = 54, OR = 55, 
    NOT = 56, PIPE = 57, AMP = 58, QUESTION_MARK = 59, COLON = 60, ARROW = 61, 
    INC = 62, DEC = 63, LPAREN = 64, RPAREN = 65, LBRACE = 66, RBRACE = 67, 
    LBRACK = 68, RBRACK = 69, SEMICOLON = 70, COMMA = 71, DOT = 72, DOUBLE_COLON = 73, 
    IDENTIFIER = 74, STRING = 75, STRING_START = 76, STRING_MIDDLE = 77, 
    STRING_END = 78, WS = 79, COMMENT = 80, BLOCK_COMMENT = 81, INVALID_CHAR = 82, 
    INVALID_IDENTIFIER = 83, INTERP_WS = 84
  };

  enum {
    INTERPOLATION = 1
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

}  // namespace pryst
