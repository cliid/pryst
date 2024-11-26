#include <gtest/gtest.h>
#include "type_checker.hpp"
#include "type_system/advanced/inference/type_inference_advanced.hpp"
#include "type_system/advanced/validation/type_validation.hpp"
#include "error_handling/advanced/chain/error_chain_advanced.hpp"
#include "type_system/advanced/types/advanced_types.hpp"

class TypeCheckerIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<pryst::TypeRegistry>();
        typeChecker = std::make_shared<pryst::TypeChecker>(registry);
        inference = std::make_shared<pryst::advanced::TypeInference>(registry);
        validation = std::make_shared<pryst::advanced::TypeValidation>(registry);
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::shared_ptr<pryst::TypeChecker> typeChecker;
    std::shared_ptr<pryst::advanced::TypeInference> inference;
    std::shared_ptr<pryst::advanced::TypeValidation> validation;
};

TEST_F(TypeCheckerIntegrationTest, InferredTypeValidation) {
    // Test that inferred types are properly validated by type checker
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();

    std::vector<std::shared_ptr<pryst::Type>> types = {intType, floatType};
    std::vector<std::string> ops = {"+"};

    auto inferredType = inference->inferType(types, ops);
    ASSERT_TRUE(inferredType->equals(floatType));
    ASSERT_TRUE(typeChecker->isTypeValid(inferredType));
}

TEST_F(TypeCheckerIntegrationTest, NullableTypeIntegration) {
    // Test nullable type handling between systems
    auto intType = registry->getIntType();
    auto nullableInt = std::make_shared<pryst::NullableType>(intType);

    ASSERT_TRUE(validation->validateCompatibility(intType, nullableInt, true));
    ASSERT_TRUE(typeChecker->isTypeValid(nullableInt));
}

TEST_F(TypeCheckerIntegrationTest, FunctionTypeValidation) {
    // Test function type validation across systems
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();

    std::vector<std::shared_ptr<pryst::Type>> paramTypes = {intType, floatType};
    auto funcType = std::make_shared<pryst::FunctionType>(floatType, paramTypes);

    ASSERT_TRUE(validation->validateFunctionCall(funcType, paramTypes));
    ASSERT_TRUE(typeChecker->isTypeValid(funcType));
}

TEST_F(TypeCheckerIntegrationTest, ErrorTypeHandling) {
    // Test error type propagation between systems
    auto errorType = std::make_shared<pryst::ErrorType>("TestError");
    auto validatedType = typeChecker->validateType(errorType);

    ASSERT_TRUE(validatedType->isError());
    ASSERT_TRUE(validation->validateCompatibility(errorType, validatedType, false));
}

TEST_F(TypeCheckerIntegrationTest, UnionTypeValidation) {
    auto intType = registry->getIntType();
    auto stringType = registry->getStringType();
    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, stringType}
    );

    ASSERT_TRUE(validation->validateCompatibility(intType, unionType, true));
    ASSERT_TRUE(typeChecker->isTypeValid(unionType));
}

TEST_F(TypeCheckerIntegrationTest, IntersectionTypeValidation) {
    auto serializableType = std::make_shared<pryst::InterfaceType>("Serializable");
    auto comparableType = std::make_shared<pryst::InterfaceType>("Comparable");
    auto intersectionType = std::make_shared<pryst::advanced::IntersectionType>(
        std::vector<std::shared_ptr<pryst::Type>>{serializableType, comparableType}
    );

    ASSERT_TRUE(validation->validateIntersectionType(intersectionType));
    ASSERT_TRUE(typeChecker->isTypeValid(intersectionType));
}

TEST_F(TypeCheckerIntegrationTest, ParameterizedTypeValidation) {
    auto intType = registry->getIntType();
    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    ASSERT_TRUE(validation->validateParameterizedType(listType));
    ASSERT_TRUE(typeChecker->isTypeValid(listType));
}

TEST_F(TypeCheckerIntegrationTest, NestedParameterizedTypeValidation) {
    auto intType = registry->getIntType();
    auto innerListType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );
    auto outerListType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{innerListType}
    );

    ASSERT_TRUE(validation->validateParameterizedType(innerListType));
    ASSERT_TRUE(validation->validateParameterizedType(outerListType));
    ASSERT_TRUE(typeChecker->isTypeValid(outerListType));
}

TEST_F(TypeCheckerIntegrationTest, UnionWithParameterizedTypeValidation) {
    auto intType = registry->getIntType();
    auto listIntType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );
    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, listIntType}
    );

    ASSERT_TRUE(validation->validateParameterizedType(listIntType));
    ASSERT_TRUE(validation->validateCompatibility(intType, unionType, true));
    ASSERT_TRUE(typeChecker->isTypeValid(unionType));
}

TEST_F(TypeCheckerIntegrationTest, TypeParameterConstraintValidation) {
    auto comparableType = std::make_shared<pryst::InterfaceType>("Comparable");
    auto typeParam = std::make_shared<pryst::TypeParameter>("T", comparableType);
    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{typeParam}
    );

    ASSERT_TRUE(validation->validateTypeParameter(typeParam));
    ASSERT_TRUE(validation->validateParameterizedType(listType));
    ASSERT_TRUE(typeChecker->isTypeValid(listType));
}
