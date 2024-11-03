#ifndef PRYST_ANTLR_RTTI_HPP
#define PRYST_ANTLR_RTTI_HPP

#include "PrystParser.h"
#include <string>
#include <typeinfo>
#include <memory>

namespace pryst {

class AntlrRTTI {
public:
    // Get type name for a parser context
    static std::string getContextTypeName(antlr4::ParserRuleContext* ctx) {
        if (!ctx) return "null";
        return typeid(*ctx).name();
    }

    // Check if a context is of a specific type
    template<typename T>
    static bool isContextType(antlr4::ParserRuleContext* ctx) {
        if (!ctx) return false;
        return dynamic_cast<T*>(ctx) != nullptr;
    }

    // Get base type for a context
    static std::string getBaseTypeName(antlr4::ParserRuleContext* ctx) {
        if (!ctx) return "null";
        return "antlr4::ParserRuleContext";
    }

    // Convert context to specific type
    template<typename T>
    static T* contextAs(antlr4::ParserRuleContext* ctx) {
        return dynamic_cast<T*>(ctx);
    }
};

} // namespace pryst

#endif // PRYST_ANTLR_RTTI_HPP
