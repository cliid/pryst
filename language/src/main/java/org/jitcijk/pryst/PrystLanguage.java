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

import com.oracle.truffle.api.*;
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
import com.oracle.truffle.api.object.Shape;
import com.oracle.truffle.api.source.Source;
import org.jitcijk.pryst.builtins.*;
import org.jitcijk.pryst.nodes.PrystEvalRootNode;
import org.jitcijk.pryst.nodes.local.PrystLexicalScope;
import org.jitcijk.pryst.parser.PrystParser;
import org.jitcijk.pryst.runtime.*;

import java.util.*;

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
        functions = PrystParser.parsePryst(this, source);

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

    @Override
    protected boolean isVisible(PrystContext context, Object value) {
        return !InteropLibrary.getFactory().getUncached(value).isNull(value);
    }

    @Override
    public Iterable<Scope> findLocalScopes(PrystContext context, Node node, Frame frame) {
        PrystLexicalScope scope = PrystLexicalScope.createScope(node);
        return () -> new Iterator<Scope>() {
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
