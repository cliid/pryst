#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class ComplexErrorChainTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("String", std::make_shared<PrimitiveType>("String"));
        registry->registerType("DivisionByZeroError", std::make_shared<ErrorType>("DivisionByZeroError"));
        registry->registerType("FileNotFoundError", std::make_shared<ErrorType>("FileNotFoundError"));
        registry->registerType("NetworkError", std::make_shared<ErrorType>("NetworkError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(ComplexErrorChainTest, NestedTryCatchBlocks) {
    auto divError = registry->getType("DivisionByZeroError");
    auto fileError = registry->getType("FileNotFoundError");
    auto netError = registry->getType("NetworkError");

    // Test nested try-catch with multiple error types
    std::vector<std::shared_ptr<Type>> errorChain = {divError, fileError, netError};
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());  // validateErrorChain returns Boolean type on success
}

TEST_F(ComplexErrorChainTest, ErrorPropagationAcrossScopes) {
    auto divError = registry->getType("DivisionByZeroError");
    auto fileError = registry->getType("FileNotFoundError");

    checker->pushScope();
    auto result1 = checker->checkErrorInScope(divError);
    checker->pushScope();
    auto result2 = checker->checkErrorInScope(fileError);
    checker->popScope();
    checker->popScope();

    EXPECT_TRUE(result1 != nullptr);
    EXPECT_TRUE(result2 != nullptr);
    EXPECT_EQ(result1->toString(), "DivisionByZeroError");
    EXPECT_EQ(result2->toString(), "FileNotFoundError");
}

TEST_F(ComplexErrorChainTest, ErrorChainValidation) {
    auto divError = registry->getType("DivisionByZeroError");
    auto fileError = registry->getType("FileNotFoundError");
    auto netError = registry->getType("NetworkError");

    auto result = checker->validateErrorChain({divError, fileError, netError});
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}
