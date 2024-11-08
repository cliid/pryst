#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <string>
#include <memory>
#include "../semantic/type_info.hpp"
#include "type_registry.hpp"

class LLVMUtils {
public:
    static llvm::Value* createGlobalString(llvm::IRBuilder<>& builder,
                                         llvm::Module* module,
                                         const std::string& str,
                                         const std::string& name = "");

    static llvm::Value* createInBoundsGEP(llvm::IRBuilder<>& builder,
                                         llvm::Type* type,
                                         llvm::Value* ptr,
                                         const std::vector<llvm::Value*>& indices);

    // Removed getPointerType as LLVM no longer handles pointer types

    static llvm::Value* createLoad(llvm::IRBuilder<>& builder,
                                 llvm::Type* type,
                                 llvm::Value* ptr,
                                 const std::string& name = "");

    static llvm::Value* createStore(llvm::IRBuilder<>& builder,
                                  llvm::Value* value,
                                  llvm::Value* ptr);

    static llvm::Value* createBitCast(llvm::IRBuilder<>& builder,
                                    llvm::Value* value,
                                    llvm::Type* destType,
                                    const std::string& name = "");

    static llvm::Value* createCall(llvm::IRBuilder<>& builder,
                                 llvm::FunctionCallee callee,
                                 const std::vector<llvm::Value*>& args,
                                 const std::string& name = "");

    // Comparison operations
    static llvm::Value* createICmpNE(llvm::IRBuilder<>& builder,
                                   llvm::Value* lhs,
                                   llvm::Value* rhs,
                                   const std::string& name = "");

    static llvm::Value* createICmpEQ(llvm::IRBuilder<>& builder,
                                   llvm::Value* lhs,
                                   llvm::Value* rhs,
                                   const std::string& name = "");

    // Branch instructions
    static void createCondBr(llvm::IRBuilder<>& builder,
                           llvm::Value* cond,
                           llvm::BasicBlock* trueBlock,
                           llvm::BasicBlock* falseBlock);

    static void createBr(llvm::IRBuilder<>& builder,
                        llvm::BasicBlock* destBlock);

    // Arithmetic operations
    static llvm::Value* createAdd(llvm::IRBuilder<>& builder,
                                llvm::Value* lhs,
                                llvm::Value* rhs,
                                const std::string& name = "");

    static llvm::Value* createFAdd(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name = "");

    static llvm::Value* createSub(llvm::IRBuilder<>& builder,
                                llvm::Value* lhs,
                                llvm::Value* rhs,
                                const std::string& name = "");

    static llvm::Value* createFSub(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name = "");

    static llvm::Value* createMul(llvm::IRBuilder<>& builder,
                                llvm::Value* lhs,
                                llvm::Value* rhs,
                                const std::string& name = "");

    static llvm::Value* createFMul(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name = "");

    static llvm::Value* createSDiv(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name = "");

    static llvm::Value* createFDiv(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name = "");

    static llvm::Value* createSRem(llvm::IRBuilder<>& builder,
                                 llvm::Value* lhs,
                                 llvm::Value* rhs,
                                 const std::string& name = "");
};
