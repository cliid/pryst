
// Generated from PrystParser.g4 by ANTLR 4.13.2


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
      "paramList", "param", "paramTypeList", "type", "statement", "tryStmtWrapper", 
      "catchBlock", "expression", "stringLiteralRule", "stringPart", "assignment", 
      "logicOr", "logicAnd", "equality", "comparison", "addition", "multiplication", 
      "unary", "postfix", "suffix", "callSuffix", "memberSuffix", "call", 
      "primary", "qualifiedIdentifier", "newExpression", "arguments", "typeCastExpr", 
      "typeConversionExpr", "classConversionExpr"
    },
    std::vector<std::string>{
      "", "'print'", "'class'", "'extends'", "'else'", "'false'", "'for'", 
      "'if'", "'null'", "'return'", "'super'", "'this'", "'true'", "'while'", 
      "'new'", "'convert'", "'namespace'", "'module'", "'import'", "'using'", 
      "'let'", "'fn'", "'const'", "'const!'", "'try'", "'catch'", "'int'", 
      "'float'", "'bool'", "'str'", "'void'", "'('", "')'", "'{'", "'}'", 
      "'['", "']'", "','", "'.'", "'-'", "'+'", "';'", "'/'", "'*'", "'!'", 
      "'='", "'>'", "'<'", "'!='", "'=='", "'>='", "'<='", "'&&'", "'||'", 
      "'++'", "'--'", "'%'", "'->'", "'::'", "", "", "", "", "", "", "", 
      "'${'"
    },
    std::vector<std::string>{
      "", "PRINT", "CLASS", "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", 
      "RETURN", "SUPER", "THIS", "TRUE", "WHILE", "NEW", "CONVERT", "NAMESPACE", 
      "MODULE", "IMPORT", "USING", "LET", "FN", "CONST", "CONST_EXPR", "TRY", 
      "CATCH", "INT", "FLOAT", "BOOL", "STR", "VOID", "LPAREN", "RPAREN", 
      "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA", "DOT", "MINUS", 
      "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", "EQUAL", "GREATER", 
      "LESS", "NOT_EQUAL", "EQUAL_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", 
      "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "ARROW", "DOUBLE_COLON", 
      "NUMBER", "IDENTIFIER", "STRING_START", "COMMENT", "WS", "STRING_CONTENT", 
      "ESCAPE_SEQ", "INTERP_START", "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,67,707,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,1,0,1,0,1,0,1,0,5,0,95,8,0,10,0,12,0,98,9,0,1,
  	0,1,0,1,1,1,1,1,1,1,1,1,1,3,1,107,8,1,1,2,1,2,1,2,1,2,3,2,113,8,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,123,8,2,10,2,12,2,126,9,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,2,5,2,135,8,2,10,2,12,2,138,9,2,1,2,1,2,3,2,142,8,2,1,3,
  	1,3,1,3,1,3,1,3,5,3,149,8,3,10,3,12,3,152,9,3,1,3,1,3,1,4,1,4,1,4,1,4,
  	5,4,160,8,4,10,4,12,4,163,9,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,5,6,
  	174,8,6,10,6,12,6,177,9,6,1,7,1,7,3,7,181,8,7,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,3,8,190,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,199,8,8,1,8,1,8,1,8,1,
  	8,3,8,205,8,8,3,8,207,8,8,1,8,1,8,1,8,3,8,212,8,8,1,8,1,8,1,8,3,8,217,
  	8,8,1,8,1,8,3,8,221,8,8,1,9,1,9,3,9,225,8,9,1,9,1,9,1,9,1,9,3,9,231,8,
  	9,1,9,1,9,5,9,235,8,9,10,9,12,9,238,9,9,1,9,1,9,1,9,3,9,243,8,9,1,9,1,
  	9,1,9,1,9,3,9,249,8,9,1,9,3,9,252,8,9,1,10,1,10,5,10,256,8,10,10,10,12,
  	10,259,9,10,1,10,1,10,1,11,1,11,1,11,1,11,3,11,267,8,11,1,11,1,11,1,11,
  	1,11,1,11,3,11,274,8,11,1,11,1,11,1,11,1,11,1,11,3,11,281,8,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,3,11,290,8,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,3,11,298,8,11,1,11,1,11,1,11,1,11,1,11,3,11,305,8,11,1,12,1,12,1,12,
  	1,12,3,12,311,8,12,1,12,1,12,1,13,1,13,5,13,317,8,13,10,13,12,13,320,
  	9,13,1,13,1,13,1,14,1,14,1,14,1,14,3,14,328,8,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,3,14,336,8,14,1,14,1,14,1,14,1,14,1,14,3,14,343,8,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,3,14,351,8,14,1,14,1,14,1,14,1,14,1,14,3,14,358,
  	8,14,1,14,1,14,1,14,1,14,1,14,3,14,365,8,14,1,15,1,15,1,15,5,15,370,8,
  	15,10,15,12,15,373,9,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	3,16,384,8,16,1,16,1,16,1,16,3,16,389,8,16,1,17,1,17,1,17,5,17,394,8,
  	17,10,17,12,17,397,9,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	1,18,1,18,1,18,1,18,3,18,412,8,18,1,18,1,18,1,18,1,18,3,18,418,8,18,1,
  	18,1,18,1,18,1,18,3,18,424,8,18,3,18,426,8,18,1,18,1,18,1,18,5,18,431,
  	8,18,10,18,12,18,434,9,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,3,19,446,8,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,3,19,461,8,19,1,19,3,19,464,8,19,1,19,1,19,3,19,468,8,
  	19,1,19,1,19,1,19,1,19,3,19,474,8,19,1,19,1,19,1,19,5,19,479,8,19,10,
  	19,12,19,482,9,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,492,8,
  	19,1,20,1,20,1,20,4,20,497,8,20,11,20,12,20,498,1,21,1,21,1,21,1,21,1,
  	21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,515,8,22,1,23,1,
  	23,5,23,519,8,23,10,23,12,23,522,9,23,1,23,1,23,1,24,1,24,1,24,1,24,1,
  	24,1,24,3,24,532,8,24,1,25,1,25,1,25,3,25,537,8,25,1,25,1,25,1,25,1,25,
  	1,26,1,26,1,26,5,26,546,8,26,10,26,12,26,549,9,26,1,27,1,27,1,27,5,27,
  	554,8,27,10,27,12,27,557,9,27,1,28,1,28,1,28,5,28,562,8,28,10,28,12,28,
  	565,9,28,1,29,1,29,1,29,5,29,570,8,29,10,29,12,29,573,9,29,1,30,1,30,
  	1,30,5,30,578,8,30,10,30,12,30,581,9,30,1,31,1,31,1,31,5,31,586,8,31,
  	10,31,12,31,589,9,31,1,32,1,32,1,32,3,32,594,8,32,1,33,1,33,1,33,1,33,
  	5,33,600,8,33,10,33,12,33,603,9,33,1,34,1,34,3,34,607,8,34,1,35,1,35,
  	3,35,611,8,35,1,35,1,35,1,36,1,36,1,36,1,36,1,36,1,36,3,36,621,8,36,1,
  	36,3,36,624,8,36,1,37,1,37,1,37,5,37,629,8,37,10,37,12,37,632,9,37,1,
  	38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,3,38,642,8,38,1,38,3,38,645,8,38,
  	1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,3,38,655,8,38,1,39,1,39,1,39,
  	5,39,660,8,39,10,39,12,39,663,9,39,1,40,1,40,1,40,1,40,3,40,669,8,40,
  	1,40,1,40,1,41,1,41,1,41,5,41,676,8,41,10,41,12,41,679,9,41,1,42,1,42,
  	1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,3,42,691,8,42,1,43,1,43,1,43,
  	1,43,1,43,1,43,1,43,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,0,1,36,45,
  	0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,
  	50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,0,5,1,0,48,
  	49,2,0,46,47,50,51,1,0,39,40,2,0,42,43,56,56,3,0,39,39,44,44,54,55,786,
  	0,96,1,0,0,0,2,106,1,0,0,0,4,141,1,0,0,0,6,143,1,0,0,0,8,155,1,0,0,0,
  	10,166,1,0,0,0,12,170,1,0,0,0,14,180,1,0,0,0,16,220,1,0,0,0,18,251,1,
  	0,0,0,20,253,1,0,0,0,22,304,1,0,0,0,24,306,1,0,0,0,26,314,1,0,0,0,28,
  	364,1,0,0,0,30,366,1,0,0,0,32,388,1,0,0,0,34,390,1,0,0,0,36,425,1,0,0,
  	0,38,491,1,0,0,0,40,493,1,0,0,0,42,500,1,0,0,0,44,514,1,0,0,0,46,516,
  	1,0,0,0,48,531,1,0,0,0,50,536,1,0,0,0,52,542,1,0,0,0,54,550,1,0,0,0,56,
  	558,1,0,0,0,58,566,1,0,0,0,60,574,1,0,0,0,62,582,1,0,0,0,64,593,1,0,0,
  	0,66,595,1,0,0,0,68,606,1,0,0,0,70,608,1,0,0,0,72,623,1,0,0,0,74,625,
  	1,0,0,0,76,654,1,0,0,0,78,656,1,0,0,0,80,664,1,0,0,0,82,672,1,0,0,0,84,
  	690,1,0,0,0,86,692,1,0,0,0,88,699,1,0,0,0,90,95,3,6,3,0,91,95,3,8,4,0,
  	92,95,3,10,5,0,93,95,3,2,1,0,94,90,1,0,0,0,94,91,1,0,0,0,94,92,1,0,0,
  	0,94,93,1,0,0,0,95,98,1,0,0,0,96,94,1,0,0,0,96,97,1,0,0,0,97,99,1,0,0,
  	0,98,96,1,0,0,0,99,100,5,0,0,1,100,1,1,0,0,0,101,107,3,14,7,0,102,107,
  	3,22,11,0,103,107,3,24,12,0,104,107,3,4,2,0,105,107,3,38,19,0,106,101,
  	1,0,0,0,106,102,1,0,0,0,106,103,1,0,0,0,106,104,1,0,0,0,106,105,1,0,0,
  	0,107,3,1,0,0,0,108,109,5,19,0,0,109,113,5,16,0,0,110,111,5,19,0,0,111,
  	113,5,17,0,0,112,108,1,0,0,0,112,110,1,0,0,0,113,114,1,0,0,0,114,115,
  	3,78,39,0,115,116,5,41,0,0,116,142,1,0,0,0,117,118,5,19,0,0,118,119,5,
  	16,0,0,119,120,3,78,39,0,120,124,5,33,0,0,121,123,3,2,1,0,122,121,1,0,
  	0,0,123,126,1,0,0,0,124,122,1,0,0,0,124,125,1,0,0,0,125,127,1,0,0,0,126,
  	124,1,0,0,0,127,128,5,34,0,0,128,142,1,0,0,0,129,130,5,19,0,0,130,131,
  	5,17,0,0,131,132,3,78,39,0,132,136,5,33,0,0,133,135,3,2,1,0,134,133,1,
  	0,0,0,135,138,1,0,0,0,136,134,1,0,0,0,136,137,1,0,0,0,137,139,1,0,0,0,
  	138,136,1,0,0,0,139,140,5,34,0,0,140,142,1,0,0,0,141,112,1,0,0,0,141,
  	117,1,0,0,0,141,129,1,0,0,0,142,5,1,0,0,0,143,144,5,16,0,0,144,145,3,
  	78,39,0,145,150,5,33,0,0,146,149,3,2,1,0,147,149,3,8,4,0,148,146,1,0,
  	0,0,148,147,1,0,0,0,149,152,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,
  	153,1,0,0,0,152,150,1,0,0,0,153,154,5,34,0,0,154,7,1,0,0,0,155,156,5,
  	17,0,0,156,157,3,78,39,0,157,161,5,33,0,0,158,160,3,2,1,0,159,158,1,0,
  	0,0,160,163,1,0,0,0,161,159,1,0,0,0,161,162,1,0,0,0,162,164,1,0,0,0,163,
  	161,1,0,0,0,164,165,5,34,0,0,165,9,1,0,0,0,166,167,5,18,0,0,167,168,3,
  	12,6,0,168,169,5,41,0,0,169,11,1,0,0,0,170,175,5,60,0,0,171,172,5,58,
  	0,0,172,174,5,60,0,0,173,171,1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,0,
  	175,176,1,0,0,0,176,13,1,0,0,0,177,175,1,0,0,0,178,181,3,16,8,0,179,181,
  	3,18,9,0,180,178,1,0,0,0,180,179,1,0,0,0,181,15,1,0,0,0,182,183,5,21,
  	0,0,183,184,5,47,0,0,184,185,3,36,18,0,185,186,5,46,0,0,186,187,5,60,
  	0,0,187,189,5,31,0,0,188,190,3,30,15,0,189,188,1,0,0,0,189,190,1,0,0,
  	0,190,191,1,0,0,0,191,192,5,32,0,0,192,193,3,20,10,0,193,221,1,0,0,0,
  	194,195,5,21,0,0,195,196,5,60,0,0,196,198,5,31,0,0,197,199,3,30,15,0,
  	198,197,1,0,0,0,198,199,1,0,0,0,199,200,1,0,0,0,200,206,5,32,0,0,201,
  	204,5,57,0,0,202,205,3,36,18,0,203,205,5,30,0,0,204,202,1,0,0,0,204,203,
  	1,0,0,0,205,207,1,0,0,0,206,201,1,0,0,0,206,207,1,0,0,0,207,208,1,0,0,
  	0,208,221,3,20,10,0,209,212,3,36,18,0,210,212,5,30,0,0,211,209,1,0,0,
  	0,211,210,1,0,0,0,212,213,1,0,0,0,213,214,5,60,0,0,214,216,5,31,0,0,215,
  	217,3,30,15,0,216,215,1,0,0,0,216,217,1,0,0,0,217,218,1,0,0,0,218,219,
  	5,32,0,0,219,221,3,20,10,0,220,182,1,0,0,0,220,194,1,0,0,0,220,211,1,
  	0,0,0,221,17,1,0,0,0,222,224,5,31,0,0,223,225,3,30,15,0,224,223,1,0,0,
  	0,224,225,1,0,0,0,225,226,1,0,0,0,226,227,5,32,0,0,227,230,5,57,0,0,228,
  	231,3,36,18,0,229,231,5,30,0,0,230,228,1,0,0,0,230,229,1,0,0,0,230,231,
  	1,0,0,0,231,232,1,0,0,0,232,236,5,33,0,0,233,235,3,2,1,0,234,233,1,0,
  	0,0,235,238,1,0,0,0,236,234,1,0,0,0,236,237,1,0,0,0,237,239,1,0,0,0,238,
  	236,1,0,0,0,239,252,5,34,0,0,240,242,5,31,0,0,241,243,3,30,15,0,242,241,
  	1,0,0,0,242,243,1,0,0,0,243,244,1,0,0,0,244,245,5,32,0,0,245,248,5,57,
  	0,0,246,249,3,36,18,0,247,249,5,30,0,0,248,246,1,0,0,0,248,247,1,0,0,
  	0,248,249,1,0,0,0,249,250,1,0,0,0,250,252,3,44,22,0,251,222,1,0,0,0,251,
  	240,1,0,0,0,252,19,1,0,0,0,253,257,5,33,0,0,254,256,3,38,19,0,255,254,
  	1,0,0,0,256,259,1,0,0,0,257,255,1,0,0,0,257,258,1,0,0,0,258,260,1,0,0,
  	0,259,257,1,0,0,0,260,261,5,34,0,0,261,21,1,0,0,0,262,263,5,20,0,0,263,
  	266,5,60,0,0,264,265,5,45,0,0,265,267,3,44,22,0,266,264,1,0,0,0,266,267,
  	1,0,0,0,267,268,1,0,0,0,268,305,5,41,0,0,269,270,5,22,0,0,270,273,5,60,
  	0,0,271,272,5,45,0,0,272,274,3,44,22,0,273,271,1,0,0,0,273,274,1,0,0,
  	0,274,275,1,0,0,0,275,305,5,41,0,0,276,277,3,36,18,0,277,280,5,60,0,0,
  	278,279,5,45,0,0,279,281,3,44,22,0,280,278,1,0,0,0,280,281,1,0,0,0,281,
  	282,1,0,0,0,282,283,5,41,0,0,283,305,1,0,0,0,284,285,5,22,0,0,285,286,
  	3,36,18,0,286,289,5,60,0,0,287,288,5,45,0,0,288,290,3,44,22,0,289,287,
  	1,0,0,0,289,290,1,0,0,0,290,291,1,0,0,0,291,292,5,41,0,0,292,305,1,0,
  	0,0,293,294,5,23,0,0,294,297,5,60,0,0,295,296,5,45,0,0,296,298,3,44,22,
  	0,297,295,1,0,0,0,297,298,1,0,0,0,298,299,1,0,0,0,299,305,5,41,0,0,300,
  	301,3,36,18,0,301,302,5,60,0,0,302,303,5,41,0,0,303,305,1,0,0,0,304,262,
  	1,0,0,0,304,269,1,0,0,0,304,276,1,0,0,0,304,284,1,0,0,0,304,293,1,0,0,
  	0,304,300,1,0,0,0,305,23,1,0,0,0,306,307,5,2,0,0,307,310,5,60,0,0,308,
  	309,5,3,0,0,309,311,5,60,0,0,310,308,1,0,0,0,310,311,1,0,0,0,311,312,
  	1,0,0,0,312,313,3,26,13,0,313,25,1,0,0,0,314,318,5,33,0,0,315,317,3,28,
  	14,0,316,315,1,0,0,0,317,320,1,0,0,0,318,316,1,0,0,0,318,319,1,0,0,0,
  	319,321,1,0,0,0,320,318,1,0,0,0,321,322,5,34,0,0,322,27,1,0,0,0,323,324,
  	3,36,18,0,324,327,5,60,0,0,325,326,5,45,0,0,326,328,3,44,22,0,327,325,
  	1,0,0,0,327,328,1,0,0,0,328,329,1,0,0,0,329,330,5,41,0,0,330,365,1,0,
  	0,0,331,332,5,20,0,0,332,335,5,60,0,0,333,334,5,45,0,0,334,336,3,44,22,
  	0,335,333,1,0,0,0,335,336,1,0,0,0,336,337,1,0,0,0,337,365,5,41,0,0,338,
  	339,5,22,0,0,339,342,5,60,0,0,340,341,5,45,0,0,341,343,3,44,22,0,342,
  	340,1,0,0,0,342,343,1,0,0,0,343,344,1,0,0,0,344,365,5,41,0,0,345,346,
  	5,22,0,0,346,347,3,36,18,0,347,350,5,60,0,0,348,349,5,45,0,0,349,351,
  	3,44,22,0,350,348,1,0,0,0,350,351,1,0,0,0,351,352,1,0,0,0,352,353,5,41,
  	0,0,353,365,1,0,0,0,354,355,5,60,0,0,355,357,5,31,0,0,356,358,3,30,15,
  	0,357,356,1,0,0,0,357,358,1,0,0,0,358,359,1,0,0,0,359,360,5,32,0,0,360,
  	361,5,57,0,0,361,362,3,36,18,0,362,363,3,20,10,0,363,365,1,0,0,0,364,
  	323,1,0,0,0,364,331,1,0,0,0,364,338,1,0,0,0,364,345,1,0,0,0,364,354,1,
  	0,0,0,365,29,1,0,0,0,366,371,3,32,16,0,367,368,5,37,0,0,368,370,3,32,
  	16,0,369,367,1,0,0,0,370,373,1,0,0,0,371,369,1,0,0,0,371,372,1,0,0,0,
  	372,31,1,0,0,0,373,371,1,0,0,0,374,375,3,36,18,0,375,376,5,60,0,0,376,
  	389,1,0,0,0,377,378,5,21,0,0,378,379,5,47,0,0,379,380,3,36,18,0,380,381,
  	5,46,0,0,381,383,5,31,0,0,382,384,3,34,17,0,383,382,1,0,0,0,383,384,1,
  	0,0,0,384,385,1,0,0,0,385,386,5,32,0,0,386,387,5,60,0,0,387,389,1,0,0,
  	0,388,374,1,0,0,0,388,377,1,0,0,0,389,33,1,0,0,0,390,395,3,36,18,0,391,
  	392,5,37,0,0,392,394,3,36,18,0,393,391,1,0,0,0,394,397,1,0,0,0,395,393,
  	1,0,0,0,395,396,1,0,0,0,396,35,1,0,0,0,397,395,1,0,0,0,398,399,6,18,-1,
  	0,399,426,5,26,0,0,400,426,5,27,0,0,401,426,5,28,0,0,402,426,5,29,0,0,
  	403,426,5,30,0,0,404,426,5,60,0,0,405,406,5,21,0,0,406,407,5,47,0,0,407,
  	408,3,36,18,0,408,409,5,46,0,0,409,411,5,31,0,0,410,412,3,34,17,0,411,
  	410,1,0,0,0,411,412,1,0,0,0,412,413,1,0,0,0,413,414,5,32,0,0,414,426,
  	1,0,0,0,415,417,5,31,0,0,416,418,3,34,17,0,417,416,1,0,0,0,417,418,1,
  	0,0,0,418,419,1,0,0,0,419,420,5,32,0,0,420,423,5,57,0,0,421,424,3,36,
  	18,0,422,424,5,30,0,0,423,421,1,0,0,0,423,422,1,0,0,0,424,426,1,0,0,0,
  	425,398,1,0,0,0,425,400,1,0,0,0,425,401,1,0,0,0,425,402,1,0,0,0,425,403,
  	1,0,0,0,425,404,1,0,0,0,425,405,1,0,0,0,425,415,1,0,0,0,426,432,1,0,0,
  	0,427,428,10,3,0,0,428,429,5,35,0,0,429,431,5,36,0,0,430,427,1,0,0,0,
  	431,434,1,0,0,0,432,430,1,0,0,0,432,433,1,0,0,0,433,37,1,0,0,0,434,432,
  	1,0,0,0,435,436,3,44,22,0,436,437,5,41,0,0,437,492,1,0,0,0,438,439,5,
  	7,0,0,439,440,5,31,0,0,440,441,3,44,22,0,441,442,5,32,0,0,442,445,3,38,
  	19,0,443,444,5,4,0,0,444,446,3,38,19,0,445,443,1,0,0,0,445,446,1,0,0,
  	0,446,492,1,0,0,0,447,448,5,13,0,0,448,449,5,31,0,0,449,450,3,44,22,0,
  	450,451,5,32,0,0,451,452,3,38,19,0,452,492,1,0,0,0,453,454,5,6,0,0,454,
  	460,5,31,0,0,455,461,3,22,11,0,456,457,3,44,22,0,457,458,5,41,0,0,458,
  	461,1,0,0,0,459,461,5,41,0,0,460,455,1,0,0,0,460,456,1,0,0,0,460,459,
  	1,0,0,0,461,463,1,0,0,0,462,464,3,44,22,0,463,462,1,0,0,0,463,464,1,0,
  	0,0,464,465,1,0,0,0,465,467,5,41,0,0,466,468,3,44,22,0,467,466,1,0,0,
  	0,467,468,1,0,0,0,468,469,1,0,0,0,469,470,5,32,0,0,470,492,3,38,19,0,
  	471,473,5,9,0,0,472,474,3,44,22,0,473,472,1,0,0,0,473,474,1,0,0,0,474,
  	475,1,0,0,0,475,492,5,41,0,0,476,480,5,33,0,0,477,479,3,38,19,0,478,477,
  	1,0,0,0,479,482,1,0,0,0,480,478,1,0,0,0,480,481,1,0,0,0,481,483,1,0,0,
  	0,482,480,1,0,0,0,483,492,5,34,0,0,484,485,5,1,0,0,485,486,5,31,0,0,486,
  	487,3,44,22,0,487,488,5,32,0,0,488,489,5,41,0,0,489,492,1,0,0,0,490,492,
  	3,40,20,0,491,435,1,0,0,0,491,438,1,0,0,0,491,447,1,0,0,0,491,453,1,0,
  	0,0,491,471,1,0,0,0,491,476,1,0,0,0,491,484,1,0,0,0,491,490,1,0,0,0,492,
  	39,1,0,0,0,493,494,5,24,0,0,494,496,3,38,19,0,495,497,3,42,21,0,496,495,
  	1,0,0,0,497,498,1,0,0,0,498,496,1,0,0,0,498,499,1,0,0,0,499,41,1,0,0,
  	0,500,501,5,25,0,0,501,502,5,31,0,0,502,503,3,36,18,0,503,504,5,60,0,
  	0,504,505,5,32,0,0,505,506,3,38,19,0,506,43,1,0,0,0,507,515,3,50,25,0,
  	508,515,3,18,9,0,509,515,3,84,42,0,510,515,3,86,43,0,511,515,3,88,44,
  	0,512,515,3,46,23,0,513,515,3,52,26,0,514,507,1,0,0,0,514,508,1,0,0,0,
  	514,509,1,0,0,0,514,510,1,0,0,0,514,511,1,0,0,0,514,512,1,0,0,0,514,513,
  	1,0,0,0,515,45,1,0,0,0,516,520,5,61,0,0,517,519,3,48,24,0,518,517,1,0,
  	0,0,519,522,1,0,0,0,520,518,1,0,0,0,520,521,1,0,0,0,521,523,1,0,0,0,522,
  	520,1,0,0,0,523,524,5,67,0,0,524,47,1,0,0,0,525,532,5,64,0,0,526,532,
  	5,65,0,0,527,528,5,66,0,0,528,529,3,44,22,0,529,530,5,34,0,0,530,532,
  	1,0,0,0,531,525,1,0,0,0,531,526,1,0,0,0,531,527,1,0,0,0,532,49,1,0,0,
  	0,533,534,3,74,37,0,534,535,5,38,0,0,535,537,1,0,0,0,536,533,1,0,0,0,
  	536,537,1,0,0,0,537,538,1,0,0,0,538,539,3,78,39,0,539,540,5,45,0,0,540,
  	541,3,44,22,0,541,51,1,0,0,0,542,547,3,54,27,0,543,544,5,53,0,0,544,546,
  	3,54,27,0,545,543,1,0,0,0,546,549,1,0,0,0,547,545,1,0,0,0,547,548,1,0,
  	0,0,548,53,1,0,0,0,549,547,1,0,0,0,550,555,3,56,28,0,551,552,5,52,0,0,
  	552,554,3,56,28,0,553,551,1,0,0,0,554,557,1,0,0,0,555,553,1,0,0,0,555,
  	556,1,0,0,0,556,55,1,0,0,0,557,555,1,0,0,0,558,563,3,58,29,0,559,560,
  	7,0,0,0,560,562,3,58,29,0,561,559,1,0,0,0,562,565,1,0,0,0,563,561,1,0,
  	0,0,563,564,1,0,0,0,564,57,1,0,0,0,565,563,1,0,0,0,566,571,3,60,30,0,
  	567,568,7,1,0,0,568,570,3,60,30,0,569,567,1,0,0,0,570,573,1,0,0,0,571,
  	569,1,0,0,0,571,572,1,0,0,0,572,59,1,0,0,0,573,571,1,0,0,0,574,579,3,
  	62,31,0,575,576,7,2,0,0,576,578,3,62,31,0,577,575,1,0,0,0,578,581,1,0,
  	0,0,579,577,1,0,0,0,579,580,1,0,0,0,580,61,1,0,0,0,581,579,1,0,0,0,582,
  	587,3,64,32,0,583,584,7,3,0,0,584,586,3,64,32,0,585,583,1,0,0,0,586,589,
  	1,0,0,0,587,585,1,0,0,0,587,588,1,0,0,0,588,63,1,0,0,0,589,587,1,0,0,
  	0,590,591,7,4,0,0,591,594,3,64,32,0,592,594,3,66,33,0,593,590,1,0,0,0,
  	593,592,1,0,0,0,594,65,1,0,0,0,595,601,3,76,38,0,596,600,3,68,34,0,597,
  	600,5,54,0,0,598,600,5,55,0,0,599,596,1,0,0,0,599,597,1,0,0,0,599,598,
  	1,0,0,0,600,603,1,0,0,0,601,599,1,0,0,0,601,602,1,0,0,0,602,67,1,0,0,
  	0,603,601,1,0,0,0,604,607,3,70,35,0,605,607,3,72,36,0,606,604,1,0,0,0,
  	606,605,1,0,0,0,607,69,1,0,0,0,608,610,5,31,0,0,609,611,3,82,41,0,610,
  	609,1,0,0,0,610,611,1,0,0,0,611,612,1,0,0,0,612,613,5,32,0,0,613,71,1,
  	0,0,0,614,615,5,38,0,0,615,624,5,60,0,0,616,617,5,38,0,0,617,618,5,60,
  	0,0,618,620,5,31,0,0,619,621,3,82,41,0,620,619,1,0,0,0,620,621,1,0,0,
  	0,621,622,1,0,0,0,622,624,5,32,0,0,623,614,1,0,0,0,623,616,1,0,0,0,624,
  	73,1,0,0,0,625,630,3,78,39,0,626,627,5,38,0,0,627,629,5,60,0,0,628,626,
  	1,0,0,0,629,632,1,0,0,0,630,628,1,0,0,0,630,631,1,0,0,0,631,75,1,0,0,
  	0,632,630,1,0,0,0,633,655,5,12,0,0,634,655,5,5,0,0,635,655,5,8,0,0,636,
  	655,5,11,0,0,637,655,5,59,0,0,638,644,3,78,39,0,639,641,5,31,0,0,640,
  	642,3,82,41,0,641,640,1,0,0,0,641,642,1,0,0,0,642,643,1,0,0,0,643,645,
  	5,32,0,0,644,639,1,0,0,0,644,645,1,0,0,0,645,655,1,0,0,0,646,647,5,31,
  	0,0,647,648,3,44,22,0,648,649,5,32,0,0,649,655,1,0,0,0,650,651,5,10,0,
  	0,651,652,5,38,0,0,652,655,5,60,0,0,653,655,3,80,40,0,654,633,1,0,0,0,
  	654,634,1,0,0,0,654,635,1,0,0,0,654,636,1,0,0,0,654,637,1,0,0,0,654,638,
  	1,0,0,0,654,646,1,0,0,0,654,650,1,0,0,0,654,653,1,0,0,0,655,77,1,0,0,
  	0,656,661,5,60,0,0,657,658,5,58,0,0,658,660,5,60,0,0,659,657,1,0,0,0,
  	660,663,1,0,0,0,661,659,1,0,0,0,661,662,1,0,0,0,662,79,1,0,0,0,663,661,
  	1,0,0,0,664,665,5,14,0,0,665,666,5,60,0,0,666,668,5,31,0,0,667,669,3,
  	82,41,0,668,667,1,0,0,0,668,669,1,0,0,0,669,670,1,0,0,0,670,671,5,32,
  	0,0,671,81,1,0,0,0,672,677,3,44,22,0,673,674,5,37,0,0,674,676,3,44,22,
  	0,675,673,1,0,0,0,676,679,1,0,0,0,677,675,1,0,0,0,677,678,1,0,0,0,678,
  	83,1,0,0,0,679,677,1,0,0,0,680,681,5,31,0,0,681,682,3,36,18,0,682,683,
  	5,32,0,0,683,684,3,44,22,0,684,691,1,0,0,0,685,686,3,36,18,0,686,687,
  	5,31,0,0,687,688,3,44,22,0,688,689,5,32,0,0,689,691,1,0,0,0,690,680,1,
  	0,0,0,690,685,1,0,0,0,691,85,1,0,0,0,692,693,3,36,18,0,693,694,5,38,0,
  	0,694,695,5,15,0,0,695,696,5,31,0,0,696,697,3,44,22,0,697,698,5,32,0,
  	0,698,87,1,0,0,0,699,700,5,60,0,0,700,701,5,38,0,0,701,702,5,15,0,0,702,
  	703,5,31,0,0,703,704,3,44,22,0,704,705,5,32,0,0,705,89,1,0,0,0,82,94,
  	96,106,112,124,136,141,148,150,161,175,180,189,198,204,206,211,216,220,
  	224,230,236,242,248,251,257,266,273,280,289,297,304,310,318,327,335,342,
  	350,357,364,371,383,388,395,411,417,423,425,432,445,460,463,467,473,480,
  	491,498,514,520,531,536,547,555,563,571,579,587,593,599,601,606,610,620,
  	623,630,641,644,654,661,668,677,690
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
    setState(96);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286616445583334) != 0)) {
      setState(94);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PrystParser::NAMESPACE: {
          setState(90);
          namespaceDecl();
          break;
        }

        case PrystParser::MODULE: {
          setState(91);
          moduleDecl();
          break;
        }

        case PrystParser::IMPORT: {
          setState(92);
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
        case PrystParser::LPAREN:
        case PrystParser::LBRACE:
        case PrystParser::MINUS:
        case PrystParser::BANG:
        case PrystParser::INCREMENT:
        case PrystParser::DECREMENT:
        case PrystParser::NUMBER:
        case PrystParser::IDENTIFIER:
        case PrystParser::STRING_START: {
          setState(93);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(98);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(99);
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
    setState(106);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(101);
      functionDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(102);
      variableDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(103);
      classDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(104);
      usingDecl();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(105);
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
    setState(141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::GlobalUsingDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(112);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(108);
        match(PrystParser::USING);
        setState(109);
        match(PrystParser::NAMESPACE);
        break;
      }

      case 2: {
        setState(110);
        match(PrystParser::USING);
        setState(111);
        match(PrystParser::MODULE);
        break;
      }

      default:
        break;
      }
      setState(114);
      qualifiedIdentifier();
      setState(115);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::BlockScopedNamespaceDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(117);
      match(PrystParser::USING);
      setState(118);
      match(PrystParser::NAMESPACE);
      setState(119);
      qualifiedIdentifier();
      setState(120);
      match(PrystParser::LBRACE);
      setState(124);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286616445124582) != 0)) {
        setState(121);
        declaration();
        setState(126);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(127);
      match(PrystParser::RBRACE);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrystParser::BlockScopedModuleDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(129);
      match(PrystParser::USING);
      setState(130);
      match(PrystParser::MODULE);
      setState(131);
      qualifiedIdentifier();
      setState(132);
      match(PrystParser::LBRACE);
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286616445124582) != 0)) {
        setState(133);
        declaration();
        setState(138);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(139);
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
    setState(143);
    match(PrystParser::NAMESPACE);
    setState(144);
    qualifiedIdentifier();
    setState(145);
    match(PrystParser::LBRACE);
    setState(150);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286616445255654) != 0)) {
      setState(148);
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
        case PrystParser::LPAREN:
        case PrystParser::LBRACE:
        case PrystParser::MINUS:
        case PrystParser::BANG:
        case PrystParser::INCREMENT:
        case PrystParser::DECREMENT:
        case PrystParser::NUMBER:
        case PrystParser::IDENTIFIER:
        case PrystParser::STRING_START: {
          setState(146);
          declaration();
          break;
        }

        case PrystParser::MODULE: {
          setState(147);
          moduleDecl();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(152);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(153);
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
    setState(155);
    match(PrystParser::MODULE);
    setState(156);
    qualifiedIdentifier();
    setState(157);
    match(PrystParser::LBRACE);
    setState(161);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286616445124582) != 0)) {
      setState(158);
      declaration();
      setState(163);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(164);
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
    setState(166);
    match(PrystParser::IMPORT);
    setState(167);
    importPath();
    setState(168);
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
    setState(170);
    match(PrystParser::IDENTIFIER);
    setState(175);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::DOUBLE_COLON) {
      setState(171);
      match(PrystParser::DOUBLE_COLON);
      setState(172);
      match(PrystParser::IDENTIFIER);
      setState(177);
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
    setState(180);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(178);
      namedFunction();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(179);
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
    setState(220);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(182);
      match(PrystParser::FN);
      setState(183);
      match(PrystParser::LESS);
      setState(184);
      type(0);
      setState(185);
      match(PrystParser::GREATER);
      setState(186);
      match(PrystParser::IDENTIFIER);
      setState(187);
      match(PrystParser::LPAREN);
      setState(189);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(188);
        paramList();
      }
      setState(191);
      match(PrystParser::RPAREN);
      setState(192);
      functionBody();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(194);
      match(PrystParser::FN);
      setState(195);
      match(PrystParser::IDENTIFIER);
      setState(196);
      match(PrystParser::LPAREN);
      setState(198);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(197);
        paramList();
      }
      setState(200);
      match(PrystParser::RPAREN);
      setState(206);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::ARROW) {
        setState(201);
        match(PrystParser::ARROW);
        setState(204);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          setState(202);
          type(0);
          break;
        }

        case 2: {
          setState(203);
          match(PrystParser::VOID);
          break;
        }

        default:
          break;
        }
      }
      setState(208);
      functionBody();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(211);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(209);
        type(0);
        break;
      }

      case 2: {
        setState(210);
        match(PrystParser::VOID);
        break;
      }

      default:
        break;
      }
      setState(213);
      match(PrystParser::IDENTIFIER);
      setState(214);
      match(PrystParser::LPAREN);
      setState(216);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(215);
        paramList();
      }
      setState(218);
      match(PrystParser::RPAREN);
      setState(219);
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
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(222);
      match(PrystParser::LPAREN);
      setState(224);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(223);
        paramList();
      }
      setState(226);
      match(PrystParser::RPAREN);
      setState(227);
      match(PrystParser::ARROW);
      setState(230);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(228);
        type(0);
        break;
      }

      case 2: {
        setState(229);
        match(PrystParser::VOID);
        break;
      }

      default:
        break;
      }
      setState(232);
      match(PrystParser::LBRACE);
      setState(236);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286616445124582) != 0)) {
        setState(233);
        declaration();
        setState(238);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(239);
      match(PrystParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(240);
      match(PrystParser::LPAREN);
      setState(242);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(241);
        paramList();
      }
      setState(244);
      match(PrystParser::RPAREN);
      setState(245);
      match(PrystParser::ARROW);
      setState(248);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
      case 1: {
        setState(246);
        type(0);
        break;
      }

      case 2: {
        setState(247);
        match(PrystParser::VOID);
        break;
      }

      default:
        break;
      }
      setState(250);
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
    setState(253);
    match(PrystParser::LBRACE);
    setState(257);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286616430968802) != 0)) {
      setState(254);
      statement();
      setState(259);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(260);
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

//----------------- TypedConstVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::TypedConstVariableDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

PrystParser::TypeContext* PrystParser::TypedConstVariableDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::TypedConstVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::TypedConstVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::TypedConstVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::TypedConstVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::TypedConstVariableDeclContext::TypedConstVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::TypedConstVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitTypedConstVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TypedVariableDeclContext ------------------------------------------------------------------

PrystParser::TypeContext* PrystParser::TypedVariableDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::TypedVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::TypedVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::TypedVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::TypedVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::TypedVariableDeclContext::TypedVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::TypedVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitTypedVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InferredVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::InferredVariableDeclContext::LET() {
  return getToken(PrystParser::LET, 0);
}

tree::TerminalNode* PrystParser::InferredVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::InferredVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::InferredVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::InferredVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::InferredVariableDeclContext::InferredVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::InferredVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitInferredVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InferredConstVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::InferredConstVariableDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

tree::TerminalNode* PrystParser::InferredConstVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::InferredConstVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::InferredConstVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::InferredConstVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::InferredConstVariableDeclContext::InferredConstVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::InferredConstVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitInferredConstVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstExprVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ConstExprVariableDeclContext::CONST_EXPR() {
  return getToken(PrystParser::CONST_EXPR, 0);
}

tree::TerminalNode* PrystParser::ConstExprVariableDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ConstExprVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::ConstExprVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ConstExprVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::ConstExprVariableDeclContext::ConstExprVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ConstExprVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitConstExprVariableDecl(this);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(304);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::InferredVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(262);
      match(PrystParser::LET);
      setState(263);
      match(PrystParser::IDENTIFIER);
      setState(266);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(264);
        match(PrystParser::EQUAL);
        setState(265);
        expression();
      }
      setState(268);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::InferredConstVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(269);
      match(PrystParser::CONST);
      setState(270);
      match(PrystParser::IDENTIFIER);
      setState(273);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(271);
        match(PrystParser::EQUAL);
        setState(272);
        expression();
      }
      setState(275);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrystParser::TypedVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(276);
      type(0);
      setState(277);
      match(PrystParser::IDENTIFIER);
      setState(280);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(278);
        match(PrystParser::EQUAL);
        setState(279);
        expression();
      }
      setState(282);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PrystParser::TypedConstVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(284);
      match(PrystParser::CONST);
      setState(285);
      type(0);
      setState(286);
      match(PrystParser::IDENTIFIER);
      setState(289);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(287);
        match(PrystParser::EQUAL);
        setState(288);
        expression();
      }
      setState(291);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PrystParser::ConstExprVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(293);
      match(PrystParser::CONST_EXPR);
      setState(294);
      match(PrystParser::IDENTIFIER);
      setState(297);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(295);
        match(PrystParser::EQUAL);
        setState(296);
        expression();
      }
      setState(299);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PrystParser::UninitializedVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(300);
      type(0);
      setState(301);
      match(PrystParser::IDENTIFIER);
      setState(302);
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
    setState(306);
    match(PrystParser::CLASS);
    setState(307);
    match(PrystParser::IDENTIFIER);
    setState(310);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EXTENDS) {
      setState(308);
      match(PrystParser::EXTENDS);
      setState(309);
      match(PrystParser::IDENTIFIER);
    }
    setState(312);
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
    setState(314);
    match(PrystParser::LBRACE);
    setState(318);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1152921508842045440) != 0)) {
      setState(315);
      classMember();
      setState(320);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(321);
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

//----------------- ClassMemberConstTypedDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassMemberConstTypedDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

PrystParser::TypeContext* PrystParser::ClassMemberConstTypedDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ClassMemberConstTypedDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassMemberConstTypedDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::ClassMemberConstTypedDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassMemberConstTypedDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::ClassMemberConstTypedDeclContext::ClassMemberConstTypedDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassMemberConstTypedDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassMemberConstTypedDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassMemberConstInferredDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassMemberConstInferredDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

tree::TerminalNode* PrystParser::ClassMemberConstInferredDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassMemberConstInferredDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::ClassMemberConstInferredDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassMemberConstInferredDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::ClassMemberConstInferredDeclContext::ClassMemberConstInferredDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassMemberConstInferredDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassMemberConstInferredDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassMemberInferredDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassMemberInferredDeclContext::LET() {
  return getToken(PrystParser::LET, 0);
}

tree::TerminalNode* PrystParser::ClassMemberInferredDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassMemberInferredDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::ClassMemberInferredDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassMemberInferredDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::ClassMemberInferredDeclContext::ClassMemberInferredDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassMemberInferredDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassMemberInferredDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassMemberFunctionDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassMemberFunctionDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassMemberFunctionDeclContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::ClassMemberFunctionDeclContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::ClassMemberFunctionDeclContext::ARROW() {
  return getToken(PrystParser::ARROW, 0);
}

PrystParser::TypeContext* PrystParser::ClassMemberFunctionDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

PrystParser::FunctionBodyContext* PrystParser::ClassMemberFunctionDeclContext::functionBody() {
  return getRuleContext<PrystParser::FunctionBodyContext>(0);
}

PrystParser::ParamListContext* PrystParser::ClassMemberFunctionDeclContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}

PrystParser::ClassMemberFunctionDeclContext::ClassMemberFunctionDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassMemberFunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassMemberFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassMemberDeclContext ------------------------------------------------------------------

PrystParser::TypeContext* PrystParser::ClassMemberDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ClassMemberDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassMemberDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::ClassMemberDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassMemberDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::ClassMemberDeclContext::ClassMemberDeclContext(ClassMemberContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassMemberDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassMemberDecl(this);
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
    setState(364);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::ClassMemberDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(323);
      type(0);
      setState(324);
      match(PrystParser::IDENTIFIER);
      setState(327);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(325);
        match(PrystParser::EQUAL);
        setState(326);
        expression();
      }
      setState(329);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::ClassMemberInferredDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(331);
      match(PrystParser::LET);
      setState(332);
      match(PrystParser::IDENTIFIER);
      setState(335);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(333);
        match(PrystParser::EQUAL);
        setState(334);
        expression();
      }
      setState(337);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrystParser::ClassMemberConstInferredDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(338);
      match(PrystParser::CONST);
      setState(339);
      match(PrystParser::IDENTIFIER);
      setState(342);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(340);
        match(PrystParser::EQUAL);
        setState(341);
        expression();
      }
      setState(344);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PrystParser::ClassMemberConstTypedDeclContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(345);
      match(PrystParser::CONST);
      setState(346);
      type(0);
      setState(347);
      match(PrystParser::IDENTIFIER);
      setState(350);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(348);
        match(PrystParser::EQUAL);
        setState(349);
        expression();
      }
      setState(352);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PrystParser::ClassMemberFunctionDeclContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(354);
      match(PrystParser::IDENTIFIER);
      setState(355);
      match(PrystParser::LPAREN);
      setState(357);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(356);
        paramList();
      }
      setState(359);
      match(PrystParser::RPAREN);
      setState(360);
      match(PrystParser::ARROW);
      setState(361);
      type(0);
      setState(362);
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
    setState(366);
    param();
    setState(371);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(367);
      match(PrystParser::COMMA);
      setState(368);
      param();
      setState(373);
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
    setState(388);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(374);
      type(0);
      setState(375);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(377);
      match(PrystParser::FN);
      setState(378);
      match(PrystParser::LESS);
      setState(379);
      type(0);
      setState(380);
      match(PrystParser::GREATER);
      setState(381);
      match(PrystParser::LPAREN);
      setState(383);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(382);
        paramTypeList();
      }
      setState(385);
      match(PrystParser::RPAREN);
      setState(386);
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
    setState(390);
    type(0);
    setState(395);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(391);
      match(PrystParser::COMMA);
      setState(392);
      type(0);
      setState(397);
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
    setState(425);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::INT: {
        _localctx = _tracker.createInstance<IntTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(399);
        match(PrystParser::INT);
        break;
      }

      case PrystParser::FLOAT: {
        _localctx = _tracker.createInstance<FloatTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(400);
        match(PrystParser::FLOAT);
        break;
      }

      case PrystParser::BOOL: {
        _localctx = _tracker.createInstance<BoolTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(401);
        match(PrystParser::BOOL);
        break;
      }

      case PrystParser::STR: {
        _localctx = _tracker.createInstance<StrTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(402);
        match(PrystParser::STR);
        break;
      }

      case PrystParser::VOID: {
        _localctx = _tracker.createInstance<VoidTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(403);
        match(PrystParser::VOID);
        break;
      }

      case PrystParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<IdentifierTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(404);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::FN: {
        _localctx = _tracker.createInstance<FunctionTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(405);
        match(PrystParser::FN);
        setState(406);
        match(PrystParser::LESS);
        setState(407);
        type(0);
        setState(408);
        match(PrystParser::GREATER);
        setState(409);
        match(PrystParser::LPAREN);
        setState(411);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1152921508836802560) != 0)) {
          setState(410);
          paramTypeList();
        }
        setState(413);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::LPAREN: {
        _localctx = _tracker.createInstance<LambdaTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(415);
        match(PrystParser::LPAREN);
        setState(417);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1152921508836802560) != 0)) {
          setState(416);
          paramTypeList();
        }
        setState(419);
        match(PrystParser::RPAREN);
        setState(420);
        match(PrystParser::ARROW);
        setState(423);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
        case 1: {
          setState(421);
          type(0);
          break;
        }

        case 2: {
          setState(422);
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
    setState(432);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleType);
        setState(427);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(428);
        match(PrystParser::LBRACKET);
        setState(429);
        match(PrystParser::RBRACKET); 
      }
      setState(434);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
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
//----------------- TryStmtContext ------------------------------------------------------------------

PrystParser::TryStmtWrapperContext* PrystParser::TryStmtContext::tryStmtWrapper() {
  return getRuleContext<PrystParser::TryStmtWrapperContext>(0);
}

PrystParser::TryStmtContext::TryStmtContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::TryStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitTryStmt(this);
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
    setState(491);
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
        setState(435);
        expression();
        setState(436);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::IF: {
        _localctx = _tracker.createInstance<PrystParser::IfStatementContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(438);
        match(PrystParser::IF);
        setState(439);
        match(PrystParser::LPAREN);
        setState(440);
        expression();
        setState(441);
        match(PrystParser::RPAREN);
        setState(442);
        statement();
        setState(445);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
        case 1: {
          setState(443);
          match(PrystParser::ELSE);
          setState(444);
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
        setState(447);
        match(PrystParser::WHILE);
        setState(448);
        match(PrystParser::LPAREN);
        setState(449);
        expression();
        setState(450);
        match(PrystParser::RPAREN);
        setState(451);
        statement();
        break;
      }

      case PrystParser::FOR: {
        _localctx = _tracker.createInstance<PrystParser::ForStatementContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(453);
        match(PrystParser::FOR);
        setState(454);
        match(PrystParser::LPAREN);
        setState(460);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
        case 1: {
          setState(455);
          variableDecl();
          break;
        }

        case 2: {
          setState(456);
          expression();
          setState(457);
          match(PrystParser::SEMICOLON);
          break;
        }

        case 3: {
          setState(459);
          match(PrystParser::SEMICOLON);
          break;
        }

        default:
          break;
        }
        setState(463);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4089286607824248096) != 0)) {
          setState(462);
          expression();
        }
        setState(465);
        match(PrystParser::SEMICOLON);
        setState(467);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4089286607824248096) != 0)) {
          setState(466);
          expression();
        }
        setState(469);
        match(PrystParser::RPAREN);
        setState(470);
        statement();
        break;
      }

      case PrystParser::RETURN: {
        _localctx = _tracker.createInstance<PrystParser::ReturnStatementContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(471);
        match(PrystParser::RETURN);
        setState(473);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4089286607824248096) != 0)) {
          setState(472);
          expression();
        }
        setState(475);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::LBRACE: {
        _localctx = _tracker.createInstance<PrystParser::BlockStatementContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(476);
        match(PrystParser::LBRACE);
        setState(480);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4089286616430968802) != 0)) {
          setState(477);
          statement();
          setState(482);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(483);
        match(PrystParser::RBRACE);
        break;
      }

      case PrystParser::PRINT: {
        _localctx = _tracker.createInstance<PrystParser::PrintStatementContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(484);
        match(PrystParser::PRINT);
        setState(485);
        match(PrystParser::LPAREN);
        setState(486);
        expression();
        setState(487);
        match(PrystParser::RPAREN);
        setState(488);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::TRY: {
        _localctx = _tracker.createInstance<PrystParser::TryStmtContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(490);
        tryStmtWrapper();
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

//----------------- TryStmtWrapperContext ------------------------------------------------------------------

PrystParser::TryStmtWrapperContext::TryStmtWrapperContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PrystParser::TryStmtWrapperContext::getRuleIndex() const {
  return PrystParser::RuleTryStmtWrapper;
}

void PrystParser::TryStmtWrapperContext::copyFrom(TryStmtWrapperContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TryStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::TryStatementContext::TRY() {
  return getToken(PrystParser::TRY, 0);
}

PrystParser::StatementContext* PrystParser::TryStatementContext::statement() {
  return getRuleContext<PrystParser::StatementContext>(0);
}

std::vector<PrystParser::CatchBlockContext *> PrystParser::TryStatementContext::catchBlock() {
  return getRuleContexts<PrystParser::CatchBlockContext>();
}

PrystParser::CatchBlockContext* PrystParser::TryStatementContext::catchBlock(size_t i) {
  return getRuleContext<PrystParser::CatchBlockContext>(i);
}

PrystParser::TryStatementContext::TryStatementContext(TryStmtWrapperContext *ctx) { copyFrom(ctx); }


std::any PrystParser::TryStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitTryStatement(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::TryStmtWrapperContext* PrystParser::tryStmtWrapper() {
  TryStmtWrapperContext *_localctx = _tracker.createInstance<TryStmtWrapperContext>(_ctx, getState());
  enterRule(_localctx, 40, PrystParser::RuleTryStmtWrapper);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    _localctx = _tracker.createInstance<PrystParser::TryStatementContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(493);
    match(PrystParser::TRY);
    setState(494);
    statement();
    setState(496); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(495);
              catchBlock();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(498); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CatchBlockContext ------------------------------------------------------------------

PrystParser::CatchBlockContext::CatchBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PrystParser::CatchBlockContext::getRuleIndex() const {
  return PrystParser::RuleCatchBlock;
}

void PrystParser::CatchBlockContext::copyFrom(CatchBlockContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CatchStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::CatchStatementContext::CATCH() {
  return getToken(PrystParser::CATCH, 0);
}

tree::TerminalNode* PrystParser::CatchStatementContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

PrystParser::TypeContext* PrystParser::CatchStatementContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::CatchStatementContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::CatchStatementContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::StatementContext* PrystParser::CatchStatementContext::statement() {
  return getRuleContext<PrystParser::StatementContext>(0);
}

PrystParser::CatchStatementContext::CatchStatementContext(CatchBlockContext *ctx) { copyFrom(ctx); }


std::any PrystParser::CatchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitCatchStatement(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::CatchBlockContext* PrystParser::catchBlock() {
  CatchBlockContext *_localctx = _tracker.createInstance<CatchBlockContext>(_ctx, getState());
  enterRule(_localctx, 42, PrystParser::RuleCatchBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<PrystParser::CatchStatementContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(500);
    match(PrystParser::CATCH);
    setState(501);
    match(PrystParser::LPAREN);
    setState(502);
    type(0);
    setState(503);
    match(PrystParser::IDENTIFIER);
    setState(504);
    match(PrystParser::RPAREN);
    setState(505);
    statement();
   
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

PrystParser::StringLiteralRuleContext* PrystParser::ExpressionContext::stringLiteralRule() {
  return getRuleContext<PrystParser::StringLiteralRuleContext>(0);
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
  enterRule(_localctx, 44, PrystParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(514);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(507);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(508);
      lambdaFunction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(509);
      typeCastExpr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(510);
      typeConversionExpr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(511);
      classConversionExpr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(512);
      stringLiteralRule();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(513);
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

//----------------- StringLiteralRuleContext ------------------------------------------------------------------

PrystParser::StringLiteralRuleContext::StringLiteralRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PrystParser::StringLiteralRuleContext::getRuleIndex() const {
  return PrystParser::RuleStringLiteralRule;
}

void PrystParser::StringLiteralRuleContext::copyFrom(StringLiteralRuleContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StringLiteralExprContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::StringLiteralExprContext::STRING_START() {
  return getToken(PrystParser::STRING_START, 0);
}

tree::TerminalNode* PrystParser::StringLiteralExprContext::STRING_END() {
  return getToken(PrystParser::STRING_END, 0);
}

std::vector<PrystParser::StringPartContext *> PrystParser::StringLiteralExprContext::stringPart() {
  return getRuleContexts<PrystParser::StringPartContext>();
}

PrystParser::StringPartContext* PrystParser::StringLiteralExprContext::stringPart(size_t i) {
  return getRuleContext<PrystParser::StringPartContext>(i);
}

PrystParser::StringLiteralExprContext::StringLiteralExprContext(StringLiteralRuleContext *ctx) { copyFrom(ctx); }


std::any PrystParser::StringLiteralExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitStringLiteralExpr(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::StringLiteralRuleContext* PrystParser::stringLiteralRule() {
  StringLiteralRuleContext *_localctx = _tracker.createInstance<StringLiteralRuleContext>(_ctx, getState());
  enterRule(_localctx, 46, PrystParser::RuleStringLiteralRule);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<PrystParser::StringLiteralExprContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(516);
    match(PrystParser::STRING_START);
    setState(520);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 7) != 0)) {
      setState(517);
      stringPart();
      setState(522);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(523);
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
  enterRule(_localctx, 48, PrystParser::RuleStringPart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(531);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::STRING_CONTENT: {
        enterOuterAlt(_localctx, 1);
        setState(525);
        match(PrystParser::STRING_CONTENT);
        break;
      }

      case PrystParser::ESCAPE_SEQ: {
        enterOuterAlt(_localctx, 2);
        setState(526);
        match(PrystParser::ESCAPE_SEQ);
        break;
      }

      case PrystParser::INTERP_START: {
        enterOuterAlt(_localctx, 3);
        setState(527);
        match(PrystParser::INTERP_START);
        setState(528);
        expression();
        setState(529);
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
  enterRule(_localctx, 50, PrystParser::RuleAssignment);

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
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
    case 1: {
      setState(533);
      call();
      setState(534);
      match(PrystParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(538);
    qualifiedIdentifier();
    setState(539);
    match(PrystParser::EQUAL);
    setState(540);
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
  enterRule(_localctx, 52, PrystParser::RuleLogicOr);
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
    setState(542);
    logicAnd();
    setState(547);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::OR) {
      setState(543);
      match(PrystParser::OR);
      setState(544);
      logicAnd();
      setState(549);
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
  enterRule(_localctx, 54, PrystParser::RuleLogicAnd);
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
    setState(550);
    equality();
    setState(555);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::AND) {
      setState(551);
      match(PrystParser::AND);
      setState(552);
      equality();
      setState(557);
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
  enterRule(_localctx, 56, PrystParser::RuleEquality);
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
    setState(558);
    comparison();
    setState(563);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::NOT_EQUAL

    || _la == PrystParser::EQUAL_EQUAL) {
      setState(559);
      _la = _input->LA(1);
      if (!(_la == PrystParser::NOT_EQUAL

      || _la == PrystParser::EQUAL_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(560);
      comparison();
      setState(565);
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
  enterRule(_localctx, 58, PrystParser::RuleComparison);
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
    setState(566);
    addition();
    setState(571);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3588805953060864) != 0)) {
      setState(567);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3588805953060864) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(568);
      addition();
      setState(573);
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
  enterRule(_localctx, 60, PrystParser::RuleAddition);
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
    setState(574);
    multiplication();
    setState(579);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(575);
        _la = _input->LA(1);
        if (!(_la == PrystParser::MINUS

        || _la == PrystParser::PLUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(576);
        multiplication(); 
      }
      setState(581);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
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
  enterRule(_localctx, 62, PrystParser::RuleMultiplication);
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
    setState(582);
    unary();
    setState(587);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72070788177461248) != 0)) {
      setState(583);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 72070788177461248) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(584);
      unary();
      setState(589);
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
  enterRule(_localctx, 64, PrystParser::RuleUnary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(593);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT: {
        enterOuterAlt(_localctx, 1);
        setState(590);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 54061337470304256) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(591);
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
        setState(592);
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
  enterRule(_localctx, 66, PrystParser::RulePostfix);

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
    setState(595);
    primary();
    setState(601);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(599);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PrystParser::LPAREN:
          case PrystParser::DOT: {
            setState(596);
            suffix();
            break;
          }

          case PrystParser::INCREMENT: {
            setState(597);
            match(PrystParser::INCREMENT);
            break;
          }

          case PrystParser::DECREMENT: {
            setState(598);
            match(PrystParser::DECREMENT);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(603);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx);
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
  enterRule(_localctx, 68, PrystParser::RuleSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(606);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(604);
        callSuffix();
        break;
      }

      case PrystParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(605);
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
  enterRule(_localctx, 70, PrystParser::RuleCallSuffix);
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
    setState(608);
    match(PrystParser::LPAREN);
    setState(610);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286607824248096) != 0)) {
      setState(609);
      arguments();
    }
    setState(612);
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
  enterRule(_localctx, 72, PrystParser::RuleMemberSuffix);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(623);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(614);
      match(PrystParser::DOT);
      setState(615);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(616);
      match(PrystParser::DOT);
      setState(617);
      match(PrystParser::IDENTIFIER);
      setState(618);
      match(PrystParser::LPAREN);
      setState(620);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286607824248096) != 0)) {
        setState(619);
        arguments();
      }
      setState(622);
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
  enterRule(_localctx, 74, PrystParser::RuleCall);

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
    setState(625);
    qualifiedIdentifier();
    setState(630);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(626);
        match(PrystParser::DOT);
        setState(627);
        match(PrystParser::IDENTIFIER); 
      }
      setState(632);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx);
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
  enterRule(_localctx, 76, PrystParser::RulePrimary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(654);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(633);
        match(PrystParser::TRUE);
        break;
      }

      case PrystParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(634);
        match(PrystParser::FALSE);
        break;
      }

      case PrystParser::NULL_: {
        enterOuterAlt(_localctx, 3);
        setState(635);
        match(PrystParser::NULL_);
        break;
      }

      case PrystParser::THIS: {
        enterOuterAlt(_localctx, 4);
        setState(636);
        match(PrystParser::THIS);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(637);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 6);
        setState(638);
        qualifiedIdentifier();
        setState(644);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
        case 1: {
          setState(639);
          match(PrystParser::LPAREN);
          setState(641);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4089286607824248096) != 0)) {
            setState(640);
            arguments();
          }
          setState(643);
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
        setState(646);
        match(PrystParser::LPAREN);
        setState(647);
        expression();
        setState(648);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::SUPER: {
        enterOuterAlt(_localctx, 8);
        setState(650);
        match(PrystParser::SUPER);
        setState(651);
        match(PrystParser::DOT);
        setState(652);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::NEW: {
        enterOuterAlt(_localctx, 9);
        setState(653);
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
  enterRule(_localctx, 78, PrystParser::RuleQualifiedIdentifier);
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
    setState(656);
    match(PrystParser::IDENTIFIER);
    setState(661);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::DOUBLE_COLON) {
      setState(657);
      match(PrystParser::DOUBLE_COLON);
      setState(658);
      match(PrystParser::IDENTIFIER);
      setState(663);
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
  enterRule(_localctx, 80, PrystParser::RuleNewExpression);
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
    setState(664);
    match(PrystParser::NEW);
    setState(665);
    match(PrystParser::IDENTIFIER);
    setState(666);
    match(PrystParser::LPAREN);
    setState(668);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286607824248096) != 0)) {
      setState(667);
      arguments();
    }
    setState(670);
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
  enterRule(_localctx, 82, PrystParser::RuleArguments);
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
    setState(672);
    expression();
    setState(677);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(673);
      match(PrystParser::COMMA);
      setState(674);
      expression();
      setState(679);
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
  enterRule(_localctx, 84, PrystParser::RuleTypeCastExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(690);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(680);
      match(PrystParser::LPAREN);
      setState(681);
      type(0);
      setState(682);
      match(PrystParser::RPAREN);
      setState(683);
      expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(685);
      type(0);
      setState(686);
      match(PrystParser::LPAREN);
      setState(687);
      expression();
      setState(688);
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
  enterRule(_localctx, 86, PrystParser::RuleTypeConversionExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(692);
    type(0);
    setState(693);
    match(PrystParser::DOT);
    setState(694);
    match(PrystParser::CONVERT);
    setState(695);
    match(PrystParser::LPAREN);
    setState(696);
    expression();
    setState(697);
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
  enterRule(_localctx, 88, PrystParser::RuleClassConversionExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(699);
    match(PrystParser::IDENTIFIER);
    setState(700);
    match(PrystParser::DOT);
    setState(701);
    match(PrystParser::CONVERT);
    setState(702);
    match(PrystParser::LPAREN);
    setState(703);
    expression();
    setState(704);
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
