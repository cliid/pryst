#include "llvm_codegen.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>

namespace pryst {

llvm::Function* LLVMCodegen::declareBoolToStr() {
    auto& context = module->getContext();
    auto boolType = llvm::Type::getInt1Ty(context);
    auto stringType = llvm::PointerType::get(context, 0);

    std::vector<llvm::Type*> args = {boolType};
    auto funcType = llvm::FunctionType::get(stringType, args, false);
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "bool_to_string", *module);

    // Create entry block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(bb);

    return func;
}

llvm::Function* LLVMCodegen::declareIntToStr() {
    auto& context = module->getContext();
    auto intType = llvm::Type::getInt32Ty(context);
    auto stringType = llvm::PointerType::get(context, 0);

    std::vector<llvm::Type*> args = {intType};
    auto funcType = llvm::FunctionType::get(stringType, args, false);
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "int_to_string", *module);

    // Create entry block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(bb);

    return func;
}

llvm::Function* LLVMCodegen::declareFloatToStr() {
    auto& context = module->getContext();
    auto floatType = llvm::Type::getFloatTy(context);
    auto stringType = llvm::PointerType::get(context, 0);

    std::vector<llvm::Type*> args = {floatType};
    auto funcType = llvm::FunctionType::get(stringType, args, false);
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "float_to_string", *module);

    // Create entry block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(bb);

    return func;
}

llvm::Function* LLVMCodegen::declareStrToBool() {
    auto& context = module->getContext();
    auto stringType = llvm::PointerType::get(context, 0);
    auto boolType = llvm::Type::getInt1Ty(context);

    std::vector<llvm::Type*> args = {stringType};
    auto funcType = llvm::FunctionType::get(boolType, args, false);
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "string_to_bool", *module);

    // Create entry block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(bb);

    return func;
}

llvm::Function* LLVMCodegen::declareStrToInt() {
    auto& context = module->getContext();
    auto stringType = llvm::PointerType::get(context, 0);
    auto intType = llvm::Type::getInt32Ty(context);

    std::vector<llvm::Type*> args = {stringType};
    auto funcType = llvm::FunctionType::get(intType, args, false);
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "string_to_int", *module);

    // Create entry block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(bb);

    return func;
}

llvm::Function* LLVMCodegen::declareStrToFloat() {
    auto& context = module->getContext();
    auto stringType = llvm::PointerType::get(context, 0);
    auto floatType = llvm::Type::getFloatTy(context);

    std::vector<llvm::Type*> args = {stringType};
    auto funcType = llvm::FunctionType::get(floatType, args, false);
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "string_to_float", *module);

    // Create entry block
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(bb);

    return func;
}

} // namespace pryst
