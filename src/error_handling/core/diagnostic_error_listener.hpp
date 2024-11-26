#pragma once

#include <antlr4-runtime.h>
#include <string>
#include <exception>

namespace pryst {
namespace core {

class DiagnosticErrorListener : public antlr4::BaseErrorListener {
public:
    DiagnosticErrorListener() = default;
    ~DiagnosticErrorListener() override = default;

    void syntaxError(
        antlr4::Recognizer *recognizer,
        antlr4::Token *offendingSymbol,
        size_t line,
        size_t charPositionInLine,
        const std::string &msg,
        std::exception_ptr e) override;

    void reportAmbiguity(
        antlr4::Parser *recognizer,
        const antlr4::dfa::DFA &dfa,
        size_t startIndex,
        size_t stopIndex,
        bool exact,
        const antlrcpp::BitSet &ambigAlts,
        antlr4::atn::ATNConfigSet *configs) override;
};

} // namespace core
} // namespace pryst
