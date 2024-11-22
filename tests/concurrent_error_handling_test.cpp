#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class ConcurrentErrorHandlingTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry->registerType("Future", std::make_shared<PrimitiveType>("Future"));
        registry->registerType("Promise", std::make_shared<PrimitiveType>("Promise"));
        registry->registerType("ConcurrencyError", std::make_shared<ErrorType>("ConcurrencyError"));
        registry->registerType("DeadlockError", std::make_shared<ErrorType>("DeadlockError"));
        registry->registerType("RaceConditionError", std::make_shared<ErrorType>("RaceConditionError"));
    }

    std::shared_ptr<TypeRegistry> registry = std::make_shared<TypeRegistry>();
    TypeChecker checker{registry};
};

TEST_F(ConcurrentErrorHandlingTest, MultipleErrorPropagation) {
    auto concurrencyError = registry->getType("ConcurrencyError");
    auto deadlockError = registry->getType("DeadlockError");
    auto raceError = registry->getType("RaceConditionError");

    checker.pushScope();  // Concurrent context
    auto result1 = checker.checkErrorInScope(concurrencyError);
    auto result2 = checker.checkErrorInScope(deadlockError);
    auto result3 = checker.checkErrorInScope(raceError);
    checker.popScope();

    EXPECT_TRUE(result1 != nullptr && result2 != nullptr && result3 != nullptr);
    EXPECT_EQ(result1->toString(), "ConcurrencyError");
    EXPECT_EQ(result2->toString(), "DeadlockError");
    EXPECT_EQ(result3->toString(), "RaceConditionError");
}

TEST_F(ConcurrentErrorHandlingTest, ErrorChainPriority) {
    auto concurrencyError = registry->getType("ConcurrencyError");
    auto deadlockError = registry->getType("DeadlockError");

    std::vector<std::shared_ptr<Type>> errorChain = {concurrencyError, deadlockError};
    auto result = checker.validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}

TEST_F(ConcurrentErrorHandlingTest, ConcurrentErrorTransformation) {
    auto concurrencyError = registry->getType("ConcurrencyError");
    auto raceError = registry->getType("RaceConditionError");

    checker.pushScope();  // Concurrent context
    auto result = checker.transformError(concurrencyError, raceError);
    checker.popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "RaceConditionError");
}
