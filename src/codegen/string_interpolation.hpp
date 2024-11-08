#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <string>
#include <optional>
#include "type_registry.hpp"

namespace pryst {
namespace codegen {

struct FormatSpecifier {
    char alignment;           // '<', '>', or '\0'
    char fill;               // Fill character for padding
    int width;              // Minimum field width
    int precision;          // Precision for floating-point
    char type;              // 'd', 'f', 's', 'b', or '\0'

    FormatSpecifier()
        : alignment('\0'), fill(' '), width(-1), precision(-1), type('\0') {}
};

class StringInterpolation {
public:
    StringInterpolation(llvm::IRBuilder<>* builder, llvm::Module* module, LLVMTypeRegistry* registry)
        : builder_(*builder), module_(module), typeRegistry_(registry) {}

    // Parse a format specifier string (e.g., ":>10.2f")
    std::optional<FormatSpecifier> parseFormatSpec(const std::string& spec);

    // Generate LLVM IR for formatted value
    llvm::Value* generateFormattedValue(llvm::Value* value,
                                      const FormatSpecifier& format,
                                      const std::string& originalExpr);

    // Generate interpolation call
    llvm::Value* generateInterpolation(const std::string& format,
                                     const std::vector<llvm::Value*>& values);

private:
    llvm::IRBuilder<>& builder_;
    llvm::Module* module_;
    LLVMTypeRegistry* typeRegistry_;

    // Helper methods for different types
    llvm::Value* formatInteger(llvm::Value* value, const FormatSpecifier& format);
    llvm::Value* formatFloat(llvm::Value* value, const FormatSpecifier& format);
    llvm::Value* formatBoolean(llvm::Value* value, const FormatSpecifier& format);
    llvm::Value* formatString(llvm::Value* value, const FormatSpecifier& format);

    // Get or declare runtime formatting functions
    llvm::Function* getFormatIntFunction();
    llvm::Function* getFormatFloatFunction();
    llvm::Function* getFormatBoolFunction();
    llvm::Function* getFormatStringFunction();
    llvm::Function* getInterpolateStringFunction();
};

} // namespace codegen
} // namespace pryst
