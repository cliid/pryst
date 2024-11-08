#include "string_interpolation.hpp"
#include <regex>
#include <sstream>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include "string_builder.hpp"
#include "type_utils.hpp"

namespace pryst {
namespace codegen {

StringInterpolation::StringInterpolation(
    llvm::LLVMContext& context,
    llvm::IRBuilder<>& builder,
    TypeRegistry& typeRegistry
) : context(context), builder(builder), typeRegistry(typeRegistry) {}

llvm::Value* StringInterpolation::generateInterpolatedString(
    const std::string& format,
    const std::vector<llvm::Value*>& expressions
) {
    std::vector<std::string> parts = parseInterpolationExpressions(format);
    llvm::Value* result = builder.CreateGlobalString(parts[0]);

    size_t exprIndex = 0;
    for (size_t i = 1; i < parts.size(); i++) {
        if (i % 2 == 1 && exprIndex < expressions.size()) {
            // Convert expression to string
            llvm::Value* exprStr = convertToString(expressions[exprIndex++]);
            // Concatenate with result
            result = concatenateStrings(result, exprStr);
        } else {
            // Concatenate literal part
            llvm::Value* literal = builder.CreateGlobalString(parts[i]);
            result = concatenateStrings(result, literal);
        }
    }

    return result;
}

std::string StringInterpolation::processEscapeSequences(const std::string& input) {
    std::stringstream result;
    bool inEscape = false;

    for (size_t i = 0; i < input.length(); i++) {
        if (inEscape) {
            if (isValidEscapeSequence(input[i])) {
                switch (input[i]) {
                    case 'n': result << '\n'; break;
                    case 't': result << '\t'; break;
                    case 'r': result << '\r'; break;
                    case '\\': result << '\\'; break;
                    case '"': result << '"'; break;
                    case '$': result << '$'; break;
                    default: result << '\\' << input[i];
                }
            } else {
                result << '\\' << input[i];
            }
            inEscape = false;
        } else if (input[i] == '\\') {
            inEscape = true;
        } else {
            result << input[i];
        }
    }

    return result.str();
}

std::vector<std::string> StringInterpolation::parseInterpolationExpressions(
    const std::string& str
) {
    std::vector<std::string> parts;
    std::regex pattern(R"(\$\{([^}]+)\})");
    std::string::const_iterator searchStart(str.cbegin());
    std::smatch match;

    while (std::regex_search(searchStart, str.cend(), match, pattern)) {
        // Add the text before the match
        parts.push_back(std::string(searchStart, match[0].first));
        // Add the expression inside ${}
        parts.push_back(match[1].str());
        searchStart = match[0].second;
    }

    // Add remaining text
    parts.push_back(std::string(searchStart, str.cend()));
    return parts;
}

llvm::Value* StringInterpolation::convertToString(llvm::Value* value) {
    llvm::Type* type = value->getType();
    llvm::Function* convFunc = nullptr;

    if (type->isIntegerTy()) {
        convFunc = getIntToStringFunction();
    } else if (type->isFloatingPointTy()) {
        convFunc = getFloatToStringFunction();
    } else if (type->isIntegerTy(1)) { // boolean
        convFunc = getBoolToStringFunction();
    } else if (typeRegistry.isStringType(type)) {
        return value; // Already a string
    }

    if (convFunc) {
        return builder.CreateCall(convFunc, {value});
    }

    // Default to toString() method if available
    // This handles custom types with toString() implementation
    return builder.CreateCall(getStringConcatFunction(), {value});
}

llvm::Value* StringInterpolation::concatenateStrings(
    llvm::Value* str1,
    llvm::Value* str2
) {
    llvm::Function* concatFunc = getStringConcatFunction();
    return builder.CreateCall(concatFunc, {str1, str2});
}

llvm::Function* StringInterpolation::getStringConcatFunction() {
    llvm::Module* module = builder.GetInsertBlock()->getModule();
    llvm::Function* func = module->getFunction("pryst_string_concat");

    if (!func) {
        // Create function declaration if it doesn't exist
        llvm::Type* strType = typeRegistry.getStringType();
        std::vector<llvm::Type*> paramTypes = {strType, strType};
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            strType, paramTypes, false);
        func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            "pryst_string_concat",
            module
        );
    }

    return func;
}

llvm::Function* StringInterpolation::getIntToStringFunction() {
    llvm::Module* module = builder.GetInsertBlock()->getModule();
    llvm::Function* func = module->getFunction("pryst_int_to_string");

    if (!func) {
        llvm::Type* strType = typeRegistry.getStringType();
        llvm::Type* intType = builder.getInt64Ty();
        std::vector<llvm::Type*> paramTypes = {intType};
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            strType, paramTypes, false);
        func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            "pryst_int_to_string",
            module
        );
    }

    return func;
}

llvm::Function* StringInterpolation::getFloatToStringFunction() {
    llvm::Module* module = builder.GetInsertBlock()->getModule();
    llvm::Function* func = module->getFunction("pryst_float_to_string");

    if (!func) {
        llvm::Type* strType = typeRegistry.getStringType();
        llvm::Type* floatType = builder.getDoubleTy();
        std::vector<llvm::Type*> paramTypes = {floatType};
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            strType, paramTypes, false);
        func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            "pryst_float_to_string",
            module
        );
    }

    return func;
}

llvm::Function* StringInterpolation::getBoolToStringFunction() {
    llvm::Module* module = builder.GetInsertBlock()->getModule();
    llvm::Function* func = module->getFunction("pryst_bool_to_string");

    if (!func) {
        llvm::Type* strType = typeRegistry.getStringType();
        llvm::Type* boolType = builder.getInt1Ty();
        std::vector<llvm::Type*> paramTypes = {boolType};
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            strType, paramTypes, false);
        func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            "pryst_bool_to_string",
            module
        );
    }

    return func;
}

std::string StringInterpolation::extractExpressionFromPlaceholder(
    const std::string& placeholder
) {
    // Remove ${} wrapper and trim whitespace
    size_t start = placeholder.find("${") + 2;
    size_t end = placeholder.find("}");
    std::string expr = placeholder.substr(start, end - start);

    // Trim whitespace
    expr.erase(0, expr.find_first_not_of(" \t\n\r"));
    expr.erase(expr.find_last_not_of(" \t\n\r") + 1);

    return expr;
}

bool StringInterpolation::isValidEscapeSequence(char c) {
    return c == 'n' || c == 't' || c == 'r' || c == '\\' ||
           c == '"' || c == '$';
}

} // namespace codegen
} // namespace pryst
