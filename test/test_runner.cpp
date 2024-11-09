#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <llvm/Support/raw_ostream.h>
#include "codegen/llvm_codegen.hpp"
#include "codegen/type_registry.hpp"
#include "codegen/type_metadata.hpp"
#include "utils/logger.hpp"
#include "parser/Parser.hpp"
#include "semantic/SemanticAnalyzer.hpp"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>

using namespace pryst;

class TestRunner {
private:
    std::unique_ptr<LLVMCodegen> codegen;
    std::string testFile;

    bool loadTestFile() {
        std::ifstream file(testFile);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open test file: " << testFile << std::endl;
            return false;
        }

        // Read file contents
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();

        try {
            // Parse and execute the test code
            auto ast = Parser::parse(content);
            if (!ast) {
                std::cerr << "Error: Failed to parse test file" << std::endl;
                return false;
            }

            // Perform semantic analysis
            SemanticAnalyzer analyzer;
            if (!analyzer.analyze(ast)) {
                std::cerr << "Error: Semantic analysis failed" << std::endl;
                return false;
            }

            // Generate and execute code
            if (!codegen->generateModule(ast)) {
                std::cerr << "Error: Code generation failed" << std::endl;
                return false;
            }

            // Execute the generated code
            auto engine = codegen->createExecutionEngine();
            if (!engine) {
                std::cerr << "Error: Failed to create execution engine" << std::endl;
                return false;
            }

            // Find and run the main function
            auto mainFn = engine->FindFunctionNamed("main");
            if (!mainFn) {
                std::cerr << "Error: Main function not found" << std::endl;
                return false;
            }

            engine->runFunction(mainFn, {});
            return true;

        } catch (const std::exception& e) {
            std::cerr << "Error during test execution: " << e.what() << std::endl;
            return false;
        }
    }

    void initializeCodegen() {
        codegen = std::make_unique<LLVMCodegen>();
        codegen->initializeModule();
    }

public:
    TestRunner(const std::string& filename) : testFile(filename) {
        Logger::getInstance().setDebugMode(true);
        Logger::getInstance().setLogLevel(LogLevel::Debug);
    }

    ~TestRunner() {
        codegen.reset();
    }

    bool runTest() {
        try {
            std::cout << "Running test: " << testFile << std::endl;

            if (!loadTestFile()) {
                return false;
            }

            initializeCodegen();

            std::cout << "Executing test..." << std::endl;

            return true;
        } catch (const std::exception& e) {
            std::cerr << "Test failed with exception: " << e.what() << std::endl;
            return false;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <test_file>" << std::endl;
        return 1;
    }

    // Initialize LLVM targets
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    // Create test runner and execute test
    try {
        TestRunner runner(argv[1]);
        bool result = runner.runTest();

        // Cleanup LLVM
        llvm::llvm_shutdown();

        return result ? 0 : 1;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        llvm::llvm_shutdown();
        return 1;
    }
}
