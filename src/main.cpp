// LLVM headers (order matters)
#include <llvm/Support/Casting.h>
#include <llvm/ADT/Optional.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

// Standard library headers
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <any>

// Project headers
#include "antlr4-runtime.h"
#include "generated/PrystLexer.h"
#include "generated/PrystParser.h"
#include "type_checker.hpp"
#include "llvm_codegen.hpp"
#include "compiler.hpp"
#include "diagnostic_error_listener.hpp"
#include "runtime.hpp"

// Use specific items from namespaces
using antlr4::ANTLRInputStream;
using antlr4::CommonTokenStream;
namespace fs = std::filesystem;

namespace {

void printUsage() {
    std::cout << "Usage: pryst <input.pst> [-o output]\n";
    std::cout << "Options:\n";
    std::cout << "  -o <file>    Specify output file (default: a.out)\n";
}

} // anonymous namespace

int main(int argc, char* argv[]) {
    // Initialize garbage collector first
    pryst::initialize_gc();

    if (argc < 2) {
        printUsage();
        return 1;
    }

    // Parse command line arguments
    std::string inputFile = argv[1];
    std::string outputFile = "a.out";

    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        }
    }

    // Check input file exists
    if (!fs::exists(inputFile)) {
        std::cerr << "Error: Input file '" << inputFile << "' does not exist\n";
        return 1;
    }

    try {
        // Create input stream
        std::ifstream stream;
        stream.open(inputFile);
        ANTLRInputStream input(stream);

        // Create lexer and parser
        pryst::PrystLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        pryst::PrystParser parser(&tokens);

        /*
        // Enable debug mode and token tracing
        tokens.fill(); // Make sure all tokens are loaded
        for (auto token : tokens.getTokens()) {
            std::cerr << "Token: " << token->toString() << "\n";
        }
        parser.setTrace(true);
        */

        // Add diagnostic error listener
        pryst::DiagnosticErrorListener errorListener;
        parser.removeErrorListeners();
        parser.addErrorListener(&errorListener);

        auto tree = parser.program();

        if (parser.getNumberOfSyntaxErrors() > 0) {
            std::cerr << "Syntax errors found. Aborting.\n";
            return 1;
        }

        // Create compiler instance
        pryst::Compiler compiler;

        // Parse and compile
        if (!compiler.compile(tree)) {
            std::cerr << "Compilation failed. Aborting.\n";
            return 1;
        }

        // Generate binary directly
        if (!compiler.compileToObjectFile(outputFile)) {
            std::cerr << "Binary generation failed. Aborting.\n";
            return 1;
        }

        std::cout << "Successfully compiled to " << outputFile << "\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
