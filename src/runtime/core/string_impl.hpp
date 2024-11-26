#pragma once

#include <string>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"

namespace pryst {
namespace core {

class StringImpl {
private:
    std::string value;

public:
    StringImpl(const std::string& value);
    ~StringImpl();

    // Core string operations
    size_t length() const;
    std::string substring(size_t start, size_t length) const;
    int indexOf(const std::string& str) const;
    int lastIndexOf(const std::string& str) const;
    std::string replace(const std::string& from, const std::string& to) const;
    std::vector<std::string> split(const std::string& delimiter) const;
    std::string trim() const;
    std::string toString() const;

    // Static LLVM registration
    static void registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder);
};

} // namespace core
} // namespace pryst
