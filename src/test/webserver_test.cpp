#include <iostream>
#include <fstream>
#include <any>
#include "antlr4-runtime.h"
#include "generated/PrystLexer.h"
#include "generated/PrystParser.h"
#include "generated/PrystParserBaseVisitor.h"
#include "generated/PrystParserVisitor.h"
#include "type_checker.hpp"
#include "type_registry.hpp"
#include "llvm_codegen.hpp"
#include "compiler.hpp"
#include "diagnostic_error_listener.hpp"

using namespace antlr4;
using namespace pryst;

int main() {
    std::ifstream stream;
    stream.open("test/webserver_test.pst");  // Update path to match CMake's copy location
    if (!stream.is_open()) {
        std::cerr << "Failed to open test/webserver_test.pst" << std::endl;
        return 1;
    }

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

    try {
        std::cout << "Testing web server implementation..." << std::endl;
        auto tree = parser.program();

        if (parser.getNumberOfSyntaxErrors() > 0) {
            std::cerr << "Syntax errors found in web server test" << std::endl;
            return 1;
        }

        // Type checking
        pryst::TypeChecker typeChecker;
        typeChecker.visit(tree);
        // Type checking errors would have thrown exceptions

        // Initialize type registry
        pryst::TypeRegistry typeRegistry;

        // Code generation
        pryst::Compiler compiler;
        pryst::LLVMCodeGen codegen(compiler.getContext(), compiler.getModule(), compiler.getBuilder(), typeRegistry);
        codegen.visit(tree);
        // Code generation errors would have thrown exceptions

        std::cout << "Web server implementation test passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
