#include "type_checker.hpp"
#include <gtest/gtest.h>
#include "type_system/advanced/types/advanced_types.hpp"

using namespace pryst;
using namespace pryst::type_system::advanced;

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

TEST_F(TypeInferenceTest, UnionTypeInference) {
    auto intType = registry->getType("Int");
    auto floatType = registry->getType("Float");

    // Test union type inference in arithmetic
    auto result = checker->inferExpressionType(
        {intType, floatType},
        {"||"}  // Union operator
    );
    EXPECT_TRUE(std::dynamic_pointer_cast<UnionType>(result) != nullptr);
}

TEST_F(TypeInferenceTest, IntersectionTypeInference) {
    auto serializableType = std::make_shared<InterfaceType>("Serializable");
    auto comparableType = std::make_shared<InterfaceType>("Comparable");
    registry->registerType("Serializable", serializableType);
    registry->registerType("Comparable", comparableType);

    // Test intersection type inference
    auto result = checker->inferExpressionType(
        {serializableType, comparableType},
        {"&&"}  // Intersection operator
    );
    EXPECT_TRUE(std::dynamic_pointer_cast<IntersectionType>(result) != nullptr);
}

TEST_F(TypeInferenceTest, ParameterizedTypeInference) {
    auto intType = registry->getType("Int");
    auto listType = registry->getType("List<T>");

    // Test parameterized type inference
    auto result = checker->inferGenericType(listType, intType);
    auto paramType = std::dynamic_pointer_cast<ParameterizedType>(result);
    EXPECT_TRUE(paramType != nullptr);
    EXPECT_EQ(paramType->getBaseType(), "List");
    EXPECT_EQ(paramType->getTypeArguments().size(), 1);
}
