
// Generated from /home/ubuntu/pryst/Pryst.g4 by ANTLR 4.13.2


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
      "AND", "OR", "INCREMENT", "DECREMENT", "PERCENT", "ARROW", "CLASS", 
      "EXTENDS", "ELSE", "FALSE", "FOR", "IF", "NULL", "RETURN", "SUPER", 
      "THIS", "TRUE", "WHILE", "NEW", "CONVERT", "INT", "FLOAT", "BOOL", 
      "STR", "VOID", "NUMBER", "STRING", "IDENTIFIER", "COMMENT", "WS"
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
  	4,0,51,317,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,
  	6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,
  	1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,17,1,18,1,18,1,18,1,19,1,19,1,19,
  	1,20,1,20,1,20,1,21,1,21,1,21,1,22,1,22,1,22,1,23,1,23,1,23,1,24,1,24,
  	1,24,1,25,1,25,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,1,28,1,28,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,30,
  	1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,33,1,33,1,33,1,33,
  	1,33,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,35,1,35,1,35,1,35,1,35,1,35,
  	1,36,1,36,1,36,1,36,1,36,1,37,1,37,1,37,1,37,1,37,1,38,1,38,1,38,1,38,
  	1,38,1,38,1,39,1,39,1,39,1,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,
  	1,41,1,41,1,41,1,41,1,42,1,42,1,42,1,42,1,42,1,42,1,43,1,43,1,43,1,43,
  	1,43,1,44,1,44,1,44,1,44,1,45,1,45,1,45,1,45,1,45,1,46,4,46,270,8,46,
  	11,46,12,46,271,1,46,1,46,4,46,276,8,46,11,46,12,46,277,3,46,280,8,46,
  	1,47,1,47,1,47,1,47,5,47,286,8,47,10,47,12,47,289,9,47,1,47,1,47,1,48,
  	1,48,5,48,295,8,48,10,48,12,48,298,9,48,1,49,1,49,1,49,1,49,5,49,304,
  	8,49,10,49,12,49,307,9,49,1,49,1,49,1,50,4,50,312,8,50,11,50,12,50,313,
  	1,50,1,50,0,0,51,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,
  	23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,
  	23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,
  	69,35,71,36,73,37,75,38,77,39,79,40,81,41,83,42,85,43,87,44,89,45,91,
  	46,93,47,95,48,97,49,99,50,101,51,1,0,6,1,0,48,57,4,0,10,10,13,13,34,
  	34,92,92,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,2,0,10,10,
  	13,13,3,0,9,10,13,13,32,32,324,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,
  	7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,
  	0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,
  	0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,
  	1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,
  	0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,
  	0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,
  	1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,
  	0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,
  	0,93,1,0,0,0,0,95,1,0,0,0,0,97,1,0,0,0,0,99,1,0,0,0,0,101,1,0,0,0,1,103,
  	1,0,0,0,3,105,1,0,0,0,5,107,1,0,0,0,7,109,1,0,0,0,9,111,1,0,0,0,11,113,
  	1,0,0,0,13,115,1,0,0,0,15,117,1,0,0,0,17,119,1,0,0,0,19,121,1,0,0,0,21,
  	123,1,0,0,0,23,125,1,0,0,0,25,127,1,0,0,0,27,129,1,0,0,0,29,131,1,0,0,
  	0,31,133,1,0,0,0,33,135,1,0,0,0,35,137,1,0,0,0,37,140,1,0,0,0,39,143,
  	1,0,0,0,41,146,1,0,0,0,43,149,1,0,0,0,45,152,1,0,0,0,47,155,1,0,0,0,49,
  	158,1,0,0,0,51,161,1,0,0,0,53,163,1,0,0,0,55,166,1,0,0,0,57,172,1,0,0,
  	0,59,180,1,0,0,0,61,185,1,0,0,0,63,191,1,0,0,0,65,195,1,0,0,0,67,198,
  	1,0,0,0,69,203,1,0,0,0,71,210,1,0,0,0,73,216,1,0,0,0,75,221,1,0,0,0,77,
  	226,1,0,0,0,79,232,1,0,0,0,81,236,1,0,0,0,83,244,1,0,0,0,85,248,1,0,0,
  	0,87,254,1,0,0,0,89,259,1,0,0,0,91,263,1,0,0,0,93,269,1,0,0,0,95,281,
  	1,0,0,0,97,292,1,0,0,0,99,299,1,0,0,0,101,311,1,0,0,0,103,104,5,40,0,
  	0,104,2,1,0,0,0,105,106,5,41,0,0,106,4,1,0,0,0,107,108,5,123,0,0,108,
  	6,1,0,0,0,109,110,5,125,0,0,110,8,1,0,0,0,111,112,5,91,0,0,112,10,1,0,
  	0,0,113,114,5,93,0,0,114,12,1,0,0,0,115,116,5,44,0,0,116,14,1,0,0,0,117,
  	118,5,46,0,0,118,16,1,0,0,0,119,120,5,45,0,0,120,18,1,0,0,0,121,122,5,
  	43,0,0,122,20,1,0,0,0,123,124,5,59,0,0,124,22,1,0,0,0,125,126,5,47,0,
  	0,126,24,1,0,0,0,127,128,5,42,0,0,128,26,1,0,0,0,129,130,5,33,0,0,130,
  	28,1,0,0,0,131,132,5,61,0,0,132,30,1,0,0,0,133,134,5,62,0,0,134,32,1,
  	0,0,0,135,136,5,60,0,0,136,34,1,0,0,0,137,138,5,33,0,0,138,139,5,61,0,
  	0,139,36,1,0,0,0,140,141,5,61,0,0,141,142,5,61,0,0,142,38,1,0,0,0,143,
  	144,5,62,0,0,144,145,5,61,0,0,145,40,1,0,0,0,146,147,5,60,0,0,147,148,
  	5,61,0,0,148,42,1,0,0,0,149,150,5,38,0,0,150,151,5,38,0,0,151,44,1,0,
  	0,0,152,153,5,124,0,0,153,154,5,124,0,0,154,46,1,0,0,0,155,156,5,43,0,
  	0,156,157,5,43,0,0,157,48,1,0,0,0,158,159,5,45,0,0,159,160,5,45,0,0,160,
  	50,1,0,0,0,161,162,5,37,0,0,162,52,1,0,0,0,163,164,5,61,0,0,164,165,5,
  	62,0,0,165,54,1,0,0,0,166,167,5,99,0,0,167,168,5,108,0,0,168,169,5,97,
  	0,0,169,170,5,115,0,0,170,171,5,115,0,0,171,56,1,0,0,0,172,173,5,101,
  	0,0,173,174,5,120,0,0,174,175,5,116,0,0,175,176,5,101,0,0,176,177,5,110,
  	0,0,177,178,5,100,0,0,178,179,5,115,0,0,179,58,1,0,0,0,180,181,5,101,
  	0,0,181,182,5,108,0,0,182,183,5,115,0,0,183,184,5,101,0,0,184,60,1,0,
  	0,0,185,186,5,102,0,0,186,187,5,97,0,0,187,188,5,108,0,0,188,189,5,115,
  	0,0,189,190,5,101,0,0,190,62,1,0,0,0,191,192,5,102,0,0,192,193,5,111,
  	0,0,193,194,5,114,0,0,194,64,1,0,0,0,195,196,5,105,0,0,196,197,5,102,
  	0,0,197,66,1,0,0,0,198,199,5,110,0,0,199,200,5,117,0,0,200,201,5,108,
  	0,0,201,202,5,108,0,0,202,68,1,0,0,0,203,204,5,114,0,0,204,205,5,101,
  	0,0,205,206,5,116,0,0,206,207,5,117,0,0,207,208,5,114,0,0,208,209,5,110,
  	0,0,209,70,1,0,0,0,210,211,5,115,0,0,211,212,5,117,0,0,212,213,5,112,
  	0,0,213,214,5,101,0,0,214,215,5,114,0,0,215,72,1,0,0,0,216,217,5,116,
  	0,0,217,218,5,104,0,0,218,219,5,105,0,0,219,220,5,115,0,0,220,74,1,0,
  	0,0,221,222,5,116,0,0,222,223,5,114,0,0,223,224,5,117,0,0,224,225,5,101,
  	0,0,225,76,1,0,0,0,226,227,5,119,0,0,227,228,5,104,0,0,228,229,5,105,
  	0,0,229,230,5,108,0,0,230,231,5,101,0,0,231,78,1,0,0,0,232,233,5,110,
  	0,0,233,234,5,101,0,0,234,235,5,119,0,0,235,80,1,0,0,0,236,237,5,99,0,
  	0,237,238,5,111,0,0,238,239,5,110,0,0,239,240,5,118,0,0,240,241,5,101,
  	0,0,241,242,5,114,0,0,242,243,5,116,0,0,243,82,1,0,0,0,244,245,5,105,
  	0,0,245,246,5,110,0,0,246,247,5,116,0,0,247,84,1,0,0,0,248,249,5,102,
  	0,0,249,250,5,108,0,0,250,251,5,111,0,0,251,252,5,97,0,0,252,253,5,116,
  	0,0,253,86,1,0,0,0,254,255,5,98,0,0,255,256,5,111,0,0,256,257,5,111,0,
  	0,257,258,5,108,0,0,258,88,1,0,0,0,259,260,5,115,0,0,260,261,5,116,0,
  	0,261,262,5,114,0,0,262,90,1,0,0,0,263,264,5,118,0,0,264,265,5,111,0,
  	0,265,266,5,105,0,0,266,267,5,100,0,0,267,92,1,0,0,0,268,270,7,0,0,0,
  	269,268,1,0,0,0,270,271,1,0,0,0,271,269,1,0,0,0,271,272,1,0,0,0,272,279,
  	1,0,0,0,273,275,5,46,0,0,274,276,7,0,0,0,275,274,1,0,0,0,276,277,1,0,
  	0,0,277,275,1,0,0,0,277,278,1,0,0,0,278,280,1,0,0,0,279,273,1,0,0,0,279,
  	280,1,0,0,0,280,94,1,0,0,0,281,287,5,34,0,0,282,286,8,1,0,0,283,284,5,
  	92,0,0,284,286,9,0,0,0,285,282,1,0,0,0,285,283,1,0,0,0,286,289,1,0,0,
  	0,287,285,1,0,0,0,287,288,1,0,0,0,288,290,1,0,0,0,289,287,1,0,0,0,290,
  	291,5,34,0,0,291,96,1,0,0,0,292,296,7,2,0,0,293,295,7,3,0,0,294,293,1,
  	0,0,0,295,298,1,0,0,0,296,294,1,0,0,0,296,297,1,0,0,0,297,98,1,0,0,0,
  	298,296,1,0,0,0,299,300,5,47,0,0,300,301,5,47,0,0,301,305,1,0,0,0,302,
  	304,8,4,0,0,303,302,1,0,0,0,304,307,1,0,0,0,305,303,1,0,0,0,305,306,1,
  	0,0,0,306,308,1,0,0,0,307,305,1,0,0,0,308,309,6,49,0,0,309,100,1,0,0,
  	0,310,312,7,5,0,0,311,310,1,0,0,0,312,313,1,0,0,0,313,311,1,0,0,0,313,
  	314,1,0,0,0,314,315,1,0,0,0,315,316,6,50,0,0,316,102,1,0,0,0,9,0,271,
  	277,279,285,287,296,305,313,1,6,0,0
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
