#include "string_interpolation.hpp"
#include <cctype>
#include <stdexcept>
#include <unordered_map>

namespace pryst {
namespace codegen {

std::optional<FormatSpecifier> StringInterpolation::parseFormatSpec(const std::string& spec) {
    if (spec.empty() || spec[0] != ':') {
        return std::nullopt;
    }

    FormatSpecifier format;
    size_t pos = 1;

    // Parse alignment and fill
    if (pos < spec.length() && (spec[pos] == '<' || spec[pos] == '>')) {
        format.alignment = spec[pos++];
        if (pos < spec.length() && !std::isdigit(spec[pos])) {
            format.fill = spec[pos++];
        }
    }

    // Parse width
    if (pos < spec.length() && std::isdigit(spec[pos])) {
        size_t width_end;
        format.width = std::stoi(spec.substr(pos), &width_end);
        pos += width_end;
    }

    // Parse precision
    if (pos < spec.length() && spec[pos] == '.') {
        pos++;
        if (pos < spec.length() && std::isdigit(spec[pos])) {
            size_t prec_end;
            format.precision = std::stoi(spec.substr(pos), &prec_end);
            pos += prec_end;
        }
    }

    // Parse type
    if (pos < spec.length()) {
        char type = spec[pos];
        if (type == 'd' || type == 'f' || type == 's' || type == 'b') {
            format.type = type;
        }
    }

    return format;
}

std::string StringInterpolation::processEscapeSequence(const std::string& sequence) {
    static const std::unordered_map<std::string, std::string> escapeMap = {
        {"\\n", "\n"},   // Newline
        {"\\t", "\t"},   // Tab
        {"\\r", "\r"},   // Carriage return
        {"\\\"", "\""},  // Double quote
        {"\\'", "'"},    // Single quote
        {"\\\\", "\\"}, // Backslash
        {"\\b", "\b"},  // Backspace
        {"\\f", "\f"},  // Form feed
        {"\\v", "\v"},  // Vertical tab
        {"\\0", "\0"}   // Null character
    };

    auto it = escapeMap.find(sequence);
    if (it != escapeMap.end()) {
        return it->second;
    }

    // Handle hex escape sequences (\xHH)
    if (sequence.size() == 4 && sequence[0] == '\\' && sequence[1] == 'x') {
        try {
            int value = std::stoi(sequence.substr(2), nullptr, 16);
            return std::string(1, static_cast<char>(value));
        } catch (...) {
            // Return original sequence on error
            return sequence;
        }
    }

    // If no match found, return the sequence as-is
    return sequence;
}

llvm::Value* StringInterpolation::generateFormattedValue(
    llvm::Value* value,
    const FormatSpecifier& format,
    const std::string& originalExpr) {

    if (!value) return nullptr;

    // Determine value type and call appropriate formatting function
    if (value->getType()->isIntegerTy()) {
        return formatInteger(value, format);
    } else if (value->getType()->isFloatingPointTy()) {
        return formatFloat(value, format);
    } else if (value->getType()->isPointerTy()) {
        // Assume string type for pointers
        return formatString(value, format);
    } else if (value->getType()->isIntegerTy(1)) {
        // Boolean type
        return formatBoolean(value, format);
    }

    throw std::runtime_error("Unsupported type in string interpolation: " + originalExpr);
}

llvm::Value* StringInterpolation::formatInteger(llvm::Value* value, const FormatSpecifier& format) {
    auto func = getFormatIntFunction();

    // Convert to i64 if needed
    if (!value->getType()->isIntegerTy(64)) {
        value = builder_.CreateSExt(value, builder_.getInt64Ty());
    }

    std::vector<llvm::Value*> args = {
        value,
        builder_.getInt32(format.width),
        builder_.getInt8(format.fill),
        builder_.getInt1(format.alignment == '<')
    };

    return builder_.CreateCall(func, args);
}

llvm::Value* StringInterpolation::formatFloat(llvm::Value* value, const FormatSpecifier& format) {
    auto func = getFormatFloatFunction();

    // Convert to double if needed
    if (!value->getType()->isDoubleTy()) {
        value = builder_.CreateFPExt(value, builder_.getDoubleTy());
    }

    std::vector<llvm::Value*> args = {
        value,
        builder_.getInt32(format.precision),
        builder_.getInt32(format.width),
        builder_.getInt8(format.fill),
        builder_.getInt1(format.alignment == '<')
    };

    return builder_.CreateCall(func, args);
}

llvm::Value* StringInterpolation::formatBoolean(llvm::Value* value, const FormatSpecifier& format) {
    auto func = getFormatBoolFunction();
    return builder_.CreateCall(func, {value});
}

llvm::Value* StringInterpolation::formatString(llvm::Value* value, const FormatSpecifier& format) {
    auto func = getFormatStringFunction();

    std::vector<llvm::Value*> args = {
        value,
        builder_.getInt32(format.width),
        builder_.getInt8(format.fill),
        builder_.getInt1(format.alignment == '<')
    };

    return builder_.CreateCall(func, args);
}

llvm::Value* StringInterpolation::generateInterpolation(
    const std::string& format,
    const std::vector<llvm::Value*>& values) {

    auto func = getInterpolateStringFunction();

    // Create format string constant
    auto formatStr = builder_.CreateGlobalStringPtr(format);

    std::vector<llvm::Value*> args;
    args.push_back(formatStr);
    args.push_back(builder_.getInt32(values.size()));
    args.insert(args.end(), values.begin(), values.end());

    return builder_.CreateCall(func, args);
}

// Helper functions to get or declare runtime functions
llvm::Function* StringInterpolation::getFormatIntFunction() {
    auto func = module_->getFunction("pryst_format_int");
    if (!func) {
        auto charPtrTy = typeRegistry_->getPointerType(builder_.getInt8Ty());
        std::vector<llvm::Type*> args = {
            builder_.getInt64Ty(),    // value
            builder_.getInt32Ty(),    // width
            builder_.getInt8Ty(),     // fill
            builder_.getInt1Ty()      // leftAlign
        };
        auto funcTy = llvm::FunctionType::get(charPtrTy, args, false);
        func = llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage,
                                    "pryst_format_int", module_);
    }
    return func;
}

llvm::Function* StringInterpolation::getFormatFloatFunction() {
    auto func = module_->getFunction("pryst_format_float");
    if (!func) {
        auto charPtrTy = typeRegistry_->getPointerType(builder_.getInt8Ty());
        std::vector<llvm::Type*> args = {
            builder_.getDoubleTy(),   // value
            builder_.getInt32Ty(),    // precision
            builder_.getInt32Ty(),    // width
            builder_.getInt8Ty(),     // fill
            builder_.getInt1Ty()      // leftAlign
        };
        auto funcTy = llvm::FunctionType::get(charPtrTy, args, false);
        func = llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage,
                                    "pryst_format_float", module_);
    }
    return func;
}

llvm::Function* StringInterpolation::getFormatBoolFunction() {
    auto func = module_->getFunction("pryst_format_bool");
    if (!func) {
        auto charPtrTy = typeRegistry_->getPointerType(builder_.getInt8Ty());
        std::vector<llvm::Type*> args = {builder_.getInt1Ty()};
        auto funcTy = llvm::FunctionType::get(charPtrTy, args, false);
        func = llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage,
                                    "pryst_format_bool", module_);
    }
    return func;
}

llvm::Function* StringInterpolation::getFormatStringFunction() {
    auto func = module_->getFunction("pryst_format_string");
    if (!func) {
        auto charPtrTy = typeRegistry_->getPointerType(builder_.getInt8Ty());
        std::vector<llvm::Type*> args = {
            charPtrTy,               // str
            builder_.getInt32Ty(),   // width
            builder_.getInt8Ty(),    // fill
            builder_.getInt1Ty()     // leftAlign
        };
        auto funcTy = llvm::FunctionType::get(charPtrTy, args, false);
        func = llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage,
                                    "pryst_format_string", module_);
    }
    return func;
}

llvm::Function* StringInterpolation::getInterpolateStringFunction() {
    auto func = module_->getFunction("pryst_interpolate_string");
    if (!func) {
        auto charPtrTy = typeRegistry_->getPointerType(builder_.getInt8Ty());
        std::vector<llvm::Type*> args = {
            charPtrTy,               // format
            builder_.getInt32Ty()    // count
        };
        auto funcTy = llvm::FunctionType::get(charPtrTy, args, true);
        func = llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage,
                                    "pryst_interpolate_string", module_);
    }
    return func;
}

} // namespace codegen
} // namespace pryst
