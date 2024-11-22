#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class AsyncErrorHandlingTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("Future", std::make_shared<PrimitiveType>("Future"));
        registry->registerType("AsyncError", std::make_shared<ErrorType>("AsyncError"));
        registry->registerType("TimeoutError", std::make_shared<ErrorType>("TimeoutError"));
        registry->registerType("NetworkError", std::make_shared<ErrorType>("NetworkError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(AsyncErrorHandlingTest, AsyncErrorPropagation) {
    auto asyncError = registry->getType("AsyncError");
    auto timeoutError = registry->getType("TimeoutError");

    checker->pushScope();  // Async context
    auto result1 = checker->checkErrorInScope(asyncError);
    auto result2 = checker->transformError(asyncError, timeoutError);
    checker->popScope();

    EXPECT_TRUE(result1 != nullptr);
    EXPECT_TRUE(result2 != nullptr);
    EXPECT_EQ(result1->toString(), "AsyncError");
    EXPECT_EQ(result2->toString(), "TimeoutError");
}

TEST_F(AsyncErrorHandlingTest, AsyncErrorChainValidation) {
    auto asyncError = registry->getType("AsyncError");
    auto netError = registry->getType("NetworkError");
    auto timeoutError = registry->getType("TimeoutError");

    std::vector<std::shared_ptr<Type>> errorChain = {asyncError, netError, timeoutError};
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}

TEST_F(AsyncErrorHandlingTest, AsyncErrorTransformation) {
    auto asyncError = registry->getType("AsyncError");
    auto netError = registry->getType("NetworkError");

    checker->pushScope();  // Async context
    auto result = checker->transformError(asyncError, netError);
    checker->popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "NetworkError");
}
