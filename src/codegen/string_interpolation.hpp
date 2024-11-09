#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "../utils/logger.hpp"
#include "type_registry.hpp"

namespace pryst {

struct FormatSpecifier {
    int width = 0;          // Minimum field width
    int precision = -1;     // Decimal precision for floats
    char fill = ' ';        // Fill character for padding
    char type = 0;          // Format type (f for float, d for decimal, etc.)
    bool leftAlign = false; // Left alignment flag
};

class StringInterpolation {
public:
    StringInterpolation(llvm::LLVMContext& context,
                       llvm::IRBuilder<>* builder,
                       llvm::Module* module,
                       TypeRegistry& typeRegistry)
        : context(context), builder(builder), module(module), typeRegistry(typeRegistry) {
        initializeStringFunctions();
    }

    // Main interpolation method
    llvm::Value* interpolate(const std::string& format,
                           const std::vector<llvm::Value*>& values,
                           const std::vector<FormatSpecifier>& specs);

    // Format value with specifier
    llvm::Value* formatValue(llvm::Value* value, const FormatSpecifier& spec);

    // Parse format specifier from string
    static FormatSpecifier parseFormatSpec(const std::string& spec);

private:
    void initializeStringFunctions();

    // Helper methods for different types
    llvm::Value* formatInt(llvm::Value* value, const FormatSpecifier& spec);
    llvm::Value* formatFloat(llvm::Value* value, const FormatSpecifier& spec);
    llvm::Value* formatBool(llvm::Value* value, const FormatSpecifier& spec);
    llvm::Value* formatString(llvm::Value* value, const FormatSpecifier& spec);

    // String manipulation helpers
    llvm::Value* allocateBuffer(size_t size);
    llvm::Value* concatenateStrings(llvm::Value* str1, llvm::Value* str2);
    llvm::Value* getStringLength(llvm::Value* str);

    llvm::LLVMContext& context;
    llvm::IRBuilder<>* builder;
    llvm::Module* module;
    TypeRegistry& typeRegistry;

    // LLVM functions for string manipulation
    llvm::Function* strlenFunc = nullptr;
    llvm::Function* strcatFunc = nullptr;
    llvm::Function* strcpyFunc = nullptr;
    llvm::Function* mallocFunc = nullptr;
    llvm::Function* freeFunc = nullptr;
    llvm::Function* sprintfFunc = nullptr;
};

} // namespace pryst
