#include "string_builder.hpp"
#include "string_utils.hpp"
#include <vector>
#include <regex>

namespace pryst {

void StringBuilder::initializeStringFunctions() {
    auto& typeRegistry = codegen->getTypeRegistry();
    auto charPtrTy = typeRegistry.getPointerType();
    auto context = codegen->getContext();
    auto module = codegen->getModule();

    // Initialize string manipulation functions
    strlenFunc = string_utils::declareStrlen(codegen);
    strcatFunc = string_utils::declareStrcat(codegen);
    strcpyFunc = string_utils::declareStrcpy(codegen);

    // Declare malloc and free
    std::vector<llvm::Type*> mallocArgs = {llvm::Type::getInt64Ty(*context)};
    auto mallocType = llvm::FunctionType::get(charPtrTy, mallocArgs, false);
    mallocFunc = llvm::Function::Create(mallocType, llvm::Function::ExternalLinkage, "malloc", module);

    std::vector<llvm::Type*> freeArgs = {charPtrTy};
    auto freeType = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), freeArgs, false);
    freeFunc = llvm::Function::Create(freeType, llvm::Function::ExternalLinkage, "free", module);

    // Declare sprintf
    std::vector<llvm::Type*> sprintfArgs = {charPtrTy, charPtrTy};
    auto sprintfType = llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), sprintfArgs, true);
    sprintfFunc = llvm::Function::Create(sprintfType, llvm::Function::ExternalLinkage, "sprintf", module);
}

llvm::Value* StringBuilder::appendLiteral(const std::string& str) {
    auto& typeRegistry = codegen->getTypeRegistry();
    auto charPtrTy = typeRegistry.getPointerType();
    auto builder = codegen->getBuilder();

    // Create global string constant
    auto globalStr = builder->CreateGlobalString(str);

    // Allocate buffer for the string
    auto size = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), str.length() + 1);
    auto buffer = builder->CreateCall(mallocFunc, {size});

    // Copy string to buffer
    builder->CreateCall(strcpyFunc, {buffer, globalStr});

    parts.push_back(buffer);
    return buffer;
}

llvm::Value* StringBuilder::appendFormatted(llvm::Value* value, const std::string& format) {
    if (!value) {
        // Handle null value case
        auto& typeRegistry = codegen->getTypeRegistry();
        auto charPtrTy = typeRegistry.getPointerType();
        auto builder = codegen->getBuilder();
        auto nullStr = builder->CreateGlobalString("null");
        auto size = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 5); // "null\0"
        auto buffer = builder->CreateCall(mallocFunc, {size});
        builder->CreateCall(strcpyFunc, {buffer, nullStr});
        parts.push_back(buffer);
        return buffer;
    }

    auto& typeRegistry = codegen->getTypeRegistry();
    auto charPtrTy = typeRegistry.getPointerType();
    auto builder = codegen->getBuilder();

    // Allocate buffer for the formatted string
    auto bufferSize = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 64);
    auto buffer = builder->CreateCall(mallocFunc, {bufferSize});

    // Create format string
    std::string formatStr = format.empty() ? "%s" : format;
    auto globalFormat = builder->CreateGlobalString(formatStr);

    // Format the value into the buffer
    std::vector<llvm::Value*> args = {buffer, globalFormat, value};
    builder->CreateCall(sprintfFunc, args);

    parts.push_back(buffer);
    return buffer;
}

llvm::Value* StringBuilder::appendInterpolatedString(
    const std::string& format,
    const std::unordered_map<std::string, llvm::Value*>& values
) {
    std::regex pattern("\\{([^:}]+)(?::([^}]+))?\\}");
    std::string::const_iterator searchStart(format.cbegin());
    std::smatch matches;
    std::string::const_iterator lastEnd = format.cbegin();

    while (std::regex_search(searchStart, format.cend(), matches, pattern)) {
        // Append literal text before the match
        std::string literal(lastEnd, matches[0].first);
        if (!literal.empty()) {
            appendLiteral(literal);
        }

        // Get variable name and format specifier
        std::string varName = matches[1].str();
        std::string formatSpec = matches[2].matched ? matches[2].str() : "";

        // Look up and append the variable value
        auto it = values.find(varName);
        if (it != values.end()) {
            appendFormatted(it->second, formatSpec);
        } else {
            appendLiteral("{" + varName + "}");
        }

        // Update search position
        lastEnd = matches[0].second;
        searchStart = matches[0].second;
    }

    // Append any remaining literal text
    std::string remaining(lastEnd, format.cend());
    if (!remaining.empty()) {
        appendLiteral(remaining);
    }

    return build();
}

llvm::Value* StringBuilder::build() {
    if (parts.empty()) {
        // Return empty string if no parts
        auto& typeRegistry = codegen->getTypeRegistry();
        auto charPtrTy = typeRegistry.getPointerType();
        auto builder = codegen->getBuilder();
        auto emptyStr = builder->CreateGlobalString("");
        auto size = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 1);
        auto buffer = builder->CreateCall(mallocFunc, {size});
        builder->CreateCall(strcpyFunc, {buffer, emptyStr});
        return buffer;
    }

    // Calculate total length
    llvm::Value* totalLen = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 1); // for null terminator
    auto builder = codegen->getBuilder();

    for (auto part : parts) {
        auto len = builder->CreateCall(strlenFunc, {part});
        totalLen = builder->CreateAdd(totalLen, len);
    }

    // Allocate final buffer
    auto buffer = builder->CreateCall(mallocFunc, {totalLen});

    // Copy first part
    builder->CreateCall(strcpyFunc, {buffer, parts[0]});

    // Concatenate remaining parts
    for (size_t i = 1; i < parts.size(); ++i) {
        builder->CreateCall(strcatFunc, {buffer, parts[i]});
    }

    // Free intermediate buffers
    for (auto part : parts) {
        builder->CreateCall(freeFunc, {part});
    }

    parts.clear();
    return buffer;
}

} // namespace pryst
