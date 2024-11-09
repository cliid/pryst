#pragma once

#include <string>
#include <vector>
#include <memory>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include "codegen/type_registry.hpp"

namespace pryst {

class StringBuilder {
public:
    StringBuilder(llvm::LLVMContext& context, llvm::IRBuilder<>* builder,
                 llvm::Module* module, TypeRegistry& typeRegistry)
        : context(context), builder(builder), module(module), typeRegistry(typeRegistry) {}

    // String manipulation methods
    llvm::Value* createStringLiteral(const std::string& str);
    llvm::Value* concatenateStrings(llvm::Value* str1, llvm::Value* str2);
    llvm::Value* createFormattedString(const std::string& format,
                                     const std::vector<llvm::Value*>& args);

    // String conversion methods
    llvm::Value* convertIntToString(llvm::Value* intValue);
    llvm::Value* convertFloatToString(llvm::Value* floatValue);
    llvm::Value* convertBoolToString(llvm::Value* boolValue);

    // String operations
    llvm::Value* getStringLength(llvm::Value* str);
    llvm::Value* compareStrings(llvm::Value* str1, llvm::Value* str2);
    llvm::Value* findSubstring(llvm::Value* str, llvm::Value* substr);

    // Memory management
    llvm::Value* allocateString(size_t size);
    void freeString(llvm::Value* str);

    // Utility methods
    llvm::Value* createStringBuffer(size_t size);
    llvm::Value* copyString(llvm::Value* src);

private:
    llvm::LLVMContext& context;
    llvm::IRBuilder<>* builder;
    llvm::Module* module;
    TypeRegistry& typeRegistry;

    // Helper methods
    llvm::Function* getOrDeclareStrlen();
    llvm::Function* getOrDeclareStrcpy();
    llvm::Function* getOrDeclareStrcat();
    llvm::Function* getOrDeclareMalloc();
    llvm::Function* getOrDeclareFree();
};

} // namespace pryst
