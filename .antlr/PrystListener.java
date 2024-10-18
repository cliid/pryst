// Generated from /Users/cliid/dev/pryst/Pryst.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link PrystParser}.
 */
public interface PrystListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link PrystParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(PrystParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(PrystParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(PrystParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(PrystParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#functionDecl}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDecl(PrystParser.FunctionDeclContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#functionDecl}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDecl(PrystParser.FunctionDeclContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#variableDecl}.
	 * @param ctx the parse tree
	 */
	void enterVariableDecl(PrystParser.VariableDeclContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#variableDecl}.
	 * @param ctx the parse tree
	 */
	void exitVariableDecl(PrystParser.VariableDeclContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#paramList}.
	 * @param ctx the parse tree
	 */
	void enterParamList(PrystParser.ParamListContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#paramList}.
	 * @param ctx the parse tree
	 */
	void exitParamList(PrystParser.ParamListContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#param}.
	 * @param ctx the parse tree
	 */
	void enterParam(PrystParser.ParamContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#param}.
	 * @param ctx the parse tree
	 */
	void exitParam(PrystParser.ParamContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(PrystParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(PrystParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(PrystParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(PrystParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#expressionStmt}.
	 * @param ctx the parse tree
	 */
	void enterExpressionStmt(PrystParser.ExpressionStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#expressionStmt}.
	 * @param ctx the parse tree
	 */
	void exitExpressionStmt(PrystParser.ExpressionStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void enterIfStmt(PrystParser.IfStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void exitIfStmt(PrystParser.IfStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void enterWhileStmt(PrystParser.WhileStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void exitWhileStmt(PrystParser.WhileStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#forStmt}.
	 * @param ctx the parse tree
	 */
	void enterForStmt(PrystParser.ForStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#forStmt}.
	 * @param ctx the parse tree
	 */
	void exitForStmt(PrystParser.ForStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#returnStmt}.
	 * @param ctx the parse tree
	 */
	void enterReturnStmt(PrystParser.ReturnStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#returnStmt}.
	 * @param ctx the parse tree
	 */
	void exitReturnStmt(PrystParser.ReturnStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#block}.
	 * @param ctx the parse tree
	 */
	void enterBlock(PrystParser.BlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#block}.
	 * @param ctx the parse tree
	 */
	void exitBlock(PrystParser.BlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(PrystParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(PrystParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#assignment}.
	 * @param ctx the parse tree
	 */
	void enterAssignment(PrystParser.AssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#assignment}.
	 * @param ctx the parse tree
	 */
	void exitAssignment(PrystParser.AssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#logicOr}.
	 * @param ctx the parse tree
	 */
	void enterLogicOr(PrystParser.LogicOrContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#logicOr}.
	 * @param ctx the parse tree
	 */
	void exitLogicOr(PrystParser.LogicOrContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#logicAnd}.
	 * @param ctx the parse tree
	 */
	void enterLogicAnd(PrystParser.LogicAndContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#logicAnd}.
	 * @param ctx the parse tree
	 */
	void exitLogicAnd(PrystParser.LogicAndContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#equality}.
	 * @param ctx the parse tree
	 */
	void enterEquality(PrystParser.EqualityContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#equality}.
	 * @param ctx the parse tree
	 */
	void exitEquality(PrystParser.EqualityContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#comparison}.
	 * @param ctx the parse tree
	 */
	void enterComparison(PrystParser.ComparisonContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#comparison}.
	 * @param ctx the parse tree
	 */
	void exitComparison(PrystParser.ComparisonContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#addition}.
	 * @param ctx the parse tree
	 */
	void enterAddition(PrystParser.AdditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#addition}.
	 * @param ctx the parse tree
	 */
	void exitAddition(PrystParser.AdditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#multiplication}.
	 * @param ctx the parse tree
	 */
	void enterMultiplication(PrystParser.MultiplicationContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#multiplication}.
	 * @param ctx the parse tree
	 */
	void exitMultiplication(PrystParser.MultiplicationContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#unary}.
	 * @param ctx the parse tree
	 */
	void enterUnary(PrystParser.UnaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#unary}.
	 * @param ctx the parse tree
	 */
	void exitUnary(PrystParser.UnaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#postfix}.
	 * @param ctx the parse tree
	 */
	void enterPostfix(PrystParser.PostfixContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#postfix}.
	 * @param ctx the parse tree
	 */
	void exitPostfix(PrystParser.PostfixContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#call}.
	 * @param ctx the parse tree
	 */
	void enterCall(PrystParser.CallContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#call}.
	 * @param ctx the parse tree
	 */
	void exitCall(PrystParser.CallContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#primary}.
	 * @param ctx the parse tree
	 */
	void enterPrimary(PrystParser.PrimaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#primary}.
	 * @param ctx the parse tree
	 */
	void exitPrimary(PrystParser.PrimaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link PrystParser#arguments}.
	 * @param ctx the parse tree
	 */
	void enterArguments(PrystParser.ArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link PrystParser#arguments}.
	 * @param ctx the parse tree
	 */
	void exitArguments(PrystParser.ArgumentsContext ctx);
}