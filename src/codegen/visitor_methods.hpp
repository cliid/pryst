#pragma once

#include "llvm_codegen.hpp"
#include "../generated/PrystParser.h"

namespace pryst {

// Helper functions for type checking without RTTI
inline bool isClassFunctionDecl(PrystParser::ClassMemberContext* ctx) {
    return ctx->getRuleIndex() == PrystParser::RuleFunctionDecl;
}

inline bool isClassVariableDecl(PrystParser::ClassMemberContext* ctx) {
    return ctx->getRuleIndex() == PrystParser::RuleVariableDecl;
}

} // namespace pryst
