// Generated from language/src/main/java/org/jitcijk/pryst/parser/Pryst.g4 by ANTLR 4.7.2
package org.jitcijk.pryst.parser;

// DO NOT MODIFY - generated from Pryst.g4 using "mx create-pryst-parser"

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.oracle.truffle.api.source.Source;
import com.oracle.truffle.api.RootCallTarget;
import org.jitcijk.pryst.PrystLanguage;
import org.jitcijk.pryst.nodes.PrystExpressionNode;
import org.jitcijk.pryst.nodes.PrystRootNode;
import org.jitcijk.pryst.nodes.PrystStatementNode;
import org.jitcijk.pryst.parser.PrystParseError;

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
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, WS=31, COMMENT=32, 
		LINE_COMMENT=33, IDENTIFIER=34, STRING_LITERAL=35, INTEGER_LITERAL=36, 
		DOUBLE_LITERAL=37;
	public static final int
		RULE_pryst = 0, RULE_function = 1, RULE_block = 2, RULE_statement = 3, 
		RULE_while_statement = 4, RULE_if_statement = 5, RULE_return_statement = 6, 
		RULE_expression = 7, RULE_logic_term = 8, RULE_logic_factor = 9, RULE_arithmetic = 10, 
		RULE_term = 11, RULE_factor = 12, RULE_member_expression = 13;
	private static String[] makeRuleNames() {
		return new String[] {
			"pryst", "function", "block", "statement", "while_statement", "if_statement", 
			"return_statement", "expression", "logic_term", "logic_factor", "arithmetic", 
			"term", "factor", "member_expression"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'function'", "'('", "','", "')'", "'{'", "'}'", "'break'", "';'", 
			"'continue'", "'debugger'", "'while'", "'if'", "'else'", "'return'", 
			"'||'", "'&&'", "'<'", "'<='", "'>'", "'>='", "'=='", "'!='", "'+'", 
			"'-'", "'*'", "'/'", "'='", "'.'", "'['", "']'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, "WS", "COMMENT", "LINE_COMMENT", 
			"IDENTIFIER", "STRING_LITERAL", "INTEGER_LITERAL", "DOUBLE_LITERAL"
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


	private PrystNodeFactory factory;
	private Source source;

	private static final class BailoutErrorListener extends BaseErrorListener {
	    private final Source source;
	    BailoutErrorListener(Source source) {
	        this.source = source;
	    }
	    @Override
	    public void syntaxError(Recognizer<?, ?> recognizer, Object offendingSymbol, int line, int charPositionInLine, String msg, RecognitionException e) {
	        throwParseError(source, line, charPositionInLine, (Token) offendingSymbol, msg);
	    }
	}

	public void SemErr(Token token, String message) {
	    assert token != null;
	    throwParseError(source, token.getLine(), token.getCharPositionInLine(), token, message);
	}

	private static void throwParseError(Source source, int line, int charPositionInLine, Token token, String message) {
	    int col = charPositionInLine + 1;
	    String location = "-- line " + line + " col " + col + ": ";
	    int length = token == null ? 1 : Math.max(token.getStopIndex() - token.getStartIndex(), 0);
	    throw new PrystParseError(source, line, col, length, String.format("Error(s) parsing script:%n" + location + message));
	}

	public static Map<String, RootCallTarget> parsePryst(PrystLanguage language, Source source) {
	    PrystLexer lexer = new PrystLexer(CharStreams.fromString(source.getCharacters().toString()));
	    PrystParser parser = new PrystParser(new CommonTokenStream(lexer));
	    lexer.removeErrorListeners();
	    parser.removeErrorListeners();
	    BailoutErrorListener listener = new BailoutErrorListener(source);
	    lexer.addErrorListener(listener);
	    parser.addErrorListener(listener);
	    parser.factory = new PrystNodeFactory(language, source);
	    parser.source = source;
	    parser.pryst();
	    return parser.factory.getAllFunctions();
	}

	public PrystParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class PrystContext extends ParserRuleContext {
		public List<FunctionContext> function() {
			return getRuleContexts(FunctionContext.class);
		}
		public FunctionContext function(int i) {
			return getRuleContext(FunctionContext.class,i);
		}
		public TerminalNode EOF() { return getToken(PrystParser.EOF, 0); }
		public PrystContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pryst; }
	}

	public final PrystContext pryst() throws RecognitionException {
		PrystContext _localctx = new PrystContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_pryst);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(28);
			function();
			setState(32);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__0) {
				{
				{
				setState(29);
				function();
				}
				}
				setState(34);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(35);
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

	public static class FunctionContext extends ParserRuleContext {
		public Token IDENTIFIER;
		public Token s;
		public BlockContext body;
		public List<TerminalNode> IDENTIFIER() { return getTokens(PrystParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(PrystParser.IDENTIFIER, i);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public FunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function; }
	}

	public final FunctionContext function() throws RecognitionException {
		FunctionContext _localctx = new FunctionContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_function);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(37);
			match(T__0);
			setState(38);
			((FunctionContext)_localctx).IDENTIFIER = match(IDENTIFIER);
			setState(39);
			((FunctionContext)_localctx).s = match(T__1);
			 factory.startFunction(((FunctionContext)_localctx).IDENTIFIER, ((FunctionContext)_localctx).s); 
			setState(51);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(41);
				((FunctionContext)_localctx).IDENTIFIER = match(IDENTIFIER);
				 factory.addFormalParameter(((FunctionContext)_localctx).IDENTIFIER); 
				setState(48);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__2) {
					{
					{
					setState(43);
					match(T__2);
					setState(44);
					((FunctionContext)_localctx).IDENTIFIER = match(IDENTIFIER);
					 factory.addFormalParameter(((FunctionContext)_localctx).IDENTIFIER); 
					}
					}
					setState(50);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			setState(53);
			match(T__3);
			setState(54);
			((FunctionContext)_localctx).body = block(false);
			 factory.finishFunction(((FunctionContext)_localctx).body.result); 
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
		public boolean inLoop;
		public PrystStatementNode result;
		public Token s;
		public StatementContext statement;
		public Token e;
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public BlockContext(ParserRuleContext parent, int invokingState, boolean inLoop) {
			super(parent, invokingState);
			this.inLoop = inLoop;
		}
		@Override public int getRuleIndex() { return RULE_block; }
	}

	public final BlockContext block(boolean inLoop) throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState(), inLoop);
		enterRule(_localctx, 4, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			 factory.startBlock();
			                                                  List<PrystStatementNode> body = new ArrayList<>(); 
			setState(58);
			((BlockContext)_localctx).s = match(T__4);
			setState(64);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__1) | (1L << T__6) | (1L << T__8) | (1L << T__9) | (1L << T__10) | (1L << T__11) | (1L << T__13) | (1L << IDENTIFIER) | (1L << STRING_LITERAL) | (1L << INTEGER_LITERAL) | (1L << DOUBLE_LITERAL))) != 0)) {
				{
				{
				setState(59);
				((BlockContext)_localctx).statement = statement(inLoop);
				 body.add(((BlockContext)_localctx).statement.result); 
				}
				}
				setState(66);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(67);
			((BlockContext)_localctx).e = match(T__5);
			 ((BlockContext)_localctx).result =  factory.finishBlock(body, ((BlockContext)_localctx).s.getStartIndex(), ((BlockContext)_localctx).e.getStopIndex() - ((BlockContext)_localctx).s.getStartIndex() + 1); 
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

	public static class StatementContext extends ParserRuleContext {
		public boolean inLoop;
		public PrystStatementNode result;
		public While_statementContext while_statement;
		public Token b;
		public Token c;
		public If_statementContext if_statement;
		public Return_statementContext return_statement;
		public ExpressionContext expression;
		public Token d;
		public While_statementContext while_statement() {
			return getRuleContext(While_statementContext.class,0);
		}
		public If_statementContext if_statement() {
			return getRuleContext(If_statementContext.class,0);
		}
		public Return_statementContext return_statement() {
			return getRuleContext(Return_statementContext.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public StatementContext(ParserRuleContext parent, int invokingState, boolean inLoop) {
			super(parent, invokingState);
			this.inLoop = inLoop;
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	}

	public final StatementContext statement(boolean inLoop) throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState(), inLoop);
		enterRule(_localctx, 6, RULE_statement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(92);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__10:
				{
				setState(70);
				((StatementContext)_localctx).while_statement = while_statement();
				 ((StatementContext)_localctx).result =  ((StatementContext)_localctx).while_statement.result; 
				}
				break;
			case T__6:
				{
				setState(73);
				((StatementContext)_localctx).b = match(T__6);
				 if (inLoop) { ((StatementContext)_localctx).result =  factory.createBreak(((StatementContext)_localctx).b); } else { SemErr(((StatementContext)_localctx).b, "break used outside of loop"); } 
				setState(75);
				match(T__7);
				}
				break;
			case T__8:
				{
				setState(76);
				((StatementContext)_localctx).c = match(T__8);
				 if (inLoop) { ((StatementContext)_localctx).result =  factory.createContinue(((StatementContext)_localctx).c); } else { SemErr(((StatementContext)_localctx).c, "continue used outside of loop"); } 
				setState(78);
				match(T__7);
				}
				break;
			case T__11:
				{
				setState(79);
				((StatementContext)_localctx).if_statement = if_statement(inLoop);
				 ((StatementContext)_localctx).result =  ((StatementContext)_localctx).if_statement.result; 
				}
				break;
			case T__13:
				{
				setState(82);
				((StatementContext)_localctx).return_statement = return_statement();
				 ((StatementContext)_localctx).result =  ((StatementContext)_localctx).return_statement.result; 
				}
				break;
			case T__1:
			case IDENTIFIER:
			case STRING_LITERAL:
			case INTEGER_LITERAL:
			case DOUBLE_LITERAL:
				{
				setState(85);
				((StatementContext)_localctx).expression = expression();
				setState(86);
				match(T__7);
				 ((StatementContext)_localctx).result =  ((StatementContext)_localctx).expression.result; 
				}
				break;
			case T__9:
				{
				setState(89);
				((StatementContext)_localctx).d = match(T__9);
				 ((StatementContext)_localctx).result =  factory.createDebugger(((StatementContext)_localctx).d); 
				setState(91);
				match(T__7);
				}
				break;
			default:
				throw new NoViableAltException(this);
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

	public static class While_statementContext extends ParserRuleContext {
		public PrystStatementNode result;
		public Token w;
		public ExpressionContext condition;
		public BlockContext body;
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public While_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_while_statement; }
	}

	public final While_statementContext while_statement() throws RecognitionException {
		While_statementContext _localctx = new While_statementContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_while_statement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(94);
			((While_statementContext)_localctx).w = match(T__10);
			setState(95);
			match(T__1);
			setState(96);
			((While_statementContext)_localctx).condition = expression();
			setState(97);
			match(T__3);
			setState(98);
			((While_statementContext)_localctx).body = block(true);
			 ((While_statementContext)_localctx).result =  factory.createWhile(((While_statementContext)_localctx).w, ((While_statementContext)_localctx).condition.result, ((While_statementContext)_localctx).body.result); 
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

	public static class If_statementContext extends ParserRuleContext {
		public boolean inLoop;
		public PrystStatementNode result;
		public Token i;
		public ExpressionContext condition;
		public BlockContext then;
		public BlockContext block;
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public List<BlockContext> block() {
			return getRuleContexts(BlockContext.class);
		}
		public BlockContext block(int i) {
			return getRuleContext(BlockContext.class,i);
		}
		public If_statementContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public If_statementContext(ParserRuleContext parent, int invokingState, boolean inLoop) {
			super(parent, invokingState);
			this.inLoop = inLoop;
		}
		@Override public int getRuleIndex() { return RULE_if_statement; }
	}

	public final If_statementContext if_statement(boolean inLoop) throws RecognitionException {
		If_statementContext _localctx = new If_statementContext(_ctx, getState(), inLoop);
		enterRule(_localctx, 10, RULE_if_statement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(101);
			((If_statementContext)_localctx).i = match(T__11);
			setState(102);
			match(T__1);
			setState(103);
			((If_statementContext)_localctx).condition = expression();
			setState(104);
			match(T__3);
			setState(105);
			((If_statementContext)_localctx).then = ((If_statementContext)_localctx).block = block(inLoop);
			 PrystStatementNode elsePart = null; 
			setState(111);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__12) {
				{
				setState(107);
				match(T__12);
				setState(108);
				((If_statementContext)_localctx).block = block(inLoop);
				 elsePart = ((If_statementContext)_localctx).block.result; 
				}
			}

			 ((If_statementContext)_localctx).result =  factory.createIf(((If_statementContext)_localctx).i, ((If_statementContext)_localctx).condition.result, ((If_statementContext)_localctx).then.result, elsePart); 
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

	public static class Return_statementContext extends ParserRuleContext {
		public PrystStatementNode result;
		public Token r;
		public ExpressionContext expression;
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Return_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_return_statement; }
	}

	public final Return_statementContext return_statement() throws RecognitionException {
		Return_statementContext _localctx = new Return_statementContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_return_statement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(115);
			((Return_statementContext)_localctx).r = match(T__13);
			 PrystExpressionNode value = null; 
			setState(120);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__1) | (1L << IDENTIFIER) | (1L << STRING_LITERAL) | (1L << INTEGER_LITERAL) | (1L << DOUBLE_LITERAL))) != 0)) {
				{
				setState(117);
				((Return_statementContext)_localctx).expression = expression();
				 value = ((Return_statementContext)_localctx).expression.result; 
				}
			}

			 ((Return_statementContext)_localctx).result =  factory.createReturn(((Return_statementContext)_localctx).r, value); 
			setState(123);
			match(T__7);
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
		public PrystExpressionNode result;
		public Logic_termContext logic_term;
		public Token op;
		public List<Logic_termContext> logic_term() {
			return getRuleContexts(Logic_termContext.class);
		}
		public Logic_termContext logic_term(int i) {
			return getRuleContext(Logic_termContext.class,i);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_expression);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(125);
			((ExpressionContext)_localctx).logic_term = logic_term();
			 ((ExpressionContext)_localctx).result =  ((ExpressionContext)_localctx).logic_term.result; 
			setState(133);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,7,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(127);
					((ExpressionContext)_localctx).op = match(T__14);
					setState(128);
					((ExpressionContext)_localctx).logic_term = logic_term();
					 ((ExpressionContext)_localctx).result =  factory.createBinary(((ExpressionContext)_localctx).op, _localctx.result, ((ExpressionContext)_localctx).logic_term.result); 
					}
					} 
				}
				setState(135);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,7,_ctx);
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

	public static class Logic_termContext extends ParserRuleContext {
		public PrystExpressionNode result;
		public Logic_factorContext logic_factor;
		public Token op;
		public List<Logic_factorContext> logic_factor() {
			return getRuleContexts(Logic_factorContext.class);
		}
		public Logic_factorContext logic_factor(int i) {
			return getRuleContext(Logic_factorContext.class,i);
		}
		public Logic_termContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic_term; }
	}

	public final Logic_termContext logic_term() throws RecognitionException {
		Logic_termContext _localctx = new Logic_termContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_logic_term);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(136);
			((Logic_termContext)_localctx).logic_factor = logic_factor();
			 ((Logic_termContext)_localctx).result =  ((Logic_termContext)_localctx).logic_factor.result; 
			setState(144);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,8,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(138);
					((Logic_termContext)_localctx).op = match(T__15);
					setState(139);
					((Logic_termContext)_localctx).logic_factor = logic_factor();
					 ((Logic_termContext)_localctx).result =  factory.createBinary(((Logic_termContext)_localctx).op, _localctx.result, ((Logic_termContext)_localctx).logic_factor.result); 
					}
					} 
				}
				setState(146);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,8,_ctx);
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

	public static class Logic_factorContext extends ParserRuleContext {
		public PrystExpressionNode result;
		public ArithmeticContext arithmetic;
		public Token op;
		public List<ArithmeticContext> arithmetic() {
			return getRuleContexts(ArithmeticContext.class);
		}
		public ArithmeticContext arithmetic(int i) {
			return getRuleContext(ArithmeticContext.class,i);
		}
		public Logic_factorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic_factor; }
	}

	public final Logic_factorContext logic_factor() throws RecognitionException {
		Logic_factorContext _localctx = new Logic_factorContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_logic_factor);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(147);
			((Logic_factorContext)_localctx).arithmetic = arithmetic();
			 ((Logic_factorContext)_localctx).result =  ((Logic_factorContext)_localctx).arithmetic.result; 
			setState(153);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
			case 1:
				{
				setState(149);
				((Logic_factorContext)_localctx).op = _input.LT(1);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__16) | (1L << T__17) | (1L << T__18) | (1L << T__19) | (1L << T__20) | (1L << T__21))) != 0)) ) {
					((Logic_factorContext)_localctx).op = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(150);
				((Logic_factorContext)_localctx).arithmetic = arithmetic();
				 ((Logic_factorContext)_localctx).result =  factory.createBinary(((Logic_factorContext)_localctx).op, _localctx.result, ((Logic_factorContext)_localctx).arithmetic.result); 
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

	public static class ArithmeticContext extends ParserRuleContext {
		public PrystExpressionNode result;
		public TermContext term;
		public Token op;
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public ArithmeticContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arithmetic; }
	}

	public final ArithmeticContext arithmetic() throws RecognitionException {
		ArithmeticContext _localctx = new ArithmeticContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_arithmetic);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(155);
			((ArithmeticContext)_localctx).term = term();
			 ((ArithmeticContext)_localctx).result =  ((ArithmeticContext)_localctx).term.result; 
			setState(163);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(157);
					((ArithmeticContext)_localctx).op = _input.LT(1);
					_la = _input.LA(1);
					if ( !(_la==T__22 || _la==T__23) ) {
						((ArithmeticContext)_localctx).op = (Token)_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(158);
					((ArithmeticContext)_localctx).term = term();
					 ((ArithmeticContext)_localctx).result =  factory.createBinary(((ArithmeticContext)_localctx).op, _localctx.result, ((ArithmeticContext)_localctx).term.result); 
					}
					} 
				}
				setState(165);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
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

	public static class TermContext extends ParserRuleContext {
		public PrystExpressionNode result;
		public FactorContext factor;
		public Token op;
		public List<FactorContext> factor() {
			return getRuleContexts(FactorContext.class);
		}
		public FactorContext factor(int i) {
			return getRuleContext(FactorContext.class,i);
		}
		public TermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term; }
	}

	public final TermContext term() throws RecognitionException {
		TermContext _localctx = new TermContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_term);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(166);
			((TermContext)_localctx).factor = factor();
			 ((TermContext)_localctx).result =  ((TermContext)_localctx).factor.result; 
			setState(174);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,11,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(168);
					((TermContext)_localctx).op = _input.LT(1);
					_la = _input.LA(1);
					if ( !(_la==T__24 || _la==T__25) ) {
						((TermContext)_localctx).op = (Token)_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(169);
					((TermContext)_localctx).factor = factor();
					 ((TermContext)_localctx).result =  factory.createBinary(((TermContext)_localctx).op, _localctx.result, ((TermContext)_localctx).factor.result); 
					}
					} 
				}
				setState(176);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,11,_ctx);
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

	public static class FactorContext extends ParserRuleContext {
		public PrystExpressionNode result;
		public Token IDENTIFIER;
		public Member_expressionContext member_expression;
		public Token STRING_LITERAL;
		public Token INTEGER_LITERAL;
		public Token DOUBLE_LITERAL;
		public Token s;
		public ExpressionContext expr;
		public Token e;
		public TerminalNode IDENTIFIER() { return getToken(PrystParser.IDENTIFIER, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(PrystParser.STRING_LITERAL, 0); }
		public TerminalNode INTEGER_LITERAL() { return getToken(PrystParser.INTEGER_LITERAL, 0); }
		public TerminalNode DOUBLE_LITERAL() { return getToken(PrystParser.DOUBLE_LITERAL, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Member_expressionContext member_expression() {
			return getRuleContext(Member_expressionContext.class,0);
		}
		public FactorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_factor; }
	}

	public final FactorContext factor() throws RecognitionException {
		FactorContext _localctx = new FactorContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_factor);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(196);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IDENTIFIER:
				{
				setState(177);
				((FactorContext)_localctx).IDENTIFIER = match(IDENTIFIER);
				 PrystExpressionNode assignmentName = factory.createStringLiteral(((FactorContext)_localctx).IDENTIFIER, false); 
				setState(183);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
				case 1:
					{
					setState(179);
					((FactorContext)_localctx).member_expression = member_expression(null, null, assignmentName);
					 ((FactorContext)_localctx).result =  ((FactorContext)_localctx).member_expression.result; 
					}
					break;
				case 2:
					{
					 ((FactorContext)_localctx).result =  factory.createRead(assignmentName); 
					}
					break;
				}
				}
				break;
			case STRING_LITERAL:
				{
				setState(185);
				((FactorContext)_localctx).STRING_LITERAL = match(STRING_LITERAL);
				 ((FactorContext)_localctx).result =  factory.createStringLiteral(((FactorContext)_localctx).STRING_LITERAL, true); 
				}
				break;
			case INTEGER_LITERAL:
				{
				setState(187);
				((FactorContext)_localctx).INTEGER_LITERAL = match(INTEGER_LITERAL);
				 ((FactorContext)_localctx).result =  factory.createIntegerLiteral(((FactorContext)_localctx).INTEGER_LITERAL); 
				}
				break;
			case DOUBLE_LITERAL:
				{
				setState(189);
				((FactorContext)_localctx).DOUBLE_LITERAL = match(DOUBLE_LITERAL);
				 ((FactorContext)_localctx).result =  factory.createDoubleLiteral(((FactorContext)_localctx).DOUBLE_LITERAL); 
				}
				break;
			case T__1:
				{
				setState(191);
				((FactorContext)_localctx).s = match(T__1);
				setState(192);
				((FactorContext)_localctx).expr = expression();
				setState(193);
				((FactorContext)_localctx).e = match(T__3);
				 ((FactorContext)_localctx).result =  factory.createParenExpression(((FactorContext)_localctx).expr.result, ((FactorContext)_localctx).s.getStartIndex(), ((FactorContext)_localctx).e.getStopIndex() - ((FactorContext)_localctx).s.getStartIndex() + 1); 
				}
				break;
			default:
				throw new NoViableAltException(this);
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

	public static class Member_expressionContext extends ParserRuleContext {
		public PrystExpressionNode r;
		public PrystExpressionNode assignmentReceiver;
		public PrystExpressionNode assignmentName;
		public PrystExpressionNode result;
		public ExpressionContext expression;
		public Token e;
		public Token IDENTIFIER;
		public Member_expressionContext member_expression;
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode IDENTIFIER() { return getToken(PrystParser.IDENTIFIER, 0); }
		public Member_expressionContext member_expression() {
			return getRuleContext(Member_expressionContext.class,0);
		}
		public Member_expressionContext(ParserRuleContext parent, int invokingState) { super(parent, invokingState); }
		public Member_expressionContext(ParserRuleContext parent, int invokingState, PrystExpressionNode r, PrystExpressionNode assignmentReceiver, PrystExpressionNode assignmentName) {
			super(parent, invokingState);
			this.r = r;
			this.assignmentReceiver = assignmentReceiver;
			this.assignmentName = assignmentName;
		}
		@Override public int getRuleIndex() { return RULE_member_expression; }
	}

	public final Member_expressionContext member_expression(PrystExpressionNode r,PrystExpressionNode assignmentReceiver,PrystExpressionNode assignmentName) throws RecognitionException {
		Member_expressionContext _localctx = new Member_expressionContext(_ctx, getState(), r, assignmentReceiver, assignmentName);
		enterRule(_localctx, 26, RULE_member_expression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			 PrystExpressionNode receiver = r;
			                                                  PrystExpressionNode nestedAssignmentName = null; 
			setState(230);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__1:
				{
				setState(199);
				match(T__1);
				 List<PrystExpressionNode> parameters = new ArrayList<>();
				                                                  if (receiver == null) {
				                                                      receiver = factory.createRead(assignmentName);
				                                                  } 
				setState(212);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__1) | (1L << IDENTIFIER) | (1L << STRING_LITERAL) | (1L << INTEGER_LITERAL) | (1L << DOUBLE_LITERAL))) != 0)) {
					{
					setState(201);
					((Member_expressionContext)_localctx).expression = expression();
					 parameters.add(((Member_expressionContext)_localctx).expression.result); 
					setState(209);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==T__2) {
						{
						{
						setState(203);
						match(T__2);
						setState(204);
						((Member_expressionContext)_localctx).expression = expression();
						 parameters.add(((Member_expressionContext)_localctx).expression.result); 
						}
						}
						setState(211);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(214);
				((Member_expressionContext)_localctx).e = match(T__3);
				 ((Member_expressionContext)_localctx).result =  factory.createCall(receiver, parameters, ((Member_expressionContext)_localctx).e); 
				}
				break;
			case T__26:
				{
				setState(216);
				match(T__26);
				setState(217);
				((Member_expressionContext)_localctx).expression = expression();
				 if (assignmentName == null) {
				                                                      SemErr((((Member_expressionContext)_localctx).expression!=null?(((Member_expressionContext)_localctx).expression.start):null), "invalid assignment target");
				                                                  } else if (assignmentReceiver == null) {
				                                                      ((Member_expressionContext)_localctx).result =  factory.createAssignment(assignmentName, ((Member_expressionContext)_localctx).expression.result);
				                                                  } else {
				                                                      ((Member_expressionContext)_localctx).result =  factory.createWriteProperty(assignmentReceiver, assignmentName, ((Member_expressionContext)_localctx).expression.result);
				                                                  } 
				}
				break;
			case T__27:
				{
				setState(220);
				match(T__27);
				 if (receiver == null) {
				                                                       receiver = factory.createRead(assignmentName);
				                                                  } 
				setState(222);
				((Member_expressionContext)_localctx).IDENTIFIER = match(IDENTIFIER);
				 nestedAssignmentName = factory.createStringLiteral(((Member_expressionContext)_localctx).IDENTIFIER, false);
				                                                  ((Member_expressionContext)_localctx).result =  factory.createReadProperty(receiver, nestedAssignmentName); 
				}
				break;
			case T__28:
				{
				setState(224);
				match(T__28);
				 if (receiver == null) {
				                                                      receiver = factory.createRead(assignmentName);
				                                                  } 
				setState(226);
				((Member_expressionContext)_localctx).expression = expression();
				 nestedAssignmentName = ((Member_expressionContext)_localctx).expression.result;
				                                                  ((Member_expressionContext)_localctx).result =  factory.createReadProperty(receiver, nestedAssignmentName); 
				setState(228);
				match(T__29);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(235);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,17,_ctx) ) {
			case 1:
				{
				setState(232);
				((Member_expressionContext)_localctx).member_expression = member_expression(_localctx.result, receiver, nestedAssignmentName);
				 ((Member_expressionContext)_localctx).result =  ((Member_expressionContext)_localctx).member_expression.result; 
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

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\'\u00f0\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\3\2\3\2\7\2!\n\2\f\2\16\2$\13"+
		"\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\7\3\61\n\3\f\3\16\3\64"+
		"\13\3\5\3\66\n\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\7\4A\n\4\f\4\16\4"+
		"D\13\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5"+
		"\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\5\5_\n\5\3\6\3\6\3\6\3\6\3\6\3\6"+
		"\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\5\7r\n\7\3\7\3\7\3\b\3\b"+
		"\3\b\3\b\3\b\5\b{\n\b\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\7\t\u0086\n"+
		"\t\f\t\16\t\u0089\13\t\3\n\3\n\3\n\3\n\3\n\3\n\7\n\u0091\n\n\f\n\16\n"+
		"\u0094\13\n\3\13\3\13\3\13\3\13\3\13\3\13\5\13\u009c\n\13\3\f\3\f\3\f"+
		"\3\f\3\f\3\f\7\f\u00a4\n\f\f\f\16\f\u00a7\13\f\3\r\3\r\3\r\3\r\3\r\3\r"+
		"\7\r\u00af\n\r\f\r\16\r\u00b2\13\r\3\16\3\16\3\16\3\16\3\16\3\16\5\16"+
		"\u00ba\n\16\3\16\3\16\3\16\3\16\3\16\3\16\3\16\3\16\3\16\3\16\3\16\5\16"+
		"\u00c7\n\16\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\7\17\u00d2\n"+
		"\17\f\17\16\17\u00d5\13\17\5\17\u00d7\n\17\3\17\3\17\3\17\3\17\3\17\3"+
		"\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\5\17\u00e9\n\17"+
		"\3\17\3\17\3\17\5\17\u00ee\n\17\3\17\2\2\20\2\4\6\b\n\f\16\20\22\24\26"+
		"\30\32\34\2\5\3\2\23\30\3\2\31\32\3\2\33\34\2\u00fd\2\36\3\2\2\2\4\'\3"+
		"\2\2\2\6;\3\2\2\2\b^\3\2\2\2\n`\3\2\2\2\fg\3\2\2\2\16u\3\2\2\2\20\177"+
		"\3\2\2\2\22\u008a\3\2\2\2\24\u0095\3\2\2\2\26\u009d\3\2\2\2\30\u00a8\3"+
		"\2\2\2\32\u00c6\3\2\2\2\34\u00c8\3\2\2\2\36\"\5\4\3\2\37!\5\4\3\2 \37"+
		"\3\2\2\2!$\3\2\2\2\" \3\2\2\2\"#\3\2\2\2#%\3\2\2\2$\"\3\2\2\2%&\7\2\2"+
		"\3&\3\3\2\2\2\'(\7\3\2\2()\7$\2\2)*\7\4\2\2*\65\b\3\1\2+,\7$\2\2,\62\b"+
		"\3\1\2-.\7\5\2\2./\7$\2\2/\61\b\3\1\2\60-\3\2\2\2\61\64\3\2\2\2\62\60"+
		"\3\2\2\2\62\63\3\2\2\2\63\66\3\2\2\2\64\62\3\2\2\2\65+\3\2\2\2\65\66\3"+
		"\2\2\2\66\67\3\2\2\2\678\7\6\2\289\5\6\4\29:\b\3\1\2:\5\3\2\2\2;<\b\4"+
		"\1\2<B\7\7\2\2=>\5\b\5\2>?\b\4\1\2?A\3\2\2\2@=\3\2\2\2AD\3\2\2\2B@\3\2"+
		"\2\2BC\3\2\2\2CE\3\2\2\2DB\3\2\2\2EF\7\b\2\2FG\b\4\1\2G\7\3\2\2\2HI\5"+
		"\n\6\2IJ\b\5\1\2J_\3\2\2\2KL\7\t\2\2LM\b\5\1\2M_\7\n\2\2NO\7\13\2\2OP"+
		"\b\5\1\2P_\7\n\2\2QR\5\f\7\2RS\b\5\1\2S_\3\2\2\2TU\5\16\b\2UV\b\5\1\2"+
		"V_\3\2\2\2WX\5\20\t\2XY\7\n\2\2YZ\b\5\1\2Z_\3\2\2\2[\\\7\f\2\2\\]\b\5"+
		"\1\2]_\7\n\2\2^H\3\2\2\2^K\3\2\2\2^N\3\2\2\2^Q\3\2\2\2^T\3\2\2\2^W\3\2"+
		"\2\2^[\3\2\2\2_\t\3\2\2\2`a\7\r\2\2ab\7\4\2\2bc\5\20\t\2cd\7\6\2\2de\5"+
		"\6\4\2ef\b\6\1\2f\13\3\2\2\2gh\7\16\2\2hi\7\4\2\2ij\5\20\t\2jk\7\6\2\2"+
		"kl\5\6\4\2lq\b\7\1\2mn\7\17\2\2no\5\6\4\2op\b\7\1\2pr\3\2\2\2qm\3\2\2"+
		"\2qr\3\2\2\2rs\3\2\2\2st\b\7\1\2t\r\3\2\2\2uv\7\20\2\2vz\b\b\1\2wx\5\20"+
		"\t\2xy\b\b\1\2y{\3\2\2\2zw\3\2\2\2z{\3\2\2\2{|\3\2\2\2|}\b\b\1\2}~\7\n"+
		"\2\2~\17\3\2\2\2\177\u0080\5\22\n\2\u0080\u0087\b\t\1\2\u0081\u0082\7"+
		"\21\2\2\u0082\u0083\5\22\n\2\u0083\u0084\b\t\1\2\u0084\u0086\3\2\2\2\u0085"+
		"\u0081\3\2\2\2\u0086\u0089\3\2\2\2\u0087\u0085\3\2\2\2\u0087\u0088\3\2"+
		"\2\2\u0088\21\3\2\2\2\u0089\u0087\3\2\2\2\u008a\u008b\5\24\13\2\u008b"+
		"\u0092\b\n\1\2\u008c\u008d\7\22\2\2\u008d\u008e\5\24\13\2\u008e\u008f"+
		"\b\n\1\2\u008f\u0091\3\2\2\2\u0090\u008c\3\2\2\2\u0091\u0094\3\2\2\2\u0092"+
		"\u0090\3\2\2\2\u0092\u0093\3\2\2\2\u0093\23\3\2\2\2\u0094\u0092\3\2\2"+
		"\2\u0095\u0096\5\26\f\2\u0096\u009b\b\13\1\2\u0097\u0098\t\2\2\2\u0098"+
		"\u0099\5\26\f\2\u0099\u009a\b\13\1\2\u009a\u009c\3\2\2\2\u009b\u0097\3"+
		"\2\2\2\u009b\u009c\3\2\2\2\u009c\25\3\2\2\2\u009d\u009e\5\30\r\2\u009e"+
		"\u00a5\b\f\1\2\u009f\u00a0\t\3\2\2\u00a0\u00a1\5\30\r\2\u00a1\u00a2\b"+
		"\f\1\2\u00a2\u00a4\3\2\2\2\u00a3\u009f\3\2\2\2\u00a4\u00a7\3\2\2\2\u00a5"+
		"\u00a3\3\2\2\2\u00a5\u00a6\3\2\2\2\u00a6\27\3\2\2\2\u00a7\u00a5\3\2\2"+
		"\2\u00a8\u00a9\5\32\16\2\u00a9\u00b0\b\r\1\2\u00aa\u00ab\t\4\2\2\u00ab"+
		"\u00ac\5\32\16\2\u00ac\u00ad\b\r\1\2\u00ad\u00af\3\2\2\2\u00ae\u00aa\3"+
		"\2\2\2\u00af\u00b2\3\2\2\2\u00b0\u00ae\3\2\2\2\u00b0\u00b1\3\2\2\2\u00b1"+
		"\31\3\2\2\2\u00b2\u00b0\3\2\2\2\u00b3\u00b4\7$\2\2\u00b4\u00b9\b\16\1"+
		"\2\u00b5\u00b6\5\34\17\2\u00b6\u00b7\b\16\1\2\u00b7\u00ba\3\2\2\2\u00b8"+
		"\u00ba\b\16\1\2\u00b9\u00b5\3\2\2\2\u00b9\u00b8\3\2\2\2\u00ba\u00c7\3"+
		"\2\2\2\u00bb\u00bc\7%\2\2\u00bc\u00c7\b\16\1\2\u00bd\u00be\7&\2\2\u00be"+
		"\u00c7\b\16\1\2\u00bf\u00c0\7\'\2\2\u00c0\u00c7\b\16\1\2\u00c1\u00c2\7"+
		"\4\2\2\u00c2\u00c3\5\20\t\2\u00c3\u00c4\7\6\2\2\u00c4\u00c5\b\16\1\2\u00c5"+
		"\u00c7\3\2\2\2\u00c6\u00b3\3\2\2\2\u00c6\u00bb\3\2\2\2\u00c6\u00bd\3\2"+
		"\2\2\u00c6\u00bf\3\2\2\2\u00c6\u00c1\3\2\2\2\u00c7\33\3\2\2\2\u00c8\u00e8"+
		"\b\17\1\2\u00c9\u00ca\7\4\2\2\u00ca\u00d6\b\17\1\2\u00cb\u00cc\5\20\t"+
		"\2\u00cc\u00d3\b\17\1\2\u00cd\u00ce\7\5\2\2\u00ce\u00cf\5\20\t\2\u00cf"+
		"\u00d0\b\17\1\2\u00d0\u00d2\3\2\2\2\u00d1\u00cd\3\2\2\2\u00d2\u00d5\3"+
		"\2\2\2\u00d3\u00d1\3\2\2\2\u00d3\u00d4\3\2\2\2\u00d4\u00d7\3\2\2\2\u00d5"+
		"\u00d3\3\2\2\2\u00d6\u00cb\3\2\2\2\u00d6\u00d7\3\2\2\2\u00d7\u00d8\3\2"+
		"\2\2\u00d8\u00d9\7\6\2\2\u00d9\u00e9\b\17\1\2\u00da\u00db\7\35\2\2\u00db"+
		"\u00dc\5\20\t\2\u00dc\u00dd\b\17\1\2\u00dd\u00e9\3\2\2\2\u00de\u00df\7"+
		"\36\2\2\u00df\u00e0\b\17\1\2\u00e0\u00e1\7$\2\2\u00e1\u00e9\b\17\1\2\u00e2"+
		"\u00e3\7\37\2\2\u00e3\u00e4\b\17\1\2\u00e4\u00e5\5\20\t\2\u00e5\u00e6"+
		"\b\17\1\2\u00e6\u00e7\7 \2\2\u00e7\u00e9\3\2\2\2\u00e8\u00c9\3\2\2\2\u00e8"+
		"\u00da\3\2\2\2\u00e8\u00de\3\2\2\2\u00e8\u00e2\3\2\2\2\u00e9\u00ed\3\2"+
		"\2\2\u00ea\u00eb\5\34\17\2\u00eb\u00ec\b\17\1\2\u00ec\u00ee\3\2\2\2\u00ed"+
		"\u00ea\3\2\2\2\u00ed\u00ee\3\2\2\2\u00ee\35\3\2\2\2\24\"\62\65B^qz\u0087"+
		"\u0092\u009b\u00a5\u00b0\u00b9\u00c6\u00d3\u00d6\u00e8\u00ed";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}