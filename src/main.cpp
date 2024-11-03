#include "antlr4-runtime.h"
#include "generated/PrystLexer.h"
#include "generated/PrystParser.h"
#include "generated/PrystBaseVisitor.h"
#include "generated/PrystVisitor.h"
#include "semantic/semantic_analyzer.hpp"
#include "codegen/llvm_codegen.hpp"
#include "jit/jit_compiler.hpp"
#include "aot/aot_compiler.hpp"
#include "diagnostic/diagnostic_visitor.hpp"
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

    // Lexing and Parsing Phase
    std::cout << "\n=== Lexing and Parsing ===\n";
    antlr4::ANTLRInputStream inputStream(input);
    PrystLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    PrystParser parser(&tokens);

    auto programContext = parser.program();
    if (parser.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "Syntax errors detected. Aborting." << std::endl;
        return 1;
    }

    // Parse Tree Output
    std::cout << "\n=== Parse Tree ===\n";
    std::cout << programContext->toStringTree(true) << std::endl;

    try {
        // Diagnostic Phase - Run before semantic analysis to catch structural issues
        std::cout << "\n=== AST Traversal Diagnostic ===\n";
        std::cout << "Tracing AST structure and member access patterns:\n";
        DiagnosticVisitor diagnosticVisitor;
        diagnosticVisitor.visitProgram(programContext);
        std::cout << "Diagnostic traversal completed successfully.\n";

        // Semantic Analysis Phase
        std::cout << "\n=== Semantic Analysis ===\n";
        SemanticAnalyzer semanticAnalyzer;
        semanticAnalyzer.visitProgram(programContext);
        std::cout << "Semantic analysis completed successfully.\n";

        // Code Generation Phase
        std::cout << "\n=== LLVM Code Generation ===\n";
        std::cerr << "DEBUG: About to create LLVMCodegen instance" << std::endl;
        LLVMCodegen codegen;
        std::cerr << "DEBUG: LLVMCodegen instance created successfully" << std::endl;
        std::cerr << "DEBUG: About to call generateModule" << std::endl;
        std::unique_ptr<llvm::Module> module = codegen.generateModule(programContext);
        std::cerr << "DEBUG: generateModule completed successfully" << std::endl;
        std::cout << "Code generation completed successfully.\n";

        // Compilation/Execution Phase
        std::cout << "\n=== Compilation/Execution ===\n";
        if (mode == "--aot") {
            AOTCompiler aot;
            aot.compile(*module, "output.o");
            std::cout << "AOT compilation completed. Output file: output.o" << std::endl;
        } else {
            JITCompiler jit;
            jit.compileAndRun(std::move(module));
            std::cout << "JIT compilation and execution completed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "\nError encountered during compilation:\n";
        std::cerr << "  " << e.what() << std::endl;
        std::cerr << "Compilation aborted.\n";
        return 1;
    }

    return 0;
}
