#include "llvm_codegen.hpp"
#include "../utils/debug.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/BasicBlock.h>

namespace pryst {

std::any LLVMCodegen::visitParenthesizedCast(PrystParser::ParenthesizedCastContext* ctx) {
    PRYST_DEBUG("Visiting parenthesized cast expression");
    auto& context = module->getContext();

    std::any valueResult = visit(ctx->expression());
    llvm::Value* value = std::any_cast<llvm::Value*>(valueResult);
    std::string targetType = ctx->type()->getText();

    return convertType(value, targetType);
}

std::any LLVMCodegen::visitConstructorCast(PrystParser::ConstructorCastContext* ctx) {
    PRYST_DEBUG("Visiting constructor cast expression");
    auto& context = module->getContext();

    std::any valueResult = visit(ctx->expression());
    llvm::Value* value = std::any_cast<llvm::Value*>(valueResult);
    std::string targetType = ctx->type()->getText();

    return convertType(value, targetType);
}

llvm::Value* LLVMCodegen::convertType(llvm::Value* value, const std::string& targetType) {
    if (!value) return nullptr;

    auto& context = module->getContext();

    // Handle basic type conversions
    if (targetType == "str") {
        return convertToString(value);
    } else if (targetType == "int") {
        if (value->getType()->isFloatTy() || value->getType()->isDoubleTy()) {
            return builder->CreateFPToSI(value, llvm::Type::getInt32Ty(context));
        }
    } else if (targetType == "float") {
        if (value->getType()->isIntegerTy()) {
            return builder->CreateSIToFP(value, llvm::Type::getDoubleTy(context));
        }
    }

    // Handle class type conversions through the type registry
    return typeRegistry->convertType(value, targetType);
}

} // namespace pryst
