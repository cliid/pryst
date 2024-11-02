#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IntrinsicInst.h>

llvm::Function* LLVMCodegen::declareStrlen() {
    // strlen(char* str) -> size_t
    llvm::FunctionType* strlenType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
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
    std::vector<llvm::Type*> strcpyParams = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)
    };
    llvm::FunctionType* strcpyType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
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
    std::vector<llvm::Type*> strcatParams = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0)
    };
    llvm::FunctionType* strcatType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
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
    std::vector<llvm::Type*> memcpyParams = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
        llvm::Type::getInt64Ty(*context)
    };
    llvm::FunctionType* memcpyType = llvm::FunctionType::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0),
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
