
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
  	4,1,67,713,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	3,11,301,8,11,1,12,1,12,1,12,1,12,3,12,307,8,12,1,12,1,12,1,13,1,13,5,
  	13,313,8,13,10,13,12,13,316,9,13,1,13,1,13,1,14,1,14,1,14,1,14,3,14,324,
  	8,14,1,14,1,14,1,14,1,14,1,14,3,14,331,8,14,1,14,1,14,1,14,1,14,1,14,
  	3,14,338,8,14,1,15,1,15,1,15,5,15,343,8,15,10,15,12,15,346,9,15,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,357,8,16,1,16,1,16,1,16,
  	3,16,362,8,16,1,17,1,17,1,17,5,17,367,8,17,10,17,12,17,370,9,17,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,385,
  	8,18,1,18,1,18,1,18,1,18,3,18,391,8,18,1,18,1,18,1,18,1,18,3,18,397,8,
  	18,3,18,399,8,18,1,18,1,18,1,18,5,18,404,8,18,10,18,12,18,407,9,18,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,419,8,19,1,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,434,8,
  	19,1,19,3,19,437,8,19,1,19,1,19,3,19,441,8,19,1,19,1,19,1,19,1,19,3,19,
  	447,8,19,1,19,1,19,1,19,5,19,452,8,19,10,19,12,19,455,9,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	5,19,473,8,19,10,19,12,19,476,9,19,1,19,1,19,1,19,5,19,481,8,19,10,19,
  	12,19,484,9,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,5,19,494,8,19,
  	10,19,12,19,497,9,19,1,19,1,19,5,19,501,8,19,10,19,12,19,504,9,19,3,19,
  	506,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,515,8,20,1,21,1,21,5,
  	21,519,8,21,10,21,12,21,522,9,21,1,21,1,21,1,21,3,21,527,8,21,1,21,3,
  	21,530,8,21,1,22,1,22,1,22,1,22,1,22,1,22,3,22,538,8,22,1,23,1,23,1,23,
  	3,23,543,8,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,5,24,552,8,24,10,24,
  	12,24,555,9,24,1,25,1,25,1,25,5,25,560,8,25,10,25,12,25,563,9,25,1,26,
  	1,26,1,26,5,26,568,8,26,10,26,12,26,571,9,26,1,27,1,27,1,27,5,27,576,
  	8,27,10,27,12,27,579,9,27,1,28,1,28,1,28,5,28,584,8,28,10,28,12,28,587,
  	9,28,1,29,1,29,1,29,5,29,592,8,29,10,29,12,29,595,9,29,1,30,1,30,1,30,
  	3,30,600,8,30,1,31,1,31,1,31,1,31,5,31,606,8,31,10,31,12,31,609,9,31,
  	1,32,1,32,3,32,613,8,32,1,33,1,33,3,33,617,8,33,1,33,1,33,1,34,1,34,1,
  	34,1,34,1,34,1,34,3,34,627,8,34,1,34,3,34,630,8,34,1,35,1,35,1,35,5,35,
  	635,8,35,10,35,12,35,638,9,35,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,
  	3,36,648,8,36,1,36,3,36,651,8,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,
  	36,3,36,661,8,36,1,37,1,37,1,37,5,37,666,8,37,10,37,12,37,669,9,37,1,
  	38,1,38,1,38,1,38,3,38,675,8,38,1,38,1,38,1,39,1,39,1,39,5,39,682,8,39,
  	10,39,12,39,685,9,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,
  	3,40,697,8,40,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,42,1,42,1,42,1,42,
  	1,42,1,42,1,42,1,42,0,1,36,43,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,
  	76,78,80,82,84,0,5,1,0,48,49,2,0,46,47,50,51,1,0,39,40,2,0,42,43,56,56,
  	3,0,39,39,44,44,54,55,790,0,92,1,0,0,0,2,102,1,0,0,0,4,137,1,0,0,0,6,
  	139,1,0,0,0,8,151,1,0,0,0,10,162,1,0,0,0,12,166,1,0,0,0,14,176,1,0,0,
  	0,16,216,1,0,0,0,18,247,1,0,0,0,20,249,1,0,0,0,22,300,1,0,0,0,24,302,
  	1,0,0,0,26,310,1,0,0,0,28,337,1,0,0,0,30,339,1,0,0,0,32,361,1,0,0,0,34,
  	363,1,0,0,0,36,398,1,0,0,0,38,505,1,0,0,0,40,514,1,0,0,0,42,529,1,0,0,
  	0,44,537,1,0,0,0,46,542,1,0,0,0,48,548,1,0,0,0,50,556,1,0,0,0,52,564,
  	1,0,0,0,54,572,1,0,0,0,56,580,1,0,0,0,58,588,1,0,0,0,60,599,1,0,0,0,62,
  	601,1,0,0,0,64,612,1,0,0,0,66,614,1,0,0,0,68,629,1,0,0,0,70,631,1,0,0,
  	0,72,660,1,0,0,0,74,662,1,0,0,0,76,670,1,0,0,0,78,678,1,0,0,0,80,696,
  	1,0,0,0,82,698,1,0,0,0,84,705,1,0,0,0,86,91,3,6,3,0,87,91,3,8,4,0,88,
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
  	1,0,0,0,176,175,1,0,0,0,177,15,1,0,0,0,178,179,5,21,0,0,179,180,5,47,
  	0,0,180,181,3,36,18,0,181,182,5,46,0,0,182,183,5,60,0,0,183,185,5,31,
  	0,0,184,186,3,30,15,0,185,184,1,0,0,0,185,186,1,0,0,0,186,187,1,0,0,0,
  	187,188,5,32,0,0,188,189,3,20,10,0,189,217,1,0,0,0,190,191,5,21,0,0,191,
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
  	256,257,5,34,0,0,257,21,1,0,0,0,258,259,5,20,0,0,259,260,5,60,0,0,260,
  	261,5,45,0,0,261,262,3,40,20,0,262,263,5,41,0,0,263,301,1,0,0,0,264,265,
  	3,36,18,0,265,266,5,60,0,0,266,267,5,45,0,0,267,268,3,40,20,0,268,269,
  	5,41,0,0,269,301,1,0,0,0,270,271,3,36,18,0,271,272,5,60,0,0,272,273,5,
  	41,0,0,273,301,1,0,0,0,274,275,5,22,0,0,275,276,5,60,0,0,276,277,5,45,
  	0,0,277,278,3,40,20,0,278,279,5,41,0,0,279,301,1,0,0,0,280,281,5,22,0,
  	0,281,282,3,36,18,0,282,283,5,60,0,0,283,284,5,45,0,0,284,285,3,40,20,
  	0,285,286,5,41,0,0,286,301,1,0,0,0,287,288,5,23,0,0,288,289,5,60,0,0,
  	289,290,5,45,0,0,290,291,3,40,20,0,291,292,5,41,0,0,292,301,1,0,0,0,293,
  	294,5,23,0,0,294,295,3,36,18,0,295,296,5,60,0,0,296,297,5,45,0,0,297,
  	298,3,40,20,0,298,299,5,41,0,0,299,301,1,0,0,0,300,258,1,0,0,0,300,264,
  	1,0,0,0,300,270,1,0,0,0,300,274,1,0,0,0,300,280,1,0,0,0,300,287,1,0,0,
  	0,300,293,1,0,0,0,301,23,1,0,0,0,302,303,5,2,0,0,303,306,5,60,0,0,304,
  	305,5,3,0,0,305,307,5,60,0,0,306,304,1,0,0,0,306,307,1,0,0,0,307,308,
  	1,0,0,0,308,309,3,26,13,0,309,25,1,0,0,0,310,314,5,33,0,0,311,313,3,28,
  	14,0,312,311,1,0,0,0,313,316,1,0,0,0,314,312,1,0,0,0,314,315,1,0,0,0,
  	315,317,1,0,0,0,316,314,1,0,0,0,317,318,5,34,0,0,318,27,1,0,0,0,319,320,
  	3,36,18,0,320,323,5,60,0,0,321,322,5,45,0,0,322,324,3,40,20,0,323,321,
  	1,0,0,0,323,324,1,0,0,0,324,325,1,0,0,0,325,326,5,41,0,0,326,338,1,0,
  	0,0,327,328,5,60,0,0,328,330,5,31,0,0,329,331,3,30,15,0,330,329,1,0,0,
  	0,330,331,1,0,0,0,331,332,1,0,0,0,332,333,5,32,0,0,333,334,5,57,0,0,334,
  	335,3,36,18,0,335,336,3,20,10,0,336,338,1,0,0,0,337,319,1,0,0,0,337,327,
  	1,0,0,0,338,29,1,0,0,0,339,344,3,32,16,0,340,341,5,37,0,0,341,343,3,32,
  	16,0,342,340,1,0,0,0,343,346,1,0,0,0,344,342,1,0,0,0,344,345,1,0,0,0,
  	345,31,1,0,0,0,346,344,1,0,0,0,347,348,3,36,18,0,348,349,5,60,0,0,349,
  	362,1,0,0,0,350,351,5,21,0,0,351,352,5,47,0,0,352,353,3,36,18,0,353,354,
  	5,46,0,0,354,356,5,31,0,0,355,357,3,34,17,0,356,355,1,0,0,0,356,357,1,
  	0,0,0,357,358,1,0,0,0,358,359,5,32,0,0,359,360,5,60,0,0,360,362,1,0,0,
  	0,361,347,1,0,0,0,361,350,1,0,0,0,362,33,1,0,0,0,363,368,3,36,18,0,364,
  	365,5,37,0,0,365,367,3,36,18,0,366,364,1,0,0,0,367,370,1,0,0,0,368,366,
  	1,0,0,0,368,369,1,0,0,0,369,35,1,0,0,0,370,368,1,0,0,0,371,372,6,18,-1,
  	0,372,399,5,26,0,0,373,399,5,27,0,0,374,399,5,28,0,0,375,399,5,29,0,0,
  	376,399,5,30,0,0,377,399,5,60,0,0,378,379,5,21,0,0,379,380,5,47,0,0,380,
  	381,3,36,18,0,381,382,5,46,0,0,382,384,5,31,0,0,383,385,3,34,17,0,384,
  	383,1,0,0,0,384,385,1,0,0,0,385,386,1,0,0,0,386,387,5,32,0,0,387,399,
  	1,0,0,0,388,390,5,31,0,0,389,391,3,34,17,0,390,389,1,0,0,0,390,391,1,
  	0,0,0,391,392,1,0,0,0,392,393,5,32,0,0,393,396,5,57,0,0,394,397,3,36,
  	18,0,395,397,5,30,0,0,396,394,1,0,0,0,396,395,1,0,0,0,397,399,1,0,0,0,
  	398,371,1,0,0,0,398,373,1,0,0,0,398,374,1,0,0,0,398,375,1,0,0,0,398,376,
  	1,0,0,0,398,377,1,0,0,0,398,378,1,0,0,0,398,388,1,0,0,0,399,405,1,0,0,
  	0,400,401,10,3,0,0,401,402,5,35,0,0,402,404,5,36,0,0,403,400,1,0,0,0,
  	404,407,1,0,0,0,405,403,1,0,0,0,405,406,1,0,0,0,406,37,1,0,0,0,407,405,
  	1,0,0,0,408,409,3,40,20,0,409,410,5,41,0,0,410,506,1,0,0,0,411,412,5,
  	7,0,0,412,413,5,31,0,0,413,414,3,40,20,0,414,415,5,32,0,0,415,418,3,38,
  	19,0,416,417,5,4,0,0,417,419,3,38,19,0,418,416,1,0,0,0,418,419,1,0,0,
  	0,419,506,1,0,0,0,420,421,5,13,0,0,421,422,5,31,0,0,422,423,3,40,20,0,
  	423,424,5,32,0,0,424,425,3,38,19,0,425,506,1,0,0,0,426,427,5,6,0,0,427,
  	433,5,31,0,0,428,434,3,22,11,0,429,430,3,40,20,0,430,431,5,41,0,0,431,
  	434,1,0,0,0,432,434,5,41,0,0,433,428,1,0,0,0,433,429,1,0,0,0,433,432,
  	1,0,0,0,434,436,1,0,0,0,435,437,3,40,20,0,436,435,1,0,0,0,436,437,1,0,
  	0,0,437,438,1,0,0,0,438,440,5,41,0,0,439,441,3,40,20,0,440,439,1,0,0,
  	0,440,441,1,0,0,0,441,442,1,0,0,0,442,443,5,32,0,0,443,506,3,38,19,0,
  	444,446,5,9,0,0,445,447,3,40,20,0,446,445,1,0,0,0,446,447,1,0,0,0,447,
  	448,1,0,0,0,448,506,5,41,0,0,449,453,5,33,0,0,450,452,3,38,19,0,451,450,
  	1,0,0,0,452,455,1,0,0,0,453,451,1,0,0,0,453,454,1,0,0,0,454,456,1,0,0,
  	0,455,453,1,0,0,0,456,506,5,34,0,0,457,458,5,1,0,0,458,459,5,31,0,0,459,
  	460,3,40,20,0,460,461,5,32,0,0,461,462,5,41,0,0,462,506,1,0,0,0,463,464,
  	5,24,0,0,464,474,3,38,19,0,465,466,5,25,0,0,466,467,5,31,0,0,467,468,
  	3,36,18,0,468,469,5,60,0,0,469,470,5,32,0,0,470,471,3,38,19,0,471,473,
  	1,0,0,0,472,465,1,0,0,0,473,476,1,0,0,0,474,472,1,0,0,0,474,475,1,0,0,
  	0,475,506,1,0,0,0,476,474,1,0,0,0,477,478,5,24,0,0,478,482,5,33,0,0,479,
  	481,3,38,19,0,480,479,1,0,0,0,481,484,1,0,0,0,482,480,1,0,0,0,482,483,
  	1,0,0,0,483,485,1,0,0,0,484,482,1,0,0,0,485,502,5,34,0,0,486,487,5,25,
  	0,0,487,488,5,31,0,0,488,489,3,36,18,0,489,490,5,60,0,0,490,491,5,32,
  	0,0,491,495,5,33,0,0,492,494,3,38,19,0,493,492,1,0,0,0,494,497,1,0,0,
  	0,495,493,1,0,0,0,495,496,1,0,0,0,496,498,1,0,0,0,497,495,1,0,0,0,498,
  	499,5,34,0,0,499,501,1,0,0,0,500,486,1,0,0,0,501,504,1,0,0,0,502,500,
  	1,0,0,0,502,503,1,0,0,0,503,506,1,0,0,0,504,502,1,0,0,0,505,408,1,0,0,
  	0,505,411,1,0,0,0,505,420,1,0,0,0,505,426,1,0,0,0,505,444,1,0,0,0,505,
  	449,1,0,0,0,505,457,1,0,0,0,505,463,1,0,0,0,505,477,1,0,0,0,506,39,1,
  	0,0,0,507,515,3,46,23,0,508,515,3,18,9,0,509,515,3,80,40,0,510,515,3,
  	82,41,0,511,515,3,84,42,0,512,515,3,42,21,0,513,515,3,48,24,0,514,507,
  	1,0,0,0,514,508,1,0,0,0,514,509,1,0,0,0,514,510,1,0,0,0,514,511,1,0,0,
  	0,514,512,1,0,0,0,514,513,1,0,0,0,515,41,1,0,0,0,516,520,5,61,0,0,517,
  	519,3,44,22,0,518,517,1,0,0,0,519,522,1,0,0,0,520,518,1,0,0,0,520,521,
  	1,0,0,0,521,523,1,0,0,0,522,520,1,0,0,0,523,530,5,67,0,0,524,526,5,61,
  	0,0,525,527,5,64,0,0,526,525,1,0,0,0,526,527,1,0,0,0,527,528,1,0,0,0,
  	528,530,5,67,0,0,529,516,1,0,0,0,529,524,1,0,0,0,530,43,1,0,0,0,531,538,
  	5,64,0,0,532,538,5,65,0,0,533,534,5,66,0,0,534,535,3,40,20,0,535,536,
  	5,34,0,0,536,538,1,0,0,0,537,531,1,0,0,0,537,532,1,0,0,0,537,533,1,0,
  	0,0,538,45,1,0,0,0,539,540,3,70,35,0,540,541,5,38,0,0,541,543,1,0,0,0,
  	542,539,1,0,0,0,542,543,1,0,0,0,543,544,1,0,0,0,544,545,3,74,37,0,545,
  	546,5,45,0,0,546,547,3,40,20,0,547,47,1,0,0,0,548,553,3,50,25,0,549,550,
  	5,53,0,0,550,552,3,50,25,0,551,549,1,0,0,0,552,555,1,0,0,0,553,551,1,
  	0,0,0,553,554,1,0,0,0,554,49,1,0,0,0,555,553,1,0,0,0,556,561,3,52,26,
  	0,557,558,5,52,0,0,558,560,3,52,26,0,559,557,1,0,0,0,560,563,1,0,0,0,
  	561,559,1,0,0,0,561,562,1,0,0,0,562,51,1,0,0,0,563,561,1,0,0,0,564,569,
  	3,54,27,0,565,566,7,0,0,0,566,568,3,54,27,0,567,565,1,0,0,0,568,571,1,
  	0,0,0,569,567,1,0,0,0,569,570,1,0,0,0,570,53,1,0,0,0,571,569,1,0,0,0,
  	572,577,3,56,28,0,573,574,7,1,0,0,574,576,3,56,28,0,575,573,1,0,0,0,576,
  	579,1,0,0,0,577,575,1,0,0,0,577,578,1,0,0,0,578,55,1,0,0,0,579,577,1,
  	0,0,0,580,585,3,58,29,0,581,582,7,2,0,0,582,584,3,58,29,0,583,581,1,0,
  	0,0,584,587,1,0,0,0,585,583,1,0,0,0,585,586,1,0,0,0,586,57,1,0,0,0,587,
  	585,1,0,0,0,588,593,3,60,30,0,589,590,7,3,0,0,590,592,3,60,30,0,591,589,
  	1,0,0,0,592,595,1,0,0,0,593,591,1,0,0,0,593,594,1,0,0,0,594,59,1,0,0,
  	0,595,593,1,0,0,0,596,597,7,4,0,0,597,600,3,60,30,0,598,600,3,62,31,0,
  	599,596,1,0,0,0,599,598,1,0,0,0,600,61,1,0,0,0,601,607,3,72,36,0,602,
  	606,3,64,32,0,603,606,5,54,0,0,604,606,5,55,0,0,605,602,1,0,0,0,605,603,
  	1,0,0,0,605,604,1,0,0,0,606,609,1,0,0,0,607,605,1,0,0,0,607,608,1,0,0,
  	0,608,63,1,0,0,0,609,607,1,0,0,0,610,613,3,66,33,0,611,613,3,68,34,0,
  	612,610,1,0,0,0,612,611,1,0,0,0,613,65,1,0,0,0,614,616,5,31,0,0,615,617,
  	3,78,39,0,616,615,1,0,0,0,616,617,1,0,0,0,617,618,1,0,0,0,618,619,5,32,
  	0,0,619,67,1,0,0,0,620,621,5,38,0,0,621,630,5,60,0,0,622,623,5,38,0,0,
  	623,624,5,60,0,0,624,626,5,31,0,0,625,627,3,78,39,0,626,625,1,0,0,0,626,
  	627,1,0,0,0,627,628,1,0,0,0,628,630,5,32,0,0,629,620,1,0,0,0,629,622,
  	1,0,0,0,630,69,1,0,0,0,631,636,3,74,37,0,632,633,5,38,0,0,633,635,5,60,
  	0,0,634,632,1,0,0,0,635,638,1,0,0,0,636,634,1,0,0,0,636,637,1,0,0,0,637,
  	71,1,0,0,0,638,636,1,0,0,0,639,661,5,12,0,0,640,661,5,5,0,0,641,661,5,
  	8,0,0,642,661,5,11,0,0,643,661,5,59,0,0,644,650,3,74,37,0,645,647,5,31,
  	0,0,646,648,3,78,39,0,647,646,1,0,0,0,647,648,1,0,0,0,648,649,1,0,0,0,
  	649,651,5,32,0,0,650,645,1,0,0,0,650,651,1,0,0,0,651,661,1,0,0,0,652,
  	653,5,31,0,0,653,654,3,40,20,0,654,655,5,32,0,0,655,661,1,0,0,0,656,657,
  	5,10,0,0,657,658,5,38,0,0,658,661,5,60,0,0,659,661,3,76,38,0,660,639,
  	1,0,0,0,660,640,1,0,0,0,660,641,1,0,0,0,660,642,1,0,0,0,660,643,1,0,0,
  	0,660,644,1,0,0,0,660,652,1,0,0,0,660,656,1,0,0,0,660,659,1,0,0,0,661,
  	73,1,0,0,0,662,667,5,60,0,0,663,664,5,58,0,0,664,666,5,60,0,0,665,663,
  	1,0,0,0,666,669,1,0,0,0,667,665,1,0,0,0,667,668,1,0,0,0,668,75,1,0,0,
  	0,669,667,1,0,0,0,670,671,5,14,0,0,671,672,5,60,0,0,672,674,5,31,0,0,
  	673,675,3,78,39,0,674,673,1,0,0,0,674,675,1,0,0,0,675,676,1,0,0,0,676,
  	677,5,32,0,0,677,77,1,0,0,0,678,683,3,40,20,0,679,680,5,37,0,0,680,682,
  	3,40,20,0,681,679,1,0,0,0,682,685,1,0,0,0,683,681,1,0,0,0,683,684,1,0,
  	0,0,684,79,1,0,0,0,685,683,1,0,0,0,686,687,5,31,0,0,687,688,3,36,18,0,
  	688,689,5,32,0,0,689,690,3,40,20,0,690,697,1,0,0,0,691,692,3,36,18,0,
  	692,693,5,31,0,0,693,694,3,40,20,0,694,695,5,32,0,0,695,697,1,0,0,0,696,
  	686,1,0,0,0,696,691,1,0,0,0,697,81,1,0,0,0,698,699,3,36,18,0,699,700,
  	5,38,0,0,700,701,5,15,0,0,701,702,5,31,0,0,702,703,3,40,20,0,703,704,
  	5,32,0,0,704,83,1,0,0,0,705,706,5,60,0,0,706,707,5,38,0,0,707,708,5,15,
  	0,0,708,709,5,31,0,0,709,710,3,40,20,0,710,711,5,32,0,0,711,85,1,0,0,
  	0,79,90,92,102,108,120,132,137,144,146,157,171,176,185,194,200,202,207,
  	212,216,220,226,232,238,244,247,253,300,306,314,323,330,337,344,356,361,
  	368,384,390,396,398,405,418,433,436,440,446,453,474,482,495,502,505,514,
  	520,526,529,537,542,553,561,569,577,585,593,599,605,607,612,616,626,629,
  	636,647,650,660,667,674,683,696
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
      ((1ULL << _la) & 4089286616445583334) != 0)) {
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
        ((1ULL << _la) & 4089286616445124582) != 0)) {
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
        ((1ULL << _la) & 4089286616445124582) != 0)) {
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
      ((1ULL << _la) & 4089286616445255654) != 0)) {
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
      ((1ULL << _la) & 4089286616445124582) != 0)) {
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
        ((1ULL << _la) & 1152921508836802560) != 0)) {
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
        ((1ULL << _la) & 1152921508836802560) != 0)) {
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
        ((1ULL << _la) & 1152921508836802560) != 0)) {
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
        ((1ULL << _la) & 1152921508836802560) != 0)) {
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
        ((1ULL << _la) & 4089286616445124582) != 0)) {
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
        ((1ULL << _la) & 1152921508836802560) != 0)) {
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
      ((1ULL << _la) & 4089286616430968802) != 0)) {
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


size_t PrystParser::VariableDeclContext::getRuleIndex() const {
  return PrystParser::RuleVariableDecl;
}

void PrystParser::VariableDeclContext::copyFrom(VariableDeclContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ClassTypedVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassTypedVariableDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
}

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

PrystParser::ClassTypedVariableDeclContext::ClassTypedVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassTypedVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassTypedVariableDecl(this);
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

tree::TerminalNode* PrystParser::TypedVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::TypedVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::TypedVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
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

tree::TerminalNode* PrystParser::InferredVariableDeclContext::EQUAL() {
  return getToken(PrystParser::EQUAL, 0);
}

PrystParser::ExpressionContext* PrystParser::InferredVariableDeclContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::InferredVariableDeclContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
}

PrystParser::InferredVariableDeclContext::InferredVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::InferredVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitInferredVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassConstTypedDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassConstTypedDeclContext::CONST_EXPR() {
  return getToken(PrystParser::CONST_EXPR, 0);
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

PrystParser::ClassConstTypedDeclContext::ClassConstTypedDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassConstTypedDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassConstTypedDecl(this);
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
//----------------- ClassInferredVariableDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassInferredVariableDeclContext::CONST() {
  return getToken(PrystParser::CONST, 0);
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

PrystParser::ClassInferredVariableDeclContext::ClassInferredVariableDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassInferredVariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassInferredVariableDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassConstInferredDeclContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::ClassConstInferredDeclContext::CONST_EXPR() {
  return getToken(PrystParser::CONST_EXPR, 0);
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

PrystParser::ClassConstInferredDeclContext::ClassConstInferredDeclContext(VariableDeclContext *ctx) { copyFrom(ctx); }


std::any PrystParser::ClassConstInferredDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitClassConstInferredDecl(this);
  else
    return visitor->visitChildren(this);
}
PrystParser::VariableDeclContext* PrystParser::variableDecl() {
  VariableDeclContext *_localctx = _tracker.createInstance<VariableDeclContext>(_ctx, getState());
  enterRule(_localctx, 22, PrystParser::RuleVariableDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(300);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::InferredVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(258);
      match(PrystParser::LET);
      setState(259);
      match(PrystParser::IDENTIFIER);
      setState(260);
      match(PrystParser::EQUAL);
      setState(261);
      expression();
      setState(262);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::TypedVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(264);
      type(0);
      setState(265);
      match(PrystParser::IDENTIFIER);
      setState(266);
      match(PrystParser::EQUAL);
      setState(267);
      expression();
      setState(268);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrystParser::UninitializedVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(270);
      type(0);
      setState(271);
      match(PrystParser::IDENTIFIER);
      setState(272);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PrystParser::ClassInferredVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(274);
      match(PrystParser::CONST);
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
      _localctx = _tracker.createInstance<PrystParser::ClassTypedVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(280);
      match(PrystParser::CONST);
      setState(281);
      type(0);
      setState(282);
      match(PrystParser::IDENTIFIER);
      setState(283);
      match(PrystParser::EQUAL);
      setState(284);
      expression();
      setState(285);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PrystParser::ClassConstInferredDeclContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(287);
      match(PrystParser::CONST_EXPR);
      setState(288);
      match(PrystParser::IDENTIFIER);
      setState(289);
      match(PrystParser::EQUAL);
      setState(290);
      expression();
      setState(291);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<PrystParser::ClassConstTypedDeclContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(293);
      match(PrystParser::CONST_EXPR);
      setState(294);
      type(0);
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
    setState(302);
    match(PrystParser::CLASS);
    setState(303);
    match(PrystParser::IDENTIFIER);
    setState(306);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EXTENDS) {
      setState(304);
      match(PrystParser::EXTENDS);
      setState(305);
      match(PrystParser::IDENTIFIER);
    }
    setState(308);
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
    setState(310);
    match(PrystParser::LBRACE);
    setState(314);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1152921508836802560) != 0)) {
      setState(311);
      classMember();
      setState(316);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(317);
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
    setState(337);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::ClassVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(319);
      type(0);
      setState(320);
      match(PrystParser::IDENTIFIER);
      setState(323);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(321);
        match(PrystParser::EQUAL);
        setState(322);
        expression();
      }
      setState(325);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::ClassFunctionDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(327);
      match(PrystParser::IDENTIFIER);
      setState(328);
      match(PrystParser::LPAREN);
      setState(330);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(329);
        paramList();
      }
      setState(332);
      match(PrystParser::RPAREN);
      setState(333);
      match(PrystParser::ARROW);
      setState(334);
      type(0);
      setState(335);
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
    setState(339);
    param();
    setState(344);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(340);
      match(PrystParser::COMMA);
      setState(341);
      param();
      setState(346);
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
    setState(361);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(347);
      type(0);
      setState(348);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(350);
      match(PrystParser::FN);
      setState(351);
      match(PrystParser::LESS);
      setState(352);
      type(0);
      setState(353);
      match(PrystParser::GREATER);
      setState(354);
      match(PrystParser::LPAREN);
      setState(356);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1152921508836802560) != 0)) {
        setState(355);
        paramTypeList();
      }
      setState(358);
      match(PrystParser::RPAREN);
      setState(359);
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
    setState(363);
    type(0);
    setState(368);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(364);
      match(PrystParser::COMMA);
      setState(365);
      type(0);
      setState(370);
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
    setState(398);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::INT: {
        _localctx = _tracker.createInstance<IntTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(372);
        match(PrystParser::INT);
        break;
      }

      case PrystParser::FLOAT: {
        _localctx = _tracker.createInstance<FloatTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(373);
        match(PrystParser::FLOAT);
        break;
      }

      case PrystParser::BOOL: {
        _localctx = _tracker.createInstance<BoolTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(374);
        match(PrystParser::BOOL);
        break;
      }

      case PrystParser::STR: {
        _localctx = _tracker.createInstance<StrTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(375);
        match(PrystParser::STR);
        break;
      }

      case PrystParser::VOID: {
        _localctx = _tracker.createInstance<VoidTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(376);
        match(PrystParser::VOID);
        break;
      }

      case PrystParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<IdentifierTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(377);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::FN: {
        _localctx = _tracker.createInstance<FunctionTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(378);
        match(PrystParser::FN);
        setState(379);
        match(PrystParser::LESS);
        setState(380);
        type(0);
        setState(381);
        match(PrystParser::GREATER);
        setState(382);
        match(PrystParser::LPAREN);
        setState(384);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1152921508836802560) != 0)) {
          setState(383);
          paramTypeList();
        }
        setState(386);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::LPAREN: {
        _localctx = _tracker.createInstance<LambdaTypeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(388);
        match(PrystParser::LPAREN);
        setState(390);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1152921508836802560) != 0)) {
          setState(389);
          paramTypeList();
        }
        setState(392);
        match(PrystParser::RPAREN);
        setState(393);
        match(PrystParser::ARROW);
        setState(396);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
        case 1: {
          setState(394);
          type(0);
          break;
        }

        case 2: {
          setState(395);
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
    setState(405);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArrayTypeContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleType);
        setState(400);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(401);
        match(PrystParser::LBRACKET);
        setState(402);
        match(PrystParser::RBRACKET); 
      }
      setState(407);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
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
//----------------- TryStatementContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::TryStatementContext::TRY() {
  return getToken(PrystParser::TRY, 0);
}

std::vector<PrystParser::StatementContext *> PrystParser::TryStatementContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::TryStatementContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::TryStatementContext::CATCH() {
  return getTokens(PrystParser::CATCH);
}

tree::TerminalNode* PrystParser::TryStatementContext::CATCH(size_t i) {
  return getToken(PrystParser::CATCH, i);
}

std::vector<tree::TerminalNode *> PrystParser::TryStatementContext::LPAREN() {
  return getTokens(PrystParser::LPAREN);
}

tree::TerminalNode* PrystParser::TryStatementContext::LPAREN(size_t i) {
  return getToken(PrystParser::LPAREN, i);
}

std::vector<PrystParser::TypeContext *> PrystParser::TryStatementContext::type() {
  return getRuleContexts<PrystParser::TypeContext>();
}

PrystParser::TypeContext* PrystParser::TryStatementContext::type(size_t i) {
  return getRuleContext<PrystParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::TryStatementContext::IDENTIFIER() {
  return getTokens(PrystParser::IDENTIFIER);
}

tree::TerminalNode* PrystParser::TryStatementContext::IDENTIFIER(size_t i) {
  return getToken(PrystParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> PrystParser::TryStatementContext::RPAREN() {
  return getTokens(PrystParser::RPAREN);
}

tree::TerminalNode* PrystParser::TryStatementContext::RPAREN(size_t i) {
  return getToken(PrystParser::RPAREN, i);
}

PrystParser::TryStatementContext::TryStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any PrystParser::TryStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
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

std::vector<tree::TerminalNode *> PrystParser::TryCatchStatementContext::LBRACE() {
  return getTokens(PrystParser::LBRACE);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::LBRACE(size_t i) {
  return getToken(PrystParser::LBRACE, i);
}

std::vector<tree::TerminalNode *> PrystParser::TryCatchStatementContext::RBRACE() {
  return getTokens(PrystParser::RBRACE);
}

tree::TerminalNode* PrystParser::TryCatchStatementContext::RBRACE(size_t i) {
  return getToken(PrystParser::RBRACE, i);
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
    setState(505);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::ExprStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(408);
      expression();
      setState(409);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(411);
      match(PrystParser::IF);
      setState(412);
      match(PrystParser::LPAREN);
      setState(413);
      expression();
      setState(414);
      match(PrystParser::RPAREN);
      setState(415);
      statement();
      setState(418);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
      case 1: {
        setState(416);
        match(PrystParser::ELSE);
        setState(417);
        statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PrystParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(420);
      match(PrystParser::WHILE);
      setState(421);
      match(PrystParser::LPAREN);
      setState(422);
      expression();
      setState(423);
      match(PrystParser::RPAREN);
      setState(424);
      statement();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PrystParser::ForStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(426);
      match(PrystParser::FOR);
      setState(427);
      match(PrystParser::LPAREN);
      setState(433);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
      case 1: {
        setState(428);
        variableDecl();
        break;
      }

      case 2: {
        setState(429);
        expression();
        setState(430);
        match(PrystParser::SEMICOLON);
        break;
      }

      case 3: {
        setState(432);
        match(PrystParser::SEMICOLON);
        break;
      }

      default:
        break;
      }
      setState(436);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286607824248096) != 0)) {
        setState(435);
        expression();
      }
      setState(438);
      match(PrystParser::SEMICOLON);
      setState(440);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286607824248096) != 0)) {
        setState(439);
        expression();
      }
      setState(442);
      match(PrystParser::RPAREN);
      setState(443);
      statement();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PrystParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(444);
      match(PrystParser::RETURN);
      setState(446);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286607824248096) != 0)) {
        setState(445);
        expression();
      }
      setState(448);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PrystParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(449);
      match(PrystParser::LBRACE);
      setState(453);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286616430968802) != 0)) {
        setState(450);
        statement();
        setState(455);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(456);
      match(PrystParser::RBRACE);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<PrystParser::PrintStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(457);
      match(PrystParser::PRINT);
      setState(458);
      match(PrystParser::LPAREN);
      setState(459);
      expression();
      setState(460);
      match(PrystParser::RPAREN);
      setState(461);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<PrystParser::TryStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(463);
      match(PrystParser::TRY);
      setState(464);
      statement();
      setState(474);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(465);
          match(PrystParser::CATCH);
          setState(466);
          match(PrystParser::LPAREN);
          setState(467);
          type(0);
          setState(468);
          match(PrystParser::IDENTIFIER);
          setState(469);
          match(PrystParser::RPAREN);
          setState(470);
          statement(); 
        }
        setState(476);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      }
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<PrystParser::TryCatchStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(477);
      match(PrystParser::TRY);
      setState(478);
      match(PrystParser::LBRACE);
      setState(482);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286616430968802) != 0)) {
        setState(479);
        statement();
        setState(484);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(485);
      match(PrystParser::RBRACE);
      setState(502);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(486);
          match(PrystParser::CATCH);
          setState(487);
          match(PrystParser::LPAREN);
          setState(488);
          type(0);
          setState(489);
          match(PrystParser::IDENTIFIER);
          setState(490);
          match(PrystParser::RPAREN);
          setState(491);
          match(PrystParser::LBRACE);
          setState(495);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4089286616430968802) != 0)) {
            setState(492);
            statement();
            setState(497);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(498);
          match(PrystParser::RBRACE); 
        }
        setState(504);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      }
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
    setState(514);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
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
      stringLiteral();
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

tree::TerminalNode* PrystParser::SimpleStringContext::STRING_START() {
  return getToken(PrystParser::STRING_START, 0);
}

tree::TerminalNode* PrystParser::SimpleStringContext::STRING_END() {
  return getToken(PrystParser::STRING_END, 0);
}

tree::TerminalNode* PrystParser::SimpleStringContext::STRING_CONTENT() {
  return getToken(PrystParser::STRING_CONTENT, 0);
}

PrystParser::SimpleStringContext::SimpleStringContext(StringLiteralContext *ctx) { copyFrom(ctx); }


std::any PrystParser::SimpleStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitSimpleString(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InterpolatedStringContext ------------------------------------------------------------------

tree::TerminalNode* PrystParser::InterpolatedStringContext::STRING_START() {
  return getToken(PrystParser::STRING_START, 0);
}

tree::TerminalNode* PrystParser::InterpolatedStringContext::STRING_END() {
  return getToken(PrystParser::STRING_END, 0);
}

std::vector<PrystParser::StringPartContext *> PrystParser::InterpolatedStringContext::stringPart() {
  return getRuleContexts<PrystParser::StringPartContext>();
}

PrystParser::StringPartContext* PrystParser::InterpolatedStringContext::stringPart(size_t i) {
  return getRuleContext<PrystParser::StringPartContext>(i);
}

PrystParser::InterpolatedStringContext::InterpolatedStringContext(StringLiteralContext *ctx) { copyFrom(ctx); }


std::any PrystParser::InterpolatedStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystParserVisitor*>(visitor))
    return parserVisitor->visitInterpolatedString(this);
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
    setState(529);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::InterpolatedStringContext>(_localctx);
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
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::SimpleStringContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(524);
      match(PrystParser::STRING_START);
      setState(526);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::STRING_CONTENT) {
        setState(525);
        match(PrystParser::STRING_CONTENT);
      }
      setState(528);
      match(PrystParser::STRING_END);
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
    setState(537);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::STRING_CONTENT: {
        enterOuterAlt(_localctx, 1);
        setState(531);
        match(PrystParser::STRING_CONTENT);
        break;
      }

      case PrystParser::ESCAPE_SEQ: {
        enterOuterAlt(_localctx, 2);
        setState(532);
        match(PrystParser::ESCAPE_SEQ);
        break;
      }

      case PrystParser::INTERP_START: {
        enterOuterAlt(_localctx, 3);
        setState(533);
        match(PrystParser::INTERP_START);
        setState(534);
        expression();
        setState(535);
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
    setState(542);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      setState(539);
      call();
      setState(540);
      match(PrystParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(544);
    qualifiedIdentifier();
    setState(545);
    match(PrystParser::EQUAL);
    setState(546);
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
    setState(548);
    logicAnd();
    setState(553);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::OR) {
      setState(549);
      match(PrystParser::OR);
      setState(550);
      logicAnd();
      setState(555);
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
    setState(556);
    equality();
    setState(561);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::AND) {
      setState(557);
      match(PrystParser::AND);
      setState(558);
      equality();
      setState(563);
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
    setState(564);
    comparison();
    setState(569);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::NOT_EQUAL

    || _la == PrystParser::EQUAL_EQUAL) {
      setState(565);
      _la = _input->LA(1);
      if (!(_la == PrystParser::NOT_EQUAL

      || _la == PrystParser::EQUAL_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(566);
      comparison();
      setState(571);
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
    setState(572);
    addition();
    setState(577);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3588805953060864) != 0)) {
      setState(573);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3588805953060864) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(574);
      addition();
      setState(579);
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
    setState(580);
    multiplication();
    setState(585);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(581);
        _la = _input->LA(1);
        if (!(_la == PrystParser::MINUS

        || _la == PrystParser::PLUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(582);
        multiplication(); 
      }
      setState(587);
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
    setState(588);
    unary();
    setState(593);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72070788177461248) != 0)) {
      setState(589);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 72070788177461248) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(590);
      unary();
      setState(595);
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
    setState(599);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT: {
        enterOuterAlt(_localctx, 1);
        setState(596);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 54061337470304256) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(597);
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
        setState(598);
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
    setState(601);
    primary();
    setState(607);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(605);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PrystParser::LPAREN:
          case PrystParser::DOT: {
            setState(602);
            suffix();
            break;
          }

          case PrystParser::INCREMENT: {
            setState(603);
            match(PrystParser::INCREMENT);
            break;
          }

          case PrystParser::DECREMENT: {
            setState(604);
            match(PrystParser::DECREMENT);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(609);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
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
    setState(612);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(610);
        callSuffix();
        break;
      }

      case PrystParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(611);
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
    setState(614);
    match(PrystParser::LPAREN);
    setState(616);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286607824248096) != 0)) {
      setState(615);
      arguments();
    }
    setState(618);
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
    setState(629);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(620);
      match(PrystParser::DOT);
      setState(621);
      match(PrystParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(622);
      match(PrystParser::DOT);
      setState(623);
      match(PrystParser::IDENTIFIER);
      setState(624);
      match(PrystParser::LPAREN);
      setState(626);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4089286607824248096) != 0)) {
        setState(625);
        arguments();
      }
      setState(628);
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
    setState(631);
    qualifiedIdentifier();
    setState(636);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(632);
        match(PrystParser::DOT);
        setState(633);
        match(PrystParser::IDENTIFIER); 
      }
      setState(638);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
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
    setState(660);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(639);
        match(PrystParser::TRUE);
        break;
      }

      case PrystParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(640);
        match(PrystParser::FALSE);
        break;
      }

      case PrystParser::NULL_: {
        enterOuterAlt(_localctx, 3);
        setState(641);
        match(PrystParser::NULL_);
        break;
      }

      case PrystParser::THIS: {
        enterOuterAlt(_localctx, 4);
        setState(642);
        match(PrystParser::THIS);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(643);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 6);
        setState(644);
        qualifiedIdentifier();
        setState(650);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
        case 1: {
          setState(645);
          match(PrystParser::LPAREN);
          setState(647);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4089286607824248096) != 0)) {
            setState(646);
            arguments();
          }
          setState(649);
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
        setState(652);
        match(PrystParser::LPAREN);
        setState(653);
        expression();
        setState(654);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::SUPER: {
        enterOuterAlt(_localctx, 8);
        setState(656);
        match(PrystParser::SUPER);
        setState(657);
        match(PrystParser::DOT);
        setState(658);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::NEW: {
        enterOuterAlt(_localctx, 9);
        setState(659);
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
    setState(662);
    match(PrystParser::IDENTIFIER);
    setState(667);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::DOUBLE_COLON) {
      setState(663);
      match(PrystParser::DOUBLE_COLON);
      setState(664);
      match(PrystParser::IDENTIFIER);
      setState(669);
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
    setState(670);
    match(PrystParser::NEW);
    setState(671);
    match(PrystParser::IDENTIFIER);
    setState(672);
    match(PrystParser::LPAREN);
    setState(674);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4089286607824248096) != 0)) {
      setState(673);
      arguments();
    }
    setState(676);
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
    setState(678);
    expression();
    setState(683);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(679);
      match(PrystParser::COMMA);
      setState(680);
      expression();
      setState(685);
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
    setState(696);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(686);
      match(PrystParser::LPAREN);
      setState(687);
      type(0);
      setState(688);
      match(PrystParser::RPAREN);
      setState(689);
      expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(691);
      type(0);
      setState(692);
      match(PrystParser::LPAREN);
      setState(693);
      expression();
      setState(694);
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
    setState(698);
    type(0);
    setState(699);
    match(PrystParser::DOT);
    setState(700);
    match(PrystParser::CONVERT);
    setState(701);
    match(PrystParser::LPAREN);
    setState(702);
    expression();
    setState(703);
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
    setState(705);
    match(PrystParser::IDENTIFIER);
    setState(706);
    match(PrystParser::DOT);
    setState(707);
    match(PrystParser::CONVERT);
    setState(708);
    match(PrystParser::LPAREN);
    setState(709);
    expression();
    setState(710);
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
