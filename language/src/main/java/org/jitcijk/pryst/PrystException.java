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

import static com.oracle.truffle.api.CompilerDirectives.shouldNotReachHere;

import com.oracle.truffle.api.CompilerDirectives.TruffleBoundary;
import com.oracle.truffle.api.TruffleException;
import com.oracle.truffle.api.interop.InteropLibrary;
import com.oracle.truffle.api.interop.UnsupportedMessageException;
import com.oracle.truffle.api.nodes.Node;
import com.oracle.truffle.api.nodes.NodeInfo;
import com.oracle.truffle.api.source.SourceSection;
import org.jitcijk.pryst.runtime.PrystContext;
import org.jitcijk.pryst.runtime.PrystLanguageView;

/**
 * Pryst does not need a sophisticated error checking and reporting mechanism, so all unexpected
 * conditions just abort execution. This exception class is used when we abort from within the Pryst
 * implementation.
 */
public class PrystException extends RuntimeException implements TruffleException {

    private static final long serialVersionUID = -6799734410727348507L;
    private static final InteropLibrary UNCACHED_LIB = InteropLibrary.getFactory().getUncached();

    private final Node location;

    @TruffleBoundary
    public PrystException(String message, Node location) {
        super(message);
        this.location = location;
    }

    @SuppressWarnings("sync-override")
    @Override
    public final Throwable fillInStackTrace() {
        return this;
    }

    public Node getLocation() {
        return location;
    }

    /**
     * Provides a user-readable message for run-time type errors. Pryst is strongly typed, i.e., there
     * are no automatic type conversions of values.
     */
    @TruffleBoundary
    public static PrystException typeError(Node operation, Object... values) {
        StringBuilder result = new StringBuilder();
        result.append("Type error");

        if (operation != null) {
            SourceSection ss = operation.getEncapsulatingSourceSection();
            if (ss != null && ss.isAvailable()) {
                result.append(" at ").append(ss.getSource().getName()).append(" line ").append(ss.getStartLine()).append(" col ").append(ss.getStartColumn());
            }
        }

        result.append(": operation");
        if (operation != null) {
            NodeInfo nodeInfo = PrystContext.lookupNodeInfo(operation.getClass());
            if (nodeInfo != null) {
                result.append(" \"").append(nodeInfo.shortName()).append("\"");
            }
        }

        result.append(" not defined for");

        String sep = " ";
        for (int i = 0; i < values.length; i++) {
            /*
             * For primitive or foreign values we request a language view so the values are printed
             * from the perspective of simple language and not another language. Since this is a
             * rather rarely invoked exceptional method, we can just create the language view for
             * primitive values and then conveniently request the meta-object and display strings.
             * Using the language view for core builtins like the typeOf builtin might not be a good
             * idea for performance reasons.
             */
            Object value = PrystLanguageView.forValue(values[i]);
            result.append(sep);
            sep = ", ";
            if (value == null) {
                result.append("ANY");
            } else {
                InteropLibrary valueLib = InteropLibrary.getFactory().getUncached(value);
                if (valueLib.hasMetaObject(value) && !valueLib.isNull(value)) {
                    String qualifiedName;
                    try {
                        qualifiedName = UNCACHED_LIB.asString(UNCACHED_LIB.getMetaQualifiedName(valueLib.getMetaObject(value)));
                    } catch (UnsupportedMessageException e) {
                        throw shouldNotReachHere(e);
                    }
                    result.append(qualifiedName);
                    result.append(" ");
                }
                if (valueLib.isString(value)) {
                    result.append("\"");
                }
                result.append(valueLib.toDisplayString(value));
                if (valueLib.isString(value)) {
                    result.append("\"");
                }
            }
        }
        return new PrystException(result.toString(), operation);
    }

}
