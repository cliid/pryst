#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>

llvm::Function* LLVMCodegen::declareBoolToStr() {
    // Create function type: bool -> char*
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getInt1Ty(*context)
    };
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        paramTypes,
        false
    );

    // Create the function
    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "boolToStr",
        module.get()
    );

    // Create basic block
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Create global string constants for "true" and "false"
    llvm::Value* trueStr = builder->CreateGlobalStringPtr("true", "true_str");
    llvm::Value* falseStr = builder->CreateGlobalStringPtr("false", "false_str");

    // Get the function parameter
    llvm::Value* boolValue = &*func->arg_begin();

    // Create conditional branch
    llvm::Value* result = builder->CreateSelect(
        boolValue,
        builder->CreateBitCast(trueStr, llvm::Type::getInt8PtrTy(*context)),
        builder->CreateBitCast(falseStr, llvm::Type::getInt8PtrTy(*context)),
        "bool_str"
    );

    // Return the selected string
    builder->CreateRet(result);

    return func;
}
