
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
      "program", "declaration", "functionDecl", "variableDecl", "classDeclaration", 
      "classBody", "classMember", "paramList", "param", "type", "statement", 
      "expression", "assignment", "logicOr", "logicAnd", "equality", "comparison", 
      "addition", "multiplication", "unary", "postfix", "call", "callSuffix", 
      "primary", "newExpression", "arguments"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'{'", "'}'", "'['", "']'", "','", "'.'", "'-'", 
      "'+'", "';'", "'/'", "'*'", "'!'", "'='", "'>'", "'<'", "'!='", "'=='", 
      "'>='", "'<='", "'&&'", "'||'", "'++'", "'--'", "'%'", "'class'", 
      "'extends'", "'else'", "'false'", "'for'", "'if'", "'null'", "'return'", 
      "'super'", "'this'", "'true'", "'while'", "'new'", "'int'", "'float'", 
      "'bool'", "'str'", "'void'"
    },
    std::vector<std::string>{
      "", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", 
      "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", 
      "EQUAL", "GREATER", "LESS", "NOT_EQUAL", "EQUAL_EQUAL", "GREATER_EQUAL", 
      "LESS_EQUAL", "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "CLASS", 
      "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", "RETURN", "SUPER", 
      "THIS", "TRUE", "WHILE", "NEW", "INT", "FLOAT", "BOOL", "STR", "VOID", 
      "NUMBER", "STRING", "IDENTIFIER", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,49,334,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,1,0,5,0,54,8,0,10,0,12,0,57,
  	9,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,65,8,1,1,2,1,2,1,2,1,2,3,2,71,8,2,1,2,
  	1,2,1,2,5,2,76,8,2,10,2,12,2,79,9,2,1,2,1,2,1,3,1,3,1,3,1,3,3,3,87,8,
  	3,1,3,1,3,1,4,1,4,1,4,1,4,3,4,95,8,4,1,4,1,4,1,5,1,5,5,5,101,8,5,10,5,
  	12,5,104,9,5,1,5,1,5,1,6,1,6,1,6,1,6,3,6,112,8,6,1,6,1,6,1,6,1,6,1,6,
  	1,6,3,6,120,8,6,1,6,1,6,1,6,5,6,125,8,6,10,6,12,6,128,9,6,1,6,1,6,3,6,
  	132,8,6,1,7,1,7,1,7,5,7,137,8,7,10,7,12,7,140,9,7,1,8,1,8,1,8,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,3,9,152,8,9,1,9,1,9,1,9,5,9,157,8,9,10,9,12,9,160,
  	9,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,172,8,10,1,
  	10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,187,
  	8,10,1,10,3,10,190,8,10,1,10,1,10,3,10,194,8,10,1,10,1,10,1,10,1,10,3,
  	10,200,8,10,1,10,1,10,1,10,5,10,205,8,10,10,10,12,10,208,9,10,1,10,3,
  	10,211,8,10,1,11,1,11,3,11,215,8,11,1,12,1,12,1,12,3,12,220,8,12,1,12,
  	1,12,1,12,1,12,1,13,1,13,1,13,5,13,229,8,13,10,13,12,13,232,9,13,1,14,
  	1,14,1,14,5,14,237,8,14,10,14,12,14,240,9,14,1,15,1,15,1,15,5,15,245,
  	8,15,10,15,12,15,248,9,15,1,16,1,16,1,16,5,16,253,8,16,10,16,12,16,256,
  	9,16,1,17,1,17,1,17,5,17,261,8,17,10,17,12,17,264,9,17,1,18,1,18,1,18,
  	5,18,269,8,18,10,18,12,18,272,9,18,1,19,1,19,1,19,3,19,277,8,19,1,20,
  	1,20,3,20,281,8,20,1,21,1,21,1,21,5,21,286,8,21,10,21,12,21,289,9,21,
  	1,22,1,22,1,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,303,
  	8,23,1,23,3,23,306,8,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,
  	316,8,23,1,24,1,24,1,24,1,24,3,24,322,8,24,1,24,1,24,1,25,1,25,1,25,5,
  	25,329,8,25,10,25,12,25,332,9,25,1,25,0,1,18,26,0,2,4,6,8,10,12,14,16,
  	18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,0,6,1,0,18,19,2,0,
  	16,17,20,21,1,0,9,10,2,0,12,13,26,26,3,0,9,9,14,14,24,25,1,0,24,25,363,
  	0,55,1,0,0,0,2,64,1,0,0,0,4,66,1,0,0,0,6,82,1,0,0,0,8,90,1,0,0,0,10,98,
  	1,0,0,0,12,131,1,0,0,0,14,133,1,0,0,0,16,141,1,0,0,0,18,151,1,0,0,0,20,
  	210,1,0,0,0,22,214,1,0,0,0,24,219,1,0,0,0,26,225,1,0,0,0,28,233,1,0,0,
  	0,30,241,1,0,0,0,32,249,1,0,0,0,34,257,1,0,0,0,36,265,1,0,0,0,38,276,
  	1,0,0,0,40,278,1,0,0,0,42,282,1,0,0,0,44,290,1,0,0,0,46,315,1,0,0,0,48,
  	317,1,0,0,0,50,325,1,0,0,0,52,54,3,2,1,0,53,52,1,0,0,0,54,57,1,0,0,0,
  	55,53,1,0,0,0,55,56,1,0,0,0,56,58,1,0,0,0,57,55,1,0,0,0,58,59,5,0,0,1,
  	59,1,1,0,0,0,60,65,3,4,2,0,61,65,3,6,3,0,62,65,3,8,4,0,63,65,3,20,10,
  	0,64,60,1,0,0,0,64,61,1,0,0,0,64,62,1,0,0,0,64,63,1,0,0,0,65,3,1,0,0,
  	0,66,67,3,18,9,0,67,68,5,47,0,0,68,70,5,1,0,0,69,71,3,14,7,0,70,69,1,
  	0,0,0,70,71,1,0,0,0,71,72,1,0,0,0,72,73,5,2,0,0,73,77,5,3,0,0,74,76,3,
  	2,1,0,75,74,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,77,78,1,0,0,0,78,80,1,
  	0,0,0,79,77,1,0,0,0,80,81,5,4,0,0,81,5,1,0,0,0,82,83,3,18,9,0,83,86,5,
  	47,0,0,84,85,5,15,0,0,85,87,3,22,11,0,86,84,1,0,0,0,86,87,1,0,0,0,87,
  	88,1,0,0,0,88,89,5,11,0,0,89,7,1,0,0,0,90,91,5,27,0,0,91,94,5,47,0,0,
  	92,93,5,28,0,0,93,95,5,47,0,0,94,92,1,0,0,0,94,95,1,0,0,0,95,96,1,0,0,
  	0,96,97,3,10,5,0,97,9,1,0,0,0,98,102,5,3,0,0,99,101,3,12,6,0,100,99,1,
  	0,0,0,101,104,1,0,0,0,102,100,1,0,0,0,102,103,1,0,0,0,103,105,1,0,0,0,
  	104,102,1,0,0,0,105,106,5,4,0,0,106,11,1,0,0,0,107,108,3,18,9,0,108,111,
  	5,47,0,0,109,110,5,15,0,0,110,112,3,22,11,0,111,109,1,0,0,0,111,112,1,
  	0,0,0,112,113,1,0,0,0,113,114,5,11,0,0,114,132,1,0,0,0,115,116,3,18,9,
  	0,116,117,5,47,0,0,117,119,5,1,0,0,118,120,3,14,7,0,119,118,1,0,0,0,119,
  	120,1,0,0,0,120,121,1,0,0,0,121,122,5,2,0,0,122,126,5,3,0,0,123,125,3,
  	2,1,0,124,123,1,0,0,0,125,128,1,0,0,0,126,124,1,0,0,0,126,127,1,0,0,0,
  	127,129,1,0,0,0,128,126,1,0,0,0,129,130,5,4,0,0,130,132,1,0,0,0,131,107,
  	1,0,0,0,131,115,1,0,0,0,132,13,1,0,0,0,133,138,3,16,8,0,134,135,5,7,0,
  	0,135,137,3,16,8,0,136,134,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,138,
  	139,1,0,0,0,139,15,1,0,0,0,140,138,1,0,0,0,141,142,3,18,9,0,142,143,5,
  	47,0,0,143,17,1,0,0,0,144,145,6,9,-1,0,145,152,5,40,0,0,146,152,5,41,
  	0,0,147,152,5,42,0,0,148,152,5,43,0,0,149,152,5,44,0,0,150,152,5,47,0,
  	0,151,144,1,0,0,0,151,146,1,0,0,0,151,147,1,0,0,0,151,148,1,0,0,0,151,
  	149,1,0,0,0,151,150,1,0,0,0,152,158,1,0,0,0,153,154,10,1,0,0,154,155,
  	5,5,0,0,155,157,5,6,0,0,156,153,1,0,0,0,157,160,1,0,0,0,158,156,1,0,0,
  	0,158,159,1,0,0,0,159,19,1,0,0,0,160,158,1,0,0,0,161,162,3,22,11,0,162,
  	163,5,11,0,0,163,211,1,0,0,0,164,165,5,32,0,0,165,166,5,1,0,0,166,167,
  	3,22,11,0,167,168,5,2,0,0,168,171,3,20,10,0,169,170,5,29,0,0,170,172,
  	3,20,10,0,171,169,1,0,0,0,171,172,1,0,0,0,172,211,1,0,0,0,173,174,5,38,
  	0,0,174,175,5,1,0,0,175,176,3,22,11,0,176,177,5,2,0,0,177,178,3,20,10,
  	0,178,211,1,0,0,0,179,180,5,31,0,0,180,186,5,1,0,0,181,187,3,6,3,0,182,
  	183,3,22,11,0,183,184,5,11,0,0,184,187,1,0,0,0,185,187,5,11,0,0,186,181,
  	1,0,0,0,186,182,1,0,0,0,186,185,1,0,0,0,187,189,1,0,0,0,188,190,3,22,
  	11,0,189,188,1,0,0,0,189,190,1,0,0,0,190,191,1,0,0,0,191,193,5,11,0,0,
  	192,194,3,22,11,0,193,192,1,0,0,0,193,194,1,0,0,0,194,195,1,0,0,0,195,
  	196,5,2,0,0,196,211,3,20,10,0,197,199,5,34,0,0,198,200,3,22,11,0,199,
  	198,1,0,0,0,199,200,1,0,0,0,200,201,1,0,0,0,201,211,5,11,0,0,202,206,
  	5,3,0,0,203,205,3,2,1,0,204,203,1,0,0,0,205,208,1,0,0,0,206,204,1,0,0,
  	0,206,207,1,0,0,0,207,209,1,0,0,0,208,206,1,0,0,0,209,211,5,4,0,0,210,
  	161,1,0,0,0,210,164,1,0,0,0,210,173,1,0,0,0,210,179,1,0,0,0,210,197,1,
  	0,0,0,210,202,1,0,0,0,211,21,1,0,0,0,212,215,3,24,12,0,213,215,3,26,13,
  	0,214,212,1,0,0,0,214,213,1,0,0,0,215,23,1,0,0,0,216,217,3,42,21,0,217,
  	218,5,8,0,0,218,220,1,0,0,0,219,216,1,0,0,0,219,220,1,0,0,0,220,221,1,
  	0,0,0,221,222,5,47,0,0,222,223,5,15,0,0,223,224,3,22,11,0,224,25,1,0,
  	0,0,225,230,3,28,14,0,226,227,5,23,0,0,227,229,3,28,14,0,228,226,1,0,
  	0,0,229,232,1,0,0,0,230,228,1,0,0,0,230,231,1,0,0,0,231,27,1,0,0,0,232,
  	230,1,0,0,0,233,238,3,30,15,0,234,235,5,22,0,0,235,237,3,30,15,0,236,
  	234,1,0,0,0,237,240,1,0,0,0,238,236,1,0,0,0,238,239,1,0,0,0,239,29,1,
  	0,0,0,240,238,1,0,0,0,241,246,3,32,16,0,242,243,7,0,0,0,243,245,3,32,
  	16,0,244,242,1,0,0,0,245,248,1,0,0,0,246,244,1,0,0,0,246,247,1,0,0,0,
  	247,31,1,0,0,0,248,246,1,0,0,0,249,254,3,34,17,0,250,251,7,1,0,0,251,
  	253,3,34,17,0,252,250,1,0,0,0,253,256,1,0,0,0,254,252,1,0,0,0,254,255,
  	1,0,0,0,255,33,1,0,0,0,256,254,1,0,0,0,257,262,3,36,18,0,258,259,7,2,
  	0,0,259,261,3,36,18,0,260,258,1,0,0,0,261,264,1,0,0,0,262,260,1,0,0,0,
  	262,263,1,0,0,0,263,35,1,0,0,0,264,262,1,0,0,0,265,270,3,38,19,0,266,
  	267,7,3,0,0,267,269,3,38,19,0,268,266,1,0,0,0,269,272,1,0,0,0,270,268,
  	1,0,0,0,270,271,1,0,0,0,271,37,1,0,0,0,272,270,1,0,0,0,273,274,7,4,0,
  	0,274,277,3,38,19,0,275,277,3,40,20,0,276,273,1,0,0,0,276,275,1,0,0,0,
  	277,39,1,0,0,0,278,280,3,46,23,0,279,281,7,5,0,0,280,279,1,0,0,0,280,
  	281,1,0,0,0,281,41,1,0,0,0,282,287,3,46,23,0,283,284,5,8,0,0,284,286,
  	5,47,0,0,285,283,1,0,0,0,286,289,1,0,0,0,287,285,1,0,0,0,287,288,1,0,
  	0,0,288,43,1,0,0,0,289,287,1,0,0,0,290,291,5,8,0,0,291,292,5,47,0,0,292,
  	45,1,0,0,0,293,316,5,37,0,0,294,316,5,30,0,0,295,316,5,33,0,0,296,316,
  	5,36,0,0,297,316,5,45,0,0,298,316,5,46,0,0,299,305,5,47,0,0,300,302,5,
  	1,0,0,301,303,3,50,25,0,302,301,1,0,0,0,302,303,1,0,0,0,303,304,1,0,0,
  	0,304,306,5,2,0,0,305,300,1,0,0,0,305,306,1,0,0,0,306,316,1,0,0,0,307,
  	308,5,1,0,0,308,309,3,22,11,0,309,310,5,2,0,0,310,316,1,0,0,0,311,312,
  	5,35,0,0,312,313,5,8,0,0,313,316,5,47,0,0,314,316,3,48,24,0,315,293,1,
  	0,0,0,315,294,1,0,0,0,315,295,1,0,0,0,315,296,1,0,0,0,315,297,1,0,0,0,
  	315,298,1,0,0,0,315,299,1,0,0,0,315,307,1,0,0,0,315,311,1,0,0,0,315,314,
  	1,0,0,0,316,47,1,0,0,0,317,318,5,39,0,0,318,319,5,47,0,0,319,321,5,1,
  	0,0,320,322,3,50,25,0,321,320,1,0,0,0,321,322,1,0,0,0,322,323,1,0,0,0,
  	323,324,5,2,0,0,324,49,1,0,0,0,325,330,3,22,11,0,326,327,5,7,0,0,327,
  	329,3,22,11,0,328,326,1,0,0,0,329,332,1,0,0,0,330,328,1,0,0,0,330,331,
  	1,0,0,0,331,51,1,0,0,0,332,330,1,0,0,0,37,55,64,70,77,86,94,102,111,119,
  	126,131,138,151,158,171,186,189,193,199,206,210,214,219,230,238,246,254,
  	262,270,276,280,287,302,305,315,321,330
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
    setState(55);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474087535114) != 0)) {
      setState(52);
      declaration();
      setState(57);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(58);
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
    setState(64);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(60);
      functionDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(61);
      variableDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(62);
      classDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(63);
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

PrystParser::TypeContext* PrystParser::FunctionDeclContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
}

tree::TerminalNode* PrystParser::FunctionDeclContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

tree::TerminalNode* PrystParser::FunctionDeclContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

tree::TerminalNode* PrystParser::FunctionDeclContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

tree::TerminalNode* PrystParser::FunctionDeclContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::FunctionDeclContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

PrystParser::ParamListContext* PrystParser::FunctionDeclContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
}

std::vector<PrystParser::DeclarationContext *> PrystParser::FunctionDeclContext::declaration() {
  return getRuleContexts<PrystParser::DeclarationContext>();
}

PrystParser::DeclarationContext* PrystParser::FunctionDeclContext::declaration(size_t i) {
  return getRuleContext<PrystParser::DeclarationContext>(i);
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
    setState(66);
    type(0);
    setState(67);
    match(PrystParser::IDENTIFIER);
    setState(68);
    match(PrystParser::LPAREN);
    setState(70);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 174822348816384) != 0)) {
      setState(69);
      paramList();
    }
    setState(72);
    match(PrystParser::RPAREN);
    setState(73);
    match(PrystParser::LBRACE);
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474087535114) != 0)) {
      setState(74);
      declaration();
      setState(79);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(80);
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
  enterRule(_localctx, 6, PrystParser::RuleVariableDecl);
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
    setState(82);
    type(0);
    setState(83);
    match(PrystParser::IDENTIFIER);
    setState(86);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EQUAL) {
      setState(84);
      match(PrystParser::EQUAL);
      setState(85);
      expression();
    }
    setState(88);
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
  enterRule(_localctx, 8, PrystParser::RuleClassDeclaration);
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
    setState(90);
    match(PrystParser::CLASS);
    setState(91);
    match(PrystParser::IDENTIFIER);
    setState(94);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EXTENDS) {
      setState(92);
      match(PrystParser::EXTENDS);
      setState(93);
      match(PrystParser::IDENTIFIER);
    }
    setState(96);
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
  enterRule(_localctx, 10, PrystParser::RuleClassBody);
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
    setState(98);
    match(PrystParser::LBRACE);
    setState(102);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 174822348816384) != 0)) {
      setState(99);
      classMember();
      setState(104);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(105);
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
  enterRule(_localctx, 12, PrystParser::RuleClassMember);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(131);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrystParser::ClassVariableDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(107);
      type(0);
      setState(108);
      match(PrystParser::IDENTIFIER);
      setState(111);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrystParser::EQUAL) {
        setState(109);
        match(PrystParser::EQUAL);
        setState(110);
        expression();
      }
      setState(113);
      match(PrystParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PrystParser::ClassFunctionDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(115);
      type(0);
      setState(116);
      match(PrystParser::IDENTIFIER);
      setState(117);
      match(PrystParser::LPAREN);
      setState(119);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 174822348816384) != 0)) {
        setState(118);
        paramList();
      }
      setState(121);
      match(PrystParser::RPAREN);
      setState(122);
      match(PrystParser::LBRACE);
      setState(126);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 281474087535114) != 0)) {
        setState(123);
        declaration();
        setState(128);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(129);
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
  enterRule(_localctx, 14, PrystParser::RuleParamList);
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
    setState(133);
    param();
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(134);
      match(PrystParser::COMMA);
      setState(135);
      param();
      setState(140);
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
  enterRule(_localctx, 16, PrystParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
    type(0);
    setState(142);
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
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, PrystParser::RuleType, precedence);

    

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
    setState(151);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::INT: {
        setState(145);
        match(PrystParser::INT);
        break;
      }

      case PrystParser::FLOAT: {
        setState(146);
        match(PrystParser::FLOAT);
        break;
      }

      case PrystParser::BOOL: {
        setState(147);
        match(PrystParser::BOOL);
        break;
      }

      case PrystParser::STR: {
        setState(148);
        match(PrystParser::STR);
        break;
      }

      case PrystParser::VOID: {
        setState(149);
        match(PrystParser::VOID);
        break;
      }

      case PrystParser::IDENTIFIER: {
        setState(150);
        match(PrystParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(158);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(153);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(154);
        match(PrystParser::LBRACKET);
        setState(155);
        match(PrystParser::RBRACKET); 
      }
      setState(160);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
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
  enterRule(_localctx, 20, PrystParser::RuleStatement);
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
      case PrystParser::NUMBER:
      case PrystParser::STRING:
      case PrystParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<PrystParser::ExprStatementContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(161);
        expression();
        setState(162);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::IF: {
        _localctx = _tracker.createInstance<PrystParser::IfStatementContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(164);
        match(PrystParser::IF);
        setState(165);
        match(PrystParser::LPAREN);
        setState(166);
        expression();
        setState(167);
        match(PrystParser::RPAREN);
        setState(168);
        statement();
        setState(171);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          setState(169);
          match(PrystParser::ELSE);
          setState(170);
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
        setState(173);
        match(PrystParser::WHILE);
        setState(174);
        match(PrystParser::LPAREN);
        setState(175);
        expression();
        setState(176);
        match(PrystParser::RPAREN);
        setState(177);
        statement();
        break;
      }

      case PrystParser::FOR: {
        _localctx = _tracker.createInstance<PrystParser::ForStatementContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(179);
        match(PrystParser::FOR);
        setState(180);
        match(PrystParser::LPAREN);
        setState(186);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          setState(181);
          variableDecl();
          break;
        }

        case 2: {
          setState(182);
          expression();
          setState(183);
          match(PrystParser::SEMICOLON);
          break;
        }

        case 3: {
          setState(185);
          match(PrystParser::SEMICOLON);
          break;
        }

        default:
          break;
        }
        setState(189);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 247090592629250) != 0)) {
          setState(188);
          expression();
        }
        setState(191);
        match(PrystParser::SEMICOLON);
        setState(193);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 247090592629250) != 0)) {
          setState(192);
          expression();
        }
        setState(195);
        match(PrystParser::RPAREN);
        setState(196);
        statement();
        break;
      }

      case PrystParser::RETURN: {
        _localctx = _tracker.createInstance<PrystParser::ReturnStatementContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(197);
        match(PrystParser::RETURN);
        setState(199);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 247090592629250) != 0)) {
          setState(198);
          expression();
        }
        setState(201);
        match(PrystParser::SEMICOLON);
        break;
      }

      case PrystParser::LBRACE: {
        _localctx = _tracker.createInstance<PrystParser::BlockStatementContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(202);
        match(PrystParser::LBRACE);
        setState(206);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 281474087535114) != 0)) {
          setState(203);
          declaration();
          setState(208);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(209);
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
  enterRule(_localctx, 22, PrystParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(214);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(212);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(213);
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
  enterRule(_localctx, 24, PrystParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(216);
      call();
      setState(217);
      match(PrystParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(221);
    match(PrystParser::IDENTIFIER);
    setState(222);
    match(PrystParser::EQUAL);
    setState(223);
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
  enterRule(_localctx, 26, PrystParser::RuleLogicOr);
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
    setState(225);
    logicAnd();
    setState(230);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::OR) {
      setState(226);
      match(PrystParser::OR);
      setState(227);
      logicAnd();
      setState(232);
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
  enterRule(_localctx, 28, PrystParser::RuleLogicAnd);
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
    setState(233);
    equality();
    setState(238);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::AND) {
      setState(234);
      match(PrystParser::AND);
      setState(235);
      equality();
      setState(240);
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
  enterRule(_localctx, 30, PrystParser::RuleEquality);
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
    setState(241);
    comparison();
    setState(246);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::NOT_EQUAL

    || _la == PrystParser::EQUAL_EQUAL) {
      setState(242);
      _la = _input->LA(1);
      if (!(_la == PrystParser::NOT_EQUAL

      || _la == PrystParser::EQUAL_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(243);
      comparison();
      setState(248);
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
  enterRule(_localctx, 32, PrystParser::RuleComparison);
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
    addition();
    setState(254);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3342336) != 0)) {
      setState(250);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3342336) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(251);
      addition();
      setState(256);
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
  enterRule(_localctx, 34, PrystParser::RuleAddition);
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
    setState(257);
    multiplication();
    setState(262);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::MINUS

    || _la == PrystParser::PLUS) {
      setState(258);
      _la = _input->LA(1);
      if (!(_la == PrystParser::MINUS

      || _la == PrystParser::PLUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(259);
      multiplication();
      setState(264);
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
  enterRule(_localctx, 36, PrystParser::RuleMultiplication);
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
    setState(265);
    unary();
    setState(270);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67121152) != 0)) {
      setState(266);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 67121152) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(267);
      unary();
      setState(272);
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
  enterRule(_localctx, 38, PrystParser::RuleUnary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(276);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT: {
        enterOuterAlt(_localctx, 1);
        setState(273);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 50348544) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(274);
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
        setState(275);
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

tree::TerminalNode* PrystParser::PostfixContext::INCREMENT() {
  return getToken(PrystParser::INCREMENT, 0);
}

tree::TerminalNode* PrystParser::PostfixContext::DECREMENT() {
  return getToken(PrystParser::DECREMENT, 0);
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
  enterRule(_localctx, 40, PrystParser::RulePostfix);
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
    setState(278);
    primary();
    setState(280);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::INCREMENT

    || _la == PrystParser::DECREMENT) {
      setState(279);
      _la = _input->LA(1);
      if (!(_la == PrystParser::INCREMENT

      || _la == PrystParser::DECREMENT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
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
  enterRule(_localctx, 42, PrystParser::RuleCall);

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
    setState(282);
    primary();
    setState(287);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(283);
        match(PrystParser::DOT);
        setState(284);
        match(PrystParser::IDENTIFIER); 
      }
      setState(289);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
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

tree::TerminalNode* PrystParser::CallSuffixContext::DOT() {
  return getToken(PrystParser::DOT, 0);
}

tree::TerminalNode* PrystParser::CallSuffixContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 44, PrystParser::RuleCallSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(290);
    match(PrystParser::DOT);
    setState(291);
    match(PrystParser::IDENTIFIER);
   
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
  enterRule(_localctx, 46, PrystParser::RulePrimary);
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
      case PrystParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(293);
        match(PrystParser::TRUE);
        break;
      }

      case PrystParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(294);
        match(PrystParser::FALSE);
        break;
      }

      case PrystParser::NULL_: {
        enterOuterAlt(_localctx, 3);
        setState(295);
        match(PrystParser::NULL_);
        break;
      }

      case PrystParser::THIS: {
        enterOuterAlt(_localctx, 4);
        setState(296);
        match(PrystParser::THIS);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(297);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::STRING: {
        enterOuterAlt(_localctx, 6);
        setState(298);
        match(PrystParser::STRING);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 7);
        setState(299);
        match(PrystParser::IDENTIFIER);
        setState(305);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrystParser::LPAREN) {
          setState(300);
          match(PrystParser::LPAREN);
          setState(302);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 247090592629250) != 0)) {
            setState(301);
            arguments();
          }
          setState(304);
          match(PrystParser::RPAREN);
        }
        break;
      }

      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 8);
        setState(307);
        match(PrystParser::LPAREN);
        setState(308);
        expression();
        setState(309);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::SUPER: {
        enterOuterAlt(_localctx, 9);
        setState(311);
        match(PrystParser::SUPER);
        setState(312);
        match(PrystParser::DOT);
        setState(313);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::NEW: {
        enterOuterAlt(_localctx, 10);
        setState(314);
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
  enterRule(_localctx, 48, PrystParser::RuleNewExpression);
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
    match(PrystParser::NEW);
    setState(318);
    match(PrystParser::IDENTIFIER);
    setState(319);
    match(PrystParser::LPAREN);
    setState(321);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 247090592629250) != 0)) {
      setState(320);
      arguments();
    }
    setState(323);
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
  enterRule(_localctx, 50, PrystParser::RuleArguments);
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
    expression();
    setState(330);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(326);
      match(PrystParser::COMMA);
      setState(327);
      expression();
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

bool PrystParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 9: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

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
