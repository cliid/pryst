#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class ErrorTransformationTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("DivisionByZeroError", std::make_shared<ErrorType>("DivisionByZeroError"));
        registry->registerType("ComputationError", std::make_shared<ErrorType>("ComputationError"));
        registry->registerType("RuntimeError", std::make_shared<ErrorType>("RuntimeError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(ErrorTransformationTest, ErrorTypeTransformation) {
    auto divError = registry->getType("DivisionByZeroError");
    auto compError = registry->getType("ComputationError");

    auto result = checker->transformError(divError, compError);
    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "ComputationError");
}

TEST_F(ErrorTransformationTest, ErrorChainTransformation) {
    auto divError = registry->getType("DivisionByZeroError");
    auto compError = registry->getType("ComputationError");
    auto runtimeError = registry->getType("RuntimeError");

    std::vector<std::shared_ptr<Type>> errorChain = {divError, compError};
    auto result1 = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result1 != nullptr);
    EXPECT_FALSE(result1->isError());

    auto result2 = checker->transformError(compError, runtimeError);
    EXPECT_TRUE(result2 != nullptr);
    EXPECT_EQ(result2->toString(), "RuntimeError");
}

TEST_F(ErrorTransformationTest, InvalidErrorTransformation) {
    auto divError = registry->getType("DivisionByZeroError");
    auto intType = registry->getType("Int");

    auto result = checker->transformError(divError, intType);
    EXPECT_TRUE(result != nullptr);
    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "TypeError");
}
