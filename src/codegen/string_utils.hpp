#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include "llvm_codegen.hpp"
#include "type_registry.hpp"

// String utility function declarations
class LLVMCodegen;  // Forward declaration

namespace string_utils {
    // Basic string operations
    llvm::Function* declareStrlen(LLVMCodegen* codegen);
    llvm::Function* declareStrcpy(LLVMCodegen* codegen);
    llvm::Function* declareStrcat(LLVMCodegen* codegen);
    llvm::Function* declareMemcpy(LLVMCodegen* codegen);

    // String interpolation
    llvm::Function* declareFormatFloat(LLVMCodegen* codegen);  // For {value:.2f} style formatting
    llvm::Function* declareFormatInt(LLVMCodegen* codegen);    // For {value:03d} style formatting
    llvm::Function* declareFormatBool(LLVMCodegen* codegen);   // For {value} boolean formatting

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
    llvm::Value* formatValue(LLVMCodegen* codegen, llvm::Value* value, const FormatSpec& spec);
    llvm::Value* interpolateString(LLVMCodegen* codegen, const std::string& format,
                                 const std::vector<llvm::Value*>& values,
                                 const std::vector<FormatSpec>& specs);
}

#endif // STRING_UTILS_HPP
