#pragma once
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "../utils/debug.hpp"
#include "../codegen/type_registry.hpp"
#include "llvm_codegen.hpp"

namespace pryst {

/**
 * StringBuilder class for handling string manipulation and interpolation in LLVM IR generation.
 * Provides functionality for building strings, formatting values, and string interpolation.
 */
class StringBuilder {
public:
    /**
     * Constructor initializes the StringBuilder with LLVM codegen instance.
     * @param codegen LLVMCodegen instance for LLVM operations
     */
    StringBuilder(LLVMCodegen* codegen)
        : codegen(codegen),
          context(*codegen->getContext()),
          builder(codegen->getBuilder()),
          module(codegen->getModule()),
          typeRegistry(codegen->getTypeRegistry()) {
        // Initialize string builder functions
        initializeStringFunctions();
    }

    /**
     * Appends a string literal to the builder.
     * @param str The string literal to append
     * @return LLVM Value pointer representing the appended string
     */
    llvm::Value* appendLiteral(const std::string& str);

    /**
     * Appends a formatted value to the builder.
     * @param value LLVM Value to format
     * @param format Optional format specifier string
     * @return LLVM Value pointer representing the formatted string
     */
    llvm::Value* appendFormatted(llvm::Value* value, const std::string& format = "");

    /**
     * Appends an interpolated string with variable substitutions.
     * @param format Format string with {variable} placeholders
     * @param values Map of variable names to LLVM Values
     * @return LLVM Value pointer representing the interpolated string
     */
    llvm::Value* appendInterpolatedString(const std::string& format, const std::unordered_map<std::string, llvm::Value*>& values);

    /**
     * Builds and returns the final string.
     * @return LLVM Value pointer representing the complete string
     */
    llvm::Value* build();

private:
    /**
     * Initializes required string manipulation functions.
     */
    void initializeStringFunctions();

    LLVMCodegen* codegen;
    llvm::LLVMContext& context;
    llvm::IRBuilder<>* builder;
    llvm::Module* module;
    LLVMTypeRegistry& typeRegistry;

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
