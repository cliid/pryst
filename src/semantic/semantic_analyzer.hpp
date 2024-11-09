#pragma once

#include <any>
#include <memory>
#include "semantic/symbol_table.hpp"
#include "semantic/module_loader.hpp"
#include "generated/PrystBaseVisitor.h"
#include "generated/PrystParser.h"
#include "utils/error_handling.hpp"

namespace pryst {

class SemanticAnalyzer : public PrystBaseVisitor {
public:
    SemanticAnalyzer();
    virtual ~SemanticAnalyzer() = default;

    virtual std::any visitProgram(PrystParser::ProgramContext *ctx) override;
    virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) override;
    virtual std::any visitForwardDecl(PrystParser::ForwardDeclContext *ctx) override;
    virtual std::any visitImportDecl(PrystParser::ImportDeclContext *ctx) override;

private:
    SymbolTable symbolTable;
    semantic::ModuleLoader moduleLoader;
};

} // namespace pryst
