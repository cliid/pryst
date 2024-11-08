#include "codegen/string_builder.hpp"
#include "utils/debug.hpp"

namespace pryst {

llvm::Value* StringBuilder::createStringBuffer(size_t size) {
    auto mallocFunc = getOrDeclareMalloc();
    return builder->CreateCall(mallocFunc, {builder->getInt64(size)});
}

llvm::Value* StringBuilder::createStringLiteral(const std::string& str) {
    PRYST_DEBUG("Creating string literal: " + str);
    return builder->CreateGlobalString(str);
}

llvm::Value* StringBuilder::concatenateStrings(llvm::Value* str1, llvm::Value* str2) {
    PRYST_DEBUG("Concatenating strings");

    auto strlenFunc = getOrDeclareStrlen();
    auto len1 = builder->CreateCall(strlenFunc, {str1});
    auto len2 = builder->CreateCall(strlenFunc, {str2});

    // Calculate total length needed
    auto totalLen = builder->CreateAdd(
        builder->CreateAdd(len1, len2),
        builder->getInt64(1)  // For null terminator
    );

    // Allocate buffer and copy strings
    auto mallocFunc = getOrDeclareMalloc();
    auto buffer = builder->CreateCall(mallocFunc, {totalLen});

    builder->CreateCall(getOrDeclareStrcpy(), {buffer, str1});
    builder->CreateCall(getOrDeclareStrcat(), {buffer, str2});

    return buffer;
}

llvm::Function* StringBuilder::getOrDeclareStrlen() {
    auto funcType = llvm::FunctionType::get(
        typeRegistry.getInt64Type(),
        {typeRegistry.getPointerType(typeRegistry.getInt8Type())},
        false
    );
    return llvm::cast<llvm::Function>(
        module->getOrInsertFunction("strlen", funcType).getCallee()
    );
}

llvm::Function* StringBuilder::getOrDeclareStrcpy() {
    auto funcType = llvm::FunctionType::get(
        typeRegistry.getPointerType(typeRegistry.getInt8Type()),
        {typeRegistry.getPointerType(typeRegistry.getInt8Type()),
         typeRegistry.getPointerType(typeRegistry.getInt8Type())},
        false
    );
    return llvm::cast<llvm::Function>(
        module->getOrInsertFunction("strcpy", funcType).getCallee()
    );
}

llvm::Function* StringBuilder::getOrDeclareStrcat() {
    auto funcType = llvm::FunctionType::get(
        typeRegistry.getPointerType(typeRegistry.getInt8Type()),
        {typeRegistry.getPointerType(typeRegistry.getInt8Type()),
         typeRegistry.getPointerType(typeRegistry.getInt8Type())},
        false
    );
    return llvm::cast<llvm::Function>(
        module->getOrInsertFunction("strcat", funcType).getCallee()
    );
}

llvm::Function* StringBuilder::getOrDeclareMalloc() {
    auto funcType = llvm::FunctionType::get(
        typeRegistry.getPointerType(typeRegistry.getInt8Type()),
        {typeRegistry.getInt64Type()},
        false
    );
    return llvm::cast<llvm::Function>(
        module->getOrInsertFunction("malloc", funcType).getCallee()
    );
}

llvm::Function* StringBuilder::getOrDeclareFree() {
    auto funcType = llvm::FunctionType::get(
        typeRegistry.getVoidType(),
        {typeRegistry.getPointerType(typeRegistry.getInt8Type())},
        false
    );
    return llvm::cast<llvm::Function>(
        module->getOrInsertFunction("free", funcType).getCallee()
    );
}

void StringBuilder::freeString(llvm::Value* str) {
    builder->CreateCall(getOrDeclareFree(), {str});
}

} // namespace pryst
