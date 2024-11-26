#pragma once

#include "../src/type_checker.hpp"

namespace pryst {
namespace testing {

// Test helper class that exposes protected TypeChecker methods for testing
class TestTypeChecker : public TypeChecker {
public:
    TestTypeChecker(llvm::LLVMContext& context, TypeRegistry& typeRegistry, runtime::RuntimeRegistry& runtimeRegistry)
        : TypeChecker(context, typeRegistry, runtimeRegistry) {}

    // Expose protected methods as public
    void testPushScope() { pushScope(); }
    void testPopScope() { popScope(); }
    void testDeclareVariable(const std::string& name, std::any type) {
        declareVariable(name, type);
    }

    // Add any other protected methods that need to be exposed for testing
};

} // namespace testing
} // namespace pryst
