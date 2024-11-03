#include "llvm_utils.hpp"

namespace pryst {

llvm::Value* LLVMUtils::createGlobalString(llvm::IRBuilder<>& builder,
                                         llvm::Module* module,
                                         const std::string& str,
                                         const std::string& name) {
    // Create a global string using LLVM 20.0.0's CreateGlobalString API
    return builder.CreateGlobalString(str, name.empty() ? ".str" : name);
}

llvm::Value* LLVMUtils::createInBoundsGEP(llvm::IRBuilder<>& builder,
                                         llvm::Type* type,
                                         llvm::Value* ptr,
                                         const std::vector<llvm::Value*>& indices) {
    // Use the new LLVM 20.0.0 GEP creation API that requires the pointee type
    return builder.CreateInBoundsGEP(type, ptr, indices);
}

llvm::PointerType* LLVMUtils::getPointerType(llvm::Type* elementType) {
    // Use LLVM 20.0.0's new pointer type creation API
    return llvm::PointerType::getUnqual(elementType);
}

llvm::Value* LLVMUtils::createLoad(llvm::IRBuilder<>& builder,
                                 llvm::Type* type,
                                 llvm::Value* ptr) {
    // Use LLVM 20.0.0's load instruction creation that requires the loaded type
    return builder.CreateLoad(type, ptr);
}

llvm::Value* LLVMUtils::createStore(llvm::IRBuilder<>& builder,
                                  llvm::Value* value,
                                  llvm::Value* ptr) {
    // Create store instruction (API unchanged in LLVM 20.0.0)
    return builder.CreateStore(value, ptr);
}

llvm::Value* LLVMUtils::createBitCast(llvm::IRBuilder<>& builder,
                                    llvm::Value* value,
                                    llvm::Type* destType) {
    // Create bitcast instruction (API unchanged in LLVM 20.0.0)
    return builder.CreateBitCast(value, destType);
}

llvm::Value* LLVMUtils::createCall(llvm::IRBuilder<>& builder,
                                 llvm::FunctionCallee callee,
                                 const std::vector<llvm::Value*>& args,
                                 const std::string& name) {
    return builder.CreateCall(callee, args, name.empty() ? "calltmp" : name);
}

llvm::Value* LLVMUtils::createICmpNE(llvm::IRBuilder<>& builder,
                                   llvm::Value* lhs,
                                   llvm::Value* rhs,
                                   const std::string& name) {
    return builder.CreateICmpNE(lhs, rhs, name.empty() ? "cmptmp" : name);
}

llvm::Value* LLVMUtils::createICmpEQ(llvm::IRBuilder<>& builder,
                                   llvm::Value* lhs,
                                   llvm::Value* rhs,
                                   const std::string& name) {
    return builder.CreateICmpEQ(lhs, rhs, name.empty() ? "cmptmp" : name);
}

void LLVMUtils::createCondBr(llvm::IRBuilder<>& builder,
                           llvm::Value* cond,
                           llvm::BasicBlock* trueBlock,
                           llvm::BasicBlock* falseBlock) {
    builder.CreateCondBr(cond, trueBlock, falseBlock);
}

void LLVMUtils::createBr(llvm::IRBuilder<>& builder,
                        llvm::BasicBlock* destBlock) {
    builder.CreateBr(destBlock);
}

llvm::Value* LLVMUtils::createAdd(llvm::IRBuilder<>& builder,
                                llvm::Value* lhs,
                                llvm::Value* rhs,
                                const std::string& name) {
    return builder.CreateAdd(lhs, rhs, name.empty() ? "addtmp" : name);
}

llvm::Value* LLVMUtils::createFAdd(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name) {
    return builder.CreateFAdd(lhs, rhs, name.empty() ? "addtmp" : name);
}

llvm::Value* LLVMUtils::createSub(llvm::IRBuilder<>& builder,
                                llvm::Value* lhs,
                                llvm::Value* rhs,
                                const std::string& name) {
    return builder.CreateSub(lhs, rhs, name.empty() ? "subtmp" : name);
}

llvm::Value* LLVMUtils::createFSub(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name) {
    return builder.CreateFSub(lhs, rhs, name.empty() ? "subtmp" : name);
}

llvm::Value* LLVMUtils::createMul(llvm::IRBuilder<>& builder,
                                llvm::Value* lhs,
                                llvm::Value* rhs,
                                const std::string& name) {
    return builder.CreateMul(lhs, rhs, name.empty() ? "multmp" : name);
}

llvm::Value* LLVMUtils::createFMul(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name) {
    return builder.CreateFMul(lhs, rhs, name.empty() ? "multmp" : name);
}

llvm::Value* LLVMUtils::createSDiv(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name) {
    return builder.CreateSDiv(lhs, rhs, name.empty() ? "divtmp" : name);
}

llvm::Value* LLVMUtils::createFDiv(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name) {
    return builder.CreateFDiv(lhs, rhs, name.empty() ? "divtmp" : name);
}

llvm::Value* LLVMUtils::createSRem(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name) {
    return builder.CreateSRem(lhs, rhs, name.empty() ? "modtmp" : name);
}

} // namespace pryst
