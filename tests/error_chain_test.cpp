#include <gtest/gtest.h>
#include "type_registry.hpp"
#include "error_type.hpp"
#include "error_chain.hpp"
#include "type_checker.hpp"
#include <memory>

using namespace pryst;
using namespace pryst::core;

class ErrorChainTest : public ::testing::Test {
protected:
    llvm::LLVMContext context;
    TypeRegistry typeRegistry{context};
    runtime::RuntimeRegistry runtimeRegistry;
    TypeChecker typeChecker{context, typeRegistry, runtimeRegistry};

    void SetUp() override {
        // Register base Error type
        auto errorType = std::make_shared<ClassType>("Error");
        typeRegistry.cacheType("Error", errorType);
    }
};

TEST_F(ErrorChainTest, ValidateErrorChainCreation) {
    // Create custom error types
    auto customError = std::make_shared<ClassType>("CustomError");
    customError->setParent(typeRegistry.getCachedType("Error"));
    typeRegistry.cacheType("CustomError", customError);

    auto chainedError = std::make_shared<ClassType>("ChainedError");
    chainedError->setParent(typeRegistry.getCachedType("Error"));
    typeRegistry.cacheType("ChainedError", chainedError);

    // Test error chain creation
    EXPECT_NO_THROW(typeRegistry.validateErrorChain("CustomError", "ChainedError"));
    auto chainType = typeRegistry.createErrorChainType("CustomError", "ChainedError");
    EXPECT_TRUE(chainType != nullptr);
    EXPECT_TRUE(typeRegistry.isErrorType(chainType->toString()));
}

TEST_F(ErrorChainTest, DetectCircularDependencies) {
    // Create error types with potential circular dependency
    auto error1 = std::make_shared<ClassType>("Error1");
    error1->setParent(typeRegistry.getCachedType("Error"));
    typeRegistry.cacheType("Error1", error1);

    auto error2 = std::make_shared<ClassType>("Error2");
    error2->setParent(typeRegistry.getCachedType("Error"));
    typeRegistry.cacheType("Error2", error2);

    // Create first chain
    EXPECT_NO_THROW(typeRegistry.validateErrorChain("Error1", "Error2"));
    auto chain1 = typeRegistry.createErrorChainType("Error1", "Error2");

    // Attempt to create circular chain (should throw)
    EXPECT_THROW(typeRegistry.validateErrorChain("Error2", "Error1"), Error);
}

TEST_F(ErrorChainTest, ValidateErrorTypeHierarchy) {
    // Create error type hierarchy
    auto baseError = std::make_shared<ClassType>("BaseError");
    baseError->setParent(typeRegistry.getCachedType("Error"));
    typeRegistry.cacheType("BaseError", baseError);

    auto derivedError = std::make_shared<ClassType>("DerivedError");
    derivedError->setParent(baseError);
    typeRegistry.cacheType("DerivedError", derivedError);

    // Test error type validation
    EXPECT_TRUE(typeRegistry.isErrorType("BaseError"));
    EXPECT_TRUE(typeRegistry.isErrorType("DerivedError"));
    EXPECT_TRUE(typeRegistry.isSubclassOf("DerivedError", "BaseError"));
}
