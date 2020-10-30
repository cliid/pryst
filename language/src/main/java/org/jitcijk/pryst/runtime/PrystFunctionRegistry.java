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

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;

import com.oracle.truffle.api.RootCallTarget;
import com.oracle.truffle.api.interop.TruffleObject;
import com.oracle.truffle.api.source.Source;
import org.jitcijk.pryst.PrystLanguage;
import org.jitcijk.pryst.parser.PrystParser;

/**
 * Manages the mapping from function names to {@link PrystFunction function objects}.
 */
public final class PrystFunctionRegistry {

    private final PrystLanguage language;
    private final FunctionsObject functionsObject = new FunctionsObject();

    public PrystFunctionRegistry(PrystLanguage language) {
        this.language = language;
    }

    /**
     * Returns the canonical {@link PrystFunction} object for the given name. If it does not exist yet,
     * it is created.
     */
    public PrystFunction lookup(String name, boolean createIfNotPresent) {
        PrystFunction result = functionsObject.functions.get(name);
        if (result == null && createIfNotPresent) {
            result = new PrystFunction(language, name);
            functionsObject.functions.put(name, result);
        }
        return result;
    }

    /**
     * Associates the {@link PrystFunction} with the given name with the given implementation root
     * node. If the function did not exist before, it defines the function. If the function existed
     * before, it redefines the function and the old implementation is discarded.
     */
    public PrystFunction register(String name, RootCallTarget callTarget) {
        PrystFunction function = lookup(name, true);
        function.setCallTarget(callTarget);
        return function;
    }

    public void register(Map<String, RootCallTarget> newFunctions) {
        for (Map.Entry<String, RootCallTarget> entry : newFunctions.entrySet()) {
            register(entry.getKey(), entry.getValue());
        }
    }

    public void register(Source newFunctions) {
        register(PrystParser.parsePryst(language, newFunctions));
    }

    public PrystFunction getFunction(String name) {
        return functionsObject.functions.get(name);
    }

    /**
     * Returns the sorted list of all functions, for printing purposes only.
     */
    public List<PrystFunction> getFunctions() {
        List<PrystFunction> result = new ArrayList<>(functionsObject.functions.values());
        result.sort(Comparator.comparing(PrystFunction::toString));
        return result;
    }

    public TruffleObject getFunctionsObject() {
        return functionsObject;
    }

}
