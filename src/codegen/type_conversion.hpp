#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include "../utils/debug.hpp"
#include <vector>

namespace pryst {
    // Forward declarations
    class LLVMCodegen;

    // DEPRECATED: Type conversion functionality has been moved to LLVMCodegen class
    // Please use LLVMCodegen::declareToString(), LLVMCodegen::declareToInt(), and
    // LLVMCodegen::declareToFloat() directly instead of the TypeConversion class.
    // This header is maintained for backward compatibility and will be removed in a future version.
    class [[deprecated("Use LLVMCodegen class methods instead")]] TypeConversion {
    public:
        static llvm::Function* declareToString(llvm::LLVMContext* context, llvm::Module* module, llvm::IRBuilder<>* builder);
        static llvm::Function* declareToInt(llvm::LLVMContext* context, llvm::Module* module, llvm::IRBuilder<>* builder);
        static llvm::Function* declareToFloat(llvm::LLVMContext* context, llvm::Module* module, llvm::IRBuilder<>* builder);
    };
}
