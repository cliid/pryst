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

import com.oracle.truffle.api.CompilerAsserts;
import com.oracle.truffle.api.CompilerDirectives.CompilationFinal;
import com.oracle.truffle.api.CompilerDirectives.TruffleBoundary;
import com.oracle.truffle.api.TruffleLanguage;
import com.oracle.truffle.api.dsl.Cached;
import com.oracle.truffle.api.dsl.Specialization;
import com.oracle.truffle.api.interop.InteropLibrary;
import com.oracle.truffle.api.interop.TruffleObject;
import com.oracle.truffle.api.library.CachedLibrary;
import com.oracle.truffle.api.library.ExportLibrary;
import com.oracle.truffle.api.library.ExportMessage;
import org.jitcijk.pryst.PrystLanguage;

/**
 * The builtin type definitions for Pryst. Pryst has no custom types, so it is not possible
 * for a guest program to create new instances of PrystType.
 * <p>
 * The isInstance type checks are declared using an functional interface and are expressed using the
 * interoperability libraries. The advantage of this is type checks automatically work for foreign
 * values or primitive values like byte or short.
 * <p>
 * The class implements the interop contracts for {@link InteropLibrary#isMetaObject(Object)} and
 * {@link InteropLibrary#isMetaInstance(Object, Object)}. The latter allows other languages and
 * tools to perform type checks using types of simple language.
 * <p>
 * In order to assign types to guest language values, Pryst values implement
 * {@link InteropLibrary#getMetaObject(Object)}. The interop contracts for primitive values cannot
 * be overriden, so in order to assign meta-objects to primitive values, the primitive values are
 * assigned using language views. See {@link PrystLanguage#getLanguageView}.
 */
@ExportLibrary(InteropLibrary.class)
@SuppressWarnings("static-method")
public final class PrystType implements TruffleObject {

    /*
     * These are the sets of builtin types in simple languages. In case of simple language the types
     * nicely match those of the types in InteropLibrary. This might not be the case and more
     * additional checks need to be performed (similar to number checking for PrystBigNumber).
     */
    public static final PrystType NUMBER = new PrystType("Number", (l, v) -> l.fitsInLong(v) || v instanceof PrystBigNumber);
    public static final PrystType NULL = new PrystType("NULL", (l, v) -> l.isNull(v));
    public static final PrystType STRING = new PrystType("String", (l, v) -> l.isString(v));
    public static final PrystType BOOLEAN = new PrystType("Boolean", (l, v) -> l.isBoolean(v));
    public static final PrystType OBJECT = new PrystType("Object", (l, v) -> l.hasMembers(v));
    public static final PrystType FUNCTION = new PrystType("Function", (l, v) -> l.isExecutable(v));

    /*
     * This array is used when all types need to be checked in a certain order. While most interop
     * types like number or string are exclusive, others traits like members might not be. For
     * example, an object might be a function. In Pryst we decided to make functions,
     * functions and not objects.
     */
    @CompilationFinal(dimensions = 1) public static final PrystType[] PRECEDENCE = new PrystType[]{NULL, NUMBER, STRING, BOOLEAN, FUNCTION, OBJECT};

    private final String name;
    private final TypeCheck isInstance;

    /*
     * We don't allow dynamic instances of PrystType. Real languages might want to expose this for
     * types that are user defined.
     */
    private PrystType(String name, TypeCheck isInstance) {
        this.name = name;
        this.isInstance = isInstance;
    }

    /**
     * Checks whether this type is of a certain instance. If used on fast-paths it is required to
     * cast {@link PrystType} to a constant.
     */
    public boolean isInstance(Object value, InteropLibrary interop) {
        CompilerAsserts.partialEvaluationConstant(this);
        return isInstance.check(interop, value);
    }

    @ExportMessage
    boolean hasLanguage() {
        return true;
    }

    @ExportMessage
    Class<? extends TruffleLanguage<?>> getLanguage() {
        return PrystLanguage.class;
    }

    /*
     * All PrystTypes are declared as interop meta-objects. Other example for meta-objects are Java
     * classes, or JavaScript prototypes.
     */
    @ExportMessage
    boolean isMetaObject() {
        return true;
    }

    /*
     * Pryst does not have the notion of a qualified or simple name, so we return the same type name
     * for both.
     */
    @ExportMessage(name = "getMetaQualifiedName")
    @ExportMessage(name = "getMetaSimpleName")
    public Object getName() {
        return name;
    }

    @ExportMessage(name = "toDisplayString")
    Object toDisplayString(@SuppressWarnings("unused") boolean allowSideEffects) {
        return name;
    }

    @Override
    public String toString() {
        return "PrystType[" + name + "]";
    }

    /*
     * The interop message isMetaInstance might be used from other languages or by the {@link
     * PrystIsInstanceBuiltin isInstance} builtin. It checks whether a given value, which might be a
     * primitive, foreign or Pryst value is of a given Pryst type. This allows other languages to make
     * their instanceOf interopable with foreign values.
     */
    @ExportMessage
    static class IsMetaInstance {

        /*
         * We assume that the same type is checked at a source location. Therefore we use an inline
         * cache to specialize for observed types to be constant. The limit of "3" specifies that we
         * specialize for 3 different types until we rewrite to the doGeneric case. The limit in
         * this example is somewhat arbitrary and should be determined using careful tuning with
         * real world benchmarks.
         */
        @Specialization(guards = "type == cachedType", limit = "3")
        static boolean doCached(@SuppressWarnings("unused") PrystType type, Object value,
                                @Cached("type") PrystType cachedType,
                                @CachedLibrary("value") InteropLibrary valueLib) {
            return cachedType.isInstance.check(valueLib, value);
        }

        @TruffleBoundary
        @Specialization(replaces = "doCached")
        static boolean doGeneric(PrystType type, Object value) {
            return type.isInstance.check(InteropLibrary.getFactory().getUncached(), value);
        }
    }

    /*
     * A convenience interface for type checks. Alternatively this could have been solved using
     * subtypes of PrystType.
     */
    @FunctionalInterface
    interface TypeCheck {

        boolean check(InteropLibrary lib, Object value);

    }

}
