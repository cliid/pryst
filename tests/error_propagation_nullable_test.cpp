#include <gtest/gtest.h>
#include "error_test_helpers.hpp"
#include "../src/type_registry.hpp"

using namespace pryst::testing;

class NullableErrorPropagationTest : public ::testing::Test {
protected:
    TypeRegistry registry;

    void SetUp() override {
        registry = ErrorTestHelper::createTestRegistry();
        setupNullableTypes();
    }

    void setupNullableTypes() {
        registry.registerClass("Optional");
        registry.registerTemplate("Result", {"T", "E"});
    }
};

TEST_F(NullableErrorPropagationTest, TestNullableTypeResolutionErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.getCachedType("NonExistent?"); },
        {"TypeRegistry", "Type lookup error", "Failed to resolve nullable base type"}
    );
}

TEST_F(NullableErrorPropagationTest, TestNullableTemplateErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.resolveTemplateType("Result", {"int?", "NonExistent"}); },
        {"TypeRegistry", "Template type resolution error", "Failed to resolve error type"}
    );
}

TEST_F(NullableErrorPropagationTest, TestNestedNullableErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.getCachedType("List<int?>?"); },
        {"TypeRegistry", "Type lookup error", "Failed to resolve nested nullable type"}
    );
}

TEST_F(NullableErrorPropagationTest, TestUnionWithNullableErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.unifyTypes(
            registry.getCachedType("int?"),
            registry.getCachedType("NonExistent?"),
            "union context"
        ); },
        {"TypeRegistry", "Type unification error", "Cannot unify with undefined nullable type"}
    );
}

TEST_F(NullableErrorPropagationTest, TestNullableMethodErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.getMethodType("Optional", "unwrap"); },
        {"TypeRegistry", "Method type resolution error", "Method not found in nullable type"}
    );
}

TEST_F(NullableErrorPropagationTest, TestNullableConstraintErrors) {
    std::vector<TypeConstraint> constraints = {
        TypeConstraint{TypeConstraint::Nullable, ""}
    };

    ErrorTestHelper::expectErrorChain(
        [&]() {
            auto intType = registry.getCachedType("int");
            registry.checkTypeConstraints(intType, constraints);
        },
        {"TypeRegistry", "Type constraint check error", "Type is not nullable"}
    );
}
