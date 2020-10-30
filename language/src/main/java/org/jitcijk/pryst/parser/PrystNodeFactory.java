/*
 * The MIT License
 *
 * Copyright (c) 2020 Jitcijk Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package org.jitcijk.pryst.parser;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.antlr.v4.runtime.Parser;
import org.antlr.v4.runtime.Token;

import com.oracle.truffle.api.RootCallTarget;
import com.oracle.truffle.api.Truffle;
import com.oracle.truffle.api.frame.FrameDescriptor;
import com.oracle.truffle.api.frame.FrameSlot;
import com.oracle.truffle.api.frame.FrameSlotKind;
import com.oracle.truffle.api.source.Source;
import com.oracle.truffle.api.source.SourceSection;
import org.jitcijk.pryst.PrystLanguage;
import org.jitcijk.pryst.nodes.PrystExpressionNode;
import org.jitcijk.pryst.nodes.PrystRootNode;
import org.jitcijk.pryst.nodes.PrystStatementNode;
import org.jitcijk.pryst.nodes.controlflow.PrystBlockNode;
import org.jitcijk.pryst.nodes.controlflow.PrystBreakNode;
import org.jitcijk.pryst.nodes.controlflow.PrystContinueNode;
import org.jitcijk.pryst.nodes.controlflow.PrystDebuggerNode;
import org.jitcijk.pryst.nodes.controlflow.PrystFunctionBodyNode;
import org.jitcijk.pryst.nodes.controlflow.PrystIfNode;
import org.jitcijk.pryst.nodes.controlflow.PrystReturnNode;
import org.jitcijk.pryst.nodes.controlflow.PrystWhileNode;
import org.jitcijk.pryst.nodes.expression.PrystAddNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystBigIntegerLiteralNode;
import org.jitcijk.pryst.nodes.expression.PrystDivNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystEqualNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystFunctionLiteralNode;
import org.jitcijk.pryst.nodes.expression.PrystInvokeNode;
import org.jitcijk.pryst.nodes.expression.PrystLessOrEqualNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystLessThanNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystLogicalAndNode;
import org.jitcijk.pryst.nodes.expression.PrystLogicalNotNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystLogicalOrNode;
import org.jitcijk.pryst.nodes.expression.PrystLongLiteralNode;
import org.jitcijk.pryst.nodes.expression.PrystMulNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystParenExpressionNode;
import org.jitcijk.pryst.nodes.expression.PrystReadPropertyNode;
import org.jitcijk.pryst.nodes.expression.PrystReadPropertyNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystStringLiteralNode;
import org.jitcijk.pryst.nodes.expression.PrystSubNodeGen;
import org.jitcijk.pryst.nodes.expression.PrystWritePropertyNode;
import org.jitcijk.pryst.nodes.expression.PrystWritePropertyNodeGen;
import org.jitcijk.pryst.nodes.local.PrystReadArgumentNode;
import org.jitcijk.pryst.nodes.local.PrystReadLocalVariableNode;
import org.jitcijk.pryst.nodes.local.PrystReadLocalVariableNodeGen;
import org.jitcijk.pryst.nodes.local.PrystWriteLocalVariableNode;
import org.jitcijk.pryst.nodes.local.PrystWriteLocalVariableNodeGen;
import org.jitcijk.pryst.nodes.util.PrystUnboxNodeGen;

/**
 * Helper class used by the Pryst {@link Parser} to create nodes. The code is factored out of the
 * automatically generated parser to keep the attributed grammar of Pryst small.
 */
public class PrystNodeFactory {

    /**
     * Local variable names that are visible in the current block. Variables are not visible outside
     * of their defining block, to prevent the usage of undefined variables. Because of that, we can
     * decide during parsing if a name references a local variable or is a function name.
     */
    static class LexicalScope {
        protected final LexicalScope outer;
        protected final Map<String, FrameSlot> locals;

        LexicalScope(LexicalScope outer) {
            this.outer = outer;
            this.locals = new HashMap<>();
            if (outer != null) {
                locals.putAll(outer.locals);
            }
        }
    }

    /* State while parsing a source unit. */
    private final Source source;
    private final Map<String, RootCallTarget> allFunctions;

    /* State while parsing a function. */
    private int functionStartPos;
    private String functionName;
    private int functionBodyStartPos; // includes parameter list
    private int parameterCount;
    private FrameDescriptor frameDescriptor;
    private List<PrystStatementNode> methodNodes;

    /* State while parsing a block. */
    private LexicalScope lexicalScope;
    private final PrystLanguage language;

    public PrystNodeFactory(PrystLanguage language, Source source) {
        this.language = language;
        this.source = source;
        this.allFunctions = new HashMap<>();
    }

    public Map<String, RootCallTarget> getAllFunctions() {
        return allFunctions;
    }

    public void startFunction(Token nameToken, Token bodyStartToken) {
        assert functionStartPos == 0;
        assert functionName == null;
        assert functionBodyStartPos == 0;
        assert parameterCount == 0;
        assert frameDescriptor == null;
        assert lexicalScope == null;

        functionStartPos = nameToken.getStartIndex();
        functionName = nameToken.getText();
        functionBodyStartPos = bodyStartToken.getStartIndex();
        frameDescriptor = new FrameDescriptor();
        methodNodes = new ArrayList<>();
        startBlock();
    }

    public void addFormalParameter(Token nameToken) {
        /*
         * Method parameters are assigned to local variables at the beginning of the method. This
         * ensures that accesses to parameters are specialized the same way as local variables are
         * specialized.
         */
        final PrystReadArgumentNode readArg = new PrystReadArgumentNode(parameterCount);
        PrystExpressionNode assignment = createAssignment(createStringLiteral(nameToken, false), readArg, parameterCount);
        methodNodes.add(assignment);
        parameterCount++;
    }

    public void finishFunction(PrystStatementNode bodyNode) {
        if (bodyNode == null) {
            // a state update that would otherwise be performed by finishBlock
            lexicalScope = lexicalScope.outer;
        } else {
            methodNodes.add(bodyNode);
            final int bodyEndPos = bodyNode.getSourceEndIndex();
            final SourceSection functionSrc = source.createSection(functionStartPos, bodyEndPos - functionStartPos);
            final PrystStatementNode methodBlock = finishBlock(methodNodes, functionBodyStartPos, bodyEndPos - functionBodyStartPos);
            assert lexicalScope == null : "Wrong scoping of blocks in parser";

            final PrystFunctionBodyNode functionBodyNode = new PrystFunctionBodyNode(methodBlock);
            functionBodyNode.setSourceSection(functionSrc.getCharIndex(), functionSrc.getCharLength());

            final PrystRootNode rootNode = new PrystRootNode(language, frameDescriptor, functionBodyNode, functionSrc, functionName);
            allFunctions.put(functionName, Truffle.getRuntime().createCallTarget(rootNode));
        }

        functionStartPos = 0;
        functionName = null;
        functionBodyStartPos = 0;
        parameterCount = 0;
        frameDescriptor = null;
        lexicalScope = null;
    }

    public void startBlock() {
        lexicalScope = new LexicalScope(lexicalScope);
    }

    public PrystStatementNode finishBlock(List<PrystStatementNode> bodyNodes, int startPos, int length) {
        lexicalScope = lexicalScope.outer;

        if (containsNull(bodyNodes)) {
            return null;
        }

        List<PrystStatementNode> flattenedNodes = new ArrayList<>(bodyNodes.size());
        flattenBlocks(bodyNodes, flattenedNodes);
        for (PrystStatementNode statement : flattenedNodes) {
            if (statement.hasSource() && !isHaltInCondition(statement)) {
                statement.addStatementTag();
            }
        }
        PrystBlockNode blockNode = new PrystBlockNode(flattenedNodes.toArray(new PrystStatementNode[flattenedNodes.size()]));
        blockNode.setSourceSection(startPos, length);
        return blockNode;
    }

    private static boolean isHaltInCondition(PrystStatementNode statement) {
        return (statement instanceof PrystIfNode) || (statement instanceof PrystWhileNode);
    }

    private void flattenBlocks(Iterable<? extends PrystStatementNode> bodyNodes, List<PrystStatementNode> flattenedNodes) {
        for (PrystStatementNode n : bodyNodes) {
            if (n instanceof PrystBlockNode) {
                flattenBlocks(((PrystBlockNode) n).getStatements(), flattenedNodes);
            } else {
                flattenedNodes.add(n);
            }
        }
    }

    /**
     * Returns an {@link PrystDebuggerNode} for the given token.
     *
     * @param debuggerToken The token containing the debugger node's info.
     * @return A PrystDebuggerNode for the given token.
     */
    PrystStatementNode createDebugger(Token debuggerToken) {
        final PrystDebuggerNode debuggerNode = new PrystDebuggerNode();
        srcFromToken(debuggerNode, debuggerToken);
        return debuggerNode;
    }

    /**
     * Returns an {@link PrystBreakNode} for the given token.
     *
     * @param breakToken The token containing the break node's info.
     * @return A PrystBreakNode for the given token.
     */
    public PrystStatementNode createBreak(Token breakToken) {
        final PrystBreakNode breakNode = new PrystBreakNode();
        srcFromToken(breakNode, breakToken);
        return breakNode;
    }

    /**
     * Returns an {@link PrystContinueNode} for the given token.
     *
     * @param continueToken The token containing the continue node's info.
     * @return A PrystContinueNode built using the given token.
     */
    public PrystStatementNode createContinue(Token continueToken) {
        final PrystContinueNode continueNode = new PrystContinueNode();
        srcFromToken(continueNode, continueToken);
        return continueNode;
    }

    /**
     * Returns an {@link PrystWhileNode} for the given parameters.
     *
     * @param whileToken The token containing the while node's info
     * @param conditionNode The conditional node for this while loop
     * @param bodyNode The body of the while loop
     * @return A PrystWhileNode built using the given parameters. null if either conditionNode or
     *         bodyNode is null.
     */
    public PrystStatementNode createWhile(Token whileToken, PrystExpressionNode conditionNode, PrystStatementNode bodyNode) {
        if (conditionNode == null || bodyNode == null) {
            return null;
        }

        conditionNode.addStatementTag();
        final int start = whileToken.getStartIndex();
        final int end = bodyNode.getSourceEndIndex();
        final PrystWhileNode whileNode = new PrystWhileNode(conditionNode, bodyNode);
        whileNode.setSourceSection(start, end - start);
        return whileNode;
    }

    /**
     * Returns an {@link PrystIfNode} for the given parameters.
     *
     * @param ifToken The token containing the if node's info
     * @param conditionNode The condition node of this if statement
     * @param thenPartNode The then part of the if
     * @param elsePartNode The else part of the if (null if no else part)
     * @return An PrystIfNode for the given parameters. null if either conditionNode or thenPartNode is
     *         null.
     */
    public PrystStatementNode createIf(Token ifToken, PrystExpressionNode conditionNode, PrystStatementNode thenPartNode, PrystStatementNode elsePartNode) {
        if (conditionNode == null || thenPartNode == null) {
            return null;
        }

        conditionNode.addStatementTag();
        final int start = ifToken.getStartIndex();
        final int end = elsePartNode == null ? thenPartNode.getSourceEndIndex() : elsePartNode.getSourceEndIndex();
        final PrystIfNode ifNode = new PrystIfNode(conditionNode, thenPartNode, elsePartNode);
        ifNode.setSourceSection(start, end - start);
        return ifNode;
    }

    /**
     * Returns an {@link PrystReturnNode} for the given parameters.
     *
     * @param t The token containing the return node's info
     * @param valueNode The value of the return (null if not returning a value)
     * @return An PrystReturnNode for the given parameters.
     */
    public PrystStatementNode createReturn(Token t, PrystExpressionNode valueNode) {
        final int start = t.getStartIndex();
        final int length = valueNode == null ? t.getText().length() : valueNode.getSourceEndIndex() - start;
        final PrystReturnNode returnNode = new PrystReturnNode(valueNode);
        returnNode.setSourceSection(start, length);
        return returnNode;
    }

    /**
     * Returns the corresponding subclass of {@link PrystExpressionNode} for binary expressions. </br>
     * These nodes are currently not instrumented.
     *
     * @param opToken The operator of the binary expression
     * @param leftNode The left node of the expression
     * @param rightNode The right node of the expression
     * @return A subclass of PrystExpressionNode using the given parameters based on the given opToken.
     *         null if either leftNode or rightNode is null.
     */
    public PrystExpressionNode createBinary(Token opToken, PrystExpressionNode leftNode, PrystExpressionNode rightNode) {
        if (leftNode == null || rightNode == null) {
            return null;
        }
        final PrystExpressionNode leftUnboxed = PrystUnboxNodeGen.create(leftNode);
        final PrystExpressionNode rightUnboxed = PrystUnboxNodeGen.create(rightNode);

        final PrystExpressionNode result;
        switch (opToken.getText()) {
            case "+":
                result = PrystAddNodeGen.create(leftUnboxed, rightUnboxed);
                break;
            case "*":
                result = PrystMulNodeGen.create(leftUnboxed, rightUnboxed);
                break;
            case "/":
                result = PrystDivNodeGen.create(leftUnboxed, rightUnboxed);
                break;
            case "-":
                result = PrystSubNodeGen.create(leftUnboxed, rightUnboxed);
                break;
            case "<":
                result = PrystLessThanNodeGen.create(leftUnboxed, rightUnboxed);
                break;
            case "<=":
                result = PrystLessOrEqualNodeGen.create(leftUnboxed, rightUnboxed);
                break;
            case ">":
                result = PrystLogicalNotNodeGen.create(PrystLessOrEqualNodeGen.create(leftUnboxed, rightUnboxed));
                break;
            case ">=":
                result = PrystLogicalNotNodeGen.create(PrystLessThanNodeGen.create(leftUnboxed, rightUnboxed));
                break;
            case "==":
                result = PrystEqualNodeGen.create(leftUnboxed, rightUnboxed);
                break;
            case "!=":
                result = PrystLogicalNotNodeGen.create(PrystEqualNodeGen.create(leftUnboxed, rightUnboxed));
                break;
            case "&&":
                result = new PrystLogicalAndNode(leftUnboxed, rightUnboxed);
                break;
            case "||":
                result = new PrystLogicalOrNode(leftUnboxed, rightUnboxed);
                break;
            default:
                throw new RuntimeException("unexpected operation: " + opToken.getText());
        }

        int start = leftNode.getSourceCharIndex();
        int length = rightNode.getSourceEndIndex() - start;
        result.setSourceSection(start, length);
        result.addExpressionTag();

        return result;
    }

    /**
     * Returns an {@link PrystInvokeNode} for the given parameters.
     *
     * @param functionNode The function being called
     * @param parameterNodes The parameters of the function call
     * @param finalToken A token used to determine the end of the sourceSelection for this call
     * @return An PrystInvokeNode for the given parameters. null if functionNode or any of the
     *         parameterNodes are null.
     */
    public PrystExpressionNode createCall(PrystExpressionNode functionNode, List<PrystExpressionNode> parameterNodes, Token finalToken) {
        if (functionNode == null || containsNull(parameterNodes)) {
            return null;
        }

        final PrystExpressionNode result = new PrystInvokeNode(functionNode, parameterNodes.toArray(new PrystExpressionNode[parameterNodes.size()]));

        final int startPos = functionNode.getSourceCharIndex();
        final int endPos = finalToken.getStartIndex() + finalToken.getText().length();
        result.setSourceSection(startPos, endPos - startPos);
        result.addExpressionTag();

        return result;
    }

    /**
     * Returns an {@link PrystWriteLocalVariableNode} for the given parameters.
     *
     * @param nameNode The name of the variable being assigned
     * @param valueNode The value to be assigned
     * @return An PrystExpressionNode for the given parameters. null if nameNode or valueNode is null.
     */
    public PrystExpressionNode createAssignment(PrystExpressionNode nameNode, PrystExpressionNode valueNode) {
        return createAssignment(nameNode, valueNode, null);
    }

    /**
     * Returns an {@link PrystWriteLocalVariableNode} for the given parameters.
     *
     * @param nameNode The name of the variable being assigned
     * @param valueNode The value to be assigned
     * @param argumentIndex null or index of the argument the assignment is assigning
     * @return An PrystExpressionNode for the given parameters. null if nameNode or valueNode is null.
     */
    public PrystExpressionNode createAssignment(PrystExpressionNode nameNode, PrystExpressionNode valueNode, Integer argumentIndex) {
        if (nameNode == null || valueNode == null) {
            return null;
        }

        String name = ((PrystStringLiteralNode) nameNode).executeGeneric(null);
        FrameSlot frameSlot = frameDescriptor.findOrAddFrameSlot(
                        name,
                        argumentIndex,
                        FrameSlotKind.Illegal);
        lexicalScope.locals.put(name, frameSlot);
        final PrystExpressionNode result = PrystWriteLocalVariableNodeGen.create(valueNode, frameSlot, nameNode);

        if (valueNode.hasSource()) {
            final int start = nameNode.getSourceCharIndex();
            final int length = valueNode.getSourceEndIndex() - start;
            result.setSourceSection(start, length);
        }
        result.addExpressionTag();

        return result;
    }

    /**
     * Returns a {@link PrystReadLocalVariableNode} if this read is a local variable or a
     * {@link PrystFunctionLiteralNode} if this read is global. In Pryst, the only global names are
     * functions.
     *
     * @param nameNode The name of the variable/function being read
     * @return either:
     *         <ul>
     *         <li>A PrystReadLocalVariableNode representing the local variable being read.</li>
     *         <li>A PrystFunctionLiteralNode representing the function definition.</li>
     *         <li>null if nameNode is null.</li>
     *         </ul>
     */
    public PrystExpressionNode createRead(PrystExpressionNode nameNode) {
        if (nameNode == null) {
            return null;
        }

        String name = ((PrystStringLiteralNode) nameNode).executeGeneric(null);
        final PrystExpressionNode result;
        final FrameSlot frameSlot = lexicalScope.locals.get(name);
        if (frameSlot != null) {
            /* Read of a local variable. */
            result = PrystReadLocalVariableNodeGen.create(frameSlot);
        } else {
            /* Read of a global name. In our language, the only global names are functions. */
            result = new PrystFunctionLiteralNode(name);
        }
        result.setSourceSection(nameNode.getSourceCharIndex(), nameNode.getSourceLength());
        result.addExpressionTag();
        return result;
    }

    public PrystExpressionNode createStringLiteral(Token literalToken, boolean removeQuotes) {
        /* Remove the trailing and ending " */
        String literal = literalToken.getText();
        if (removeQuotes) {
            assert literal.length() >= 2 && literal.startsWith("\"") && literal.endsWith("\"");
            literal = literal.substring(1, literal.length() - 1);
        }

        final PrystStringLiteralNode result = new PrystStringLiteralNode(literal.intern());
        srcFromToken(result, literalToken);
        result.addExpressionTag();
        return result;
    }

    public PrystExpressionNode createNumericLiteral(Token literalToken) {
        PrystExpressionNode result;
        try {
            /* Try if the literal is small enough to fit into a long value. */
            result = new PrystLongLiteralNode(Long.parseLong(literalToken.getText()));
        } catch (NumberFormatException ex) {
            /* Overflow of long value, so fall back to BigInteger. */
            result = new PrystBigIntegerLiteralNode(new BigInteger(literalToken.getText()));
        }
        srcFromToken(result, literalToken);
        result.addExpressionTag();
        return result;
    }

    public PrystExpressionNode createParenExpression(PrystExpressionNode expressionNode, int start, int length) {
        if (expressionNode == null) {
            return null;
        }

        final PrystParenExpressionNode result = new PrystParenExpressionNode(expressionNode);
        result.setSourceSection(start, length);
        return result;
    }

    /**
     * Returns an {@link PrystReadPropertyNode} for the given parameters.
     *
     * @param receiverNode The receiver of the property access
     * @param nameNode The name of the property being accessed
     * @return An PrystExpressionNode for the given parameters. null if receiverNode or nameNode is
     *         null.
     */
    public PrystExpressionNode createReadProperty(PrystExpressionNode receiverNode, PrystExpressionNode nameNode) {
        if (receiverNode == null || nameNode == null) {
            return null;
        }

        final PrystExpressionNode result = PrystReadPropertyNodeGen.create(receiverNode, nameNode);

        final int startPos = receiverNode.getSourceCharIndex();
        final int endPos = nameNode.getSourceEndIndex();
        result.setSourceSection(startPos, endPos - startPos);
        result.addExpressionTag();

        return result;
    }

    /**
     * Returns an {@link PrystWritePropertyNode} for the given parameters.
     *
     * @param receiverNode The receiver object of the property assignment
     * @param nameNode The name of the property being assigned
     * @param valueNode The value to be assigned
     * @return An PrystExpressionNode for the given parameters. null if receiverNode, nameNode or
     *         valueNode is null.
     */
    public PrystExpressionNode createWriteProperty(PrystExpressionNode receiverNode, PrystExpressionNode nameNode, PrystExpressionNode valueNode) {
        if (receiverNode == null || nameNode == null || valueNode == null) {
            return null;
        }

        final PrystExpressionNode result = PrystWritePropertyNodeGen.create(receiverNode, nameNode, valueNode);

        final int start = receiverNode.getSourceCharIndex();
        final int length = valueNode.getSourceEndIndex() - start;
        result.setSourceSection(start, length);
        result.addExpressionTag();

        return result;
    }

    /**
     * Creates source description of a single token.
     */
    private static void srcFromToken(PrystStatementNode node, Token token) {
        node.setSourceSection(token.getStartIndex(), token.getText().length());
    }

    /**
     * Checks whether a list contains a null.
     */
    private static boolean containsNull(List<?> list) {
        for (Object e : list) {
            if (e == null) {
                return true;
            }
        }
        return false;
    }

}
