#include "string_utils.hpp"
#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>

namespace pryst {

llvm::Function* declareStrlen(LLVMCodegen* codegen) {
    auto typeRegistry = codegen->getTypeRegistry();
    auto module = codegen->getModule();
    auto& context = module->getContext();

    // Get string type (i8*)
    auto stringType = llvm::PointerType::get(context, 0);
    auto intType = llvm::Type::getInt32Ty(context);

    // Create function type: i32 (i8*)
    std::vector<llvm::Type*> args = {stringType};
    auto funcType = llvm::FunctionType::get(intType, args, false);

    // Create function
    return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "strlen", *module);
}

} // namespace pryst
