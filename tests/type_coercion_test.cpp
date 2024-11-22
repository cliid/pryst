#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class TypeCoercionTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("Float", std::make_shared<PrimitiveType>("Float"));
        registry->registerType("String", std::make_shared<PrimitiveType>("String"));
        registry->registerType("Boolean", std::make_shared<PrimitiveType>("Boolean"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(TypeCoercionTest, NumericTypeCoercion) {
    auto intType = registry->getType("Int");
    auto floatType = registry->getType("Float");

    // Test int-float arithmetic coercion
    auto result = checker->checkBinaryExpression(intType, "+", floatType);
    EXPECT_FALSE(result->isError());
    EXPECT_EQ(result->toString(), "Float");

    // Test float-int multiplication
    result = checker->checkBinaryExpression(floatType, "*", intType);
    EXPECT_FALSE(result->isError());
    EXPECT_EQ(result->toString(), "Float");
}

TEST_F(TypeCoercionTest, StringCoercion) {
    auto stringType = registry->getType("String");
    auto intType = registry->getType("Int");
    auto floatType = registry->getType("Float");

    // Test string concatenation with numbers
    auto result = checker->checkBinaryExpression(stringType, "+", intType);
    EXPECT_FALSE(result->isError());
    EXPECT_EQ(result->toString(), "String");

    result = checker->checkBinaryExpression(stringType, "+", floatType);
    EXPECT_FALSE(result->isError());
    EXPECT_EQ(result->toString(), "String");
}

TEST_F(TypeCoercionTest, BooleanCoercion) {
    auto boolType = registry->getType("Boolean");
    auto intType = registry->getType("Int");

    // Test boolean to int coercion
    auto result = checker->checkBinaryExpression(boolType, "+", intType);
    EXPECT_TRUE(result->isError());  // Should not allow boolean arithmetic

    // Test comparison coercion
    result = checker->checkBinaryExpression(boolType, "==", intType);
    EXPECT_TRUE(result->isError());  // Should not allow boolean-int comparison
}

TEST_F(TypeCoercionTest, ComplexExpressionCoercion) {
    auto intType = registry->getType("Int");
    auto floatType = registry->getType("Float");
    auto stringType = registry->getType("String");

    // Test complex expression type inference
    std::vector<std::shared_ptr<Type>> types = {intType, floatType, intType};
    std::vector<std::string> operators = {"+", "*"};

    auto result = checker->checkComplexExpression(types, operators);
    EXPECT_FALSE(result->isError());
    EXPECT_EQ(result->toString(), "Float");

    // Test invalid complex expression
    types = {intType, stringType, floatType};
    result = checker->checkComplexExpression(types, operators);
    EXPECT_TRUE(result->isError());
}
