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
package org.jitcijk.pryst;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;

import com.oracle.truffle.api.CallTarget;
import com.oracle.truffle.api.RootCallTarget;
import com.oracle.truffle.api.Scope;
import com.oracle.truffle.api.Truffle;
import com.oracle.truffle.api.TruffleLanguage;
import com.oracle.truffle.api.TruffleLanguage.ContextPolicy;
import com.oracle.truffle.api.debug.DebuggerTags;
import com.oracle.truffle.api.dsl.NodeFactory;
import com.oracle.truffle.api.frame.Frame;
import com.oracle.truffle.api.instrumentation.AllocationReporter;
import com.oracle.truffle.api.instrumentation.ProvidedTags;
import com.oracle.truffle.api.instrumentation.StandardTags;
import com.oracle.truffle.api.interop.InteropLibrary;
import com.oracle.truffle.api.nodes.Node;
import com.oracle.truffle.api.nodes.RootNode;
import com.oracle.truffle.api.object.DynamicObject;
import com.oracle.truffle.api.object.DynamicObjectLibrary;
import com.oracle.truffle.api.object.Shape;
import com.oracle.truffle.api.source.Source;
import org.jitcijk.pryst.builtins.PrystBuiltinNode;
import org.jitcijk.pryst.builtins.PrystDefineFunctionBuiltin;
import org.jitcijk.pryst.builtins.PrystNanoTimeBuiltin;
import org.jitcijk.pryst.builtins.PrystPrintlnBuiltin;
import org.jitcijk.pryst.builtins.PrystReadlnBuiltin;
import org.jitcijk.pryst.builtins.PrystStackTraceBuiltin;
import org.jitcijk.pryst.nodes.PrystEvalRootNode;
import org.jitcijk.pryst.nodes.PrystTypes;
import org.jitcijk.pryst.nodes.controlflow.PrystBlockNode;
import org.jitcijk.pryst.nodes.controlflow.PrystBreakNode;
import org.jitcijk.pryst.nodes.controlflow.PrystContinueNode;
import org.jitcijk.pryst.nodes.controlflow.PrystDebuggerNode;
import org.jitcijk.pryst.nodes.controlflow.PrystIfNode;
import org.jitcijk.pryst.nodes.controlflow.PrystReturnNode;
import org.jitcijk.pryst.nodes.controlflow.PrystWhileNode;
import org.jitcijk.pryst.nodes.expression.PrystAddNode;
import org.jitcijk.pryst.nodes.expression.PrystBigIntegerLiteralNode;
import org.jitcijk.pryst.nodes.expression.PrystDivNode;
import org.jitcijk.pryst.nodes.expression.PrystEqualNode;
import org.jitcijk.pryst.nodes.expression.PrystFunctionLiteralNode;
import org.jitcijk.pryst.nodes.expression.PrystInvokeNode;
import org.jitcijk.pryst.nodes.expression.PrystLessOrEqualNode;
import org.jitcijk.pryst.nodes.expression.PrystLessThanNode;
import org.jitcijk.pryst.nodes.expression.PrystLogicalAndNode;
import org.jitcijk.pryst.nodes.expression.PrystLogicalOrNode;
import org.jitcijk.pryst.nodes.expression.PrystMulNode;
import org.jitcijk.pryst.nodes.expression.PrystReadPropertyNode;
import org.jitcijk.pryst.nodes.expression.PrystStringLiteralNode;
import org.jitcijk.pryst.nodes.expression.PrystSubNode;
import org.jitcijk.pryst.nodes.expression.PrystWritePropertyNode;
import org.jitcijk.pryst.nodes.local.PrystLexicalScope;
import org.jitcijk.pryst.nodes.local.PrystReadLocalVariableNode;
import org.jitcijk.pryst.nodes.local.PrystWriteLocalVariableNode;
import org.jitcijk.pryst.parser.PrystNodeFactory;
import org.jitcijk.pryst.parser.PrystLexer;
import org.jitcijk.pryst.parser.PrystParser;
import org.jitcijk.pryst.runtime.PrystBigNumber;
import org.jitcijk.pryst.runtime.PrystContext;
import org.jitcijk.pryst.runtime.PrystFunction;
import org.jitcijk.pryst.runtime.PrystFunctionRegistry;
import org.jitcijk.pryst.runtime.PrystLanguageView;
import org.jitcijk.pryst.runtime.PrystNull;
import org.jitcijk.pryst.runtime.PrystObject;

/**
 * Pryst is a simple language to demonstrate and showcase features of Truffle. The implementation is as
 * simple and clean as possible in order to help understanding the ideas and concepts of Truffle.
 * The language has first class functions, and objects are key-value stores.
 * <p>
 * Pryst is statically typed, i.e., there are type names specified by the programmer. Pryst is
 * strongly typed, i.e., there is no automatic conversion between types. If an operation is not
 * available for the types encountered at run time, a type error is reported and execution is
 * stopped. For example, {@code 4 - "2"} results in a type error because subtraction is only defined
 * for numbers.
 *
 * <p>
 * <b>Types:</b>
 * <ul>
 * <li>Number: arbitrary precision integer numbers. The implementation uses the Java primitive type
 * {@code long} to represent numbers that fit into the 64 bit range, and {@link PrystBigNumber} for
 * numbers that exceed the range. Using a primitive type such as {@code long} is crucial for
 * performance.
 * <li>Boolean: implemented as the Java primitive type {@code boolean}.
 * <li>String: implemented as the Java standard type {@link String}.
 * <li>Function: implementation type {@link PrystFunction}.
 * <li>Object: efficient implementation using the object model provided by Truffle. The
 * implementation type of objects is a subclass of {@link DynamicObject}.
 * <li>Null (with only one value {@code null}): implemented as the singleton
 * {@link PrystNull#SINGLETON}.
 * </ul>
 * The class {@link PrystTypes} lists these types for the Truffle DSL, i.e., for type-specialized
 * operations that are specified using Truffle DSL annotations.
 *
 * <p>
 * <b>Language concepts:</b>
 * <ul>
 * <li>Literals for {@link PrystBigIntegerLiteralNode numbers} , {@link PrystStringLiteralNode strings},
 * and {@link PrystFunctionLiteralNode functions}.
 * <li>Basic arithmetic, logical, and comparison operations: {@link PrystAddNode +}, {@link PrystSubNode
 * -}, {@link PrystMulNode *}, {@link PrystDivNode /}, {@link PrystLogicalAndNode logical and},
 * {@link PrystLogicalOrNode logical or}, {@link PrystEqualNode ==}, !=, {@link PrystLessThanNode &lt;},
 * {@link PrystLessOrEqualNode &le;}, &gt;, &ge;.
 * <li>Local variables: local variables must be defined (via a {@link PrystWriteLocalVariableNode
 * write}) before they can be used (by a {@link PrystReadLocalVariableNode read}). Local variables are
 * not visible outside of the block where they were first defined.
 * <li>Basic control flow statements: {@link PrystBlockNode blocks}, {@link PrystIfNode if},
 * {@link PrystWhileNode while} with {@link PrystBreakNode break} and {@link PrystContinueNode continue},
 * {@link PrystReturnNode return}.
 * <li>Debugging control: {@link PrystDebuggerNode debugger} statement uses
 * {@link DebuggerTags#AlwaysHalt} tag to halt the execution when run under the debugger.
 * <li>Function calls: {@link PrystInvokeNode invocations} are efficiently implemented with
 * {@link PrystDispatchNode polymorphic inline caches}.
 * <li>Object access: {@link PrystReadPropertyNode} and {@link PrystWritePropertyNode} use a cached
 * {@link DynamicObjectLibrary} as the polymorphic inline cache for property reads and writes,
 * respectively.
 * </ul>
 *
 * <p>
 * <b>Syntax and parsing:</b><br>
 * The syntax is described as an attributed grammar. The {@link PrystParser} and
 * {@link PrystLexer} are automatically generated by ANTLR 4. The grammar contains semantic
 * actions that build the AST for a method. To keep these semantic actions short, they are mostly
 * calls to the {@link PrystNodeFactory} that performs the actual node creation. All functions found in
 * the Pryst source are added to the {@link PrystFunctionRegistry}, which is accessible from the
 * {@link PrystContext}.
 *
 * <p>
 * <b>Builtin functions:</b><br>
 * Library functions that are available to every Pryst source without prior definition are called
 * builtin functions. They are added to the {@link PrystFunctionRegistry} when the {@link PrystContext} is
 * created. Some of the current builtin functions are
 * <ul>
 * <li>{@link PrystReadlnBuiltin readln}: Read a String from the {@link PrystContext#getInput() standard
 * input}.
 * <li>{@link PrystPrintlnBuiltin println}: Write a value to the {@link PrystContext#getOutput() standard
 * output}.
 * <li>{@link PrystNanoTimeBuiltin nanoTime}: Returns the value of a high-resolution time, in
 * nanoseconds.
 * <li>{@link PrystDefineFunctionBuiltin defineFunction}: Parses the functions provided as a String
 * argument and adds them to the function registry. Functions that are already defined are replaced
 * with the new version.
 * <li>{@link PrystStackTraceBuiltin stckTrace}: Print all function activations with all local
 * variables.
 * </ul>
 */
@TruffleLanguage.Registration(id = PrystLanguage.ID, name = "Pryst", defaultMimeType = PrystLanguage.MIME_TYPE, characterMimeTypes = PrystLanguage.MIME_TYPE, contextPolicy = ContextPolicy.SHARED, fileTypeDetectors = PrystFileDetector.class)
@ProvidedTags({StandardTags.CallTag.class, StandardTags.StatementTag.class, StandardTags.RootTag.class, StandardTags.RootBodyTag.class, StandardTags.ExpressionTag.class, DebuggerTags.AlwaysHalt.class,
                StandardTags.ReadVariableTag.class, StandardTags.WriteVariableTag.class})
public final class PrystLanguage extends TruffleLanguage<PrystContext> {
    public static volatile int counter;

    public static final String ID = "pryst";
    public static final String MIME_TYPE = "application/x-pryst";

    private final Shape rootShape;

    public PrystLanguage() {
        counter++;
        this.rootShape = Shape.newBuilder().layout(PrystObject.class).build();
    }

    @Override
    protected PrystContext createContext(Env env) {
        return new PrystContext(this, env, new ArrayList<>(EXTERNAL_BUILTINS));
    }

    @Override
    protected CallTarget parse(ParsingRequest request) throws Exception {
        Source source = request.getSource();
        Map<String, RootCallTarget> functions;
        /*
         * Parse the provided source. At this point, we do not have a PrystContext yet. Registration of
         * the functions with the PrystContext happens lazily in PrystEvalRootNode.
         */
        if (request.getArgumentNames().isEmpty()) {
            functions = PrystParser.parsePryst(this, source);
        } else {
            StringBuilder sb = new StringBuilder();
            sb.append("function main(");
            String sep = "";
            for (String argumentName : request.getArgumentNames()) {
                sb.append(sep);
                sb.append(argumentName);
                sep = ",";
            }
            sb.append(") { return ");
            sb.append(source.getCharacters());
            sb.append(";}");
            String language = source.getLanguage() == null ? ID : source.getLanguage();
            Source decoratedSource = Source.newBuilder(language, sb.toString(), source.getName()).build();
            functions = PrystParser.parsePryst(this, decoratedSource);
        }

        RootCallTarget main = functions.get("main");
        RootNode evalMain;
        if (main != null) {
            /*
             * We have a main function, so "evaluating" the parsed source means invoking that main
             * function. However, we need to lazily register functions into the PrystContext first, so
             * we cannot use the original PrystRootNode for the main function. Instead, we create a new
             * PrystEvalRootNode that does everything we need.
             */
            evalMain = new PrystEvalRootNode(this, main, functions);
        } else {
            /*
             * Even without a main function, "evaluating" the parsed source needs to register the
             * functions into the PrystContext.
             */
            evalMain = new PrystEvalRootNode(this, null, functions);
        }
        return Truffle.getRuntime().createCallTarget(evalMain);
    }

    @Override
    protected Object getLanguageView(PrystContext context, Object value) {
        return PrystLanguageView.create(value);
    }

    /*
     * Still necessary for the old Pryst TCK to pass. We should remove with the old TCK. New language
     * should not override this.
     */
    @SuppressWarnings("deprecation")
    @Override
    protected Object findExportedSymbol(PrystContext context, String globalName, boolean onlyExplicit) {
        return context.getFunctionRegistry().lookup(globalName, false);
    }

    @Override
    protected boolean isVisible(PrystContext context, Object value) {
        return !InteropLibrary.getFactory().getUncached(value).isNull(value);
    }

    @Override
    public Iterable<Scope> findLocalScopes(PrystContext context, Node node, Frame frame) {
        final PrystLexicalScope scope = PrystLexicalScope.createScope(node);
        return new Iterable<Scope>() {
            @Override
            public Iterator<Scope> iterator() {
                return new Iterator<Scope>() {
                    private PrystLexicalScope previousScope;
                    private PrystLexicalScope nextScope = scope;

                    @Override
                    public boolean hasNext() {
                        if (nextScope == null) {
                            nextScope = previousScope.findParent();
                        }
                        return nextScope != null;
                    }

                    @Override
                    public Scope next() {
                        if (!hasNext()) {
                            throw new NoSuchElementException();
                        }
                        Object functionObject = findFunctionObject();
                        Scope vscope = Scope.newBuilder(nextScope.getName(), nextScope.getVariables(frame)).node(nextScope.getNode()).arguments(nextScope.getArguments(frame)).rootInstance(
                                        functionObject).build();
                        previousScope = nextScope;
                        nextScope = null;
                        return vscope;
                    }

                    private Object findFunctionObject() {
                        String name = node.getRootNode().getName();
                        return context.getFunctionRegistry().getFunction(name);
                    }
                };
            }
        };
    }

    @Override
    protected Iterable<Scope> findTopScopes(PrystContext context) {
        return context.getTopScopes();
    }

    public Shape getRootShape() {
        return rootShape;
    }

    /**
     * Allocate an empty object. All new objects initially have no properties. Properties are added
     * when they are first stored, i.e., the store triggers a shape change of the object.
     */
    public PrystObject createObject(AllocationReporter reporter) {
        reporter.onEnter(null, 0, AllocationReporter.SIZE_UNKNOWN);
        PrystObject object = new PrystObject(rootShape);
        reporter.onReturnValue(object, 0, AllocationReporter.SIZE_UNKNOWN);
        return object;
    }

    public static PrystContext getCurrentContext() {
        return getCurrentContext(PrystLanguage.class);
    }

    private static final List<NodeFactory<? extends PrystBuiltinNode>> EXTERNAL_BUILTINS = Collections.synchronizedList(new ArrayList<>());

    public static void installBuiltin(NodeFactory<? extends PrystBuiltinNode> builtin) {
        EXTERNAL_BUILTINS.add(builtin);
    }

}
