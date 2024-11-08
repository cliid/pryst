
// Generated from PrystLexer.g4 by ANTLR 4.13.2


#include "PrystLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct PrystLexerStaticData final {
  PrystLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PrystLexerStaticData(const PrystLexerStaticData&) = delete;
  PrystLexerStaticData(PrystLexerStaticData&&) = delete;
  PrystLexerStaticData& operator=(const PrystLexerStaticData&) = delete;
  PrystLexerStaticData& operator=(PrystLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag prystlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<PrystLexerStaticData> prystlexerLexerStaticData = nullptr;

void prystlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (prystlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(prystlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<PrystLexerStaticData>(
    std::vector<std::string>{
      "PRINT", "CLASS", "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", 
      "RETURN", "SUPER", "THIS", "TRUE", "WHILE", "NEW", "CONVERT", "NAMESPACE", 
      "MODULE", "IMPORT", "USING", "LET", "FN", "CONST", "CONST_EXPR", "INT", 
      "FLOAT", "BOOL", "STR", "VOID", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "LBRACKET", "RBRACKET", "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", 
      "SLASH", "STAR", "BANG", "EQUAL", "GREATER", "LESS", "NOT_EQUAL", 
      "EQUAL_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", "AND", "OR", "INCREMENT", 
      "DECREMENT", "PERCENT", "ARROW", "DOUBLE_COLON", "NUMBER", "IDENTIFIER", 
      "STRING_START", "COMMENT", "WS", "STRING_CONTENT", "ESCAPE_SEQ", "INTERP_START", 
      "STRING_END"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "IN_STRING"
    },
    std::vector<std::string>{
      "", "'print'", "'class'", "'extends'", "'else'", "'false'", "'for'", 
      "'if'", "'null'", "'return'", "'super'", "'this'", "'true'", "'while'", 
      "'new'", "'convert'", "'namespace'", "'module'", "'import'", "'using'", 
      "'let'", "'fn'", "'const'", "'const!'", "'int'", "'float'", "'bool'", 
      "'str'", "'void'", "'('", "')'", "'{'", "'}'", "'['", "']'", "','", 
      "'.'", "'-'", "'+'", "';'", "'/'", "'*'", "'!'", "'='", "'>'", "'<'", 
      "'!='", "'=='", "'>='", "'<='", "'&&'", "'||'", "'++'", "'--'", "'%'", 
      "'->'", "'::'", "", "", "", "", "", "", "", "'${'"
    },
    std::vector<std::string>{
      "", "PRINT", "CLASS", "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", 
      "RETURN", "SUPER", "THIS", "TRUE", "WHILE", "NEW", "CONVERT", "NAMESPACE", 
      "MODULE", "IMPORT", "USING", "LET", "FN", "CONST", "CONST_EXPR", "INT", 
      "FLOAT", "BOOL", "STR", "VOID", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "LBRACKET", "RBRACKET", "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", 
      "SLASH", "STAR", "BANG", "EQUAL", "GREATER", "LESS", "NOT_EQUAL", 
      "EQUAL_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", "AND", "OR", "INCREMENT", 
      "DECREMENT", "PERCENT", "ARROW", "DOUBLE_COLON", "NUMBER", "IDENTIFIER", 
      "STRING_START", "COMMENT", "WS", "STRING_CONTENT", "ESCAPE_SEQ", "INTERP_START", 
      "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,65,423,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,
  	2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,
  	13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,
  	20,2,21,7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,
  	27,2,28,7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,
  	34,2,35,7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,
  	41,2,42,7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,
  	48,2,49,7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,
  	55,2,56,7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,
  	62,2,63,7,63,2,64,7,64,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,
  	1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,1,
  	11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,
  	14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,
  	15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,
  	20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,
  	25,1,25,1,25,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,28,1,28,1,
  	29,1,29,1,30,1,30,1,31,1,31,1,32,1,32,1,33,1,33,1,34,1,34,1,35,1,35,1,
  	36,1,36,1,37,1,37,1,38,1,38,1,39,1,39,1,40,1,40,1,41,1,41,1,42,1,42,1,
  	43,1,43,1,44,1,44,1,45,1,45,1,45,1,46,1,46,1,46,1,47,1,47,1,47,1,48,1,
  	48,1,48,1,49,1,49,1,49,1,50,1,50,1,50,1,51,1,51,1,51,1,52,1,52,1,52,1,
  	53,1,53,1,54,1,54,1,54,1,55,1,55,1,55,1,56,4,56,358,8,56,11,56,12,56,
  	359,1,56,1,56,4,56,364,8,56,11,56,12,56,365,3,56,368,8,56,1,57,1,57,5,
  	57,372,8,57,10,57,12,57,375,9,57,1,58,1,58,1,58,1,58,1,59,1,59,1,59,1,
  	59,5,59,385,8,59,10,59,12,59,388,9,59,1,59,1,59,1,60,4,60,393,8,60,11,
  	60,12,60,394,1,60,1,60,1,61,4,61,400,8,61,11,61,12,61,401,1,62,1,62,1,
  	62,1,62,1,62,1,62,1,62,1,62,1,62,3,62,413,8,62,1,63,1,63,1,63,1,63,1,
  	63,1,64,1,64,1,64,1,64,0,0,65,2,1,4,2,6,3,8,4,10,5,12,6,14,7,16,8,18,
  	9,20,10,22,11,24,12,26,13,28,14,30,15,32,16,34,17,36,18,38,19,40,20,42,
  	21,44,22,46,23,48,24,50,25,52,26,54,27,56,28,58,29,60,30,62,31,64,32,
  	66,33,68,34,70,35,72,36,74,37,76,38,78,39,80,40,82,41,84,42,86,43,88,
  	44,90,45,92,46,94,47,96,48,98,49,100,50,102,51,104,52,106,53,108,54,110,
  	55,112,56,114,57,116,58,118,59,120,60,122,61,124,62,126,63,128,64,130,
  	65,2,0,1,8,1,0,48,57,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,
  	122,2,0,10,10,13,13,3,0,9,10,13,13,32,32,6,0,10,10,13,13,34,34,36,36,
  	92,92,123,123,8,0,34,34,39,39,92,92,98,98,102,102,110,110,114,114,116,
  	116,3,0,48,57,65,70,97,102,429,0,2,1,0,0,0,0,4,1,0,0,0,0,6,1,0,0,0,0,
  	8,1,0,0,0,0,10,1,0,0,0,0,12,1,0,0,0,0,14,1,0,0,0,0,16,1,0,0,0,0,18,1,
  	0,0,0,0,20,1,0,0,0,0,22,1,0,0,0,0,24,1,0,0,0,0,26,1,0,0,0,0,28,1,0,0,
  	0,0,30,1,0,0,0,0,32,1,0,0,0,0,34,1,0,0,0,0,36,1,0,0,0,0,38,1,0,0,0,0,
  	40,1,0,0,0,0,42,1,0,0,0,0,44,1,0,0,0,0,46,1,0,0,0,0,48,1,0,0,0,0,50,1,
  	0,0,0,0,52,1,0,0,0,0,54,1,0,0,0,0,56,1,0,0,0,0,58,1,0,0,0,0,60,1,0,0,
  	0,0,62,1,0,0,0,0,64,1,0,0,0,0,66,1,0,0,0,0,68,1,0,0,0,0,70,1,0,0,0,0,
  	72,1,0,0,0,0,74,1,0,0,0,0,76,1,0,0,0,0,78,1,0,0,0,0,80,1,0,0,0,0,82,1,
  	0,0,0,0,84,1,0,0,0,0,86,1,0,0,0,0,88,1,0,0,0,0,90,1,0,0,0,0,92,1,0,0,
  	0,0,94,1,0,0,0,0,96,1,0,0,0,0,98,1,0,0,0,0,100,1,0,0,0,0,102,1,0,0,0,
  	0,104,1,0,0,0,0,106,1,0,0,0,0,108,1,0,0,0,0,110,1,0,0,0,0,112,1,0,0,0,
  	0,114,1,0,0,0,0,116,1,0,0,0,0,118,1,0,0,0,0,120,1,0,0,0,0,122,1,0,0,0,
  	1,124,1,0,0,0,1,126,1,0,0,0,1,128,1,0,0,0,1,130,1,0,0,0,2,132,1,0,0,0,
  	4,138,1,0,0,0,6,144,1,0,0,0,8,152,1,0,0,0,10,157,1,0,0,0,12,163,1,0,0,
  	0,14,167,1,0,0,0,16,170,1,0,0,0,18,175,1,0,0,0,20,182,1,0,0,0,22,188,
  	1,0,0,0,24,193,1,0,0,0,26,198,1,0,0,0,28,204,1,0,0,0,30,208,1,0,0,0,32,
  	216,1,0,0,0,34,226,1,0,0,0,36,233,1,0,0,0,38,240,1,0,0,0,40,246,1,0,0,
  	0,42,250,1,0,0,0,44,253,1,0,0,0,46,259,1,0,0,0,48,266,1,0,0,0,50,270,
  	1,0,0,0,52,276,1,0,0,0,54,281,1,0,0,0,56,285,1,0,0,0,58,290,1,0,0,0,60,
  	292,1,0,0,0,62,294,1,0,0,0,64,296,1,0,0,0,66,298,1,0,0,0,68,300,1,0,0,
  	0,70,302,1,0,0,0,72,304,1,0,0,0,74,306,1,0,0,0,76,308,1,0,0,0,78,310,
  	1,0,0,0,80,312,1,0,0,0,82,314,1,0,0,0,84,316,1,0,0,0,86,318,1,0,0,0,88,
  	320,1,0,0,0,90,322,1,0,0,0,92,324,1,0,0,0,94,327,1,0,0,0,96,330,1,0,0,
  	0,98,333,1,0,0,0,100,336,1,0,0,0,102,339,1,0,0,0,104,342,1,0,0,0,106,
  	345,1,0,0,0,108,348,1,0,0,0,110,350,1,0,0,0,112,353,1,0,0,0,114,357,1,
  	0,0,0,116,369,1,0,0,0,118,376,1,0,0,0,120,380,1,0,0,0,122,392,1,0,0,0,
  	124,399,1,0,0,0,126,412,1,0,0,0,128,414,1,0,0,0,130,419,1,0,0,0,132,133,
  	5,112,0,0,133,134,5,114,0,0,134,135,5,105,0,0,135,136,5,110,0,0,136,137,
  	5,116,0,0,137,3,1,0,0,0,138,139,5,99,0,0,139,140,5,108,0,0,140,141,5,
  	97,0,0,141,142,5,115,0,0,142,143,5,115,0,0,143,5,1,0,0,0,144,145,5,101,
  	0,0,145,146,5,120,0,0,146,147,5,116,0,0,147,148,5,101,0,0,148,149,5,110,
  	0,0,149,150,5,100,0,0,150,151,5,115,0,0,151,7,1,0,0,0,152,153,5,101,0,
  	0,153,154,5,108,0,0,154,155,5,115,0,0,155,156,5,101,0,0,156,9,1,0,0,0,
  	157,158,5,102,0,0,158,159,5,97,0,0,159,160,5,108,0,0,160,161,5,115,0,
  	0,161,162,5,101,0,0,162,11,1,0,0,0,163,164,5,102,0,0,164,165,5,111,0,
  	0,165,166,5,114,0,0,166,13,1,0,0,0,167,168,5,105,0,0,168,169,5,102,0,
  	0,169,15,1,0,0,0,170,171,5,110,0,0,171,172,5,117,0,0,172,173,5,108,0,
  	0,173,174,5,108,0,0,174,17,1,0,0,0,175,176,5,114,0,0,176,177,5,101,0,
  	0,177,178,5,116,0,0,178,179,5,117,0,0,179,180,5,114,0,0,180,181,5,110,
  	0,0,181,19,1,0,0,0,182,183,5,115,0,0,183,184,5,117,0,0,184,185,5,112,
  	0,0,185,186,5,101,0,0,186,187,5,114,0,0,187,21,1,0,0,0,188,189,5,116,
  	0,0,189,190,5,104,0,0,190,191,5,105,0,0,191,192,5,115,0,0,192,23,1,0,
  	0,0,193,194,5,116,0,0,194,195,5,114,0,0,195,196,5,117,0,0,196,197,5,101,
  	0,0,197,25,1,0,0,0,198,199,5,119,0,0,199,200,5,104,0,0,200,201,5,105,
  	0,0,201,202,5,108,0,0,202,203,5,101,0,0,203,27,1,0,0,0,204,205,5,110,
  	0,0,205,206,5,101,0,0,206,207,5,119,0,0,207,29,1,0,0,0,208,209,5,99,0,
  	0,209,210,5,111,0,0,210,211,5,110,0,0,211,212,5,118,0,0,212,213,5,101,
  	0,0,213,214,5,114,0,0,214,215,5,116,0,0,215,31,1,0,0,0,216,217,5,110,
  	0,0,217,218,5,97,0,0,218,219,5,109,0,0,219,220,5,101,0,0,220,221,5,115,
  	0,0,221,222,5,112,0,0,222,223,5,97,0,0,223,224,5,99,0,0,224,225,5,101,
  	0,0,225,33,1,0,0,0,226,227,5,109,0,0,227,228,5,111,0,0,228,229,5,100,
  	0,0,229,230,5,117,0,0,230,231,5,108,0,0,231,232,5,101,0,0,232,35,1,0,
  	0,0,233,234,5,105,0,0,234,235,5,109,0,0,235,236,5,112,0,0,236,237,5,111,
  	0,0,237,238,5,114,0,0,238,239,5,116,0,0,239,37,1,0,0,0,240,241,5,117,
  	0,0,241,242,5,115,0,0,242,243,5,105,0,0,243,244,5,110,0,0,244,245,5,103,
  	0,0,245,39,1,0,0,0,246,247,5,108,0,0,247,248,5,101,0,0,248,249,5,116,
  	0,0,249,41,1,0,0,0,250,251,5,102,0,0,251,252,5,110,0,0,252,43,1,0,0,0,
  	253,254,5,99,0,0,254,255,5,111,0,0,255,256,5,110,0,0,256,257,5,115,0,
  	0,257,258,5,116,0,0,258,45,1,0,0,0,259,260,5,99,0,0,260,261,5,111,0,0,
  	261,262,5,110,0,0,262,263,5,115,0,0,263,264,5,116,0,0,264,265,5,33,0,
  	0,265,47,1,0,0,0,266,267,5,105,0,0,267,268,5,110,0,0,268,269,5,116,0,
  	0,269,49,1,0,0,0,270,271,5,102,0,0,271,272,5,108,0,0,272,273,5,111,0,
  	0,273,274,5,97,0,0,274,275,5,116,0,0,275,51,1,0,0,0,276,277,5,98,0,0,
  	277,278,5,111,0,0,278,279,5,111,0,0,279,280,5,108,0,0,280,53,1,0,0,0,
  	281,282,5,115,0,0,282,283,5,116,0,0,283,284,5,114,0,0,284,55,1,0,0,0,
  	285,286,5,118,0,0,286,287,5,111,0,0,287,288,5,105,0,0,288,289,5,100,0,
  	0,289,57,1,0,0,0,290,291,5,40,0,0,291,59,1,0,0,0,292,293,5,41,0,0,293,
  	61,1,0,0,0,294,295,5,123,0,0,295,63,1,0,0,0,296,297,5,125,0,0,297,65,
  	1,0,0,0,298,299,5,91,0,0,299,67,1,0,0,0,300,301,5,93,0,0,301,69,1,0,0,
  	0,302,303,5,44,0,0,303,71,1,0,0,0,304,305,5,46,0,0,305,73,1,0,0,0,306,
  	307,5,45,0,0,307,75,1,0,0,0,308,309,5,43,0,0,309,77,1,0,0,0,310,311,5,
  	59,0,0,311,79,1,0,0,0,312,313,5,47,0,0,313,81,1,0,0,0,314,315,5,42,0,
  	0,315,83,1,0,0,0,316,317,5,33,0,0,317,85,1,0,0,0,318,319,5,61,0,0,319,
  	87,1,0,0,0,320,321,5,62,0,0,321,89,1,0,0,0,322,323,5,60,0,0,323,91,1,
  	0,0,0,324,325,5,33,0,0,325,326,5,61,0,0,326,93,1,0,0,0,327,328,5,61,0,
  	0,328,329,5,61,0,0,329,95,1,0,0,0,330,331,5,62,0,0,331,332,5,61,0,0,332,
  	97,1,0,0,0,333,334,5,60,0,0,334,335,5,61,0,0,335,99,1,0,0,0,336,337,5,
  	38,0,0,337,338,5,38,0,0,338,101,1,0,0,0,339,340,5,124,0,0,340,341,5,124,
  	0,0,341,103,1,0,0,0,342,343,5,43,0,0,343,344,5,43,0,0,344,105,1,0,0,0,
  	345,346,5,45,0,0,346,347,5,45,0,0,347,107,1,0,0,0,348,349,5,37,0,0,349,
  	109,1,0,0,0,350,351,5,45,0,0,351,352,5,62,0,0,352,111,1,0,0,0,353,354,
  	5,58,0,0,354,355,5,58,0,0,355,113,1,0,0,0,356,358,7,0,0,0,357,356,1,0,
  	0,0,358,359,1,0,0,0,359,357,1,0,0,0,359,360,1,0,0,0,360,367,1,0,0,0,361,
  	363,5,46,0,0,362,364,7,0,0,0,363,362,1,0,0,0,364,365,1,0,0,0,365,363,
  	1,0,0,0,365,366,1,0,0,0,366,368,1,0,0,0,367,361,1,0,0,0,367,368,1,0,0,
  	0,368,115,1,0,0,0,369,373,7,1,0,0,370,372,7,2,0,0,371,370,1,0,0,0,372,
  	375,1,0,0,0,373,371,1,0,0,0,373,374,1,0,0,0,374,117,1,0,0,0,375,373,1,
  	0,0,0,376,377,5,34,0,0,377,378,1,0,0,0,378,379,6,58,0,0,379,119,1,0,0,
  	0,380,381,5,47,0,0,381,382,5,47,0,0,382,386,1,0,0,0,383,385,8,3,0,0,384,
  	383,1,0,0,0,385,388,1,0,0,0,386,384,1,0,0,0,386,387,1,0,0,0,387,389,1,
  	0,0,0,388,386,1,0,0,0,389,390,6,59,1,0,390,121,1,0,0,0,391,393,7,4,0,
  	0,392,391,1,0,0,0,393,394,1,0,0,0,394,392,1,0,0,0,394,395,1,0,0,0,395,
  	396,1,0,0,0,396,397,6,60,1,0,397,123,1,0,0,0,398,400,8,5,0,0,399,398,
  	1,0,0,0,400,401,1,0,0,0,401,399,1,0,0,0,401,402,1,0,0,0,402,125,1,0,0,
  	0,403,404,5,92,0,0,404,413,7,6,0,0,405,406,5,92,0,0,406,407,5,117,0,0,
  	407,408,1,0,0,0,408,409,7,7,0,0,409,410,7,7,0,0,410,411,7,7,0,0,411,413,
  	7,7,0,0,412,403,1,0,0,0,412,405,1,0,0,0,413,127,1,0,0,0,414,415,5,36,
  	0,0,415,416,5,123,0,0,416,417,1,0,0,0,417,418,6,63,2,0,418,129,1,0,0,
  	0,419,420,5,34,0,0,420,421,1,0,0,0,421,422,6,64,3,0,422,131,1,0,0,0,10,
  	0,1,359,365,367,373,386,394,401,412,4,5,1,0,6,0,0,5,0,0,4,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  prystlexerLexerStaticData = std::move(staticData);
}

}

PrystLexer::PrystLexer(CharStream *input) : Lexer(input) {
  PrystLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *prystlexerLexerStaticData->atn, prystlexerLexerStaticData->decisionToDFA, prystlexerLexerStaticData->sharedContextCache);
}

PrystLexer::~PrystLexer() {
  delete _interpreter;
}

std::string PrystLexer::getGrammarFileName() const {
  return "PrystLexer.g4";
}

const std::vector<std::string>& PrystLexer::getRuleNames() const {
  return prystlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& PrystLexer::getChannelNames() const {
  return prystlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& PrystLexer::getModeNames() const {
  return prystlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& PrystLexer::getVocabulary() const {
  return prystlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PrystLexer::getSerializedATN() const {
  return prystlexerLexerStaticData->serializedATN;
}

const atn::ATN& PrystLexer::getATN() const {
  return *prystlexerLexerStaticData->atn;
}




void PrystLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  prystlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(prystlexerLexerOnceFlag, prystlexerLexerInitialize);
#endif
}
