#pragma once

#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <string>

namespace pryst {

class LLVMCodegen;  // Forward declaration

// These functions should be member functions of LLVMCodegen
// They are declared here for organization purposes
class BuiltinFunctions {
public:
    // Type conversion functions
    static llvm::Function* declareBoolToStr(LLVMCodegen* codegen);
    static llvm::Function* declareIntToStr(LLVMCodegen* codegen);
    static llvm::Function* declareFloatToStr(LLVMCodegen* codegen);

    // String manipulation functions
    static llvm::Function* declareStrConcat(LLVMCodegen* codegen);
    static llvm::Function* declareStrLen(LLVMCodegen* codegen);
    static llvm::Function* declareStrSubstr(LLVMCodegen* codegen);

    // Math functions
    static llvm::Function* declareMathSqrt(LLVMCodegen* codegen);
    static llvm::Function* declareMathPow(LLVMCodegen* codegen);
    static llvm::Function* declareMathAbs(LLVMCodegen* codegen);
};

} // namespace pryst
