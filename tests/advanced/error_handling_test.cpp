#include <gtest/gtest.h>
#include "error_handling/advanced/chain/error_chain_advanced.hpp"
#include "error_handling/advanced/propagation/error_propagation.hpp"
#include "error_handling/advanced/transformation/error_transform.hpp"
#include "type_registry.hpp"
#include "type_system/advanced/types/advanced_types.hpp"

using namespace pryst::advanced;

class AdvancedErrorHandlingTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<pryst::TypeRegistry>();
        chain = std::make_shared<ErrorChain>();
        propagation = std::make_shared<ErrorPropagation>(registry);
        transform = std::make_shared<ErrorTransform>(registry);
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::shared_ptr<ErrorChain> chain;
    std::shared_ptr<ErrorPropagation> propagation;
    std::shared_ptr<ErrorTransform> transform;
};

TEST_F(AdvancedErrorHandlingTest, ErrorChainValidation) {
    auto error1 = std::make_shared<pryst::ErrorType>("TypeError");
    auto error2 = std::make_shared<pryst::ErrorType>("NullError");

    chain->addError(error1);
    chain->addError(error2);

    ASSERT_TRUE(chain->validate());
    ASSERT_EQ(chain->getFirstError()->toString(), "TypeError");
}

TEST_F(AdvancedErrorHandlingTest, ErrorChainDuplicateDetection) {
    auto error1 = std::make_shared<pryst::ErrorType>("TypeError");
    auto error2 = std::make_shared<pryst::ErrorType>("TypeError"); // Duplicate

    chain->addError(error1);
    chain->addError(error2);

    ASSERT_FALSE(chain->validate());
}

TEST_F(AdvancedErrorHandlingTest, ErrorTransformationCustom) {
    auto sourceError = std::make_shared<pryst::ErrorType>("OriginalError");
    auto customError = transform->transformToCustomError(sourceError, "CustomizedError");

    ASSERT_TRUE(customError->isError());
    ASSERT_TRUE(customError->toString().find("CustomizedError") != std::string::npos);
    ASSERT_TRUE(customError->toString().find("OriginalError") != std::string::npos);
}

TEST_F(AdvancedErrorHandlingTest, ErrorPropagationEmpty) {
    auto sourceError = std::make_shared<pryst::ErrorType>("InitialError");
    std::vector<std::shared_ptr<pryst::Type>> emptyPath;

    auto result = propagation->propagateError(sourceError, emptyPath);
    ASSERT_TRUE(result->isError());
    ASSERT_EQ(result->toString(), "InitialError");
}

TEST_F(AdvancedErrorHandlingTest, ErrorPropagationInvalidPath) {
    auto sourceError = std::make_shared<pryst::ErrorType>("InitialError");
    std::vector<std::shared_ptr<pryst::Type>> invalidPath = {
        registry->getIntType() // Not an error type
    };

    auto result = propagation->propagateError(sourceError, invalidPath);
    ASSERT_TRUE(result->isError());
    ASSERT_EQ(result->toString(), "InvalidPropagationPath");
}

TEST_F(AdvancedErrorHandlingTest, UnionTypeErrorHandling) {
    auto intType = registry->getIntType();
    auto stringType = registry->getStringType();
    auto unionType = std::make_shared<type_system::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, stringType}
    );

    auto error = std::make_shared<pryst::ErrorType>("UnionTypeError");
    chain->addError(error);

    auto result = transform->transformToCustomError(error, "InvalidUnionType");
    ASSERT_TRUE(result->isError());
    ASSERT_TRUE(result->toString().find("InvalidUnionType") != std::string::npos);
}

TEST_F(AdvancedErrorHandlingTest, IntersectionTypeErrorHandling) {
    auto error = std::make_shared<pryst::ErrorType>("IncompatibleIntersection");
    chain->addError(error);

    std::vector<std::shared_ptr<pryst::Type>> propagationPath = {
        std::make_shared<pryst::ErrorType>("ConflictingInterfaces"),
        std::make_shared<pryst::ErrorType>("IncompatibleMethods")
    };

    auto result = propagation->propagateError(error, propagationPath);
    ASSERT_TRUE(result->isError());
    ASSERT_TRUE(result->toString().find("IncompatibleMethods") != std::string::npos);
}

TEST_F(AdvancedErrorHandlingTest, ParameterizedTypeErrorHandling) {
    auto error = std::make_shared<pryst::ErrorType>("InvalidTypeParameter");
    auto customError = transform->transformToCustomError(error, "ParameterizedTypeError");

    chain->addError(customError);
    ASSERT_TRUE(chain->validate());
    ASSERT_TRUE(chain->getFirstError()->toString().find("ParameterizedTypeError") != std::string::npos);
}
