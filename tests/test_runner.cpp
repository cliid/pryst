#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <chrono>

// Google Test needs to be included before LLVM to prevent namespace conflicts
#include <gtest/gtest.h>

// LLVM includes with explicit namespace handling
#include <llvm/Support/MemAlloc.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/Error.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/Twine.h>

// Project includes after LLVM
#include "compiler.hpp"
#include "runtime.hpp"
#include <antlr4-runtime.h>
#include "PrystLexer.h"
#include "PrystParser.h"
#include "type_system/advanced/inference/type_inference_advanced.hpp"
#include "type_system/advanced/validation/type_validation.hpp"
#include "error_handling/advanced/chain/error_chain_advanced.hpp"
#include "error_handling/advanced/propagation/error_propagation.hpp"
#include "error_handling/advanced/transformation/error_transform.hpp"

namespace fs = std::filesystem;

// Helper functions for test execution
std::string readTestFile(const fs::path& path) {
    std::ifstream file(path);
    if (!file.is_open() || fs::file_size(path) == 0) {
        throw std::runtime_error("Failed to open or empty test file: " + path.string());
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::unique_ptr<pryst::PrystParser> setupAntlr(const std::string& input) {
    auto input_stream = std::make_unique<antlr4::ANTLRInputStream>(input);
    auto lexer = std::make_unique<pryst::PrystLexer>(input_stream.get());
    auto tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
    return std::make_unique<pryst::PrystParser>(tokens.get());
}

class PrystTest : public ::testing::Test {
protected:
    void SetUp() override {
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();
        pryst::initialize_gc();

        // Initialize advanced type system components
        registry = std::make_shared<pryst::TypeRegistry>();
        typeInference = std::make_shared<pryst::advanced::TypeInference>(registry);
        typeValidation = std::make_shared<pryst::advanced::TypeValidation>(registry);
        errorChain = std::make_shared<pryst::advanced::ErrorChain>();
        errorPropagation = std::make_shared<pryst::advanced::ErrorPropagation>(registry);
        errorTransform = std::make_shared<pryst::advanced::ErrorTransform>(registry);
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::shared_ptr<pryst::advanced::TypeInference> typeInference;
    std::shared_ptr<pryst::advanced::TypeValidation> typeValidation;
    std::shared_ptr<pryst::advanced::ErrorChain> errorChain;
    std::shared_ptr<pryst::advanced::ErrorPropagation> errorPropagation;
    std::shared_ptr<pryst::advanced::ErrorTransform> errorTransform;
};

// Test files are now compiled separately
// No need to include them here as they're linked via CMake

int main(int argc, char** argv) {
    auto total_start_time = std::chrono::high_resolution_clock::now();

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <test_category>\n";
        return 1;
    }

    std::string category = argv[1];
    fs::path test_dir = fs::current_path() / "tests";

    // Run C++ tests first using Google Test
    ::testing::InitGoogleTest(&argc, argv);
    int cpp_test_result = RUN_ALL_TESTS();

    // If only running C++ tests, return the result
    if (category == "cpp_tests") {
        return cpp_test_result;
    }

    std::vector<std::string> valid_categories = {"core_tests", "reflection_tests", "web_tests"};
    if (std::find(valid_categories.begin(), valid_categories.end(), category) == valid_categories.end()) {
        std::cerr << "Invalid test category: " << category << "\n";
        std::cerr << "Valid categories are: ";
        for (const auto& cat : valid_categories) {
            std::cerr << cat << " ";
        }
        std::cerr << "\n";
        return 1;
    }

    if (category == "core_tests") {
        test_dir /= "core";
    } else if (category == "reflection_tests") {
        test_dir /= "reflection";
    } else if (category == "web_tests") {
        test_dir /= "web";
    }

    if (!fs::exists(test_dir) || !fs::is_directory(test_dir)) {
        std::cerr << "Test directory not found: " << test_dir << "\n";
        return 1;
    }

    // Initialize test statistics
    struct TestStats {
        int total = 0;
        int passed = 0;
        std::string category;
        TestStats(std::string cat) : category(cat) {}
    };
    TestStats stats(category);
    bool all_passed = true;
    bool found_tests = false;

    for (const auto& entry : fs::directory_iterator(test_dir)) {
        if (entry.path().extension() != ".pst") continue;

        std::cout << "\n=== Running test: " << entry.path().filename().string() << " ===\n";
        auto start_time = std::chrono::high_resolution_clock::now();

        try {
            std::string input = readTestFile(entry.path());
            auto parser = setupAntlr(input);
            auto tree = parser->program();

            // Parse and compile
            auto compiler = std::make_unique<pryst::Compiler>();
            if (compiler->compile(tree)) {
                auto& registry = compiler->getRuntimeRegistry();
                registry.registerBuiltins();
                registry.registerWebTypes();

                // Execute using JIT - create a copy of the module since compiler owns it
                std::unique_ptr<llvm::Module> moduleCopy(llvm::CloneModule(compiler->getModule()));
                std::string errStr;
                std::unique_ptr<llvm::ExecutionEngine> engine(
                    llvm::EngineBuilder(std::move(moduleCopy))
                        .setErrorStr(&errStr)
                        .setEngineKind(llvm::EngineKind::JIT)
                        .setOptLevel(llvm::CodeGenOpt::None)
                        .create()
                );

                if (!engine) {
                    throw std::runtime_error("Failed to create execution engine: " + errStr);
                }

                llvm::Function* mainFn = engine->FindFunctionNamed("main");
                if (!mainFn) {
                    throw std::runtime_error("No main function found");
                }

                auto exec_start = std::chrono::high_resolution_clock::now();
                engine->runFunction(mainFn, std::vector<llvm::GenericValue>());
                auto exec_end = std::chrono::high_resolution_clock::now();

                auto exec_duration = std::chrono::duration_cast<std::chrono::milliseconds>(exec_end - exec_start);
                auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(exec_end - start_time);

                std::cout << "Test execution time: " << exec_duration.count() << "ms\n";
                std::cout << "Total test time (including compilation): " << total_duration.count() << "ms\n";
                std::cout << "Test passed successfully\n";
                stats.passed++;
            } else {
                throw std::runtime_error("Compilation failed for " + entry.path().filename().string());
            }
        } catch (const std::exception& e) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            std::ofstream error_log("test_errors.log", std::ios::app);
            error_log << "=== Test Failed: " << entry.path().filename().string() << " ===\n";
            error_log << "Error: " << e.what() << "\n\n";
            std::cerr << "Test failed: " << e.what() << "\n";
            std::cerr << "File: " << entry.path().filename().string() << "\n";
            std::cerr << "Duration: " << duration.count() << "ms\n\n";
            all_passed = false;
        }
        stats.total++;
    }

    auto total_end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::seconds>(total_end_time - total_start_time);

    std::cout << "\n=== Test Summary for " << stats.category << " ===\n";
    std::cout << "Total Tests: " << stats.total << "\n";
    std::cout << "Passed: " << stats.passed << "\n";
    std::cout << "Failed: " << (stats.total - stats.passed) << "\n";
    std::cout << "Total Duration: " << total_duration.count() << " seconds\n";
    std::cout << "Result: " << (all_passed ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << "\n\n";

    return (all_passed && cpp_test_result == 0) ? 0 : 1;
}
