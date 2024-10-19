
// Generated from Pryst.g4 by ANTLR 4.13.2


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
      "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA", 
      "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", "EQUAL", 
      "GREATER", "LESS", "NOT_EQUAL", "EQUAL_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", 
      "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "CLASS", "EXTENDS", 
      "ELSE", "FALSE", "FOR", "IF", "NULL", "RETURN", "SUPER", "THIS", "TRUE", 
      "WHILE", "NEW", "INT", "FLOAT", "BOOL", "STR", "NUMBER", "STRING", 
      "IDENTIFIER", "COMMENT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'{'", "'}'", "'['", "']'", "','", "'.'", "'-'", 
      "'+'", "';'", "'/'", "'*'", "'!'", "'='", "'>'", "'<'", "'!='", "'=='", 
      "'>='", "'<='", "'&&'", "'||'", "'++'", "'--'", "'%'", "'class'", 
      "'extends'", "'else'", "'false'", "'for'", "'if'", "'null'", "'return'", 
      "'super'", "'this'", "'true'", "'while'", "'new'", "'int'", "'float'", 
      "'bool'", "'str'"
    },
    std::vector<std::string>{
      "", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", 
      "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", 
      "EQUAL", "GREATER", "LESS", "NOT_EQUAL", "EQUAL_EQUAL", "GREATER_EQUAL", 
      "LESS_EQUAL", "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "CLASS", 
      "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", "RETURN", "SUPER", 
      "THIS", "TRUE", "WHILE", "NEW", "INT", "FLOAT", "BOOL", "STR", "NUMBER", 
      "STRING", "IDENTIFIER", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,48,295,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,1,0,1,0,1,1,1,
  	1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,
  	1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,
  	1,17,1,17,1,18,1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,21,
  	1,22,1,22,1,22,1,23,1,23,1,23,1,24,1,24,1,24,1,25,1,25,1,26,1,26,1,26,
  	1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,28,1,28,1,28,
  	1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,30,1,31,1,31,
  	1,31,1,32,1,32,1,32,1,32,1,32,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,34,
  	1,34,1,34,1,34,1,34,1,34,1,35,1,35,1,35,1,35,1,35,1,36,1,36,1,36,1,36,
  	1,36,1,37,1,37,1,37,1,37,1,37,1,37,1,38,1,38,1,38,1,38,1,39,1,39,1,39,
  	1,39,1,40,1,40,1,40,1,40,1,40,1,40,1,41,1,41,1,41,1,41,1,41,1,42,1,42,
  	1,42,1,42,1,43,4,43,248,8,43,11,43,12,43,249,1,43,1,43,4,43,254,8,43,
  	11,43,12,43,255,3,43,258,8,43,1,44,1,44,1,44,1,44,5,44,264,8,44,10,44,
  	12,44,267,9,44,1,44,1,44,1,45,1,45,5,45,273,8,45,10,45,12,45,276,9,45,
  	1,46,1,46,1,46,1,46,5,46,282,8,46,10,46,12,46,285,9,46,1,46,1,46,1,47,
  	4,47,290,8,47,11,47,12,47,291,1,47,1,47,0,0,48,1,1,3,2,5,3,7,4,9,5,11,
  	6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,
  	37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,
  	30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,79,40,81,41,
  	83,42,85,43,87,44,89,45,91,46,93,47,95,48,1,0,6,1,0,48,57,2,0,34,34,92,
  	92,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,2,0,10,10,13,13,
  	3,0,9,10,13,13,32,32,302,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,
  	0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,
  	19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,
  	0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,
  	0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,
  	51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,
  	0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,
  	0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,
  	83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,
  	0,0,0,0,95,1,0,0,0,1,97,1,0,0,0,3,99,1,0,0,0,5,101,1,0,0,0,7,103,1,0,
  	0,0,9,105,1,0,0,0,11,107,1,0,0,0,13,109,1,0,0,0,15,111,1,0,0,0,17,113,
  	1,0,0,0,19,115,1,0,0,0,21,117,1,0,0,0,23,119,1,0,0,0,25,121,1,0,0,0,27,
  	123,1,0,0,0,29,125,1,0,0,0,31,127,1,0,0,0,33,129,1,0,0,0,35,131,1,0,0,
  	0,37,134,1,0,0,0,39,137,1,0,0,0,41,140,1,0,0,0,43,143,1,0,0,0,45,146,
  	1,0,0,0,47,149,1,0,0,0,49,152,1,0,0,0,51,155,1,0,0,0,53,157,1,0,0,0,55,
  	163,1,0,0,0,57,171,1,0,0,0,59,176,1,0,0,0,61,182,1,0,0,0,63,186,1,0,0,
  	0,65,189,1,0,0,0,67,194,1,0,0,0,69,201,1,0,0,0,71,207,1,0,0,0,73,212,
  	1,0,0,0,75,217,1,0,0,0,77,223,1,0,0,0,79,227,1,0,0,0,81,231,1,0,0,0,83,
  	237,1,0,0,0,85,242,1,0,0,0,87,247,1,0,0,0,89,259,1,0,0,0,91,270,1,0,0,
  	0,93,277,1,0,0,0,95,289,1,0,0,0,97,98,5,40,0,0,98,2,1,0,0,0,99,100,5,
  	41,0,0,100,4,1,0,0,0,101,102,5,123,0,0,102,6,1,0,0,0,103,104,5,125,0,
  	0,104,8,1,0,0,0,105,106,5,91,0,0,106,10,1,0,0,0,107,108,5,93,0,0,108,
  	12,1,0,0,0,109,110,5,44,0,0,110,14,1,0,0,0,111,112,5,46,0,0,112,16,1,
  	0,0,0,113,114,5,45,0,0,114,18,1,0,0,0,115,116,5,43,0,0,116,20,1,0,0,0,
  	117,118,5,59,0,0,118,22,1,0,0,0,119,120,5,47,0,0,120,24,1,0,0,0,121,122,
  	5,42,0,0,122,26,1,0,0,0,123,124,5,33,0,0,124,28,1,0,0,0,125,126,5,61,
  	0,0,126,30,1,0,0,0,127,128,5,62,0,0,128,32,1,0,0,0,129,130,5,60,0,0,130,
  	34,1,0,0,0,131,132,5,33,0,0,132,133,5,61,0,0,133,36,1,0,0,0,134,135,5,
  	61,0,0,135,136,5,61,0,0,136,38,1,0,0,0,137,138,5,62,0,0,138,139,5,61,
  	0,0,139,40,1,0,0,0,140,141,5,60,0,0,141,142,5,61,0,0,142,42,1,0,0,0,143,
  	144,5,38,0,0,144,145,5,38,0,0,145,44,1,0,0,0,146,147,5,124,0,0,147,148,
  	5,124,0,0,148,46,1,0,0,0,149,150,5,43,0,0,150,151,5,43,0,0,151,48,1,0,
  	0,0,152,153,5,45,0,0,153,154,5,45,0,0,154,50,1,0,0,0,155,156,5,37,0,0,
  	156,52,1,0,0,0,157,158,5,99,0,0,158,159,5,108,0,0,159,160,5,97,0,0,160,
  	161,5,115,0,0,161,162,5,115,0,0,162,54,1,0,0,0,163,164,5,101,0,0,164,
  	165,5,120,0,0,165,166,5,116,0,0,166,167,5,101,0,0,167,168,5,110,0,0,168,
  	169,5,100,0,0,169,170,5,115,0,0,170,56,1,0,0,0,171,172,5,101,0,0,172,
  	173,5,108,0,0,173,174,5,115,0,0,174,175,5,101,0,0,175,58,1,0,0,0,176,
  	177,5,102,0,0,177,178,5,97,0,0,178,179,5,108,0,0,179,180,5,115,0,0,180,
  	181,5,101,0,0,181,60,1,0,0,0,182,183,5,102,0,0,183,184,5,111,0,0,184,
  	185,5,114,0,0,185,62,1,0,0,0,186,187,5,105,0,0,187,188,5,102,0,0,188,
  	64,1,0,0,0,189,190,5,110,0,0,190,191,5,117,0,0,191,192,5,108,0,0,192,
  	193,5,108,0,0,193,66,1,0,0,0,194,195,5,114,0,0,195,196,5,101,0,0,196,
  	197,5,116,0,0,197,198,5,117,0,0,198,199,5,114,0,0,199,200,5,110,0,0,200,
  	68,1,0,0,0,201,202,5,115,0,0,202,203,5,117,0,0,203,204,5,112,0,0,204,
  	205,5,101,0,0,205,206,5,114,0,0,206,70,1,0,0,0,207,208,5,116,0,0,208,
  	209,5,104,0,0,209,210,5,105,0,0,210,211,5,115,0,0,211,72,1,0,0,0,212,
  	213,5,116,0,0,213,214,5,114,0,0,214,215,5,117,0,0,215,216,5,101,0,0,216,
  	74,1,0,0,0,217,218,5,119,0,0,218,219,5,104,0,0,219,220,5,105,0,0,220,
  	221,5,108,0,0,221,222,5,101,0,0,222,76,1,0,0,0,223,224,5,110,0,0,224,
  	225,5,101,0,0,225,226,5,119,0,0,226,78,1,0,0,0,227,228,5,105,0,0,228,
  	229,5,110,0,0,229,230,5,116,0,0,230,80,1,0,0,0,231,232,5,102,0,0,232,
  	233,5,108,0,0,233,234,5,111,0,0,234,235,5,97,0,0,235,236,5,116,0,0,236,
  	82,1,0,0,0,237,238,5,98,0,0,238,239,5,111,0,0,239,240,5,111,0,0,240,241,
  	5,108,0,0,241,84,1,0,0,0,242,243,5,115,0,0,243,244,5,116,0,0,244,245,
  	5,114,0,0,245,86,1,0,0,0,246,248,7,0,0,0,247,246,1,0,0,0,248,249,1,0,
  	0,0,249,247,1,0,0,0,249,250,1,0,0,0,250,257,1,0,0,0,251,253,5,46,0,0,
  	252,254,7,0,0,0,253,252,1,0,0,0,254,255,1,0,0,0,255,253,1,0,0,0,255,256,
  	1,0,0,0,256,258,1,0,0,0,257,251,1,0,0,0,257,258,1,0,0,0,258,88,1,0,0,
  	0,259,265,5,34,0,0,260,264,8,1,0,0,261,262,5,92,0,0,262,264,9,0,0,0,263,
  	260,1,0,0,0,263,261,1,0,0,0,264,267,1,0,0,0,265,263,1,0,0,0,265,266,1,
  	0,0,0,266,268,1,0,0,0,267,265,1,0,0,0,268,269,5,34,0,0,269,90,1,0,0,0,
  	270,274,7,2,0,0,271,273,7,3,0,0,272,271,1,0,0,0,273,276,1,0,0,0,274,272,
  	1,0,0,0,274,275,1,0,0,0,275,92,1,0,0,0,276,274,1,0,0,0,277,278,5,47,0,
  	0,278,279,5,47,0,0,279,283,1,0,0,0,280,282,8,4,0,0,281,280,1,0,0,0,282,
  	285,1,0,0,0,283,281,1,0,0,0,283,284,1,0,0,0,284,286,1,0,0,0,285,283,1,
  	0,0,0,286,287,6,46,0,0,287,94,1,0,0,0,288,290,7,5,0,0,289,288,1,0,0,0,
  	290,291,1,0,0,0,291,289,1,0,0,0,291,292,1,0,0,0,292,293,1,0,0,0,293,294,
  	6,47,0,0,294,96,1,0,0,0,9,0,249,255,257,263,265,274,283,291,1,6,0,0
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
  return "Pryst.g4";
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
