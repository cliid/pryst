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
    llvm::Function* declareStrlen(LLVMCodegen* codegen);
    llvm::Function* declareStrcpy(LLVMCodegen* codegen);
    llvm::Function* declareStrcat(LLVMCodegen* codegen);
    llvm::Function* declareMemcpy(LLVMCodegen* codegen);
}

#endif // STRING_UTILS_HPP
