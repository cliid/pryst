#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IntrinsicInst.h>

llvm::Function* LLVMCodegen::declareStrlen() {
    // strlen(char* str) -> size_t
    auto int8Ty = llvm::Type::getInt8Ty(*context);
    auto int8PtrTy = llvm::PointerType::getUnqual(int8Ty);
    llvm::FunctionType* strlenType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        int8PtrTy,
        false
    );
    llvm::Function* strlenFunc = llvm::Function::Create(
        strlenType,
        llvm::Function::ExternalLinkage,
        "strlen",
        module.get()
    );
    stringFunctions["strlen"] = strlenFunc;
    return strlenFunc;
}

llvm::Function* LLVMCodegen::declareStrcpy() {
    // strcpy(char* dest, const char* src) -> char*
    auto int8Ty = llvm::Type::getInt8Ty(*context);
    auto int8PtrTy = llvm::PointerType::getUnqual(int8Ty);
    std::vector<llvm::Type*> strcpyParams = {
        int8PtrTy,
        int8PtrTy
    };
    llvm::FunctionType* strcpyType = llvm::FunctionType::get(
        int8PtrTy,
        strcpyParams,
        false
    );
    llvm::Function* strcpyFunc = llvm::Function::Create(
        strcpyType,
        llvm::Function::ExternalLinkage,
        "strcpy",
        module.get()
    );
    stringFunctions["strcpy"] = strcpyFunc;
    return strcpyFunc;
}

llvm::Function* LLVMCodegen::declareStrcat() {
    // strcat(char* dest, const char* src) -> char*
    auto int8Ty = llvm::Type::getInt8Ty(*context);
    auto int8PtrTy = llvm::PointerType::getUnqual(int8Ty);
    std::vector<llvm::Type*> strcatParams = {
        int8PtrTy,
        int8PtrTy
    };
    llvm::FunctionType* strcatType = llvm::FunctionType::get(
        int8PtrTy,
        strcatParams,
        false
    );
    llvm::Function* strcatFunc = llvm::Function::Create(
        strcatType,
        llvm::Function::ExternalLinkage,
        "strcat",
        module.get()
    );
    stringFunctions["strcat"] = strcatFunc;
    return strcatFunc;
}

llvm::Function* LLVMCodegen::declareMemcpy() {
    // memcpy(void* dest, const void* src, size_t n) -> void*
    auto int8Ty = llvm::Type::getInt8Ty(*context);
    auto int8PtrTy = llvm::PointerType::getUnqual(int8Ty);
    std::vector<llvm::Type*> memcpyParams = {
        int8PtrTy,
        int8PtrTy,
        llvm::Type::getInt64Ty(*context)
    };
    llvm::FunctionType* memcpyType = llvm::FunctionType::get(
        int8PtrTy,
        memcpyParams,
        false
    );
    llvm::Function* memcpyFunc = llvm::Function::Create(
        memcpyType,
        llvm::Function::ExternalLinkage,
        "llvm.memcpy.p0i8.p0i8.i64",
        module.get()
    );
    stringFunctions["memcpy"] = memcpyFunc;
    return memcpyFunc;
}
