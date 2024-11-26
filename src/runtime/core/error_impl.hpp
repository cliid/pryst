#pragma once

#include <string>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"

namespace pryst {
namespace core {

class ErrorImpl {
private:
    std::string message;
    int code;

public:
    ErrorImpl(const std::string& message, int code = 0);
    ~ErrorImpl();

    std::string getMessage() const;
    int getCode() const;
    std::string toString() const;

    static void registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder);
};

} // namespace core
} // namespace pryst
