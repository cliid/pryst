#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class TypeInferenceTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("Float", std::make_shared<PrimitiveType>("Float"));
        registry->registerType("String", std::make_shared<PrimitiveType>("String"));
        registry->registerType("List<T>", std::make_shared<GenericType>("List"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(TypeInferenceTest, ComplexExpressionInference) {
    auto intType = registry->getType("Int");
    auto floatType = registry->getType("Float");

    // Test nested arithmetic inference
    auto result = checker->inferExpressionType(
        {intType, floatType, intType},
        {"+", "*"}
    );
    EXPECT_EQ(result->toString(), "Float");
}

TEST_F(TypeInferenceTest, GenericTypeInference) {
    auto intType = registry->getType("Int");
    auto listType = registry->getType("List<T>");

    // Test generic type parameter inference
    auto result = checker->inferGenericType(listType, intType);
    EXPECT_EQ(result->toString(), "List<Int>");
}

TEST_F(TypeInferenceTest, LambdaInference) {
    auto intType = registry->getType("Int");
    auto floatType = registry->getType("Float");

    // Test lambda return type inference
    auto result = checker->inferLambdaReturnType(
        {intType, floatType},
        {"+"}
    );
    EXPECT_EQ(result->toString(), "Float");
}
