#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "semantic/semantic_analyzer.hpp"
#include "codegen/llvm_codegen.hpp"
#include "jit/jit_compiler.hpp"
#include "aot/aot_compiler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << input_file.rdbuf();
    std::string source = buffer.str();

    Lexer lexer(source);
    std::vector<Token> tokens = lexer.scanTokens();

    Parser parser(tokens);
    std::unique_ptr<Program> ast = parser.parse();

    SemanticAnalyzer semanticAnalyzer;
    semanticAnalyzer.analyze(*ast);

    LLVMCodegen codegen;
    std::unique_ptr<llvm::Module> module = codegen.generateModule(*ast);

    // Choose between JIT and AOT compilation
    bool useJIT = true;  // This could be a command-line option
    if (useJIT) {
        JITCompiler jit;
        jit.compileAndRun(std::move(module));
    } else {
        AOTCompiler aot;
        aot.compile(*module, "output.o");
    }

    return 0;
}
