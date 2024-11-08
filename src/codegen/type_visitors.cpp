#include "llvm_codegen.hpp"
#include "../semantic/type_info.hpp"
#include "../semantic/type_kinds.hpp"
#include <llvm/IR/DerivedTypes.h>

namespace pryst {

std::any LLVMCodegen::visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) {
    visit(ctx->expression());
    llvm::Value* value = lastValue;
    std::string targetTypeName = ctx->type()->getText();
    llvm::Type* targetType = getLLVMType(targetTypeName);

    auto& registry = *typeRegistry;
    std::string valueTypeName;
    llvm::Type* valueType = value->getType();

    if (valueType->isStructTy()) {
        valueTypeName = valueType->getStructName().str();
    } else if (valueType->isIntegerTy(1)) {
        valueTypeName = "bool";
    } else if (valueType->isIntegerTy(32)) {
        valueTypeName = "int";
    } else if (valueType->isDoubleTy()) {
        valueTypeName = "float";
    } else if (valueType->isPointerTy()) {
        valueTypeName = "string";
    }

    TypeInfoPtr valueTypeInfo = registry.getTypeInfo(valueTypeName);
    TypeInfoPtr targetTypeInfo = registry.getTypeInfo(targetTypeName);

    // Handle string conversions
    if (valueTypeInfo && valueTypeInfo->getKind() == TypeKind::String) {
        lastValue = convertFromString(value, targetType);
    } else if (targetTypeInfo && targetTypeInfo->getKind() == TypeKind::String) {
        lastValue = convertToString(value);
    } else if (value->getType()->isIntegerTy() && targetType->isFloatingPointTy()) {
        lastValue = builder->CreateSIToFP(value, targetType, "int2float");
    } else if (value->getType()->isFloatingPointTy() && targetType->isIntegerTy()) {
        lastValue = builder->CreateFPToSI(value, targetType, "float2int");
    }

    return {};
}

llvm::Value* LLVMCodegen::convertToString(llvm::Value* value) {
    if (!value) return nullptr;
    llvm::Type* type = value->getType();
    
    if (type->isIntegerTy(1)) {
        return builder->CreateCall(module->getFunction("bool_to_string"), {value});
    } else if (type->isIntegerTy(32)) {
        return builder->CreateCall(module->getFunction("int_to_string"), {value});
    } else if (type->isFloatTy()) {
        return builder->CreateCall(module->getFunction("float_to_string"), {value});
    }
    return value;
}

llvm::Value* LLVMCodegen::convertFromString(llvm::Value* value, llvm::Type* targetType) {
    if (!value || !targetType) return nullptr;
    
    if (targetType->isIntegerTy(1)) {
        return builder->CreateCall(module->getFunction("string_to_bool"), {value});
    } else if (targetType->isIntegerTy(32)) {
        return builder->CreateCall(module->getFunction("string_to_int"), {value});
    } else if (targetType->isFloatTy()) {
        return builder->CreateCall(module->getFunction("string_to_float"), {value});
    }
    return value;
}

} // namespace pryst
