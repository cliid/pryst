#include "../src/semantic/module_loader.hpp"
#include "../src/semantic/symbol_table.hpp"
#include "../src/utils/logger.hpp"
#include <memory>
#include <iostream>
#include <filesystem>

void runModuleTests() {
    // Initialize components
    auto symbolTable = std::make_shared<SymbolTable>();
    auto moduleLoader = std::make_shared<ModuleLoader>(symbolTable);

    try {
        // Add test directory to module search paths
        moduleLoader->addModuleSearchPath("test/modules");

        std::cout << "=== Running Module System Tests ===\n";

        // Test 1: Load test module
        std::cout << "\nTest 1: Loading test::web module...\n";
        auto webModule = moduleLoader->loadModule("test::web");
        std::cout << "✓ Successfully loaded test::web module\n";

        // Test 2: Verify exports
        std::cout << "\nTest 2: Verifying module exports...\n";
        auto exports = moduleLoader->getModuleExports("test::web");
        if (exports.find("SERVER_NAME") != exports.end() &&
            exports.find("MAX_CONNECTIONS") != exports.end()) {
            std::cout << "✓ Found expected exports\n";
        } else {
            throw std::runtime_error("Missing expected exports");
        }

        // Test 3: Load and verify client module
        std::cout << "\nTest 3: Loading test::client module...\n";
        auto clientModule = moduleLoader->loadModule("test::client");
        std::cout << "✓ Successfully loaded test::client module\n";

        // Test 4: Verify function exports
        std::cout << "\nTest 4: Verifying function exports...\n";
        auto functions = moduleLoader->getModuleExportedFunctions("test::client");
        if (functions.find("test_imports") != functions.end() &&
            functions.find("test_block_scope") != functions.end()) {
            std::cout << "✓ Found expected function exports\n";
        } else {
            throw std::runtime_error("Missing expected function exports");
        }

        std::cout << "\n=== All Module System Tests Passed ===\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        throw;
    }
}

int main() {
    try {
        runModuleTests();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Tests failed: " << e.what() << std::endl;
        return 1;
    }
}
