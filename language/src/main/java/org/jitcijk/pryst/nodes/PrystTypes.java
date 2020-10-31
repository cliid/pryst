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
package org.jitcijk.pryst.nodes;

import java.math.BigInteger;

import com.oracle.truffle.api.CompilerDirectives.TruffleBoundary;
import com.oracle.truffle.api.dsl.ImplicitCast;
import com.oracle.truffle.api.dsl.TypeCast;
import com.oracle.truffle.api.dsl.TypeCheck;
import com.oracle.truffle.api.dsl.TypeSystem;
import org.jitcijk.pryst.PrystLanguage;
import org.jitcijk.pryst.runtime.PrystBigInteger;
import org.jitcijk.pryst.runtime.PrystNull;

/**
 * The type system of Pryst, as explained in {@link PrystLanguage}. Based on the {@link TypeSystem}
 * annotation, the Truffle DSL generates the subclass {@link SLTypesGen} with type test and type
 * conversion methods for some types. In this class, we only cover types where the automatically
 * generated ones would not be sufficient.
 */
@TypeSystem({long.class, double.class, boolean.class})
public abstract class PrystTypes {

    /**
     * Example of a manually specified type check that replaces the automatically generated type
     * check that the Truffle DSL would generate. For {@link PrystNull}, we do not need an
     * {@code instanceof} check, because we know that there is only a {@link PrystNull#SINGLETON
     * singleton} instance.
     */
    @TypeCheck(PrystNull.class)
    public static boolean isPrystNull(Object value) {
        return value == PrystNull.SINGLETON;
    }

    /**
     * Example of a manually specified type cast that replaces the automatically generated type cast
     * that the Truffle DSL would generate. For {@link PrystNull}, we do not need an actual cast,
     * because we know that there is only a {@link PrystNull#SINGLETON singleton} instance.
     */
    @TypeCast(PrystNull.class)
    public static PrystNull asPrystNull(Object value) {
        assert isPrystNull(value);
        return PrystNull.SINGLETON;
    }

    /**
     * Informs the Truffle DSL that a primitive {@code long} value can be used in all
     * specializations where a {@link PrystBigInteger} is expected. This models the semantic of Pryst: It
     * only has an arbitrary precision Number type (implemented as {@link PrystBigInteger}, and
     * {@code long} is only used as a performance optimization to avoid the costly
     * {@link PrystBigInteger} arithmetic for values that fit into a 64-bit primitive value.
     */
    @ImplicitCast
    @TruffleBoundary
    public static PrystBigInteger castBigInteger(long value) {
        return new PrystBigInteger(BigInteger.valueOf(value));
    }
}
