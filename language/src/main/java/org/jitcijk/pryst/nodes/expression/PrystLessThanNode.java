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

import com.oracle.truffle.api.CompilerDirectives.TruffleBoundary;
import com.oracle.truffle.api.dsl.Fallback;
import com.oracle.truffle.api.dsl.Specialization;
import com.oracle.truffle.api.nodes.NodeInfo;
import org.jitcijk.pryst.PrystException;
import org.jitcijk.pryst.nodes.PrystBinaryNode;
import org.jitcijk.pryst.runtime.PrystBigNumber;

/**
 * This class is similar to the extensively documented {@link PrystAddNode}. The only difference: the
 * specialized methods return {@code boolean} instead of the input types.
 */
@NodeInfo(shortName = "<")
public abstract class PrystLessThanNode extends PrystBinaryNode {

    @Specialization
    protected boolean lessThan(long left, long right) {
        return left < right;
    }

    @Specialization
    @TruffleBoundary
    protected boolean lessThan(PrystBigNumber left, PrystBigNumber right) {
        return left.compareTo(right) < 0;
    }

    @Fallback
    protected Object typeError(Object left, Object right) {
        throw PrystException.typeError(this, left, right);
    }

}
