#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class ParameterizedTypeErrorTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("List", std::make_shared<PrimitiveType>("List"));
        registry->registerType("Map", std::make_shared<PrimitiveType>("Map"));
        registry->registerType("ParameterError", std::make_shared<ErrorType>("ParameterError"));
        registry->registerType("BoundError", std::make_shared<ErrorType>("BoundError"));
        registry->registerType("ConstraintError", std::make_shared<ErrorType>("ConstraintError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(ParameterizedTypeErrorTest, ParameterizedTypeValidation) {
    auto paramError = registry->getType("ParameterError");
    auto boundError = registry->getType("BoundError");

    checker->pushScope();  // Parameterized type context
    auto result1 = checker->checkErrorInScope(paramError);
    auto result2 = checker->checkErrorInScope(boundError);
    checker->popScope();

    EXPECT_TRUE(result1 != nullptr && result2 != nullptr);
    EXPECT_EQ(result1->toString(), "ParameterError");
    EXPECT_EQ(result2->toString(), "BoundError");
}

TEST_F(ParameterizedTypeErrorTest, ConstraintErrorHandling) {
    auto constraintError = registry->getType("ConstraintError");
    auto paramError = registry->getType("ParameterError");

    std::vector<std::shared_ptr<Type>> errorChain = {constraintError, paramError};
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}

TEST_F(ParameterizedTypeErrorTest, ParameterErrorTransformation) {
    auto paramError = registry->getType("ParameterError");
    auto constraintError = registry->getType("ConstraintError");

    checker->pushScope();  // Parameterized type context
    auto result = checker->transformError(paramError, constraintError);
    checker->popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "ConstraintError");
}
