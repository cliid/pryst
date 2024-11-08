
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
      "program", "declaration", "usingDecl", "namespaceDecl", "moduleDecl", 
      "importDecl", "importPath", "functionDecl", "namedFunction", "lambdaFunction", 
      "functionBody", "variableDecl", "classDeclaration", "classBody", "classMember", 
      "paramList", "param", "paramTypeList", "type", "statement", "expression", 
      "stringLiteral", "assignment", "logicOr", "logicAnd", "equality", 
      "comparison", "addition", "multiplication", "unary", "postfix", "suffix", 
      "callSuffix", "memberSuffix", "call", "primary", "qualifiedIdentifier", 
      "newExpression", "arguments", "typeCastExpr", "typeConversionExpr", 
      "classConversionExpr", "tryCatchStatement"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'{'", "'}'", "'['", "']'", "','", "'.'", "'-'", 
      "'+'", "';'", "'/'", "'*'", "'!'", "'='", "'>'", "'<'", "'!='", "'=='", 
      "'>='", "'<='", "'&&'", "'||'", "'++'", "'--'", "'%'", "'->'", "'::'", 
      "'print'", "'class'", "'extends'", "'else'", "'false'", "'for'", "'if'", 
      "'null'", "'return'", "'super'", "'this'", "'true'", "'while'", "'new'", 
      "'convert'", "'namespace'", "'module'", "'import'", "'using'", "'let'", 
      "'fn'", "'const'", "'const!'", "'try'", "'catch'", "'int'", "'float'", 
      "'bool'", "'str'", "'void'"
    },
    std::vector<std::string>{
      "", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", 
      "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", 
      "EQUAL", "GREATER", "LESS", "NOT_EQUAL", "EQUAL_EQUAL", "GREATER_EQUAL", 
      "LESS_EQUAL", "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "ARROW", 
      "DOUBLE_COLON", "PRINT", "CLASS", "EXTENDS", "ELSE", "FALSE", "FOR", 
      "IF", "NULL", "RETURN", "SUPER", "THIS", "TRUE", "WHILE", "NEW", "CONVERT", 
      "NAMESPACE", "MODULE", "IMPORT", "USING", "LET", "FN", "CONST", "CONST_EXPR", 
      "TRY", "CATCH", "INT", "FLOAT", "BOOL", "STR", "VOID", "NUMBER", "STRING", 
      "IDENTIFIER", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,63,645,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,1,0,1,0,1,0,1,0,5,0,91,8,0,10,0,12,0,94,9,0,1,0,1,0,1,1,1,1,1,1,1,
  	1,1,1,3,1,103,8,1,1,2,1,2,1,2,1,2,3,2,109,8,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,5,2,119,8,2,10,2,12,2,122,9,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,
  	131,8,2,10,2,12,2,134,9,2,1,2,1,2,3,2,138,8,2,1,3,1,3,1,3,1,3,1,3,5,3,
  	145,8,3,10,3,12,3,148,9,3,1,3,1,3,1,4,1,4,1,4,1,4,5,4,156,8,4,10,4,12,
  	4,159,9,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,5,6,170,8,6,10,6,12,6,173,
  	9,6,1,7,1,7,3,7,177,8,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,186,8,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,3,8,195,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	3,8,206,8,8,1,8,1,8,1,8,3,8,211,8,8,1,9,1,9,3,9,215,8,9,1,9,1,9,1,9,1,
  	9,1,9,5,9,222,8,9,10,9,12,9,225,9,9,1,9,1,9,1,9,1,9,3,9,231,8,9,1,9,1,
  	9,1,9,1,9,1,9,3,9,238,8,9,1,10,1,10,5,10,242,8,10,10,10,12,10,245,9,10,
  	1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,259,
  	8,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,270,8,11,1,12,
  	1,12,1,12,1,12,3,12,276,8,12,1,12,1,12,1,13,1,13,5,13,282,8,13,10,13,
  	12,13,285,9,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,3,14,317,8,14,1,14,1,14,1,14,1,14,1,14,3,14,
  	324,8,14,1,15,1,15,1,15,5,15,329,8,15,10,15,12,15,332,9,15,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,343,8,16,1,16,1,16,1,16,3,16,
  	348,8,16,1,17,1,17,1,17,5,17,353,8,17,10,17,12,17,356,9,17,1,18,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,371,8,18,
  	1,18,1,18,3,18,375,8,18,1,18,1,18,1,18,5,18,380,8,18,10,18,12,18,383,
  	9,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,395,8,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,
  	410,8,19,1,19,3,19,413,8,19,1,19,1,19,3,19,417,8,19,1,19,1,19,1,19,1,
  	19,3,19,423,8,19,1,19,1,19,1,19,5,19,428,8,19,10,19,12,19,431,9,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,5,19,440,8,19,10,19,12,19,443,9,19,3,
  	19,445,8,19,1,19,1,19,3,19,449,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	3,20,458,8,20,1,21,1,21,1,22,1,22,1,22,3,22,465,8,22,1,22,1,22,1,22,1,
  	22,1,23,1,23,1,23,5,23,474,8,23,10,23,12,23,477,9,23,1,24,1,24,1,24,5,
  	24,482,8,24,10,24,12,24,485,9,24,1,25,1,25,1,25,5,25,490,8,25,10,25,12,
  	25,493,9,25,1,26,1,26,1,26,5,26,498,8,26,10,26,12,26,501,9,26,1,27,1,
  	27,1,27,5,27,506,8,27,10,27,12,27,509,9,27,1,28,1,28,1,28,5,28,514,8,
  	28,10,28,12,28,517,9,28,1,29,1,29,1,29,3,29,522,8,29,1,30,1,30,1,30,1,
  	30,5,30,528,8,30,10,30,12,30,531,9,30,1,31,1,31,3,31,535,8,31,1,32,1,
  	32,3,32,539,8,32,1,32,1,32,1,33,1,33,1,33,1,33,1,33,1,33,3,33,549,8,33,
  	1,33,3,33,552,8,33,1,34,1,34,1,34,5,34,557,8,34,10,34,12,34,560,9,34,
  	1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,3,35,571,8,35,1,35,3,35,
  	574,8,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,3,35,584,8,35,1,36,1,
  	36,1,36,5,36,589,8,36,10,36,12,36,592,9,36,1,37,1,37,1,37,1,37,3,37,598,
  	8,37,1,37,1,37,1,38,1,38,1,38,5,38,605,8,38,10,38,12,38,608,9,38,1,39,
  	1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,3,39,620,8,39,1,40,1,40,
  	1,40,1,40,1,40,1,40,1,40,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,42,1,42,
  	1,42,1,42,1,42,1,42,1,42,3,42,643,8,42,1,42,0,1,36,43,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,64,66,68,70,72,74,76,78,80,82,84,0,6,2,0,48,48,50,50,1,0,18,19,
  	2,0,16,17,20,21,1,0,9,10,2,0,12,13,26,26,3,0,9,9,14,14,24,25,706,0,92,
  	1,0,0,0,2,102,1,0,0,0,4,137,1,0,0,0,6,139,1,0,0,0,8,151,1,0,0,0,10,162,
  	1,0,0,0,12,166,1,0,0,0,14,176,1,0,0,0,16,210,1,0,0,0,18,237,1,0,0,0,20,
  	239,1,0,0,0,22,269,1,0,0,0,24,271,1,0,0,0,26,279,1,0,0,0,28,323,1,0,0,
  	0,30,325,1,0,0,0,32,347,1,0,0,0,34,349,1,0,0,0,36,374,1,0,0,0,38,448,
  	1,0,0,0,40,457,1,0,0,0,42,459,1,0,0,0,44,464,1,0,0,0,46,470,1,0,0,0,48,
  	478,1,0,0,0,50,486,1,0,0,0,52,494,1,0,0,0,54,502,1,0,0,0,56,510,1,0,0,
  	0,58,521,1,0,0,0,60,523,1,0,0,0,62,534,1,0,0,0,64,536,1,0,0,0,66,551,
  	1,0,0,0,68,553,1,0,0,0,70,583,1,0,0,0,72,585,1,0,0,0,74,593,1,0,0,0,76,
  	601,1,0,0,0,78,619,1,0,0,0,80,621,1,0,0,0,82,628,1,0,0,0,84,635,1,0,0,
  	0,86,91,3,6,3,0,87,91,3,8,4,0,88,91,3,10,5,0,89,91,3,2,1,0,90,86,1,0,
  	0,0,90,87,1,0,0,0,90,88,1,0,0,0,90,89,1,0,0,0,91,94,1,0,0,0,92,90,1,0,
  	0,0,92,93,1,0,0,0,93,95,1,0,0,0,94,92,1,0,0,0,95,96,5,0,0,1,96,1,1,0,
  	0,0,97,103,3,14,7,0,98,103,3,22,11,0,99,103,3,24,12,0,100,103,3,4,2,0,
  	101,103,3,38,19,0,102,97,1,0,0,0,102,98,1,0,0,0,102,99,1,0,0,0,102,100,
  	1,0,0,0,102,101,1,0,0,0,103,3,1,0,0,0,104,105,5,47,0,0,105,109,5,44,0,
  	0,106,107,5,47,0,0,107,109,5,45,0,0,108,104,1,0,0,0,108,106,1,0,0,0,109,
  	110,1,0,0,0,110,111,3,72,36,0,111,112,5,11,0,0,112,138,1,0,0,0,113,114,
  	5,47,0,0,114,115,5,44,0,0,115,116,3,72,36,0,116,120,5,3,0,0,117,119,3,
  	2,1,0,118,117,1,0,0,0,119,122,1,0,0,0,120,118,1,0,0,0,120,121,1,0,0,0,
  	121,123,1,0,0,0,122,120,1,0,0,0,123,124,5,4,0,0,124,138,1,0,0,0,125,126,
  	5,47,0,0,126,127,5,45,0,0,127,128,3,72,36,0,128,132,5,3,0,0,129,131,3,
  	2,1,0,130,129,1,0,0,0,131,134,1,0,0,0,132,130,1,0,0,0,132,133,1,0,0,0,
  	133,135,1,0,0,0,134,132,1,0,0,0,135,136,5,4,0,0,136,138,1,0,0,0,137,108,
  	1,0,0,0,137,113,1,0,0,0,137,125,1,0,0,0,138,5,1,0,0,0,139,140,5,44,0,
  	0,140,141,3,72,36,0,141,146,5,3,0,0,142,145,3,2,1,0,143,145,3,8,4,0,144,
  	142,1,0,0,0,144,143,1,0,0,0,145,148,1,0,0,0,146,144,1,0,0,0,146,147,1,
  	0,0,0,147,149,1,0,0,0,148,146,1,0,0,0,149,150,5,4,0,0,150,7,1,0,0,0,151,
  	152,5,45,0,0,152,153,3,72,36,0,153,157,5,3,0,0,154,156,3,2,1,0,155,154,
  	1,0,0,0,156,159,1,0,0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,160,1,0,0,
  	0,159,157,1,0,0,0,160,161,5,4,0,0,161,9,1,0,0,0,162,163,5,46,0,0,163,
  	164,3,12,6,0,164,165,5,11,0,0,165,11,1,0,0,0,166,171,5,61,0,0,167,168,
  	5,28,0,0,168,170,5,61,0,0,169,167,1,0,0,0,170,173,1,0,0,0,171,169,1,0,
  	0,0,171,172,1,0,0,0,172,13,1,0,0,0,173,171,1,0,0,0,174,177,3,16,8,0,175,
  	177,3,18,9,0,176,174,1,0,0,0,176,175,1,0,0,0,177,15,1,0,0,0,178,179,5,
  	49,0,0,179,180,5,17,0,0,180,181,3,36,18,0,181,182,5,16,0,0,182,183,5,
  	61,0,0,183,185,5,1,0,0,184,186,3,30,15,0,185,184,1,0,0,0,185,186,1,0,
  	0,0,186,187,1,0,0,0,187,188,5,2,0,0,188,189,3,20,10,0,189,211,1,0,0,0,
  	190,191,5,49,0,0,191,192,5,61,0,0,192,194,5,1,0,0,193,195,3,30,15,0,194,
  	193,1,0,0,0,194,195,1,0,0,0,195,196,1,0,0,0,196,197,5,2,0,0,197,198,5,
  	27,0,0,198,199,3,36,18,0,199,200,3,20,10,0,200,211,1,0,0,0,201,202,3,
  	36,18,0,202,203,5,61,0,0,203,205,5,1,0,0,204,206,3,30,15,0,205,204,1,
  	0,0,0,205,206,1,0,0,0,206,207,1,0,0,0,207,208,5,2,0,0,208,209,3,20,10,
  	0,209,211,1,0,0,0,210,178,1,0,0,0,210,190,1,0,0,0,210,201,1,0,0,0,211,
  	17,1,0,0,0,212,214,5,1,0,0,213,215,3,30,15,0,214,213,1,0,0,0,214,215,
  	1,0,0,0,215,216,1,0,0,0,216,217,5,2,0,0,217,218,5,27,0,0,218,219,3,36,
  	18,0,219,223,5,3,0,0,220,222,3,2,1,0,221,220,1,0,0,0,222,225,1,0,0,0,
  	223,221,1,0,0,0,223,224,1,0,0,0,224,226,1,0,0,0,225,223,1,0,0,0,226,227,
  	5,4,0,0,227,238,1,0,0,0,228,230,5,1,0,0,229,231,3,30,15,0,230,229,1,0,
  	0,0,230,231,1,0,0,0,231,232,1,0,0,0,232,233,5,2,0,0,233,234,5,27,0,0,
  	234,235,3,36,18,0,235,236,3,40,20,0,236,238,1,0,0,0,237,212,1,0,0,0,237,
  	228,1,0,0,0,238,19,1,0,0,0,239,243,5,3,0,0,240,242,3,38,19,0,241,240,
  	1,0,0,0,242,245,1,0,0,0,243,241,1,0,0,0,243,244,1,0,0,0,244,246,1,0,0,
  	0,245,243,1,0,0,0,246,247,5,4,0,0,247,21,1,0,0,0,248,249,7,0,0,0,249,
  	250,5,61,0,0,250,251,5,15,0,0,251,252,3,40,20,0,252,253,5,11,0,0,253,
  	270,1,0,0,0,254,259,3,36,18,0,255,256,5,50,0,0,256,259,3,36,18,0,257,
  	259,5,51,0,0,258,254,1,0,0,0,258,255,1,0,0,0,258,257,1,0,0,0,259,260,
  	1,0,0,0,260,261,5,61,0,0,261,262,5,15,0,0,262,263,3,40,20,0,263,264,5,
  	11,0,0,264,270,1,0,0,0,265,266,3,36,18,0,266,267,5,61,0,0,267,268,5,11,
  	0,0,268,270,1,0,0,0,269,248,1,0,0,0,269,258,1,0,0,0,269,265,1,0,0,0,270,
  	23,1,0,0,0,271,272,5,30,0,0,272,275,5,61,0,0,273,274,5,31,0,0,274,276,
  	5,61,0,0,275,273,1,0,0,0,275,276,1,0,0,0,276,277,1,0,0,0,277,278,3,26,
  	13,0,278,25,1,0,0,0,279,283,5,3,0,0,280,282,3,28,14,0,281,280,1,0,0,0,
  	282,285,1,0,0,0,283,281,1,0,0,0,283,284,1,0,0,0,284,286,1,0,0,0,285,283,
  	1,0,0,0,286,287,5,4,0,0,287,27,1,0,0,0,288,289,3,36,18,0,289,290,5,61,
  	0,0,290,291,5,15,0,0,291,292,3,40,20,0,292,293,5,11,0,0,293,324,1,0,0,
  	0,294,295,5,48,0,0,295,296,5,61,0,0,296,297,5,15,0,0,297,298,3,40,20,
  	0,298,299,5,11,0,0,299,324,1,0,0,0,300,301,5,50,0,0,301,302,5,61,0,0,
  	302,303,5,15,0,0,303,304,3,40,20,0,304,305,5,11,0,0,305,324,1,0,0,0,306,
  	307,5,50,0,0,307,308,3,36,18,0,308,309,5,61,0,0,309,310,5,15,0,0,310,
  	311,3,40,20,0,311,312,5,11,0,0,312,324,1,0,0,0,313,314,5,61,0,0,314,316,
  	5,1,0,0,315,317,3,30,15,0,316,315,1,0,0,0,316,317,1,0,0,0,317,318,1,0,
  	0,0,318,319,5,2,0,0,319,320,5,27,0,0,320,321,3,36,18,0,321,322,3,20,10,
  	0,322,324,1,0,0,0,323,288,1,0,0,0,323,294,1,0,0,0,323,300,1,0,0,0,323,
  	306,1,0,0,0,323,313,1,0,0,0,324,29,1,0,0,0,325,330,3,32,16,0,326,327,
  	5,7,0,0,327,329,3,32,16,0,328,326,1,0,0,0,329,332,1,0,0,0,330,328,1,0,
  	0,0,330,331,1,0,0,0,331,31,1,0,0,0,332,330,1,0,0,0,333,334,3,36,18,0,
  	334,335,5,61,0,0,335,348,1,0,0,0,336,337,5,49,0,0,337,338,5,17,0,0,338,
  	339,3,36,18,0,339,340,5,16,0,0,340,342,5,1,0,0,341,343,3,34,17,0,342,
  	341,1,0,0,0,342,343,1,0,0,0,343,344,1,0,0,0,344,345,5,2,0,0,345,346,5,
  	61,0,0,346,348,1,0,0,0,347,333,1,0,0,0,347,336,1,0,0,0,348,33,1,0,0,0,
  	349,354,3,36,18,0,350,351,5,7,0,0,351,353,3,36,18,0,352,350,1,0,0,0,353,
  	356,1,0,0,0,354,352,1,0,0,0,354,355,1,0,0,0,355,35,1,0,0,0,356,354,1,
  	0,0,0,357,358,6,18,-1,0,358,375,5,54,0,0,359,375,5,55,0,0,360,375,5,56,
  	0,0,361,375,5,57,0,0,362,375,5,58,0,0,363,375,5,61,0,0,364,365,5,49,0,
  	0,365,366,5,17,0,0,366,367,3,36,18,0,367,368,5,16,0,0,368,370,5,1,0,0,
  	369,371,3,34,17,0,370,369,1,0,0,0,370,371,1,0,0,0,371,372,1,0,0,0,372,
  	373,5,2,0,0,373,375,1,0,0,0,374,357,1,0,0,0,374,359,1,0,0,0,374,360,1,
  	0,0,0,374,361,1,0,0,0,374,362,1,0,0,0,374,363,1,0,0,0,374,364,1,0,0,0,
  	375,381,1,0,0,0,376,377,10,2,0,0,377,378,5,5,0,0,378,380,5,6,0,0,379,
  	376,1,0,0,0,380,383,1,0,0,0,381,379,1,0,0,0,381,382,1,0,0,0,382,37,1,
  	0,0,0,383,381,1,0,0,0,384,385,3,40,20,0,385,386,5,11,0,0,386,449,1,0,
  	0,0,387,388,5,35,0,0,388,389,5,1,0,0,389,390,3,40,20,0,390,391,5,2,0,
  	0,391,394,3,38,19,0,392,393,5,32,0,0,393,395,3,38,19,0,394,392,1,0,0,
  	0,394,395,1,0,0,0,395,449,1,0,0,0,396,397,5,41,0,0,397,398,5,1,0,0,398,
  	399,3,40,20,0,399,400,5,2,0,0,400,401,3,38,19,0,401,449,1,0,0,0,402,403,
  	5,34,0,0,403,409,5,1,0,0,404,410,3,22,11,0,405,406,3,40,20,0,406,407,
  	5,11,0,0,407,410,1,0,0,0,408,410,5,11,0,0,409,404,1,0,0,0,409,405,1,0,
  	0,0,409,408,1,0,0,0,410,412,1,0,0,0,411,413,3,40,20,0,412,411,1,0,0,0,
  	412,413,1,0,0,0,413,414,1,0,0,0,414,416,5,11,0,0,415,417,3,40,20,0,416,
  	415,1,0,0,0,416,417,1,0,0,0,417,418,1,0,0,0,418,419,5,2,0,0,419,449,3,
  	38,19,0,420,422,5,37,0,0,421,423,3,40,20,0,422,421,1,0,0,0,422,423,1,
  	0,0,0,423,424,1,0,0,0,424,449,5,11,0,0,425,429,5,3,0,0,426,428,3,38,19,
  	0,427,426,1,0,0,0,428,431,1,0,0,0,429,427,1,0,0,0,429,430,1,0,0,0,430,
  	432,1,0,0,0,431,429,1,0,0,0,432,449,5,4,0,0,433,449,3,84,42,0,434,435,
  	5,29,0,0,435,444,5,1,0,0,436,441,3,40,20,0,437,438,5,7,0,0,438,440,3,
  	40,20,0,439,437,1,0,0,0,440,443,1,0,0,0,441,439,1,0,0,0,441,442,1,0,0,
  	0,442,445,1,0,0,0,443,441,1,0,0,0,444,436,1,0,0,0,444,445,1,0,0,0,445,
  	446,1,0,0,0,446,447,5,2,0,0,447,449,5,11,0,0,448,384,1,0,0,0,448,387,
  	1,0,0,0,448,396,1,0,0,0,448,402,1,0,0,0,448,420,1,0,0,0,448,425,1,0,0,
  	0,448,433,1,0,0,0,448,434,1,0,0,0,449,39,1,0,0,0,450,458,3,44,22,0,451,
  	458,3,18,9,0,452,458,3,78,39,0,453,458,3,80,40,0,454,458,3,82,41,0,455,
  	458,3,42,21,0,456,458,3,46,23,0,457,450,1,0,0,0,457,451,1,0,0,0,457,452,
  	1,0,0,0,457,453,1,0,0,0,457,454,1,0,0,0,457,455,1,0,0,0,457,456,1,0,0,
  	0,458,41,1,0,0,0,459,460,5,60,0,0,460,43,1,0,0,0,461,462,3,68,34,0,462,
  	463,5,8,0,0,463,465,1,0,0,0,464,461,1,0,0,0,464,465,1,0,0,0,465,466,1,
  	0,0,0,466,467,3,72,36,0,467,468,5,15,0,0,468,469,3,40,20,0,469,45,1,0,
  	0,0,470,475,3,48,24,0,471,472,5,23,0,0,472,474,3,48,24,0,473,471,1,0,
  	0,0,474,477,1,0,0,0,475,473,1,0,0,0,475,476,1,0,0,0,476,47,1,0,0,0,477,
  	475,1,0,0,0,478,483,3,50,25,0,479,480,5,22,0,0,480,482,3,50,25,0,481,
  	479,1,0,0,0,482,485,1,0,0,0,483,481,1,0,0,0,483,484,1,0,0,0,484,49,1,
  	0,0,0,485,483,1,0,0,0,486,491,3,52,26,0,487,488,7,1,0,0,488,490,3,52,
  	26,0,489,487,1,0,0,0,490,493,1,0,0,0,491,489,1,0,0,0,491,492,1,0,0,0,
  	492,51,1,0,0,0,493,491,1,0,0,0,494,499,3,54,27,0,495,496,7,2,0,0,496,
  	498,3,54,27,0,497,495,1,0,0,0,498,501,1,0,0,0,499,497,1,0,0,0,499,500,
  	1,0,0,0,500,53,1,0,0,0,501,499,1,0,0,0,502,507,3,56,28,0,503,504,7,3,
  	0,0,504,506,3,56,28,0,505,503,1,0,0,0,506,509,1,0,0,0,507,505,1,0,0,0,
  	507,508,1,0,0,0,508,55,1,0,0,0,509,507,1,0,0,0,510,515,3,58,29,0,511,
  	512,7,4,0,0,512,514,3,58,29,0,513,511,1,0,0,0,514,517,1,0,0,0,515,513,
  	1,0,0,0,515,516,1,0,0,0,516,57,1,0,0,0,517,515,1,0,0,0,518,519,7,5,0,
  	0,519,522,3,58,29,0,520,522,3,60,30,0,521,518,1,0,0,0,521,520,1,0,0,0,
  	522,59,1,0,0,0,523,529,3,70,35,0,524,528,3,62,31,0,525,528,5,24,0,0,526,
  	528,5,25,0,0,527,524,1,0,0,0,527,525,1,0,0,0,527,526,1,0,0,0,528,531,
  	1,0,0,0,529,527,1,0,0,0,529,530,1,0,0,0,530,61,1,0,0,0,531,529,1,0,0,
  	0,532,535,3,64,32,0,533,535,3,66,33,0,534,532,1,0,0,0,534,533,1,0,0,0,
  	535,63,1,0,0,0,536,538,5,1,0,0,537,539,3,76,38,0,538,537,1,0,0,0,538,
  	539,1,0,0,0,539,540,1,0,0,0,540,541,5,2,0,0,541,65,1,0,0,0,542,543,5,
  	8,0,0,543,552,5,61,0,0,544,545,5,8,0,0,545,546,5,61,0,0,546,548,5,1,0,
  	0,547,549,3,76,38,0,548,547,1,0,0,0,548,549,1,0,0,0,549,550,1,0,0,0,550,
  	552,5,2,0,0,551,542,1,0,0,0,551,544,1,0,0,0,552,67,1,0,0,0,553,558,3,
  	72,36,0,554,555,5,8,0,0,555,557,5,61,0,0,556,554,1,0,0,0,557,560,1,0,
  	0,0,558,556,1,0,0,0,558,559,1,0,0,0,559,69,1,0,0,0,560,558,1,0,0,0,561,
  	584,5,40,0,0,562,584,5,33,0,0,563,584,5,36,0,0,564,584,5,39,0,0,565,584,
  	5,59,0,0,566,584,5,60,0,0,567,573,3,72,36,0,568,570,5,1,0,0,569,571,3,
  	76,38,0,570,569,1,0,0,0,570,571,1,0,0,0,571,572,1,0,0,0,572,574,5,2,0,
  	0,573,568,1,0,0,0,573,574,1,0,0,0,574,584,1,0,0,0,575,576,5,1,0,0,576,
  	577,3,40,20,0,577,578,5,2,0,0,578,584,1,0,0,0,579,580,5,38,0,0,580,581,
  	5,8,0,0,581,584,5,61,0,0,582,584,3,74,37,0,583,561,1,0,0,0,583,562,1,
  	0,0,0,583,563,1,0,0,0,583,564,1,0,0,0,583,565,1,0,0,0,583,566,1,0,0,0,
  	583,567,1,0,0,0,583,575,1,0,0,0,583,579,1,0,0,0,583,582,1,0,0,0,584,71,
  	1,0,0,0,585,590,5,61,0,0,586,587,5,28,0,0,587,589,5,61,0,0,588,586,1,
  	0,0,0,589,592,1,0,0,0,590,588,1,0,0,0,590,591,1,0,0,0,591,73,1,0,0,0,
  	592,590,1,0,0,0,593,594,5,42,0,0,594,595,5,61,0,0,595,597,5,1,0,0,596,
  	598,3,76,38,0,597,596,1,0,0,0,597,598,1,0,0,0,598,599,1,0,0,0,599,600,
  	5,2,0,0,600,75,1,0,0,0,601,606,3,40,20,0,602,603,5,7,0,0,603,605,3,40,
  	20,0,604,602,1,0,0,0,605,608,1,0,0,0,606,604,1,0,0,0,606,607,1,0,0,0,
  	607,77,1,0,0,0,608,606,1,0,0,0,609,610,5,1,0,0,610,611,3,36,18,0,611,
  	612,5,2,0,0,612,613,3,40,20,0,613,620,1,0,0,0,614,615,3,36,18,0,615,616,
  	5,1,0,0,616,617,3,40,20,0,617,618,5,2,0,0,618,620,1,0,0,0,619,609,1,0,
  	0,0,619,614,1,0,0,0,620,79,1,0,0,0,621,622,3,36,18,0,622,623,5,8,0,0,
  	623,624,5,43,0,0,624,625,5,1,0,0,625,626,3,40,20,0,626,627,5,2,0,0,627,
  	81,1,0,0,0,628,629,5,61,0,0,629,630,5,8,0,0,630,631,5,43,0,0,631,632,
  	5,1,0,0,632,633,3,40,20,0,633,634,5,2,0,0,634,83,1,0,0,0,635,636,5,52,
  	0,0,636,642,3,38,19,0,637,638,5,53,0,0,638,639,5,1,0,0,639,640,5,61,0,
  	0,640,641,5,2,0,0,641,643,3,38,19,0,642,637,1,0,0,0,642,643,1,0,0,0,643,
  	85,1,0,0,0,67,90,92,102,108,120,132,137,144,146,157,171,176,185,194,205,
  	210,214,223,230,237,243,258,269,275,283,316,323,330,342,347,354,370,374,
  	381,394,409,412,416,422,429,441,444,448,457,464,475,483,491,499,507,515,
  	521,527,529,534,538,548,551,558,570,573,583,590,597,606,619,642
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

std::vector<PrystParser::NamespaceDeclContext *> PrystParser::ProgramContext::namespaceDecl() {
  return getRuleContexts<PrystParser::NamespaceDeclContext>();
}

PrystParser::NamespaceDeclContext* PrystParser::ProgramContext::namespaceDecl(size_t i) {
  return getRuleContext<PrystParser::NamespaceDeclContext>(i);
}

std::vector<PrystParser::ModuleDeclContext *> PrystParser::ProgramContext::moduleDecl() {
  return getRuleContexts<PrystParser::ModuleDeclContext>();
}

PrystParser::ModuleDeclContext* PrystParser::ProgramContext::moduleDecl(size_t i) {
  return getRuleContext<PrystParser::ModuleDeclContext>(i);
}

std::vector<PrystParser::ImportDeclContext *> PrystParser::ProgramContext::importDecl() {
  return getRuleContexts<PrystParser::ImportDeclContext>();
}

PrystParser::ImportDeclContext* PrystParser::ProgramContext::importDecl(size_t i) {
  return getRuleContext<PrystParser::ImportDeclContext>(i);
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
    setState(92);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4602670016150651402) != 0)) {
      setState(90);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PrystParser::NAMESPACE: {
          setState(86);
          namespaceDecl();
          break;
        }

        case PrystParser::MODULE: {
          setState(87);
          moduleDecl();
          break;
        }

        case PrystParser::IMPORT: {
          setState(88);
          importDecl();
          break;
        }

        case PrystParser::LPAREN:
        case PrystParser::LBRACE:
        case PrystParser::MINUS:
        case PrystParser::BANG:
        case PrystParser::INCREMENT:
        case PrystParser::DECREMENT:
        case PrystParser::PRINT:
        case PrystParser::CLASS:
        case PrystParser::FALSE:
        case PrystParser::FOR:
        case PrystParser::IF:
        case PrystParser::NULL_:
        case PrystParser::RETURN:
        case PrystParser::SUPER:
        case PrystParser::THIS:
        case PrystParser::TRUE:
        case PrystParser::WHILE:
        case PrystParser::NEW:
        case PrystParser::USING:
        case PrystParser::LET:
        case PrystParser::FN:
        case PrystParser::CONST:
        case PrystParser::CONST_EXPR:
        case PrystParser::TRY:
        case PrystParser::INT:
        case PrystParser::FLOAT:
        case PrystParser::BOOL:
        case PrystParser::STR:
        case PrystParser::VOID:
        case PrystParser::NUMBER:
        case PrystParser::STRING:
        case PrystParser::IDENTIFIER: {
          setState(89);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(94);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(95);
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

PrystParser::UsingDeclContext* PrystParser::DeclarationContext::usingDecl() {
  return getRuleContext<PrystParser::UsingDeclContext>(0);
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
    setState(102);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(97);
      functionDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(98);
      variableDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(99);
      classDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(100);
      usingDecl();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(101);
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

//----------------- UsingDeclContext ------------------------------------------------------------------

PrystParser::UsingDeclContext::UsingDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PrystParser::UsingDeclContext::getRuleIndex() const {
  return PrystParser::RuleUsingDecl;
}

void PrystParser::UsingDeclContext::copyFrom(UsingDeclContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- GlobalUsingDeclContext ------------------------------------------------------------------

PrystParser::QualifiedIdentifierContext* PrystParser::GlobalUsingDeclContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
}

tree::TerminalNode* PrystParser::GlobalUsingDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::GlobalUsingDeclContext::USING() {
  return getToken(PrystParser::USING, 0);
}

tree::TerminalNode* PrystParser::GlobalUsingDeclContext::NAMESPACE() {
  return getToken(PrystParser::NAMESPACE, 0);
}

tree::TerminalNode* PrystParser::GlobalUsingDeclContext::MODULE() {
  return getToken(PrystParser::MODULE, 0);
}

PrystParser::GlobalUsingDeclContext::GlobalUsingDeclContext(UsingDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::GlobalUsingDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitGlobalUsingDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockScopedModuleDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::BlockScopedModuleDeclContext::USING() {
  return getToken(PrystParser::USING, 0);
}

tree::TerminalNode* PrystParser::BlockScopedModuleDeclContext::MODULE() {
  return getToken(PrystParser::MODULE, 0);
}

PrystParser::QualifiedIdentifierContext* PrystParser::BlockScopedModuleDeclContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
}

tree::TerminalNode* PrystParser::BlockScopedModuleDeclContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::BlockScopedModuleDeclContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::BlockScopedModuleDeclContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::BlockScopedModuleDeclContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}

PrystParser::BlockScopedModuleDeclContext::BlockScopedModuleDeclContext(UsingDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::BlockScopedModuleDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitBlockScopedModuleDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockScopedNamespaceDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::BlockScopedNamespaceDeclContext::USING() {
  return getToken(PrystParser::USING, 0);
}

tree::TerminalNode* PrystParser::BlockScopedNamespaceDeclContext::NAMESPACE() {
  return getToken(PrystParser::NAMESPACE, 0);
}

PrystParser::QualifiedIdentifierContext* PrystParser::BlockScopedNamespaceDeclContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
}

tree::TerminalNode* PrystParser::BlockScopedNamespaceDeclContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::BlockScopedNamespaceDeclContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::BlockScopedNamespaceDeclContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::BlockScopedNamespaceDeclContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}

PrystParser::BlockScopedNamespaceDeclContext::BlockScopedNamespaceDeclContext(UsingDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::BlockScopedNamespaceDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitBlockScopedNamespaceDecl(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::UsingDeclContext* PrystParser::usingDecl() {
  UsingDeclContext *_localctx = _tracker.createInstance<UsingDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, PrystParser::RuleUsingDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(137);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::GlobalUsingDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(108);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(104);
        match(PrystParser::USING);
        setState(105);
        match(PrystParser::NAMESPACE);
        break;
      }

      case 2: {
        setState(106);
        match(PrystParser::USING);
        setState(107);
        match(PrystParser::MODULE);
        break;
      }

      default:
        break;
      }
      setState(110);
      qualifiedIdentifier();
      setState(111);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::BlockScopedNamespaceDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(113);
      match(PrystParser::USING);
      setState(114);
      match(PrystParser::NAMESPACE);
      setState(115);
      qualifiedIdentifier();
      setState(116);
      match(PrystParser::LBRACE);
      setState(120);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4602546870848340490) != 0)) {
        setState(117);
        declaration();
        setState(122);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(123);
      match(PrystParser::RBRACE);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrystParser::BlockScopedModuleDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(125);
      match(PrystParser::USING);
      setState(126);
      match(PrystParser::MODULE);
      setState(127);
      qualifiedIdentifier();
      setState(128);
      match(PrystParser::LBRACE);
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4602546870848340490) != 0)) {
        setState(129);
        declaration();
        setState(134);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(135);
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

//----------------- NamespaceDeclContext ------------------------------------------------------------------

PrystParser::NamespaceDeclContext::NamespaceDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::NamespaceDeclContext::NAMESPACE() {
  return getToken(PrystParser::NAMESPACE, 0);
}

PrystParser::QualifiedIdentifierContext* PrystParser::NamespaceDeclContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
}

tree::TerminalNode* PrystParser::NamespaceDeclContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::NamespaceDeclContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::NamespaceDeclContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::NamespaceDeclContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}

std::vector<PrystParser::ModuleDeclContext *> PrystParser::NamespaceDeclContext::moduleDecl() {
  return getRuleContexts<PrystParser::ModuleDeclContext>();
}

PrystParser::ModuleDeclContext* PrystParser::NamespaceDeclContext::moduleDecl(size_t i) {
  return getRuleContext<PrystParser::ModuleDeclContext>(i);
}


size_t PrystParser::NamespaceDeclContext::getRuleIndex() const {
  return PrystParser::RuleNamespaceDecl;
}


std::any PrystParser::NamespaceDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitNamespaceDecl(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::NamespaceDeclContext* PrystParser::namespaceDecl() {
  NamespaceDeclContext *_localctx = _tracker.createInstance<NamespaceDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, PrystParser::RuleNamespaceDecl);
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
    setState(139);
    match(PrystParser::NAMESPACE);
    setState(140);
    qualifiedIdentifier();
    setState(141);
    match(PrystParser::LBRACE);
    setState(146);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4602582055220429322) != 0)) {
      setState(144);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PrystParser::LPAREN:
        case PrystParser::LBRACE:
        case PrystParser::MINUS:
        case PrystParser::BANG:
        case PrystParser::INCREMENT:
        case PrystParser::DECREMENT:
        case PrystParser::PRINT:
        case PrystParser::CLASS:
        case PrystParser::FALSE:
        case PrystParser::FOR:
        case PrystParser::IF:
        case PrystParser::NULL_:
        case PrystParser::RETURN:
        case PrystParser::SUPER:
        case PrystParser::THIS:
        case PrystParser::TRUE:
        case PrystParser::WHILE:
        case PrystParser::NEW:
        case PrystParser::USING:
        case PrystParser::LET:
        case PrystParser::FN:
        case PrystParser::CONST:
        case PrystParser::CONST_EXPR:
        case PrystParser::TRY:
        case PrystParser::INT:
        case PrystParser::FLOAT:
        case PrystParser::BOOL:
        case PrystParser::STR:
        case PrystParser::VOID:
        case PrystParser::NUMBER:
        case PrystParser::STRING:
        case PrystParser::IDENTIFIER: {
          setState(142);
          declaration();
          break;
        }

        case PrystParser::MODULE: {
          setState(143);
          moduleDecl();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(148);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(149);
    match(PrystParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModuleDeclContext ------------------------------------------------------------------

PrystParser::ModuleDeclContext::ModuleDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::ModuleDeclContext::MODULE() {
  return getToken(PrystParser::MODULE, 0);
}

PrystParser::QualifiedIdentifierContext* PrystParser::ModuleDeclContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
}

tree::TerminalNode* PrystParser::ModuleDeclContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::ModuleDeclContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::ModuleDeclContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::ModuleDeclContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}


size_t PrystParser::ModuleDeclContext::getRuleIndex() const {
  return PrystParser::RuleModuleDecl;
}


std::any PrystParser::ModuleDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitModuleDecl(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ModuleDeclContext* PrystParser::moduleDecl() {
  ModuleDeclContext *_localctx = _tracker.createInstance<ModuleDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, PrystParser::RuleModuleDecl);
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
    setState(151);
    match(PrystParser::MODULE);
    setState(152);
    qualifiedIdentifier();
    setState(153);
    match(PrystParser::LBRACE);
    setState(157);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4602546870848340490) != 0)) {
      setState(154);
      declaration();
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(160);
    match(PrystParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportDeclContext ------------------------------------------------------------------

PrystParser::ImportDeclContext::ImportDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::ImportDeclContext::IMPORT() {
  return getToken(PrystParser::IMPORT, 0);
}

PrystParser::ImportPathContext* PrystParser::ImportDeclContext::importPath() {
  return getRuleContext<PrystParser::ImportPathContext>(0);
}

tree::TerminalNode* PrystParser::ImportDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}


size_t PrystParser::ImportDeclContext::getRuleIndex() const {
  return PrystParser::RuleImportDecl;
}


std::any PrystParser::ImportDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitImportDecl(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ImportDeclContext* PrystParser::importDecl() {
  ImportDeclContext *_localctx = _tracker.createInstance<ImportDeclContext>(_ctx, getState());
  enterRule(_localctx, 10, PrystParser::RuleImportDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    match(PrystParser::IMPORT);
    setState(163);
    importPath();
    setState(164);
    match(PrystParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportPathContext ------------------------------------------------------------------

PrystParser::ImportPathContext::ImportPathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> PrystParser::ImportPathContext::IDENTIFIER() {
  return getTokens(PrystParser::IDENTIFIER);
}

tree::TerminalNode* PrystParser::ImportPathContext::IDENTIFIER(size_t i) {
  return getToken(PrystParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> PrystParser::ImportPathContext::DOUBLE_COLON() {
  return getTokens(PrystParser::DOUBLE_COLON);
}

tree::TerminalNode* PrystParser::ImportPathContext::DOUBLE_COLON(size_t i) {
  return getToken(PrystParser::DOUBLE_COLON, i);
}


size_t PrystParser::ImportPathContext::getRuleIndex() const {
  return PrystParser::RuleImportPath;
}


std::any PrystParser::ImportPathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitImportPath(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ImportPathContext* PrystParser::importPath() {
  ImportPathContext *_localctx = _tracker.createInstance<ImportPathContext>(_ctx, getState());
  enterRule(_localctx, 12, PrystParser::RuleImportPath);
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
    setState(166);
    match(PrystParser::IDENTIFIER);
    setState(171);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::DOUBLE_COLON) {
      setState(167);
      match(PrystParser::DOUBLE_COLON);
      setState(168);
      match(PrystParser::IDENTIFIER);
      setState(173);
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
  enterRule(_localctx, 14, PrystParser::RuleFunctionDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(176);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::FN:
      case PrystParser::INT:
      case PrystParser::FLOAT:
      case PrystParser::BOOL:
      case PrystParser::STR:
      case PrystParser::VOID:
      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(174);
        namedFunction();
        break;
      }

      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(175);
        lambdaFunction();
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

//----------------- NamedFunctionContext ------------------------------------------------------------------

PrystParser::NamedFunctionContext::NamedFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::NamedFunctionContext::FN() {
  return getToken(PrystParser::FN, 0);
}

tree::TerminalNode* PrystParser::NamedFunctionContext::LESS() {
  return getToken(PrystParser::LESS, 0);
}

PrystParser::TypeContext* PrystParser::NamedFunctionContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::NamedFunctionContext::GREATER() {
  return getToken(PrystParser::GREATER, 0);
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

PrystParser::FunctionBodyContext* PrystParser::NamedFunctionContext::functionBody() {
  return getRuleContext<PrystParser::FunctionBodyContext>(0);
}

PrystParser::ParamListContext* PrystParser::NamedFunctionContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}

tree::TerminalNode* PrystParser::NamedFunctionContext::ARROW() {
  return getToken(PrystParser::ARROW, 0);
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
  enterRule(_localctx, 16, PrystParser::RuleNamedFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(178);
      match(PrystParser::FN);
      setState(179);
      match(PrystParser::LESS);
      setState(180);
      type(0);
      setState(181);
      match(PrystParser::GREATER);
      setState(182);
      match(PrystParser::IDENTIFIER);
      setState(183);
      match(PrystParser::LPAREN);
      setState(185);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2864852312961056768) != 0)) {
        setState(184);
        paramList();
      }
      setState(187);
      match(PrystParser::RPAREN);
      setState(188);
      functionBody();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(190);
      match(PrystParser::FN);
      setState(191);
      match(PrystParser::IDENTIFIER);
      setState(192);
      match(PrystParser::LPAREN);
      setState(194);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2864852312961056768) != 0)) {
        setState(193);
        paramList();
      }
      setState(196);
      match(PrystParser::RPAREN);
      setState(197);
      match(PrystParser::ARROW);
      setState(198);
      type(0);
      setState(199);
      functionBody();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(201);
      type(0);
      setState(202);
      match(PrystParser::IDENTIFIER);
      setState(203);
      match(PrystParser::LPAREN);
      setState(205);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2864852312961056768) != 0)) {
        setState(204);
        paramList();
      }
      setState(207);
      match(PrystParser::RPAREN);
      setState(208);
      functionBody();
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

PrystParser::TypeContext* PrystParser::LambdaFunctionContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
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

PrystParser::ExpressionContext* PrystParser::LambdaFunctionContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
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
  enterRule(_localctx, 18, PrystParser::RuleLambdaFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(237);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(212);
      match(PrystParser::LPAREN);
      setState(214);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2864852312961056768) != 0)) {
        setState(213);
        paramList();
      }
      setState(216);
      match(PrystParser::RPAREN);
      setState(217);
      match(PrystParser::ARROW);
      setState(218);
      type(0);
      setState(219);
      match(PrystParser::LBRACE);
      setState(223);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4602546870848340490) != 0)) {
        setState(220);
        declaration();
        setState(225);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(226);
      match(PrystParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(228);
      match(PrystParser::LPAREN);
      setState(230);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2864852312961056768) != 0)) {
        setState(229);
        paramList();
      }
      setState(232);
      match(PrystParser::RPAREN);
      setState(233);
      match(PrystParser::ARROW);
      setState(234);
      type(0);
      setState(235);
      expression();
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

//----------------- FunctionBodyContext ------------------------------------------------------------------

PrystParser::FunctionBodyContext::FunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::FunctionBodyContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::FunctionBodyContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

std::vector<PrystParser::StatementContext *> PrystParser::FunctionBodyContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::FunctionBodyContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}


size_t PrystParser::FunctionBodyContext::getRuleIndex() const {
  return PrystParser::RuleFunctionBody;
}


std::any PrystParser::FunctionBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitFunctionBody(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::FunctionBodyContext* PrystParser::functionBody() {
  FunctionBodyContext *_localctx = _tracker.createInstance<FunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 20, PrystParser::RuleFunctionBody);
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
    setState(239);
    match(PrystParser::LBRACE);
    setState(243);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4598746957589004810) != 0)) {
      setState(240);
      statement();
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(246);
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


size_t PrystParser::VariableDeclContext::getRuleIndex() const {
  return PrystParser::RuleVariableDecl;
}

void PrystParser::VariableDeclContext::copyFrom(VariableDeclContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TypedVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::TypedVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::TypedVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::TypedVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::TypedVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::TypeContext* PrystParser::TypedVariableDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::TypedVariableDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

tree::TerminalNode* PrystParser::TypedVariableDeclContext::CONST_EXPR() {
  return getToken(PrystParser::CONST_EXPR, 0);
}

PrystParser::TypedVariableDeclContext::TypedVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::TypedVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitTypedVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InferredVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::InferredVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::InferredVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::InferredVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::InferredVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::InferredVariableDeclContext::LET() {
  return getToken(PrystParser::LET, 0);
}

tree::TerminalNode* PrystParser::InferredVariableDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

PrystParser::InferredVariableDeclContext::InferredVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::InferredVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitInferredVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UninitializedVariableDeclContext ------------------------------------------------------------------

PrystParser::TypeContext* PrystParser::UninitializedVariableDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::UninitializedVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::UninitializedVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::UninitializedVariableDeclContext::UninitializedVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::UninitializedVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitUninitializedVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::VariableDeclContext* PrystParser::variableDecl() {
  VariableDeclContext *_localctx = _tracker.createInstance<VariableDeclContext>(_ctx, getState());
  enterRule(_localctx, 22, PrystParser::RuleVariableDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(269);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::InferredVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(248);
      _la = _input->LA(1);
      if (!(_la == PrystParser::LET

      || _la == PrystParser::CONST)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(249);
      match(PrystParser::IDENTIFIER);
      setState(250);
      match(PrystParser::EQUAL);
      setState(251);
      expression();
      setState(252);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::TypedVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(258);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PrystParser::FN:
        case PrystParser::INT:
        case PrystParser::FLOAT:
        case PrystParser::BOOL:
        case PrystParser::STR:
        case PrystParser::VOID:
        case PrystParser::IDENTIFIER: {
          setState(254);
          type(0);
          break;
        }

        case PrystParser::CONST: {
          setState(255);
          match(PrystParser::CONST);
          setState(256);
          type(0);
          break;
        }

        case PrystParser::CONST_EXPR: {
          setState(257);
          match(PrystParser::CONST_EXPR);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(260);
      match(PrystParser::IDENTIFIER);
      setState(261);
      match(PrystParser::EQUAL);
      setState(262);
      expression();
      setState(263);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrystParser::UninitializedVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(265);
      type(0);
      setState(266);
      match(PrystParser::IDENTIFIER);
      setState(267);
      match(PrystParser::SEMICOLON);
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
  enterRule(_localctx, 24, PrystParser::RuleClassDeclaration);
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
    setState(271);
    match(PrystParser::CLASS);
    setState(272);
    match(PrystParser::IDENTIFIER);
    setState(275);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EXTENDS) {
      setState(273);
      match(PrystParser::EXTENDS);
      setState(274);
      match(PrystParser::IDENTIFIER);
    }
    setState(277);
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
  enterRule(_localctx, 26, PrystParser::RuleClassBody);
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
    setState(279);
    match(PrystParser::LBRACE);
    setState(283);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2866259687844610048) != 0)) {
      setState(280);
      classMember();
      setState(285);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(286);
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

//----------------- ClassTypedVariableDeclContext ------------------------------------------------------------------

PrystParser::TypeContext* PrystParser::ClassTypedVariableDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ClassTypedVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassTypedVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassTypedVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::ClassTypedVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::ClassTypedVariableDeclContext::ClassTypedVariableDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassTypedVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassTypedVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassFunctionDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::ClassFunctionDeclContext::ARROW() {
  return getToken(PrystParser::ARROW, 0);
}

PrystParser::TypeContext* PrystParser::ClassFunctionDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

PrystParser::FunctionBodyContext* PrystParser::ClassFunctionDeclContext::functionBody() {
  return getRuleContext<PrystParser::FunctionBodyContext>(0);
}

PrystParser::ParamListContext* PrystParser::ClassFunctionDeclContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}

PrystParser::ClassFunctionDeclContext::ClassFunctionDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassFunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassConstTypedDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassConstTypedDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

PrystParser::TypeContext* PrystParser::ClassConstTypedDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ClassConstTypedDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassConstTypedDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassConstTypedDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::ClassConstTypedDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::ClassConstTypedDeclContext::ClassConstTypedDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassConstTypedDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassConstTypedDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassInferredVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassInferredVariableDeclContext::LET() {
  return getToken(PrystParser::LET, 0);
}

tree::TerminalNode* PrystParser::ClassInferredVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassInferredVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassInferredVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::ClassInferredVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::ClassInferredVariableDeclContext::ClassInferredVariableDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassInferredVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassInferredVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassConstInferredDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassConstInferredDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

tree::TerminalNode* PrystParser::ClassConstInferredDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassConstInferredDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassConstInferredDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::ClassConstInferredDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::ClassConstInferredDeclContext::ClassConstInferredDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassConstInferredDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassConstInferredDecl(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::ClassMemberContext* PrystParser::classMember() {
  ClassMemberContext *_localctx = _tracker.createInstance<ClassMemberContext>(_ctx, getState());
  enterRule(_localctx, 28, PrystParser::RuleClassMember);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(323);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::ClassTypedVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(288);
      type(0);
      setState(289);
      match(PrystParser::IDENTIFIER);
      setState(290);
      match(PrystParser::EQUAL);
      setState(291);
      expression();
      setState(292);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::ClassInferredVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(294);
      match(PrystParser::LET);
      setState(295);
      match(PrystParser::IDENTIFIER);
      setState(296);
      match(PrystParser::EQUAL);
      setState(297);
      expression();
      setState(298);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrystParser::ClassConstInferredDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(300);
      match(PrystParser::CONST);
      setState(301);
      match(PrystParser::IDENTIFIER);
      setState(302);
      match(PrystParser::EQUAL);
      setState(303);
      expression();
      setState(304);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PrystParser::ClassConstTypedDeclContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(306);
      match(PrystParser::CONST);
      setState(307);
      type(0);
      setState(308);
      match(PrystParser::IDENTIFIER);
      setState(309);
      match(PrystParser::EQUAL);
      setState(310);
      expression();
      setState(311);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PrystParser::ClassFunctionDeclContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(313);
      match(PrystParser::IDENTIFIER);
      setState(314);
      match(PrystParser::LPAREN);
      setState(316);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2864852312961056768) != 0)) {
        setState(315);
        paramList();
      }
      setState(318);
      match(PrystParser::RPAREN);
      setState(319);
      match(PrystParser::ARROW);
      setState(320);
      type(0);
      setState(321);
      functionBody();
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
  enterRule(_localctx, 30, PrystParser::RuleParamList);
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
    setState(325);
    param();
    setState(330);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(326);
      match(PrystParser::COMMA);
      setState(327);
      param();
      setState(332);
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

tree::TerminalNode* PrystParser::ParamContext::FN() {
  return getToken(PrystParser::FN, 0);
}

tree::TerminalNode* PrystParser::ParamContext::LESS() {
  return getToken(PrystParser::LESS, 0);
}

tree::TerminalNode* PrystParser::ParamContext::GREATER() {
  return getToken(PrystParser::GREATER, 0);
}

tree::TerminalNode* PrystParser::ParamContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::ParamContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ParamTypeListContext* PrystParser::ParamContext::paramTypeList() {
  return getRuleContext<PrystParser::ParamTypeListContext>(0);
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
  enterRule(_localctx, 32, PrystParser::RuleParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(347);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(333);
      type(0);
      setState(334);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(336);
      match(PrystParser::FN);
      setState(337);
      match(PrystParser::LESS);
      setState(338);
      type(0);
      setState(339);
      match(PrystParser::GREATER);
      setState(340);
      match(PrystParser::LPAREN);
      setState(342);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2864852312961056768) != 0)) {
        setState(341);
        paramTypeList();
      }
      setState(344);
      match(PrystParser::RPAREN);
      setState(345);
      match(PrystParser::IDENTIFIER);
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

//----------------- ParamTypeListContext ------------------------------------------------------------------

PrystParser::ParamTypeListContext::ParamTypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PrystParser::TypeContext *> PrystParser::ParamTypeListContext::type() {
  return getRuleContexts<PrystParser::TypeContext>();
}

PrystParser::TypeContext* PrystParser::ParamTypeListContext::type(size_t i) {
  return getRuleContext<PrystParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::ParamTypeListContext::COMMA() {
  return getTokens(PrystParser::COMMA);
}

tree::TerminalNode* PrystParser::ParamTypeListContext::COMMA(size_t i) {
  return getToken(PrystParser::COMMA, i);
}


size_t PrystParser::ParamTypeListContext::getRuleIndex() const {
  return PrystParser::RuleParamTypeList;
}


std::any PrystParser::ParamTypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitParamTypeList(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ParamTypeListContext* PrystParser::paramTypeList() {
  ParamTypeListContext *_localctx = _tracker.createInstance<ParamTypeListContext>(_ctx, getState());
  enterRule(_localctx, 34, PrystParser::RuleParamTypeList);
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
    setState(349);
    type(0);
    setState(354);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(350);
      match(PrystParser::COMMA);
      setState(351);
      type(0);
      setState(356);
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

//----------------- TypeContext ------------------------------------------------------------------

PrystParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PrystParser::TypeContext::getRuleIndex() const {
  return PrystParser::RuleType;
}

void PrystParser::TypeContext::copyFrom(TypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FloatTypeContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::FloatTypeContext::FLOAT() {
  return getToken(PrystParser::FLOAT, 0);
}

PrystParser::FloatTypeContext::FloatTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::FloatTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitFloatType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayTypeContext ------------------------------------------------------------------

PrystParser::TypeContext* PrystParser::ArrayTypeContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ArrayTypeContext::LBRACKET() {
  return getToken(PrystParser::LBRACKET, 0);
}

tree::TerminalNode* PrystParser::ArrayTypeContext::RBRACKET() {
  return getToken(PrystParser::RBRACKET, 0);
}

PrystParser::ArrayTypeContext::ArrayTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StrTypeContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::StrTypeContext::STR() {
  return getToken(PrystParser::STR, 0);
}

PrystParser::StrTypeContext::StrTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::StrTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitStrType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntTypeContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::IntTypeContext::INT() {
  return getToken(PrystParser::INT, 0);
}

PrystParser::IntTypeContext::IntTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::IntTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitIntType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VoidTypeContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::VoidTypeContext::VOID() {
  return getToken(PrystParser::VOID, 0);
}

PrystParser::VoidTypeContext::VoidTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::VoidTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitVoidType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierTypeContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::IdentifierTypeContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

PrystParser::IdentifierTypeContext::IdentifierTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::IdentifierTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitIdentifierType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionTypeContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::FunctionTypeContext::FN() {
  return getToken(PrystParser::FN, 0);
}

tree::TerminalNode* PrystParser::FunctionTypeContext::LESS() {
  return getToken(PrystParser::LESS, 0);
}

PrystParser::TypeContext* PrystParser::FunctionTypeContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::FunctionTypeContext::GREATER() {
  return getToken(PrystParser::GREATER, 0);
}

tree::TerminalNode* PrystParser::FunctionTypeContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::FunctionTypeContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ParamTypeListContext* PrystParser::FunctionTypeContext::paramTypeList() {
  return getRuleContext<PrystParser::ParamTypeListContext>(0);
}

PrystParser::FunctionTypeContext::FunctionTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolTypeContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::BoolTypeContext::BOOL() {
  return getToken(PrystParser::BOOL, 0);
}

PrystParser::BoolTypeContext::BoolTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::BoolTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitBoolType(this);
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
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, PrystParser::RuleType, precedence);

    size_t _la = 0;

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
    setState(374);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::INT: {
        _localctx = _tracker.createInstance<IntTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(358);
        match(PrystParser::INT);
        break;
      }

      case PrystParser::FLOAT: {
        _localctx = _tracker.createInstance<FloatTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(359);
        match(PrystParser::FLOAT);
        break;
      }

      case PrystParser::BOOL: {
        _localctx = _tracker.createInstance<BoolTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(360);
        match(PrystParser::BOOL);
        break;
      }

      case PrystParser::STR: {
        _localctx = _tracker.createInstance<StrTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(361);
        match(PrystParser::STR);
        break;
      }

      case PrystParser::VOID: {
        _localctx = _tracker.createInstance<VoidTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(362);
        match(PrystParser::VOID);
        break;
      }

      case PrystParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<IdentifierTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(363);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::FN: {
        _localctx = _tracker.createInstance<FunctionTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(364);
        match(PrystParser::FN);
        setState(365);
        match(PrystParser::LESS);
        setState(366);
        type(0);
        setState(367);
        match(PrystParser::GREATER);
        setState(368);
        match(PrystParser::LPAREN);
        setState(370);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 2864852312961056768) != 0)) {
          setState(369);
          paramTypeList();
        }
        setState(372);
        match(PrystParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(381);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleType);
        setState(376);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(377);
        match(PrystParser::LBRACKET);
        setState(378);
        match(PrystParser::RBRACKET); 
      }
      setState(383);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
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
//----------------- PrintStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::PrintStatementContext::PRINT() {
  return getToken(PrystParser::PRINT, 0);
}

tree::TerminalNode* PrystParser::PrintStatementContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::PrintStatementContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::PrintStatementContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

std::vector<PrystParser::ExpressionContext *> PrystParser::PrintStatementContext::expression() {
  return getRuleContexts<PrystParser::ExpressionContext>();
}

PrystParser::ExpressionContext* PrystParser::PrintStatementContext::expression(size_t i) {
  return getRuleContext<PrystParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::PrintStatementContext::COMMA() {
  return getTokens(PrystParser::COMMA);
}

tree::TerminalNode* PrystParser::PrintStatementContext::COMMA(size_t i) {
  return getToken(PrystParser::COMMA, i);
}

PrystParser::PrintStatementContext::PrintStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::PrintStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitPrintStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TryStatementContext ------------------------------------------------------------------

PrystParser::TryCatchStatementContext* PrystParser::TryStatementContext::tryCatchStatement() {
  return getRuleContext<PrystParser::TryCatchStatementContext>(0);
}

PrystParser::TryStatementContext::TryStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::TryStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitTryStatement(this);
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

std::vector<PrystParser::StatementContext *> PrystParser::BlockStatementContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::BlockStatementContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
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
  enterRule(_localctx, 38, PrystParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(448);
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
      case PrystParser::FN:
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
        setState(384);
        expression();
        setState(385);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::IF: {
        _localctx = _tracker.createInstance<PrystParser::IfStatementContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(387);
        match(PrystParser::IF);
        setState(388);
        match(PrystParser::LPAREN);
        setState(389);
        expression();
        setState(390);
        match(PrystParser::RPAREN);
        setState(391);
        statement();
        setState(394);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          setState(392);
          match(PrystParser::ELSE);
          setState(393);
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
        setState(396);
        match(PrystParser::WHILE);
        setState(397);
        match(PrystParser::LPAREN);
        setState(398);
        expression();
        setState(399);
        match(PrystParser::RPAREN);
        setState(400);
        statement();
        break;
      }

      case PrystParser::FOR: {
        _localctx = _tracker.createInstance<PrystParser::ForStatementContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(402);
        match(PrystParser::FOR);
        setState(403);
        match(PrystParser::LPAREN);
        setState(409);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          setState(404);
          variableDecl();
          break;
        }

        case 2: {
          setState(405);
          expression();
          setState(406);
          match(PrystParser::SEMICOLON);
          break;
        }

        case 3: {
          setState(408);
          match(PrystParser::SEMICOLON);
          break;
        }

        default:
          break;
        }
        setState(412);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4594240969422946818) != 0)) {
          setState(411);
          expression();
        }
        setState(414);
        match(PrystParser::SEMICOLON);
        setState(416);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4594240969422946818) != 0)) {
          setState(415);
          expression();
        }
        setState(418);
        match(PrystParser::RPAREN);
        setState(419);
        statement();
        break;
      }

      case PrystParser::RETURN: {
        _localctx = _tracker.createInstance<PrystParser::ReturnStatementContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(420);
        match(PrystParser::RETURN);
        setState(422);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4594240969422946818) != 0)) {
          setState(421);
          expression();
        }
        setState(424);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::LBRACE: {
        _localctx = _tracker.createInstance<PrystParser::BlockStatementContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(425);
        match(PrystParser::LBRACE);
        setState(429);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4598746957589004810) != 0)) {
          setState(426);
          statement();
          setState(431);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(432);
        match(PrystParser::RBRACE);
        break;
      }

      case PrystParser::TRY: {
        _localctx = _tracker.createInstance<PrystParser::TryStatementContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(433);
        tryCatchStatement();
        break;
      }

      case PrystParser::PRINT: {
        _localctx = _tracker.createInstance<PrystParser::PrintStatementContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(434);
        match(PrystParser::PRINT);
        setState(435);
        match(PrystParser::LPAREN);
        setState(444);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4594240969422946818) != 0)) {
          setState(436);
          expression();
          setState(441);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrystParser::COMMA) {
            setState(437);
            match(PrystParser::COMMA);
            setState(438);
            expression();
            setState(443);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(446);
        match(PrystParser::RPAREN);
        setState(447);
        match(PrystParser::SEMICOLON);
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

PrystParser::LambdaFunctionContext* PrystParser::ExpressionContext::lambdaFunction() {
  return getRuleContext<PrystParser::LambdaFunctionContext>(0);
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

PrystParser::StringLiteralContext* PrystParser::ExpressionContext::stringLiteral() {
  return getRuleContext<PrystParser::StringLiteralContext>(0);
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
  enterRule(_localctx, 40, PrystParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(457);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(450);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(451);
      lambdaFunction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(452);
      typeCastExpr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(453);
      typeConversionExpr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(454);
      classConversionExpr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(455);
      stringLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(456);
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

//----------------- StringLiteralContext ------------------------------------------------------------------

PrystParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PrystParser::StringLiteralContext::getRuleIndex() const {
  return PrystParser::RuleStringLiteral;
}

void PrystParser::StringLiteralContext::copyFrom(StringLiteralContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SimpleStringContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::SimpleStringContext::STRING() {
  return getToken(PrystParser::STRING, 0);
}

PrystParser::SimpleStringContext::SimpleStringContext(StringLiteralContext *ctx) { copyFrom(ctx); }


std::any PrystParser::SimpleStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitSimpleString(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::StringLiteralContext* PrystParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 42, PrystParser::RuleStringLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<PrystParser::SimpleStringContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(459);
    match(PrystParser::STRING);
   
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

PrystParser::QualifiedIdentifierContext* PrystParser::AssignmentContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
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
  enterRule(_localctx, 44, PrystParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(464);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      setState(461);
      call();
      setState(462);
      match(PrystParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(466);
    qualifiedIdentifier();
    setState(467);
    match(PrystParser::EQUAL);
    setState(468);
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
  enterRule(_localctx, 46, PrystParser::RuleLogicOr);
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
    setState(470);
    logicAnd();
    setState(475);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::OR) {
      setState(471);
      match(PrystParser::OR);
      setState(472);
      logicAnd();
      setState(477);
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
  enterRule(_localctx, 48, PrystParser::RuleLogicAnd);
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
    setState(478);
    equality();
    setState(483);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::AND) {
      setState(479);
      match(PrystParser::AND);
      setState(480);
      equality();
      setState(485);
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
  enterRule(_localctx, 50, PrystParser::RuleEquality);
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
    setState(486);
    comparison();
    setState(491);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::NOT_EQUAL

    || _la == PrystParser::EQUAL_EQUAL) {
      setState(487);
      _la = _input->LA(1);
      if (!(_la == PrystParser::NOT_EQUAL

      || _la == PrystParser::EQUAL_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(488);
      comparison();
      setState(493);
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
  enterRule(_localctx, 52, PrystParser::RuleComparison);
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
    setState(494);
    addition();
    setState(499);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3342336) != 0)) {
      setState(495);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3342336) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(496);
      addition();
      setState(501);
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
  enterRule(_localctx, 54, PrystParser::RuleAddition);
  size_t _la = 0;

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
    setState(502);
    multiplication();
    setState(507);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(503);
        _la = _input->LA(1);
        if (!(_la == PrystParser::MINUS

        || _la == PrystParser::PLUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(504);
        multiplication(); 
      }
      setState(509);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
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
  enterRule(_localctx, 56, PrystParser::RuleMultiplication);
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
    setState(510);
    unary();
    setState(515);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67121152) != 0)) {
      setState(511);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 67121152) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(512);
      unary();
      setState(517);
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
  enterRule(_localctx, 58, PrystParser::RuleUnary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(521);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT: {
        enterOuterAlt(_localctx, 1);
        setState(518);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 50348544) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(519);
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
        setState(520);
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
  enterRule(_localctx, 60, PrystParser::RulePostfix);

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
    setState(523);
    primary();
    setState(529);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(527);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PrystParser::LPAREN:
          case PrystParser::DOT: {
            setState(524);
            suffix();
            break;
          }

          case PrystParser::INCREMENT: {
            setState(525);
            match(PrystParser::INCREMENT);
            break;
          }

          case PrystParser::DECREMENT: {
            setState(526);
            match(PrystParser::DECREMENT);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(531);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
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
  enterRule(_localctx, 62, PrystParser::RuleSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(534);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(532);
        callSuffix();
        break;
      }

      case PrystParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(533);
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
  enterRule(_localctx, 64, PrystParser::RuleCallSuffix);
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
    setState(536);
    match(PrystParser::LPAREN);
    setState(538);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4594240969422946818) != 0)) {
      setState(537);
      arguments();
    }
    setState(540);
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

tree::TerminalNode* PrystParser::MemberSuffixContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::MemberSuffixContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ArgumentsContext* PrystParser::MemberSuffixContext::arguments() {
  return getRuleContext<PrystParser::ArgumentsContext>(0);
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
  enterRule(_localctx, 66, PrystParser::RuleMemberSuffix);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(551);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(542);
      match(PrystParser::DOT);
      setState(543);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(544);
      match(PrystParser::DOT);
      setState(545);
      match(PrystParser::IDENTIFIER);
      setState(546);
      match(PrystParser::LPAREN);
      setState(548);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4594240969422946818) != 0)) {
        setState(547);
        arguments();
      }
      setState(550);
      match(PrystParser::RPAREN);
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

//----------------- CallContext ------------------------------------------------------------------

PrystParser::CallContext::CallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::QualifiedIdentifierContext* PrystParser::CallContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
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
  enterRule(_localctx, 68, PrystParser::RuleCall);

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
    setState(553);
    qualifiedIdentifier();
    setState(558);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(554);
        match(PrystParser::DOT);
        setState(555);
        match(PrystParser::IDENTIFIER); 
      }
      setState(560);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
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

PrystParser::QualifiedIdentifierContext* PrystParser::PrimaryContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
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

tree::TerminalNode* PrystParser::PrimaryContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 70, PrystParser::RulePrimary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(583);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(561);
        match(PrystParser::TRUE);
        break;
      }

      case PrystParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(562);
        match(PrystParser::FALSE);
        break;
      }

      case PrystParser::NULL_: {
        enterOuterAlt(_localctx, 3);
        setState(563);
        match(PrystParser::NULL_);
        break;
      }

      case PrystParser::THIS: {
        enterOuterAlt(_localctx, 4);
        setState(564);
        match(PrystParser::THIS);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(565);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::STRING: {
        enterOuterAlt(_localctx, 6);
        setState(566);
        match(PrystParser::STRING);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 7);
        setState(567);
        qualifiedIdentifier();
        setState(573);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
        case 1: {
          setState(568);
          match(PrystParser::LPAREN);
          setState(570);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4594240969422946818) != 0)) {
            setState(569);
            arguments();
          }
          setState(572);
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
        setState(575);
        match(PrystParser::LPAREN);
        setState(576);
        expression();
        setState(577);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::SUPER: {
        enterOuterAlt(_localctx, 9);
        setState(579);
        match(PrystParser::SUPER);
        setState(580);
        match(PrystParser::DOT);
        setState(581);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::NEW: {
        enterOuterAlt(_localctx, 10);
        setState(582);
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

//----------------- QualifiedIdentifierContext ------------------------------------------------------------------

PrystParser::QualifiedIdentifierContext::QualifiedIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> PrystParser::QualifiedIdentifierContext::IDENTIFIER() {
  return getTokens(PrystParser::IDENTIFIER);
}

tree::TerminalNode* PrystParser::QualifiedIdentifierContext::IDENTIFIER(size_t i) {
  return getToken(PrystParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> PrystParser::QualifiedIdentifierContext::DOUBLE_COLON() {
  return getTokens(PrystParser::DOUBLE_COLON);
}

tree::TerminalNode* PrystParser::QualifiedIdentifierContext::DOUBLE_COLON(size_t i) {
  return getToken(PrystParser::DOUBLE_COLON, i);
}


size_t PrystParser::QualifiedIdentifierContext::getRuleIndex() const {
  return PrystParser::RuleQualifiedIdentifier;
}


std::any PrystParser::QualifiedIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitQualifiedIdentifier(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::QualifiedIdentifierContext* PrystParser::qualifiedIdentifier() {
  QualifiedIdentifierContext *_localctx = _tracker.createInstance<QualifiedIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 72, PrystParser::RuleQualifiedIdentifier);
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
    setState(585);
    match(PrystParser::IDENTIFIER);
    setState(590);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::DOUBLE_COLON) {
      setState(586);
      match(PrystParser::DOUBLE_COLON);
      setState(587);
      match(PrystParser::IDENTIFIER);
      setState(592);
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
  enterRule(_localctx, 74, PrystParser::RuleNewExpression);
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
    setState(593);
    match(PrystParser::NEW);
    setState(594);
    match(PrystParser::IDENTIFIER);
    setState(595);
    match(PrystParser::LPAREN);
    setState(597);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4594240969422946818) != 0)) {
      setState(596);
      arguments();
    }
    setState(599);
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
  enterRule(_localctx, 76, PrystParser::RuleArguments);
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
    setState(601);
    expression();
    setState(606);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(602);
      match(PrystParser::COMMA);
      setState(603);
      expression();
      setState(608);
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
  enterRule(_localctx, 78, PrystParser::RuleTypeCastExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(619);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(609);
        match(PrystParser::LPAREN);
        setState(610);
        type(0);
        setState(611);
        match(PrystParser::RPAREN);
        setState(612);
        expression();
        break;
      }

      case PrystParser::FN:
      case PrystParser::INT:
      case PrystParser::FLOAT:
      case PrystParser::BOOL:
      case PrystParser::STR:
      case PrystParser::VOID:
      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(614);
        type(0);
        setState(615);
        match(PrystParser::LPAREN);
        setState(616);
        expression();
        setState(617);
        match(PrystParser::RPAREN);
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
  enterRule(_localctx, 80, PrystParser::RuleTypeConversionExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(621);
    type(0);
    setState(622);
    match(PrystParser::DOT);
    setState(623);
    match(PrystParser::CONVERT);
    setState(624);
    match(PrystParser::LPAREN);
    setState(625);
    expression();
    setState(626);
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
  enterRule(_localctx, 82, PrystParser::RuleClassConversionExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(628);
    match(PrystParser::IDENTIFIER);
    setState(629);
    match(PrystParser::DOT);
    setState(630);
    match(PrystParser::CONVERT);
    setState(631);
    match(PrystParser::LPAREN);
    setState(632);
    expression();
    setState(633);
    match(PrystParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TryCatchStatementContext ------------------------------------------------------------------

PrystParser::TryCatchStatementContext::TryCatchStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::TRY() {
  return getToken(PrystParser::TRY, 0);
}

std::vector<PrystParser::StatementContext *> PrystParser::TryCatchStatementContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::TryCatchStatementContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::CATCH() {
  return getToken(PrystParser::CATCH, 0);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}


size_t PrystParser::TryCatchStatementContext::getRuleIndex() const {
  return PrystParser::RuleTryCatchStatement;
}


std::any PrystParser::TryCatchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitTryCatchStatement(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::TryCatchStatementContext* PrystParser::tryCatchStatement() {
  TryCatchStatementContext *_localctx = _tracker.createInstance<TryCatchStatementContext>(_ctx, getState());
  enterRule(_localctx, 84, PrystParser::RuleTryCatchStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(635);
    match(PrystParser::TRY);
    setState(636);
    statement();
    setState(642);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      setState(637);
      match(PrystParser::CATCH);
      setState(638);
      match(PrystParser::LPAREN);
      setState(639);
      match(PrystParser::IDENTIFIER);
      setState(640);
      match(PrystParser::RPAREN);
      setState(641);
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

bool PrystParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 18: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool PrystParser::typeSempred(TypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

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
