#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <antlr4-runtime.h>
#include "generated/PrystLexer.h"
#include "generated/PrystParser.h"
#include "codegen/llvm_codegen.hpp"
#include "utils/logger.hpp"
#include <llvm/IR/Module.h>

using namespace antlr4;
using namespace llvm;
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input-file> [--debug]" << endl;
        return 1;
    }

    bool debug = false;
    string inputFile;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--debug") {
            debug = true;
        } else {
            inputFile = arg;
        }
    }

    try {
        ifstream stream;
        stream.open(inputFile);

        ANTLRInputStream input(stream);
        PrystLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        PrystParser parser(&tokens);

        auto programContext = parser.program();

        if (parser.getNumberOfSyntaxErrors() > 0) {
            cerr << "Parsing failed." << endl;
            return 1;
        }

        // Create LLVM context and initialize code generator
        LLVMContext context;
        pryst::LLVMCodegen codegen(context);

        // Generate LLVM module
        auto module = codegen.getModule();
        if (!module) {
            cerr << "Failed to generate module." << endl;
            return 1;
        }

        // Visit the parse tree
        codegen.visit(programContext);

        // Output LLVM IR
        module->print(outs(), nullptr);

        return 0;
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
