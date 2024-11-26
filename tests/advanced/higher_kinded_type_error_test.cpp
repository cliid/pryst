#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class HigherKindedTypeErrorTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Functor", std::make_shared<PrimitiveType>("Functor"));
        registry->registerType("Monad", std::make_shared<PrimitiveType>("Monad"));
        registry->registerType("KindError", std::make_shared<ErrorType>("KindError"));
        registry->registerType("RankError", std::make_shared<ErrorType>("RankError"));
        registry->registerType("LiftError", std::make_shared<ErrorType>("LiftError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(HigherKindedTypeErrorTest, HigherKindedTypeValidation) {
    auto kindError = registry->getType("KindError");
    auto rankError = registry->getType("RankError");

    checker->pushScope();  // Higher-kinded type context
    auto result1 = checker->checkErrorInScope(kindError);
    auto result2 = checker->checkErrorInScope(rankError);
    checker->popScope();

    EXPECT_TRUE(result1 != nullptr && result2 != nullptr);
    EXPECT_EQ(result1->toString(), "KindError");
    EXPECT_EQ(result2->toString(), "RankError");
}

TEST_F(HigherKindedTypeErrorTest, LiftErrorHandling) {
    auto liftError = registry->getType("LiftError");
    auto kindError = registry->getType("KindError");

    std::vector<std::shared_ptr<Type>> errorChain = {liftError, kindError};
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}

TEST_F(HigherKindedTypeErrorTest, KindErrorTransformation) {
    auto kindError = registry->getType("KindError");
    auto liftError = registry->getType("LiftError");

    checker->pushScope();  // Higher-kinded type context
    auto result = checker->transformError(kindError, liftError);
    checker->popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "LiftError");
}
