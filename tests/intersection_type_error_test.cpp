#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class IntersectionTypeErrorTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Interface", std::make_shared<PrimitiveType>("Interface"));
        registry->registerType("Trait", std::make_shared<PrimitiveType>("Trait"));
        registry->registerType("IntersectionError", std::make_shared<ErrorType>("IntersectionError"));
        registry->registerType("InterfaceError", std::make_shared<ErrorType>("InterfaceError"));
        registry->registerType("TraitError", std::make_shared<ErrorType>("TraitError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(IntersectionTypeErrorTest, IntersectionTypeValidation) {
    auto intersectionError = registry->getType("IntersectionError");
    auto interfaceError = registry->getType("InterfaceError");

    checker->pushScope();  // Intersection type context
    auto result1 = checker->checkErrorInScope(intersectionError);
    auto result2 = checker->checkErrorInScope(interfaceError);
    checker->popScope();

    EXPECT_TRUE(result1 != nullptr && result2 != nullptr);
    EXPECT_EQ(result1->toString(), "IntersectionError");
    EXPECT_EQ(result2->toString(), "InterfaceError");
}

TEST_F(IntersectionTypeErrorTest, TraitErrorHandling) {
    auto traitError = registry->getType("TraitError");
    auto intersectionError = registry->getType("IntersectionError");

    std::vector<std::shared_ptr<Type>> errorChain = {traitError, intersectionError};
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}

TEST_F(IntersectionTypeErrorTest, IntersectionErrorTransformation) {
    auto intersectionError = registry->getType("IntersectionError");
    auto traitError = registry->getType("TraitError");

    checker->pushScope();  // Intersection type context
    auto result = checker->transformError(intersectionError, traitError);
    checker->popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "TraitError");
}
