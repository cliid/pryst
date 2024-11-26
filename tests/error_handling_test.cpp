#include <gtest/gtest.h>
#include "../src/error_type.hpp"
#include "../src/error_chain.hpp"
#include "../src/type_registry.hpp"
#include "../src/error_handler.hpp"
#include <memory>

using namespace pryst::core;

class ErrorHandlingTest : public ::testing::Test {
protected:
    void SetUp() override {
        context = std::make_unique<llvm::LLVMContext>();
        registry = std::make_unique<TypeRegistry>(*context);
    }

    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<TypeRegistry> registry;
};

TEST_F(ErrorHandlingTest, ErrorTypeCreation) {
    auto errorType = makeErrorType("Division by zero", "ArithmeticError");
    EXPECT_TRUE(errorType->isError());
    EXPECT_EQ(errorType->getMessage(), "Division by zero");
    EXPECT_EQ(errorType->getErrorType(), "ArithmeticError");
}

TEST_F(ErrorHandlingTest, ErrorChaining) {
    auto error1 = makeErrorType("Invalid index", "IndexError");
    auto error2 = error1->chain("Array access failed");

    EXPECT_TRUE(error2->isError());
    EXPECT_EQ(error2->getMessage(), "Array access failed: Invalid index");
    EXPECT_EQ(error2->getErrorType(), "IndexError");
}

TEST_F(ErrorHandlingTest, ErrorTransformation) {
    auto error = makeErrorType("Invalid operation", "RuntimeError");
    auto transformed = error->transform("TypeError");

    EXPECT_TRUE(transformed->isError());
    EXPECT_EQ(transformed->getMessage(), "Invalid operation");
    EXPECT_EQ(transformed->getErrorType(), "TypeError");
}

TEST_F(ErrorHandlingTest, ErrorTypeHierarchy) {
    registry->registerErrorType("Error");
    registry->registerErrorType("TypeError");
    registry->registerErrorType("ValueError");

    registry->registerErrorHierarchy("TypeError", "Error");
    registry->registerErrorHierarchy("ValueError", "Error");

    auto typeError = registry->getCachedType("TypeError");
    auto valueError = registry->getCachedType("ValueError");
    auto baseError = registry->getCachedType("Error");

    EXPECT_TRUE(registry->isAssignable(typeError, baseError));
    EXPECT_TRUE(registry->isAssignable(valueError, baseError));
    EXPECT_FALSE(registry->isAssignable(typeError, valueError));
}

TEST_F(ErrorHandlingTest, ErrorHandlerTypedErrors) {
    auto handler = createTypedErrorHandler(*registry);
    auto error = Error("ValueError", "Invalid value");

    handler->handleTypedError(error, "ValueError");
    EXPECT_TRUE(handler->getChain().hasErrors());
    EXPECT_EQ(handler->getChain().getErrors().size(), 1);

    // Test error type mismatch
    handler->handleTypedError(error, "TypeError");
    EXPECT_EQ(handler->getChain().getErrors().size(), 2);
    EXPECT_TRUE(handler->getChain().getErrors()[1]->getType() == "TypeError");
}

TEST_F(ErrorHandlingTest, ErrorPropagation) {
    auto baseError = makeErrorType("Base error", "Error");
    auto propagated = std::make_shared<ErrorPropagationType>(baseError);

    EXPECT_TRUE(propagated->isError());
    EXPECT_EQ(propagated->toString(), "error<error<Error>: Base error>");
}
