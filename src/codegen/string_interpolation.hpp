#pragma once

#include <string>
#include <vector>
#include <memory>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include "type_registry.hpp"
#include "string_utils.hpp"

namespace pryst {
namespace codegen {

class StringInterpolation {
public:
    StringInterpolation(llvm::LLVMContext& context, llvm::IRBuilder<>& builder, TypeRegistry& typeRegistry);

    // Generate LLVM IR for string interpolation
    llvm::Value* generateInterpolatedString(
        const std::string& format,
        const std::vector<llvm::Value*>& expressions
    );

    // Handle escape sequences in string literals
    std::string processEscapeSequences(const std::string& input);

    // Parse interpolation expressions from string
    std::vector<std::string> parseInterpolationExpressions(const std::string& str);

private:
    llvm::LLVMContext& context;
    llvm::IRBuilder<>& builder;
    TypeRegistry& typeRegistry;

    // Helper methods for code generation
    llvm::Value* convertToString(llvm::Value* value);
    llvm::Value* concatenateStrings(llvm::Value* str1, llvm::Value* str2);

    // Runtime support functions
    llvm::Function* getStringConcatFunction();
    llvm::Function* getIntToStringFunction();
    llvm::Function* getFloatToStringFunction();
    llvm::Function* getBoolToStringFunction();

    // Utility methods
    std::string extractExpressionFromPlaceholder(const std::string& placeholder);
    bool isValidEscapeSequence(char c);
};

} // namespace codegen
} // namespace pryst
