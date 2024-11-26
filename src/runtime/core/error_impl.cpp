#include "error_impl.hpp"
#include <stdexcept>
#include <sstream>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Verifier.h"

namespace pryst {
namespace core {

ErrorImpl::ErrorImpl(const std::string& message, int code)
    : message(message), code(code) {}

ErrorImpl::~ErrorImpl() {}

std::string ErrorImpl::getMessage() const {
    return message;
}

int ErrorImpl::getCode() const {
    return code;
}

std::string ErrorImpl::toString() const {
    std::stringstream ss;
    ss << "Error(" << message << ", code=" << code << ")";
    return ss.str();
}

void ErrorImpl::registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder) {
    auto& context = module->getContext();
    auto voidTy = llvm::Type::getVoidTy(context);
    auto int8PtrTy = llvm::Type::getInt8PtrTy(context);
    auto int32Ty = llvm::Type::getInt32Ty(context);

    // Create Error class type
    std::vector<llvm::Type*> errorFields;
    errorFields.push_back(int8PtrTy);  // message
    errorFields.push_back(int32Ty);    // code
    auto errorStructTy = llvm::StructType::create(context, errorFields, "struct.pryst.core.Error");

    // Create constructor
    std::vector<llvm::Type*> ctorArgs = {int8PtrTy, int32Ty};  // message and code
    auto ctorTy = llvm::FunctionType::get(errorStructTy->getPointerTo(), ctorArgs, false);
    auto ctor = llvm::Function::Create(ctorTy, llvm::Function::ExternalLinkage,
                                     "Error_new", module);

    // Create constructor body
    auto ctorBB = llvm::BasicBlock::Create(context, "entry", ctor);
    builder.SetInsertPoint(ctorBB);

    // Allocate Error object
    auto errorObj = builder.CreateAlloca(errorStructTy);

    // Store message
    auto messageGEP = builder.CreateStructGEP(errorStructTy, errorObj, 0);
    builder.CreateStore(ctor->getArg(0), messageGEP);

    // Store code
    auto codeGEP = builder.CreateStructGEP(errorStructTy, errorObj, 1);
    builder.CreateStore(ctor->getArg(1), codeGEP);

    // Return the object
    builder.CreateRet(errorObj);

    // Create getMessage method
    std::vector<llvm::Type*> getMessageArgs = {errorStructTy->getPointerTo()};
    auto getMessageTy = llvm::FunctionType::get(int8PtrTy, getMessageArgs, false);
    auto getMessage = llvm::Function::Create(getMessageTy, llvm::Function::ExternalLinkage,
                                          "Error_getMessage", module);

    // Create getMessage body
    auto getMessageBB = llvm::BasicBlock::Create(context, "entry", getMessage);
    builder.SetInsertPoint(getMessageBB);

    // Get message from this pointer
    auto thisObj = getMessage->getArg(0);
    auto messageGEP2 = builder.CreateStructGEP(errorStructTy, thisObj, 0);
    auto message = builder.CreateLoad(int8PtrTy, messageGEP2);
    builder.CreateRet(message);

    // Create getCode method
    std::vector<llvm::Type*> getCodeArgs = {errorStructTy->getPointerTo()};
    auto getCodeTy = llvm::FunctionType::get(int32Ty, getCodeArgs, false);
    auto getCode = llvm::Function::Create(getCodeTy, llvm::Function::ExternalLinkage,
                                       "Error_getCode", module);

    // Create getCode body
    auto getCodeBB = llvm::BasicBlock::Create(context, "entry", getCode);
    builder.SetInsertPoint(getCodeBB);

    // Get code from this pointer
    auto thisObj2 = getCode->getArg(0);
    auto codeGEP2 = builder.CreateStructGEP(errorStructTy, thisObj2, 1);
    auto code = builder.CreateLoad(int32Ty, codeGEP2);
    builder.CreateRet(code);

    // Create toString method
    std::vector<llvm::Type*> toStringArgs = {errorStructTy->getPointerTo()};
    auto toStringTy = llvm::FunctionType::get(int8PtrTy, toStringArgs, false);
    auto toString = llvm::Function::Create(toStringTy, llvm::Function::ExternalLinkage,
                                        "Error_toString", module);

    // Create toString body
    auto toStringBB = llvm::BasicBlock::Create(context, "entry", toString);
    builder.SetInsertPoint(toStringBB);

    // Call extern C function to create string representation
    auto toStringFn = module->getOrInsertFunction("pryst_core_Error_toString",
        llvm::FunctionType::get(int8PtrTy, {errorStructTy->getPointerTo()}, false));
    auto result = builder.CreateCall(toStringFn, {toString->getArg(0)});
    builder.CreateRet(result);

    // Verify all functions
    llvm::verifyFunction(*ctor);
    llvm::verifyFunction(*getMessage);
    llvm::verifyFunction(*getCode);
    llvm::verifyFunction(*toString);
}

} // namespace core
} // namespace pryst
