#include "antlr4-runtime.h"
#include "generated/PrystLexer.h"
#include "generated/PrystParser.h"
#include "semantic/semantic_analyzer.hpp"
#include "codegen/llvm_codegen.hpp"
#include "jit/jit_compiler.hpp"
#include "aot/aot_compiler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file> [--jit|--aot]" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string mode = (argc > 2) ? argv[2] : "--jit";  // Default to JIT mode

    std::ifstream input(inputFile);
    if (!input.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }

    antlr4::ANTLRInputStream inputStream(input);
    PrystLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    PrystParser parser(&tokens);

    auto programContext = parser.program();

    SemanticAnalyzer semanticAnalyzer;
    semanticAnalyzer.visitProgram(programContext);

    LLVMCodegen codegen;
    std::unique_ptr<llvm::Module> module = codegen.generateModule(programContext);

    if (mode == "--aot") {
        AOTCompiler aot;
        aot.compile(*module, "output.o");
        std::cout << "AOT compilation completed. Output file: output.o" << std::endl;
    } else {
        JITCompiler jit;
        jit.compileAndRun(std::move(module));
        std::cout << "JIT compilation and execution completed." << std::endl;
    }

    return 0;
}
