#pragma once

#include <llvm/IR/Function.h>
#include "codegen/llvm_codegen.hpp"

namespace pryst {

llvm::Function* declareStrlen(LLVMCodegen* codegen);
llvm::Function* declareStrcpy(LLVMCodegen* codegen);
llvm::Function* declareStrcat(LLVMCodegen* codegen);

} // namespace pryst
