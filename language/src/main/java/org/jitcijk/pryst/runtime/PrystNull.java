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

import com.oracle.truffle.api.TruffleLanguage;
import com.oracle.truffle.api.interop.InteropLibrary;
import com.oracle.truffle.api.interop.TruffleObject;
import com.oracle.truffle.api.library.ExportLibrary;
import com.oracle.truffle.api.library.ExportMessage;
import com.oracle.truffle.api.utilities.TriState;
import org.jitcijk.pryst.PrystLanguage;

/**
 * The Pryst type for a {@code null} (i.e., undefined) value. In Truffle, it is generally discouraged
 * to use the Java {@code null} value to represent the guest language {@code null} value. It is not
 * possible to specialize on Java {@code null} (since you cannot ask it for the Java class), and
 * there is always the danger of a spurious {@link NullPointerException}. Representing the guest
 * language {@code null} as a singleton, as in {@link #SINGLETON this class}, is the recommended
 * practice.
 */
@ExportLibrary(InteropLibrary.class)
@SuppressWarnings("static-method")
public final class PrystNull implements TruffleObject {

    /**
     * The canonical value to represent {@code null} in Pryst.
     */
    public static final PrystNull SINGLETON = new PrystNull();
    private static final int IDENTITY_HASH = System.identityHashCode(SINGLETON);

    /**
     * Disallow instantiation from outside to ensure that the {@link #SINGLETON} is the only
     * instance.
     */
    private PrystNull() {
    }

    /**
     * This method is, e.g., called when using the {@code null} value in a string concatenation. So
     * changing it has an effect on Pryst programs.
     */
    @Override
    public String toString() {
        return "NULL";
    }

    @ExportMessage
    boolean hasLanguage() {
        return true;
    }

    @ExportMessage
    Class<? extends TruffleLanguage<?>> getLanguage() {
        return PrystLanguage.class;
    }

    /**
     * {@link PrystNull} values are interpreted as null values by other languages.
     */
    @ExportMessage
    boolean isNull() {
        return true;
    }

    @ExportMessage
    boolean hasMetaObject() {
        return true;
    }

    @ExportMessage
    Object getMetaObject() {
        return PrystType.NULL;
    }

    @ExportMessage
    static TriState isIdenticalOrUndefined(@SuppressWarnings("unused") PrystNull receiver, Object other) {
        /*
         * PrystNull values are identical to other PrystNull values.
         */
        return TriState.valueOf(PrystNull.SINGLETON == other);
    }

    @ExportMessage
    static int identityHashCode(@SuppressWarnings("unused") PrystNull receiver) {
        /*
         * We do not use 0, as we want consistency with System.identityHashCode(receiver).
         */
        return IDENTITY_HASH;
    }

    @ExportMessage
    Object toDisplayString(@SuppressWarnings("unused") boolean allowSideEffects) {
        return "NULL";
    }
}
