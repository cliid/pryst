#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/DerivedTypes.h>

namespace pryst {

llvm::Function* LLVMCodegen::declareToString() {
    auto& context = module->getContext();
    auto voidType = llvm::Type::getVoidTy(context);
    auto stringType = llvm::PointerType::get(context, 0);

    std::vector<llvm::Type*> args = {voidType};
    auto funcType = llvm::FunctionType::get(stringType, args, false);
    return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "to_string", *module);
}

llvm::Value* LLVMCodegen::convertToString(llvm::Value* value) {
    if (!value) return nullptr;
    llvm::Type* type = value->getType();

    if (type->isIntegerTy(1)) {
        return builder->CreateCall(declareBoolToStr(), {value});
    } else if (type->isIntegerTy(32)) {
        return builder->CreateCall(declareIntToStr(), {value});
    } else if (type->isFloatTy()) {
        return builder->CreateCall(declareFloatToStr(), {value});
    } else {
        return builder->CreateCall(declareToString(), {value});
    }
}

llvm::Value* LLVMCodegen::convertFromString(llvm::Value* value, llvm::Type* targetType) {
    if (!value || !targetType) return nullptr;

    if (targetType->isIntegerTy(1)) {
        return builder->CreateCall(declareStrToBool(), {value});
    } else if (targetType->isIntegerTy(32)) {
        return builder->CreateCall(declareStrToInt(), {value});
    } else if (targetType->isFloatTy()) {
        return builder->CreateCall(declareStrToFloat(), {value});
    }
    return value;
}

} // namespace pryst
