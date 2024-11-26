#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class GenericTypeErrorTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("List", std::make_shared<PrimitiveType>("List"));
        registry->registerType("Map", std::make_shared<PrimitiveType>("Map"));
        registry->registerType("GenericError", std::make_shared<ErrorType>("GenericError"));
        registry->registerType("TypeParameterError", std::make_shared<ErrorType>("TypeParameterError"));
        registry->registerType("BoundError", std::make_shared<ErrorType>("BoundError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(GenericTypeErrorTest, GenericTypeValidation) {
    auto genericError = registry->getType("GenericError");
    auto paramError = registry->getType("TypeParameterError");

    checker->pushScope();  // Generic type context
    auto result1 = checker->checkErrorInScope(genericError);
    auto result2 = checker->checkErrorInScope(paramError);
    checker->popScope();

    EXPECT_TRUE(result1 != nullptr && result2 != nullptr);
    EXPECT_EQ(result1->toString(), "GenericError");
    EXPECT_EQ(result2->toString(), "TypeParameterError");
}

TEST_F(GenericTypeErrorTest, BoundErrorHandling) {
    auto boundError = registry->getType("BoundError");
    auto genericError = registry->getType("GenericError");

    std::vector<std::shared_ptr<Type>> errorChain = {boundError, genericError};
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}

TEST_F(GenericTypeErrorTest, GenericErrorTransformation) {
    auto genericError = registry->getType("GenericError");
    auto boundError = registry->getType("BoundError");

    checker->pushScope();  // Generic type context
    auto result = checker->transformError(genericError, boundError);
    checker->popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "BoundError");
}
