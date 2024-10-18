
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
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "T__24", 
      "T__25", "T__26", "T__27", "T__28", "T__29", "T__30", "T__31", "T__32", 
      "T__33", "T__34", "T__35", "T__36", "T__37", "T__38", "T__39", "NUMBER", 
      "STRING", "IDENTIFIER", "COMMENT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'='", "';'", "','", "'int'", "'float'", "'bool'", 
      "'str'", "'['", "']'", "'if'", "'else'", "'while'", "'for'", "'return'", 
      "'{'", "'}'", "'.'", "'||'", "'&&'", "'!='", "'=='", "'<'", "'<='", 
      "'>'", "'>='", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'++'", "'--'", 
      "'true'", "'false'", "'null'", "'this'", "'super'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "NUMBER", "STRING", "IDENTIFIER", "COMMENT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,45,271,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,
  	1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,
  	8,1,9,1,9,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,
  	1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,20,1,21,
  	1,21,1,21,1,22,1,22,1,22,1,23,1,23,1,24,1,24,1,24,1,25,1,25,1,26,1,26,
  	1,26,1,27,1,27,1,28,1,28,1,29,1,29,1,30,1,30,1,31,1,31,1,32,1,32,1,33,
  	1,33,1,33,1,34,1,34,1,34,1,35,1,35,1,35,1,35,1,35,1,36,1,36,1,36,1,36,
  	1,36,1,36,1,37,1,37,1,37,1,37,1,37,1,38,1,38,1,38,1,38,1,38,1,39,1,39,
  	1,39,1,39,1,39,1,39,1,40,4,40,224,8,40,11,40,12,40,225,1,40,1,40,4,40,
  	230,8,40,11,40,12,40,231,3,40,234,8,40,1,41,1,41,5,41,238,8,41,10,41,
  	12,41,241,9,41,1,41,1,41,1,42,1,42,5,42,247,8,42,10,42,12,42,250,9,42,
  	1,43,1,43,1,43,1,43,5,43,256,8,43,10,43,12,43,259,9,43,1,43,1,43,1,43,
  	1,43,1,44,4,44,266,8,44,11,44,12,44,267,1,44,1,44,2,239,257,0,45,1,1,
  	3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,
  	15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,
  	53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,
  	38,77,39,79,40,81,41,83,42,85,43,87,44,89,45,1,0,4,1,0,48,57,3,0,65,90,
  	95,95,97,122,4,0,48,57,65,90,95,95,97,122,3,0,9,10,13,13,32,32,277,0,
  	1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,
  	0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,
  	23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,
  	0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,
  	0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,
  	55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,
  	0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,
  	0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,
  	87,1,0,0,0,0,89,1,0,0,0,1,91,1,0,0,0,3,93,1,0,0,0,5,95,1,0,0,0,7,97,1,
  	0,0,0,9,99,1,0,0,0,11,101,1,0,0,0,13,105,1,0,0,0,15,111,1,0,0,0,17,116,
  	1,0,0,0,19,120,1,0,0,0,21,122,1,0,0,0,23,124,1,0,0,0,25,127,1,0,0,0,27,
  	132,1,0,0,0,29,138,1,0,0,0,31,142,1,0,0,0,33,149,1,0,0,0,35,151,1,0,0,
  	0,37,153,1,0,0,0,39,155,1,0,0,0,41,158,1,0,0,0,43,161,1,0,0,0,45,164,
  	1,0,0,0,47,167,1,0,0,0,49,169,1,0,0,0,51,172,1,0,0,0,53,174,1,0,0,0,55,
  	177,1,0,0,0,57,179,1,0,0,0,59,181,1,0,0,0,61,183,1,0,0,0,63,185,1,0,0,
  	0,65,187,1,0,0,0,67,189,1,0,0,0,69,192,1,0,0,0,71,195,1,0,0,0,73,200,
  	1,0,0,0,75,206,1,0,0,0,77,211,1,0,0,0,79,216,1,0,0,0,81,223,1,0,0,0,83,
  	235,1,0,0,0,85,244,1,0,0,0,87,251,1,0,0,0,89,265,1,0,0,0,91,92,5,40,0,
  	0,92,2,1,0,0,0,93,94,5,41,0,0,94,4,1,0,0,0,95,96,5,61,0,0,96,6,1,0,0,
  	0,97,98,5,59,0,0,98,8,1,0,0,0,99,100,5,44,0,0,100,10,1,0,0,0,101,102,
  	5,105,0,0,102,103,5,110,0,0,103,104,5,116,0,0,104,12,1,0,0,0,105,106,
  	5,102,0,0,106,107,5,108,0,0,107,108,5,111,0,0,108,109,5,97,0,0,109,110,
  	5,116,0,0,110,14,1,0,0,0,111,112,5,98,0,0,112,113,5,111,0,0,113,114,5,
  	111,0,0,114,115,5,108,0,0,115,16,1,0,0,0,116,117,5,115,0,0,117,118,5,
  	116,0,0,118,119,5,114,0,0,119,18,1,0,0,0,120,121,5,91,0,0,121,20,1,0,
  	0,0,122,123,5,93,0,0,123,22,1,0,0,0,124,125,5,105,0,0,125,126,5,102,0,
  	0,126,24,1,0,0,0,127,128,5,101,0,0,128,129,5,108,0,0,129,130,5,115,0,
  	0,130,131,5,101,0,0,131,26,1,0,0,0,132,133,5,119,0,0,133,134,5,104,0,
  	0,134,135,5,105,0,0,135,136,5,108,0,0,136,137,5,101,0,0,137,28,1,0,0,
  	0,138,139,5,102,0,0,139,140,5,111,0,0,140,141,5,114,0,0,141,30,1,0,0,
  	0,142,143,5,114,0,0,143,144,5,101,0,0,144,145,5,116,0,0,145,146,5,117,
  	0,0,146,147,5,114,0,0,147,148,5,110,0,0,148,32,1,0,0,0,149,150,5,123,
  	0,0,150,34,1,0,0,0,151,152,5,125,0,0,152,36,1,0,0,0,153,154,5,46,0,0,
  	154,38,1,0,0,0,155,156,5,124,0,0,156,157,5,124,0,0,157,40,1,0,0,0,158,
  	159,5,38,0,0,159,160,5,38,0,0,160,42,1,0,0,0,161,162,5,33,0,0,162,163,
  	5,61,0,0,163,44,1,0,0,0,164,165,5,61,0,0,165,166,5,61,0,0,166,46,1,0,
  	0,0,167,168,5,60,0,0,168,48,1,0,0,0,169,170,5,60,0,0,170,171,5,61,0,0,
  	171,50,1,0,0,0,172,173,5,62,0,0,173,52,1,0,0,0,174,175,5,62,0,0,175,176,
  	5,61,0,0,176,54,1,0,0,0,177,178,5,43,0,0,178,56,1,0,0,0,179,180,5,45,
  	0,0,180,58,1,0,0,0,181,182,5,42,0,0,182,60,1,0,0,0,183,184,5,47,0,0,184,
  	62,1,0,0,0,185,186,5,37,0,0,186,64,1,0,0,0,187,188,5,33,0,0,188,66,1,
  	0,0,0,189,190,5,43,0,0,190,191,5,43,0,0,191,68,1,0,0,0,192,193,5,45,0,
  	0,193,194,5,45,0,0,194,70,1,0,0,0,195,196,5,116,0,0,196,197,5,114,0,0,
  	197,198,5,117,0,0,198,199,5,101,0,0,199,72,1,0,0,0,200,201,5,102,0,0,
  	201,202,5,97,0,0,202,203,5,108,0,0,203,204,5,115,0,0,204,205,5,101,0,
  	0,205,74,1,0,0,0,206,207,5,110,0,0,207,208,5,117,0,0,208,209,5,108,0,
  	0,209,210,5,108,0,0,210,76,1,0,0,0,211,212,5,116,0,0,212,213,5,104,0,
  	0,213,214,5,105,0,0,214,215,5,115,0,0,215,78,1,0,0,0,216,217,5,115,0,
  	0,217,218,5,117,0,0,218,219,5,112,0,0,219,220,5,101,0,0,220,221,5,114,
  	0,0,221,80,1,0,0,0,222,224,7,0,0,0,223,222,1,0,0,0,224,225,1,0,0,0,225,
  	223,1,0,0,0,225,226,1,0,0,0,226,233,1,0,0,0,227,229,5,46,0,0,228,230,
  	7,0,0,0,229,228,1,0,0,0,230,231,1,0,0,0,231,229,1,0,0,0,231,232,1,0,0,
  	0,232,234,1,0,0,0,233,227,1,0,0,0,233,234,1,0,0,0,234,82,1,0,0,0,235,
  	239,5,34,0,0,236,238,9,0,0,0,237,236,1,0,0,0,238,241,1,0,0,0,239,240,
  	1,0,0,0,239,237,1,0,0,0,240,242,1,0,0,0,241,239,1,0,0,0,242,243,5,34,
  	0,0,243,84,1,0,0,0,244,248,7,1,0,0,245,247,7,2,0,0,246,245,1,0,0,0,247,
  	250,1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,86,1,0,0,0,250,248,1,
  	0,0,0,251,252,5,47,0,0,252,253,5,47,0,0,253,257,1,0,0,0,254,256,9,0,0,
  	0,255,254,1,0,0,0,256,259,1,0,0,0,257,258,1,0,0,0,257,255,1,0,0,0,258,
  	260,1,0,0,0,259,257,1,0,0,0,260,261,5,10,0,0,261,262,1,0,0,0,262,263,
  	6,43,0,0,263,88,1,0,0,0,264,266,7,3,0,0,265,264,1,0,0,0,266,267,1,0,0,
  	0,267,265,1,0,0,0,267,268,1,0,0,0,268,269,1,0,0,0,269,270,6,44,0,0,270,
  	90,1,0,0,0,8,0,225,231,233,239,248,257,267,1,6,0,0
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
