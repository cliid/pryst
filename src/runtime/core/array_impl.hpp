#pragma once

#include <vector>
#include <string>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"

namespace pryst {
namespace core {

class ArrayImpl {
private:
    void* data;          // Pointer to array data
    size_t length_;      // Current length
    size_t capacity_;    // Current capacity
    std::string type;    // Runtime type information

public:
    ArrayImpl(const std::string& elementType);
    ~ArrayImpl();

    // Core array operations
    size_t length() const { return length_; }
    void push(void* element);
    void* pop();
    void* shift();
    void unshift(void* element);
    int indexOf(void* element) const;
    ArrayImpl* slice(size_t start, size_t end) const;
    std::string join(const std::string& delimiter) const;

    // Type information
    const std::string& getType() const { return type; }

    // Internal helpers
    void ensureCapacity(size_t needed);
    size_t elementSize() const;
    bool compareElements(const void* a, const void* b) const;
    void copyElement(void* dest, const void* src) const;

    // Static LLVM registration
    static void registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder);
};

} // namespace core
} // namespace pryst
