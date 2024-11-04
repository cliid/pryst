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
    std::vector<llvm::Type*> memcpyParams = {
        llvm::Type::getInt8Ty(*context),      // dest (opaque pointer)
        llvm::Type::getInt8Ty(*context),      // src (opaque pointer)
        llvm::Type::getInt64Ty(*context),     // size
        llvm::Type::getInt1Ty(*context)       // isVolatile
    };
    llvm::FunctionType* memcpyType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*context),  // Return type: void
        memcpyParams,
        false
    );

    // Create the function with explicit attributes
    llvm::Function* memcpyFunc = llvm::Function::Create(
        memcpyType,
        llvm::Function::ExternalLinkage,
        "llvm.memcpy.p0.p0.i64",
        module.get()
    );

    // Only set essential function attributes
    memcpyFunc->addFnAttr(llvm::Attribute::WillReturn);
    memcpyFunc->addFnAttr(llvm::Attribute::NoUnwind);

    // Clear all parameter attributes
    for (auto& arg : memcpyFunc->args()) {
        arg.removeAttr(llvm::Attribute::NoAlias);
        arg.removeAttr(llvm::Attribute::NoCapture);
        arg.removeAttr(llvm::Attribute::ReadOnly);
        arg.removeAttr(llvm::Attribute::WriteOnly);
    }

    // Set parameter attributes explicitly to none
    llvm::AttributeList emptyAttrs;
    memcpyFunc->setAttributes(emptyAttrs);

    stringFunctions["memcpy"] = memcpyFunc;
    return memcpyFunc;
}
