#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include "../utils/debug.hpp"
#include <vector>

namespace pryst {
    class TypeConversion {
    public:
        static llvm::Function* declareToString(llvm::LLVMContext* context, llvm::Module* module, llvm::IRBuilder<>* builder);
        static llvm::Function* declareToInt(llvm::LLVMContext* context, llvm::Module* module, llvm::IRBuilder<>* builder);
        static llvm::Function* declareToFloat(llvm::LLVMContext* context, llvm::Module* module, llvm::IRBuilder<>* builder);
    };
}
