#include "string_interpolation.hpp"
#include <sstream>
#include <regex>

namespace pryst {

void StringInterpolation::initializeStringFunctions() {
    auto i8PtrTy = typeRegistry.getPointerType("i8");
    auto i32Ty = typeRegistry.getIntType();
    auto voidTy = typeRegistry.getVoidType();

    // strlen(char*)
    if (!strlenFunc) {
        std::vector<llvm::Type*> strlenParams = {i8PtrTy};
        auto strlenType = llvm::FunctionType::get(i32Ty, strlenParams, false);
        strlenFunc = llvm::Function::Create(strlenType, llvm::Function::ExternalLinkage, "strlen", module);
    }

    // strcat(char*, const char*)
    if (!strcatFunc) {
        std::vector<llvm::Type*> strcatParams = {i8PtrTy, i8PtrTy};
        auto strcatType = llvm::FunctionType::get(i8PtrTy, strcatParams, false);
        strcatFunc = llvm::Function::Create(strcatType, llvm::Function::ExternalLinkage, "strcat", module);
    }

    // strcpy(char*, const char*)
    if (!strcpyFunc) {
        std::vector<llvm::Type*> strcpyParams = {i8PtrTy, i8PtrTy};
        auto strcpyType = llvm::FunctionType::get(i8PtrTy, strcpyParams, false);
        strcpyFunc = llvm::Function::Create(strcpyType, llvm::Function::ExternalLinkage, "strcpy", module);
    }

    // malloc(size_t)
    if (!mallocFunc) {
        std::vector<llvm::Type*> mallocParams = {i32Ty};
        auto mallocType = llvm::FunctionType::get(i8PtrTy, mallocParams, false);
        mallocFunc = llvm::Function::Create(mallocType, llvm::Function::ExternalLinkage, "malloc", module);
    }

    // free(void*)
    if (!freeFunc) {
        std::vector<llvm::Type*> freeParams = {i8PtrTy};
        auto freeType = llvm::FunctionType::get(voidTy, freeParams, false);
        freeFunc = llvm::Function::Create(freeType, llvm::Function::ExternalLinkage, "free", module);
    }

    // sprintf(char*, const char*, ...)
    if (!sprintfFunc) {
        std::vector<llvm::Type*> sprintfParams = {i8PtrTy, i8PtrTy};
        auto sprintfType = llvm::FunctionType::get(i32Ty, sprintfParams, true);
        sprintfFunc = llvm::Function::Create(sprintfType, llvm::Function::ExternalLinkage, "sprintf", module);
    }
}

FormatSpecifier StringInterpolation::parseFormatSpec(const std::string& spec) {
    FormatSpecifier result;
    if (spec.empty()) return result;

    std::regex formatRegex(R"(([<>])?(\d+)?(?:\.(\d+))?([dfs])?)", std::regex::ECMAScript);
    std::smatch match;

    if (std::regex_match(spec, match, formatRegex)) {
        // Alignment
        if (match[1].matched) {
            result.leftAlign = (match[1].str() == "<");
        }

        // Width
        if (match[2].matched) {
            result.width = std::stoi(match[2].str());
        }

        // Precision
        if (match[3].matched) {
            result.precision = std::stoi(match[3].str());
        }

        // Type
        if (match[4].matched) {
            result.type = match[4].str()[0];
        }
    }

    return result;
}

llvm::Value* StringInterpolation::formatValue(llvm::Value* value, const FormatSpecifier& spec) {
    if (!value) {
        PRYST_ERROR("Null value passed to formatValue");
        return nullptr;
    }

    auto valueType = value->getType();
    if (valueType->isIntegerTy()) {
        return formatInt(value, spec);
    } else if (valueType->isFloatTy()) {
        return formatFloat(value, spec);
    } else if (valueType->isPointerTy()) {
        return formatString(value, spec);
    } else {
        PRYST_ERROR("Unsupported type for string interpolation");
        return nullptr;
    }
}

llvm::Value* StringInterpolation::formatInt(llvm::Value* value, const FormatSpecifier& spec) {
    // Allocate buffer for the formatted string
    auto buffer = allocateBuffer(32);  // Reasonable size for int formatting

    // Create format string based on specifier
    std::string format = "%";
    if (spec.leftAlign) format += "-";
    if (spec.width > 0) format += std::to_string(spec.width);
    format += spec.type ? spec.type : 'd';

    // Create format string constant
    auto formatStr = builder->CreateGlobalStringPtr(format);

    // Call sprintf
    std::vector<llvm::Value*> args = {buffer, formatStr, value};
    builder->CreateCall(sprintfFunc, args);

    return buffer;
}

llvm::Value* StringInterpolation::formatFloat(llvm::Value* value, const FormatSpecifier& spec) {
    auto buffer = allocateBuffer(64);  // Larger buffer for float formatting

    std::string format = "%";
    if (spec.leftAlign) format += "-";
    if (spec.width > 0) format += std::to_string(spec.width);
    if (spec.precision >= 0) {
        format += "." + std::to_string(spec.precision);
    }
    format += spec.type ? spec.type : 'f';

    auto formatStr = builder->CreateGlobalStringPtr(format);
    std::vector<llvm::Value*> args = {buffer, formatStr, value};
    builder->CreateCall(sprintfFunc, args);

    return buffer;
}

llvm::Value* StringInterpolation::formatString(llvm::Value* value, const FormatSpecifier& spec) {
    if (!spec.width) return value;  // No formatting needed

    auto buffer = allocateBuffer(spec.width + 1);
    auto formatStr = builder->CreateGlobalStringPtr("%-*s");

    std::vector<llvm::Value*> args = {
        buffer,
        formatStr,
        builder->getInt32(spec.width),
        value
    };
    builder->CreateCall(sprintfFunc, args);

    return buffer;
}

llvm::Value* StringInterpolation::interpolate(const std::string& format,
                                            const std::vector<llvm::Value*>& values,
                                            const std::vector<FormatSpecifier>& specs) {
    if (values.empty()) {
        return builder->CreateGlobalStringPtr(format);
    }

    // Parse format string and find interpolation points
    std::vector<std::string> parts;
    std::vector<size_t> valueIndices;

    size_t pos = 0;
    size_t valueIndex = 0;

    while (pos < format.length()) {
        size_t openBrace = format.find('{', pos);
        if (openBrace == std::string::npos) {
            parts.push_back(format.substr(pos));
            break;
        }

        parts.push_back(format.substr(pos, openBrace - pos));
        size_t closeBrace = format.find('}', openBrace);
        if (closeBrace == std::string::npos) {
            PRYST_ERROR("Unclosed brace in format string");
            return nullptr;
        }

        valueIndices.push_back(valueIndex++);
        pos = closeBrace + 1;
    }

    // Allocate buffer for result
    size_t totalSize = format.length() + 256;  // Base size plus extra space
    auto buffer = allocateBuffer(totalSize);

    // Copy first part
    if (!parts.empty()) {
        auto firstPart = builder->CreateGlobalStringPtr(parts[0]);
        builder->CreateCall(strcpyFunc, {buffer, firstPart});
    }

    // Interpolate values
    for (size_t i = 0; i < valueIndices.size(); ++i) {
        auto value = values[valueIndices[i]];
        auto spec = i < specs.size() ? specs[i] : FormatSpecifier();

        // Format the value
        auto formattedValue = formatValue(value, spec);
        if (!formattedValue) continue;

        // Concatenate the formatted value
        builder->CreateCall(strcatFunc, {buffer, formattedValue});

        // Add the next literal part if it exists
        if (i + 1 < parts.size()) {
            auto nextPart = builder->CreateGlobalStringPtr(parts[i + 1]);
            builder->CreateCall(strcatFunc, {buffer, nextPart});
        }
    }

    return buffer;
}

llvm::Value* StringInterpolation::allocateBuffer(size_t size) {
    return builder->CreateCall(mallocFunc, {builder->getInt32(size)});
}

llvm::Value* StringInterpolation::getStringLength(llvm::Value* str) {
    return builder->CreateCall(strlenFunc, {str});
}

llvm::Value* StringInterpolation::concatenateStrings(llvm::Value* str1, llvm::Value* str2) {
    return builder->CreateCall(strcatFunc, {str1, str2});
}

} // namespace pryst
