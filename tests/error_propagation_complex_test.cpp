#include <gtest/gtest.h>
#include "error_test_helpers.hpp"
#include "../src/type_registry.hpp"

using namespace pryst::testing;

class ComplexErrorPropagationTest : public ::testing::Test {
protected:
    TypeRegistry registry;

    void SetUp() override {
        registry = ErrorTestHelper::createTestRegistry();
        setupComplexTypes();
    }

    void setupComplexTypes() {
        registry.registerClass("Base");
        registry.registerClass("Derived");
        registry.registerInheritance("Derived", "Base");
        registry.registerTemplate("List", {"T"});
        registry.registerTemplate("Map", {"K", "V"});
    }
};

TEST_F(ComplexErrorPropagationTest, TestTemplateInstantiationErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.resolveTemplateType("List", {"NonExistentType"}); },
        {"TypeRegistry", "Template type resolution error", "Failed to resolve template parameter"}
    );
}

TEST_F(ComplexErrorPropagationTest, TestNestedTemplateErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.resolveTemplateType("List", {"Map<int, NonExistent>"}); },
        {"TypeRegistry", "Template type resolution error", "Failed to resolve nested type"}
    );
}

TEST_F(ComplexErrorPropagationTest, TestInheritanceErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.registerInheritance("NonExistent", "Base"); },
        {"TypeRegistry", "Inheritance registration error", "Derived class not found"}
    );
}

TEST_F(ComplexErrorPropagationTest, TestMethodInheritanceErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() { registry.getMethodType("Derived", "nonexistentMethod"); },
        {"TypeRegistry", "Method type resolution error", "Method not found in inheritance chain"}
    );
}

TEST_F(ComplexErrorPropagationTest, TestTemplateConstraintErrors) {
    std::vector<TypeConstraint> constraints = {
        TypeConstraint{TypeConstraint::Interface, "Comparable"}
    };

    ErrorTestHelper::expectErrorChain(
        [&]() {
            auto listType = registry.resolveTemplateType("List", {"int"});
            registry.checkTypeConstraints(listType, constraints);
        },
        {"TypeRegistry", "Type constraint check error", "Interface not implemented"}
    );
}

TEST_F(ComplexErrorPropagationTest, TestRecursiveTypeErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() {
            registry.resolveTemplateType("List", {"List<List<NonExistent>>"});
        },
        {"TypeRegistry", "Template type resolution error", "Recursive type resolution failed"}
    );
}

TEST_F(ComplexErrorPropagationTest, TestMultipleTypeParameterErrors) {
    ErrorTestHelper::expectErrorChain(
        [&]() {
            registry.resolveTemplateType("Map", {"NonExistent1", "NonExistent2"});
        },
        {"TypeRegistry", "Template type resolution error", "Multiple type parameters failed"}
    );
}
