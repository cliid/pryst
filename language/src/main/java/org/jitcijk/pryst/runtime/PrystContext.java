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
package org.jitcijk.pryst.runtime;

import static com.oracle.truffle.api.CompilerDirectives.shouldNotReachHere;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Collections;
import java.util.List;

import com.oracle.truffle.api.CallTarget;
import com.oracle.truffle.api.CompilerDirectives.TruffleBoundary;
import com.oracle.truffle.api.Scope;
import com.oracle.truffle.api.Truffle;
import com.oracle.truffle.api.TruffleLanguage;
import com.oracle.truffle.api.TruffleLanguage.Env;
import com.oracle.truffle.api.dsl.NodeFactory;
import com.oracle.truffle.api.frame.FrameDescriptor;
import com.oracle.truffle.api.instrumentation.AllocationReporter;
import com.oracle.truffle.api.interop.TruffleObject;
import com.oracle.truffle.api.nodes.NodeInfo;
import com.oracle.truffle.api.source.Source;
import org.jitcijk.pryst.PrystLanguage;
import org.jitcijk.pryst.builtins.PrystBuiltinNode;
import org.jitcijk.pryst.builtins.PrystDefineFunctionBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystEvalBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystGetSizeBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystHasSizeBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystImportBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystIsExecutableBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystIsInstanceBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystIsNullBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystNanoTimeBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystNewObjectBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystPrintlnBuiltin;
import org.jitcijk.pryst.builtins.PrystPrintlnBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystReadlnBuiltin;
import org.jitcijk.pryst.builtins.PrystReadlnBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystStackTraceBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystTypeOfBuiltinFactory;
import org.jitcijk.pryst.builtins.PrystWrapPrimitiveBuiltinFactory;
import org.jitcijk.pryst.nodes.PrystExpressionNode;
import org.jitcijk.pryst.nodes.PrystRootNode;
import org.jitcijk.pryst.nodes.local.PrystReadArgumentNode;

/**
 * The run-time state of Pryst during execution. The context is created by the {@link PrystLanguage}. It
 * is used, for example, by {@link PrystBuiltinNode#getContext() builtin functions}.
 * <p>
 * It would be an error to have two different context instances during the execution of one script.
 * However, if two separate scripts run in one Java VM at the same time, they have a different
 * context. Therefore, the context is not a singleton.
 */
public final class PrystContext {

    private static final Source BUILTIN_SOURCE = Source.newBuilder(PrystLanguage.ID, "", "Pryst builtin").build();

    private final Env env;
    private final BufferedReader input;
    private final PrintWriter output;
    private final PrystFunctionRegistry functionRegistry;
    private final PrystLanguage language;
    private final AllocationReporter allocationReporter;
    private final Iterable<Scope> topScopes; // Cache the top scopes

    public PrystContext(PrystLanguage language, TruffleLanguage.Env env, List<NodeFactory<? extends PrystBuiltinNode>> externalBuiltins) {
        this.env = env;
        this.input = new BufferedReader(new InputStreamReader(env.in()));
        this.output = new PrintWriter(env.out(), true);
        this.language = language;
        this.allocationReporter = env.lookup(AllocationReporter.class);
        this.functionRegistry = new PrystFunctionRegistry(language);
        this.topScopes = Collections.singleton(Scope.newBuilder("global", functionRegistry.getFunctionsObject()).build());
        installBuiltins();
        for (NodeFactory<? extends PrystBuiltinNode> builtin : externalBuiltins) {
            installBuiltin(builtin);
        }
    }

    /**
     * Return the current Truffle environment.
     */
    public Env getEnv() {
        return env;
    }

    /**
     * Returns the default input, i.e., the source for the {@link PrystReadlnBuiltin}. To allow unit
     * testing, we do not use {@link System#in} directly.
     */
    public BufferedReader getInput() {
        return input;
    }

    /**
     * The default default, i.e., the output for the {@link PrystPrintlnBuiltin}. To allow unit
     * testing, we do not use {@link System#out} directly.
     */
    public PrintWriter getOutput() {
        return output;
    }

    /**
     * Returns the registry of all functions that are currently defined.
     */
    public PrystFunctionRegistry getFunctionRegistry() {
        return functionRegistry;
    }

    public Iterable<Scope> getTopScopes() {
        return topScopes;
    }

    /**
     * Adds all builtin functions to the {@link PrystFunctionRegistry}. This method lists all
     * {@link PrystBuiltinNode builtin implementation classes}.
     */
    private void installBuiltins() {
        installBuiltin(PrystReadlnBuiltinFactory.getInstance());
        installBuiltin(PrystPrintlnBuiltinFactory.getInstance());
        installBuiltin(PrystNanoTimeBuiltinFactory.getInstance());
        installBuiltin(PrystDefineFunctionBuiltinFactory.getInstance());
        installBuiltin(PrystStackTraceBuiltinFactory.getInstance());
        installBuiltin(PrystNewObjectBuiltinFactory.getInstance());
        installBuiltin(PrystEvalBuiltinFactory.getInstance());
        installBuiltin(PrystImportBuiltinFactory.getInstance());
        installBuiltin(PrystGetSizeBuiltinFactory.getInstance());
        installBuiltin(PrystHasSizeBuiltinFactory.getInstance());
        installBuiltin(PrystIsExecutableBuiltinFactory.getInstance());
        installBuiltin(PrystIsNullBuiltinFactory.getInstance());
        installBuiltin(PrystWrapPrimitiveBuiltinFactory.getInstance());
        installBuiltin(PrystTypeOfBuiltinFactory.getInstance());
        installBuiltin(PrystIsInstanceBuiltinFactory.getInstance());
    }

    public void installBuiltin(NodeFactory<? extends PrystBuiltinNode> factory) {
        /*
         * The builtin node factory is a class that is automatically generated by the Truffle DSL.
         * The signature returned by the factory reflects the signature of the @Specialization
         *
         * methods in the builtin classes.
         */
        int argumentCount = factory.getExecutionSignature().size();
        PrystExpressionNode[] argumentNodes = new PrystExpressionNode[argumentCount];
        /*
         * Builtin functions are like normal functions, i.e., the arguments are passed in as an
         * Object[] array encapsulated in PrystArguments. A PrystReadArgumentNode extracts a parameter
         * from this array.
         */
        for (int i = 0; i < argumentCount; i++) {
            argumentNodes[i] = new PrystReadArgumentNode(i);
        }
        /* Instantiate the builtin node. This node performs the actual functionality. */
        PrystBuiltinNode builtinBodyNode = factory.createNode((Object) argumentNodes);
        builtinBodyNode.addRootTag();
        /* The name of the builtin function is specified via an annotation on the node class. */
        String name = lookupNodeInfo(builtinBodyNode.getClass()).shortName();
        builtinBodyNode.setUnavailableSourceSection();

        /* Wrap the builtin in a RootNode. Truffle requires all AST to start with a RootNode. */
        PrystRootNode rootNode = new PrystRootNode(language, new FrameDescriptor(), builtinBodyNode, BUILTIN_SOURCE.createUnavailableSection(), name);

        /* Register the builtin function in our function registry. */
        getFunctionRegistry().register(name, Truffle.getRuntime().createCallTarget(rootNode));
    }

    public static NodeInfo lookupNodeInfo(Class<?> clazz) {
        if (clazz == null) {
            return null;
        }
        NodeInfo info = clazz.getAnnotation(NodeInfo.class);
        if (info != null) {
            return info;
        } else {
            return lookupNodeInfo(clazz.getSuperclass());
        }
    }

    /*
     * Methods for object creation / object property access.
     */
    public AllocationReporter getAllocationReporter() {
        return allocationReporter;
    }

    /*
     * Methods for language interoperability.
     */

    public static Object fromForeignValue(Object a) {
        if (a instanceof Long || a instanceof PrystBigNumber || a instanceof String || a instanceof Boolean) {
            return a;
        } else if (a instanceof Character) {
            return fromForeignCharacter((Character) a);
        } else if (a instanceof Number) {
            return fromForeignNumber(a);
        } else if (a instanceof TruffleObject) {
            return a;
        } else if (a instanceof PrystContext) {
            return a;
        }
        throw shouldNotReachHere("Value is not a truffle value.");
    }

    @TruffleBoundary
    private static long fromForeignNumber(Object a) {
        return ((Number) a).longValue();
    }

    @TruffleBoundary
    private static String fromForeignCharacter(char c) {
        return String.valueOf(c);
    }

    public CallTarget parse(Source source) {
        return env.parsePublic(source);
    }

    /**
     * Returns an object that contains bindings that were exported across all used languages. To
     * read or write from this object the {@link TruffleObject interop} API can be used.
     */
    public TruffleObject getPolyglotBindings() {
        return (TruffleObject) env.getPolyglotBindings();
    }

    public static PrystContext getCurrent() {
        return PrystLanguage.getCurrentContext();
    }

}
