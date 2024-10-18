// Generated from /Users/cliid/dev/pryst/Pryst.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class PrystParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, T__30=31, 
		T__31=32, T__32=33, T__33=34, T__34=35, T__35=36, T__36=37, T__37=38, 
		T__38=39, T__39=40, NUMBER=41, STRING=42, IDENTIFIER=43, COMMENT=44, WS=45;
	public static final int
		RULE_program = 0, RULE_declaration = 1, RULE_functionDecl = 2, RULE_variableDecl = 3, 
		RULE_paramList = 4, RULE_param = 5, RULE_type = 6, RULE_statement = 7, 
		RULE_expressionStmt = 8, RULE_ifStmt = 9, RULE_whileStmt = 10, RULE_forStmt = 11, 
		RULE_returnStmt = 12, RULE_block = 13, RULE_expression = 14, RULE_assignment = 15, 
		RULE_logicOr = 16, RULE_logicAnd = 17, RULE_equality = 18, RULE_comparison = 19, 
		RULE_addition = 20, RULE_multiplication = 21, RULE_unary = 22, RULE_postfix = 23, 
		RULE_call = 24, RULE_primary = 25, RULE_arguments = 26;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "declaration", "functionDecl", "variableDecl", "paramList", 
			"param", "type", "statement", "expressionStmt", "ifStmt", "whileStmt", 
			"forStmt", "returnStmt", "block", "expression", "assignment", "logicOr", 
			"logicAnd", "equality", "comparison", "addition", "multiplication", "unary", 
			"postfix", "call", "primary", "arguments"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "')'", "'='", "';'", "','", "'int'", "'float'", "'bool'", 
			"'str'", "'['", "']'", "'if'", "'else'", "'while'", "'for'", "'return'", 
			"'{'", "'}'", "'.'", "'||'", "'&&'", "'!='", "'=='", "'<'", "'<='", "'>'", 
			"'>='", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'++'", "'--'", "'true'", 
			"'false'", "'null'", "'this'", "'super'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, "NUMBER", "STRING", "IDENTIFIER", "COMMENT", 
			"WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Pryst.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public PrystParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(PrystParser.EOF, 0); }
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitProgram(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(57);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__5) | (1L << T__6) | (1L << T__7) | (1L << T__8) | (1L << T__11) | (1L << T__13) | (1L << T__14) | (1L << T__15) | (1L << T__16) | (1L << T__28) | (1L << T__32) | (1L << T__33) | (1L << T__34) | (1L << T__35) | (1L << T__36) | (1L << T__37) | (1L << T__38) | (1L << T__39) | (1L << NUMBER) | (1L << STRING) | (1L << IDENTIFIER))) != 0)) {
				{
				{
				setState(54);
				declaration();
				}
				}
				setState(59);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(60);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclarationContext extends ParserRuleContext {
		public FunctionDeclContext functionDecl() {
			return getRuleContext(FunctionDeclContext.class,0);
		}
		public VariableDeclContext variableDecl() {
			return getRuleContext(VariableDeclContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public DeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitDeclaration(this);
		}
	}

	public final DeclarationContext declaration() throws RecognitionException {
		DeclarationContext _localctx = new DeclarationContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_declaration);
		try {
			setState(65);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(62);
				functionDecl();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(63);
				variableDecl();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(64);
				statement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionDeclContext extends ParserRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(PrystParser.IDENTIFIER, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public ParamListContext paramList() {
			return getRuleContext(ParamListContext.class,0);
		}
		public FunctionDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionDecl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterFunctionDecl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitFunctionDecl(this);
		}
	}

	public final FunctionDeclContext functionDecl() throws RecognitionException {
		FunctionDeclContext _localctx = new FunctionDeclContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_functionDecl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(67);
			type(0);
			setState(68);
			match(IDENTIFIER);
			setState(69);
			match(T__0);
			setState(71);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__5) | (1L << T__6) | (1L << T__7) | (1L << T__8))) != 0)) {
				{
				setState(70);
				paramList();
				}
			}

			setState(73);
			match(T__1);
			setState(74);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VariableDeclContext extends ParserRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(PrystParser.IDENTIFIER, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public VariableDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDecl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterVariableDecl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitVariableDecl(this);
		}
	}

	public final VariableDeclContext variableDecl() throws RecognitionException {
		VariableDeclContext _localctx = new VariableDeclContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_variableDecl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(76);
			type(0);
			setState(77);
			match(IDENTIFIER);
			setState(80);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__2) {
				{
				setState(78);
				match(T__2);
				setState(79);
				expression();
				}
			}

			setState(82);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ParamListContext extends ParserRuleContext {
		public List<ParamContext> param() {
			return getRuleContexts(ParamContext.class);
		}
		public ParamContext param(int i) {
			return getRuleContext(ParamContext.class,i);
		}
		public ParamListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_paramList; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterParamList(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitParamList(this);
		}
	}

	public final ParamListContext paramList() throws RecognitionException {
		ParamListContext _localctx = new ParamListContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_paramList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(84);
			param();
			setState(89);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__4) {
				{
				{
				setState(85);
				match(T__4);
				setState(86);
				param();
				}
				}
				setState(91);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ParamContext extends ParserRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(PrystParser.IDENTIFIER, 0); }
		public ParamContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_param; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterParam(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitParam(this);
		}
	}

	public final ParamContext param() throws RecognitionException {
		ParamContext _localctx = new ParamContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_param);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(92);
			type(0);
			setState(93);
			match(IDENTIFIER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TypeContext extends ParserRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitType(this);
		}
	}

	public final TypeContext type() throws RecognitionException {
		return type(0);
	}

	private TypeContext type(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		TypeContext _localctx = new TypeContext(_ctx, _parentState);
		TypeContext _prevctx = _localctx;
		int _startState = 12;
		enterRecursionRule(_localctx, 12, RULE_type, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(100);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__5:
				{
				setState(96);
				match(T__5);
				}
				break;
			case T__6:
				{
				setState(97);
				match(T__6);
				}
				break;
			case T__7:
				{
				setState(98);
				match(T__7);
				}
				break;
			case T__8:
				{
				setState(99);
				match(T__8);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			_ctx.stop = _input.LT(-1);
			setState(107);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new TypeContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_type);
					setState(102);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(103);
					match(T__9);
					setState(104);
					match(T__10);
					}
					} 
				}
				setState(109);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class StatementContext extends ParserRuleContext {
		public ExpressionStmtContext expressionStmt() {
			return getRuleContext(ExpressionStmtContext.class,0);
		}
		public IfStmtContext ifStmt() {
			return getRuleContext(IfStmtContext.class,0);
		}
		public WhileStmtContext whileStmt() {
			return getRuleContext(WhileStmtContext.class,0);
		}
		public ForStmtContext forStmt() {
			return getRuleContext(ForStmtContext.class,0);
		}
		public ReturnStmtContext returnStmt() {
			return getRuleContext(ReturnStmtContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitStatement(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_statement);
		try {
			setState(116);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__0:
			case T__28:
			case T__32:
			case T__33:
			case T__34:
			case T__35:
			case T__36:
			case T__37:
			case T__38:
			case T__39:
			case NUMBER:
			case STRING:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(110);
				expressionStmt();
				}
				break;
			case T__11:
				enterOuterAlt(_localctx, 2);
				{
				setState(111);
				ifStmt();
				}
				break;
			case T__13:
				enterOuterAlt(_localctx, 3);
				{
				setState(112);
				whileStmt();
				}
				break;
			case T__14:
				enterOuterAlt(_localctx, 4);
				{
				setState(113);
				forStmt();
				}
				break;
			case T__15:
				enterOuterAlt(_localctx, 5);
				{
				setState(114);
				returnStmt();
				}
				break;
			case T__16:
				enterOuterAlt(_localctx, 6);
				{
				setState(115);
				block();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionStmtContext extends ParserRuleContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public ExpressionStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expressionStmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterExpressionStmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitExpressionStmt(this);
		}
	}

	public final ExpressionStmtContext expressionStmt() throws RecognitionException {
		ExpressionStmtContext _localctx = new ExpressionStmtContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_expressionStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(118);
			expression();
			setState(119);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IfStmtContext extends ParserRuleContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public IfStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifStmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterIfStmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitIfStmt(this);
		}
	}

	public final IfStmtContext ifStmt() throws RecognitionException {
		IfStmtContext _localctx = new IfStmtContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_ifStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			match(T__11);
			setState(122);
			match(T__0);
			setState(123);
			expression();
			setState(124);
			match(T__1);
			setState(125);
			statement();
			setState(128);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				{
				setState(126);
				match(T__12);
				setState(127);
				statement();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class WhileStmtContext extends ParserRuleContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public WhileStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_whileStmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterWhileStmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitWhileStmt(this);
		}
	}

	public final WhileStmtContext whileStmt() throws RecognitionException {
		WhileStmtContext _localctx = new WhileStmtContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_whileStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(130);
			match(T__13);
			setState(131);
			match(T__0);
			setState(132);
			expression();
			setState(133);
			match(T__1);
			setState(134);
			statement();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ForStmtContext extends ParserRuleContext {
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public VariableDeclContext variableDecl() {
			return getRuleContext(VariableDeclContext.class,0);
		}
		public ExpressionStmtContext expressionStmt() {
			return getRuleContext(ExpressionStmtContext.class,0);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public ForStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forStmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterForStmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitForStmt(this);
		}
	}

	public final ForStmtContext forStmt() throws RecognitionException {
		ForStmtContext _localctx = new ForStmtContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_forStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(136);
			match(T__14);
			setState(137);
			match(T__0);
			setState(141);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__5:
			case T__6:
			case T__7:
			case T__8:
				{
				setState(138);
				variableDecl();
				}
				break;
			case T__0:
			case T__28:
			case T__32:
			case T__33:
			case T__34:
			case T__35:
			case T__36:
			case T__37:
			case T__38:
			case T__39:
			case NUMBER:
			case STRING:
			case IDENTIFIER:
				{
				setState(139);
				expressionStmt();
				}
				break;
			case T__3:
				{
				setState(140);
				match(T__3);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(144);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__28) | (1L << T__32) | (1L << T__33) | (1L << T__34) | (1L << T__35) | (1L << T__36) | (1L << T__37) | (1L << T__38) | (1L << T__39) | (1L << NUMBER) | (1L << STRING) | (1L << IDENTIFIER))) != 0)) {
				{
				setState(143);
				expression();
				}
			}

			setState(146);
			match(T__3);
			setState(148);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__28) | (1L << T__32) | (1L << T__33) | (1L << T__34) | (1L << T__35) | (1L << T__36) | (1L << T__37) | (1L << T__38) | (1L << T__39) | (1L << NUMBER) | (1L << STRING) | (1L << IDENTIFIER))) != 0)) {
				{
				setState(147);
				expression();
				}
			}

			setState(150);
			match(T__1);
			setState(151);
			statement();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ReturnStmtContext extends ParserRuleContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public ReturnStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_returnStmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterReturnStmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitReturnStmt(this);
		}
	}

	public final ReturnStmtContext returnStmt() throws RecognitionException {
		ReturnStmtContext _localctx = new ReturnStmtContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_returnStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(153);
			match(T__15);
			setState(155);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__28) | (1L << T__32) | (1L << T__33) | (1L << T__34) | (1L << T__35) | (1L << T__36) | (1L << T__37) | (1L << T__38) | (1L << T__39) | (1L << NUMBER) | (1L << STRING) | (1L << IDENTIFIER))) != 0)) {
				{
				setState(154);
				expression();
				}
			}

			setState(157);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BlockContext extends ParserRuleContext {
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitBlock(this);
		}
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(159);
			match(T__16);
			setState(163);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__5) | (1L << T__6) | (1L << T__7) | (1L << T__8) | (1L << T__11) | (1L << T__13) | (1L << T__14) | (1L << T__15) | (1L << T__16) | (1L << T__28) | (1L << T__32) | (1L << T__33) | (1L << T__34) | (1L << T__35) | (1L << T__36) | (1L << T__37) | (1L << T__38) | (1L << T__39) | (1L << NUMBER) | (1L << STRING) | (1L << IDENTIFIER))) != 0)) {
				{
				{
				setState(160);
				declaration();
				}
				}
				setState(165);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(166);
			match(T__17);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionContext extends ParserRuleContext {
		public AssignmentContext assignment() {
			return getRuleContext(AssignmentContext.class,0);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitExpression(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(168);
			assignment();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AssignmentContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(PrystParser.IDENTIFIER, 0); }
		public AssignmentContext assignment() {
			return getRuleContext(AssignmentContext.class,0);
		}
		public CallContext call() {
			return getRuleContext(CallContext.class,0);
		}
		public LogicOrContext logicOr() {
			return getRuleContext(LogicOrContext.class,0);
		}
		public AssignmentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterAssignment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitAssignment(this);
		}
	}

	public final AssignmentContext assignment() throws RecognitionException {
		AssignmentContext _localctx = new AssignmentContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_assignment);
		try {
			setState(179);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(173);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
				case 1:
					{
					setState(170);
					call();
					setState(171);
					match(T__18);
					}
					break;
				}
				setState(175);
				match(IDENTIFIER);
				setState(176);
				match(T__2);
				setState(177);
				assignment();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(178);
				logicOr();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LogicOrContext extends ParserRuleContext {
		public List<LogicAndContext> logicAnd() {
			return getRuleContexts(LogicAndContext.class);
		}
		public LogicAndContext logicAnd(int i) {
			return getRuleContext(LogicAndContext.class,i);
		}
		public LogicOrContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logicOr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterLogicOr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitLogicOr(this);
		}
	}

	public final LogicOrContext logicOr() throws RecognitionException {
		LogicOrContext _localctx = new LogicOrContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_logicOr);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(181);
			logicAnd();
			setState(186);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__19) {
				{
				{
				setState(182);
				match(T__19);
				setState(183);
				logicAnd();
				}
				}
				setState(188);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LogicAndContext extends ParserRuleContext {
		public List<EqualityContext> equality() {
			return getRuleContexts(EqualityContext.class);
		}
		public EqualityContext equality(int i) {
			return getRuleContext(EqualityContext.class,i);
		}
		public LogicAndContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logicAnd; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterLogicAnd(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitLogicAnd(this);
		}
	}

	public final LogicAndContext logicAnd() throws RecognitionException {
		LogicAndContext _localctx = new LogicAndContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_logicAnd);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(189);
			equality();
			setState(194);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__20) {
				{
				{
				setState(190);
				match(T__20);
				setState(191);
				equality();
				}
				}
				setState(196);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class EqualityContext extends ParserRuleContext {
		public List<ComparisonContext> comparison() {
			return getRuleContexts(ComparisonContext.class);
		}
		public ComparisonContext comparison(int i) {
			return getRuleContext(ComparisonContext.class,i);
		}
		public EqualityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_equality; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterEquality(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitEquality(this);
		}
	}

	public final EqualityContext equality() throws RecognitionException {
		EqualityContext _localctx = new EqualityContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_equality);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(197);
			comparison();
			setState(202);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__21 || _la==T__22) {
				{
				{
				setState(198);
				_la = _input.LA(1);
				if ( !(_la==T__21 || _la==T__22) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(199);
				comparison();
				}
				}
				setState(204);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ComparisonContext extends ParserRuleContext {
		public List<AdditionContext> addition() {
			return getRuleContexts(AdditionContext.class);
		}
		public AdditionContext addition(int i) {
			return getRuleContext(AdditionContext.class,i);
		}
		public ComparisonContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_comparison; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterComparison(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitComparison(this);
		}
	}

	public final ComparisonContext comparison() throws RecognitionException {
		ComparisonContext _localctx = new ComparisonContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_comparison);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(205);
			addition();
			setState(210);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__23) | (1L << T__24) | (1L << T__25) | (1L << T__26))) != 0)) {
				{
				{
				setState(206);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__23) | (1L << T__24) | (1L << T__25) | (1L << T__26))) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(207);
				addition();
				}
				}
				setState(212);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AdditionContext extends ParserRuleContext {
		public List<MultiplicationContext> multiplication() {
			return getRuleContexts(MultiplicationContext.class);
		}
		public MultiplicationContext multiplication(int i) {
			return getRuleContext(MultiplicationContext.class,i);
		}
		public AdditionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_addition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterAddition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitAddition(this);
		}
	}

	public final AdditionContext addition() throws RecognitionException {
		AdditionContext _localctx = new AdditionContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_addition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(213);
			multiplication();
			setState(218);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__27 || _la==T__28) {
				{
				{
				setState(214);
				_la = _input.LA(1);
				if ( !(_la==T__27 || _la==T__28) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(215);
				multiplication();
				}
				}
				setState(220);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MultiplicationContext extends ParserRuleContext {
		public List<UnaryContext> unary() {
			return getRuleContexts(UnaryContext.class);
		}
		public UnaryContext unary(int i) {
			return getRuleContext(UnaryContext.class,i);
		}
		public MultiplicationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplication; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterMultiplication(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitMultiplication(this);
		}
	}

	public final MultiplicationContext multiplication() throws RecognitionException {
		MultiplicationContext _localctx = new MultiplicationContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_multiplication);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(221);
			unary();
			setState(226);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__29) | (1L << T__30) | (1L << T__31))) != 0)) {
				{
				{
				setState(222);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__29) | (1L << T__30) | (1L << T__31))) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(223);
				unary();
				}
				}
				setState(228);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class UnaryContext extends ParserRuleContext {
		public UnaryContext unary() {
			return getRuleContext(UnaryContext.class,0);
		}
		public PostfixContext postfix() {
			return getRuleContext(PostfixContext.class,0);
		}
		public UnaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unary; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterUnary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitUnary(this);
		}
	}

	public final UnaryContext unary() throws RecognitionException {
		UnaryContext _localctx = new UnaryContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_unary);
		int _la;
		try {
			setState(232);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__28:
			case T__32:
			case T__33:
			case T__34:
				enterOuterAlt(_localctx, 1);
				{
				setState(229);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__28) | (1L << T__32) | (1L << T__33) | (1L << T__34))) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(230);
				unary();
				}
				break;
			case T__0:
			case T__35:
			case T__36:
			case T__37:
			case T__38:
			case T__39:
			case NUMBER:
			case STRING:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				setState(231);
				postfix();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PostfixContext extends ParserRuleContext {
		public PrimaryContext primary() {
			return getRuleContext(PrimaryContext.class,0);
		}
		public PostfixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_postfix; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterPostfix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitPostfix(this);
		}
	}

	public final PostfixContext postfix() throws RecognitionException {
		PostfixContext _localctx = new PostfixContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_postfix);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(234);
			primary();
			setState(236);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__33 || _la==T__34) {
				{
				setState(235);
				_la = _input.LA(1);
				if ( !(_la==T__33 || _la==T__34) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CallContext extends ParserRuleContext {
		public PrimaryContext primary() {
			return getRuleContext(PrimaryContext.class,0);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> IDENTIFIER() { return getTokens(PrystParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(PrystParser.IDENTIFIER, i);
		}
		public List<ArgumentsContext> arguments() {
			return getRuleContexts(ArgumentsContext.class);
		}
		public ArgumentsContext arguments(int i) {
			return getRuleContext(ArgumentsContext.class,i);
		}
		public CallContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_call; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterCall(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitCall(this);
		}
	}

	public final CallContext call() throws RecognitionException {
		CallContext _localctx = new CallContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_call);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(238);
			primary();
			setState(252);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,26,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					setState(250);
					_errHandler.sync(this);
					switch (_input.LA(1)) {
					case T__0:
						{
						setState(239);
						match(T__0);
						setState(241);
						_errHandler.sync(this);
						_la = _input.LA(1);
						if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__28) | (1L << T__32) | (1L << T__33) | (1L << T__34) | (1L << T__35) | (1L << T__36) | (1L << T__37) | (1L << T__38) | (1L << T__39) | (1L << NUMBER) | (1L << STRING) | (1L << IDENTIFIER))) != 0)) {
							{
							setState(240);
							arguments();
							}
						}

						setState(243);
						match(T__1);
						}
						break;
					case T__9:
						{
						setState(244);
						match(T__9);
						setState(245);
						expression();
						setState(246);
						match(T__10);
						}
						break;
					case T__18:
						{
						setState(248);
						match(T__18);
						setState(249);
						match(IDENTIFIER);
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					} 
				}
				setState(254);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,26,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PrimaryContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(PrystParser.NUMBER, 0); }
		public TerminalNode STRING() { return getToken(PrystParser.STRING, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PrystParser.IDENTIFIER, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public PrimaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primary; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterPrimary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitPrimary(this);
		}
	}

	public final PrimaryContext primary() throws RecognitionException {
		PrimaryContext _localctx = new PrimaryContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_primary);
		try {
			setState(269);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__35:
				enterOuterAlt(_localctx, 1);
				{
				setState(255);
				match(T__35);
				}
				break;
			case T__36:
				enterOuterAlt(_localctx, 2);
				{
				setState(256);
				match(T__36);
				}
				break;
			case T__37:
				enterOuterAlt(_localctx, 3);
				{
				setState(257);
				match(T__37);
				}
				break;
			case T__38:
				enterOuterAlt(_localctx, 4);
				{
				setState(258);
				match(T__38);
				}
				break;
			case NUMBER:
				enterOuterAlt(_localctx, 5);
				{
				setState(259);
				match(NUMBER);
				}
				break;
			case STRING:
				enterOuterAlt(_localctx, 6);
				{
				setState(260);
				match(STRING);
				}
				break;
			case IDENTIFIER:
				enterOuterAlt(_localctx, 7);
				{
				setState(261);
				match(IDENTIFIER);
				}
				break;
			case T__0:
				enterOuterAlt(_localctx, 8);
				{
				setState(262);
				match(T__0);
				setState(263);
				expression();
				setState(264);
				match(T__1);
				}
				break;
			case T__39:
				enterOuterAlt(_localctx, 9);
				{
				setState(266);
				match(T__39);
				setState(267);
				match(T__18);
				setState(268);
				match(IDENTIFIER);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArgumentsContext extends ParserRuleContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public ArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).enterArguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof PrystListener ) ((PrystListener)listener).exitArguments(this);
		}
	}

	public final ArgumentsContext arguments() throws RecognitionException {
		ArgumentsContext _localctx = new ArgumentsContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_arguments);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(271);
			expression();
			setState(276);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__4) {
				{
				{
				setState(272);
				match(T__4);
				setState(273);
				expression();
				}
				}
				setState(278);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 6:
			return type_sempred((TypeContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean type_sempred(TypeContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 1);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3/\u011a\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\3\2\7\2:\n\2\f\2\16\2=\13\2\3\2\3\2\3\3"+
		"\3\3\3\3\5\3D\n\3\3\4\3\4\3\4\3\4\5\4J\n\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5"+
		"\5\5S\n\5\3\5\3\5\3\6\3\6\3\6\7\6Z\n\6\f\6\16\6]\13\6\3\7\3\7\3\7\3\b"+
		"\3\b\3\b\3\b\3\b\5\bg\n\b\3\b\3\b\3\b\7\bl\n\b\f\b\16\bo\13\b\3\t\3\t"+
		"\3\t\3\t\3\t\3\t\5\tw\n\t\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\13\3"+
		"\13\5\13\u0083\n\13\3\f\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\r\3\r\3\r\5\r\u0090"+
		"\n\r\3\r\5\r\u0093\n\r\3\r\3\r\5\r\u0097\n\r\3\r\3\r\3\r\3\16\3\16\5\16"+
		"\u009e\n\16\3\16\3\16\3\17\3\17\7\17\u00a4\n\17\f\17\16\17\u00a7\13\17"+
		"\3\17\3\17\3\20\3\20\3\21\3\21\3\21\5\21\u00b0\n\21\3\21\3\21\3\21\3\21"+
		"\5\21\u00b6\n\21\3\22\3\22\3\22\7\22\u00bb\n\22\f\22\16\22\u00be\13\22"+
		"\3\23\3\23\3\23\7\23\u00c3\n\23\f\23\16\23\u00c6\13\23\3\24\3\24\3\24"+
		"\7\24\u00cb\n\24\f\24\16\24\u00ce\13\24\3\25\3\25\3\25\7\25\u00d3\n\25"+
		"\f\25\16\25\u00d6\13\25\3\26\3\26\3\26\7\26\u00db\n\26\f\26\16\26\u00de"+
		"\13\26\3\27\3\27\3\27\7\27\u00e3\n\27\f\27\16\27\u00e6\13\27\3\30\3\30"+
		"\3\30\5\30\u00eb\n\30\3\31\3\31\5\31\u00ef\n\31\3\32\3\32\3\32\5\32\u00f4"+
		"\n\32\3\32\3\32\3\32\3\32\3\32\3\32\3\32\7\32\u00fd\n\32\f\32\16\32\u0100"+
		"\13\32\3\33\3\33\3\33\3\33\3\33\3\33\3\33\3\33\3\33\3\33\3\33\3\33\3\33"+
		"\3\33\5\33\u0110\n\33\3\34\3\34\3\34\7\34\u0115\n\34\f\34\16\34\u0118"+
		"\13\34\3\34\2\3\16\35\2\4\6\b\n\f\16\20\22\24\26\30\32\34\36 \"$&(*,."+
		"\60\62\64\66\2\b\3\2\30\31\3\2\32\35\3\2\36\37\3\2 \"\4\2\37\37#%\3\2"+
		"$%\2\u012b\2;\3\2\2\2\4C\3\2\2\2\6E\3\2\2\2\bN\3\2\2\2\nV\3\2\2\2\f^\3"+
		"\2\2\2\16f\3\2\2\2\20v\3\2\2\2\22x\3\2\2\2\24{\3\2\2\2\26\u0084\3\2\2"+
		"\2\30\u008a\3\2\2\2\32\u009b\3\2\2\2\34\u00a1\3\2\2\2\36\u00aa\3\2\2\2"+
		" \u00b5\3\2\2\2\"\u00b7\3\2\2\2$\u00bf\3\2\2\2&\u00c7\3\2\2\2(\u00cf\3"+
		"\2\2\2*\u00d7\3\2\2\2,\u00df\3\2\2\2.\u00ea\3\2\2\2\60\u00ec\3\2\2\2\62"+
		"\u00f0\3\2\2\2\64\u010f\3\2\2\2\66\u0111\3\2\2\28:\5\4\3\298\3\2\2\2:"+
		"=\3\2\2\2;9\3\2\2\2;<\3\2\2\2<>\3\2\2\2=;\3\2\2\2>?\7\2\2\3?\3\3\2\2\2"+
		"@D\5\6\4\2AD\5\b\5\2BD\5\20\t\2C@\3\2\2\2CA\3\2\2\2CB\3\2\2\2D\5\3\2\2"+
		"\2EF\5\16\b\2FG\7-\2\2GI\7\3\2\2HJ\5\n\6\2IH\3\2\2\2IJ\3\2\2\2JK\3\2\2"+
		"\2KL\7\4\2\2LM\5\34\17\2M\7\3\2\2\2NO\5\16\b\2OR\7-\2\2PQ\7\5\2\2QS\5"+
		"\36\20\2RP\3\2\2\2RS\3\2\2\2ST\3\2\2\2TU\7\6\2\2U\t\3\2\2\2V[\5\f\7\2"+
		"WX\7\7\2\2XZ\5\f\7\2YW\3\2\2\2Z]\3\2\2\2[Y\3\2\2\2[\\\3\2\2\2\\\13\3\2"+
		"\2\2][\3\2\2\2^_\5\16\b\2_`\7-\2\2`\r\3\2\2\2ab\b\b\1\2bg\7\b\2\2cg\7"+
		"\t\2\2dg\7\n\2\2eg\7\13\2\2fa\3\2\2\2fc\3\2\2\2fd\3\2\2\2fe\3\2\2\2gm"+
		"\3\2\2\2hi\f\3\2\2ij\7\f\2\2jl\7\r\2\2kh\3\2\2\2lo\3\2\2\2mk\3\2\2\2m"+
		"n\3\2\2\2n\17\3\2\2\2om\3\2\2\2pw\5\22\n\2qw\5\24\13\2rw\5\26\f\2sw\5"+
		"\30\r\2tw\5\32\16\2uw\5\34\17\2vp\3\2\2\2vq\3\2\2\2vr\3\2\2\2vs\3\2\2"+
		"\2vt\3\2\2\2vu\3\2\2\2w\21\3\2\2\2xy\5\36\20\2yz\7\6\2\2z\23\3\2\2\2{"+
		"|\7\16\2\2|}\7\3\2\2}~\5\36\20\2~\177\7\4\2\2\177\u0082\5\20\t\2\u0080"+
		"\u0081\7\17\2\2\u0081\u0083\5\20\t\2\u0082\u0080\3\2\2\2\u0082\u0083\3"+
		"\2\2\2\u0083\25\3\2\2\2\u0084\u0085\7\20\2\2\u0085\u0086\7\3\2\2\u0086"+
		"\u0087\5\36\20\2\u0087\u0088\7\4\2\2\u0088\u0089\5\20\t\2\u0089\27\3\2"+
		"\2\2\u008a\u008b\7\21\2\2\u008b\u008f\7\3\2\2\u008c\u0090\5\b\5\2\u008d"+
		"\u0090\5\22\n\2\u008e\u0090\7\6\2\2\u008f\u008c\3\2\2\2\u008f\u008d\3"+
		"\2\2\2\u008f\u008e\3\2\2\2\u0090\u0092\3\2\2\2\u0091\u0093\5\36\20\2\u0092"+
		"\u0091\3\2\2\2\u0092\u0093\3\2\2\2\u0093\u0094\3\2\2\2\u0094\u0096\7\6"+
		"\2\2\u0095\u0097\5\36\20\2\u0096\u0095\3\2\2\2\u0096\u0097\3\2\2\2\u0097"+
		"\u0098\3\2\2\2\u0098\u0099\7\4\2\2\u0099\u009a\5\20\t\2\u009a\31\3\2\2"+
		"\2\u009b\u009d\7\22\2\2\u009c\u009e\5\36\20\2\u009d\u009c\3\2\2\2\u009d"+
		"\u009e\3\2\2\2\u009e\u009f\3\2\2\2\u009f\u00a0\7\6\2\2\u00a0\33\3\2\2"+
		"\2\u00a1\u00a5\7\23\2\2\u00a2\u00a4\5\4\3\2\u00a3\u00a2\3\2\2\2\u00a4"+
		"\u00a7\3\2\2\2\u00a5\u00a3\3\2\2\2\u00a5\u00a6\3\2\2\2\u00a6\u00a8\3\2"+
		"\2\2\u00a7\u00a5\3\2\2\2\u00a8\u00a9\7\24\2\2\u00a9\35\3\2\2\2\u00aa\u00ab"+
		"\5 \21\2\u00ab\37\3\2\2\2\u00ac\u00ad\5\62\32\2\u00ad\u00ae\7\25\2\2\u00ae"+
		"\u00b0\3\2\2\2\u00af\u00ac\3\2\2\2\u00af\u00b0\3\2\2\2\u00b0\u00b1\3\2"+
		"\2\2\u00b1\u00b2\7-\2\2\u00b2\u00b3\7\5\2\2\u00b3\u00b6\5 \21\2\u00b4"+
		"\u00b6\5\"\22\2\u00b5\u00af\3\2\2\2\u00b5\u00b4\3\2\2\2\u00b6!\3\2\2\2"+
		"\u00b7\u00bc\5$\23\2\u00b8\u00b9\7\26\2\2\u00b9\u00bb\5$\23\2\u00ba\u00b8"+
		"\3\2\2\2\u00bb\u00be\3\2\2\2\u00bc\u00ba\3\2\2\2\u00bc\u00bd\3\2\2\2\u00bd"+
		"#\3\2\2\2\u00be\u00bc\3\2\2\2\u00bf\u00c4\5&\24\2\u00c0\u00c1\7\27\2\2"+
		"\u00c1\u00c3\5&\24\2\u00c2\u00c0\3\2\2\2\u00c3\u00c6\3\2\2\2\u00c4\u00c2"+
		"\3\2\2\2\u00c4\u00c5\3\2\2\2\u00c5%\3\2\2\2\u00c6\u00c4\3\2\2\2\u00c7"+
		"\u00cc\5(\25\2\u00c8\u00c9\t\2\2\2\u00c9\u00cb\5(\25\2\u00ca\u00c8\3\2"+
		"\2\2\u00cb\u00ce\3\2\2\2\u00cc\u00ca\3\2\2\2\u00cc\u00cd\3\2\2\2\u00cd"+
		"\'\3\2\2\2\u00ce\u00cc\3\2\2\2\u00cf\u00d4\5*\26\2\u00d0\u00d1\t\3\2\2"+
		"\u00d1\u00d3\5*\26\2\u00d2\u00d0\3\2\2\2\u00d3\u00d6\3\2\2\2\u00d4\u00d2"+
		"\3\2\2\2\u00d4\u00d5\3\2\2\2\u00d5)\3\2\2\2\u00d6\u00d4\3\2\2\2\u00d7"+
		"\u00dc\5,\27\2\u00d8\u00d9\t\4\2\2\u00d9\u00db\5,\27\2\u00da\u00d8\3\2"+
		"\2\2\u00db\u00de\3\2\2\2\u00dc\u00da\3\2\2\2\u00dc\u00dd\3\2\2\2\u00dd"+
		"+\3\2\2\2\u00de\u00dc\3\2\2\2\u00df\u00e4\5.\30\2\u00e0\u00e1\t\5\2\2"+
		"\u00e1\u00e3\5.\30\2\u00e2\u00e0\3\2\2\2\u00e3\u00e6\3\2\2\2\u00e4\u00e2"+
		"\3\2\2\2\u00e4\u00e5\3\2\2\2\u00e5-\3\2\2\2\u00e6\u00e4\3\2\2\2\u00e7"+
		"\u00e8\t\6\2\2\u00e8\u00eb\5.\30\2\u00e9\u00eb\5\60\31\2\u00ea\u00e7\3"+
		"\2\2\2\u00ea\u00e9\3\2\2\2\u00eb/\3\2\2\2\u00ec\u00ee\5\64\33\2\u00ed"+
		"\u00ef\t\7\2\2\u00ee\u00ed\3\2\2\2\u00ee\u00ef\3\2\2\2\u00ef\61\3\2\2"+
		"\2\u00f0\u00fe\5\64\33\2\u00f1\u00f3\7\3\2\2\u00f2\u00f4\5\66\34\2\u00f3"+
		"\u00f2\3\2\2\2\u00f3\u00f4\3\2\2\2\u00f4\u00f5\3\2\2\2\u00f5\u00fd\7\4"+
		"\2\2\u00f6\u00f7\7\f\2\2\u00f7\u00f8\5\36\20\2\u00f8\u00f9\7\r\2\2\u00f9"+
		"\u00fd\3\2\2\2\u00fa\u00fb\7\25\2\2\u00fb\u00fd\7-\2\2\u00fc\u00f1\3\2"+
		"\2\2\u00fc\u00f6\3\2\2\2\u00fc\u00fa\3\2\2\2\u00fd\u0100\3\2\2\2\u00fe"+
		"\u00fc\3\2\2\2\u00fe\u00ff\3\2\2\2\u00ff\63\3\2\2\2\u0100\u00fe\3\2\2"+
		"\2\u0101\u0110\7&\2\2\u0102\u0110\7\'\2\2\u0103\u0110\7(\2\2\u0104\u0110"+
		"\7)\2\2\u0105\u0110\7+\2\2\u0106\u0110\7,\2\2\u0107\u0110\7-\2\2\u0108"+
		"\u0109\7\3\2\2\u0109\u010a\5\36\20\2\u010a\u010b\7\4\2\2\u010b\u0110\3"+
		"\2\2\2\u010c\u010d\7*\2\2\u010d\u010e\7\25\2\2\u010e\u0110\7-\2\2\u010f"+
		"\u0101\3\2\2\2\u010f\u0102\3\2\2\2\u010f\u0103\3\2\2\2\u010f\u0104\3\2"+
		"\2\2\u010f\u0105\3\2\2\2\u010f\u0106\3\2\2\2\u010f\u0107\3\2\2\2\u010f"+
		"\u0108\3\2\2\2\u010f\u010c\3\2\2\2\u0110\65\3\2\2\2\u0111\u0116\5\36\20"+
		"\2\u0112\u0113\7\7\2\2\u0113\u0115\5\36\20\2\u0114\u0112\3\2\2\2\u0115"+
		"\u0118\3\2\2\2\u0116\u0114\3\2\2\2\u0116\u0117\3\2\2\2\u0117\67\3\2\2"+
		"\2\u0118\u0116\3\2\2\2\37;CIR[fmv\u0082\u008f\u0092\u0096\u009d\u00a5"+
		"\u00af\u00b5\u00bc\u00c4\u00cc\u00d4\u00dc\u00e4\u00ea\u00ee\u00f3\u00fc"+
		"\u00fe\u010f\u0116";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}