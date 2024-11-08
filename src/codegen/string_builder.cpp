#include "string_builder.hpp"
#include "../utils/debug.hpp"
#include <regex>
#include <vector>
#include <sstream>
#include <cstdio>

namespace pryst {



void StringBuilder::initializeStringFunctions() {
    PRYST_DEBUG("Initializing string builder functions");

    // Get types we'll need using TypeRegistry
    auto charPtrTy = typeRegistry.getPointerType();
    auto int32Ty = builder->getInt32Ty();
    auto int64Ty = builder->getInt64Ty();
    auto voidTy = builder->getVoidTy();

    // strlen(char*) -> size_t
    std::vector<llvm::Type*> strlenArgs;
    strlenArgs.push_back(charPtrTy);
    strlenFunc = llvm::Function::Create(
        llvm::FunctionType::get(int64Ty, strlenArgs, false),
        llvm::Function::ExternalLinkage,
        "strlen",
        module
    );

    // strcat(char*, const char*) -> char*
    std::vector<llvm::Type*> strcatArgs;
    strcatArgs.push_back(charPtrTy);
    strcatArgs.push_back(charPtrTy);
    strcatFunc = llvm::Function::Create(
        llvm::FunctionType::get(charPtrTy, strcatArgs, false),
        llvm::Function::ExternalLinkage,
        "strcat",
        module
    );

    // strcpy(char*, const char*) -> char*
    std::vector<llvm::Type*> strcpyArgs;
    strcpyArgs.push_back(charPtrTy);
    strcpyArgs.push_back(charPtrTy);
    strcpyFunc = llvm::Function::Create(
        llvm::FunctionType::get(charPtrTy, strcpyArgs, false),
        llvm::Function::ExternalLinkage,
        "strcpy",
        module
    );

    // malloc(size_t) -> void*
    std::vector<llvm::Type*> mallocArgs;
    mallocArgs.push_back(int64Ty);
    mallocFunc = llvm::Function::Create(
        llvm::FunctionType::get(charPtrTy, mallocArgs, false),
        llvm::Function::ExternalLinkage,
        "malloc",
        module
    );

    // free(void*)
    std::vector<llvm::Type*> freeArgs;
    freeArgs.push_back(charPtrTy);
    freeFunc = llvm::Function::Create(
        llvm::FunctionType::get(voidTy, freeArgs, false),
        llvm::Function::ExternalLinkage,
        "free",
        module
    );

    // Initialize sprintf with variadic arguments
    std::vector<llvm::Type*> sprintfArgs;
    sprintfArgs.push_back(charPtrTy);
    sprintfArgs.push_back(charPtrTy);
    sprintfFunc = llvm::Function::Create(
        llvm::FunctionType::get(int32Ty, sprintfArgs, true),
        llvm::Function::ExternalLinkage,
        "sprintf",
        module
    );

    PRYST_DEBUG("String builder functions initialized");
}

llvm::Value* StringBuilder::appendLiteral(const std::string& str) {
    PRYST_DEBUG("Appending literal: " + str);
    auto globalStr = builder->CreateGlobalString(str);
    auto charPtrTy = typeRegistry.getPointerType();
    auto globalStrPtr = builder->CreateBitCast(globalStr, charPtrTy);
    parts.push_back(globalStrPtr);
    return globalStrPtr;
}

llvm::Value* StringBuilder::appendFormatted(llvm::Value* value, const std::string& format) {
    PRYST_DEBUG("Formatting value with format: " + format);

    // Allocate buffer for formatted output
    auto bufferSize = builder->getInt64(64); // Reasonable size for most values
    auto buffer = builder->CreateCall(mallocFunc, {bufferSize});

    // Create format string based on value type and format specifier
    std::string formatStr;
    if (value->getType()->isFloatingPointTy()) {
        if (format.empty()) {
            formatStr = "%.6f"; // Default precision
        } else if (format[0] == '.') {
            int precision = std::stoi(format.substr(1));
            formatStr = "%." + std::to_string(precision) + "f";
        } else {
            formatStr = "%" + format + "f";
        }
    } else if (value->getType()->isIntegerTy()) {
        formatStr = format.empty() ? "%d" : "%" + format + "d";
    } else if (value->getType()->isIntegerTy(1)) { // Boolean
        formatStr = "%s";
        auto trueStr = builder->CreateGlobalString("true");
        auto falseStr = builder->CreateGlobalString("false");
        auto charPtrTy = typeRegistry.getPointerType();
        auto trueStrPtr = builder->CreateBitCast(trueStr, charPtrTy);
        auto falseStrPtr = builder->CreateBitCast(falseStr, charPtrTy);
        value = builder->CreateSelect(value, trueStrPtr, falseStrPtr);
    } else {
        formatStr = "%s";
    }

    // Create format string constant
    auto formatStrGlobal = builder->CreateGlobalString(formatStr);
    auto charPtrTy = typeRegistry.getPointerType();
    auto formatStrPtr = builder->CreateBitCast(formatStrGlobal, charPtrTy);

    // Call sprintf with appropriate arguments
    std::vector<llvm::Value*> args;
    args.push_back(buffer);
    args.push_back(formatStrPtr);
    args.push_back(value);
    builder->CreateCall(sprintfFunc, args);

    parts.push_back(buffer);
    return buffer;
}

llvm::Value* StringBuilder::appendInterpolatedString(
    const std::string& format,
    const std::unordered_map<std::string, llvm::Value*>& values
) {
    PRYST_DEBUG("Processing interpolated string: " + format);

    std::regex pattern("\\{([^:}]+)(?::([^}]+))?\\}");
    std::string::const_iterator searchStart(format.cbegin());
    std::smatch matches;

    while (std::regex_search(searchStart, format.cend(), matches, pattern)) {
        // Add literal text before the placeholder
        std::string literal(searchStart, matches[0].first);
        if (!literal.empty()) {
            appendLiteral(literal);
        }

        // Get variable name and format specifier
        std::string varName = matches[1].str();
        std::string formatSpec = matches[2].str();

        // Find and format the value
        auto it = values.find(varName);
        if (it != values.end()) {
            appendFormatted(it->second, formatSpec);
        } else {
            PRYST_ERROR("Variable not found in interpolation: " + varName);
            appendLiteral("{" + varName + "}");
        }

        searchStart = matches[0].second;
    }

    // Add remaining literal text
    std::string remaining(searchStart, format.cend());
    if (!remaining.empty()) {
        appendLiteral(remaining);
    }

    return build();
}

llvm::Value* StringBuilder::build() {
    PRYST_DEBUG("Building final string");

    if (parts.empty()) {
        auto emptyStr = builder->CreateGlobalString("");
        auto charPtrTy = typeRegistry.getPointerType();
        return builder->CreateBitCast(emptyStr, charPtrTy);
    }

    // Calculate total length needed
    llvm::Value* totalLen = builder->getInt64(1); // Start with 1 for null terminator
    for (auto part : parts) {
        auto len = builder->CreateCall(strlenFunc, {part});
        totalLen = builder->CreateAdd(totalLen, len);
    }

    // Allocate buffer
    auto buffer = builder->CreateCall(mallocFunc, {totalLen});

    // Copy first part
    builder->CreateCall(strcpyFunc, {buffer, parts[0]});

    // Concatenate remaining parts
    for (size_t i = 1; i < parts.size(); i++) {
        builder->CreateCall(strcatFunc, {buffer, parts[i]});
    }

    // Clear parts for next use
    parts.clear();

    return buffer;
}

} // namespace pryst
