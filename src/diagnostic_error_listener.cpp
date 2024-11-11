#include "diagnostic_error_listener.hpp"
#include <iostream>
#include <sstream>

namespace pryst {

void DiagnosticErrorListener::syntaxError(antlr4::Recognizer *recognizer,
                                        antlr4::Token *offendingSymbol,
                                        size_t line,
                                        size_t charPositionInLine,
                                        const std::string &msg,
                                        std::exception_ptr e) {
    auto* parser = static_cast<antlr4::Parser*>(recognizer);
    auto* tokens = parser->getTokenStream();

    std::cerr << "\n=== PARSING ERROR DETAILS ===\n";
    std::cerr << "Location: Line " << line << ", Column " << charPositionInLine << "\n";
    std::cerr << "Message: " << msg << "\n";

    if (offendingSymbol) {
        std::cerr << "Offending symbol: '" << offendingSymbol->getText() << "'\n";
        std::cerr << "Symbol type: " << parser->getVocabulary().getDisplayName(offendingSymbol->getType()) << "\n";
    }

    // Print current rule context
    auto ruleContext = dynamic_cast<antlr4::ParserRuleContext*>(parser->getRuleContext());
    if (ruleContext) {
        std::cerr << "\nRule context stack:\n";
        while (ruleContext != nullptr) {
            std::cerr << "  " << parser->getRuleNames()[ruleContext->getRuleIndex()] << "\n";
            ruleContext = dynamic_cast<antlr4::ParserRuleContext*>(ruleContext->parent);
        }
    }

    // Print expected tokens with descriptions
    auto expectedTokens = parser->getExpectedTokens();
    if (!expectedTokens.isEmpty()) {
        std::cerr << "\nExpected one of:\n";
        for (size_t i = 0; i < expectedTokens.size(); i++) {
            auto tokenType = expectedTokens.get(i);
            std::cerr << "  - " << parser->getVocabulary().getDisplayName(tokenType);
            auto literalName = parser->getVocabulary().getLiteralName(tokenType);
            auto symbolicName = parser->getVocabulary().getSymbolicName(tokenType);
            if (literalName != "") {
                std::cerr << " (literal: " << literalName << ")";
            }
            if (symbolicName != "") {
                std::cerr << " (symbol: " << symbolicName << ")";
            }
            std::cerr << "\n";
        }
    }

    // Print context with improved formatting
    std::cerr << "\nContext:\n";
    size_t start = std::max(0, static_cast<int>(line - 3));
    size_t end = line + 3;
    std::string input = tokens->getTokenSource()->getInputStream()->toString();
    std::istringstream iss(input);
    std::string lineStr;
    size_t currentLine = 1;

    while (std::getline(iss, lineStr) && currentLine <= end) {
        if (currentLine >= start) {
            std::string lineNum = std::to_string(currentLine);
            std::cerr << std::string(4 - lineNum.length(), ' ') << lineNum << " | " << lineStr << "\n";
            if (currentLine == line) {
                std::cerr << "     | " << std::string(charPositionInLine, ' ') << "^\n";
                std::cerr << "     | " << std::string(charPositionInLine, ' ') << "|\n";
                std::cerr << "     | " << std::string(charPositionInLine, ' ') << "Error occurs here\n";
            }
        }
        currentLine++;
    }
    std::cerr << "\n=== END ERROR DETAILS ===\n\n";
}

} // namespace pryst
