#include <gtest/gtest.h>
#include "../src/type_registry.hpp"
#include "../src/error_propagation.hpp"

class ErrorPropagationTest : public ::testing::Test {
protected:
    TypeRegistry registry;

    void SetUp() override {
        // Set up basic types and classes for testing
        registry.registerPrimitiveType("int");
        registry.registerPrimitiveType("string");
        registry.registerClass("TestClass");
    }
};

TEST_F(ErrorPropagationTest, TestCachedTypeErrorPropagation) {
    EXPECT_THROW({
        try {
            registry.getCachedType("nonexistent");
        } catch (const Error& e) {
            EXPECT_EQ(e.type(), "TypeError");
            EXPECT_TRUE(e.what().find("Type not found in cache") != std::string::npos);
            throw;
        }
    }, Error);
}

TEST_F(ErrorPropagationTest, TestMemberTypeErrorPropagation) {
    EXPECT_THROW({
        try {
            registry.getMemberType("TestClass", "nonexistent");
        } catch (const Error& e) {
            EXPECT_EQ(e.type(), "TypeError");
            EXPECT_TRUE(e.what().find("Member nonexistent not found") != std::string::npos);
            throw;
        }
    }, Error);
}

TEST_F(ErrorPropagationTest, TestMethodTypeErrorPropagation) {
    EXPECT_THROW({
        try {
            registry.getMethodType("TestClass", "nonexistent");
        } catch (const Error& e) {
            EXPECT_EQ(e.type(), "TypeError");
            EXPECT_TRUE(e.what().find("Method nonexistent not found") != std::string::npos);
            throw;
        }
    }, Error);
}

TEST_F(ErrorPropagationTest, TestTemplateTypeErrorPropagation) {
    EXPECT_THROW({
        try {
            registry.resolveTemplateType("List", {"nonexistent"});
        } catch (const Error& e) {
            EXPECT_EQ(e.type(), "TypeError");
            EXPECT_TRUE(e.what().find("Failed to resolve template parameter") != std::string::npos);
            throw;
        }
    }, Error);
}

TEST_F(ErrorPropagationTest, TestTypeUnificationErrorPropagation) {
    auto intType = registry.getCachedType("int");
    auto stringType = registry.getCachedType("string");

    EXPECT_THROW({
        try {
            registry.unifyTypes(intType, stringType, "test context");
        } catch (const Error& e) {
            EXPECT_EQ(e.type(), "TypeError");
            EXPECT_TRUE(e.what().find("Types cannot be unified") != std::string::npos);
            throw;
        }
    }, Error);
}

TEST_F(ErrorPropagationTest, TestTypeConstraintErrorPropagation) {
    auto intType = registry.getCachedType("int");
    std::vector<TypeConstraint> constraints = {
        TypeConstraint{TypeConstraint::Interface, "Comparable"}
    };

    EXPECT_THROW({
        try {
            registry.checkTypeConstraints(intType, constraints);
        } catch (const Error& e) {
            EXPECT_EQ(e.type(), "TypeError");
            EXPECT_TRUE(e.what().find("Failed to check type constraint") != std::string::npos);
            throw;
        }
    }, Error);
}

TEST_F(ErrorPropagationTest, TestNullableTypeErrorPropagation) {
    EXPECT_THROW({
        try {
            registry.getCachedType("nonexistent?");
        } catch (const Error& e) {
            EXPECT_EQ(e.type(), "TypeError");
            EXPECT_TRUE(e.what().find("Failed to get cached nullable type") != std::string::npos);
            throw;
        }
    }, Error);
}

TEST_F(ErrorPropagationTest, TestErrorTransformationChain) {
    EXPECT_THROW({
        try {
            // This should trigger multiple error transformations
            registry.resolveTemplateType("List", {"nonexistent?"});
        } catch (const Error& e) {
            // Verify error message contains all context from the chain
            EXPECT_TRUE(e.what().find("TypeRegistry") != std::string::npos);
            EXPECT_TRUE(e.what().find("Template type resolution error") != std::string::npos);
            EXPECT_TRUE(e.what().find("Failed to resolve template parameter") != std::string::npos);
            throw;
        }
    }, Error);
}
