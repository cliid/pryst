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

import com.oracle.truffle.api.dsl.Specialization;
import com.oracle.truffle.api.interop.InteropLibrary;
import com.oracle.truffle.api.library.CachedLibrary;
import com.oracle.truffle.api.nodes.ExplodeLoop;
import com.oracle.truffle.api.nodes.NodeInfo;
import org.jitcijk.pryst.runtime.PrystNull;
import org.jitcijk.pryst.runtime.PrystType;

/**
 * Built-in function that returns the type of a guest language value.
 */
@NodeInfo(shortName = "typeOf")
@SuppressWarnings("unused")
public abstract class PrystTypeOfBuiltin extends PrystBuiltinNode {

    /*
     * This returns the Pryst type for a particular operand value.
     */
    @Specialization(limit = "3")
    @ExplodeLoop
    public Object doDefault(Object operand,
                    @CachedLibrary("operand") InteropLibrary interop) {
        for (PrystType type : PrystType.PRECEDENCE) {
            if (type.isInstance(operand, interop)) {
                return type;
            }
        }
        return PrystNull.SINGLETON;
    }

}
