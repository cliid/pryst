#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

llvm::Function* LLVMCodegen::declarePrintf() {
    llvm::FunctionType* printfType = llvm::FunctionType::get(
        llvm::IntegerType::getInt32Ty(*context), 
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0), 
        true
    );
    llvm::Function* printfFunc = llvm::Function::Create(
        printfType, 
        llvm::Function::ExternalLinkage, 
        "printf", 
        module.get()
    );
    return printfFunc;
}
