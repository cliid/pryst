
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
      "block", "variableDecl", "classDecl", "classBody", "classMember", 
      "paramList", "param", "paramTypeList", "type", "statement", "expression", 
      "stringLiteral", "stringPart", "assignment", "logicOr", "logicAnd", 
      "equality", "comparison", "addition", "multiplication", "unary", "postfix", 
      "suffix", "callSuffix", "memberSuffix", "call", "primary", "qualifiedIdentifier", 
      "newExpr", "arguments", "typeCastExpr", "typeConversionExpr", "classConversionExpr", 
      "tryCatchStmt"
    },
    std::vector<std::string>{
      "", "'print'", "'class'", "'extends'", "'else'", "'false'", "'for'", 
      "'if'", "'null'", "'return'", "'super'", "'this'", "'true'", "'while'", 
      "'new'", "'convert'", "'namespace'", "'module'", "'import'", "'using'", 
      "'let'", "'fn'", "'const'", "'const!'", "'try'", "'catch'", "'int'", 
      "'float'", "'bool'", "'str'", "'void'", "'('", "')'", "'{'", "", "'['", 
      "']'", "','", "'.'", "'-'", "'+'", "';'", "'/'", "'*'", "'!'", "'='", 
      "'<'", "'>'", "'!='", "'=='", "'>='", "'<='", "'&&'", "'||'", "'++'", 
      "'--'", "'%'", "'->'", "'::'", "", "", "", "", "", "", "", "", "'${'"
    },
    std::vector<std::string>{
      "", "PRINT", "CLASS", "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", 
      "RETURN", "SUPER", "THIS", "TRUE", "WHILE", "NEW", "CONVERT", "NAMESPACE", 
      "MODULE", "IMPORT", "USING", "LET", "FN", "CONST", "CONST_EXPR", "TRY", 
      "CATCH", "INT_TYPE", "FLOAT_TYPE", "BOOL_TYPE", "STR_TYPE", "VOID_TYPE", 
      "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA", 
      "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", "EQUAL", 
      "LESS", "GREATER", "NOT_EQUAL", "EQUAL_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", 
      "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "ARROW", "DOUBLE_COLON", 
      "NUMBER", "IDENTIFIER", "STRING", "STRING_START", "COMMENT", "WS", 
      "STRING_CONTENT", "ESCAPE_SEQ", "INTERP_START", "INTERP_END", "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,69,620,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,1,0,5,0,90,8,0,10,0,12,0,93,9,0,1,0,1,0,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,3,1,105,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,127,8,2,1,3,1,3,1,3,1,3,1,4,
  	1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,5,6,144,8,6,10,6,12,6,147,9,6,
  	1,7,1,7,3,7,151,8,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,160,8,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,3,8,169,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,
  	180,8,8,1,8,1,8,1,8,3,8,185,8,8,1,9,1,9,3,9,189,8,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,3,9,198,8,9,1,9,1,9,1,9,1,9,1,9,3,9,205,8,9,1,10,1,10,5,10,
  	209,8,10,10,10,12,10,212,9,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,3,11,226,8,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,3,11,237,8,11,1,12,1,12,1,12,1,12,3,12,243,8,12,1,12,1,12,1,
  	13,1,13,5,13,249,8,13,10,13,12,13,252,9,13,1,13,1,13,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,284,8,14,1,
  	14,1,14,1,14,1,14,1,14,3,14,291,8,14,1,15,1,15,1,15,5,15,296,8,15,10,
  	15,12,15,299,9,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,310,
  	8,16,1,16,1,16,1,16,3,16,315,8,16,1,17,1,17,1,17,5,17,320,8,17,10,17,
  	12,17,323,9,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	1,18,1,18,3,18,338,8,18,1,18,1,18,3,18,342,8,18,1,18,1,18,1,18,5,18,347,
  	8,18,10,18,12,18,350,9,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,3,19,362,8,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,3,19,377,8,19,1,19,3,19,380,8,19,1,19,1,19,3,19,384,8,
  	19,1,19,1,19,1,19,1,19,3,19,390,8,19,1,19,1,19,1,19,1,19,1,19,1,19,1,
  	19,1,19,5,19,400,8,19,10,19,12,19,403,9,19,3,19,405,8,19,1,19,1,19,3,
  	19,409,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,418,8,20,1,21,1,21,
  	5,21,422,8,21,10,21,12,21,425,9,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,
  	1,22,3,22,435,8,22,1,23,1,23,1,23,3,23,440,8,23,1,23,1,23,1,23,1,23,1,
  	24,1,24,1,24,5,24,449,8,24,10,24,12,24,452,9,24,1,25,1,25,1,25,5,25,457,
  	8,25,10,25,12,25,460,9,25,1,26,1,26,1,26,5,26,465,8,26,10,26,12,26,468,
  	9,26,1,27,1,27,1,27,5,27,473,8,27,10,27,12,27,476,9,27,1,28,1,28,1,28,
  	5,28,481,8,28,10,28,12,28,484,9,28,1,29,1,29,1,29,5,29,489,8,29,10,29,
  	12,29,492,9,29,1,30,1,30,1,30,3,30,497,8,30,1,31,1,31,1,31,1,31,5,31,
  	503,8,31,10,31,12,31,506,9,31,1,32,1,32,3,32,510,8,32,1,33,1,33,3,33,
  	514,8,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,34,3,34,524,8,34,1,34,3,
  	34,527,8,34,1,35,1,35,1,35,5,35,532,8,35,10,35,12,35,535,9,35,1,36,1,
  	36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,546,8,36,1,36,3,36,549,8,36,
  	1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,559,8,36,1,37,1,37,1,37,
  	5,37,564,8,37,10,37,12,37,567,9,37,1,38,1,38,1,38,1,38,3,38,573,8,38,
  	1,38,1,38,1,39,1,39,1,39,5,39,580,8,39,10,39,12,39,583,9,39,1,40,1,40,
  	1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,3,40,595,8,40,1,41,1,41,1,41,
  	1,41,1,41,1,41,1,41,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,43,1,43,1,43,
  	1,43,1,43,1,43,1,43,3,43,618,8,43,1,43,0,1,36,44,0,2,4,6,8,10,12,14,16,
  	18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,
  	64,66,68,70,72,74,76,78,80,82,84,86,0,6,2,0,20,20,22,22,1,0,48,49,2,0,
  	46,47,50,51,1,0,39,40,2,0,42,43,56,56,3,0,39,39,44,44,54,55,676,0,91,
  	1,0,0,0,2,104,1,0,0,0,4,126,1,0,0,0,6,128,1,0,0,0,8,132,1,0,0,0,10,136,
  	1,0,0,0,12,140,1,0,0,0,14,150,1,0,0,0,16,184,1,0,0,0,18,204,1,0,0,0,20,
  	206,1,0,0,0,22,236,1,0,0,0,24,238,1,0,0,0,26,246,1,0,0,0,28,290,1,0,0,
  	0,30,292,1,0,0,0,32,314,1,0,0,0,34,316,1,0,0,0,36,341,1,0,0,0,38,408,
  	1,0,0,0,40,417,1,0,0,0,42,419,1,0,0,0,44,434,1,0,0,0,46,439,1,0,0,0,48,
  	445,1,0,0,0,50,453,1,0,0,0,52,461,1,0,0,0,54,469,1,0,0,0,56,477,1,0,0,
  	0,58,485,1,0,0,0,60,496,1,0,0,0,62,498,1,0,0,0,64,509,1,0,0,0,66,511,
  	1,0,0,0,68,526,1,0,0,0,70,528,1,0,0,0,72,558,1,0,0,0,74,560,1,0,0,0,76,
  	568,1,0,0,0,78,576,1,0,0,0,80,594,1,0,0,0,82,596,1,0,0,0,84,603,1,0,0,
  	0,86,610,1,0,0,0,88,90,3,2,1,0,89,88,1,0,0,0,90,93,1,0,0,0,91,89,1,0,
  	0,0,91,92,1,0,0,0,92,94,1,0,0,0,93,91,1,0,0,0,94,95,5,0,0,1,95,1,1,0,
  	0,0,96,105,3,14,7,0,97,105,3,22,11,0,98,105,3,24,12,0,99,105,3,4,2,0,
  	100,105,3,38,19,0,101,105,3,6,3,0,102,105,3,8,4,0,103,105,3,10,5,0,104,
  	96,1,0,0,0,104,97,1,0,0,0,104,98,1,0,0,0,104,99,1,0,0,0,104,100,1,0,0,
  	0,104,101,1,0,0,0,104,102,1,0,0,0,104,103,1,0,0,0,105,3,1,0,0,0,106,107,
  	5,19,0,0,107,108,5,16,0,0,108,109,3,74,37,0,109,110,5,41,0,0,110,127,
  	1,0,0,0,111,112,5,19,0,0,112,113,5,17,0,0,113,114,3,74,37,0,114,115,5,
  	41,0,0,115,127,1,0,0,0,116,117,5,19,0,0,117,118,5,16,0,0,118,119,3,74,
  	37,0,119,120,3,20,10,0,120,127,1,0,0,0,121,122,5,19,0,0,122,123,5,17,
  	0,0,123,124,3,74,37,0,124,125,3,20,10,0,125,127,1,0,0,0,126,106,1,0,0,
  	0,126,111,1,0,0,0,126,116,1,0,0,0,126,121,1,0,0,0,127,5,1,0,0,0,128,129,
  	5,16,0,0,129,130,3,74,37,0,130,131,3,20,10,0,131,7,1,0,0,0,132,133,5,
  	17,0,0,133,134,3,74,37,0,134,135,3,20,10,0,135,9,1,0,0,0,136,137,5,18,
  	0,0,137,138,3,12,6,0,138,139,5,41,0,0,139,11,1,0,0,0,140,145,5,60,0,0,
  	141,142,5,58,0,0,142,144,5,60,0,0,143,141,1,0,0,0,144,147,1,0,0,0,145,
  	143,1,0,0,0,145,146,1,0,0,0,146,13,1,0,0,0,147,145,1,0,0,0,148,151,3,
  	16,8,0,149,151,3,18,9,0,150,148,1,0,0,0,150,149,1,0,0,0,151,15,1,0,0,
  	0,152,153,5,21,0,0,153,154,5,46,0,0,154,155,3,36,18,0,155,156,5,47,0,
  	0,156,157,5,60,0,0,157,159,5,31,0,0,158,160,3,30,15,0,159,158,1,0,0,0,
  	159,160,1,0,0,0,160,161,1,0,0,0,161,162,5,32,0,0,162,163,3,20,10,0,163,
  	185,1,0,0,0,164,165,5,21,0,0,165,166,5,60,0,0,166,168,5,31,0,0,167,169,
  	3,30,15,0,168,167,1,0,0,0,168,169,1,0,0,0,169,170,1,0,0,0,170,171,5,32,
  	0,0,171,172,5,57,0,0,172,173,3,36,18,0,173,174,3,20,10,0,174,185,1,0,
  	0,0,175,176,3,36,18,0,176,177,5,60,0,0,177,179,5,31,0,0,178,180,3,30,
  	15,0,179,178,1,0,0,0,179,180,1,0,0,0,180,181,1,0,0,0,181,182,5,32,0,0,
  	182,183,3,20,10,0,183,185,1,0,0,0,184,152,1,0,0,0,184,164,1,0,0,0,184,
  	175,1,0,0,0,185,17,1,0,0,0,186,188,5,31,0,0,187,189,3,30,15,0,188,187,
  	1,0,0,0,188,189,1,0,0,0,189,190,1,0,0,0,190,191,5,32,0,0,191,192,5,57,
  	0,0,192,193,3,36,18,0,193,194,3,20,10,0,194,205,1,0,0,0,195,197,5,31,
  	0,0,196,198,3,30,15,0,197,196,1,0,0,0,197,198,1,0,0,0,198,199,1,0,0,0,
  	199,200,5,32,0,0,200,201,5,57,0,0,201,202,3,36,18,0,202,203,3,40,20,0,
  	203,205,1,0,0,0,204,186,1,0,0,0,204,195,1,0,0,0,205,19,1,0,0,0,206,210,
  	5,33,0,0,207,209,3,2,1,0,208,207,1,0,0,0,209,212,1,0,0,0,210,208,1,0,
  	0,0,210,211,1,0,0,0,211,213,1,0,0,0,212,210,1,0,0,0,213,214,5,34,0,0,
  	214,21,1,0,0,0,215,216,7,0,0,0,216,217,5,60,0,0,217,218,5,45,0,0,218,
  	219,3,40,20,0,219,220,5,41,0,0,220,237,1,0,0,0,221,226,3,36,18,0,222,
  	223,5,22,0,0,223,226,3,36,18,0,224,226,5,23,0,0,225,221,1,0,0,0,225,222,
  	1,0,0,0,225,224,1,0,0,0,226,227,1,0,0,0,227,228,5,60,0,0,228,229,5,45,
  	0,0,229,230,3,40,20,0,230,231,5,41,0,0,231,237,1,0,0,0,232,233,3,36,18,
  	0,233,234,5,60,0,0,234,235,5,41,0,0,235,237,1,0,0,0,236,215,1,0,0,0,236,
  	225,1,0,0,0,236,232,1,0,0,0,237,23,1,0,0,0,238,239,5,2,0,0,239,242,5,
  	60,0,0,240,241,5,3,0,0,241,243,5,60,0,0,242,240,1,0,0,0,242,243,1,0,0,
  	0,243,244,1,0,0,0,244,245,3,26,13,0,245,25,1,0,0,0,246,250,5,33,0,0,247,
  	249,3,28,14,0,248,247,1,0,0,0,249,252,1,0,0,0,250,248,1,0,0,0,250,251,
  	1,0,0,0,251,253,1,0,0,0,252,250,1,0,0,0,253,254,5,34,0,0,254,27,1,0,0,
  	0,255,256,3,36,18,0,256,257,5,60,0,0,257,258,5,45,0,0,258,259,3,40,20,
  	0,259,260,5,41,0,0,260,291,1,0,0,0,261,262,5,20,0,0,262,263,5,60,0,0,
  	263,264,5,45,0,0,264,265,3,40,20,0,265,266,5,41,0,0,266,291,1,0,0,0,267,
  	268,5,22,0,0,268,269,5,60,0,0,269,270,5,45,0,0,270,271,3,40,20,0,271,
  	272,5,41,0,0,272,291,1,0,0,0,273,274,5,22,0,0,274,275,3,36,18,0,275,276,
  	5,60,0,0,276,277,5,45,0,0,277,278,3,40,20,0,278,279,5,41,0,0,279,291,
  	1,0,0,0,280,281,5,60,0,0,281,283,5,31,0,0,282,284,3,30,15,0,283,282,1,
  	0,0,0,283,284,1,0,0,0,284,285,1,0,0,0,285,286,5,32,0,0,286,287,5,57,0,
  	0,287,288,3,36,18,0,288,289,3,20,10,0,289,291,1,0,0,0,290,255,1,0,0,0,
  	290,261,1,0,0,0,290,267,1,0,0,0,290,273,1,0,0,0,290,280,1,0,0,0,291,29,
  	1,0,0,0,292,297,3,32,16,0,293,294,5,37,0,0,294,296,3,32,16,0,295,293,
  	1,0,0,0,296,299,1,0,0,0,297,295,1,0,0,0,297,298,1,0,0,0,298,31,1,0,0,
  	0,299,297,1,0,0,0,300,301,3,36,18,0,301,302,5,60,0,0,302,315,1,0,0,0,
  	303,304,5,21,0,0,304,305,5,46,0,0,305,306,3,36,18,0,306,307,5,47,0,0,
  	307,309,5,31,0,0,308,310,3,34,17,0,309,308,1,0,0,0,309,310,1,0,0,0,310,
  	311,1,0,0,0,311,312,5,32,0,0,312,313,5,60,0,0,313,315,1,0,0,0,314,300,
  	1,0,0,0,314,303,1,0,0,0,315,33,1,0,0,0,316,321,3,36,18,0,317,318,5,37,
  	0,0,318,320,3,36,18,0,319,317,1,0,0,0,320,323,1,0,0,0,321,319,1,0,0,0,
  	321,322,1,0,0,0,322,35,1,0,0,0,323,321,1,0,0,0,324,325,6,18,-1,0,325,
  	342,5,26,0,0,326,342,5,27,0,0,327,342,5,28,0,0,328,342,5,29,0,0,329,342,
  	5,30,0,0,330,342,5,60,0,0,331,332,5,21,0,0,332,333,5,46,0,0,333,334,3,
  	36,18,0,334,335,5,47,0,0,335,337,5,31,0,0,336,338,3,34,17,0,337,336,1,
  	0,0,0,337,338,1,0,0,0,338,339,1,0,0,0,339,340,5,32,0,0,340,342,1,0,0,
  	0,341,324,1,0,0,0,341,326,1,0,0,0,341,327,1,0,0,0,341,328,1,0,0,0,341,
  	329,1,0,0,0,341,330,1,0,0,0,341,331,1,0,0,0,342,348,1,0,0,0,343,344,10,
  	2,0,0,344,345,5,35,0,0,345,347,5,36,0,0,346,343,1,0,0,0,347,350,1,0,0,
  	0,348,346,1,0,0,0,348,349,1,0,0,0,349,37,1,0,0,0,350,348,1,0,0,0,351,
  	352,3,40,20,0,352,353,5,41,0,0,353,409,1,0,0,0,354,355,5,7,0,0,355,356,
  	5,31,0,0,356,357,3,40,20,0,357,358,5,32,0,0,358,361,3,38,19,0,359,360,
  	5,4,0,0,360,362,3,38,19,0,361,359,1,0,0,0,361,362,1,0,0,0,362,409,1,0,
  	0,0,363,364,5,13,0,0,364,365,5,31,0,0,365,366,3,40,20,0,366,367,5,32,
  	0,0,367,368,3,38,19,0,368,409,1,0,0,0,369,370,5,6,0,0,370,376,5,31,0,
  	0,371,377,3,22,11,0,372,373,3,40,20,0,373,374,5,41,0,0,374,377,1,0,0,
  	0,375,377,5,41,0,0,376,371,1,0,0,0,376,372,1,0,0,0,376,375,1,0,0,0,377,
  	379,1,0,0,0,378,380,3,40,20,0,379,378,1,0,0,0,379,380,1,0,0,0,380,381,
  	1,0,0,0,381,383,5,41,0,0,382,384,3,40,20,0,383,382,1,0,0,0,383,384,1,
  	0,0,0,384,385,1,0,0,0,385,386,5,32,0,0,386,409,3,38,19,0,387,389,5,9,
  	0,0,388,390,3,40,20,0,389,388,1,0,0,0,389,390,1,0,0,0,390,391,1,0,0,0,
  	391,409,5,41,0,0,392,409,3,20,10,0,393,409,3,86,43,0,394,395,5,1,0,0,
  	395,404,5,31,0,0,396,401,3,40,20,0,397,398,5,37,0,0,398,400,3,40,20,0,
  	399,397,1,0,0,0,400,403,1,0,0,0,401,399,1,0,0,0,401,402,1,0,0,0,402,405,
  	1,0,0,0,403,401,1,0,0,0,404,396,1,0,0,0,404,405,1,0,0,0,405,406,1,0,0,
  	0,406,407,5,32,0,0,407,409,5,41,0,0,408,351,1,0,0,0,408,354,1,0,0,0,408,
  	363,1,0,0,0,408,369,1,0,0,0,408,387,1,0,0,0,408,392,1,0,0,0,408,393,1,
  	0,0,0,408,394,1,0,0,0,409,39,1,0,0,0,410,418,3,46,23,0,411,418,3,18,9,
  	0,412,418,3,80,40,0,413,418,3,82,41,0,414,418,3,84,42,0,415,418,3,42,
  	21,0,416,418,3,48,24,0,417,410,1,0,0,0,417,411,1,0,0,0,417,412,1,0,0,
  	0,417,413,1,0,0,0,417,414,1,0,0,0,417,415,1,0,0,0,417,416,1,0,0,0,418,
  	41,1,0,0,0,419,423,5,62,0,0,420,422,3,44,22,0,421,420,1,0,0,0,422,425,
  	1,0,0,0,423,421,1,0,0,0,423,424,1,0,0,0,424,426,1,0,0,0,425,423,1,0,0,
  	0,426,427,5,69,0,0,427,43,1,0,0,0,428,435,5,65,0,0,429,435,5,66,0,0,430,
  	431,5,67,0,0,431,432,3,40,20,0,432,433,5,68,0,0,433,435,1,0,0,0,434,428,
  	1,0,0,0,434,429,1,0,0,0,434,430,1,0,0,0,435,45,1,0,0,0,436,437,3,70,35,
  	0,437,438,5,38,0,0,438,440,1,0,0,0,439,436,1,0,0,0,439,440,1,0,0,0,440,
  	441,1,0,0,0,441,442,3,74,37,0,442,443,5,45,0,0,443,444,3,40,20,0,444,
  	47,1,0,0,0,445,450,3,50,25,0,446,447,5,53,0,0,447,449,3,50,25,0,448,446,
  	1,0,0,0,449,452,1,0,0,0,450,448,1,0,0,0,450,451,1,0,0,0,451,49,1,0,0,
  	0,452,450,1,0,0,0,453,458,3,52,26,0,454,455,5,52,0,0,455,457,3,52,26,
  	0,456,454,1,0,0,0,457,460,1,0,0,0,458,456,1,0,0,0,458,459,1,0,0,0,459,
  	51,1,0,0,0,460,458,1,0,0,0,461,466,3,54,27,0,462,463,7,1,0,0,463,465,
  	3,54,27,0,464,462,1,0,0,0,465,468,1,0,0,0,466,464,1,0,0,0,466,467,1,0,
  	0,0,467,53,1,0,0,0,468,466,1,0,0,0,469,474,3,56,28,0,470,471,7,2,0,0,
  	471,473,3,56,28,0,472,470,1,0,0,0,473,476,1,0,0,0,474,472,1,0,0,0,474,
  	475,1,0,0,0,475,55,1,0,0,0,476,474,1,0,0,0,477,482,3,58,29,0,478,479,
  	7,3,0,0,479,481,3,58,29,0,480,478,1,0,0,0,481,484,1,0,0,0,482,480,1,0,
  	0,0,482,483,1,0,0,0,483,57,1,0,0,0,484,482,1,0,0,0,485,490,3,60,30,0,
  	486,487,7,4,0,0,487,489,3,60,30,0,488,486,1,0,0,0,489,492,1,0,0,0,490,
  	488,1,0,0,0,490,491,1,0,0,0,491,59,1,0,0,0,492,490,1,0,0,0,493,494,7,
  	5,0,0,494,497,3,60,30,0,495,497,3,62,31,0,496,493,1,0,0,0,496,495,1,0,
  	0,0,497,61,1,0,0,0,498,504,3,72,36,0,499,503,3,64,32,0,500,503,5,54,0,
  	0,501,503,5,55,0,0,502,499,1,0,0,0,502,500,1,0,0,0,502,501,1,0,0,0,503,
  	506,1,0,0,0,504,502,1,0,0,0,504,505,1,0,0,0,505,63,1,0,0,0,506,504,1,
  	0,0,0,507,510,3,66,33,0,508,510,3,68,34,0,509,507,1,0,0,0,509,508,1,0,
  	0,0,510,65,1,0,0,0,511,513,5,31,0,0,512,514,3,78,39,0,513,512,1,0,0,0,
  	513,514,1,0,0,0,514,515,1,0,0,0,515,516,5,32,0,0,516,67,1,0,0,0,517,518,
  	5,38,0,0,518,527,5,60,0,0,519,520,5,38,0,0,520,521,5,60,0,0,521,523,5,
  	31,0,0,522,524,3,78,39,0,523,522,1,0,0,0,523,524,1,0,0,0,524,525,1,0,
  	0,0,525,527,5,32,0,0,526,517,1,0,0,0,526,519,1,0,0,0,527,69,1,0,0,0,528,
  	533,3,74,37,0,529,530,5,38,0,0,530,532,5,60,0,0,531,529,1,0,0,0,532,535,
  	1,0,0,0,533,531,1,0,0,0,533,534,1,0,0,0,534,71,1,0,0,0,535,533,1,0,0,
  	0,536,559,5,12,0,0,537,559,5,5,0,0,538,559,5,8,0,0,539,559,5,11,0,0,540,
  	559,5,59,0,0,541,559,5,61,0,0,542,548,3,74,37,0,543,545,5,31,0,0,544,
  	546,3,78,39,0,545,544,1,0,0,0,545,546,1,0,0,0,546,547,1,0,0,0,547,549,
  	5,32,0,0,548,543,1,0,0,0,548,549,1,0,0,0,549,559,1,0,0,0,550,551,5,31,
  	0,0,551,552,3,40,20,0,552,553,5,32,0,0,553,559,1,0,0,0,554,555,5,10,0,
  	0,555,556,5,38,0,0,556,559,5,60,0,0,557,559,3,76,38,0,558,536,1,0,0,0,
  	558,537,1,0,0,0,558,538,1,0,0,0,558,539,1,0,0,0,558,540,1,0,0,0,558,541,
  	1,0,0,0,558,542,1,0,0,0,558,550,1,0,0,0,558,554,1,0,0,0,558,557,1,0,0,
  	0,559,73,1,0,0,0,560,565,5,60,0,0,561,562,5,58,0,0,562,564,5,60,0,0,563,
  	561,1,0,0,0,564,567,1,0,0,0,565,563,1,0,0,0,565,566,1,0,0,0,566,75,1,
  	0,0,0,567,565,1,0,0,0,568,569,5,14,0,0,569,570,5,60,0,0,570,572,5,31,
  	0,0,571,573,3,78,39,0,572,571,1,0,0,0,572,573,1,0,0,0,573,574,1,0,0,0,
  	574,575,5,32,0,0,575,77,1,0,0,0,576,581,3,40,20,0,577,578,5,37,0,0,578,
  	580,3,40,20,0,579,577,1,0,0,0,580,583,1,0,0,0,581,579,1,0,0,0,581,582,
  	1,0,0,0,582,79,1,0,0,0,583,581,1,0,0,0,584,585,5,31,0,0,585,586,3,36,
  	18,0,586,587,5,32,0,0,587,588,3,40,20,0,588,595,1,0,0,0,589,590,3,36,
  	18,0,590,591,5,31,0,0,591,592,3,40,20,0,592,593,5,32,0,0,593,595,1,0,
  	0,0,594,584,1,0,0,0,594,589,1,0,0,0,595,81,1,0,0,0,596,597,3,36,18,0,
  	597,598,5,38,0,0,598,599,5,15,0,0,599,600,5,31,0,0,600,601,3,40,20,0,
  	601,602,5,32,0,0,602,83,1,0,0,0,603,604,5,60,0,0,604,605,5,38,0,0,605,
  	606,5,15,0,0,606,607,5,31,0,0,607,608,3,40,20,0,608,609,5,32,0,0,609,
  	85,1,0,0,0,610,611,5,24,0,0,611,617,3,38,19,0,612,613,5,25,0,0,613,614,
  	5,31,0,0,614,615,5,60,0,0,615,616,5,32,0,0,616,618,3,38,19,0,617,612,
  	1,0,0,0,617,618,1,0,0,0,618,87,1,0,0,0,60,91,104,126,145,150,159,168,
  	179,184,188,197,204,210,225,236,242,250,283,290,297,309,314,321,337,341,
  	348,361,376,379,383,389,401,404,408,417,423,434,439,450,458,466,474,482,
  	490,496,502,504,509,513,523,526,533,545,548,558,565,572,581,594,617
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
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8700972634872971238) != 0)) {
      setState(88);
      declaration();
      setState(93);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(94);
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

PrystParser::ClassDeclContext* PrystParser::DeclarationContext::classDecl() {
  return getRuleContext<PrystParser::ClassDeclContext>(0);
}

PrystParser::UsingDeclContext* PrystParser::DeclarationContext::usingDecl() {
  return getRuleContext<PrystParser::UsingDeclContext>(0);
}

PrystParser::StatementContext* PrystParser::DeclarationContext::statement() {
  return getRuleContext<PrystParser::StatementContext>(0);
}

PrystParser::NamespaceDeclContext* PrystParser::DeclarationContext::namespaceDecl() {
  return getRuleContext<PrystParser::NamespaceDeclContext>(0);
}

PrystParser::ModuleDeclContext* PrystParser::DeclarationContext::moduleDecl() {
  return getRuleContext<PrystParser::ModuleDeclContext>(0);
}

PrystParser::ImportDeclContext* PrystParser::DeclarationContext::importDecl() {
  return getRuleContext<PrystParser::ImportDeclContext>(0);
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
    setState(104);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(96);
      functionDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(97);
      variableDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(98);
      classDecl();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(99);
      usingDecl();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(100);
      statement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(101);
      namespaceDecl();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(102);
      moduleDecl();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(103);
      importDecl();
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

tree::TerminalNode* PrystParser::UsingDeclContext::USING() {
  return getToken(PrystParser::USING, 0);
}

tree::TerminalNode* PrystParser::UsingDeclContext::NAMESPACE() {
  return getToken(PrystParser::NAMESPACE, 0);
}

PrystParser::QualifiedIdentifierContext* PrystParser::UsingDeclContext::qualifiedIdentifier() {
  return getRuleContext<PrystParser::QualifiedIdentifierContext>(0);
}

tree::TerminalNode* PrystParser::UsingDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::UsingDeclContext::MODULE() {
  return getToken(PrystParser::MODULE, 0);
}

PrystParser::BlockContext* PrystParser::UsingDeclContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
}


size_t PrystParser::UsingDeclContext::getRuleIndex() const {
  return PrystParser::RuleUsingDecl;
}


std::any PrystParser::UsingDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitUsingDecl(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::UsingDeclContext* PrystParser::usingDecl() {
  UsingDeclContext *_localctx = _tracker.createInstance<UsingDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, PrystParser::RuleUsingDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(126);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(106);
      match(PrystParser::USING);
      setState(107);
      match(PrystParser::NAMESPACE);
      setState(108);
      qualifiedIdentifier();
      setState(109);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(111);
      match(PrystParser::USING);
      setState(112);
      match(PrystParser::MODULE);
      setState(113);
      qualifiedIdentifier();
      setState(114);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(116);
      match(PrystParser::USING);
      setState(117);
      match(PrystParser::NAMESPACE);
      setState(118);
      qualifiedIdentifier();
      setState(119);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(121);
      match(PrystParser::USING);
      setState(122);
      match(PrystParser::MODULE);
      setState(123);
      qualifiedIdentifier();
      setState(124);
      block();
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

PrystParser::BlockContext* PrystParser::NamespaceDeclContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(128);
    match(PrystParser::NAMESPACE);
    setState(129);
    qualifiedIdentifier();
    setState(130);
    block();
   
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

PrystParser::BlockContext* PrystParser::ModuleDeclContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
    match(PrystParser::MODULE);
    setState(133);
    qualifiedIdentifier();
    setState(134);
    block();
   
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
    setState(136);
    match(PrystParser::IMPORT);
    setState(137);
    importPath();
    setState(138);
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
    setState(140);
    match(PrystParser::IDENTIFIER);
    setState(145);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::DOUBLE_COLON) {
      setState(141);
      match(PrystParser::DOUBLE_COLON);
      setState(142);
      match(PrystParser::IDENTIFIER);
      setState(147);
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
    setState(150);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::FN:
      case PrystParser::INT_TYPE:
      case PrystParser::FLOAT_TYPE:
      case PrystParser::BOOL_TYPE:
      case PrystParser::STR_TYPE:
      case PrystParser::VOID_TYPE:
      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(148);
        namedFunction();
        break;
      }

      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(149);
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

PrystParser::BlockContext* PrystParser::NamedFunctionContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
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
    setState(184);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(152);
      match(PrystParser::FN);
      setState(153);
      match(PrystParser::LESS);
      setState(154);
      type(0);
      setState(155);
      match(PrystParser::GREATER);
      setState(156);
      match(PrystParser::IDENTIFIER);
      setState(157);
      match(PrystParser::LPAREN);
      setState(159);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921506689318912) != 0)) {
        setState(158);
        paramList();
      }
      setState(161);
      match(PrystParser::RPAREN);
      setState(162);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(164);
      match(PrystParser::FN);
      setState(165);
      match(PrystParser::IDENTIFIER);
      setState(166);
      match(PrystParser::LPAREN);
      setState(168);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921506689318912) != 0)) {
        setState(167);
        paramList();
      }
      setState(170);
      match(PrystParser::RPAREN);
      setState(171);
      match(PrystParser::ARROW);
      setState(172);
      type(0);
      setState(173);
      block();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(175);
      type(0);
      setState(176);
      match(PrystParser::IDENTIFIER);
      setState(177);
      match(PrystParser::LPAREN);
      setState(179);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921506689318912) != 0)) {
        setState(178);
        paramList();
      }
      setState(181);
      match(PrystParser::RPAREN);
      setState(182);
      block();
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

PrystParser::BlockContext* PrystParser::LambdaFunctionContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
}

PrystParser::ParamListContext* PrystParser::LambdaFunctionContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
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
    setState(204);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(186);
      match(PrystParser::LPAREN);
      setState(188);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921506689318912) != 0)) {
        setState(187);
        paramList();
      }
      setState(190);
      match(PrystParser::RPAREN);
      setState(191);
      match(PrystParser::ARROW);
      setState(192);
      type(0);
      setState(193);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(195);
      match(PrystParser::LPAREN);
      setState(197);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921506689318912) != 0)) {
        setState(196);
        paramList();
      }
      setState(199);
      match(PrystParser::RPAREN);
      setState(200);
      match(PrystParser::ARROW);
      setState(201);
      type(0);
      setState(202);
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

//----------------- BlockContext ------------------------------------------------------------------

PrystParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::BlockContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::BlockContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::BlockContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::BlockContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
}


size_t PrystParser::BlockContext::getRuleIndex() const {
  return PrystParser::RuleBlock;
}


std::any PrystParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::BlockContext* PrystParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 20, PrystParser::RuleBlock);
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
    setState(206);
    match(PrystParser::LBRACE);
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8700972634872971238) != 0)) {
      setState(207);
      declaration();
      setState(212);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(213);
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

tree::TerminalNode* PrystParser::VariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::VariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
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
    setState(236);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(215);
      _la = _input->LA(1);
      if (!(_la == PrystParser::LET

      || _la == PrystParser::CONST)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(216);
      match(PrystParser::IDENTIFIER);
      setState(217);
      match(PrystParser::EQUAL);
      setState(218);
      expression();
      setState(219);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(225);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PrystParser::FN:
        case PrystParser::INT_TYPE:
        case PrystParser::FLOAT_TYPE:
        case PrystParser::BOOL_TYPE:
        case PrystParser::STR_TYPE:
        case PrystParser::VOID_TYPE:
        case PrystParser::IDENTIFIER: {
          setState(221);
          type(0);
          break;
        }

        case PrystParser::CONST: {
          setState(222);
          match(PrystParser::CONST);
          setState(223);
          type(0);
          break;
        }

        case PrystParser::CONST_EXPR: {
          setState(224);
          match(PrystParser::CONST_EXPR);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(227);
      match(PrystParser::IDENTIFIER);
      setState(228);
      match(PrystParser::EQUAL);
      setState(229);
      expression();
      setState(230);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(232);
      type(0);
      setState(233);
      match(PrystParser::IDENTIFIER);
      setState(234);
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

//----------------- ClassDeclContext ------------------------------------------------------------------

PrystParser::ClassDeclContext::ClassDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::ClassDeclContext::CLASS() {
  return getToken(PrystParser::CLASS, 0);
}

std::vector<tree::TerminalNode *> PrystParser::ClassDeclContext::IDENTIFIER() {
  return getTokens(PrystParser::IDENTIFIER);
}

tree::TerminalNode* PrystParser::ClassDeclContext::IDENTIFIER(size_t i) {
  return getToken(PrystParser::IDENTIFIER, i);
}

PrystParser::ClassBodyContext* PrystParser::ClassDeclContext::classBody() {
  return getRuleContext<PrystParser::ClassBodyContext>(0);
}

tree::TerminalNode* PrystParser::ClassDeclContext::EXTENDS() {
  return getToken(PrystParser::EXTENDS, 0);
}


size_t PrystParser::ClassDeclContext::getRuleIndex() const {
  return PrystParser::RuleClassDecl;
}


std::any PrystParser::ClassDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassDecl(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ClassDeclContext* PrystParser::classDecl() {
  ClassDeclContext *_localctx = _tracker.createInstance<ClassDeclContext>(_ctx, getState());
  enterRule(_localctx, 24, PrystParser::RuleClassDecl);
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
    setState(238);
    match(PrystParser::CLASS);
    setState(239);
    match(PrystParser::IDENTIFIER);
    setState(242);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EXTENDS) {
      setState(240);
      match(PrystParser::EXTENDS);
      setState(241);
      match(PrystParser::IDENTIFIER);
    }
    setState(244);
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
    setState(246);
    match(PrystParser::LBRACE);
    setState(250);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1152921506694561792) != 0)) {
      setState(247);
      classMember();
      setState(252);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(253);
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

PrystParser::TypeContext* PrystParser::ClassMemberContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::ClassMemberContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::ClassMemberContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::ClassMemberContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::ClassMemberContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

tree::TerminalNode* PrystParser::ClassMemberContext::LET() {
  return getToken(PrystParser::LET, 0);
}

tree::TerminalNode* PrystParser::ClassMemberContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

tree::TerminalNode* PrystParser::ClassMemberContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::ClassMemberContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::ClassMemberContext::ARROW() {
  return getToken(PrystParser::ARROW, 0);
}

PrystParser::BlockContext* PrystParser::ClassMemberContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
}

PrystParser::ParamListContext* PrystParser::ClassMemberContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}


size_t PrystParser::ClassMemberContext::getRuleIndex() const {
  return PrystParser::RuleClassMember;
}


std::any PrystParser::ClassMemberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassMember(this);
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
    setState(290);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(255);
      type(0);
      setState(256);
      match(PrystParser::IDENTIFIER);
      setState(257);
      match(PrystParser::EQUAL);
      setState(258);
      expression();
      setState(259);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(261);
      match(PrystParser::LET);
      setState(262);
      match(PrystParser::IDENTIFIER);
      setState(263);
      match(PrystParser::EQUAL);
      setState(264);
      expression();
      setState(265);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(267);
      match(PrystParser::CONST);
      setState(268);
      match(PrystParser::IDENTIFIER);
      setState(269);
      match(PrystParser::EQUAL);
      setState(270);
      expression();
      setState(271);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(273);
      match(PrystParser::CONST);
      setState(274);
      type(0);
      setState(275);
      match(PrystParser::IDENTIFIER);
      setState(276);
      match(PrystParser::EQUAL);
      setState(277);
      expression();
      setState(278);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(280);
      match(PrystParser::IDENTIFIER);
      setState(281);
      match(PrystParser::LPAREN);
      setState(283);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921506689318912) != 0)) {
        setState(282);
        paramList();
      }
      setState(285);
      match(PrystParser::RPAREN);
      setState(286);
      match(PrystParser::ARROW);
      setState(287);
      type(0);
      setState(288);
      block();
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
    setState(292);
    param();
    setState(297);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(293);
      match(PrystParser::COMMA);
      setState(294);
      param();
      setState(299);
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
    setState(314);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(300);
      type(0);
      setState(301);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(303);
      match(PrystParser::FN);
      setState(304);
      match(PrystParser::LESS);
      setState(305);
      type(0);
      setState(306);
      match(PrystParser::GREATER);
      setState(307);
      match(PrystParser::LPAREN);
      setState(309);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921506689318912) != 0)) {
        setState(308);
        paramTypeList();
      }
      setState(311);
      match(PrystParser::RPAREN);
      setState(312);
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
    setState(316);
    type(0);
    setState(321);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(317);
      match(PrystParser::COMMA);
      setState(318);
      type(0);
      setState(323);
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

tree::TerminalNode* PrystParser::TypeContext::INT_TYPE() {
  return getToken(PrystParser::INT_TYPE, 0);
}

tree::TerminalNode* PrystParser::TypeContext::FLOAT_TYPE() {
  return getToken(PrystParser::FLOAT_TYPE, 0);
}

tree::TerminalNode* PrystParser::TypeContext::BOOL_TYPE() {
  return getToken(PrystParser::BOOL_TYPE, 0);
}

tree::TerminalNode* PrystParser::TypeContext::STR_TYPE() {
  return getToken(PrystParser::STR_TYPE, 0);
}

tree::TerminalNode* PrystParser::TypeContext::VOID_TYPE() {
  return getToken(PrystParser::VOID_TYPE, 0);
}

tree::TerminalNode* PrystParser::TypeContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::TypeContext::FN() {
  return getToken(PrystParser::FN, 0);
}

tree::TerminalNode* PrystParser::TypeContext::LESS() {
  return getToken(PrystParser::LESS, 0);
}

PrystParser::TypeContext* PrystParser::TypeContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::TypeContext::GREATER() {
  return getToken(PrystParser::GREATER, 0);
}

tree::TerminalNode* PrystParser::TypeContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::TypeContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ParamTypeListContext* PrystParser::TypeContext::paramTypeList() {
  return getRuleContext<PrystParser::ParamTypeListContext>(0);
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
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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
    setState(341);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::INT_TYPE: {
        setState(325);
        match(PrystParser::INT_TYPE);
        break;
      }

      case PrystParser::FLOAT_TYPE: {
        setState(326);
        match(PrystParser::FLOAT_TYPE);
        break;
      }

      case PrystParser::BOOL_TYPE: {
        setState(327);
        match(PrystParser::BOOL_TYPE);
        break;
      }

      case PrystParser::STR_TYPE: {
        setState(328);
        match(PrystParser::STR_TYPE);
        break;
      }

      case PrystParser::VOID_TYPE: {
        setState(329);
        match(PrystParser::VOID_TYPE);
        break;
      }

      case PrystParser::IDENTIFIER: {
        setState(330);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::FN: {
        setState(331);
        match(PrystParser::FN);
        setState(332);
        match(PrystParser::LESS);
        setState(333);
        type(0);
        setState(334);
        match(PrystParser::GREATER);
        setState(335);
        match(PrystParser::LPAREN);
        setState(337);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1152921506689318912) != 0)) {
          setState(336);
          paramTypeList();
        }
        setState(339);
        match(PrystParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(348);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(343);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(344);
        match(PrystParser::LBRACKET);
        setState(345);
        match(PrystParser::RBRACKET); 
      }
      setState(350);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
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

std::vector<PrystParser::ExpressionContext *> PrystParser::StatementContext::expression() {
  return getRuleContexts<PrystParser::ExpressionContext>();
}

PrystParser::ExpressionContext* PrystParser::StatementContext::expression(size_t i) {
  return getRuleContext<PrystParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::StatementContext::SEMICOLON() {
  return getTokens(PrystParser::SEMICOLON);
}

tree::TerminalNode* PrystParser::StatementContext::SEMICOLON(size_t i) {
  return getToken(PrystParser::SEMICOLON, i);
}

tree::TerminalNode* PrystParser::StatementContext::IF() {
  return getToken(PrystParser::IF, 0);
}

tree::TerminalNode* PrystParser::StatementContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::StatementContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

std::vector<PrystParser::StatementContext *> PrystParser::StatementContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::StatementContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}

tree::TerminalNode* PrystParser::StatementContext::ELSE() {
  return getToken(PrystParser::ELSE, 0);
}

tree::TerminalNode* PrystParser::StatementContext::WHILE() {
  return getToken(PrystParser::WHILE, 0);
}

tree::TerminalNode* PrystParser::StatementContext::FOR() {
  return getToken(PrystParser::FOR, 0);
}

PrystParser::VariableDeclContext* PrystParser::StatementContext::variableDecl() {
  return getRuleContext<PrystParser::VariableDeclContext>(0);
}

tree::TerminalNode* PrystParser::StatementContext::RETURN() {
  return getToken(PrystParser::RETURN, 0);
}

PrystParser::BlockContext* PrystParser::StatementContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
}

PrystParser::TryCatchStmtContext* PrystParser::StatementContext::tryCatchStmt() {
  return getRuleContext<PrystParser::TryCatchStmtContext>(0);
}

tree::TerminalNode* PrystParser::StatementContext::PRINT() {
  return getToken(PrystParser::PRINT, 0);
}

std::vector<tree::TerminalNode *> PrystParser::StatementContext::COMMA() {
  return getTokens(PrystParser::COMMA);
}

tree::TerminalNode* PrystParser::StatementContext::COMMA(size_t i) {
  return getToken(PrystParser::COMMA, i);
}


size_t PrystParser::StatementContext::getRuleIndex() const {
  return PrystParser::RuleStatement;
}


std::any PrystParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
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
    setState(408);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::FALSE:
      case PrystParser::NULL_:
      case PrystParser::SUPER:
      case PrystParser::THIS:
      case PrystParser::TRUE:
      case PrystParser::NEW:
      case PrystParser::FN:
      case PrystParser::INT_TYPE:
      case PrystParser::FLOAT_TYPE:
      case PrystParser::BOOL_TYPE:
      case PrystParser::STR_TYPE:
      case PrystParser::VOID_TYPE:
      case PrystParser::LPAREN:
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT:
      case PrystParser::NUMBER:
      case PrystParser::IDENTIFIER:
      case PrystParser::STRING:
      case PrystParser::STRING_START: {
        enterOuterAlt(_localctx, 1);
        setState(351);
        expression();
        setState(352);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::IF: {
        enterOuterAlt(_localctx, 2);
        setState(354);
        match(PrystParser::IF);
        setState(355);
        match(PrystParser::LPAREN);
        setState(356);
        expression();
        setState(357);
        match(PrystParser::RPAREN);
        setState(358);
        statement();
        setState(361);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          setState(359);
          match(PrystParser::ELSE);
          setState(360);
          statement();
          break;
        }

        default:
          break;
        }
        break;
      }

      case PrystParser::WHILE: {
        enterOuterAlt(_localctx, 3);
        setState(363);
        match(PrystParser::WHILE);
        setState(364);
        match(PrystParser::LPAREN);
        setState(365);
        expression();
        setState(366);
        match(PrystParser::RPAREN);
        setState(367);
        statement();
        break;
      }

      case PrystParser::FOR: {
        enterOuterAlt(_localctx, 4);
        setState(369);
        match(PrystParser::FOR);
        setState(370);
        match(PrystParser::LPAREN);
        setState(376);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          setState(371);
          variableDecl();
          break;
        }

        case 2: {
          setState(372);
          expression();
          setState(373);
          match(PrystParser::SEMICOLON);
          break;
        }

        case 3: {
          setState(375);
          match(PrystParser::SEMICOLON);
          break;
        }

        default:
          break;
        }
        setState(379);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8700972626251636000) != 0)) {
          setState(378);
          expression();
        }
        setState(381);
        match(PrystParser::SEMICOLON);
        setState(383);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8700972626251636000) != 0)) {
          setState(382);
          expression();
        }
        setState(385);
        match(PrystParser::RPAREN);
        setState(386);
        statement();
        break;
      }

      case PrystParser::RETURN: {
        enterOuterAlt(_localctx, 5);
        setState(387);
        match(PrystParser::RETURN);
        setState(389);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8700972626251636000) != 0)) {
          setState(388);
          expression();
        }
        setState(391);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::LBRACE: {
        enterOuterAlt(_localctx, 6);
        setState(392);
        block();
        break;
      }

      case PrystParser::TRY: {
        enterOuterAlt(_localctx, 7);
        setState(393);
        tryCatchStmt();
        break;
      }

      case PrystParser::PRINT: {
        enterOuterAlt(_localctx, 8);
        setState(394);
        match(PrystParser::PRINT);
        setState(395);
        match(PrystParser::LPAREN);
        setState(404);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8700972626251636000) != 0)) {
          setState(396);
          expression();
          setState(401);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrystParser::COMMA) {
            setState(397);
            match(PrystParser::COMMA);
            setState(398);
            expression();
            setState(403);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(406);
        match(PrystParser::RPAREN);
        setState(407);
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
    setState(417);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(410);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(411);
      lambdaFunction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(412);
      typeCastExpr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(413);
      typeConversionExpr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(414);
      classConversionExpr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(415);
      stringLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(416);
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
    setState(419);
    match(PrystParser::STRING_START);
    setState(423);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7) != 0)) {
      setState(420);
      stringPart();
      setState(425);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(426);
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

tree::TerminalNode* PrystParser::StringPartContext::INTERP_END() {
  return getToken(PrystParser::INTERP_END, 0);
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
    setState(434);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::STRING_CONTENT: {
        enterOuterAlt(_localctx, 1);
        setState(428);
        match(PrystParser::STRING_CONTENT);
        break;
      }

      case PrystParser::ESCAPE_SEQ: {
        enterOuterAlt(_localctx, 2);
        setState(429);
        match(PrystParser::ESCAPE_SEQ);
        break;
      }

      case PrystParser::INTERP_START: {
        enterOuterAlt(_localctx, 3);
        setState(430);
        match(PrystParser::INTERP_START);
        setState(431);
        expression();
        setState(432);
        match(PrystParser::INTERP_END);
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
    setState(439);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      setState(436);
      call();
      setState(437);
      match(PrystParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(441);
    qualifiedIdentifier();
    setState(442);
    match(PrystParser::EQUAL);
    setState(443);
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
    setState(445);
    logicAnd();
    setState(450);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::OR) {
      setState(446);
      match(PrystParser::OR);
      setState(447);
      logicAnd();
      setState(452);
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
    setState(453);
    equality();
    setState(458);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::AND) {
      setState(454);
      match(PrystParser::AND);
      setState(455);
      equality();
      setState(460);
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
    setState(461);
    comparison();
    setState(466);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::NOT_EQUAL

    || _la == PrystParser::EQUAL_EQUAL) {
      setState(462);
      _la = _input->LA(1);
      if (!(_la == PrystParser::NOT_EQUAL

      || _la == PrystParser::EQUAL_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(463);
      comparison();
      setState(468);
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
    setState(469);
    addition();
    setState(474);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3588805953060864) != 0)) {
      setState(470);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3588805953060864) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(471);
      addition();
      setState(476);
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
    setState(477);
    multiplication();
    setState(482);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(478);
        _la = _input->LA(1);
        if (!(_la == PrystParser::MINUS

        || _la == PrystParser::PLUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(479);
        multiplication(); 
      }
      setState(484);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx);
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
    setState(485);
    unary();
    setState(490);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72070788177461248) != 0)) {
      setState(486);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 72070788177461248) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(487);
      unary();
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
    setState(496);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT: {
        enterOuterAlt(_localctx, 1);
        setState(493);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 54061337470304256) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(494);
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
      case PrystParser::IDENTIFIER:
      case PrystParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(495);
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
    setState(498);
    primary();
    setState(504);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(502);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PrystParser::LPAREN:
          case PrystParser::DOT: {
            setState(499);
            suffix();
            break;
          }

          case PrystParser::INCREMENT: {
            setState(500);
            match(PrystParser::INCREMENT);
            break;
          }

          case PrystParser::DECREMENT: {
            setState(501);
            match(PrystParser::DECREMENT);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(506);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
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
    setState(509);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(507);
        callSuffix();
        break;
      }

      case PrystParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(508);
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
    setState(511);
    match(PrystParser::LPAREN);
    setState(513);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8700972626251636000) != 0)) {
      setState(512);
      arguments();
    }
    setState(515);
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
    setState(526);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(517);
      match(PrystParser::DOT);
      setState(518);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(519);
      match(PrystParser::DOT);
      setState(520);
      match(PrystParser::IDENTIFIER);
      setState(521);
      match(PrystParser::LPAREN);
      setState(523);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8700972626251636000) != 0)) {
        setState(522);
        arguments();
      }
      setState(525);
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
    setState(528);
    qualifiedIdentifier();
    setState(533);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(529);
        match(PrystParser::DOT);
        setState(530);
        match(PrystParser::IDENTIFIER); 
      }
      setState(535);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
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

PrystParser::NewExprContext* PrystParser::PrimaryContext::newExpr() {
  return getRuleContext<PrystParser::NewExprContext>(0);
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
    setState(558);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(536);
        match(PrystParser::TRUE);
        break;
      }

      case PrystParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(537);
        match(PrystParser::FALSE);
        break;
      }

      case PrystParser::NULL_: {
        enterOuterAlt(_localctx, 3);
        setState(538);
        match(PrystParser::NULL_);
        break;
      }

      case PrystParser::THIS: {
        enterOuterAlt(_localctx, 4);
        setState(539);
        match(PrystParser::THIS);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(540);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::STRING: {
        enterOuterAlt(_localctx, 6);
        setState(541);
        match(PrystParser::STRING);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 7);
        setState(542);
        qualifiedIdentifier();
        setState(548);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
        case 1: {
          setState(543);
          match(PrystParser::LPAREN);
          setState(545);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8700972626251636000) != 0)) {
            setState(544);
            arguments();
          }
          setState(547);
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
        setState(550);
        match(PrystParser::LPAREN);
        setState(551);
        expression();
        setState(552);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::SUPER: {
        enterOuterAlt(_localctx, 9);
        setState(554);
        match(PrystParser::SUPER);
        setState(555);
        match(PrystParser::DOT);
        setState(556);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::NEW: {
        enterOuterAlt(_localctx, 10);
        setState(557);
        newExpr();
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
    setState(560);
    match(PrystParser::IDENTIFIER);
    setState(565);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::DOUBLE_COLON) {
      setState(561);
      match(PrystParser::DOUBLE_COLON);
      setState(562);
      match(PrystParser::IDENTIFIER);
      setState(567);
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

//----------------- NewExprContext ------------------------------------------------------------------

PrystParser::NewExprContext::NewExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::NewExprContext::NEW() {
  return getToken(PrystParser::NEW, 0);
}

tree::TerminalNode* PrystParser::NewExprContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::NewExprContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::NewExprContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

PrystParser::ArgumentsContext* PrystParser::NewExprContext::arguments() {
  return getRuleContext<PrystParser::ArgumentsContext>(0);
}


size_t PrystParser::NewExprContext::getRuleIndex() const {
  return PrystParser::RuleNewExpr;
}


std::any PrystParser::NewExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitNewExpr(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::NewExprContext* PrystParser::newExpr() {
  NewExprContext *_localctx = _tracker.createInstance<NewExprContext>(_ctx, getState());
  enterRule(_localctx, 76, PrystParser::RuleNewExpr);
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
    setState(568);
    match(PrystParser::NEW);
    setState(569);
    match(PrystParser::IDENTIFIER);
    setState(570);
    match(PrystParser::LPAREN);
    setState(572);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8700972626251636000) != 0)) {
      setState(571);
      arguments();
    }
    setState(574);
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
    setState(576);
    expression();
    setState(581);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(577);
      match(PrystParser::COMMA);
      setState(578);
      expression();
      setState(583);
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
    setState(594);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(584);
        match(PrystParser::LPAREN);
        setState(585);
        type(0);
        setState(586);
        match(PrystParser::RPAREN);
        setState(587);
        expression();
        break;
      }

      case PrystParser::FN:
      case PrystParser::INT_TYPE:
      case PrystParser::FLOAT_TYPE:
      case PrystParser::BOOL_TYPE:
      case PrystParser::STR_TYPE:
      case PrystParser::VOID_TYPE:
      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(589);
        type(0);
        setState(590);
        match(PrystParser::LPAREN);
        setState(591);
        expression();
        setState(592);
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
    setState(596);
    type(0);
    setState(597);
    match(PrystParser::DOT);
    setState(598);
    match(PrystParser::CONVERT);
    setState(599);
    match(PrystParser::LPAREN);
    setState(600);
    expression();
    setState(601);
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
    setState(603);
    match(PrystParser::IDENTIFIER);
    setState(604);
    match(PrystParser::DOT);
    setState(605);
    match(PrystParser::CONVERT);
    setState(606);
    match(PrystParser::LPAREN);
    setState(607);
    expression();
    setState(608);
    match(PrystParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TryCatchStmtContext ------------------------------------------------------------------

PrystParser::TryCatchStmtContext::TryCatchStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PrystParser::TryCatchStmtContext::TRY() {
  return getToken(PrystParser::TRY, 0);
}

std::vector<PrystParser::StatementContext *> PrystParser::TryCatchStmtContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::TryCatchStmtContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}

tree::TerminalNode* PrystParser::TryCatchStmtContext::CATCH() {
  return getToken(PrystParser::CATCH, 0);
}

tree::TerminalNode* PrystParser::TryCatchStmtContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::TryCatchStmtContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::TryCatchStmtContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}


size_t PrystParser::TryCatchStmtContext::getRuleIndex() const {
  return PrystParser::RuleTryCatchStmt;
}


std::any PrystParser::TryCatchStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitTryCatchStmt(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::TryCatchStmtContext* PrystParser::tryCatchStmt() {
  TryCatchStmtContext *_localctx = _tracker.createInstance<TryCatchStmtContext>(_ctx, getState());
  enterRule(_localctx, 86, PrystParser::RuleTryCatchStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(610);
    match(PrystParser::TRY);
    setState(611);
    statement();
    setState(617);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      setState(612);
      match(PrystParser::CATCH);
      setState(613);
      match(PrystParser::LPAREN);
      setState(614);
      match(PrystParser::IDENTIFIER);
      setState(615);
      match(PrystParser::RPAREN);
      setState(616);
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
  prystparserParserInitialize();
#else
  ::antlr4::internal::call_once(prystparserParserOnceFlag, prystparserParserInitialize);
#endif
}
