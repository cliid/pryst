#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class UnionTypeErrorTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Option", std::make_shared<PrimitiveType>("Option"));
        registry->registerType("Either", std::make_shared<PrimitiveType>("Either"));
        registry->registerType("UnionError", std::make_shared<ErrorType>("UnionError"));
        registry->registerType("VariantError", std::make_shared<ErrorType>("VariantError"));
        registry->registerType("TypeMismatchError", std::make_shared<ErrorType>("TypeMismatchError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(UnionTypeErrorTest, UnionTypeValidation) {
    auto unionError = registry->getType("UnionError");
    auto variantError = registry->getType("VariantError");

    checker->pushScope();  // Union type context
    auto result1 = checker->checkErrorInScope(unionError);
    auto result2 = checker->checkErrorInScope(variantError);
    checker->popScope();

    EXPECT_TRUE(result1 != nullptr && result2 != nullptr);
    EXPECT_EQ(result1->toString(), "UnionError");
    EXPECT_EQ(result2->toString(), "VariantError");
}

TEST_F(UnionTypeErrorTest, TypeMismatchHandling) {
    auto mismatchError = registry->getType("TypeMismatchError");
    auto unionError = registry->getType("UnionError");

    std::vector<std::shared_ptr<Type>> errorChain = {mismatchError, unionError};
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}

TEST_F(UnionTypeErrorTest, UnionErrorTransformation) {
    auto unionError = registry->getType("UnionError");
    auto mismatchError = registry->getType("TypeMismatchError");

    checker->pushScope();  // Union type context
    auto result = checker->transformError(unionError, mismatchError);
    checker->popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "TypeMismatchError");
}
