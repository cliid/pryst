#include "llvm_codegen.hpp"
#include "string_interpolation.hpp"
#include "../utils/logger.hpp"
#include <regex>

namespace pryst {

std::any LLVMCodegen::visitStringLiteral(PrystParser::StringLiteralContext *ctx) {
    if (!ctx) return nullptr;

    // Initialize string interpolation if needed
    if (!stringInterpolation) {
        stringInterpolation = std::make_unique<StringInterpolation>(
            *context, builder.get(), module.get(), typeRegistry);
    }

    // Collect string parts and expressions
    std::vector<llvm::Value*> values;
    std::vector<FormatSpecifier> specs;
    std::string formatString;

    for (auto part : ctx->stringPart()) {
        if (auto text = part->StringText()) {
            // Handle literal text
            std::string content = text->getText();
            // Remove quotes and unescape
            content = content.substr(1, content.length() - 2);
            formatString += content;
        } else if (auto interp = part->StringInterp()) {
            // Handle interpolation
            std::string interpText = interp->getText();
            // Extract expression and format specifier
            std::regex interpRegex(R"(\{([^:}]+)(?::([^}]+))?\})");
            std::smatch match;
            if (std::regex_match(interpText, match, interpRegex)) {
                formatString += "{}";  // Placeholder for the value

                // Visit the expression
                if (auto expr = part->expression()) {
                    auto result = std::any_cast<llvm::Value*>(visit(expr));
                    if (!result) {
                        PRYST_ERROR("Failed to evaluate interpolated expression");
                        continue;
                    }
                    values.push_back(result);
                }

                // Parse format specifier if present
                if (match[2].matched) {
                    specs.push_back(StringInterpolation::parseFormatSpec(match[2].str()));
                } else {
                    specs.push_back(FormatSpecifier{});  // Default format
                }
            }
        }
    }

    // If no interpolation, return simple string literal
    if (values.empty()) {
        return builder->CreateGlobalStringPtr(formatString);
    }

    // Perform string interpolation
    return stringInterpolation->interpolate(formatString, values, specs);
}

std::any LLVMCodegen::visitStringPart(PrystParser::StringPartContext *ctx) {
    if (!ctx) return nullptr;

    if (auto text = ctx->StringText()) {
        std::string content = text->getText();
        // Remove quotes and unescape
        content = content.substr(1, content.length() - 2);
        return builder->CreateGlobalStringPtr(content);
    } else if (auto interp = ctx->StringInterp()) {
        if (auto expr = ctx->expression()) {
            return visit(expr);
        }
    }

    return nullptr;
}

} // namespace pryst
