#pragma once
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "../utils/debug.hpp"
#include "../codegen/type_registry.hpp"

namespace pryst {

class StringBuilder {
public:
    StringBuilder(llvm::LLVMContext& context, llvm::IRBuilder<>* builder, llvm::Module* module, TypeRegistry& typeRegistry)
        : context(context), builder(builder), module(module), typeRegistry(typeRegistry) {
        // Initialize string builder functions
        initializeStringFunctions();
    }

    // Add a string literal
    llvm::Value* appendLiteral(const std::string& str);

    // Add a formatted value (handles format specifiers)
    llvm::Value* appendFormatted(llvm::Value* value, const std::string& format = "");

    // Add a string literal with interpolation support
    llvm::Value* appendInterpolatedString(const std::string& format, const std::unordered_map<std::string, llvm::Value*>& values);

    // Get the final string
    llvm::Value* build();

private:
    void initializeStringFunctions();
    llvm::Value* handleFormatSpecifier(llvm::Value* value, const std::string& format);
    llvm::Value* formatFloat(llvm::Value* value, int precision);
    llvm::Value* formatInt(llvm::Value* value, int width, char pad);

    llvm::LLVMContext& context;
    llvm::IRBuilder<>* builder;
    llvm::Module* module;
    TypeRegistry& typeRegistry;

    // String manipulation functions
    llvm::Function* strlenFunc = nullptr;
    llvm::Function* strcatFunc = nullptr;
    llvm::Function* strcpyFunc = nullptr;
    llvm::Function* mallocFunc = nullptr;
    llvm::Function* freeFunc = nullptr;
    llvm::Function* sprintfFunc = nullptr;

    // Buffer for building the string
    std::vector<llvm::Value*> parts;
};

} // namespace pryst
