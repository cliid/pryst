#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class ErrorChainTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<pryst::TypeRegistry>();
        registry->registerType("IOException", std::make_shared<pryst::ErrorType>("IOException"));
        registry->registerType("NetworkError", std::make_shared<pryst::ErrorType>("NetworkError"));
        registry->registerType("DatabaseError", std::make_shared<pryst::ErrorType>("DatabaseError"));
        registry->registerType("ValidationError", std::make_shared<pryst::ErrorType>("ValidationError"));
        checker = std::make_unique<pryst::TypeChecker>(registry);
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::unique_ptr<pryst::TypeChecker> checker;
};

TEST_F(ErrorChainTest, NestedTryCatchBlocks) {
    auto ioError = registry->getType("IOException");
    auto netError = registry->getType("NetworkError");
    auto dbError = registry->getType("DatabaseError");

    // Test nested try-catch with multiple error types
    auto result = checker->checkNestedErrorHandling({ioError, netError}, {dbError});
    EXPECT_FALSE(result->isError());

    // Test error propagation through nested blocks
    result = checker->checkErrorPropagation(ioError, {netError, dbError});
    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "IOException");
}

TEST_F(ErrorChainTest, ErrorPropagationInScopes) {
    auto ioError = registry->getType("IOException");
    auto validationError = registry->getType("ValidationError");

    // Test error chain across multiple scopes
    checker->pushScope();
    auto result = checker->checkErrorInScope(ioError);
    checker->popScope();

    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "IOException");

    // Test error transformation across scopes
    checker->pushScope();
    result = checker->transformError(ioError, validationError);
    checker->popScope();

    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "ValidationError");
}

TEST_F(ErrorChainTest, MultipleErrorHandling) {
    auto ioError = registry->getType("IOException");
    auto netError = registry->getType("NetworkError");
    auto dbError = registry->getType("DatabaseError");

    std::vector<std::shared_ptr<pryst::Type>> errorChain = {ioError, netError, dbError};

    // Test handling multiple errors in chain
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_FALSE(result->isError());

    // Test invalid error chain
    errorChain.push_back(ioError); // Duplicate error type
    result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result->isError());
}
