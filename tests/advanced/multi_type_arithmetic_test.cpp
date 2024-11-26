#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class MultiTypeArithmeticTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("Float", std::make_shared<PrimitiveType>("Float"));
        registry->registerType("Double", std::make_shared<PrimitiveType>("Double"));
        registry->registerType("ArithmeticError", std::make_shared<ErrorType>("ArithmeticError"));
    }

    std::shared_ptr<TypeRegistry> registry = std::make_shared<TypeRegistry>();
    TypeChecker checker{registry};
};

TEST_F(MultiTypeArithmeticTest, MixedTypeAddition) {
    auto intType = registry->getType("Int");
    auto floatType = registry->getType("Float");

    checker.pushScope();
    auto result = checker.checkBinaryExpression(intType, "+", floatType);
    checker.popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "Float");
}

TEST_F(MultiTypeArithmeticTest, TypePromotionChain) {
    auto intType = registry->getType("Int");
    auto doubleType = registry->getType("Double");

    checker.pushScope();
    auto result = checker.checkBinaryExpression(intType, "*", doubleType);
    checker.popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "Double");
}

TEST_F(MultiTypeArithmeticTest, ComplexExpressionTypes) {
    auto intType = registry->getType("Int");
    auto floatType = registry->getType("Float");
    auto doubleType = registry->getType("Double");

    checker.pushScope();
    // (int + float) * double
    auto intermediate = checker.checkBinaryExpression(intType, "+", floatType);
    auto result = checker.checkBinaryExpression(intermediate, "*", doubleType);
    checker.popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "Double");
}

TEST_F(MultiTypeArithmeticTest, InvalidTypeOperations) {
    auto intType = registry->getType("Int");
    auto errorType = registry->getType("ArithmeticError");

    checker.pushScope();
    auto result = checker.checkBinaryExpression(intType, "+", errorType);
    checker.popScope();

    EXPECT_TRUE(result->isError());
    EXPECT_EQ(result->toString(), "ArithmeticError");
}
