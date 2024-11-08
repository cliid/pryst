#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>
#include "llvm_codegen.hpp"
#include "type_registry.hpp"

namespace string_utils {
    // Basic string operations
    llvm::Function* declareStrlen(pryst::LLVMCodegen* codegen);
    llvm::Function* declareStrcpy(pryst::LLVMCodegen* codegen);
    llvm::Function* declareStrcat(pryst::LLVMCodegen* codegen);
    llvm::Function* declareMemcpy(pryst::LLVMCodegen* codegen);

    // String interpolation
    llvm::Function* declareFormatFloat(pryst::LLVMCodegen* codegen);  // For {value:.2f} style formatting
    llvm::Function* declareFormatInt(pryst::LLVMCodegen* codegen);    // For {value:03d} style formatting
    llvm::Function* declareFormatBool(pryst::LLVMCodegen* codegen);   // For {value} boolean formatting

    // Format specifier parsing
    struct FormatSpec {
        int width;          // Minimum field width
        int precision;      // Decimal precision for floats
        char fill;          // Fill character for padding
        char type;          // Format type (f for float, d for decimal, etc.)
        bool leftAlign;     // Left alignment flag
    };

    // Helper functions for string interpolation
    FormatSpec parseFormatSpec(const std::string& spec);
    llvm::Value* formatValue(pryst::LLVMCodegen* codegen, llvm::Value* value, const FormatSpec& spec);
    llvm::Value* interpolateString(pryst::LLVMCodegen* codegen, const std::string& format,
                                 const std::vector<llvm::Value*>& values,
                                 const std::vector<FormatSpec>& specs);
}

#endif // STRING_UTILS_HPP
