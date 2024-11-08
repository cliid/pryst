#include <antlr4-runtime.h>
#include "generated/PrystLexer.h"
#include "generated/PrystParser.h"
#include "semantic/semantic_analyzer.hpp"
#include "codegen/llvm_codegen.hpp"
#include "jit/jit_compiler.hpp"
#include "utils/logger.hpp"
#include <llvm/Support/Error.h>
#include <memory>
#include <iostream>
#include <fstream>

using std::string;
using std::unique_ptr;
using std::make_unique;
using std::ifstream;

using llvm::Module;
using llvm::Error;

namespace pryst {
class Logger;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file> [--debug] [--jit]" << std::endl;
        return 1;
    }

    string inputFile = argv[1];
    bool debugMode = false;
    string mode = "aot";  // Default to AOT compilation

    // Parse command line arguments
    for (int i = 2; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--debug") {
            debugMode = true;
        } else if (arg == "--jit") {
            mode = "jit";
        }
    }

    try {
        auto& logger = pryst::Logger::getInstance();
        logger.setDebugEnabled(debugMode);

        // Read input file
        ifstream input(inputFile);
        if (!input.is_open()) {
            PRYST_ERROR("Could not open input file: " + inputFile);
            return 1;
        }

        antlr4::ANTLRInputStream inputStream(input);
        PrystLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        PrystParser parser(&tokens);

        auto* programContext = parser.program();
        if (parser.getNumberOfSyntaxErrors() > 0) {
            PRYST_ERROR("Syntax errors found during parsing");
            return 1;
        }

        // Semantic analysis
        pryst::SemanticAnalyzer semanticAnalyzer;
        semanticAnalyzer.visitProgram(programContext);

        // Code generation
        pryst::LLVMCodegen codegen;
        unique_ptr<Module> module = codegen.generateModule(programContext);

        if (mode == "jit") {
            pryst::JITCompiler jit;
            jit.compileAndRun(std::move(module));
        } else {
            // AOT compilation (to be implemented)
            PRYST_ERROR("AOT compilation not yet implemented");
            return 1;
        }

    } catch (const std::exception& e) {
        PRYST_ERROR(string("Exception: ") + e.what());
        return 1;
    }

    return 0;
}
