#include "diagnostic_error_listener.hpp"
#include <iostream>

namespace pryst {

void DiagnosticErrorListener::syntaxError(
    antlr4::Recognizer *recognizer,
    antlr4::Token *offendingSymbol,
    size_t line,
    size_t charPositionInLine,
    const std::string &msg,
    std::exception_ptr e) {

    std::cerr << "Error at line " << line << ":" << charPositionInLine << " - " << msg << std::endl;
    if (offendingSymbol != nullptr) {
        std::cerr << "Offending symbol: " << offendingSymbol->getText() << std::endl;
    }
}

void DiagnosticErrorListener::reportAmbiguity(
    antlr4::Parser *recognizer,
    const antlr4::dfa::DFA &dfa,
    size_t startIndex,
    size_t stopIndex,
    bool exact,
    const antlrcpp::BitSet &ambigAlts,
    antlr4::atn::ATNConfigSet *configs) {

    std::cerr << "Ambiguity detected between index " << startIndex << " and " << stopIndex << std::endl;
}

} // namespace pryst
