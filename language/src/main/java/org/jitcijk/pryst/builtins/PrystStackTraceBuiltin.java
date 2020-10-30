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

import com.oracle.truffle.api.CallTarget;
import com.oracle.truffle.api.CompilerDirectives.TruffleBoundary;
import com.oracle.truffle.api.RootCallTarget;
import com.oracle.truffle.api.Truffle;
import com.oracle.truffle.api.dsl.Specialization;
import com.oracle.truffle.api.frame.Frame;
import com.oracle.truffle.api.frame.FrameDescriptor;
import com.oracle.truffle.api.frame.FrameInstance;
import com.oracle.truffle.api.frame.FrameInstance.FrameAccess;
import com.oracle.truffle.api.frame.FrameInstanceVisitor;
import com.oracle.truffle.api.frame.FrameSlot;
import com.oracle.truffle.api.nodes.NodeInfo;
import com.oracle.truffle.api.nodes.RootNode;

/**
 * Returns a string representation of the current stack. This includes the {@link CallTarget}s and
 * the contents of the {@link Frame}.
 */
@NodeInfo(shortName = "stacktrace")
public abstract class PrystStackTraceBuiltin extends PrystBuiltinNode {

    @Specialization
    public String trace() {
        return createStackTrace();
    }

    @TruffleBoundary
    private static String createStackTrace() {
        final StringBuilder str = new StringBuilder();

        Truffle.getRuntime().iterateFrames(new FrameInstanceVisitor<Integer>() {
            private int skip = 1; // skip stack trace builtin

            @Override
            public Integer visitFrame(FrameInstance frameInstance) {
                if (skip > 0) {
                    skip--;
                    return null;
                }
                CallTarget callTarget = frameInstance.getCallTarget();
                Frame frame = frameInstance.getFrame(FrameAccess.READ_ONLY);
                RootNode rn = ((RootCallTarget) callTarget).getRootNode();
                // ignore internal or interop stack frames
                if (rn.isInternal() || rn.getLanguageInfo() == null) {
                    return 1;
                }
                if (str.length() > 0) {
                    str.append(System.getProperty("line.separator"));
                }
                str.append("Frame: ").append(rn.toString());
                FrameDescriptor frameDescriptor = frame.getFrameDescriptor();
                for (FrameSlot s : frameDescriptor.getSlots()) {
                    str.append(", ").append(s.getIdentifier()).append("=").append(frame.getValue(s));
                }
                return null;
            }
        });
        return str.toString();
    }
}
