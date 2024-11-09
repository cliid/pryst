
// Generated from /home/ubuntu/pryst/PrystParser.g4 by ANTLR 4.13.2


#include "PrystParserVisitor.h"

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

::antlr4::internal::OnceFlag prystparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<PrystParserStaticData> prystparserParserStaticData = nullptr;

void prystparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (prystparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(prystparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<PrystParserStaticData>(
    std::vector<std::string>{
      "program", "declaration", "usingDecl", "namespaceDecl", "moduleDecl", 
      "importDecl", "importPath", "functionDecl", "namedFunction", "lambdaFunction", 
      "functionBody", "variableDecl", "classDeclaration", "classBody", "classMember", 
      "paramList", "param", "paramTypeList", "type", "statement", "expression", 
      "stringLiteral", "stringPart", "assignment", "logicOr", "logicAnd", 
      "equality", "comparison", "addition", "multiplication", "unary", "postfix", 
      "suffix", "callSuffix", "memberSuffix", "call", "primary", "qualifiedIdentifier", 
      "newExpression", "arguments", "typeCastExpr", "typeConversionExpr", 
      "classConversionExpr"
    },
    std::vector<std::string>{
      "", "'print'", "'class'", "'extends'", "'else'", "'false'", "'for'", 
      "'if'", "'null'", "'return'", "'super'", "'this'", "'true'", "'while'", 
      "'new'", "'convert'", "'namespace'", "'module'", "'import'", "'using'", 
      "'try'", "'catch'", "'let'", "'fn'", "'const'", "'const!'", "'int'", 
      "'float'", "'bool'", "'str'", "'void'", "'('", "')'", "'{'", "'}'", 
      "'['", "']'", "','", "'.'", "'-'", "'+'", "';'", "'/'", "'*'", "'!'", 
      "'='", "'>'", "'<'", "'!='", "'=='", "'>='", "'<='", "'&&'", "'||'", 
      "'++'", "'--'", "'%'", "'->'", "'::'", "", "", "", "", "", "", "", 
      "'${'"
    },
    std::vector<std::string>{
      "", "PRINT", "CLASS", "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", 
      "RETURN", "SUPER", "THIS", "TRUE", "WHILE", "NEW", "CONVERT", "NAMESPACE", 
      "MODULE", "IMPORT", "USING", "TRY", "CATCH", "LET", "FN", "CONST", 
      "CONST_EXPR", "INT", "FLOAT", "BOOL", "STR", "VOID", "LPAREN", "RPAREN", 
      "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA", "DOT", "MINUS", 
      "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", "EQUAL", "GREATER", 
      "LESS", "NOT_EQUAL", "EQUAL_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", 
      "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "ARROW", "DOUBLE_COLON", 
      "NUMBER", "IDENTIFIER", "STRING_START", "COMMENT", "WS", "STRING_CONTENT", 
      "ESCAPE_SEQ", "INTERP_START", "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,67,650,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	8,1,8,1,8,1,8,1,8,1,8,3,8,195,8,8,1,8,1,8,1,8,1,8,3,8,201,8,8,3,8,203,
  	8,8,1,8,1,8,1,8,3,8,208,8,8,1,8,1,8,1,8,3,8,213,8,8,1,8,1,8,3,8,217,8,
  	8,1,9,1,9,3,9,221,8,9,1,9,1,9,1,9,1,9,3,9,227,8,9,1,9,1,9,5,9,231,8,9,
  	10,9,12,9,234,9,9,1,9,1,9,1,9,3,9,239,8,9,1,9,1,9,1,9,1,9,3,9,245,8,9,
  	1,9,3,9,248,8,9,1,10,1,10,5,10,252,8,10,10,10,12,10,255,9,10,1,10,1,10,
  	1,11,1,11,1,11,1,11,1,11,1,11,3,11,265,8,11,1,11,1,11,1,11,3,11,270,8,
  	11,1,11,1,11,1,12,1,12,1,12,1,12,3,12,278,8,12,1,12,1,12,1,13,1,13,5,
  	13,284,8,13,10,13,12,13,287,9,13,1,13,1,13,1,14,1,14,1,14,1,14,3,14,295,
  	8,14,1,14,1,14,1,14,1,14,1,14,3,14,302,8,14,1,14,1,14,1,14,1,14,1,14,
  	3,14,309,8,14,1,15,1,15,1,15,5,15,314,8,15,10,15,12,15,317,9,15,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,328,8,16,1,16,1,16,1,16,
  	3,16,333,8,16,1,17,1,17,1,17,5,17,338,8,17,10,17,12,17,341,9,17,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,356,
  	8,18,1,18,1,18,1,18,1,18,3,18,362,8,18,1,18,1,18,1,18,1,18,3,18,368,8,
  	18,3,18,370,8,18,1,18,1,18,1,18,5,18,375,8,18,10,18,12,18,378,9,18,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,390,8,19,1,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,405,8,
  	19,1,19,3,19,408,8,19,1,19,1,19,3,19,412,8,19,1,19,1,19,1,19,1,19,3,19,
  	418,8,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,5,19,430,8,
  	19,10,19,12,19,433,9,19,1,19,1,19,5,19,437,8,19,10,19,12,19,440,9,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,449,8,19,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,3,20,458,8,20,1,21,1,21,5,21,462,8,21,10,21,12,21,465,
  	9,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,3,22,475,8,22,1,23,1,23,
  	1,23,3,23,480,8,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,5,24,489,8,24,10,
  	24,12,24,492,9,24,1,25,1,25,1,25,5,25,497,8,25,10,25,12,25,500,9,25,1,
  	26,1,26,1,26,5,26,505,8,26,10,26,12,26,508,9,26,1,27,1,27,1,27,5,27,513,
  	8,27,10,27,12,27,516,9,27,1,28,1,28,1,28,5,28,521,8,28,10,28,12,28,524,
  	9,28,1,29,1,29,1,29,5,29,529,8,29,10,29,12,29,532,9,29,1,30,1,30,1,30,
  	3,30,537,8,30,1,31,1,31,1,31,1,31,5,31,543,8,31,10,31,12,31,546,9,31,
  	1,32,1,32,3,32,550,8,32,1,33,1,33,3,33,554,8,33,1,33,1,33,1,34,1,34,1,
  	34,1,34,1,34,1,34,3,34,564,8,34,1,34,3,34,567,8,34,1,35,1,35,1,35,5,35,
  	572,8,35,10,35,12,35,575,9,35,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,
  	3,36,585,8,36,1,36,3,36,588,8,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,
  	36,3,36,598,8,36,1,37,1,37,1,37,5,37,603,8,37,10,37,12,37,606,9,37,1,
  	38,1,38,1,38,1,38,3,38,612,8,38,1,38,1,38,1,39,1,39,1,39,5,39,619,8,39,
  	10,39,12,39,622,9,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,
  	3,40,634,8,40,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,42,1,42,1,42,1,42,
  	1,42,1,42,1,42,1,42,0,1,36,43,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,
  	76,78,80,82,84,0,5,1,0,48,49,2,0,46,47,50,51,1,0,39,40,2,0,42,43,56,56,
  	3,0,39,39,44,44,54,55,720,0,92,1,0,0,0,2,102,1,0,0,0,4,137,1,0,0,0,6,
  	139,1,0,0,0,8,151,1,0,0,0,10,162,1,0,0,0,12,166,1,0,0,0,14,176,1,0,0,
  	0,16,216,1,0,0,0,18,247,1,0,0,0,20,249,1,0,0,0,22,264,1,0,0,0,24,273,
  	1,0,0,0,26,281,1,0,0,0,28,308,1,0,0,0,30,310,1,0,0,0,32,332,1,0,0,0,34,
  	334,1,0,0,0,36,369,1,0,0,0,38,448,1,0,0,0,40,457,1,0,0,0,42,459,1,0,0,
  	0,44,474,1,0,0,0,46,479,1,0,0,0,48,485,1,0,0,0,50,493,1,0,0,0,52,501,
  	1,0,0,0,54,509,1,0,0,0,56,517,1,0,0,0,58,525,1,0,0,0,60,536,1,0,0,0,62,
  	538,1,0,0,0,64,549,1,0,0,0,66,551,1,0,0,0,68,566,1,0,0,0,70,568,1,0,0,
  	0,72,597,1,0,0,0,74,599,1,0,0,0,76,607,1,0,0,0,78,615,1,0,0,0,80,633,
  	1,0,0,0,82,635,1,0,0,0,84,642,1,0,0,0,86,91,3,6,3,0,87,91,3,8,4,0,88,
  	91,3,10,5,0,89,91,3,2,1,0,90,86,1,0,0,0,90,87,1,0,0,0,90,88,1,0,0,0,90,
  	89,1,0,0,0,91,94,1,0,0,0,92,90,1,0,0,0,92,93,1,0,0,0,93,95,1,0,0,0,94,
  	92,1,0,0,0,95,96,5,0,0,1,96,1,1,0,0,0,97,103,3,14,7,0,98,103,3,22,11,
  	0,99,103,3,24,12,0,100,103,3,4,2,0,101,103,3,38,19,0,102,97,1,0,0,0,102,
  	98,1,0,0,0,102,99,1,0,0,0,102,100,1,0,0,0,102,101,1,0,0,0,103,3,1,0,0,
  	0,104,105,5,19,0,0,105,109,5,16,0,0,106,107,5,19,0,0,107,109,5,17,0,0,
  	108,104,1,0,0,0,108,106,1,0,0,0,109,110,1,0,0,0,110,111,3,74,37,0,111,
  	112,5,41,0,0,112,138,1,0,0,0,113,114,5,19,0,0,114,115,5,16,0,0,115,116,
  	3,74,37,0,116,120,5,33,0,0,117,119,3,2,1,0,118,117,1,0,0,0,119,122,1,
  	0,0,0,120,118,1,0,0,0,120,121,1,0,0,0,121,123,1,0,0,0,122,120,1,0,0,0,
  	123,124,5,34,0,0,124,138,1,0,0,0,125,126,5,19,0,0,126,127,5,17,0,0,127,
  	128,3,74,37,0,128,132,5,33,0,0,129,131,3,2,1,0,130,129,1,0,0,0,131,134,
  	1,0,0,0,132,130,1,0,0,0,132,133,1,0,0,0,133,135,1,0,0,0,134,132,1,0,0,
  	0,135,136,5,34,0,0,136,138,1,0,0,0,137,108,1,0,0,0,137,113,1,0,0,0,137,
  	125,1,0,0,0,138,5,1,0,0,0,139,140,5,16,0,0,140,141,3,74,37,0,141,146,
  	5,33,0,0,142,145,3,2,1,0,143,145,3,8,4,0,144,142,1,0,0,0,144,143,1,0,
  	0,0,145,148,1,0,0,0,146,144,1,0,0,0,146,147,1,0,0,0,147,149,1,0,0,0,148,
  	146,1,0,0,0,149,150,5,34,0,0,150,7,1,0,0,0,151,152,5,17,0,0,152,153,3,
  	74,37,0,153,157,5,33,0,0,154,156,3,2,1,0,155,154,1,0,0,0,156,159,1,0,
  	0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,160,1,0,0,0,159,157,1,0,0,0,160,
  	161,5,34,0,0,161,9,1,0,0,0,162,163,5,18,0,0,163,164,3,12,6,0,164,165,
  	5,41,0,0,165,11,1,0,0,0,166,171,5,60,0,0,167,168,5,58,0,0,168,170,5,60,
  	0,0,169,167,1,0,0,0,170,173,1,0,0,0,171,169,1,0,0,0,171,172,1,0,0,0,172,
  	13,1,0,0,0,173,171,1,0,0,0,174,177,3,16,8,0,175,177,3,18,9,0,176,174,
  	1,0,0,0,176,175,1,0,0,0,177,15,1,0,0,0,178,179,5,23,0,0,179,180,5,47,
  	0,0,180,181,3,36,18,0,181,182,5,46,0,0,182,183,5,60,0,0,183,185,5,31,
  	0,0,184,186,3,30,15,0,185,184,1,0,0,0,185,186,1,0,0,0,186,187,1,0,0,0,
  	187,188,5,32,0,0,188,189,3,20,10,0,189,217,1,0,0,0,190,191,5,23,0,0,191,
  	192,5,60,0,0,192,194,5,31,0,0,193,195,3,30,15,0,194,193,1,0,0,0,194,195,
  	1,0,0,0,195,196,1,0,0,0,196,202,5,32,0,0,197,200,5,57,0,0,198,201,3,36,
  	18,0,199,201,5,30,0,0,200,198,1,0,0,0,200,199,1,0,0,0,201,203,1,0,0,0,
  	202,197,1,0,0,0,202,203,1,0,0,0,203,204,1,0,0,0,204,217,3,20,10,0,205,
  	208,3,36,18,0,206,208,5,30,0,0,207,205,1,0,0,0,207,206,1,0,0,0,208,209,
  	1,0,0,0,209,210,5,60,0,0,210,212,5,31,0,0,211,213,3,30,15,0,212,211,1,
  	0,0,0,212,213,1,0,0,0,213,214,1,0,0,0,214,215,5,32,0,0,215,217,3,20,10,
  	0,216,178,1,0,0,0,216,190,1,0,0,0,216,207,1,0,0,0,217,17,1,0,0,0,218,
  	220,5,31,0,0,219,221,3,30,15,0,220,219,1,0,0,0,220,221,1,0,0,0,221,222,
  	1,0,0,0,222,223,5,32,0,0,223,226,5,57,0,0,224,227,3,36,18,0,225,227,5,
  	30,0,0,226,224,1,0,0,0,226,225,1,0,0,0,226,227,1,0,0,0,227,228,1,0,0,
  	0,228,232,5,33,0,0,229,231,3,2,1,0,230,229,1,0,0,0,231,234,1,0,0,0,232,
  	230,1,0,0,0,232,233,1,0,0,0,233,235,1,0,0,0,234,232,1,0,0,0,235,248,5,
  	34,0,0,236,238,5,31,0,0,237,239,3,30,15,0,238,237,1,0,0,0,238,239,1,0,
  	0,0,239,240,1,0,0,0,240,241,5,32,0,0,241,244,5,57,0,0,242,245,3,36,18,
  	0,243,245,5,30,0,0,244,242,1,0,0,0,244,243,1,0,0,0,244,245,1,0,0,0,245,
  	246,1,0,0,0,246,248,3,40,20,0,247,218,1,0,0,0,247,236,1,0,0,0,248,19,
  	1,0,0,0,249,253,5,33,0,0,250,252,3,38,19,0,251,250,1,0,0,0,252,255,1,
  	0,0,0,253,251,1,0,0,0,253,254,1,0,0,0,254,256,1,0,0,0,255,253,1,0,0,0,
  	256,257,5,34,0,0,257,21,1,0,0,0,258,265,5,22,0,0,259,265,5,24,0,0,260,
  	265,3,36,18,0,261,262,5,24,0,0,262,265,3,36,18,0,263,265,5,25,0,0,264,
  	258,1,0,0,0,264,259,1,0,0,0,264,260,1,0,0,0,264,261,1,0,0,0,264,263,1,
  	0,0,0,265,266,1,0,0,0,266,269,5,60,0,0,267,268,5,45,0,0,268,270,3,40,
  	20,0,269,267,1,0,0,0,269,270,1,0,0,0,270,271,1,0,0,0,271,272,5,41,0,0,
  	272,23,1,0,0,0,273,274,5,2,0,0,274,277,5,60,0,0,275,276,5,3,0,0,276,278,
  	5,60,0,0,277,275,1,0,0,0,277,278,1,0,0,0,278,279,1,0,0,0,279,280,3,26,
  	13,0,280,25,1,0,0,0,281,285,5,33,0,0,282,284,3,28,14,0,283,282,1,0,0,
  	0,284,287,1,0,0,0,285,283,1,0,0,0,285,286,1,0,0,0,286,288,1,0,0,0,287,
  	285,1,0,0,0,288,289,5,34,0,0,289,27,1,0,0,0,290,291,3,36,18,0,291,294,
  	5,60,0,0,292,293,5,45,0,0,293,295,3,40,20,0,294,292,1,0,0,0,294,295,1,
  	0,0,0,295,296,1,0,0,0,296,297,5,41,0,0,297,309,1,0,0,0,298,299,5,60,0,
  	0,299,301,5,31,0,0,300,302,3,30,15,0,301,300,1,0,0,0,301,302,1,0,0,0,
  	302,303,1,0,0,0,303,304,5,32,0,0,304,305,5,57,0,0,305,306,3,36,18,0,306,
  	307,3,20,10,0,307,309,1,0,0,0,308,290,1,0,0,0,308,298,1,0,0,0,309,29,
  	1,0,0,0,310,315,3,32,16,0,311,312,5,37,0,0,312,314,3,32,16,0,313,311,
  	1,0,0,0,314,317,1,0,0,0,315,313,1,0,0,0,315,316,1,0,0,0,316,31,1,0,0,
  	0,317,315,1,0,0,0,318,319,3,36,18,0,319,320,5,60,0,0,320,333,1,0,0,0,
  	321,322,5,23,0,0,322,323,5,47,0,0,323,324,3,36,18,0,324,325,5,46,0,0,
  	325,327,5,31,0,0,326,328,3,34,17,0,327,326,1,0,0,0,327,328,1,0,0,0,328,
  	329,1,0,0,0,329,330,5,32,0,0,330,331,5,60,0,0,331,333,1,0,0,0,332,318,
  	1,0,0,0,332,321,1,0,0,0,333,33,1,0,0,0,334,339,3,36,18,0,335,336,5,37,
  	0,0,336,338,3,36,18,0,337,335,1,0,0,0,338,341,1,0,0,0,339,337,1,0,0,0,
  	339,340,1,0,0,0,340,35,1,0,0,0,341,339,1,0,0,0,342,343,6,18,-1,0,343,
  	370,5,26,0,0,344,370,5,27,0,0,345,370,5,28,0,0,346,370,5,29,0,0,347,370,
  	5,30,0,0,348,370,5,60,0,0,349,350,5,23,0,0,350,351,5,47,0,0,351,352,3,
  	36,18,0,352,353,5,46,0,0,353,355,5,31,0,0,354,356,3,34,17,0,355,354,1,
  	0,0,0,355,356,1,0,0,0,356,357,1,0,0,0,357,358,5,32,0,0,358,370,1,0,0,
  	0,359,361,5,31,0,0,360,362,3,34,17,0,361,360,1,0,0,0,361,362,1,0,0,0,
  	362,363,1,0,0,0,363,364,5,32,0,0,364,367,5,57,0,0,365,368,3,36,18,0,366,
  	368,5,30,0,0,367,365,1,0,0,0,367,366,1,0,0,0,368,370,1,0,0,0,369,342,
  	1,0,0,0,369,344,1,0,0,0,369,345,1,0,0,0,369,346,1,0,0,0,369,347,1,0,0,
  	0,369,348,1,0,0,0,369,349,1,0,0,0,369,359,1,0,0,0,370,376,1,0,0,0,371,
  	372,10,3,0,0,372,373,5,35,0,0,373,375,5,36,0,0,374,371,1,0,0,0,375,378,
  	1,0,0,0,376,374,1,0,0,0,376,377,1,0,0,0,377,37,1,0,0,0,378,376,1,0,0,
  	0,379,380,3,40,20,0,380,381,5,41,0,0,381,449,1,0,0,0,382,383,5,7,0,0,
  	383,384,5,31,0,0,384,385,3,40,20,0,385,386,5,32,0,0,386,389,3,38,19,0,
  	387,388,5,4,0,0,388,390,3,38,19,0,389,387,1,0,0,0,389,390,1,0,0,0,390,
  	449,1,0,0,0,391,392,5,13,0,0,392,393,5,31,0,0,393,394,3,40,20,0,394,395,
  	5,32,0,0,395,396,3,38,19,0,396,449,1,0,0,0,397,398,5,6,0,0,398,404,5,
  	31,0,0,399,405,3,22,11,0,400,401,3,40,20,0,401,402,5,41,0,0,402,405,1,
  	0,0,0,403,405,5,41,0,0,404,399,1,0,0,0,404,400,1,0,0,0,404,403,1,0,0,
  	0,405,407,1,0,0,0,406,408,3,40,20,0,407,406,1,0,0,0,407,408,1,0,0,0,408,
  	409,1,0,0,0,409,411,5,41,0,0,410,412,3,40,20,0,411,410,1,0,0,0,411,412,
  	1,0,0,0,412,413,1,0,0,0,413,414,5,32,0,0,414,449,3,38,19,0,415,417,5,
  	9,0,0,416,418,3,40,20,0,417,416,1,0,0,0,417,418,1,0,0,0,418,419,1,0,0,
  	0,419,449,5,41,0,0,420,421,5,20,0,0,421,431,3,38,19,0,422,423,5,21,0,
  	0,423,424,5,31,0,0,424,425,3,36,18,0,425,426,5,60,0,0,426,427,5,32,0,
  	0,427,428,3,38,19,0,428,430,1,0,0,0,429,422,1,0,0,0,430,433,1,0,0,0,431,
  	429,1,0,0,0,431,432,1,0,0,0,432,449,1,0,0,0,433,431,1,0,0,0,434,438,5,
  	33,0,0,435,437,3,38,19,0,436,435,1,0,0,0,437,440,1,0,0,0,438,436,1,0,
  	0,0,438,439,1,0,0,0,439,441,1,0,0,0,440,438,1,0,0,0,441,449,5,34,0,0,
  	442,443,5,1,0,0,443,444,5,31,0,0,444,445,3,40,20,0,445,446,5,32,0,0,446,
  	447,5,41,0,0,447,449,1,0,0,0,448,379,1,0,0,0,448,382,1,0,0,0,448,391,
  	1,0,0,0,448,397,1,0,0,0,448,415,1,0,0,0,448,420,1,0,0,0,448,434,1,0,0,
  	0,448,442,1,0,0,0,449,39,1,0,0,0,450,458,3,46,23,0,451,458,3,18,9,0,452,
  	458,3,80,40,0,453,458,3,82,41,0,454,458,3,84,42,0,455,458,3,42,21,0,456,
  	458,3,48,24,0,457,450,1,0,0,0,457,451,1,0,0,0,457,452,1,0,0,0,457,453,
  	1,0,0,0,457,454,1,0,0,0,457,455,1,0,0,0,457,456,1,0,0,0,458,41,1,0,0,
  	0,459,463,5,61,0,0,460,462,3,44,22,0,461,460,1,0,0,0,462,465,1,0,0,0,
  	463,461,1,0,0,0,463,464,1,0,0,0,464,466,1,0,0,0,465,463,1,0,0,0,466,467,
  	5,67,0,0,467,43,1,0,0,0,468,475,5,64,0,0,469,475,5,65,0,0,470,471,5,66,
  	0,0,471,472,3,40,20,0,472,473,5,34,0,0,473,475,1,0,0,0,474,468,1,0,0,
  	0,474,469,1,0,0,0,474,470,1,0,0,0,475,45,1,0,0,0,476,477,3,70,35,0,477,
  	478,5,38,0,0,478,480,1,0,0,0,479,476,1,0,0,0,479,480,1,0,0,0,480,481,
  	1,0,0,0,481,482,3,74,37,0,482,483,5,45,0,0,483,484,3,40,20,0,484,47,1,
  	0,0,0,485,490,3,50,25,0,486,487,5,53,0,0,487,489,3,50,25,0,488,486,1,
  	0,0,0,489,492,1,0,0,0,490,488,1,0,0,0,490,491,1,0,0,0,491,49,1,0,0,0,
  	492,490,1,0,0,0,493,498,3,52,26,0,494,495,5,52,0,0,495,497,3,52,26,0,
  	496,494,1,0,0,0,497,500,1,0,0,0,498,496,1,0,0,0,498,499,1,0,0,0,499,51,
  	1,0,0,0,500,498,1,0,0,0,501,506,3,54,27,0,502,503,7,0,0,0,503,505,3,54,
  	27,0,504,502,1,0,0,0,505,508,1,0,0,0,506,504,1,0,0,0,506,507,1,0,0,0,
  	507,53,1,0,0,0,508,506,1,0,0,0,509,514,3,56,28,0,510,511,7,1,0,0,511,
  	513,3,56,28,0,512,510,1,0,0,0,513,516,1,0,0,0,514,512,1,0,0,0,514,515,
  	1,0,0,0,515,55,1,0,0,0,516,514,1,0,0,0,517,522,3,58,29,0,518,519,7,2,
  	0,0,519,521,3,58,29,0,520,518,1,0,0,0,521,524,1,0,0,0,522,520,1,0,0,0,
  	522,523,1,0,0,0,523,57,1,0,0,0,524,522,1,0,0,0,525,530,3,60,30,0,526,
  	527,7,3,0,0,527,529,3,60,30,0,528,526,1,0,0,0,529,532,1,0,0,0,530,528,
  	1,0,0,0,530,531,1,0,0,0,531,59,1,0,0,0,532,530,1,0,0,0,533,534,7,4,0,
  	0,534,537,3,60,30,0,535,537,3,62,31,0,536,533,1,0,0,0,536,535,1,0,0,0,
  	537,61,1,0,0,0,538,544,3,72,36,0,539,543,3,64,32,0,540,543,5,54,0,0,541,
  	543,5,55,0,0,542,539,1,0,0,0,542,540,1,0,0,0,542,541,1,0,0,0,543,546,
  	1,0,0,0,544,542,1,0,0,0,544,545,1,0,0,0,545,63,1,0,0,0,546,544,1,0,0,
  	0,547,550,3,66,33,0,548,550,3,68,34,0,549,547,1,0,0,0,549,548,1,0,0,0,
  	550,65,1,0,0,0,551,553,5,31,0,0,552,554,3,78,39,0,553,552,1,0,0,0,553,
  	554,1,0,0,0,554,555,1,0,0,0,555,556,5,32,0,0,556,67,1,0,0,0,557,558,5,
  	38,0,0,558,567,5,60,0,0,559,560,5,38,0,0,560,561,5,60,0,0,561,563,5,31,
  	0,0,562,564,3,78,39,0,563,562,1,0,0,0,563,564,1,0,0,0,564,565,1,0,0,0,
  	565,567,5,32,0,0,566,557,1,0,0,0,566,559,1,0,0,0,567,69,1,0,0,0,568,573,
  	3,74,37,0,569,570,5,38,0,0,570,572,5,60,0,0,571,569,1,0,0,0,572,575,1,
  	0,0,0,573,571,1,0,0,0,573,574,1,0,0,0,574,71,1,0,0,0,575,573,1,0,0,0,
  	576,598,5,12,0,0,577,598,5,5,0,0,578,598,5,8,0,0,579,598,5,11,0,0,580,
  	598,5,59,0,0,581,587,3,74,37,0,582,584,5,31,0,0,583,585,3,78,39,0,584,
  	583,1,0,0,0,584,585,1,0,0,0,585,586,1,0,0,0,586,588,5,32,0,0,587,582,
  	1,0,0,0,587,588,1,0,0,0,588,598,1,0,0,0,589,590,5,31,0,0,590,591,3,40,
  	20,0,591,592,5,32,0,0,592,598,1,0,0,0,593,594,5,10,0,0,594,595,5,38,0,
  	0,595,598,5,60,0,0,596,598,3,76,38,0,597,576,1,0,0,0,597,577,1,0,0,0,
  	597,578,1,0,0,0,597,579,1,0,0,0,597,580,1,0,0,0,597,581,1,0,0,0,597,589,
  	1,0,0,0,597,593,1,0,0,0,597,596,1,0,0,0,598,73,1,0,0,0,599,604,5,60,0,
  	0,600,601,5,58,0,0,601,603,5,60,0,0,602,600,1,0,0,0,603,606,1,0,0,0,604,
  	602,1,0,0,0,604,605,1,0,0,0,605,75,1,0,0,0,606,604,1,0,0,0,607,608,5,
  	14,0,0,608,609,5,60,0,0,609,611,5,31,0,0,610,612,3,78,39,0,611,610,1,
  	0,0,0,611,612,1,0,0,0,612,613,1,0,0,0,613,614,5,32,0,0,614,77,1,0,0,0,
  	615,620,3,40,20,0,616,617,5,37,0,0,617,619,3,40,20,0,618,616,1,0,0,0,
  	619,622,1,0,0,0,620,618,1,0,0,0,620,621,1,0,0,0,621,79,1,0,0,0,622,620,
  	1,0,0,0,623,624,5,31,0,0,624,625,3,36,18,0,625,626,5,32,0,0,626,627,3,
  	40,20,0,627,634,1,0,0,0,628,629,3,36,18,0,629,630,5,31,0,0,630,631,3,
  	40,20,0,631,632,5,32,0,0,632,634,1,0,0,0,633,623,1,0,0,0,633,628,1,0,
  	0,0,634,81,1,0,0,0,635,636,3,36,18,0,636,637,5,38,0,0,637,638,5,15,0,
  	0,638,639,5,31,0,0,639,640,3,40,20,0,640,641,5,32,0,0,641,83,1,0,0,0,
  	642,643,5,60,0,0,643,644,5,38,0,0,644,645,5,15,0,0,645,646,5,31,0,0,646,
  	647,3,40,20,0,647,648,5,32,0,0,648,85,1,0,0,0,75,90,92,102,108,120,132,
  	137,144,146,157,171,176,185,194,200,202,207,212,216,220,226,232,238,244,
  	247,253,264,269,277,285,294,301,308,315,327,332,339,355,361,367,369,376,
  	389,404,407,411,417,431,438,448,457,463,474,479,490,498,506,514,522,530,
  	536,542,544,549,553,563,566,573,584,587,597,604,611,620,633
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  prystparserParserStaticData = std::move(staticData);
}

}

PrystParser::PrystParser(TokenStream *input) : PrystParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

PrystParser::PrystParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  PrystParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *prystparserParserStaticData->atn, prystparserParserStaticData->decisionToDFA, prystparserParserStaticData->sharedContextCache, options);
}

PrystParser::~PrystParser() {
  delete _interpreter;
}

const atn::ATN& PrystParser::getATN() const {
  return *prystparserParserStaticData->atn;
}

std::string PrystParser::getGrammarFileName() const {
  return "PrystParser.g4";
}

const std::vector<std::string>& PrystParser::getRuleNames() const {
  return prystparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& PrystParser::getVocabulary() const {
  return prystparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PrystParser::getSerializedATN() const {
  return prystparserParserStaticData->serializedATN;
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
      ((1ULL << _la) & 4089286616477040614) != 0)) {
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
        case PrystParser::TRY:
        case PrystParser::LET:
        case PrystParser::FN:
        case PrystParser::CONST:
        case PrystParser::CONST_EXPR:
        case PrystParser::INT:
        case PrystParser::FLOAT:
        case PrystParser::BOOL:
        case PrystParser::STR:
        case PrystParser::VOID:
        case PrystParser::LPAREN:
        case PrystParser::LBRACE:
        case PrystParser::MINUS:
        case PrystParser::BANG:
        case PrystParser::INCREMENT:
        case PrystParser::DECREMENT:
        case PrystParser::NUMBER:
        case PrystParser::IDENTIFIER:
        case PrystParser::STRING_START: {
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
        ((1ULL << _la) & 4089286616476581862) != 0)) {
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
        ((1ULL << _la) & 4089286616476581862) != 0)) {
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
      ((1ULL << _la) & 4089286616476712934) != 0)) {
      setState(144);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
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
        case PrystParser::TRY:
        case PrystParser::LET:
        case PrystParser::FN:
        case PrystParser::CONST:
        case PrystParser::CONST_EXPR:
        case PrystParser::INT:
        case PrystParser::FLOAT:
        case PrystParser::BOOL:
        case PrystParser::STR:
        case PrystParser::VOID:
        case PrystParser::LPAREN:
        case PrystParser::LBRACE:
        case PrystParser::MINUS:
        case PrystParser::BANG:
        case PrystParser::INCREMENT:
        case PrystParser::DECREMENT:
        case PrystParser::NUMBER:
        case PrystParser::IDENTIFIER:
        case PrystParser::STRING_START: {
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
      ((1ULL << _la) & 4089286616476581862) != 0)) {
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(174);
      namedFunction();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(175);
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

tree::TerminalNode* PrystParser::NamedFunctionContext::VOID() {
  return getToken(PrystParser::VOID, 0);
}


size_t PrystParser::NamedFunctionContext::getRuleIndex() const {
  return PrystParser::RuleNamedFunction;
}


std::any PrystParser::NamedFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(216);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
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
        ((1ULL << _la) & 1152921508843094016) != 0)) {
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
        ((1ULL << _la) & 1152921508843094016) != 0)) {
        setState(193);
        paramList();
      }
      setState(196);
      match(PrystParser::RPAREN);
      setState(202);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::ARROW) {
        setState(197);
        match(PrystParser::ARROW);
        setState(200);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          setState(198);
          type(0);
          break;
        }

        case 2: {
          setState(199);
          match(PrystParser::VOID);
          break;
        }

        default:
          break;
        }
      }
      setState(204);
      functionBody();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(207);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(205);
        type(0);
        break;
      }

      case 2: {
        setState(206);
        match(PrystParser::VOID);
        break;
      }

      default:
        break;
      }
      setState(209);
      match(PrystParser::IDENTIFIER);
      setState(210);
      match(PrystParser::LPAREN);
      setState(212);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508843094016) != 0)) {
        setState(211);
        paramList();
      }
      setState(214);
      match(PrystParser::RPAREN);
      setState(215);
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

tree::TerminalNode* PrystParser::LambdaFunctionContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

PrystParser::ParamListContext* PrystParser::LambdaFunctionContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}

PrystParser::TypeContext* PrystParser::LambdaFunctionContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::LambdaFunctionContext::VOID() {
  return getToken(PrystParser::VOID, 0);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(247);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(218);
      match(PrystParser::LPAREN);
      setState(220);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508843094016) != 0)) {
        setState(219);
        paramList();
      }
      setState(222);
      match(PrystParser::RPAREN);
      setState(223);
      match(PrystParser::ARROW);
      setState(226);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(224);
        type(0);
        break;
      }

      case 2: {
        setState(225);
        match(PrystParser::VOID);
        break;
      }

      default:
        break;
      }
      setState(228);
      match(PrystParser::LBRACE);
      setState(232);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286616476581862) != 0)) {
        setState(229);
        declaration();
        setState(234);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(235);
      match(PrystParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(236);
      match(PrystParser::LPAREN);
      setState(238);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508843094016) != 0)) {
        setState(237);
        paramList();
      }
      setState(240);
      match(PrystParser::RPAREN);
      setState(241);
      match(PrystParser::ARROW);
      setState(244);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
      case 1: {
        setState(242);
        type(0);
        break;
      }

      case 2: {
        setState(243);
        match(PrystParser::VOID);
        break;
      }

      default:
        break;
      }
      setState(246);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(249);
    match(PrystParser::LBRACE);
    setState(253);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286616421531618) != 0)) {
      setState(250);
      statement();
      setState(255);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(256);
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

tree::TerminalNode* PrystParser::VariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::VariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::VariableDeclContext::LET() {
  return getToken(PrystParser::LET, 0);
}

tree::TerminalNode* PrystParser::VariableDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

PrystParser::TypeContext* PrystParser::VariableDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::VariableDeclContext::CONST_EXPR() {
  return getToken(PrystParser::CONST_EXPR, 0);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitVariableDecl(this);
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
    enterOuterAlt(_localctx, 1);
    setState(264);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      setState(258);
      match(PrystParser::LET);
      break;
    }

    case 2: {
      setState(259);
      match(PrystParser::CONST);
      break;
    }

    case 3: {
      setState(260);
      type(0);
      break;
    }

    case 4: {
      setState(261);
      match(PrystParser::CONST);
      setState(262);
      type(0);
      break;
    }

    case 5: {
      setState(263);
      match(PrystParser::CONST_EXPR);
      break;
    }

    default:
      break;
    }
    setState(266);
    match(PrystParser::IDENTIFIER);
    setState(269);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EQUAL) {
      setState(267);
      match(PrystParser::EQUAL);
      setState(268);
      expression();
    }
    setState(271);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(273);
    match(PrystParser::CLASS);
    setState(274);
    match(PrystParser::IDENTIFIER);
    setState(277);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EXTENDS) {
      setState(275);
      match(PrystParser::EXTENDS);
      setState(276);
      match(PrystParser::IDENTIFIER);
    }
    setState(279);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(281);
    match(PrystParser::LBRACE);
    setState(285);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1152921508843094016) != 0)) {
      setState(282);
      classMember();
      setState(287);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(288);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassVariableDecl(this);
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
    setState(308);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::ClassVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(290);
      type(0);
      setState(291);
      match(PrystParser::IDENTIFIER);
      setState(294);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(292);
        match(PrystParser::EQUAL);
        setState(293);
        expression();
      }
      setState(296);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::ClassFunctionDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(298);
      match(PrystParser::IDENTIFIER);
      setState(299);
      match(PrystParser::LPAREN);
      setState(301);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508843094016) != 0)) {
        setState(300);
        paramList();
      }
      setState(303);
      match(PrystParser::RPAREN);
      setState(304);
      match(PrystParser::ARROW);
      setState(305);
      type(0);
      setState(306);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(310);
    param();
    setState(315);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(311);
      match(PrystParser::COMMA);
      setState(312);
      param();
      setState(317);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(332);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(318);
      type(0);
      setState(319);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(321);
      match(PrystParser::FN);
      setState(322);
      match(PrystParser::LESS);
      setState(323);
      type(0);
      setState(324);
      match(PrystParser::GREATER);
      setState(325);
      match(PrystParser::LPAREN);
      setState(327);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508843094016) != 0)) {
        setState(326);
        paramTypeList();
      }
      setState(329);
      match(PrystParser::RPAREN);
      setState(330);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(334);
    type(0);
    setState(339);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(335);
      match(PrystParser::COMMA);
      setState(336);
      type(0);
      setState(341);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitFloatType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LambdaTypeContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::LambdaTypeContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::LambdaTypeContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::LambdaTypeContext::ARROW() {
  return getToken(PrystParser::ARROW, 0);
}

PrystParser::TypeContext* PrystParser::LambdaTypeContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::LambdaTypeContext::VOID() {
  return getToken(PrystParser::VOID, 0);
}

PrystParser::ParamTypeListContext* PrystParser::LambdaTypeContext::paramTypeList() {
  return getRuleContext<PrystParser::ParamTypeListContext>(0);
}

PrystParser::LambdaTypeContext::LambdaTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any PrystParser::LambdaTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitLambdaType(this);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(369);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::INT: {
        _localctx = _tracker.createInstance<IntTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(343);
        match(PrystParser::INT);
        break;
      }

      case PrystParser::FLOAT: {
        _localctx = _tracker.createInstance<FloatTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(344);
        match(PrystParser::FLOAT);
        break;
      }

      case PrystParser::BOOL: {
        _localctx = _tracker.createInstance<BoolTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(345);
        match(PrystParser::BOOL);
        break;
      }

      case PrystParser::STR: {
        _localctx = _tracker.createInstance<StrTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(346);
        match(PrystParser::STR);
        break;
      }

      case PrystParser::VOID: {
        _localctx = _tracker.createInstance<VoidTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(347);
        match(PrystParser::VOID);
        break;
      }

      case PrystParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<IdentifierTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(348);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::FN: {
        _localctx = _tracker.createInstance<FunctionTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(349);
        match(PrystParser::FN);
        setState(350);
        match(PrystParser::LESS);
        setState(351);
        type(0);
        setState(352);
        match(PrystParser::GREATER);
        setState(353);
        match(PrystParser::LPAREN);
        setState(355);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1152921508843094016) != 0)) {
          setState(354);
          paramTypeList();
        }
        setState(357);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::LPAREN: {
        _localctx = _tracker.createInstance<LambdaTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(359);
        match(PrystParser::LPAREN);
        setState(361);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1152921508843094016) != 0)) {
          setState(360);
          paramTypeList();
        }
        setState(363);
        match(PrystParser::RPAREN);
        setState(364);
        match(PrystParser::ARROW);
        setState(367);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
        case 1: {
          setState(365);
          type(0);
          break;
        }

        case 2: {
          setState(366);
          match(PrystParser::VOID);
          break;
        }

        default:
          break;
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(376);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleType);
        setState(371);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(372);
        match(PrystParser::LBRACKET);
        setState(373);
        match(PrystParser::RBRACKET); 
      }
      setState(378);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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

PrystParser::ExpressionContext* PrystParser::PrintStatementContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::PrintStatementContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::PrintStatementContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::PrintStatementContext::PrintStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::PrintStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitPrintStatement(this);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TryCatchStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::TryCatchStatementContext::TRY() {
  return getToken(PrystParser::TRY, 0);
}

std::vector<PrystParser::StatementContext *> PrystParser::TryCatchStatementContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::TryCatchStatementContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::TryCatchStatementContext::CATCH() {
  return getTokens(PrystParser::CATCH);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::CATCH(size_t i) {
  return getToken(PrystParser::CATCH, i);
}

std::vector<tree::TerminalNode *> PrystParser::TryCatchStatementContext::LPAREN() {
  return getTokens(PrystParser::LPAREN);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::LPAREN(size_t i) {
  return getToken(PrystParser::LPAREN, i);
}

std::vector<PrystParser::TypeContext *> PrystParser::TryCatchStatementContext::type() {
  return getRuleContexts<PrystParser::TypeContext>();
}

PrystParser::TypeContext* PrystParser::TryCatchStatementContext::type(size_t i) {
  return getRuleContext<PrystParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::TryCatchStatementContext::IDENTIFIER() {
  return getTokens(PrystParser::IDENTIFIER);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::IDENTIFIER(size_t i) {
  return getToken(PrystParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> PrystParser::TryCatchStatementContext::RPAREN() {
  return getTokens(PrystParser::RPAREN);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::RPAREN(size_t i) {
  return getToken(PrystParser::RPAREN, i);
}

PrystParser::TryCatchStatementContext::TryCatchStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::TryCatchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitTryCatchStatement(this);
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
    size_t alt;
    setState(448);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
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
      case PrystParser::LPAREN:
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT:
      case PrystParser::NUMBER:
      case PrystParser::IDENTIFIER:
      case PrystParser::STRING_START: {
        _localctx = _tracker.createInstance<PrystParser::ExprStatementContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(379);
        expression();
        setState(380);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::IF: {
        _localctx = _tracker.createInstance<PrystParser::IfStatementContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(382);
        match(PrystParser::IF);
        setState(383);
        match(PrystParser::LPAREN);
        setState(384);
        expression();
        setState(385);
        match(PrystParser::RPAREN);
        setState(386);
        statement();
        setState(389);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
        case 1: {
          setState(387);
          match(PrystParser::ELSE);
          setState(388);
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
        setState(391);
        match(PrystParser::WHILE);
        setState(392);
        match(PrystParser::LPAREN);
        setState(393);
        expression();
        setState(394);
        match(PrystParser::RPAREN);
        setState(395);
        statement();
        break;
      }

      case PrystParser::FOR: {
        _localctx = _tracker.createInstance<PrystParser::ForStatementContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(397);
        match(PrystParser::FOR);
        setState(398);
        match(PrystParser::LPAREN);
        setState(404);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          setState(399);
          variableDecl();
          break;
        }

        case 2: {
          setState(400);
          expression();
          setState(401);
          match(PrystParser::SEMICOLON);
          break;
        }

        case 3: {
          setState(403);
          match(PrystParser::SEMICOLON);
          break;
        }

        default:
          break;
        }
        setState(407);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4089286607830539552) != 0)) {
          setState(406);
          expression();
        }
        setState(409);
        match(PrystParser::SEMICOLON);
        setState(411);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4089286607830539552) != 0)) {
          setState(410);
          expression();
        }
        setState(413);
        match(PrystParser::RPAREN);
        setState(414);
        statement();
        break;
      }

      case PrystParser::RETURN: {
        _localctx = _tracker.createInstance<PrystParser::ReturnStatementContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(415);
        match(PrystParser::RETURN);
        setState(417);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4089286607830539552) != 0)) {
          setState(416);
          expression();
        }
        setState(419);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::TRY: {
        _localctx = _tracker.createInstance<PrystParser::TryCatchStatementContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(420);
        match(PrystParser::TRY);
        setState(421);
        statement();
        setState(431);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(422);
            match(PrystParser::CATCH);
            setState(423);
            match(PrystParser::LPAREN);
            setState(424);
            type(0);
            setState(425);
            match(PrystParser::IDENTIFIER);
            setState(426);
            match(PrystParser::RPAREN);
            setState(427);
            statement(); 
          }
          setState(433);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
        }
        break;
      }

      case PrystParser::LBRACE: {
        _localctx = _tracker.createInstance<PrystParser::BlockStatementContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(434);
        match(PrystParser::LBRACE);
        setState(438);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4089286616421531618) != 0)) {
          setState(435);
          statement();
          setState(440);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(441);
        match(PrystParser::RBRACE);
        break;
      }

      case PrystParser::PRINT: {
        _localctx = _tracker.createInstance<PrystParser::PrintStatementContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(442);
        match(PrystParser::PRINT);
        setState(443);
        match(PrystParser::LPAREN);
        setState(444);
        expression();
        setState(445);
        match(PrystParser::RPAREN);
        setState(446);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
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

tree::TerminalNode* PrystParser::StringLiteralContext::STRING_START() {
  return getToken(PrystParser::STRING_START, 0);
}

tree::TerminalNode* PrystParser::StringLiteralContext::STRING_END() {
  return getToken(PrystParser::STRING_END, 0);
}

std::vector<PrystParser::StringPartContext *> PrystParser::StringLiteralContext::stringPart() {
  return getRuleContexts<PrystParser::StringPartContext>();
}

PrystParser::StringPartContext* PrystParser::StringLiteralContext::stringPart(size_t i) {
  return getRuleContext<PrystParser::StringPartContext>(i);
}


size_t PrystParser::StringLiteralContext::getRuleIndex() const {
  return PrystParser::RuleStringLiteral;
}


std::any PrystParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::StringLiteralContext* PrystParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 42, PrystParser::RuleStringLiteral);
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
    setState(459);
    match(PrystParser::STRING_START);
    setState(463);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 7) != 0)) {
      setState(460);
      stringPart();
      setState(465);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(466);
    match(PrystParser::STRING_END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringPartContext ------------------------------------------------------------------

PrystParser::StringPartContext::StringPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::StringPartContext::STRING_CONTENT() {
  return getToken(PrystParser::STRING_CONTENT, 0);
}

tree::TerminalNode* PrystParser::StringPartContext::ESCAPE_SEQ() {
  return getToken(PrystParser::ESCAPE_SEQ, 0);
}

tree::TerminalNode* PrystParser::StringPartContext::INTERP_START() {
  return getToken(PrystParser::INTERP_START, 0);
}

PrystParser::ExpressionContext* PrystParser::StringPartContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::StringPartContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}


size_t PrystParser::StringPartContext::getRuleIndex() const {
  return PrystParser::RuleStringPart;
}


std::any PrystParser::StringPartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitStringPart(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::StringPartContext* PrystParser::stringPart() {
  StringPartContext *_localctx = _tracker.createInstance<StringPartContext>(_ctx, getState());
  enterRule(_localctx, 44, PrystParser::RuleStringPart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(474);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::STRING_CONTENT: {
        enterOuterAlt(_localctx, 1);
        setState(468);
        match(PrystParser::STRING_CONTENT);
        break;
      }

      case PrystParser::ESCAPE_SEQ: {
        enterOuterAlt(_localctx, 2);
        setState(469);
        match(PrystParser::ESCAPE_SEQ);
        break;
      }

      case PrystParser::INTERP_START: {
        enterOuterAlt(_localctx, 3);
        setState(470);
        match(PrystParser::INTERP_START);
        setState(471);
        expression();
        setState(472);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::AssignmentContext* PrystParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 46, PrystParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(479);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      setState(476);
      call();
      setState(477);
      match(PrystParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(481);
    qualifiedIdentifier();
    setState(482);
    match(PrystParser::EQUAL);
    setState(483);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitLogicOr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::LogicOrContext* PrystParser::logicOr() {
  LogicOrContext *_localctx = _tracker.createInstance<LogicOrContext>(_ctx, getState());
  enterRule(_localctx, 48, PrystParser::RuleLogicOr);
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
    setState(485);
    logicAnd();
    setState(490);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::OR) {
      setState(486);
      match(PrystParser::OR);
      setState(487);
      logicAnd();
      setState(492);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitLogicAnd(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::LogicAndContext* PrystParser::logicAnd() {
  LogicAndContext *_localctx = _tracker.createInstance<LogicAndContext>(_ctx, getState());
  enterRule(_localctx, 50, PrystParser::RuleLogicAnd);
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
    setState(493);
    equality();
    setState(498);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::AND) {
      setState(494);
      match(PrystParser::AND);
      setState(495);
      equality();
      setState(500);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitEquality(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::EqualityContext* PrystParser::equality() {
  EqualityContext *_localctx = _tracker.createInstance<EqualityContext>(_ctx, getState());
  enterRule(_localctx, 52, PrystParser::RuleEquality);
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
    setState(501);
    comparison();
    setState(506);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::NOT_EQUAL

    || _la == PrystParser::EQUAL_EQUAL) {
      setState(502);
      _la = _input->LA(1);
      if (!(_la == PrystParser::NOT_EQUAL

      || _la == PrystParser::EQUAL_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(503);
      comparison();
      setState(508);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ComparisonContext* PrystParser::comparison() {
  ComparisonContext *_localctx = _tracker.createInstance<ComparisonContext>(_ctx, getState());
  enterRule(_localctx, 54, PrystParser::RuleComparison);
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
    setState(509);
    addition();
    setState(514);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3588805953060864) != 0)) {
      setState(510);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3588805953060864) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(511);
      addition();
      setState(516);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitAddition(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::AdditionContext* PrystParser::addition() {
  AdditionContext *_localctx = _tracker.createInstance<AdditionContext>(_ctx, getState());
  enterRule(_localctx, 56, PrystParser::RuleAddition);
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
    setState(517);
    multiplication();
    setState(522);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(518);
        _la = _input->LA(1);
        if (!(_la == PrystParser::MINUS

        || _la == PrystParser::PLUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(519);
        multiplication(); 
      }
      setState(524);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitMultiplication(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::MultiplicationContext* PrystParser::multiplication() {
  MultiplicationContext *_localctx = _tracker.createInstance<MultiplicationContext>(_ctx, getState());
  enterRule(_localctx, 58, PrystParser::RuleMultiplication);
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
    setState(525);
    unary();
    setState(530);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72070788177461248) != 0)) {
      setState(526);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 72070788177461248) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(527);
      unary();
      setState(532);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitUnary(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::UnaryContext* PrystParser::unary() {
  UnaryContext *_localctx = _tracker.createInstance<UnaryContext>(_ctx, getState());
  enterRule(_localctx, 60, PrystParser::RuleUnary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(536);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT: {
        enterOuterAlt(_localctx, 1);
        setState(533);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 54061337470304256) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(534);
        unary();
        break;
      }

      case PrystParser::FALSE:
      case PrystParser::NULL_:
      case PrystParser::SUPER:
      case PrystParser::THIS:
      case PrystParser::TRUE:
      case PrystParser::NEW:
      case PrystParser::LPAREN:
      case PrystParser::NUMBER:
      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(535);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitPostfix(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::PostfixContext* PrystParser::postfix() {
  PostfixContext *_localctx = _tracker.createInstance<PostfixContext>(_ctx, getState());
  enterRule(_localctx, 62, PrystParser::RulePostfix);

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
    setState(538);
    primary();
    setState(544);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(542);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PrystParser::LPAREN:
          case PrystParser::DOT: {
            setState(539);
            suffix();
            break;
          }

          case PrystParser::INCREMENT: {
            setState(540);
            match(PrystParser::INCREMENT);
            break;
          }

          case PrystParser::DECREMENT: {
            setState(541);
            match(PrystParser::DECREMENT);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(546);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitSuffix(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::SuffixContext* PrystParser::suffix() {
  SuffixContext *_localctx = _tracker.createInstance<SuffixContext>(_ctx, getState());
  enterRule(_localctx, 64, PrystParser::RuleSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(549);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(547);
        callSuffix();
        break;
      }

      case PrystParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(548);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitCallSuffix(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::CallSuffixContext* PrystParser::callSuffix() {
  CallSuffixContext *_localctx = _tracker.createInstance<CallSuffixContext>(_ctx, getState());
  enterRule(_localctx, 66, PrystParser::RuleCallSuffix);
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
    setState(551);
    match(PrystParser::LPAREN);
    setState(553);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286607830539552) != 0)) {
      setState(552);
      arguments();
    }
    setState(555);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitMemberSuffix(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::MemberSuffixContext* PrystParser::memberSuffix() {
  MemberSuffixContext *_localctx = _tracker.createInstance<MemberSuffixContext>(_ctx, getState());
  enterRule(_localctx, 68, PrystParser::RuleMemberSuffix);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(566);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(557);
      match(PrystParser::DOT);
      setState(558);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(559);
      match(PrystParser::DOT);
      setState(560);
      match(PrystParser::IDENTIFIER);
      setState(561);
      match(PrystParser::LPAREN);
      setState(563);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286607830539552) != 0)) {
        setState(562);
        arguments();
      }
      setState(565);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::CallContext* PrystParser::call() {
  CallContext *_localctx = _tracker.createInstance<CallContext>(_ctx, getState());
  enterRule(_localctx, 70, PrystParser::RuleCall);

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
    setState(568);
    qualifiedIdentifier();
    setState(573);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(569);
        match(PrystParser::DOT);
        setState(570);
        match(PrystParser::IDENTIFIER); 
      }
      setState(575);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitPrimary(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::PrimaryContext* PrystParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 72, PrystParser::RulePrimary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(597);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(576);
        match(PrystParser::TRUE);
        break;
      }

      case PrystParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(577);
        match(PrystParser::FALSE);
        break;
      }

      case PrystParser::NULL_: {
        enterOuterAlt(_localctx, 3);
        setState(578);
        match(PrystParser::NULL_);
        break;
      }

      case PrystParser::THIS: {
        enterOuterAlt(_localctx, 4);
        setState(579);
        match(PrystParser::THIS);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(580);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 6);
        setState(581);
        qualifiedIdentifier();
        setState(587);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
        case 1: {
          setState(582);
          match(PrystParser::LPAREN);
          setState(584);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4089286607830539552) != 0)) {
            setState(583);
            arguments();
          }
          setState(586);
          match(PrystParser::RPAREN);
          break;
        }

        default:
          break;
        }
        break;
      }

      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 7);
        setState(589);
        match(PrystParser::LPAREN);
        setState(590);
        expression();
        setState(591);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::SUPER: {
        enterOuterAlt(_localctx, 8);
        setState(593);
        match(PrystParser::SUPER);
        setState(594);
        match(PrystParser::DOT);
        setState(595);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::NEW: {
        enterOuterAlt(_localctx, 9);
        setState(596);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitQualifiedIdentifier(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::QualifiedIdentifierContext* PrystParser::qualifiedIdentifier() {
  QualifiedIdentifierContext *_localctx = _tracker.createInstance<QualifiedIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 74, PrystParser::RuleQualifiedIdentifier);
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
    setState(599);
    match(PrystParser::IDENTIFIER);
    setState(604);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::DOUBLE_COLON) {
      setState(600);
      match(PrystParser::DOUBLE_COLON);
      setState(601);
      match(PrystParser::IDENTIFIER);
      setState(606);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitNewExpression(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::NewExpressionContext* PrystParser::newExpression() {
  NewExpressionContext *_localctx = _tracker.createInstance<NewExpressionContext>(_ctx, getState());
  enterRule(_localctx, 76, PrystParser::RuleNewExpression);
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
    setState(607);
    match(PrystParser::NEW);
    setState(608);
    match(PrystParser::IDENTIFIER);
    setState(609);
    match(PrystParser::LPAREN);
    setState(611);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286607830539552) != 0)) {
      setState(610);
      arguments();
    }
    setState(613);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ArgumentsContext* PrystParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 78, PrystParser::RuleArguments);
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
    setState(615);
    expression();
    setState(620);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(616);
      match(PrystParser::COMMA);
      setState(617);
      expression();
      setState(622);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitTypeCastExpr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::TypeCastExprContext* PrystParser::typeCastExpr() {
  TypeCastExprContext *_localctx = _tracker.createInstance<TypeCastExprContext>(_ctx, getState());
  enterRule(_localctx, 80, PrystParser::RuleTypeCastExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(633);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(623);
      match(PrystParser::LPAREN);
      setState(624);
      type(0);
      setState(625);
      match(PrystParser::RPAREN);
      setState(626);
      expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(628);
      type(0);
      setState(629);
      match(PrystParser::LPAREN);
      setState(630);
      expression();
      setState(631);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitTypeConversionExpr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::TypeConversionExprContext* PrystParser::typeConversionExpr() {
  TypeConversionExprContext *_localctx = _tracker.createInstance<TypeConversionExprContext>(_ctx, getState());
  enterRule(_localctx, 82, PrystParser::RuleTypeConversionExpr);

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
    type(0);
    setState(636);
    match(PrystParser::DOT);
    setState(637);
    match(PrystParser::CONVERT);
    setState(638);
    match(PrystParser::LPAREN);
    setState(639);
    expression();
    setState(640);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassConversionExpr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ClassConversionExprContext* PrystParser::classConversionExpr() {
  ClassConversionExprContext *_localctx = _tracker.createInstance<ClassConversionExprContext>(_ctx, getState());
  enterRule(_localctx, 84, PrystParser::RuleClassConversionExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(642);
    match(PrystParser::IDENTIFIER);
    setState(643);
    match(PrystParser::DOT);
    setState(644);
    match(PrystParser::CONVERT);
    setState(645);
    match(PrystParser::LPAREN);
    setState(646);
    expression();
    setState(647);
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
    case 18: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool PrystParser::typeSempred(TypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void PrystParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  prystparserParserInitialize();
#else
  ::antlr4::internal::call_once(prystparserParserOnceFlag, prystparserParserInitialize);
#endif
}
