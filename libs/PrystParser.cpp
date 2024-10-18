
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
      "program", "declaration", "functionDecl", "variableDecl", "paramList", 
      "param", "type", "statement", "expressionStmt", "ifStmt", "whileStmt", 
      "forStmt", "returnStmt", "block", "expression", "assignment", "logicOr", 
      "logicAnd", "equality", "comparison", "addition", "multiplication", 
      "unary", "postfix", "call", "primary", "arguments"
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
  	4,1,45,280,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,1,0,5,0,56,8,0,10,
  	0,12,0,59,9,0,1,0,1,0,1,1,1,1,1,1,3,1,66,8,1,1,2,1,2,1,2,1,2,3,2,72,8,
  	2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,3,3,81,8,3,1,3,1,3,1,4,1,4,1,4,5,4,88,8,
  	4,10,4,12,4,91,9,4,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,3,6,101,8,6,1,6,1,
  	6,1,6,5,6,106,8,6,10,6,12,6,109,9,6,1,7,1,7,1,7,1,7,1,7,1,7,3,7,117,8,
  	7,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,129,8,9,1,10,1,10,1,10,
  	1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,3,11,142,8,11,1,11,3,11,145,8,
  	11,1,11,1,11,3,11,149,8,11,1,11,1,11,1,11,1,12,1,12,3,12,156,8,12,1,12,
  	1,12,1,13,1,13,5,13,162,8,13,10,13,12,13,165,9,13,1,13,1,13,1,14,1,14,
  	1,15,1,15,1,15,3,15,174,8,15,1,15,1,15,1,15,1,15,3,15,180,8,15,1,16,1,
  	16,1,16,5,16,185,8,16,10,16,12,16,188,9,16,1,17,1,17,1,17,5,17,193,8,
  	17,10,17,12,17,196,9,17,1,18,1,18,1,18,5,18,201,8,18,10,18,12,18,204,
  	9,18,1,19,1,19,1,19,5,19,209,8,19,10,19,12,19,212,9,19,1,20,1,20,1,20,
  	5,20,217,8,20,10,20,12,20,220,9,20,1,21,1,21,1,21,5,21,225,8,21,10,21,
  	12,21,228,9,21,1,22,1,22,1,22,3,22,233,8,22,1,23,1,23,3,23,237,8,23,1,
  	24,1,24,1,24,3,24,242,8,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,5,24,251,
  	8,24,10,24,12,24,254,9,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,
  	1,25,1,25,1,25,1,25,1,25,3,25,270,8,25,1,26,1,26,1,26,5,26,275,8,26,10,
  	26,12,26,278,9,26,1,26,0,1,12,27,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,52,0,6,1,0,22,23,1,0,24,27,1,0,28,
  	29,1,0,30,32,2,0,29,29,33,35,1,0,34,35,297,0,57,1,0,0,0,2,65,1,0,0,0,
  	4,67,1,0,0,0,6,76,1,0,0,0,8,84,1,0,0,0,10,92,1,0,0,0,12,100,1,0,0,0,14,
  	116,1,0,0,0,16,118,1,0,0,0,18,121,1,0,0,0,20,130,1,0,0,0,22,136,1,0,0,
  	0,24,153,1,0,0,0,26,159,1,0,0,0,28,168,1,0,0,0,30,179,1,0,0,0,32,181,
  	1,0,0,0,34,189,1,0,0,0,36,197,1,0,0,0,38,205,1,0,0,0,40,213,1,0,0,0,42,
  	221,1,0,0,0,44,232,1,0,0,0,46,234,1,0,0,0,48,238,1,0,0,0,50,269,1,0,0,
  	0,52,271,1,0,0,0,54,56,3,2,1,0,55,54,1,0,0,0,56,59,1,0,0,0,57,55,1,0,
  	0,0,57,58,1,0,0,0,58,60,1,0,0,0,59,57,1,0,0,0,60,61,5,0,0,1,61,1,1,0,
  	0,0,62,66,3,4,2,0,63,66,3,6,3,0,64,66,3,14,7,0,65,62,1,0,0,0,65,63,1,
  	0,0,0,65,64,1,0,0,0,66,3,1,0,0,0,67,68,3,12,6,0,68,69,5,43,0,0,69,71,
  	5,1,0,0,70,72,3,8,4,0,71,70,1,0,0,0,71,72,1,0,0,0,72,73,1,0,0,0,73,74,
  	5,2,0,0,74,75,3,26,13,0,75,5,1,0,0,0,76,77,3,12,6,0,77,80,5,43,0,0,78,
  	79,5,3,0,0,79,81,3,28,14,0,80,78,1,0,0,0,80,81,1,0,0,0,81,82,1,0,0,0,
  	82,83,5,4,0,0,83,7,1,0,0,0,84,89,3,10,5,0,85,86,5,5,0,0,86,88,3,10,5,
  	0,87,85,1,0,0,0,88,91,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,9,1,0,0,
  	0,91,89,1,0,0,0,92,93,3,12,6,0,93,94,5,43,0,0,94,11,1,0,0,0,95,96,6,6,
  	-1,0,96,101,5,6,0,0,97,101,5,7,0,0,98,101,5,8,0,0,99,101,5,9,0,0,100,
  	95,1,0,0,0,100,97,1,0,0,0,100,98,1,0,0,0,100,99,1,0,0,0,101,107,1,0,0,
  	0,102,103,10,1,0,0,103,104,5,10,0,0,104,106,5,11,0,0,105,102,1,0,0,0,
  	106,109,1,0,0,0,107,105,1,0,0,0,107,108,1,0,0,0,108,13,1,0,0,0,109,107,
  	1,0,0,0,110,117,3,16,8,0,111,117,3,18,9,0,112,117,3,20,10,0,113,117,3,
  	22,11,0,114,117,3,24,12,0,115,117,3,26,13,0,116,110,1,0,0,0,116,111,1,
  	0,0,0,116,112,1,0,0,0,116,113,1,0,0,0,116,114,1,0,0,0,116,115,1,0,0,0,
  	117,15,1,0,0,0,118,119,3,28,14,0,119,120,5,4,0,0,120,17,1,0,0,0,121,122,
  	5,12,0,0,122,123,5,1,0,0,123,124,3,28,14,0,124,125,5,2,0,0,125,128,3,
  	14,7,0,126,127,5,13,0,0,127,129,3,14,7,0,128,126,1,0,0,0,128,129,1,0,
  	0,0,129,19,1,0,0,0,130,131,5,14,0,0,131,132,5,1,0,0,132,133,3,28,14,0,
  	133,134,5,2,0,0,134,135,3,14,7,0,135,21,1,0,0,0,136,137,5,15,0,0,137,
  	141,5,1,0,0,138,142,3,6,3,0,139,142,3,16,8,0,140,142,5,4,0,0,141,138,
  	1,0,0,0,141,139,1,0,0,0,141,140,1,0,0,0,142,144,1,0,0,0,143,145,3,28,
  	14,0,144,143,1,0,0,0,144,145,1,0,0,0,145,146,1,0,0,0,146,148,5,4,0,0,
  	147,149,3,28,14,0,148,147,1,0,0,0,148,149,1,0,0,0,149,150,1,0,0,0,150,
  	151,5,2,0,0,151,152,3,14,7,0,152,23,1,0,0,0,153,155,5,16,0,0,154,156,
  	3,28,14,0,155,154,1,0,0,0,155,156,1,0,0,0,156,157,1,0,0,0,157,158,5,4,
  	0,0,158,25,1,0,0,0,159,163,5,17,0,0,160,162,3,2,1,0,161,160,1,0,0,0,162,
  	165,1,0,0,0,163,161,1,0,0,0,163,164,1,0,0,0,164,166,1,0,0,0,165,163,1,
  	0,0,0,166,167,5,18,0,0,167,27,1,0,0,0,168,169,3,30,15,0,169,29,1,0,0,
  	0,170,171,3,48,24,0,171,172,5,19,0,0,172,174,1,0,0,0,173,170,1,0,0,0,
  	173,174,1,0,0,0,174,175,1,0,0,0,175,176,5,43,0,0,176,177,5,3,0,0,177,
  	180,3,30,15,0,178,180,3,32,16,0,179,173,1,0,0,0,179,178,1,0,0,0,180,31,
  	1,0,0,0,181,186,3,34,17,0,182,183,5,20,0,0,183,185,3,34,17,0,184,182,
  	1,0,0,0,185,188,1,0,0,0,186,184,1,0,0,0,186,187,1,0,0,0,187,33,1,0,0,
  	0,188,186,1,0,0,0,189,194,3,36,18,0,190,191,5,21,0,0,191,193,3,36,18,
  	0,192,190,1,0,0,0,193,196,1,0,0,0,194,192,1,0,0,0,194,195,1,0,0,0,195,
  	35,1,0,0,0,196,194,1,0,0,0,197,202,3,38,19,0,198,199,7,0,0,0,199,201,
  	3,38,19,0,200,198,1,0,0,0,201,204,1,0,0,0,202,200,1,0,0,0,202,203,1,0,
  	0,0,203,37,1,0,0,0,204,202,1,0,0,0,205,210,3,40,20,0,206,207,7,1,0,0,
  	207,209,3,40,20,0,208,206,1,0,0,0,209,212,1,0,0,0,210,208,1,0,0,0,210,
  	211,1,0,0,0,211,39,1,0,0,0,212,210,1,0,0,0,213,218,3,42,21,0,214,215,
  	7,2,0,0,215,217,3,42,21,0,216,214,1,0,0,0,217,220,1,0,0,0,218,216,1,0,
  	0,0,218,219,1,0,0,0,219,41,1,0,0,0,220,218,1,0,0,0,221,226,3,44,22,0,
  	222,223,7,3,0,0,223,225,3,44,22,0,224,222,1,0,0,0,225,228,1,0,0,0,226,
  	224,1,0,0,0,226,227,1,0,0,0,227,43,1,0,0,0,228,226,1,0,0,0,229,230,7,
  	4,0,0,230,233,3,44,22,0,231,233,3,46,23,0,232,229,1,0,0,0,232,231,1,0,
  	0,0,233,45,1,0,0,0,234,236,3,50,25,0,235,237,7,5,0,0,236,235,1,0,0,0,
  	236,237,1,0,0,0,237,47,1,0,0,0,238,252,3,50,25,0,239,241,5,1,0,0,240,
  	242,3,52,26,0,241,240,1,0,0,0,241,242,1,0,0,0,242,243,1,0,0,0,243,251,
  	5,2,0,0,244,245,5,10,0,0,245,246,3,28,14,0,246,247,5,11,0,0,247,251,1,
  	0,0,0,248,249,5,19,0,0,249,251,5,43,0,0,250,239,1,0,0,0,250,244,1,0,0,
  	0,250,248,1,0,0,0,251,254,1,0,0,0,252,250,1,0,0,0,252,253,1,0,0,0,253,
  	49,1,0,0,0,254,252,1,0,0,0,255,270,5,36,0,0,256,270,5,37,0,0,257,270,
  	5,38,0,0,258,270,5,39,0,0,259,270,5,41,0,0,260,270,5,42,0,0,261,270,5,
  	43,0,0,262,263,5,1,0,0,263,264,3,28,14,0,264,265,5,2,0,0,265,270,1,0,
  	0,0,266,267,5,40,0,0,267,268,5,19,0,0,268,270,5,43,0,0,269,255,1,0,0,
  	0,269,256,1,0,0,0,269,257,1,0,0,0,269,258,1,0,0,0,269,259,1,0,0,0,269,
  	260,1,0,0,0,269,261,1,0,0,0,269,262,1,0,0,0,269,266,1,0,0,0,270,51,1,
  	0,0,0,271,276,3,28,14,0,272,273,5,5,0,0,273,275,3,28,14,0,274,272,1,0,
  	0,0,275,278,1,0,0,0,276,274,1,0,0,0,276,277,1,0,0,0,277,53,1,0,0,0,278,
  	276,1,0,0,0,29,57,65,71,80,89,100,107,116,128,141,144,148,155,163,173,
  	179,186,194,202,210,218,226,232,236,241,250,252,269,276
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
    setState(57);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17584133231554) != 0)) {
      setState(54);
      declaration();
      setState(59);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(60);
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
    setState(65);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(62);
      functionDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(63);
      variableDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(64);
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

PrystParser::BlockContext* PrystParser::FunctionDeclContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
}

PrystParser::ParamListContext* PrystParser::FunctionDeclContext::paramList() {
  return getRuleContext<PrystParser::ParamListContext>(0);
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
    setState(67);
    type(0);
    setState(68);
    match(PrystParser::IDENTIFIER);
    setState(69);
    match(PrystParser::T__0);
    setState(71);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 960) != 0)) {
      setState(70);
      paramList();
    }
    setState(73);
    match(PrystParser::T__1);
    setState(74);
    block();
   
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
    setState(76);
    type(0);
    setState(77);
    match(PrystParser::IDENTIFIER);
    setState(80);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::T__2) {
      setState(78);
      match(PrystParser::T__2);
      setState(79);
      expression();
    }
    setState(82);
    match(PrystParser::T__3);
   
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
  enterRule(_localctx, 8, PrystParser::RuleParamList);
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
    setState(84);
    param();
    setState(89);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::T__4) {
      setState(85);
      match(PrystParser::T__4);
      setState(86);
      param();
      setState(91);
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
  enterRule(_localctx, 10, PrystParser::RuleParam);

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
    type(0);
    setState(93);
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

PrystParser::TypeContext* PrystParser::TypeContext::type() {
  return getRuleContext<PrystParser::TypeContext>(0);
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
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, PrystParser::RuleType, precedence);

    

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
    setState(100);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::T__5: {
        setState(96);
        match(PrystParser::T__5);
        break;
      }

      case PrystParser::T__6: {
        setState(97);
        match(PrystParser::T__6);
        break;
      }

      case PrystParser::T__7: {
        setState(98);
        match(PrystParser::T__7);
        break;
      }

      case PrystParser::T__8: {
        setState(99);
        match(PrystParser::T__8);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(107);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(102);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(103);
        match(PrystParser::T__9);
        setState(104);
        match(PrystParser::T__10); 
      }
      setState(109);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
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

PrystParser::ExpressionStmtContext* PrystParser::StatementContext::expressionStmt() {
  return getRuleContext<PrystParser::ExpressionStmtContext>(0);
}

PrystParser::IfStmtContext* PrystParser::StatementContext::ifStmt() {
  return getRuleContext<PrystParser::IfStmtContext>(0);
}

PrystParser::WhileStmtContext* PrystParser::StatementContext::whileStmt() {
  return getRuleContext<PrystParser::WhileStmtContext>(0);
}

PrystParser::ForStmtContext* PrystParser::StatementContext::forStmt() {
  return getRuleContext<PrystParser::ForStmtContext>(0);
}

PrystParser::ReturnStmtContext* PrystParser::StatementContext::returnStmt() {
  return getRuleContext<PrystParser::ReturnStmtContext>(0);
}

PrystParser::BlockContext* PrystParser::StatementContext::block() {
  return getRuleContext<PrystParser::BlockContext>(0);
}


size_t PrystParser::StatementContext::getRuleIndex() const {
  return PrystParser::RuleStatement;
}


std::any PrystParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::StatementContext* PrystParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 14, PrystParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(116);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::T__0:
      case PrystParser::T__28:
      case PrystParser::T__32:
      case PrystParser::T__33:
      case PrystParser::T__34:
      case PrystParser::T__35:
      case PrystParser::T__36:
      case PrystParser::T__37:
      case PrystParser::T__38:
      case PrystParser::T__39:
      case PrystParser::NUMBER:
      case PrystParser::STRING:
      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(110);
        expressionStmt();
        break;
      }

      case PrystParser::T__11: {
        enterOuterAlt(_localctx, 2);
        setState(111);
        ifStmt();
        break;
      }

      case PrystParser::T__13: {
        enterOuterAlt(_localctx, 3);
        setState(112);
        whileStmt();
        break;
      }

      case PrystParser::T__14: {
        enterOuterAlt(_localctx, 4);
        setState(113);
        forStmt();
        break;
      }

      case PrystParser::T__15: {
        enterOuterAlt(_localctx, 5);
        setState(114);
        returnStmt();
        break;
      }

      case PrystParser::T__16: {
        enterOuterAlt(_localctx, 6);
        setState(115);
        block();
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

//----------------- ExpressionStmtContext ------------------------------------------------------------------

PrystParser::ExpressionStmtContext::ExpressionStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::ExpressionContext* PrystParser::ExpressionStmtContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}


size_t PrystParser::ExpressionStmtContext::getRuleIndex() const {
  return PrystParser::RuleExpressionStmt;
}


std::any PrystParser::ExpressionStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitExpressionStmt(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ExpressionStmtContext* PrystParser::expressionStmt() {
  ExpressionStmtContext *_localctx = _tracker.createInstance<ExpressionStmtContext>(_ctx, getState());
  enterRule(_localctx, 16, PrystParser::RuleExpressionStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    expression();
    setState(119);
    match(PrystParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStmtContext ------------------------------------------------------------------

PrystParser::IfStmtContext::IfStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::ExpressionContext* PrystParser::IfStmtContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

std::vector<PrystParser::StatementContext *> PrystParser::IfStmtContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::IfStmtContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}


size_t PrystParser::IfStmtContext::getRuleIndex() const {
  return PrystParser::RuleIfStmt;
}


std::any PrystParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::IfStmtContext* PrystParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 18, PrystParser::RuleIfStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(PrystParser::T__11);
    setState(122);
    match(PrystParser::T__0);
    setState(123);
    expression();
    setState(124);
    match(PrystParser::T__1);
    setState(125);
    statement();
    setState(128);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(126);
      match(PrystParser::T__12);
      setState(127);
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

//----------------- WhileStmtContext ------------------------------------------------------------------

PrystParser::WhileStmtContext::WhileStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::ExpressionContext* PrystParser::WhileStmtContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

PrystParser::StatementContext* PrystParser::WhileStmtContext::statement() {
  return getRuleContext<PrystParser::StatementContext>(0);
}


size_t PrystParser::WhileStmtContext::getRuleIndex() const {
  return PrystParser::RuleWhileStmt;
}


std::any PrystParser::WhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitWhileStmt(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::WhileStmtContext* PrystParser::whileStmt() {
  WhileStmtContext *_localctx = _tracker.createInstance<WhileStmtContext>(_ctx, getState());
  enterRule(_localctx, 20, PrystParser::RuleWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(PrystParser::T__13);
    setState(131);
    match(PrystParser::T__0);
    setState(132);
    expression();
    setState(133);
    match(PrystParser::T__1);
    setState(134);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStmtContext ------------------------------------------------------------------

PrystParser::ForStmtContext::ForStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::StatementContext* PrystParser::ForStmtContext::statement() {
  return getRuleContext<PrystParser::StatementContext>(0);
}

PrystParser::VariableDeclContext* PrystParser::ForStmtContext::variableDecl() {
  return getRuleContext<PrystParser::VariableDeclContext>(0);
}

PrystParser::ExpressionStmtContext* PrystParser::ForStmtContext::expressionStmt() {
  return getRuleContext<PrystParser::ExpressionStmtContext>(0);
}

std::vector<PrystParser::ExpressionContext *> PrystParser::ForStmtContext::expression() {
  return getRuleContexts<PrystParser::ExpressionContext>();
}

PrystParser::ExpressionContext* PrystParser::ForStmtContext::expression(size_t i) {
  return getRuleContext<PrystParser::ExpressionContext>(i);
}


size_t PrystParser::ForStmtContext::getRuleIndex() const {
  return PrystParser::RuleForStmt;
}


std::any PrystParser::ForStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitForStmt(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ForStmtContext* PrystParser::forStmt() {
  ForStmtContext *_localctx = _tracker.createInstance<ForStmtContext>(_ctx, getState());
  enterRule(_localctx, 22, PrystParser::RuleForStmt);
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
    setState(136);
    match(PrystParser::T__14);
    setState(137);
    match(PrystParser::T__0);
    setState(141);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::T__5:
      case PrystParser::T__6:
      case PrystParser::T__7:
      case PrystParser::T__8: {
        setState(138);
        variableDecl();
        break;
      }

      case PrystParser::T__0:
      case PrystParser::T__28:
      case PrystParser::T__32:
      case PrystParser::T__33:
      case PrystParser::T__34:
      case PrystParser::T__35:
      case PrystParser::T__36:
      case PrystParser::T__37:
      case PrystParser::T__38:
      case PrystParser::T__39:
      case PrystParser::NUMBER:
      case PrystParser::STRING:
      case PrystParser::IDENTIFIER: {
        setState(139);
        expressionStmt();
        break;
      }

      case PrystParser::T__3: {
        setState(140);
        match(PrystParser::T__3);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(144);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17584132980738) != 0)) {
      setState(143);
      expression();
    }
    setState(146);
    match(PrystParser::T__3);
    setState(148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17584132980738) != 0)) {
      setState(147);
      expression();
    }
    setState(150);
    match(PrystParser::T__1);
    setState(151);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStmtContext ------------------------------------------------------------------

PrystParser::ReturnStmtContext::ReturnStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PrystParser::ExpressionContext* PrystParser::ReturnStmtContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}


size_t PrystParser::ReturnStmtContext::getRuleIndex() const {
  return PrystParser::RuleReturnStmt;
}


std::any PrystParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ReturnStmtContext* PrystParser::returnStmt() {
  ReturnStmtContext *_localctx = _tracker.createInstance<ReturnStmtContext>(_ctx, getState());
  enterRule(_localctx, 24, PrystParser::RuleReturnStmt);
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
    setState(153);
    match(PrystParser::T__15);
    setState(155);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17584132980738) != 0)) {
      setState(154);
      expression();
    }
    setState(157);
    match(PrystParser::T__3);
   
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
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::BlockContext* PrystParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 26, PrystParser::RuleBlock);
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
    setState(159);
    match(PrystParser::T__16);
    setState(163);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17584133231554) != 0)) {
      setState(160);
      declaration();
      setState(165);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(166);
    match(PrystParser::T__17);
   
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
  enterRule(_localctx, 28, PrystParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    assignment();
   
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

PrystParser::AssignmentContext* PrystParser::AssignmentContext::assignment() {
  return getRuleContext<PrystParser::AssignmentContext>(0);
}

PrystParser::CallContext* PrystParser::AssignmentContext::call() {
  return getRuleContext<PrystParser::CallContext>(0);
}

PrystParser::LogicOrContext* PrystParser::AssignmentContext::logicOr() {
  return getRuleContext<PrystParser::LogicOrContext>(0);
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
  enterRule(_localctx, 30, PrystParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(179);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(173);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(170);
        call();
        setState(171);
        match(PrystParser::T__18);
        break;
      }

      default:
        break;
      }
      setState(175);
      match(PrystParser::IDENTIFIER);
      setState(176);
      match(PrystParser::T__2);
      setState(177);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(178);
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
  enterRule(_localctx, 32, PrystParser::RuleLogicOr);
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
    setState(181);
    logicAnd();
    setState(186);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::T__19) {
      setState(182);
      match(PrystParser::T__19);
      setState(183);
      logicAnd();
      setState(188);
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
  enterRule(_localctx, 34, PrystParser::RuleLogicAnd);
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
    setState(189);
    equality();
    setState(194);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::T__20) {
      setState(190);
      match(PrystParser::T__20);
      setState(191);
      equality();
      setState(196);
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
  enterRule(_localctx, 36, PrystParser::RuleEquality);
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
    setState(197);
    comparison();
    setState(202);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::T__21

    || _la == PrystParser::T__22) {
      setState(198);
      _la = _input->LA(1);
      if (!(_la == PrystParser::T__21

      || _la == PrystParser::T__22)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(199);
      comparison();
      setState(204);
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
  enterRule(_localctx, 38, PrystParser::RuleComparison);
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
    setState(205);
    addition();
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 251658240) != 0)) {
      setState(206);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 251658240) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(207);
      addition();
      setState(212);
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
  enterRule(_localctx, 40, PrystParser::RuleAddition);
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
    setState(213);
    multiplication();
    setState(218);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::T__27

    || _la == PrystParser::T__28) {
      setState(214);
      _la = _input->LA(1);
      if (!(_la == PrystParser::T__27

      || _la == PrystParser::T__28)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(215);
      multiplication();
      setState(220);
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
  enterRule(_localctx, 42, PrystParser::RuleMultiplication);
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
    setState(221);
    unary();
    setState(226);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7516192768) != 0)) {
      setState(222);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 7516192768) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(223);
      unary();
      setState(228);
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
  enterRule(_localctx, 44, PrystParser::RuleUnary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::T__28:
      case PrystParser::T__32:
      case PrystParser::T__33:
      case PrystParser::T__34: {
        enterOuterAlt(_localctx, 1);
        setState(229);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 60666413056) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(230);
        unary();
        break;
      }

      case PrystParser::T__0:
      case PrystParser::T__35:
      case PrystParser::T__36:
      case PrystParser::T__37:
      case PrystParser::T__38:
      case PrystParser::T__39:
      case PrystParser::NUMBER:
      case PrystParser::STRING:
      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(231);
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
  enterRule(_localctx, 46, PrystParser::RulePostfix);
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
    setState(234);
    primary();
    setState(236);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::T__33

    || _la == PrystParser::T__34) {
      setState(235);
      _la = _input->LA(1);
      if (!(_la == PrystParser::T__33

      || _la == PrystParser::T__34)) {
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

std::vector<PrystParser::ExpressionContext *> PrystParser::CallContext::expression() {
  return getRuleContexts<PrystParser::ExpressionContext>();
}

PrystParser::ExpressionContext* PrystParser::CallContext::expression(size_t i) {
  return getRuleContext<PrystParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> PrystParser::CallContext::IDENTIFIER() {
  return getTokens(PrystParser::IDENTIFIER);
}

tree::TerminalNode* PrystParser::CallContext::IDENTIFIER(size_t i) {
  return getToken(PrystParser::IDENTIFIER, i);
}

std::vector<PrystParser::ArgumentsContext *> PrystParser::CallContext::arguments() {
  return getRuleContexts<PrystParser::ArgumentsContext>();
}

PrystParser::ArgumentsContext* PrystParser::CallContext::arguments(size_t i) {
  return getRuleContext<PrystParser::ArgumentsContext>(i);
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
  enterRule(_localctx, 48, PrystParser::RuleCall);
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
    setState(238);
    primary();
    setState(252);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(250);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PrystParser::T__0: {
            setState(239);
            match(PrystParser::T__0);
            setState(241);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~ 0x3fULL) == 0) &&
              ((1ULL << _la) & 17584132980738) != 0)) {
              setState(240);
              arguments();
            }
            setState(243);
            match(PrystParser::T__1);
            break;
          }

          case PrystParser::T__9: {
            setState(244);
            match(PrystParser::T__9);
            setState(245);
            expression();
            setState(246);
            match(PrystParser::T__10);
            break;
          }

          case PrystParser::T__18: {
            setState(248);
            match(PrystParser::T__18);
            setState(249);
            match(PrystParser::IDENTIFIER);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(254);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
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

tree::TerminalNode* PrystParser::PrimaryContext::NUMBER() {
  return getToken(PrystParser::NUMBER, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::STRING() {
  return getToken(PrystParser::STRING, 0);
}

tree::TerminalNode* PrystParser::PrimaryContext::IDENTIFIER() {
  return getToken(PrystParser::IDENTIFIER, 0);
}

PrystParser::ExpressionContext* PrystParser::PrimaryContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
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
  enterRule(_localctx, 50, PrystParser::RulePrimary);

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
    switch (_input->LA(1)) {
      case PrystParser::T__35: {
        enterOuterAlt(_localctx, 1);
        setState(255);
        match(PrystParser::T__35);
        break;
      }

      case PrystParser::T__36: {
        enterOuterAlt(_localctx, 2);
        setState(256);
        match(PrystParser::T__36);
        break;
      }

      case PrystParser::T__37: {
        enterOuterAlt(_localctx, 3);
        setState(257);
        match(PrystParser::T__37);
        break;
      }

      case PrystParser::T__38: {
        enterOuterAlt(_localctx, 4);
        setState(258);
        match(PrystParser::T__38);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(259);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::STRING: {
        enterOuterAlt(_localctx, 6);
        setState(260);
        match(PrystParser::STRING);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 7);
        setState(261);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::T__0: {
        enterOuterAlt(_localctx, 8);
        setState(262);
        match(PrystParser::T__0);
        setState(263);
        expression();
        setState(264);
        match(PrystParser::T__1);
        break;
      }

      case PrystParser::T__39: {
        enterOuterAlt(_localctx, 9);
        setState(266);
        match(PrystParser::T__39);
        setState(267);
        match(PrystParser::T__18);
        setState(268);
        match(PrystParser::IDENTIFIER);
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
  enterRule(_localctx, 52, PrystParser::RuleArguments);
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
    expression();
    setState(276);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::T__4) {
      setState(272);
      match(PrystParser::T__4);
      setState(273);
      expression();
      setState(278);
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
    case 6: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

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
