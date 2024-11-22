#include "type_checker.hpp"
#include <gtest/gtest.h>

namespace pryst {
namespace testing {

class TypeCheckerTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<pryst::TypeRegistry>();
        registry->registerType("Int", std::make_shared<pryst::PrimitiveType>("Int"));
        registry->registerType("Boolean", std::make_shared<pryst::PrimitiveType>("Boolean"));
        registry->registerType("TypeError", std::make_shared<pryst::ErrorType>("TypeError"));
        registry->registerType("UnsupportedOperationError", std::make_shared<pryst::ErrorType>("UnsupportedOperationError"));
        checker = std::make_unique<pryst::TypeChecker>(registry);
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::unique_ptr<pryst::TypeChecker> checker;
};

TEST_F(TypeCheckerTest, BinaryArithmeticExpressions) {
    auto intType = registry->getType("Int");

    // Test valid arithmetic
    auto result = checker->checkBinaryExpression(intType, "+", intType);
    EXPECT_FALSE(result->isError());
    EXPECT_TRUE(result->isPrimitive());

    // Test invalid operands
    auto errorType = registry->getType("TypeError");
    result = checker->checkBinaryExpression(errorType, "+", intType);
    EXPECT_TRUE(result->isError());
}

TEST_F(TypeCheckerTest, ComparisonExpressions) {
    auto intType = registry->getType("Int");
    auto boolType = registry->getType("Boolean");

    auto result = checker->checkBinaryExpression(intType, "==", intType);
    EXPECT_FALSE(result->isError());
    EXPECT_EQ(result->toString(), "Boolean");
}

TEST_F(TypeCheckerTest, UnaryExpressions) {
    auto intType = registry->getType("Int");
    auto boolType = registry->getType("Boolean");

    // Test numeric negation
    auto result = checker->checkUnaryExpression("-", intType);
    EXPECT_FALSE(result->isError());
    EXPECT_TRUE(result->isPrimitive());

    // Test logical not
    result = checker->checkUnaryExpression("!", boolType);
    EXPECT_FALSE(result->isError());
    EXPECT_EQ(result->toString(), "Boolean");
}

TEST_F(TypeCheckerTest, ErrorPropagation) {
    auto errorType = registry->getType("TypeError");
    auto intType = registry->getType("Int");

    // Test error propagation in binary expressions
    auto result = checker->checkBinaryExpression(errorType, "+", intType);
    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "TypeError");

    // Test error propagation in unary expressions
    result = checker->checkUnaryExpression("-", errorType);
    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "TypeError");
}

TEST_F(TypeCheckerTest, UnsupportedOperations) {
    auto intType = registry->getType("Int");

    // Test unsupported binary operator
    auto result = checker->checkBinaryExpression(intType, "^", intType);
    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "UnsupportedOperationError");

    // Test unsupported unary operator
    result = checker->checkUnaryExpression("~", intType);
    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "UnsupportedOperationError");
}

} // namespace testing
} // namespace pryst
