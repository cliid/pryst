#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/GlobalVariable.h>

llvm::Function* LLVMCodegen::declareBoolToStr() {
    // Create function type: bool -> char*
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getInt1Ty(*context)
    };
    auto strType = typeRegistry.getStrType();
    auto llvmStrType = LLVMTypeRegistry::getInstance().getLLVMType(strType, *context);
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmStrType,
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

    // Create global string constants for "true" and "false" using LLVM 20.0.0 API
    auto trueStr = builder->CreateGlobalString("true", "true_str");
    auto falseStr = builder->CreateGlobalString("false", "false_str");

    // Get the function parameter
    llvm::Value* boolValue = &*func->arg_begin();

    // Create conditional branch using opaque pointers
    llvm::Value* result = builder->CreateSelect(
        boolValue,
        trueStr,
        falseStr,
        "bool_str"
    );

    // Return the selected string
    builder->CreateRet(result);

    return func;
}
