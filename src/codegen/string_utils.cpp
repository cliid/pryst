#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IntrinsicInst.h>

llvm::Function* LLVMCodegen::declareStrlen() {
    // strlen(char* str) -> size_t
    auto strType = typeRegistry.getStrType();
    auto llvmStrType = LLVMTypeRegistry::getInstance().getLLVMType(strType, *context);
    llvm::FunctionType* strlenType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),  // Return type: size_t
        llvmStrType,                       // Parameter: string
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
    auto strType = typeRegistry.getStrType();
    auto llvmStrType = LLVMTypeRegistry::getInstance().getLLVMType(strType, *context);
    std::vector<llvm::Type*> strcpyParams = {
        llvmStrType,  // dest
        llvmStrType   // src
    };
    llvm::FunctionType* strcpyType = llvm::FunctionType::get(
        llvmStrType,  // Return type: string
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
    auto strType = typeRegistry.getStrType();
    auto llvmStrType = LLVMTypeRegistry::getInstance().getLLVMType(strType, *context);
    std::vector<llvm::Type*> strcatParams = {
        llvmStrType,  // dest
        llvmStrType   // src
    };
    llvm::FunctionType* strcatType = llvm::FunctionType::get(
        llvmStrType,  // Return type: string
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
    auto strType = typeRegistry.getStrType();
    auto llvmStrType = LLVMTypeRegistry::getInstance().getLLVMType(strType, *context);
    std::vector<llvm::Type*> memcpyParams = {
        llvmStrType,                       // dest
        llvmStrType,                       // src
        llvm::Type::getInt64Ty(*context)  // size
    };
    llvm::FunctionType* memcpyType = llvm::FunctionType::get(
        llvmStrType,  // Return type: string
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
