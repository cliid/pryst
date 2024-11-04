
// Generated from Pryst.g4 by ANTLR 4.13.2


#include "PrystVisitor.h"

#include "PrystParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct PrystParserStaticData final {
  PrystParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PrystParserStaticData(const PrystParserStaticData&) = delete;
  PrystParserStaticData(PrystParserStaticData&&) = delete;
  PrystParserStaticData& operator=(const PrystParserStaticData&) = delete;
  PrystParserStaticData& operator=(PrystParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag prystParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<PrystParserStaticData> prystParserStaticData = nullptr;

void prystParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (prystParserStaticData != nullptr) {
    return;
  }
#else
  assert(prystParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<PrystParserStaticData>(
    std::vector<std::string>{
      "program", "declaration", "functionDecl", "namedFunction", "lambdaFunction", 
      "variableDecl", "classDeclaration", "classBody", "classMember", "paramList", 
      "param", "type", "statement", "expression", "assignment", "logicOr", 
      "logicAnd", "equality", "comparison", "addition", "multiplication", 
      "unary", "postfix", "suffix", "callSuffix", "memberSuffix", "call", 
      "primary", "newExpression", "arguments", "typeCastExpr", "typeConversionExpr", 
      "classConversionExpr"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'{'", "'}'", "'['", "']'", "','", "'.'", "'-'", 
      "'+'", "';'", "'/'", "'*'", "'!'", "'='", "'>'", "'<'", "'!='", "'=='", 
      "'>='", "'<='", "'&&'", "'||'", "'++'", "'--'", "'%'", "'=>'", "'class'", 
      "'extends'", "'else'", "'false'", "'for'", "'if'", "'null'", "'return'", 
      "'super'", "'this'", "'true'", "'while'", "'new'", "'convert'", "'int'", 
      "'float'", "'bool'", "'str'", "'void'"
    },
    std::vector<std::string>{
      "", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", 
      "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", 
      "EQUAL", "GREATER", "LESS", "NOT_EQUAL", "EQUAL_EQUAL", "GREATER_EQUAL", 
      "LESS_EQUAL", "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "ARROW", 
      "CLASS", "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", "RETURN", 
      "SUPER", "THIS", "TRUE", "WHILE", "NEW", "CONVERT", "INT", "FLOAT", 
      "BOOL", "STR", "VOID", "NUMBER", "STRING", "IDENTIFIER", "COMMENT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,407,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,1,0,5,0,68,8,0,10,0,12,0,71,
  	9,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,79,8,1,1,2,1,2,3,2,83,8,2,1,3,1,3,1,3,
  	1,3,3,3,89,8,3,1,3,1,3,1,3,5,3,94,8,3,10,3,12,3,97,9,3,1,3,1,3,1,4,3,
  	4,102,8,4,1,4,1,4,3,4,106,8,4,1,4,1,4,1,4,1,4,5,4,112,8,4,10,4,12,4,115,
  	9,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,123,8,5,1,5,1,5,1,6,1,6,1,6,1,6,3,6,131,
  	8,6,1,6,1,6,1,7,1,7,5,7,137,8,7,10,7,12,7,140,9,7,1,7,1,7,1,8,1,8,1,8,
  	1,8,3,8,148,8,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,156,8,8,1,8,1,8,1,8,5,8,161,
  	8,8,10,8,12,8,164,9,8,1,8,1,8,3,8,168,8,8,1,9,1,9,1,9,5,9,173,8,9,10,
  	9,12,9,176,9,9,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,
  	188,8,11,1,11,1,11,1,11,5,11,193,8,11,10,11,12,11,196,9,11,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,208,8,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,223,8,12,1,12,
  	3,12,226,8,12,1,12,1,12,3,12,230,8,12,1,12,1,12,1,12,1,12,3,12,236,8,
  	12,1,12,1,12,1,12,5,12,241,8,12,10,12,12,12,244,9,12,1,12,3,12,247,8,
  	12,1,13,1,13,1,13,1,13,1,13,3,13,254,8,13,1,14,1,14,1,14,3,14,259,8,14,
  	1,14,1,14,1,14,1,14,1,15,1,15,1,15,5,15,268,8,15,10,15,12,15,271,9,15,
  	1,16,1,16,1,16,5,16,276,8,16,10,16,12,16,279,9,16,1,17,1,17,1,17,5,17,
  	284,8,17,10,17,12,17,287,9,17,1,18,1,18,1,18,5,18,292,8,18,10,18,12,18,
  	295,9,18,1,19,1,19,1,19,5,19,300,8,19,10,19,12,19,303,9,19,1,20,1,20,
  	1,20,5,20,308,8,20,10,20,12,20,311,9,20,1,21,1,21,1,21,3,21,316,8,21,
  	1,22,1,22,1,22,1,22,5,22,322,8,22,10,22,12,22,325,9,22,1,23,1,23,3,23,
  	329,8,23,1,24,1,24,3,24,333,8,24,1,24,1,24,1,25,1,25,1,25,1,26,1,26,1,
  	26,5,26,343,8,26,10,26,12,26,346,9,26,1,27,1,27,1,27,1,27,1,27,1,27,1,
  	27,1,27,1,27,3,27,357,8,27,1,27,3,27,360,8,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,3,27,370,8,27,1,28,1,28,1,28,1,28,3,28,376,8,28,1,28,1,
  	28,1,29,1,29,1,29,5,29,383,8,29,10,29,12,29,386,9,29,1,30,1,30,1,30,1,
  	30,1,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,0,1,22,33,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,
  	34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,0,5,1,0,18,19,2,0,16,
  	17,20,21,1,0,9,10,2,0,12,13,26,26,3,0,9,9,14,14,24,25,440,0,69,1,0,0,
  	0,2,78,1,0,0,0,4,82,1,0,0,0,6,84,1,0,0,0,8,101,1,0,0,0,10,118,1,0,0,0,
  	12,126,1,0,0,0,14,134,1,0,0,0,16,167,1,0,0,0,18,169,1,0,0,0,20,177,1,
  	0,0,0,22,187,1,0,0,0,24,246,1,0,0,0,26,253,1,0,0,0,28,258,1,0,0,0,30,
  	264,1,0,0,0,32,272,1,0,0,0,34,280,1,0,0,0,36,288,1,0,0,0,38,296,1,0,0,
  	0,40,304,1,0,0,0,42,315,1,0,0,0,44,317,1,0,0,0,46,328,1,0,0,0,48,330,
  	1,0,0,0,50,336,1,0,0,0,52,339,1,0,0,0,54,369,1,0,0,0,56,371,1,0,0,0,58,
  	379,1,0,0,0,60,387,1,0,0,0,62,392,1,0,0,0,64,399,1,0,0,0,66,68,3,2,1,
  	0,67,66,1,0,0,0,68,71,1,0,0,0,69,67,1,0,0,0,69,70,1,0,0,0,70,72,1,0,0,
  	0,71,69,1,0,0,0,72,73,5,0,0,1,73,1,1,0,0,0,74,79,3,4,2,0,75,79,3,10,5,
  	0,76,79,3,12,6,0,77,79,3,24,12,0,78,74,1,0,0,0,78,75,1,0,0,0,78,76,1,
  	0,0,0,78,77,1,0,0,0,79,3,1,0,0,0,80,83,3,6,3,0,81,83,3,8,4,0,82,80,1,
  	0,0,0,82,81,1,0,0,0,83,5,1,0,0,0,84,85,3,22,11,0,85,86,5,49,0,0,86,88,
  	5,1,0,0,87,89,3,18,9,0,88,87,1,0,0,0,88,89,1,0,0,0,89,90,1,0,0,0,90,91,
  	5,2,0,0,91,95,5,3,0,0,92,94,3,2,1,0,93,92,1,0,0,0,94,97,1,0,0,0,95,93,
  	1,0,0,0,95,96,1,0,0,0,96,98,1,0,0,0,97,95,1,0,0,0,98,99,5,4,0,0,99,7,
  	1,0,0,0,100,102,3,22,11,0,101,100,1,0,0,0,101,102,1,0,0,0,102,103,1,0,
  	0,0,103,105,5,1,0,0,104,106,3,18,9,0,105,104,1,0,0,0,105,106,1,0,0,0,
  	106,107,1,0,0,0,107,108,5,2,0,0,108,109,5,27,0,0,109,113,5,3,0,0,110,
  	112,3,2,1,0,111,110,1,0,0,0,112,115,1,0,0,0,113,111,1,0,0,0,113,114,1,
  	0,0,0,114,116,1,0,0,0,115,113,1,0,0,0,116,117,5,4,0,0,117,9,1,0,0,0,118,
  	119,3,22,11,0,119,122,5,49,0,0,120,121,5,15,0,0,121,123,3,26,13,0,122,
  	120,1,0,0,0,122,123,1,0,0,0,123,124,1,0,0,0,124,125,5,11,0,0,125,11,1,
  	0,0,0,126,127,5,28,0,0,127,130,5,49,0,0,128,129,5,29,0,0,129,131,5,49,
  	0,0,130,128,1,0,0,0,130,131,1,0,0,0,131,132,1,0,0,0,132,133,3,14,7,0,
  	133,13,1,0,0,0,134,138,5,3,0,0,135,137,3,16,8,0,136,135,1,0,0,0,137,140,
  	1,0,0,0,138,136,1,0,0,0,138,139,1,0,0,0,139,141,1,0,0,0,140,138,1,0,0,
  	0,141,142,5,4,0,0,142,15,1,0,0,0,143,144,3,22,11,0,144,147,5,49,0,0,145,
  	146,5,15,0,0,146,148,3,26,13,0,147,145,1,0,0,0,147,148,1,0,0,0,148,149,
  	1,0,0,0,149,150,5,11,0,0,150,168,1,0,0,0,151,152,3,22,11,0,152,153,5,
  	49,0,0,153,155,5,1,0,0,154,156,3,18,9,0,155,154,1,0,0,0,155,156,1,0,0,
  	0,156,157,1,0,0,0,157,158,5,2,0,0,158,162,5,3,0,0,159,161,3,2,1,0,160,
  	159,1,0,0,0,161,164,1,0,0,0,162,160,1,0,0,0,162,163,1,0,0,0,163,165,1,
  	0,0,0,164,162,1,0,0,0,165,166,5,4,0,0,166,168,1,0,0,0,167,143,1,0,0,0,
  	167,151,1,0,0,0,168,17,1,0,0,0,169,174,3,20,10,0,170,171,5,7,0,0,171,
  	173,3,20,10,0,172,170,1,0,0,0,173,176,1,0,0,0,174,172,1,0,0,0,174,175,
  	1,0,0,0,175,19,1,0,0,0,176,174,1,0,0,0,177,178,3,22,11,0,178,179,5,49,
  	0,0,179,21,1,0,0,0,180,181,6,11,-1,0,181,188,5,42,0,0,182,188,5,43,0,
  	0,183,188,5,44,0,0,184,188,5,45,0,0,185,188,5,46,0,0,186,188,5,49,0,0,
  	187,180,1,0,0,0,187,182,1,0,0,0,187,183,1,0,0,0,187,184,1,0,0,0,187,185,
  	1,0,0,0,187,186,1,0,0,0,188,194,1,0,0,0,189,190,10,1,0,0,190,191,5,5,
  	0,0,191,193,5,6,0,0,192,189,1,0,0,0,193,196,1,0,0,0,194,192,1,0,0,0,194,
  	195,1,0,0,0,195,23,1,0,0,0,196,194,1,0,0,0,197,198,3,26,13,0,198,199,
  	5,11,0,0,199,247,1,0,0,0,200,201,5,33,0,0,201,202,5,1,0,0,202,203,3,26,
  	13,0,203,204,5,2,0,0,204,207,3,24,12,0,205,206,5,30,0,0,206,208,3,24,
  	12,0,207,205,1,0,0,0,207,208,1,0,0,0,208,247,1,0,0,0,209,210,5,39,0,0,
  	210,211,5,1,0,0,211,212,3,26,13,0,212,213,5,2,0,0,213,214,3,24,12,0,214,
  	247,1,0,0,0,215,216,5,32,0,0,216,222,5,1,0,0,217,223,3,10,5,0,218,219,
  	3,26,13,0,219,220,5,11,0,0,220,223,1,0,0,0,221,223,5,11,0,0,222,217,1,
  	0,0,0,222,218,1,0,0,0,222,221,1,0,0,0,223,225,1,0,0,0,224,226,3,26,13,
  	0,225,224,1,0,0,0,225,226,1,0,0,0,226,227,1,0,0,0,227,229,5,11,0,0,228,
  	230,3,26,13,0,229,228,1,0,0,0,229,230,1,0,0,0,230,231,1,0,0,0,231,232,
  	5,2,0,0,232,247,3,24,12,0,233,235,5,35,0,0,234,236,3,26,13,0,235,234,
  	1,0,0,0,235,236,1,0,0,0,236,237,1,0,0,0,237,247,5,11,0,0,238,242,5,3,
  	0,0,239,241,3,2,1,0,240,239,1,0,0,0,241,244,1,0,0,0,242,240,1,0,0,0,242,
  	243,1,0,0,0,243,245,1,0,0,0,244,242,1,0,0,0,245,247,5,4,0,0,246,197,1,
  	0,0,0,246,200,1,0,0,0,246,209,1,0,0,0,246,215,1,0,0,0,246,233,1,0,0,0,
  	246,238,1,0,0,0,247,25,1,0,0,0,248,254,3,28,14,0,249,254,3,60,30,0,250,
  	254,3,62,31,0,251,254,3,64,32,0,252,254,3,30,15,0,253,248,1,0,0,0,253,
  	249,1,0,0,0,253,250,1,0,0,0,253,251,1,0,0,0,253,252,1,0,0,0,254,27,1,
  	0,0,0,255,256,3,52,26,0,256,257,5,8,0,0,257,259,1,0,0,0,258,255,1,0,0,
  	0,258,259,1,0,0,0,259,260,1,0,0,0,260,261,5,49,0,0,261,262,5,15,0,0,262,
  	263,3,26,13,0,263,29,1,0,0,0,264,269,3,32,16,0,265,266,5,23,0,0,266,268,
  	3,32,16,0,267,265,1,0,0,0,268,271,1,0,0,0,269,267,1,0,0,0,269,270,1,0,
  	0,0,270,31,1,0,0,0,271,269,1,0,0,0,272,277,3,34,17,0,273,274,5,22,0,0,
  	274,276,3,34,17,0,275,273,1,0,0,0,276,279,1,0,0,0,277,275,1,0,0,0,277,
  	278,1,0,0,0,278,33,1,0,0,0,279,277,1,0,0,0,280,285,3,36,18,0,281,282,
  	7,0,0,0,282,284,3,36,18,0,283,281,1,0,0,0,284,287,1,0,0,0,285,283,1,0,
  	0,0,285,286,1,0,0,0,286,35,1,0,0,0,287,285,1,0,0,0,288,293,3,38,19,0,
  	289,290,7,1,0,0,290,292,3,38,19,0,291,289,1,0,0,0,292,295,1,0,0,0,293,
  	291,1,0,0,0,293,294,1,0,0,0,294,37,1,0,0,0,295,293,1,0,0,0,296,301,3,
  	40,20,0,297,298,7,2,0,0,298,300,3,40,20,0,299,297,1,0,0,0,300,303,1,0,
  	0,0,301,299,1,0,0,0,301,302,1,0,0,0,302,39,1,0,0,0,303,301,1,0,0,0,304,
  	309,3,42,21,0,305,306,7,3,0,0,306,308,3,42,21,0,307,305,1,0,0,0,308,311,
  	1,0,0,0,309,307,1,0,0,0,309,310,1,0,0,0,310,41,1,0,0,0,311,309,1,0,0,
  	0,312,313,7,4,0,0,313,316,3,42,21,0,314,316,3,44,22,0,315,312,1,0,0,0,
  	315,314,1,0,0,0,316,43,1,0,0,0,317,323,3,54,27,0,318,322,3,46,23,0,319,
  	322,5,24,0,0,320,322,5,25,0,0,321,318,1,0,0,0,321,319,1,0,0,0,321,320,
  	1,0,0,0,322,325,1,0,0,0,323,321,1,0,0,0,323,324,1,0,0,0,324,45,1,0,0,
  	0,325,323,1,0,0,0,326,329,3,48,24,0,327,329,3,50,25,0,328,326,1,0,0,0,
  	328,327,1,0,0,0,329,47,1,0,0,0,330,332,5,1,0,0,331,333,3,58,29,0,332,
  	331,1,0,0,0,332,333,1,0,0,0,333,334,1,0,0,0,334,335,5,2,0,0,335,49,1,
  	0,0,0,336,337,5,8,0,0,337,338,5,49,0,0,338,51,1,0,0,0,339,344,3,54,27,
  	0,340,341,5,8,0,0,341,343,5,49,0,0,342,340,1,0,0,0,343,346,1,0,0,0,344,
  	342,1,0,0,0,344,345,1,0,0,0,345,53,1,0,0,0,346,344,1,0,0,0,347,370,5,
  	38,0,0,348,370,5,31,0,0,349,370,5,34,0,0,350,370,5,37,0,0,351,370,5,47,
  	0,0,352,370,5,48,0,0,353,359,5,49,0,0,354,356,5,1,0,0,355,357,3,58,29,
  	0,356,355,1,0,0,0,356,357,1,0,0,0,357,358,1,0,0,0,358,360,5,2,0,0,359,
  	354,1,0,0,0,359,360,1,0,0,0,360,370,1,0,0,0,361,362,5,1,0,0,362,363,3,
  	26,13,0,363,364,5,2,0,0,364,370,1,0,0,0,365,366,5,36,0,0,366,367,5,8,
  	0,0,367,370,5,49,0,0,368,370,3,56,28,0,369,347,1,0,0,0,369,348,1,0,0,
  	0,369,349,1,0,0,0,369,350,1,0,0,0,369,351,1,0,0,0,369,352,1,0,0,0,369,
  	353,1,0,0,0,369,361,1,0,0,0,369,365,1,0,0,0,369,368,1,0,0,0,370,55,1,
  	0,0,0,371,372,5,40,0,0,372,373,5,49,0,0,373,375,5,1,0,0,374,376,3,58,
  	29,0,375,374,1,0,0,0,375,376,1,0,0,0,376,377,1,0,0,0,377,378,5,2,0,0,
  	378,57,1,0,0,0,379,384,3,26,13,0,380,381,5,7,0,0,381,383,3,26,13,0,382,
  	380,1,0,0,0,383,386,1,0,0,0,384,382,1,0,0,0,384,385,1,0,0,0,385,59,1,
  	0,0,0,386,384,1,0,0,0,387,388,5,1,0,0,388,389,3,22,11,0,389,390,5,2,0,
  	0,390,391,3,26,13,0,391,61,1,0,0,0,392,393,3,22,11,0,393,394,5,8,0,0,
  	394,395,5,41,0,0,395,396,5,1,0,0,396,397,3,26,13,0,397,398,5,2,0,0,398,
  	63,1,0,0,0,399,400,5,49,0,0,400,401,5,8,0,0,401,402,5,41,0,0,402,403,
  	5,1,0,0,403,404,3,26,13,0,404,405,5,2,0,0,405,65,1,0,0,0,44,69,78,82,
  	88,95,101,105,113,122,130,138,147,155,162,167,174,187,194,207,222,225,
  	229,235,242,246,253,258,269,277,285,293,301,309,315,321,323,328,332,344,
  	356,359,369,375,384
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  prystParserStaticData = std::move(staticData);
}

}

PrystParser::PrystParser(TokenStream *input) : PrystParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

PrystParser::PrystParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  PrystParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *prystParserStaticData->atn, prystParserStaticData->decisionToDFA, prystParserStaticData->sharedContextCache, options);
}

PrystParser::~PrystParser() {
  delete _interpreter;
}

const atn::ATN& PrystParser::getATN() const {
  return *prystParserStaticData->atn;
}

std::string PrystParser::getGrammarFileName() const {
  return "Pryst.g4";
}

const std::vector<std::string>& PrystParser::getRuleNames() const {
  return prystParserStaticData->ruleNames;
}

const dfa::Vocabulary& PrystParser::getVocabulary() const {
  return prystParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PrystParser::getSerializedATN() const {
  return prystParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

PrystParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::ProgramContext::EOF() {
  return getToken(PrystParser::EOF, 0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::ProgramContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::ProgramContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}


size_t PrystParser::ProgramContext::getRuleIndex() const {
  return PrystParser::RuleProgram;
}


std::any PrystParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ProgramContext* PrystParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, PrystParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1123699054887434) != 0)) {
      setState(66);
      declaration();
      setState(71);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(72);
    match(PrystParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

PrystParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::FunctionDeclContext* PrystParser::DeclarationContext::functionDecl() {
  return getRuleContext<PrystParser::FunctionDeclContext>(0);
}

PrystParser::VariableDeclContext* PrystParser::DeclarationContext::variableDecl() {
  return getRuleContext<PrystParser::VariableDeclContext>(0);
}

PrystParser::ClassDeclarationContext* PrystParser::DeclarationContext::classDeclaration() {
  return getRuleContext<PrystParser::ClassDeclarationContext>(0);
}

PrystParser::StatementContext* PrystParser::DeclarationContext::statement() {
  return getRuleContext<PrystParser::StatementContext>(0);
}


size_t PrystParser::DeclarationContext::getRuleIndex() const {
  return PrystParser::RuleDeclaration;
}


std::any PrystParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::DeclarationContext* PrystParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, PrystParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(78);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(74);
      functionDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(75);
      variableDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(76);
      classDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(77);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclContext ------------------------------------------------------------------

PrystParser::FunctionDeclContext::FunctionDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::NamedFunctionContext* PrystParser::FunctionDeclContext::namedFunction() {
  return getRuleContext<PrystParser::NamedFunctionContext>(0);
}

PrystParser::LambdaFunctionContext* PrystParser::FunctionDeclContext::lambdaFunction() {
  return getRuleContext<PrystParser::LambdaFunctionContext>(0);
}


size_t PrystParser::FunctionDeclContext::getRuleIndex() const {
  return PrystParser::RuleFunctionDecl;
}


std::any PrystParser::FunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::FunctionDeclContext* PrystParser::functionDecl() {
  FunctionDeclContext *_localctx = _tracker.createInstance<FunctionDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, PrystParser::RuleFunctionDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(82);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(80);
      namedFunction();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(81);
      lambdaFunction();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamedFunctionContext ------------------------------------------------------------------

PrystParser::NamedFunctionContext::NamedFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::TypeContext* PrystParser::NamedFunctionContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::NamedFunctionContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::NamedFunctionContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::NamedFunctionContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::NamedFunctionContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::NamedFunctionContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

PrystParser::ParamListContext* PrystParser::NamedFunctionContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::NamedFunctionContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::NamedFunctionContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}


size_t PrystParser::NamedFunctionContext::getRuleIndex() const {
  return PrystParser::RuleNamedFunction;
}


std::any PrystParser::NamedFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitNamedFunction(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::NamedFunctionContext* PrystParser::namedFunction() {
  NamedFunctionContext *_localctx = _tracker.createInstance<NamedFunctionContext>(_ctx, getState());
  enterRule(_localctx, 6, PrystParser::RuleNamedFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    type(0);
    setState(85);
    match(PrystParser::IDENTIFIER);
    setState(86);
    match(PrystParser::LPAREN);
    setState(88);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 699289395265536) != 0)) {
      setState(87);
      paramList();
    }
    setState(90);
    match(PrystParser::RPAREN);
    setState(91);
    match(PrystParser::LBRACE);
    setState(95);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1123699054887434) != 0)) {
      setState(92);
      declaration();
      setState(97);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(98);
    match(PrystParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LambdaFunctionContext ------------------------------------------------------------------

PrystParser::LambdaFunctionContext::LambdaFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::ARROW() {
  return getToken(PrystParser::ARROW, 0);
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

PrystParser::TypeContext* PrystParser::LambdaFunctionContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

PrystParser::ParamListContext* PrystParser::LambdaFunctionContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::LambdaFunctionContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::LambdaFunctionContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}


size_t PrystParser::LambdaFunctionContext::getRuleIndex() const {
  return PrystParser::RuleLambdaFunction;
}


std::any PrystParser::LambdaFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitLambdaFunction(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::LambdaFunctionContext* PrystParser::lambdaFunction() {
  LambdaFunctionContext *_localctx = _tracker.createInstance<LambdaFunctionContext>(_ctx, getState());
  enterRule(_localctx, 8, PrystParser::RuleLambdaFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 699289395265536) != 0)) {
      setState(100);
      type(0);
    }
    setState(103);
    match(PrystParser::LPAREN);
    setState(105);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 699289395265536) != 0)) {
      setState(104);
      paramList();
    }
    setState(107);
    match(PrystParser::RPAREN);
    setState(108);
    match(PrystParser::ARROW);
    setState(109);
    match(PrystParser::LBRACE);
    setState(113);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1123699054887434) != 0)) {
      setState(110);
      declaration();
      setState(115);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(116);
    match(PrystParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclContext ------------------------------------------------------------------

PrystParser::VariableDeclContext::VariableDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::TypeContext* PrystParser::VariableDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::VariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::VariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::VariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::VariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}


size_t PrystParser::VariableDeclContext::getRuleIndex() const {
  return PrystParser::RuleVariableDecl;
}


std::any PrystParser::VariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitVariableDecl(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::VariableDeclContext* PrystParser::variableDecl() {
  VariableDeclContext *_localctx = _tracker.createInstance<VariableDeclContext>(_ctx, getState());
  enterRule(_localctx, 10, PrystParser::RuleVariableDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    type(0);
    setState(119);
    match(PrystParser::IDENTIFIER);
    setState(122);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EQUAL) {
      setState(120);
      match(PrystParser::EQUAL);
      setState(121);
      expression();
    }
    setState(124);
    match(PrystParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclarationContext ------------------------------------------------------------------

PrystParser::ClassDeclarationContext::ClassDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::ClassDeclarationContext::CLASS() {
  return getToken(PrystParser::CLASS, 0);
}

std::vector<tree::TerminalNode *> PrystParser::ClassDeclarationContext::IDENTIFIER() {
  return getTokens(PrystParser::IDENTIFIER);
}

tree::TerminalNode* PrystParser::ClassDeclarationContext::IDENTIFIER(size_t i) {
  return getToken(PrystParser::IDENTIFIER, i);
}

PrystParser::ClassBodyContext* PrystParser::ClassDeclarationContext::classBody() {
  return getRuleContext<PrystParser::ClassBodyContext>(0);
}

tree::TerminalNode* PrystParser::ClassDeclarationContext::EXTENDS() {
  return getToken(PrystParser::EXTENDS, 0);
}


size_t PrystParser::ClassDeclarationContext::getRuleIndex() const {
  return PrystParser::RuleClassDeclaration;
}


std::any PrystParser::ClassDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ClassDeclarationContext* PrystParser::classDeclaration() {
  ClassDeclarationContext *_localctx = _tracker.createInstance<ClassDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 12, PrystParser::RuleClassDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    match(PrystParser::CLASS);
    setState(127);
    match(PrystParser::IDENTIFIER);
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EXTENDS) {
      setState(128);
      match(PrystParser::EXTENDS);
      setState(129);
      match(PrystParser::IDENTIFIER);
    }
    setState(132);
    classBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassBodyContext ------------------------------------------------------------------

PrystParser::ClassBodyContext::ClassBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::ClassBodyContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::ClassBodyContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

std::vector<PrystParser::ClassMemberContext *> PrystParser::ClassBodyContext::classMember() {
  return getRuleContexts<PrystParser::ClassMemberContext>();
}

PrystParser::ClassMemberContext* PrystParser::ClassBodyContext::classMember(size_t i) {
  return getRuleContext<PrystParser::ClassMemberContext>(i);
}


size_t PrystParser::ClassBodyContext::getRuleIndex() const {
  return PrystParser::RuleClassBody;
}


std::any PrystParser::ClassBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassBody(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ClassBodyContext* PrystParser::classBody() {
  ClassBodyContext *_localctx = _tracker.createInstance<ClassBodyContext>(_ctx, getState());
  enterRule(_localctx, 14, PrystParser::RuleClassBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    match(PrystParser::LBRACE);
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 699289395265536) != 0)) {
      setState(135);
      classMember();
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(141);
    match(PrystParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassMemberContext ------------------------------------------------------------------

PrystParser::ClassMemberContext::ClassMemberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PrystParser::ClassMemberContext::getRuleIndex() const {
  return PrystParser::RuleClassMember;
}

void PrystParser::ClassMemberContext::copyFrom(ClassMemberContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ClassFunctionDeclContext ------------------------------------------------------------------

PrystParser::TypeContext* PrystParser::ClassFunctionDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

PrystParser::ParamListContext* PrystParser::ClassFunctionDeclContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::ClassFunctionDeclContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::ClassFunctionDeclContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}

PrystParser::ClassFunctionDeclContext::ClassFunctionDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassFunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassVariableDeclContext ------------------------------------------------------------------

PrystParser::TypeContext* PrystParser::ClassVariableDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ClassVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::ClassVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::ClassVariableDeclContext::ClassVariableDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::ClassMemberContext* PrystParser::classMember() {
  ClassMemberContext *_localctx = _tracker.createInstance<ClassMemberContext>(_ctx, getState());
  enterRule(_localctx, 16, PrystParser::RuleClassMember);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(167);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::ClassVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(143);
      type(0);
      setState(144);
      match(PrystParser::IDENTIFIER);
      setState(147);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(145);
        match(PrystParser::EQUAL);
        setState(146);
        expression();
      }
      setState(149);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::ClassFunctionDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(151);
      type(0);
      setState(152);
      match(PrystParser::IDENTIFIER);
      setState(153);
      match(PrystParser::LPAREN);
      setState(155);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 699289395265536) != 0)) {
        setState(154);
        paramList();
      }
      setState(157);
      match(PrystParser::RPAREN);
      setState(158);
      match(PrystParser::LBRACE);
      setState(162);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1123699054887434) != 0)) {
        setState(159);
        declaration();
        setState(164);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(165);
      match(PrystParser::RBRACE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamListContext ------------------------------------------------------------------

PrystParser::ParamListContext::ParamListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::ParamContext *> PrystParser::ParamListContext::param() {
  return getRuleContexts<PrystParser::ParamContext>();
}

PrystParser::ParamContext* PrystParser::ParamListContext::param(size_t i) {
  return getRuleContext<PrystParser::ParamContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::ParamListContext::COMMA() {
  return getTokens(PrystParser::COMMA);
}

tree::TerminalNode* PrystParser::ParamListContext::COMMA(size_t i) {
  return getToken(PrystParser::COMMA, i);
}


size_t PrystParser::ParamListContext::getRuleIndex() const {
  return PrystParser::RuleParamList;
}


std::any PrystParser::ParamListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitParamList(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ParamListContext* PrystParser::paramList() {
  ParamListContext *_localctx = _tracker.createInstance<ParamListContext>(_ctx, getState());
  enterRule(_localctx, 18, PrystParser::RuleParamList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(169);
    param();
    setState(174);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(170);
      match(PrystParser::COMMA);
      setState(171);
      param();
      setState(176);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

PrystParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::TypeContext* PrystParser::ParamContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ParamContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}


size_t PrystParser::ParamContext::getRuleIndex() const {
  return PrystParser::RuleParam;
}


std::any PrystParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ParamContext* PrystParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 20, PrystParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    type(0);
    setState(178);
    match(PrystParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

PrystParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::TypeContext::INT() {
  return getToken(PrystParser::INT, 0);
}

tree::TerminalNode* PrystParser::TypeContext::FLOAT() {
  return getToken(PrystParser::FLOAT, 0);
}

tree::TerminalNode* PrystParser::TypeContext::BOOL() {
  return getToken(PrystParser::BOOL, 0);
}

tree::TerminalNode* PrystParser::TypeContext::STR() {
  return getToken(PrystParser::STR, 0);
}

tree::TerminalNode* PrystParser::TypeContext::VOID() {
  return getToken(PrystParser::VOID, 0);
}

tree::TerminalNode* PrystParser::TypeContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

PrystParser::TypeContext* PrystParser::TypeContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::TypeContext::LBRACKET() {
  return getToken(PrystParser::LBRACKET, 0);
}

tree::TerminalNode* PrystParser::TypeContext::RBRACKET() {
  return getToken(PrystParser::RBRACKET, 0);
}


size_t PrystParser::TypeContext::getRuleIndex() const {
  return PrystParser::RuleType;
}


std::any PrystParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}


PrystParser::TypeContext* PrystParser::type() {
   return type(0);
}

PrystParser::TypeContext* PrystParser::type(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PrystParser::TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, parentState);
  PrystParser::TypeContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, PrystParser::RuleType, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(187);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::INT: {
        setState(181);
        match(PrystParser::INT);
        break;
      }

      case PrystParser::FLOAT: {
        setState(182);
        match(PrystParser::FLOAT);
        break;
      }

      case PrystParser::BOOL: {
        setState(183);
        match(PrystParser::BOOL);
        break;
      }

      case PrystParser::STR: {
        setState(184);
        match(PrystParser::STR);
        break;
      }

      case PrystParser::VOID: {
        setState(185);
        match(PrystParser::VOID);
        break;
      }

      case PrystParser::IDENTIFIER: {
        setState(186);
        match(PrystParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(194);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(189);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(190);
        match(PrystParser::LBRACKET);
        setState(191);
        match(PrystParser::RBRACKET); 
      }
      setState(196);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

PrystParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PrystParser::StatementContext::getRuleIndex() const {
  return PrystParser::RuleStatement;
}

void PrystParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- WhileStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::WhileStatementContext::WHILE() {
  return getToken(PrystParser::WHILE, 0);
}

tree::TerminalNode* PrystParser::WhileStatementContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

PrystParser::ExpressionContext* PrystParser::WhileStatementContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::WhileStatementContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::StatementContext* PrystParser::WhileStatementContext::statement() {
  return getRuleContext<PrystParser::StatementContext>(0);
}

PrystParser::WhileStatementContext::WhileStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::BlockStatementContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::BlockStatementContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::BlockStatementContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::BlockStatementContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}

PrystParser::BlockStatementContext::BlockStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprStatementContext ------------------------------------------------------------------

PrystParser::ExpressionContext* PrystParser::ExprStatementContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::ExprStatementContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::ExprStatementContext::ExprStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ExprStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitExprStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ForStatementContext::FOR() {
  return getToken(PrystParser::FOR, 0);
}

tree::TerminalNode* PrystParser::ForStatementContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> PrystParser::ForStatementContext::SEMICOLON() {
  return getTokens(PrystParser::SEMICOLON);
}

tree::TerminalNode* PrystParser::ForStatementContext::SEMICOLON(size_t i) {
  return getToken(PrystParser::SEMICOLON, i);
}

tree::TerminalNode* PrystParser::ForStatementContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::StatementContext* PrystParser::ForStatementContext::statement() {
  return getRuleContext<PrystParser::StatementContext>(0);
}

PrystParser::VariableDeclContext* PrystParser::ForStatementContext::variableDecl() {
  return getRuleContext<PrystParser::VariableDeclContext>(0);
}

std::vector<PrystParser::ExpressionContext *> PrystParser::ForStatementContext::expression() {
  return getRuleContexts<PrystParser::ExpressionContext>();
}

PrystParser::ExpressionContext* PrystParser::ForStatementContext::expression(size_t i) {
  return getRuleContext<PrystParser::ExpressionContext>(i);
}

PrystParser::ForStatementContext::ForStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::IfStatementContext::IF() {
  return getToken(PrystParser::IF, 0);
}

tree::TerminalNode* PrystParser::IfStatementContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

PrystParser::ExpressionContext* PrystParser::IfStatementContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::IfStatementContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

std::vector<PrystParser::StatementContext *> PrystParser::IfStatementContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}

tree::TerminalNode* PrystParser::IfStatementContext::ELSE() {
  return getToken(PrystParser::ELSE, 0);
}

PrystParser::IfStatementContext::IfStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ReturnStatementContext::RETURN() {
  return getToken(PrystParser::RETURN, 0);
}

tree::TerminalNode* PrystParser::ReturnStatementContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::ExpressionContext* PrystParser::ReturnStatementContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::ReturnStatementContext::ReturnStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::StatementContext* PrystParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 24, PrystParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(246);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN:
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT:
      case PrystParser::FALSE:
      case PrystParser::NULL_:
      case PrystParser::SUPER:
      case PrystParser::THIS:
      case PrystParser::TRUE:
      case PrystParser::NEW:
      case PrystParser::INT:
      case PrystParser::FLOAT:
      case PrystParser::BOOL:
      case PrystParser::STR:
      case PrystParser::VOID:
      case PrystParser::NUMBER:
      case PrystParser::STRING:
      case PrystParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<PrystParser::ExprStatementContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(197);
        expression();
        setState(198);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::IF: {
        _localctx = _tracker.createInstance<PrystParser::IfStatementContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(200);
        match(PrystParser::IF);
        setState(201);
        match(PrystParser::LPAREN);
        setState(202);
        expression();
        setState(203);
        match(PrystParser::RPAREN);
        setState(204);
        statement();
        setState(207);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
        case 1: {
          setState(205);
          match(PrystParser::ELSE);
          setState(206);
          statement();
          break;
        }

        default:
          break;
        }
        break;
      }

      case PrystParser::WHILE: {
        _localctx = _tracker.createInstance<PrystParser::WhileStatementContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(209);
        match(PrystParser::WHILE);
        setState(210);
        match(PrystParser::LPAREN);
        setState(211);
        expression();
        setState(212);
        match(PrystParser::RPAREN);
        setState(213);
        statement();
        break;
      }

      case PrystParser::FOR: {
        _localctx = _tracker.createInstance<PrystParser::ForStatementContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(215);
        match(PrystParser::FOR);
        setState(216);
        match(PrystParser::LPAREN);
        setState(222);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
        case 1: {
          setState(217);
          variableDecl();
          break;
        }

        case 2: {
          setState(218);
          expression();
          setState(219);
          match(PrystParser::SEMICOLON);
          break;
        }

        case 3: {
          setState(221);
          match(PrystParser::SEMICOLON);
          break;
        }

        default:
          break;
        }
        setState(225);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1123101785997826) != 0)) {
          setState(224);
          expression();
        }
        setState(227);
        match(PrystParser::SEMICOLON);
        setState(229);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1123101785997826) != 0)) {
          setState(228);
          expression();
        }
        setState(231);
        match(PrystParser::RPAREN);
        setState(232);
        statement();
        break;
      }

      case PrystParser::RETURN: {
        _localctx = _tracker.createInstance<PrystParser::ReturnStatementContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(233);
        match(PrystParser::RETURN);
        setState(235);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1123101785997826) != 0)) {
          setState(234);
          expression();
        }
        setState(237);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::LBRACE: {
        _localctx = _tracker.createInstance<PrystParser::BlockStatementContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(238);
        match(PrystParser::LBRACE);
        setState(242);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1123699054887434) != 0)) {
          setState(239);
          declaration();
          setState(244);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(245);
        match(PrystParser::RBRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

PrystParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::AssignmentContext* PrystParser::ExpressionContext::assignment() {
  return getRuleContext<PrystParser::AssignmentContext>(0);
}

PrystParser::TypeCastExprContext* PrystParser::ExpressionContext::typeCastExpr() {
  return getRuleContext<PrystParser::TypeCastExprContext>(0);
}

PrystParser::TypeConversionExprContext* PrystParser::ExpressionContext::typeConversionExpr() {
  return getRuleContext<PrystParser::TypeConversionExprContext>(0);
}

PrystParser::ClassConversionExprContext* PrystParser::ExpressionContext::classConversionExpr() {
  return getRuleContext<PrystParser::ClassConversionExprContext>(0);
}

PrystParser::LogicOrContext* PrystParser::ExpressionContext::logicOr() {
  return getRuleContext<PrystParser::LogicOrContext>(0);
}


size_t PrystParser::ExpressionContext::getRuleIndex() const {
  return PrystParser::RuleExpression;
}


std::any PrystParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ExpressionContext* PrystParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 26, PrystParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(253);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(248);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(249);
      typeCastExpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(250);
      typeConversionExpr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(251);
      classConversionExpr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(252);
      logicOr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

PrystParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::AssignmentContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::AssignmentContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::AssignmentContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::CallContext* PrystParser::AssignmentContext::call() {
  return getRuleContext<PrystParser::CallContext>(0);
}

tree::TerminalNode* PrystParser::AssignmentContext::DOT() {
  return getToken(PrystParser::DOT, 0);
}


size_t PrystParser::AssignmentContext::getRuleIndex() const {
  return PrystParser::RuleAssignment;
}


std::any PrystParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::AssignmentContext* PrystParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 28, PrystParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      setState(255);
      call();
      setState(256);
      match(PrystParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(260);
    match(PrystParser::IDENTIFIER);
    setState(261);
    match(PrystParser::EQUAL);
    setState(262);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicOrContext ------------------------------------------------------------------

PrystParser::LogicOrContext::LogicOrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::LogicAndContext *> PrystParser::LogicOrContext::logicAnd() {
  return getRuleContexts<PrystParser::LogicAndContext>();
}

PrystParser::LogicAndContext* PrystParser::LogicOrContext::logicAnd(size_t i) {
  return getRuleContext<PrystParser::LogicAndContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::LogicOrContext::OR() {
  return getTokens(PrystParser::OR);
}

tree::TerminalNode* PrystParser::LogicOrContext::OR(size_t i) {
  return getToken(PrystParser::OR, i);
}


size_t PrystParser::LogicOrContext::getRuleIndex() const {
  return PrystParser::RuleLogicOr;
}


std::any PrystParser::LogicOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitLogicOr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::LogicOrContext* PrystParser::logicOr() {
  LogicOrContext *_localctx = _tracker.createInstance<LogicOrContext>(_ctx, getState());
  enterRule(_localctx, 30, PrystParser::RuleLogicOr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(264);
    logicAnd();
    setState(269);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::OR) {
      setState(265);
      match(PrystParser::OR);
      setState(266);
      logicAnd();
      setState(271);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicAndContext ------------------------------------------------------------------

PrystParser::LogicAndContext::LogicAndContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::EqualityContext *> PrystParser::LogicAndContext::equality() {
  return getRuleContexts<PrystParser::EqualityContext>();
}

PrystParser::EqualityContext* PrystParser::LogicAndContext::equality(size_t i) {
  return getRuleContext<PrystParser::EqualityContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::LogicAndContext::AND() {
  return getTokens(PrystParser::AND);
}

tree::TerminalNode* PrystParser::LogicAndContext::AND(size_t i) {
  return getToken(PrystParser::AND, i);
}


size_t PrystParser::LogicAndContext::getRuleIndex() const {
  return PrystParser::RuleLogicAnd;
}


std::any PrystParser::LogicAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitLogicAnd(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::LogicAndContext* PrystParser::logicAnd() {
  LogicAndContext *_localctx = _tracker.createInstance<LogicAndContext>(_ctx, getState());
  enterRule(_localctx, 32, PrystParser::RuleLogicAnd);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    equality();
    setState(277);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::AND) {
      setState(273);
      match(PrystParser::AND);
      setState(274);
      equality();
      setState(279);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityContext ------------------------------------------------------------------

PrystParser::EqualityContext::EqualityContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::ComparisonContext *> PrystParser::EqualityContext::comparison() {
  return getRuleContexts<PrystParser::ComparisonContext>();
}

PrystParser::ComparisonContext* PrystParser::EqualityContext::comparison(size_t i) {
  return getRuleContext<PrystParser::ComparisonContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::EqualityContext::NOT_EQUAL() {
  return getTokens(PrystParser::NOT_EQUAL);
}

tree::TerminalNode* PrystParser::EqualityContext::NOT_EQUAL(size_t i) {
  return getToken(PrystParser::NOT_EQUAL, i);
}

std::vector<tree::TerminalNode *> PrystParser::EqualityContext::EQUAL_EQUAL() {
  return getTokens(PrystParser::EQUAL_EQUAL);
}

tree::TerminalNode* PrystParser::EqualityContext::EQUAL_EQUAL(size_t i) {
  return getToken(PrystParser::EQUAL_EQUAL, i);
}


size_t PrystParser::EqualityContext::getRuleIndex() const {
  return PrystParser::RuleEquality;
}


std::any PrystParser::EqualityContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitEquality(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::EqualityContext* PrystParser::equality() {
  EqualityContext *_localctx = _tracker.createInstance<EqualityContext>(_ctx, getState());
  enterRule(_localctx, 34, PrystParser::RuleEquality);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    comparison();
    setState(285);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::NOT_EQUAL

    || _la == PrystParser::EQUAL_EQUAL) {
      setState(281);
      _la = _input->LA(1);
      if (!(_la == PrystParser::NOT_EQUAL

      || _la == PrystParser::EQUAL_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(282);
      comparison();
      setState(287);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonContext ------------------------------------------------------------------

PrystParser::ComparisonContext::ComparisonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::AdditionContext *> PrystParser::ComparisonContext::addition() {
  return getRuleContexts<PrystParser::AdditionContext>();
}

PrystParser::AdditionContext* PrystParser::ComparisonContext::addition(size_t i) {
  return getRuleContext<PrystParser::AdditionContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::ComparisonContext::LESS() {
  return getTokens(PrystParser::LESS);
}

tree::TerminalNode* PrystParser::ComparisonContext::LESS(size_t i) {
  return getToken(PrystParser::LESS, i);
}

std::vector<tree::TerminalNode *> PrystParser::ComparisonContext::LESS_EQUAL() {
  return getTokens(PrystParser::LESS_EQUAL);
}

tree::TerminalNode* PrystParser::ComparisonContext::LESS_EQUAL(size_t i) {
  return getToken(PrystParser::LESS_EQUAL, i);
}

std::vector<tree::TerminalNode *> PrystParser::ComparisonContext::GREATER() {
  return getTokens(PrystParser::GREATER);
}

tree::TerminalNode* PrystParser::ComparisonContext::GREATER(size_t i) {
  return getToken(PrystParser::GREATER, i);
}

std::vector<tree::TerminalNode *> PrystParser::ComparisonContext::GREATER_EQUAL() {
  return getTokens(PrystParser::GREATER_EQUAL);
}

tree::TerminalNode* PrystParser::ComparisonContext::GREATER_EQUAL(size_t i) {
  return getToken(PrystParser::GREATER_EQUAL, i);
}


size_t PrystParser::ComparisonContext::getRuleIndex() const {
  return PrystParser::RuleComparison;
}


std::any PrystParser::ComparisonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ComparisonContext* PrystParser::comparison() {
  ComparisonContext *_localctx = _tracker.createInstance<ComparisonContext>(_ctx, getState());
  enterRule(_localctx, 36, PrystParser::RuleComparison);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    addition();
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3342336) != 0)) {
      setState(289);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3342336) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(290);
      addition();
      setState(295);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditionContext ------------------------------------------------------------------

PrystParser::AdditionContext::AdditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::MultiplicationContext *> PrystParser::AdditionContext::multiplication() {
  return getRuleContexts<PrystParser::MultiplicationContext>();
}

PrystParser::MultiplicationContext* PrystParser::AdditionContext::multiplication(size_t i) {
  return getRuleContext<PrystParser::MultiplicationContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::AdditionContext::PLUS() {
  return getTokens(PrystParser::PLUS);
}

tree::TerminalNode* PrystParser::AdditionContext::PLUS(size_t i) {
  return getToken(PrystParser::PLUS, i);
}

std::vector<tree::TerminalNode *> PrystParser::AdditionContext::MINUS() {
  return getTokens(PrystParser::MINUS);
}

tree::TerminalNode* PrystParser::AdditionContext::MINUS(size_t i) {
  return getToken(PrystParser::MINUS, i);
}


size_t PrystParser::AdditionContext::getRuleIndex() const {
  return PrystParser::RuleAddition;
}


std::any PrystParser::AdditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitAddition(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::AdditionContext* PrystParser::addition() {
  AdditionContext *_localctx = _tracker.createInstance<AdditionContext>(_ctx, getState());
  enterRule(_localctx, 38, PrystParser::RuleAddition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    multiplication();
    setState(301);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::MINUS

    || _la == PrystParser::PLUS) {
      setState(297);
      _la = _input->LA(1);
      if (!(_la == PrystParser::MINUS

      || _la == PrystParser::PLUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(298);
      multiplication();
      setState(303);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicationContext ------------------------------------------------------------------

PrystParser::MultiplicationContext::MultiplicationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::UnaryContext *> PrystParser::MultiplicationContext::unary() {
  return getRuleContexts<PrystParser::UnaryContext>();
}

PrystParser::UnaryContext* PrystParser::MultiplicationContext::unary(size_t i) {
  return getRuleContext<PrystParser::UnaryContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::MultiplicationContext::STAR() {
  return getTokens(PrystParser::STAR);
}

tree::TerminalNode* PrystParser::MultiplicationContext::STAR(size_t i) {
  return getToken(PrystParser::STAR, i);
}

std::vector<tree::TerminalNode *> PrystParser::MultiplicationContext::SLASH() {
  return getTokens(PrystParser::SLASH);
}

tree::TerminalNode* PrystParser::MultiplicationContext::SLASH(size_t i) {
  return getToken(PrystParser::SLASH, i);
}

std::vector<tree::TerminalNode *> PrystParser::MultiplicationContext::PERCENT() {
  return getTokens(PrystParser::PERCENT);
}

tree::TerminalNode* PrystParser::MultiplicationContext::PERCENT(size_t i) {
  return getToken(PrystParser::PERCENT, i);
}


size_t PrystParser::MultiplicationContext::getRuleIndex() const {
  return PrystParser::RuleMultiplication;
}


std::any PrystParser::MultiplicationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitMultiplication(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::MultiplicationContext* PrystParser::multiplication() {
  MultiplicationContext *_localctx = _tracker.createInstance<MultiplicationContext>(_ctx, getState());
  enterRule(_localctx, 40, PrystParser::RuleMultiplication);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
    unary();
    setState(309);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67121152) != 0)) {
      setState(305);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 67121152) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(306);
      unary();
      setState(311);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryContext ------------------------------------------------------------------

PrystParser::UnaryContext::UnaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::UnaryContext* PrystParser::UnaryContext::unary() {
  return getRuleContext<PrystParser::UnaryContext>(0);
}

tree::TerminalNode* PrystParser::UnaryContext::BANG() {
  return getToken(PrystParser::BANG, 0);
}

tree::TerminalNode* PrystParser::UnaryContext::MINUS() {
  return getToken(PrystParser::MINUS, 0);
}

tree::TerminalNode* PrystParser::UnaryContext::INCREMENT() {
  return getToken(PrystParser::INCREMENT, 0);
}

tree::TerminalNode* PrystParser::UnaryContext::DECREMENT() {
  return getToken(PrystParser::DECREMENT, 0);
}

PrystParser::PostfixContext* PrystParser::UnaryContext::postfix() {
  return getRuleContext<PrystParser::PostfixContext>(0);
}


size_t PrystParser::UnaryContext::getRuleIndex() const {
  return PrystParser::RuleUnary;
}


std::any PrystParser::UnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitUnary(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::UnaryContext* PrystParser::unary() {
  UnaryContext *_localctx = _tracker.createInstance<UnaryContext>(_ctx, getState());
  enterRule(_localctx, 42, PrystParser::RuleUnary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(315);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT: {
        enterOuterAlt(_localctx, 1);
        setState(312);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 50348544) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(313);
        unary();
        break;
      }

      case PrystParser::LPAREN:
      case PrystParser::FALSE:
      case PrystParser::NULL_:
      case PrystParser::SUPER:
      case PrystParser::THIS:
      case PrystParser::TRUE:
      case PrystParser::NEW:
      case PrystParser::NUMBER:
      case PrystParser::STRING:
      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(314);
        postfix();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixContext ------------------------------------------------------------------

PrystParser::PostfixContext::PostfixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::PrimaryContext* PrystParser::PostfixContext::primary() {
  return getRuleContext<PrystParser::PrimaryContext>(0);
}

std::vector<PrystParser::SuffixContext *> PrystParser::PostfixContext::suffix() {
  return getRuleContexts<PrystParser::SuffixContext>();
}

PrystParser::SuffixContext* PrystParser::PostfixContext::suffix(size_t i) {
  return getRuleContext<PrystParser::SuffixContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::PostfixContext::INCREMENT() {
  return getTokens(PrystParser::INCREMENT);
}

tree::TerminalNode* PrystParser::PostfixContext::INCREMENT(size_t i) {
  return getToken(PrystParser::INCREMENT, i);
}

std::vector<tree::TerminalNode *> PrystParser::PostfixContext::DECREMENT() {
  return getTokens(PrystParser::DECREMENT);
}

tree::TerminalNode* PrystParser::PostfixContext::DECREMENT(size_t i) {
  return getToken(PrystParser::DECREMENT, i);
}


size_t PrystParser::PostfixContext::getRuleIndex() const {
  return PrystParser::RulePostfix;
}


std::any PrystParser::PostfixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitPostfix(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::PostfixContext* PrystParser::postfix() {
  PostfixContext *_localctx = _tracker.createInstance<PostfixContext>(_ctx, getState());
  enterRule(_localctx, 44, PrystParser::RulePostfix);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(317);
    primary();
    setState(323);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 50331906) != 0)) {
      setState(321);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PrystParser::LPAREN:
        case PrystParser::DOT: {
          setState(318);
          suffix();
          break;
        }

        case PrystParser::INCREMENT: {
          setState(319);
          match(PrystParser::INCREMENT);
          break;
        }

        case PrystParser::DECREMENT: {
          setState(320);
          match(PrystParser::DECREMENT);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(325);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SuffixContext ------------------------------------------------------------------

PrystParser::SuffixContext::SuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::CallSuffixContext* PrystParser::SuffixContext::callSuffix() {
  return getRuleContext<PrystParser::CallSuffixContext>(0);
}

PrystParser::MemberSuffixContext* PrystParser::SuffixContext::memberSuffix() {
  return getRuleContext<PrystParser::MemberSuffixContext>(0);
}


size_t PrystParser::SuffixContext::getRuleIndex() const {
  return PrystParser::RuleSuffix;
}


std::any PrystParser::SuffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitSuffix(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::SuffixContext* PrystParser::suffix() {
  SuffixContext *_localctx = _tracker.createInstance<SuffixContext>(_ctx, getState());
  enterRule(_localctx, 46, PrystParser::RuleSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(328);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(326);
        callSuffix();
        break;
      }

      case PrystParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(327);
        memberSuffix();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallSuffixContext ------------------------------------------------------------------

PrystParser::CallSuffixContext::CallSuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::CallSuffixContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::CallSuffixContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ArgumentsContext* PrystParser::CallSuffixContext::arguments() {
  return getRuleContext<PrystParser::ArgumentsContext>(0);
}


size_t PrystParser::CallSuffixContext::getRuleIndex() const {
  return PrystParser::RuleCallSuffix;
}


std::any PrystParser::CallSuffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitCallSuffix(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::CallSuffixContext* PrystParser::callSuffix() {
  CallSuffixContext *_localctx = _tracker.createInstance<CallSuffixContext>(_ctx, getState());
  enterRule(_localctx, 48, PrystParser::RuleCallSuffix);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(330);
    match(PrystParser::LPAREN);
    setState(332);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1123101785997826) != 0)) {
      setState(331);
      arguments();
    }
    setState(334);
    match(PrystParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemberSuffixContext ------------------------------------------------------------------

PrystParser::MemberSuffixContext::MemberSuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::MemberSuffixContext::DOT() {
  return getToken(PrystParser::DOT, 0);
}

tree::TerminalNode* PrystParser::MemberSuffixContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}


size_t PrystParser::MemberSuffixContext::getRuleIndex() const {
  return PrystParser::RuleMemberSuffix;
}


std::any PrystParser::MemberSuffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitMemberSuffix(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::MemberSuffixContext* PrystParser::memberSuffix() {
  MemberSuffixContext *_localctx = _tracker.createInstance<MemberSuffixContext>(_ctx, getState());
  enterRule(_localctx, 50, PrystParser::RuleMemberSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
    match(PrystParser::DOT);
    setState(337);
    match(PrystParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallContext ------------------------------------------------------------------

PrystParser::CallContext::CallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::PrimaryContext* PrystParser::CallContext::primary() {
  return getRuleContext<PrystParser::PrimaryContext>(0);
}

std::vector<tree::TerminalNode *> PrystParser::CallContext::DOT() {
  return getTokens(PrystParser::DOT);
}

tree::TerminalNode* PrystParser::CallContext::DOT(size_t i) {
  return getToken(PrystParser::DOT, i);
}

std::vector<tree::TerminalNode *> PrystParser::CallContext::IDENTIFIER() {
  return getTokens(PrystParser::IDENTIFIER);
}

tree::TerminalNode* PrystParser::CallContext::IDENTIFIER(size_t i) {
  return getToken(PrystParser::IDENTIFIER, i);
}


size_t PrystParser::CallContext::getRuleIndex() const {
  return PrystParser::RuleCall;
}


std::any PrystParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::CallContext* PrystParser::call() {
  CallContext *_localctx = _tracker.createInstance<CallContext>(_ctx, getState());
  enterRule(_localctx, 52, PrystParser::RuleCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(339);
    primary();
    setState(344);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(340);
        match(PrystParser::DOT);
        setState(341);
        match(PrystParser::IDENTIFIER); 
      }
      setState(346);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

PrystParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::PrimaryContext::TRUE() {
  return getToken(PrystParser::TRUE, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::FALSE() {
  return getToken(PrystParser::FALSE, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::NULL_() {
  return getToken(PrystParser::NULL_, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::THIS() {
  return getToken(PrystParser::THIS, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::NUMBER() {
  return getToken(PrystParser::NUMBER, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::STRING() {
  return getToken(PrystParser::STRING, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ArgumentsContext* PrystParser::PrimaryContext::arguments() {
  return getRuleContext<PrystParser::ArgumentsContext>(0);
}

PrystParser::ExpressionContext* PrystParser::PrimaryContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::PrimaryContext::SUPER() {
  return getToken(PrystParser::SUPER, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::DOT() {
  return getToken(PrystParser::DOT, 0);
}

PrystParser::NewExpressionContext* PrystParser::PrimaryContext::newExpression() {
  return getRuleContext<PrystParser::NewExpressionContext>(0);
}


size_t PrystParser::PrimaryContext::getRuleIndex() const {
  return PrystParser::RulePrimary;
}


std::any PrystParser::PrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitPrimary(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::PrimaryContext* PrystParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 54, PrystParser::RulePrimary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(369);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(347);
        match(PrystParser::TRUE);
        break;
      }

      case PrystParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(348);
        match(PrystParser::FALSE);
        break;
      }

      case PrystParser::NULL_: {
        enterOuterAlt(_localctx, 3);
        setState(349);
        match(PrystParser::NULL_);
        break;
      }

      case PrystParser::THIS: {
        enterOuterAlt(_localctx, 4);
        setState(350);
        match(PrystParser::THIS);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(351);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::STRING: {
        enterOuterAlt(_localctx, 6);
        setState(352);
        match(PrystParser::STRING);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 7);
        setState(353);
        match(PrystParser::IDENTIFIER);
        setState(359);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
        case 1: {
          setState(354);
          match(PrystParser::LPAREN);
          setState(356);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 1123101785997826) != 0)) {
            setState(355);
            arguments();
          }
          setState(358);
          match(PrystParser::RPAREN);
          break;
        }

        default:
          break;
        }
        break;
      }

      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 8);
        setState(361);
        match(PrystParser::LPAREN);
        setState(362);
        expression();
        setState(363);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::SUPER: {
        enterOuterAlt(_localctx, 9);
        setState(365);
        match(PrystParser::SUPER);
        setState(366);
        match(PrystParser::DOT);
        setState(367);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::NEW: {
        enterOuterAlt(_localctx, 10);
        setState(368);
        newExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NewExpressionContext ------------------------------------------------------------------

PrystParser::NewExpressionContext::NewExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::NewExpressionContext::NEW() {
  return getToken(PrystParser::NEW, 0);
}

tree::TerminalNode* PrystParser::NewExpressionContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::NewExpressionContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::NewExpressionContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ArgumentsContext* PrystParser::NewExpressionContext::arguments() {
  return getRuleContext<PrystParser::ArgumentsContext>(0);
}


size_t PrystParser::NewExpressionContext::getRuleIndex() const {
  return PrystParser::RuleNewExpression;
}


std::any PrystParser::NewExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitNewExpression(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::NewExpressionContext* PrystParser::newExpression() {
  NewExpressionContext *_localctx = _tracker.createInstance<NewExpressionContext>(_ctx, getState());
  enterRule(_localctx, 56, PrystParser::RuleNewExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(371);
    match(PrystParser::NEW);
    setState(372);
    match(PrystParser::IDENTIFIER);
    setState(373);
    match(PrystParser::LPAREN);
    setState(375);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1123101785997826) != 0)) {
      setState(374);
      arguments();
    }
    setState(377);
    match(PrystParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

PrystParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::ExpressionContext *> PrystParser::ArgumentsContext::expression() {
  return getRuleContexts<PrystParser::ExpressionContext>();
}

PrystParser::ExpressionContext* PrystParser::ArgumentsContext::expression(size_t i) {
  return getRuleContext<PrystParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::ArgumentsContext::COMMA() {
  return getTokens(PrystParser::COMMA);
}

tree::TerminalNode* PrystParser::ArgumentsContext::COMMA(size_t i) {
  return getToken(PrystParser::COMMA, i);
}


size_t PrystParser::ArgumentsContext::getRuleIndex() const {
  return PrystParser::RuleArguments;
}


std::any PrystParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ArgumentsContext* PrystParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 58, PrystParser::RuleArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(379);
    expression();
    setState(384);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(380);
      match(PrystParser::COMMA);
      setState(381);
      expression();
      setState(386);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeCastExprContext ------------------------------------------------------------------

PrystParser::TypeCastExprContext::TypeCastExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::TypeCastExprContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

PrystParser::TypeContext* PrystParser::TypeCastExprContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::TypeCastExprContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ExpressionContext* PrystParser::TypeCastExprContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}


size_t PrystParser::TypeCastExprContext::getRuleIndex() const {
  return PrystParser::RuleTypeCastExpr;
}


std::any PrystParser::TypeCastExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitTypeCastExpr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::TypeCastExprContext* PrystParser::typeCastExpr() {
  TypeCastExprContext *_localctx = _tracker.createInstance<TypeCastExprContext>(_ctx, getState());
  enterRule(_localctx, 60, PrystParser::RuleTypeCastExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(387);
    match(PrystParser::LPAREN);
    setState(388);
    type(0);
    setState(389);
    match(PrystParser::RPAREN);
    setState(390);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeConversionExprContext ------------------------------------------------------------------

PrystParser::TypeConversionExprContext::TypeConversionExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::TypeContext* PrystParser::TypeConversionExprContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::TypeConversionExprContext::DOT() {
  return getToken(PrystParser::DOT, 0);
}

tree::TerminalNode* PrystParser::TypeConversionExprContext::CONVERT() {
  return getToken(PrystParser::CONVERT, 0);
}

tree::TerminalNode* PrystParser::TypeConversionExprContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

PrystParser::ExpressionContext* PrystParser::TypeConversionExprContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::TypeConversionExprContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}


size_t PrystParser::TypeConversionExprContext::getRuleIndex() const {
  return PrystParser::RuleTypeConversionExpr;
}


std::any PrystParser::TypeConversionExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitTypeConversionExpr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::TypeConversionExprContext* PrystParser::typeConversionExpr() {
  TypeConversionExprContext *_localctx = _tracker.createInstance<TypeConversionExprContext>(_ctx, getState());
  enterRule(_localctx, 62, PrystParser::RuleTypeConversionExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(392);
    type(0);
    setState(393);
    match(PrystParser::DOT);
    setState(394);
    match(PrystParser::CONVERT);
    setState(395);
    match(PrystParser::LPAREN);
    setState(396);
    expression();
    setState(397);
    match(PrystParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassConversionExprContext ------------------------------------------------------------------

PrystParser::ClassConversionExprContext::ClassConversionExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::ClassConversionExprContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassConversionExprContext::DOT() {
  return getToken(PrystParser::DOT, 0);
}

tree::TerminalNode* PrystParser::ClassConversionExprContext::CONVERT() {
  return getToken(PrystParser::CONVERT, 0);
}

tree::TerminalNode* PrystParser::ClassConversionExprContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassConversionExprContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::ClassConversionExprContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}


size_t PrystParser::ClassConversionExprContext::getRuleIndex() const {
  return PrystParser::RuleClassConversionExpr;
}


std::any PrystParser::ClassConversionExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassConversionExpr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ClassConversionExprContext* PrystParser::classConversionExpr() {
  ClassConversionExprContext *_localctx = _tracker.createInstance<ClassConversionExprContext>(_ctx, getState());
  enterRule(_localctx, 64, PrystParser::RuleClassConversionExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(399);
    match(PrystParser::IDENTIFIER);
    setState(400);
    match(PrystParser::DOT);
    setState(401);
    match(PrystParser::CONVERT);
    setState(402);
    match(PrystParser::LPAREN);
    setState(403);
    expression();
    setState(404);
    match(PrystParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool PrystParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 11: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool PrystParser::typeSempred(TypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void PrystParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  prystParserInitialize();
#else
  ::antlr4::internal::call_once(prystParserOnceFlag, prystParserInitialize);
#endif
}
