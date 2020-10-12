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

import com.oracle.truffle.api.frame.VirtualFrame;
import com.oracle.truffle.api.nodes.UnexpectedResultException;
import com.oracle.truffle.api.profiles.ConditionProfile;
import org.jitcijk.pryst.PrystException;
import org.jitcijk.pryst.nodes.PrystExpressionNode;

/**
 * Logical operations in Pryst use short circuit evaluation: if the evaluation of the left operand
 * already decides the result of the operation, the right operand must not be executed. This is
 * expressed in using this base class for {@link PrystLogicalAndNode} and {@link PrystLogicalOrNode}.
 */
public abstract class PrystShortCircuitNode extends PrystExpressionNode {

    @Child private PrystExpressionNode left;
    @Child private PrystExpressionNode right;

    /**
     * Short circuits might be used just like a conditional statement it makes sense to profile the
     * branch probability.
     */
    private final ConditionProfile evaluateRightProfile = ConditionProfile.createCountingProfile();

    public PrystShortCircuitNode(PrystExpressionNode left, PrystExpressionNode right) {
        this.left = left;
        this.right = right;
    }

    @Override
    public final Object executeGeneric(VirtualFrame frame) {
        return executeBoolean(frame);
    }

    @Override
    public final boolean executeBoolean(VirtualFrame frame) {
        boolean leftValue;
        try {
            leftValue = left.executeBoolean(frame);
        } catch (UnexpectedResultException e) {
            throw PrystException.typeError(this, e.getResult(), null);
        }
        boolean rightValue;
        try {
            if (evaluateRightProfile.profile(isEvaluateRight(leftValue))) {
                rightValue = right.executeBoolean(frame);
            } else {
                rightValue = false;
            }
        } catch (UnexpectedResultException e) {
            throw PrystException.typeError(this, leftValue, e.getResult());
        }
        return execute(leftValue, rightValue);
    }

    /**
     * This method is called after the left child was evaluated, but before the right child is
     * evaluated. The right child is only evaluated when the return value is {code true}.
     */
    protected abstract boolean isEvaluateRight(boolean leftValue);

    /**
     * Calculates the result of the short circuit operation. If the right node is not evaluated then
     * <code>false</code> is provided.
     */
    protected abstract boolean execute(boolean leftValue, boolean rightValue);

}
