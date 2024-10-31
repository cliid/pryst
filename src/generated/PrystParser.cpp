
// Generated from /Users/cliid/dev/pryst/Pryst.g4 by ANTLR 4.13.2


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
      "classMember", "paramList", "param", "type", "statement", "expressionStmt", 
      "ifStmt", "whileStmt", "forStmt", "returnStmt", "block", "expression", 
      "assignment", "logicOr", "logicAnd", "equality", "comparison", "addition", 
      "multiplication", "unary", "postfix", "call", "callSuffix", "primary", 
      "newExpression", "arguments"
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
  	4,1,49,322,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,1,0,5,0,64,8,0,10,0,12,0,67,9,0,1,0,1,0,1,1,1,
  	1,1,1,1,1,3,1,75,8,1,1,2,1,2,1,2,1,2,3,2,81,8,2,1,2,1,2,1,2,1,3,1,3,1,
  	3,1,3,3,3,90,8,3,1,3,1,3,1,4,1,4,1,4,1,4,3,4,98,8,4,1,4,1,4,5,4,102,8,
  	4,10,4,12,4,105,9,4,1,4,1,4,1,5,1,5,3,5,111,8,5,1,6,1,6,1,6,5,6,116,8,
  	6,10,6,12,6,119,9,6,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,131,8,
  	8,1,8,1,8,1,8,5,8,136,8,8,10,8,12,8,139,9,8,1,9,1,9,1,9,1,9,1,9,1,9,3,
  	9,147,8,9,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,159,
  	8,11,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,3,13,172,
  	8,13,1,13,3,13,175,8,13,1,13,1,13,3,13,179,8,13,1,13,1,13,1,13,1,14,1,
  	14,3,14,186,8,14,1,14,1,14,1,15,1,15,5,15,192,8,15,10,15,12,15,195,9,
  	15,1,15,1,15,1,16,1,16,3,16,201,8,16,1,17,1,17,1,17,3,17,206,8,17,1,17,
  	1,17,1,17,1,17,1,18,1,18,1,18,5,18,215,8,18,10,18,12,18,218,9,18,1,19,
  	1,19,1,19,5,19,223,8,19,10,19,12,19,226,9,19,1,20,1,20,1,20,5,20,231,
  	8,20,10,20,12,20,234,9,20,1,21,1,21,1,21,5,21,239,8,21,10,21,12,21,242,
  	9,21,1,22,1,22,1,22,5,22,247,8,22,10,22,12,22,250,9,22,1,23,1,23,1,23,
  	5,23,255,8,23,10,23,12,23,258,9,23,1,24,1,24,1,24,3,24,263,8,24,1,25,
  	1,25,3,25,267,8,25,1,26,1,26,5,26,271,8,26,10,26,12,26,274,9,26,1,27,
  	1,27,3,27,278,8,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,287,8,27,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,
  	28,3,28,304,8,28,1,29,1,29,1,29,1,29,3,29,310,8,29,1,29,1,29,1,30,1,30,
  	1,30,5,30,317,8,30,10,30,12,30,320,9,30,1,30,0,1,16,31,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,0,6,1,0,18,19,2,0,16,17,20,21,1,0,9,10,2,0,12,13,26,26,3,0,9,9,14,
  	14,24,25,1,0,24,25,343,0,65,1,0,0,0,2,74,1,0,0,0,4,76,1,0,0,0,6,85,1,
  	0,0,0,8,93,1,0,0,0,10,110,1,0,0,0,12,112,1,0,0,0,14,120,1,0,0,0,16,130,
  	1,0,0,0,18,146,1,0,0,0,20,148,1,0,0,0,22,151,1,0,0,0,24,160,1,0,0,0,26,
  	166,1,0,0,0,28,183,1,0,0,0,30,189,1,0,0,0,32,200,1,0,0,0,34,205,1,0,0,
  	0,36,211,1,0,0,0,38,219,1,0,0,0,40,227,1,0,0,0,42,235,1,0,0,0,44,243,
  	1,0,0,0,46,251,1,0,0,0,48,262,1,0,0,0,50,264,1,0,0,0,52,268,1,0,0,0,54,
  	286,1,0,0,0,56,303,1,0,0,0,58,305,1,0,0,0,60,313,1,0,0,0,62,64,3,2,1,
  	0,63,62,1,0,0,0,64,67,1,0,0,0,65,63,1,0,0,0,65,66,1,0,0,0,66,68,1,0,0,
  	0,67,65,1,0,0,0,68,69,5,0,0,1,69,1,1,0,0,0,70,75,3,4,2,0,71,75,3,6,3,
  	0,72,75,3,8,4,0,73,75,3,18,9,0,74,70,1,0,0,0,74,71,1,0,0,0,74,72,1,0,
  	0,0,74,73,1,0,0,0,75,3,1,0,0,0,76,77,3,16,8,0,77,78,5,47,0,0,78,80,5,
  	1,0,0,79,81,3,12,6,0,80,79,1,0,0,0,80,81,1,0,0,0,81,82,1,0,0,0,82,83,
  	5,2,0,0,83,84,3,30,15,0,84,5,1,0,0,0,85,86,3,16,8,0,86,89,5,47,0,0,87,
  	88,5,15,0,0,88,90,3,32,16,0,89,87,1,0,0,0,89,90,1,0,0,0,90,91,1,0,0,0,
  	91,92,5,11,0,0,92,7,1,0,0,0,93,94,5,27,0,0,94,97,5,47,0,0,95,96,5,28,
  	0,0,96,98,5,47,0,0,97,95,1,0,0,0,97,98,1,0,0,0,98,99,1,0,0,0,99,103,5,
  	3,0,0,100,102,3,10,5,0,101,100,1,0,0,0,102,105,1,0,0,0,103,101,1,0,0,
  	0,103,104,1,0,0,0,104,106,1,0,0,0,105,103,1,0,0,0,106,107,5,4,0,0,107,
  	9,1,0,0,0,108,111,3,6,3,0,109,111,3,4,2,0,110,108,1,0,0,0,110,109,1,0,
  	0,0,111,11,1,0,0,0,112,117,3,14,7,0,113,114,5,7,0,0,114,116,3,14,7,0,
  	115,113,1,0,0,0,116,119,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,13,
  	1,0,0,0,119,117,1,0,0,0,120,121,3,16,8,0,121,122,5,47,0,0,122,15,1,0,
  	0,0,123,124,6,8,-1,0,124,131,5,40,0,0,125,131,5,41,0,0,126,131,5,42,0,
  	0,127,131,5,43,0,0,128,131,5,44,0,0,129,131,5,47,0,0,130,123,1,0,0,0,
  	130,125,1,0,0,0,130,126,1,0,0,0,130,127,1,0,0,0,130,128,1,0,0,0,130,129,
  	1,0,0,0,131,137,1,0,0,0,132,133,10,1,0,0,133,134,5,5,0,0,134,136,5,6,
  	0,0,135,132,1,0,0,0,136,139,1,0,0,0,137,135,1,0,0,0,137,138,1,0,0,0,138,
  	17,1,0,0,0,139,137,1,0,0,0,140,147,3,20,10,0,141,147,3,22,11,0,142,147,
  	3,24,12,0,143,147,3,26,13,0,144,147,3,28,14,0,145,147,3,30,15,0,146,140,
  	1,0,0,0,146,141,1,0,0,0,146,142,1,0,0,0,146,143,1,0,0,0,146,144,1,0,0,
  	0,146,145,1,0,0,0,147,19,1,0,0,0,148,149,3,32,16,0,149,150,5,11,0,0,150,
  	21,1,0,0,0,151,152,5,32,0,0,152,153,5,1,0,0,153,154,3,32,16,0,154,155,
  	5,2,0,0,155,158,3,18,9,0,156,157,5,29,0,0,157,159,3,18,9,0,158,156,1,
  	0,0,0,158,159,1,0,0,0,159,23,1,0,0,0,160,161,5,38,0,0,161,162,5,1,0,0,
  	162,163,3,32,16,0,163,164,5,2,0,0,164,165,3,18,9,0,165,25,1,0,0,0,166,
  	167,5,31,0,0,167,171,5,1,0,0,168,172,3,6,3,0,169,172,3,20,10,0,170,172,
  	5,11,0,0,171,168,1,0,0,0,171,169,1,0,0,0,171,170,1,0,0,0,172,174,1,0,
  	0,0,173,175,3,32,16,0,174,173,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,
  	176,178,5,11,0,0,177,179,3,32,16,0,178,177,1,0,0,0,178,179,1,0,0,0,179,
  	180,1,0,0,0,180,181,5,2,0,0,181,182,3,18,9,0,182,27,1,0,0,0,183,185,5,
  	34,0,0,184,186,3,32,16,0,185,184,1,0,0,0,185,186,1,0,0,0,186,187,1,0,
  	0,0,187,188,5,11,0,0,188,29,1,0,0,0,189,193,5,3,0,0,190,192,3,2,1,0,191,
  	190,1,0,0,0,192,195,1,0,0,0,193,191,1,0,0,0,193,194,1,0,0,0,194,196,1,
  	0,0,0,195,193,1,0,0,0,196,197,5,4,0,0,197,31,1,0,0,0,198,201,3,34,17,
  	0,199,201,3,36,18,0,200,198,1,0,0,0,200,199,1,0,0,0,201,33,1,0,0,0,202,
  	203,3,52,26,0,203,204,5,8,0,0,204,206,1,0,0,0,205,202,1,0,0,0,205,206,
  	1,0,0,0,206,207,1,0,0,0,207,208,5,47,0,0,208,209,5,15,0,0,209,210,3,32,
  	16,0,210,35,1,0,0,0,211,216,3,38,19,0,212,213,5,23,0,0,213,215,3,38,19,
  	0,214,212,1,0,0,0,215,218,1,0,0,0,216,214,1,0,0,0,216,217,1,0,0,0,217,
  	37,1,0,0,0,218,216,1,0,0,0,219,224,3,40,20,0,220,221,5,22,0,0,221,223,
  	3,40,20,0,222,220,1,0,0,0,223,226,1,0,0,0,224,222,1,0,0,0,224,225,1,0,
  	0,0,225,39,1,0,0,0,226,224,1,0,0,0,227,232,3,42,21,0,228,229,7,0,0,0,
  	229,231,3,42,21,0,230,228,1,0,0,0,231,234,1,0,0,0,232,230,1,0,0,0,232,
  	233,1,0,0,0,233,41,1,0,0,0,234,232,1,0,0,0,235,240,3,44,22,0,236,237,
  	7,1,0,0,237,239,3,44,22,0,238,236,1,0,0,0,239,242,1,0,0,0,240,238,1,0,
  	0,0,240,241,1,0,0,0,241,43,1,0,0,0,242,240,1,0,0,0,243,248,3,46,23,0,
  	244,245,7,2,0,0,245,247,3,46,23,0,246,244,1,0,0,0,247,250,1,0,0,0,248,
  	246,1,0,0,0,248,249,1,0,0,0,249,45,1,0,0,0,250,248,1,0,0,0,251,256,3,
  	48,24,0,252,253,7,3,0,0,253,255,3,48,24,0,254,252,1,0,0,0,255,258,1,0,
  	0,0,256,254,1,0,0,0,256,257,1,0,0,0,257,47,1,0,0,0,258,256,1,0,0,0,259,
  	260,7,4,0,0,260,263,3,48,24,0,261,263,3,50,25,0,262,259,1,0,0,0,262,261,
  	1,0,0,0,263,49,1,0,0,0,264,266,3,56,28,0,265,267,7,5,0,0,266,265,1,0,
  	0,0,266,267,1,0,0,0,267,51,1,0,0,0,268,272,3,56,28,0,269,271,3,54,27,
  	0,270,269,1,0,0,0,271,274,1,0,0,0,272,270,1,0,0,0,272,273,1,0,0,0,273,
  	53,1,0,0,0,274,272,1,0,0,0,275,277,5,1,0,0,276,278,3,60,30,0,277,276,
  	1,0,0,0,277,278,1,0,0,0,278,279,1,0,0,0,279,287,5,2,0,0,280,281,5,5,0,
  	0,281,282,3,32,16,0,282,283,5,6,0,0,283,287,1,0,0,0,284,285,5,8,0,0,285,
  	287,5,47,0,0,286,275,1,0,0,0,286,280,1,0,0,0,286,284,1,0,0,0,287,55,1,
  	0,0,0,288,304,5,37,0,0,289,304,5,30,0,0,290,304,5,33,0,0,291,304,5,36,
  	0,0,292,304,5,45,0,0,293,304,5,46,0,0,294,304,5,47,0,0,295,296,5,1,0,
  	0,296,297,3,32,16,0,297,298,5,2,0,0,298,304,1,0,0,0,299,300,5,35,0,0,
  	300,301,5,8,0,0,301,304,5,47,0,0,302,304,3,58,29,0,303,288,1,0,0,0,303,
  	289,1,0,0,0,303,290,1,0,0,0,303,291,1,0,0,0,303,292,1,0,0,0,303,293,1,
  	0,0,0,303,294,1,0,0,0,303,295,1,0,0,0,303,299,1,0,0,0,303,302,1,0,0,0,
  	304,57,1,0,0,0,305,306,5,39,0,0,306,307,5,47,0,0,307,309,5,1,0,0,308,
  	310,3,60,30,0,309,308,1,0,0,0,309,310,1,0,0,0,310,311,1,0,0,0,311,312,
  	5,2,0,0,312,59,1,0,0,0,313,318,3,32,16,0,314,315,5,7,0,0,315,317,3,32,
  	16,0,316,314,1,0,0,0,317,320,1,0,0,0,318,316,1,0,0,0,318,319,1,0,0,0,
  	319,61,1,0,0,0,320,318,1,0,0,0,33,65,74,80,89,97,103,110,117,130,137,
  	146,158,171,174,178,185,193,200,205,216,224,232,240,248,256,262,266,272,
  	277,286,303,309,318
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
    setState(65);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474087535114) != 0)) {
      setState(62);
      declaration();
      setState(67);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(68);
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
    setState(74);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(70);
      functionDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(71);
      variableDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(72);
      classDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(73);
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
    setState(76);
    type(0);
    setState(77);
    match(PrystParser::IDENTIFIER);
    setState(78);
    match(PrystParser::LPAREN);
    setState(80);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 174822348816384) != 0)) {
      setState(79);
      paramList();
    }
    setState(82);
    match(PrystParser::RPAREN);
    setState(83);
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
    setState(85);
    type(0);
    setState(86);
    match(PrystParser::IDENTIFIER);
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EQUAL) {
      setState(87);
      match(PrystParser::EQUAL);
      setState(88);
      expression();
    }
    setState(91);
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

tree::TerminalNode* PrystParser::ClassDeclarationContext::LBRACE() {
  return getToken(PrystParser::LBRACE, 0);
}

tree::TerminalNode* PrystParser::ClassDeclarationContext::RBRACE() {
  return getToken(PrystParser::RBRACE, 0);
}

tree::TerminalNode* PrystParser::ClassDeclarationContext::EXTENDS() {
  return getToken(PrystParser::EXTENDS, 0);
}

std::vector<PrystParser::ClassMemberContext *> PrystParser::ClassDeclarationContext::classMember() {
  return getRuleContexts<PrystParser::ClassMemberContext>();
}

PrystParser::ClassMemberContext* PrystParser::ClassDeclarationContext::classMember(size_t i) {
  return getRuleContext<PrystParser::ClassMemberContext>(i);
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
    setState(93);
    match(PrystParser::CLASS);
    setState(94);
    match(PrystParser::IDENTIFIER);
    setState(97);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::EXTENDS) {
      setState(95);
      match(PrystParser::EXTENDS);
      setState(96);
      match(PrystParser::IDENTIFIER);
    }
    setState(99);
    match(PrystParser::LBRACE);
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 174822348816384) != 0)) {
      setState(100);
      classMember();
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(106);
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

PrystParser::VariableDeclContext* PrystParser::ClassMemberContext::variableDecl() {
  return getRuleContext<PrystParser::VariableDeclContext>(0);
}

PrystParser::FunctionDeclContext* PrystParser::ClassMemberContext::functionDecl() {
  return getRuleContext<PrystParser::FunctionDeclContext>(0);
}


size_t PrystParser::ClassMemberContext::getRuleIndex() const {
  return PrystParser::RuleClassMember;
}


std::any PrystParser::ClassMemberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitClassMember(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::ClassMemberContext* PrystParser::classMember() {
  ClassMemberContext *_localctx = _tracker.createInstance<ClassMemberContext>(_ctx, getState());
  enterRule(_localctx, 10, PrystParser::RuleClassMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(110);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(108);
      variableDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(109);
      functionDecl();
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
  enterRule(_localctx, 12, PrystParser::RuleParamList);
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
    setState(112);
    param();
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(113);
      match(PrystParser::COMMA);
      setState(114);
      param();
      setState(119);
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
  enterRule(_localctx, 14, PrystParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    type(0);
    setState(121);
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
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, PrystParser::RuleType, precedence);

    

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
    setState(130);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::INT: {
        setState(124);
        match(PrystParser::INT);
        break;
      }

      case PrystParser::FLOAT: {
        setState(125);
        match(PrystParser::FLOAT);
        break;
      }

      case PrystParser::BOOL: {
        setState(126);
        match(PrystParser::BOOL);
        break;
      }

      case PrystParser::STR: {
        setState(127);
        match(PrystParser::STR);
        break;
      }

      case PrystParser::VOID: {
        setState(128);
        match(PrystParser::VOID);
        break;
      }

      case PrystParser::IDENTIFIER: {
        setState(129);
        match(PrystParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(137);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(132);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(133);
        match(PrystParser::LBRACKET);
        setState(134);
        match(PrystParser::RBRACKET); 
      }
      setState(139);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
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
  enterRule(_localctx, 18, PrystParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(146);
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
        enterOuterAlt(_localctx, 1);
        setState(140);
        expressionStmt();
        break;
      }

      case PrystParser::IF: {
        enterOuterAlt(_localctx, 2);
        setState(141);
        ifStmt();
        break;
      }

      case PrystParser::WHILE: {
        enterOuterAlt(_localctx, 3);
        setState(142);
        whileStmt();
        break;
      }

      case PrystParser::FOR: {
        enterOuterAlt(_localctx, 4);
        setState(143);
        forStmt();
        break;
      }

      case PrystParser::RETURN: {
        enterOuterAlt(_localctx, 5);
        setState(144);
        returnStmt();
        break;
      }

      case PrystParser::LBRACE: {
        enterOuterAlt(_localctx, 6);
        setState(145);
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

tree::TerminalNode* PrystParser::ExpressionStmtContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
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
  enterRule(_localctx, 20, PrystParser::RuleExpressionStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    expression();
    setState(149);
    match(PrystParser::SEMICOLON);
   
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

tree::TerminalNode* PrystParser::IfStmtContext::IF() {
  return getToken(PrystParser::IF, 0);
}

tree::TerminalNode* PrystParser::IfStmtContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

PrystParser::ExpressionContext* PrystParser::IfStmtContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::IfStmtContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
}

std::vector<PrystParser::StatementContext *> PrystParser::IfStmtContext::statement() {
  return getRuleContexts<PrystParser::StatementContext>();
}

PrystParser::StatementContext* PrystParser::IfStmtContext::statement(size_t i) {
  return getRuleContext<PrystParser::StatementContext>(i);
}

tree::TerminalNode* PrystParser::IfStmtContext::ELSE() {
  return getToken(PrystParser::ELSE, 0);
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
  enterRule(_localctx, 22, PrystParser::RuleIfStmt);

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
    match(PrystParser::IF);
    setState(152);
    match(PrystParser::LPAREN);
    setState(153);
    expression();
    setState(154);
    match(PrystParser::RPAREN);
    setState(155);
    statement();
    setState(158);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(156);
      match(PrystParser::ELSE);
      setState(157);
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

tree::TerminalNode* PrystParser::WhileStmtContext::WHILE() {
  return getToken(PrystParser::WHILE, 0);
}

tree::TerminalNode* PrystParser::WhileStmtContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

PrystParser::ExpressionContext* PrystParser::WhileStmtContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::WhileStmtContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
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
  enterRule(_localctx, 24, PrystParser::RuleWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(PrystParser::WHILE);
    setState(161);
    match(PrystParser::LPAREN);
    setState(162);
    expression();
    setState(163);
    match(PrystParser::RPAREN);
    setState(164);
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

tree::TerminalNode* PrystParser::ForStmtContext::FOR() {
  return getToken(PrystParser::FOR, 0);
}

tree::TerminalNode* PrystParser::ForStmtContext::LPAREN() {
  return getToken(PrystParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> PrystParser::ForStmtContext::SEMICOLON() {
  return getTokens(PrystParser::SEMICOLON);
}

tree::TerminalNode* PrystParser::ForStmtContext::SEMICOLON(size_t i) {
  return getToken(PrystParser::SEMICOLON, i);
}

tree::TerminalNode* PrystParser::ForStmtContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
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
  enterRule(_localctx, 26, PrystParser::RuleForStmt);
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
    match(PrystParser::FOR);
    setState(167);
    match(PrystParser::LPAREN);
    setState(171);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(168);
      variableDecl();
      break;
    }

    case 2: {
      setState(169);
      expressionStmt();
      break;
    }

    case 3: {
      setState(170);
      match(PrystParser::SEMICOLON);
      break;
    }

    default:
      break;
    }
    setState(174);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 247090592629250) != 0)) {
      setState(173);
      expression();
    }
    setState(176);
    match(PrystParser::SEMICOLON);
    setState(178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 247090592629250) != 0)) {
      setState(177);
      expression();
    }
    setState(180);
    match(PrystParser::RPAREN);
    setState(181);
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

tree::TerminalNode* PrystParser::ReturnStmtContext::RETURN() {
  return getToken(PrystParser::RETURN, 0);
}

tree::TerminalNode* PrystParser::ReturnStmtContext::SEMICOLON() {
  return getToken(PrystParser::SEMICOLON, 0);
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
  enterRule(_localctx, 28, PrystParser::RuleReturnStmt);
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
    setState(183);
    match(PrystParser::RETURN);
    setState(185);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 247090592629250) != 0)) {
      setState(184);
      expression();
    }
    setState(187);
    match(PrystParser::SEMICOLON);
   
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
  if (auto parserVisitor = dynamic_cast<PrystVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

PrystParser::BlockContext* PrystParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 30, PrystParser::RuleBlock);
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
    match(PrystParser::LBRACE);
    setState(193);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474087535114) != 0)) {
      setState(190);
      declaration();
      setState(195);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(196);
    match(PrystParser::RBRACE);
   
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
  enterRule(_localctx, 32, PrystParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(200);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(198);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(199);
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
  enterRule(_localctx, 34, PrystParser::RuleAssignment);

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
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(202);
      call();
      setState(203);
      match(PrystParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(207);
    match(PrystParser::IDENTIFIER);
    setState(208);
    match(PrystParser::EQUAL);
    setState(209);
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
  enterRule(_localctx, 36, PrystParser::RuleLogicOr);
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
    setState(211);
    logicAnd();
    setState(216);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::OR) {
      setState(212);
      match(PrystParser::OR);
      setState(213);
      logicAnd();
      setState(218);
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
  enterRule(_localctx, 38, PrystParser::RuleLogicAnd);
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
    setState(219);
    equality();
    setState(224);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::AND) {
      setState(220);
      match(PrystParser::AND);
      setState(221);
      equality();
      setState(226);
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
  enterRule(_localctx, 40, PrystParser::RuleEquality);
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
    setState(227);
    comparison();
    setState(232);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::NOT_EQUAL

    || _la == PrystParser::EQUAL_EQUAL) {
      setState(228);
      _la = _input->LA(1);
      if (!(_la == PrystParser::NOT_EQUAL

      || _la == PrystParser::EQUAL_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(229);
      comparison();
      setState(234);
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
  enterRule(_localctx, 42, PrystParser::RuleComparison);
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
    setState(235);
    addition();
    setState(240);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3342336) != 0)) {
      setState(236);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3342336) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(237);
      addition();
      setState(242);
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
  enterRule(_localctx, 44, PrystParser::RuleAddition);
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
    setState(243);
    multiplication();
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::MINUS

    || _la == PrystParser::PLUS) {
      setState(244);
      _la = _input->LA(1);
      if (!(_la == PrystParser::MINUS

      || _la == PrystParser::PLUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(245);
      multiplication();
      setState(250);
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
  enterRule(_localctx, 46, PrystParser::RuleMultiplication);
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
    setState(251);
    unary();
    setState(256);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67121152) != 0)) {
      setState(252);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 67121152) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(253);
      unary();
      setState(258);
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
  enterRule(_localctx, 48, PrystParser::RuleUnary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::MINUS:
      case PrystParser::BANG:
      case PrystParser::INCREMENT:
      case PrystParser::DECREMENT: {
        enterOuterAlt(_localctx, 1);
        setState(259);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 50348544) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(260);
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
        setState(261);
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
  enterRule(_localctx, 50, PrystParser::RulePostfix);
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
    primary();
    setState(266);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrystParser::INCREMENT

    || _la == PrystParser::DECREMENT) {
      setState(265);
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

std::vector<PrystParser::CallSuffixContext *> PrystParser::CallContext::callSuffix() {
  return getRuleContexts<PrystParser::CallSuffixContext>();
}

PrystParser::CallSuffixContext* PrystParser::CallContext::callSuffix(size_t i) {
  return getRuleContext<PrystParser::CallSuffixContext>(i);
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
  enterRule(_localctx, 52, PrystParser::RuleCall);

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
    setState(268);
    primary();
    setState(272);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(269);
        callSuffix(); 
      }
      setState(274);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
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

tree::TerminalNode* PrystParser::CallSuffixContext::LBRACKET() {
  return getToken(PrystParser::LBRACKET, 0);
}

PrystParser::ExpressionContext* PrystParser::CallSuffixContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::CallSuffixContext::RBRACKET() {
  return getToken(PrystParser::RBRACKET, 0);
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
  enterRule(_localctx, 54, PrystParser::RuleCallSuffix);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(286);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(275);
        match(PrystParser::LPAREN);
        setState(277);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 247090592629250) != 0)) {
          setState(276);
          arguments();
        }
        setState(279);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::LBRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(280);
        match(PrystParser::LBRACKET);
        setState(281);
        expression();
        setState(282);
        match(PrystParser::RBRACKET);
        break;
      }

      case PrystParser::DOT: {
        enterOuterAlt(_localctx, 3);
        setState(284);
        match(PrystParser::DOT);
        setState(285);
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

PrystParser::ExpressionContext* PrystParser::PrimaryContext::expression() {
  return getRuleContext<PrystParser::ExpressionContext>(0);
}

tree::TerminalNode* PrystParser::PrimaryContext::RPAREN() {
  return getToken(PrystParser::RPAREN, 0);
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
  enterRule(_localctx, 56, PrystParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(303);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrystParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(288);
        match(PrystParser::TRUE);
        break;
      }

      case PrystParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(289);
        match(PrystParser::FALSE);
        break;
      }

      case PrystParser::NULL_: {
        enterOuterAlt(_localctx, 3);
        setState(290);
        match(PrystParser::NULL_);
        break;
      }

      case PrystParser::THIS: {
        enterOuterAlt(_localctx, 4);
        setState(291);
        match(PrystParser::THIS);
        break;
      }

      case PrystParser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(292);
        match(PrystParser::NUMBER);
        break;
      }

      case PrystParser::STRING: {
        enterOuterAlt(_localctx, 6);
        setState(293);
        match(PrystParser::STRING);
        break;
      }

      case PrystParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 7);
        setState(294);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::LPAREN: {
        enterOuterAlt(_localctx, 8);
        setState(295);
        match(PrystParser::LPAREN);
        setState(296);
        expression();
        setState(297);
        match(PrystParser::RPAREN);
        break;
      }

      case PrystParser::SUPER: {
        enterOuterAlt(_localctx, 9);
        setState(299);
        match(PrystParser::SUPER);
        setState(300);
        match(PrystParser::DOT);
        setState(301);
        match(PrystParser::IDENTIFIER);
        break;
      }

      case PrystParser::NEW: {
        enterOuterAlt(_localctx, 10);
        setState(302);
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
  enterRule(_localctx, 58, PrystParser::RuleNewExpression);
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
    setState(305);
    match(PrystParser::NEW);
    setState(306);
    match(PrystParser::IDENTIFIER);
    setState(307);
    match(PrystParser::LPAREN);
    setState(309);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 247090592629250) != 0)) {
      setState(308);
      arguments();
    }
    setState(311);
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
  enterRule(_localctx, 60, PrystParser::RuleArguments);
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
    setState(313);
    expression();
    setState(318);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrystParser::COMMA) {
      setState(314);
      match(PrystParser::COMMA);
      setState(315);
      expression();
      setState(320);
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
    case 8: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

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
