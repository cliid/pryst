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
package org.jitcijk.pryst.builtins;

import com.oracle.truffle.api.dsl.GenerateNodeFactory;
import com.oracle.truffle.api.dsl.NodeChild;
import com.oracle.truffle.api.dsl.UnsupportedSpecializationException;
import com.oracle.truffle.api.frame.VirtualFrame;
import com.oracle.truffle.api.nodes.UnexpectedResultException;
import org.jitcijk.pryst.PrystException;
import org.jitcijk.pryst.nodes.PrystExpressionNode;
import org.jitcijk.pryst.runtime.PrystContext;
import org.jitcijk.pryst.runtime.PrystFunctionRegistry;

/**
 * Base class for all builtin functions. It contains the Truffle DSL annotation {@link NodeChild}
 * that defines the function arguments.<br>
 * The builtin functions are registered in {@link PrystContext#installBuiltins}. Every builtin node
 * subclass is instantiated there, wrapped into a function, and added to the
 * {@link PrystFunctionRegistry}. This ensures that builtin functions can be called like user-defined
 * functions; there is no special function lookup or call node for builtin functions.
 */
@NodeChild(value = "arguments", type = PrystExpressionNode[].class)
@GenerateNodeFactory
public abstract class PrystBuiltinNode extends PrystExpressionNode {

    @Override
    public final Object executeGeneric(VirtualFrame frame) {
        try {
            return execute(frame);
        } catch (UnsupportedSpecializationException e) {
            throw PrystException.typeError(e.getNode(), e.getSuppliedValues());
        }
    }

    @Override
    public final boolean executeBoolean(VirtualFrame frame) throws UnexpectedResultException {
        return super.executeBoolean(frame);
    }

    @Override
    public final long executeLong(VirtualFrame frame) throws UnexpectedResultException {
        return super.executeLong(frame);
    }

    @Override
    public final double executeDouble(VirtualFrame frame) throws UnexpectedResultException {
        return super.executeDouble(frame);
    }

    @Override
    public final void executeVoid(VirtualFrame frame) {
        super.executeVoid(frame);
    }

    protected abstract Object execute(VirtualFrame frame);
}
