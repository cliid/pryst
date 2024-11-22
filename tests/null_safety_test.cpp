#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class NullSafetyTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("Int?", std::make_shared<NullableType>("Int"));
        registry->registerType("String", std::make_shared<PrimitiveType>("String"));
        registry->registerType("String?", std::make_shared<NullableType>("String"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(NullSafetyTest, NullableOperations) {
    auto nullableInt = registry->getType("Int?");
    auto nullableString = registry->getType("String?");
    auto intType = registry->getType("Int");

    // Test nullable arithmetic
    auto result = checker->checkBinaryExpression(nullableInt, "+", intType);
    EXPECT_TRUE(result->isNullable());
    auto nullableResult = std::dynamic_pointer_cast<NullableType>(result);
    EXPECT_TRUE(nullableResult != nullptr);
    EXPECT_EQ(nullableResult->getBaseType(), "Int");

    // Test nullable comparison
    result = checker->checkBinaryExpression(nullableInt, "==", intType);
    EXPECT_FALSE(result->isNullable());
    EXPECT_EQ(result->toString(), "Boolean");
}

TEST_F(NullSafetyTest, NullPropagation) {
    auto nullableInt = registry->getType("Int?");
    auto nullableString = registry->getType("String?");

    // Test null propagation in expressions
    std::vector<std::shared_ptr<Type>> types = {nullableInt, nullableInt};
    std::vector<std::string> operators = {"+"};

    auto result = checker->checkComplexExpression(types, operators);
    EXPECT_TRUE(result->isNullable());
    auto nullableResult = std::dynamic_pointer_cast<NullableType>(result);
    EXPECT_TRUE(nullableResult != nullptr);
    EXPECT_EQ(nullableResult->getBaseType(), "Int");
}

TEST_F(NullSafetyTest, NullCoalescing) {
    auto nullableInt = registry->getType("Int?");
    auto intType = registry->getType("Int");

    // Test null coalescing operation
    auto result = checker->checkNullCoalescing(nullableInt, intType);
    EXPECT_FALSE(result->isNullable());
    EXPECT_EQ(result->toString(), "Int");
}
