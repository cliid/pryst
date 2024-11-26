#include <gtest/gtest.h>
#include "scope_manager.hpp"
#include "type_system/advanced/inference/type_inference_advanced.hpp"
#include "type_system/advanced/validation/type_validation.hpp"
#include "type_system/advanced/types/advanced_types.hpp"

class ScopeIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<pryst::TypeRegistry>();
        scopeManager = std::make_shared<pryst::ScopeManager>();
        typeInference = std::make_shared<pryst::advanced::TypeInference>(registry);
        typeValidation = std::make_shared<pryst::advanced::TypeValidation>(registry);
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::shared_ptr<pryst::ScopeManager> scopeManager;
    std::shared_ptr<pryst::advanced::TypeInference> typeInference;
    std::shared_ptr<pryst::advanced::TypeValidation> typeValidation;
};

TEST_F(ScopeIntegrationTest, TypeInferenceInNestedScopes) {
    scopeManager->enterScope();

    auto intType = registry->getIntType();
    scopeManager->addVariable("x", intType);

    auto floatType = registry->getFloatType();
    scopeManager->addVariable("y", floatType);

    std::vector<std::shared_ptr<pryst::Type>> types = {intType, floatType};
    auto inferredType = typeInference->inferType(types, {});

    ASSERT_TRUE(typeValidation->validateCompatibility(inferredType, floatType, true));
    ASSERT_TRUE(scopeManager->lookupVariable("x")->equals(intType));
    ASSERT_TRUE(scopeManager->lookupVariable("y")->equals(floatType));

    scopeManager->exitScope();
}

TEST_F(ScopeIntegrationTest, ShadowingWithAdvancedTypes) {
    scopeManager->enterScope();
    auto intType = registry->getIntType();
    scopeManager->addVariable("x", intType);

    scopeManager->enterScope();
    auto nullableInt = std::make_shared<pryst::NullableType>(intType);
    scopeManager->addVariable("x", nullableInt);

    auto lookupType = scopeManager->lookupVariable("x");
    ASSERT_TRUE(lookupType->equals(nullableInt));
    ASSERT_TRUE(typeValidation->validateCompatibility(intType, lookupType, true));

    scopeManager->exitScope();
    lookupType = scopeManager->lookupVariable("x");
    ASSERT_TRUE(lookupType->equals(intType));

    scopeManager->exitScope();
}

TEST_F(ScopeIntegrationTest, FunctionScopeTypeInference) {
    scopeManager->enterScope(); // Function scope

    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();

    std::vector<std::shared_ptr<pryst::Type>> paramTypes = {intType, floatType};
    auto funcType = std::make_shared<pryst::FunctionType>(floatType, paramTypes);

    scopeManager->addVariable("func", funcType);

    auto lookupType = scopeManager->lookupVariable("func");
    ASSERT_TRUE(lookupType->equals(funcType));
    ASSERT_TRUE(typeValidation->validateFunctionType(lookupType));

    scopeManager->exitScope();
}

TEST_F(ScopeIntegrationTest, ErrorTypeScoping) {
    scopeManager->enterScope();

    auto errorType = std::make_shared<pryst::ErrorType>("TestError");
    scopeManager->addVariable("err", errorType);

    auto lookupType = scopeManager->lookupVariable("err");
    ASSERT_TRUE(lookupType->isError());
    ASSERT_TRUE(lookupType->equals(errorType));

    scopeManager->enterScope();
    auto intType = registry->getIntType();
    scopeManager->addVariable("err", intType); // Shadow error with valid type

    lookupType = scopeManager->lookupVariable("err");
    ASSERT_FALSE(lookupType->isError());
    ASSERT_TRUE(lookupType->equals(intType));

    scopeManager->exitScope();
    scopeManager->exitScope();
}

TEST_F(ScopeIntegrationTest, UnionTypeScoping) {
    scopeManager->enterScope();

    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();
    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, floatType}
    );

    scopeManager->addVariable("union_var", unionType);
    auto lookupType = scopeManager->lookupVariable("union_var");
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::UnionType>(lookupType) != nullptr);
    ASSERT_TRUE(typeValidation->validateCompatibility(intType, lookupType, true));

    scopeManager->exitScope();
}

TEST_F(ScopeIntegrationTest, IntersectionTypeScoping) {
    scopeManager->enterScope();

    auto serializableType = std::make_shared<pryst::InterfaceType>("Serializable");
    auto comparableType = std::make_shared<pryst::InterfaceType>("Comparable");
    auto intersectionType = std::make_shared<pryst::advanced::IntersectionType>(
        std::vector<std::shared_ptr<pryst::Type>>{serializableType, comparableType}
    );

    scopeManager->addVariable("intersection_var", intersectionType);
    auto lookupType = scopeManager->lookupVariable("intersection_var");
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::IntersectionType>(lookupType) != nullptr);

    scopeManager->exitScope();
}

TEST_F(ScopeIntegrationTest, ParameterizedTypeScoping) {
    scopeManager->enterScope();

    auto intType = registry->getIntType();
    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    scopeManager->addVariable("list_var", listType);
    auto lookupType = scopeManager->lookupVariable("list_var");
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(lookupType) != nullptr);

    scopeManager->exitScope();
}

TEST_F(ScopeIntegrationTest, NestedParameterizedTypeScoping) {
    scopeManager->enterScope(); // Outer scope

    auto intType = registry->getIntType();
    auto innerListType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    auto outerListType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{innerListType}
    );

    scopeManager->addVariable("nested_list", outerListType);

    scopeManager->enterScope(); // Inner scope
    auto lookupType = scopeManager->lookupVariable("nested_list");
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(lookupType) != nullptr);

    auto paramType = std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(lookupType);
    ASSERT_EQ(paramType->getTypeParameters().size(), 1);
    auto innerType = paramType->getTypeParameters()[0];
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(innerType) != nullptr);

    scopeManager->exitScope();
    scopeManager->exitScope();
}

TEST_F(ScopeIntegrationTest, UnionTypeWithParameterizedComponents) {
    scopeManager->enterScope();

    auto intType = registry->getIntType();
    auto listIntType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, listIntType}
    );

    scopeManager->addVariable("complex_union", unionType);
    auto lookupType = scopeManager->lookupVariable("complex_union");

    auto unionPtr = std::dynamic_pointer_cast<pryst::advanced::UnionType>(lookupType);
    ASSERT_TRUE(unionPtr != nullptr);
    ASSERT_EQ(unionPtr->getTypes().size(), 2);

    auto paramComponent = std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(
        unionPtr->getTypes()[1]
    );
    ASSERT_TRUE(paramComponent != nullptr);
    ASSERT_TRUE(paramComponent->getTypeParameters()[0]->equals(intType));

    scopeManager->exitScope();
}
