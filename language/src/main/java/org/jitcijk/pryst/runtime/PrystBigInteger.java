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

import java.math.BigInteger;

import com.oracle.truffle.api.CompilerDirectives.TruffleBoundary;
import com.oracle.truffle.api.TruffleLanguage;
import com.oracle.truffle.api.interop.InteropLibrary;
import com.oracle.truffle.api.interop.TruffleObject;
import com.oracle.truffle.api.interop.UnsupportedMessageException;
import com.oracle.truffle.api.library.ExportLibrary;
import com.oracle.truffle.api.library.ExportMessage;
import org.jitcijk.pryst.PrystLanguage;

@ExportLibrary(InteropLibrary.class)
@SuppressWarnings("static-method")
public final class PrystBigInteger implements TruffleObject, Comparable<PrystBigInteger> {

    private static final long LONG_MAX_SAFE_DOUBLE = 9007199254740991L; // 2 ** 53 - 1
    private static final int INT_MAX_SAFE_FLOAT = 16777215; // 2 ** 24 - 1

    private static boolean inSafeDoubleRange(long l) {
        return l >= -LONG_MAX_SAFE_DOUBLE && l <= LONG_MAX_SAFE_DOUBLE;
    }

    private static boolean inSafeFloatRange(int i) {
        return i >= -INT_MAX_SAFE_FLOAT && i <= INT_MAX_SAFE_FLOAT;
    }

    private final BigInteger value;

    public PrystBigInteger(BigInteger value) {
        this.value = value;
    }

    public PrystBigInteger(long value) {
        this.value = BigInteger.valueOf(value);
    }

    public BigInteger getValue() {
        return value;
    }

    @TruffleBoundary
    public int compareTo(PrystBigInteger o) {
        return value.compareTo(o.getValue());
    }

    @Override
    @TruffleBoundary
    public String toString() {
        return value.toString();
    }

    @Override
    @TruffleBoundary
    public boolean equals(Object obj) {
        if (obj instanceof PrystBigInteger) {
            return value.equals(((PrystBigInteger) obj).getValue());
        }
        return false;
    }

    @Override
    public int hashCode() {
        return value.hashCode();
    }

    @SuppressWarnings("static-method")
    @ExportMessage
    boolean isNumber() {
        return fitsInLong();
    }

    @ExportMessage
    @TruffleBoundary
    boolean fitsInByte() {
        return value.bitLength() < 8;
    }

    @ExportMessage
    @TruffleBoundary
    boolean fitsInShort() {
        return value.bitLength() < 16;
    }

    @ExportMessage
    @TruffleBoundary
    boolean fitsInFloat() {
        return fitsInInt() && inSafeFloatRange(value.intValue());
    }

    @ExportMessage
    @TruffleBoundary
    boolean fitsInLong() {
        return value.bitLength() < 64;
    }

    @ExportMessage
    @TruffleBoundary
    boolean fitsInInt() {
        return value.bitLength() < 32;
    }

    @ExportMessage
    @TruffleBoundary
    boolean fitsInDouble() {
        return fitsInLong() && inSafeDoubleRange(value.longValue());
    }

    @ExportMessage
    @TruffleBoundary
    double asDouble() throws UnsupportedMessageException {
        if (fitsInDouble()) {
            return value.doubleValue();
        } else {
            throw UnsupportedMessageException.create();
        }
    }

    @ExportMessage
    @TruffleBoundary
    long asLong() throws UnsupportedMessageException {
        if (fitsInLong()) {
            return value.longValue();
        } else {
            throw UnsupportedMessageException.create();
        }
    }

    @ExportMessage
    @TruffleBoundary
    byte asByte() throws UnsupportedMessageException {
        if (fitsInByte()) {
            return value.byteValue();
        } else {
            throw UnsupportedMessageException.create();
        }
    }

    @ExportMessage
    @TruffleBoundary
    int asInt() throws UnsupportedMessageException {
        if (fitsInInt()) {
            return value.intValue();
        } else {
            throw UnsupportedMessageException.create();
        }
    }

    @ExportMessage
    @TruffleBoundary
    float asFloat() throws UnsupportedMessageException {
        if (fitsInFloat()) {
            return value.floatValue();
        } else {
            throw UnsupportedMessageException.create();
        }
    }

    @ExportMessage
    @TruffleBoundary
    short asShort() throws UnsupportedMessageException {
        if (fitsInShort()) {
            return value.shortValue();
        } else {
            throw UnsupportedMessageException.create();
        }
    }

    @ExportMessage
    boolean hasLanguage() {
        return true;
    }

    @ExportMessage
    Class<? extends TruffleLanguage<?>> getLanguage() {
        return PrystLanguage.class;
    }

    @ExportMessage
    boolean hasMetaObject() {
        return true;
    }

    @ExportMessage
    Object getMetaObject() {
        return PrystType.INTEGER;
    }

    @ExportMessage
    @TruffleBoundary
    Object toDisplayString(@SuppressWarnings("unused") boolean allowSideEffects) {
        return value.toString();
    }

}
