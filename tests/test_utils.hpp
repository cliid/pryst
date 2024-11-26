#pragma once

#include <antlr4-runtime.h>
#include "../src/generated/PrystLexer.h"
#include "../src/generated/PrystParser.h"
#include "../src/error.hpp"
#include "../src/compiler.hpp"
#include "../src/type_checker.hpp"
#include "../src/runtime/runtime_registry.hpp"
#include "test_type_checker.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace pryst {
namespace testing {

inline antlr4::tree::ParseTree* parseCode(const char* code) {
    antlr4::ANTLRInputStream input(code);
    PrystLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    PrystParser parser(&tokens);

    // Configure error handling
    parser.removeErrorListeners();
    parser.addErrorListener(new antlr4::DiagnosticErrorListener());

    // Parse the input
    auto tree = parser.program();

    if (parser.getNumberOfSyntaxErrors() > 0) {
        throw Error("SyntaxError", "Failed to parse test code");
    }

    return tree;
}

// Test fixture base class that handles compilation and type checking
class PrystTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<TypeRegistry> typeRegistry;
    std::unique_ptr<runtime::RuntimeRegistry> runtimeRegistry;
    std::unique_ptr<Compiler> compiler;

    void SetUp() override {
        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>("test_module", *context);
        typeRegistry = std::make_unique<TypeRegistry>(*context);
        runtimeRegistry = std::make_unique<runtime::RuntimeRegistry>(module.get());
        compiler = std::make_unique<Compiler>();
        auto testChecker = std::make_unique<testing::TestTypeChecker>(*context, *typeRegistry, *runtimeRegistry);
        compiler->setTypeChecker(std::move(testChecker));
    }

    void TearDown() override {
        compiler.reset();
        runtimeRegistry.reset();
        typeRegistry.reset();
        module.reset();
        context.reset();
    }

    bool compileCode(const std::string& code) {
        auto tree = parseCode(code.c_str());
        return compiler->compile(tree);
    }

    TypeRegistry& getRegistry() {
        return *typeRegistry;
    }
};

} // namespace testing
} // namespace pryst
