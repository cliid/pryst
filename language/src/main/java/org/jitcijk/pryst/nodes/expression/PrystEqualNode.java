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

import static com.oracle.truffle.api.CompilerDirectives.shouldNotReachHere;

import com.oracle.truffle.api.CompilerDirectives.TruffleBoundary;
import com.oracle.truffle.api.dsl.Specialization;
import com.oracle.truffle.api.interop.InteropLibrary;
import com.oracle.truffle.api.interop.UnsupportedMessageException;
import com.oracle.truffle.api.library.CachedLibrary;
import com.oracle.truffle.api.nodes.NodeInfo;
import org.jitcijk.pryst.nodes.PrystBinaryNode;
import org.jitcijk.pryst.runtime.PrystBigNumber;
import org.jitcijk.pryst.runtime.PrystFunction;
import org.jitcijk.pryst.runtime.PrystNull;

/**
 * The {@code ==} operator of SL is defined on all types. Therefore, we need a
 * {@link #equal(Object, Object) implementation} that can handle all possible types including
 * interop types.
 * <p>
 * Note that we do not need the analogous {@code !=} operator, because we can just
 * {@link PrystLogicalNotNode negate} the {@code ==} operator.
 */
@NodeInfo(shortName = "==")
public abstract class PrystEqualNode extends PrystBinaryNode {

    @Specialization
    protected boolean doLong(long left, long right) {
        return left == right;
    }

    @Specialization
    @TruffleBoundary
    protected boolean doBigNumber(PrystBigNumber left, PrystBigNumber right) {
        return left.equals(right);
    }

    @Specialization
    protected boolean doBoolean(boolean left, boolean right) {
        return left == right;
    }

    @Specialization
    protected boolean doString(String left, String right) {
        return left.equals(right);
    }

    @Specialization
    protected boolean doNull(PrystNull left, PrystNull right) {
        /* There is only the singleton instance of SLNull, so we do not need equals(). */
        return left == right;
    }

    @Specialization
    protected boolean doFunction(PrystFunction left, Object right) {
        /*
         * Our function registry maintains one canonical SLFunction object per function name, so we
         * do not need equals().
         */
        return left == right;
    }

    /*
     * This is a generic specialization of equality operation. Since it is generic this
     * specialization covers the entire semantics. One can see this by having no method guards set
     * and the types for the left and right value are Object. The previous specializations are only
     * here for interpreter performance and footprint reasons. They could be removed and this
     * operation be semantically equivalent.
     *
     * We cache four combinations of interop values until we fallback to the uncached version of
     * this specialization. This limit is set arbitrary and for a real language should be set to the
     * minimal possible value, for a set of given benchmarks.
     *
     * This specialization is generic and handles all the cases, but in this case we decided to not
     * replace the previous specializations, as they are still more efficient in the interpeter.
     */
    @Specialization(limit = "4")
    public boolean doGeneric(Object left, Object right,
                    @CachedLibrary("left") InteropLibrary leftInterop,
                    @CachedLibrary("right") InteropLibrary rightInterop) {
        /*
         * This method looks very inefficient. In practice most of these branches fold as the
         * interop type checks typically return a constant when using a cached library.
         *
         * Exercise: Try looking at what happens to this method during partial evaluation in IGV.
         * Tip: comment out all the previous @Specialization annotations to make it easier to
         * activate this specialization.
         */
        try {
            if (leftInterop.isBoolean(left) && rightInterop.isBoolean(right)) {
                return doBoolean(leftInterop.asBoolean(left), rightInterop.asBoolean(right));
            } else if (leftInterop.isString(left) && rightInterop.isString(right)) {
                return doString(leftInterop.asString(left), (rightInterop.asString(right)));
            } else if (leftInterop.isNull(left) && rightInterop.isNull(right)) {
                return true;
            } else if (leftInterop.fitsInLong(left) && rightInterop.fitsInLong(right)) {
                return doLong(leftInterop.asLong(left), (rightInterop.asLong(right)));
            } else if (left instanceof PrystBigNumber && right instanceof PrystBigNumber) {
                return doBigNumber((PrystBigNumber) left, (PrystBigNumber) right);
            } else if (leftInterop.hasIdentity(left) && rightInterop.hasIdentity(right)) {
                return leftInterop.isIdentical(left, right, rightInterop);
            } else {
                /*
                 * We return false in good dynamic language manner. Stricter languages might throw
                 * an error here.
                 */
                return false;
            }
        } catch (UnsupportedMessageException e) {
            // this case must not happen as we always check interop types before converting
            throw shouldNotReachHere(e);
        }
    }

}
