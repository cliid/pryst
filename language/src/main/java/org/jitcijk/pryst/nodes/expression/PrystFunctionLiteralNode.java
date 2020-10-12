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
package org.jitcijk.pryst.nodes.expression;

import com.oracle.truffle.api.CallTarget;
import com.oracle.truffle.api.CompilerDirectives;
import com.oracle.truffle.api.CompilerDirectives.CompilationFinal;
import com.oracle.truffle.api.frame.VirtualFrame;
import com.oracle.truffle.api.nodes.NodeInfo;
import org.jitcijk.pryst.PrystLanguage;
import org.jitcijk.pryst.nodes.PrystExpressionNode;
import org.jitcijk.pryst.runtime.PrystContext;
import org.jitcijk.pryst.runtime.PrystFunction;
import org.jitcijk.pryst.runtime.PrystFunctionRegistry;

/**
 * Constant literal for a {@link PrystFunction function} value, created when a function name occurs as
 * a literal in Pryst source code. Note that function redefinition can change the {@link CallTarget
 * call target} that is executed when calling the function, but the {@link PrystFunction} for a name
 * never changes. This is guaranteed by the {@link PrystFunctionRegistry}.
 */
@NodeInfo(shortName = "func")
public final class PrystFunctionLiteralNode extends PrystExpressionNode {

    /** The name of the function. */
    private final String functionName;

    /**
     * The resolved function. During parsing (in the constructor of this node), we do not have the
     * {@link PrystContext} available yet, so the lookup can only be done at {@link #executeGeneric
     * first execution}. The {@link CompilationFinal} annotation ensures that the function can still
     * be constant folded during compilation.
     */
    @CompilationFinal private PrystFunction cachedFunction;

    public PrystFunctionLiteralNode(String functionName) {
        this.functionName = functionName;
    }

    @Override
    public PrystFunction executeGeneric(VirtualFrame frame) {
        if (cachedFunction == null) {
            /* We are about to change a @CompilationFinal field. */
            CompilerDirectives.transferToInterpreterAndInvalidate();
            /* First execution of the node: lookup the function in the function registry. */
            cachedFunction = lookupContextReference(PrystLanguage.class).get().getFunctionRegistry().lookup(functionName, true);
        }
        return cachedFunction;
    }

}
