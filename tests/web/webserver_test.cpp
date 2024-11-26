#include <iostream>
#include <fstream>
#include <any>
#include <antlr4-runtime.h>
#include "PrystLexer.h"
#include "PrystParser.h"
#include "PrystParserBaseVisitor.h"
#include "PrystParserVisitor.h"
#include "type_checker.hpp"
#include "type_registry.hpp"
#include "llvm_codegen.hpp"
#include "compiler.hpp"
#include "diagnostic_error_listener.hpp"
#include <gtest/gtest.h>

using namespace antlr4;
using namespace pryst;

class WebServerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Any common setup code can go here
    }

    void TearDown() override {
        // Any common cleanup code can go here
    }
};

TEST_F(WebServerTest, TestWebServerImplementation) {
    std::ifstream stream;
    stream.open("test/webserver_test.pst");
    ASSERT_TRUE(stream.is_open()) << "Failed to open test/webserver_test.pst";

    ANTLRInputStream input(stream);
    PrystLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    // Enable debug mode and token tracing
    tokens.fill(); // Make sure all tokens are loaded
    for (auto token : tokens.getTokens()) {
        std::cerr << "Token: " << token->toString() << "\n";
    }

    pryst::PrystParser parser(&tokens);
    parser.setTrace(true);

    // Add diagnostic error listener
    pryst::DiagnosticErrorListener errorListener;
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    std::cout << "Testing web server implementation..." << std::endl;
    auto tree = parser.program();

    ASSERT_EQ(0, parser.getNumberOfSyntaxErrors()) << "Syntax errors found in web server test";

    // Create compiler instance first to get context and registry
    pryst::Compiler compiler;

    // Type checking with compiler's context and registry
    pryst::TypeChecker typeChecker(compiler.getContext(), compiler.getRegistry(), compiler.getRuntimeRegistry());
    ASSERT_NO_THROW(typeChecker.visit(tree)) << "Type checking failed";

    // Code generation
    pryst::LLVMCodeGen codegen(compiler.getContext(), compiler.getModule(), compiler.getBuilder(), compiler.getRegistry());
    ASSERT_NO_THROW(codegen.visit(tree)) << "Code generation failed";

    std::cout << "Web server implementation test passed!" << std::endl;
}
