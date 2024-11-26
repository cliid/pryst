#include "type_checker.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class RecursiveTypeErrorTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Tree", std::make_shared<PrimitiveType>("Tree"));
        registry->registerType("LinkedList", std::make_shared<PrimitiveType>("LinkedList"));
        registry->registerType("RecursionError", std::make_shared<ErrorType>("RecursionError"));
        registry->registerType("InfiniteRecursionError", std::make_shared<ErrorType>("InfiniteRecursionError"));
        registry->registerType("CyclicReferenceError", std::make_shared<ErrorType>("CyclicReferenceError"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(RecursiveTypeErrorTest, RecursiveTypeValidation) {
    auto recursionError = registry->getType("RecursionError");
    auto infiniteError = registry->getType("InfiniteRecursionError");

    checker->pushScope();  // Recursive type context
    auto result1 = checker->checkErrorInScope(recursionError);
    auto result2 = checker->checkErrorInScope(infiniteError);
    checker->popScope();

    EXPECT_TRUE(result1 != nullptr && result2 != nullptr);
    EXPECT_EQ(result1->toString(), "RecursionError");
    EXPECT_EQ(result2->toString(), "InfiniteRecursionError");
}

TEST_F(RecursiveTypeErrorTest, CyclicReferenceHandling) {
    auto cyclicError = registry->getType("CyclicReferenceError");
    auto recursionError = registry->getType("RecursionError");

    std::vector<std::shared_ptr<Type>> errorChain = {cyclicError, recursionError};
    auto result = checker->validateErrorChain(errorChain);
    EXPECT_TRUE(result != nullptr);
    EXPECT_FALSE(result->isError());
}

TEST_F(RecursiveTypeErrorTest, RecursiveErrorTransformation) {
    auto recursionError = registry->getType("RecursionError");
    auto cyclicError = registry->getType("CyclicReferenceError");

    checker->pushScope();  // Recursive type context
    auto result = checker->transformError(recursionError, cyclicError);
    checker->popScope();

    EXPECT_TRUE(result != nullptr);
    EXPECT_EQ(result->toString(), "CyclicReferenceError");
}
