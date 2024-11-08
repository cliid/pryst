#include "llvm_codegen.hpp"
#include "../utils/debug.hpp"
#include <llvm/IR/Constants.h>

namespace pryst {

llvm::Value* LLVMCodegen::generateTypeOf(llvm::Value* value) {
    if (!value) return nullptr;

    auto& context = module->getContext();
    auto type = value->getType();
    std::string typeName;

    if (type->isIntegerTy(32)) {
        typeName = "int";
    } else if (type->isDoubleTy()) {
        typeName = "float";
    } else if (type->isIntegerTy(1)) {
        typeName = "bool";
    } else if (type->isPointerTy()) {
        typeName = "str"; // Assuming pointer is string for now
    } else {
        typeName = "unknown";
    }

    // Create global string constant using CreateGlobalString
    auto typeStrGlobal = builder->CreateGlobalString(typeName);
    return builder->CreateBitCast(typeStrGlobal, typeRegistry->getPointerType(typeRegistry->getInt8Type()));
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    if (!value) return nullptr;

    auto type = value->getType();
    bool isInstance = false;

    if (typeName == "int") {
        isInstance = type->isIntegerTy(32);
    } else if (typeName == "float") {
        isInstance = type->isDoubleTy();
    } else if (typeName == "bool") {
        isInstance = type->isIntegerTy(1);
    } else if (typeName == "str") {
        isInstance = type->isPointerTy();
    }

    return llvm::ConstantInt::get(typeRegistry->getBoolType(), isInstance);
}

llvm::Value* LLVMCodegen::generateGetTypeInfo(const std::string& typeName) {
    auto typeInfo = typeRegistry->getTypeInfo(typeName);
    if (!typeInfo) {
        PRYST_ERROR("Unknown type: " + typeName);
        return nullptr;
    }

    // Create type info structure
    std::string info = "Type: " + typeName + "\n";
    info += "Size: " + std::to_string(typeInfo->getSize()) + " bytes\n";

    // Create global string constant using CreateGlobalString
    auto infoStrGlobal = builder->CreateGlobalString(info);
    return builder->CreateBitCast(infoStrGlobal, typeRegistry->getPointerType(typeRegistry->getInt8Type()));
}

} // namespace pryst
