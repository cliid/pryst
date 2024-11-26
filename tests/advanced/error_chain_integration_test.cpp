#include <gtest/gtest.h>
#include "type_checker.hpp"
#include "error_handling/advanced/chain/error_chain_advanced.hpp"
#include "error_handling/advanced/propagation/error_propagation.hpp"
#include "error_handling/advanced/transformation/error_transform.hpp"
#include "type_system/advanced/types/advanced_types.hpp"

class ErrorChainIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<pryst::TypeRegistry>();
        typeChecker = std::make_shared<pryst::TypeChecker>(registry);
        errorChain = std::make_shared<pryst::advanced::ErrorChain>();
        errorPropagation = std::make_shared<pryst::advanced::ErrorPropagation>(registry);
        errorTransform = std::make_shared<pryst::advanced::ErrorTransform>(registry);
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::shared_ptr<pryst::TypeChecker> typeChecker;
    std::shared_ptr<pryst::advanced::ErrorChain> errorChain;
    std::shared_ptr<pryst::advanced::ErrorPropagation> errorPropagation;
    std::shared_ptr<pryst::advanced::ErrorTransform> errorTransform;
};

TEST_F(ErrorChainIntegrationTest, ErrorPropagationWithTypeChecker) {
    // Test error propagation through type checker
    auto errorType = std::make_shared<pryst::ErrorType>("InitialError");
    errorChain->addError(errorType);

    auto propagatedError = errorPropagation->propagateError(errorType);
    auto checkedType = typeChecker->validateType(propagatedError);

    ASSERT_TRUE(checkedType->isError());
    ASSERT_TRUE(errorChain->containsError(checkedType));
}

TEST_F(ErrorChainIntegrationTest, ErrorTransformationInTypeChecking) {
    // Test error transformation during type checking
    auto sourceError = std::make_shared<pryst::ErrorType>("SourceError");
    auto targetError = std::make_shared<pryst::ErrorType>("TargetError");

    auto transformedError = errorTransform->transformError(sourceError, targetError);
    auto checkedType = typeChecker->validateType(transformedError);

    ASSERT_TRUE(checkedType->isError());
    ASSERT_EQ(checkedType->getErrorMessage(), "TargetError");
}

TEST_F(ErrorChainIntegrationTest, ErrorChainValidation) {
    // Test error chain validation with type checker
    auto error1 = std::make_shared<pryst::ErrorType>("Error1");
    auto error2 = std::make_shared<pryst::ErrorType>("Error2");

    errorChain->addError(error1);
    errorChain->addError(error2);

    auto checkedType1 = typeChecker->validateType(error1);
    auto checkedType2 = typeChecker->validateType(error2);

    ASSERT_TRUE(errorChain->containsError(checkedType1));
    ASSERT_TRUE(errorChain->containsError(checkedType2));
    ASSERT_EQ(errorChain->getErrorCount(), 2);
}

TEST_F(ErrorChainIntegrationTest, ErrorRecoveryWithTypeChecker) {
    // Test error recovery during type checking
    auto errorType = std::make_shared<pryst::ErrorType>("RecoverableError");
    errorChain->addError(errorType);

    auto recoveredType = registry->getIntType();
    auto transformedType = errorTransform->transformError(errorType, recoveredType);
    auto checkedType = typeChecker->validateType(transformedType);

    ASSERT_FALSE(checkedType->isError());
    ASSERT_TRUE(checkedType->equals(recoveredType));
}

TEST_F(ErrorChainIntegrationTest, UnionTypeErrorHandling) {
    auto intType = registry->getIntType();
    auto stringType = registry->getStringType();
    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, stringType}
    );

    auto errorType = std::make_shared<pryst::ErrorType>("UnionTypeError");
    errorChain->addError(errorType);

    auto checkedType = typeChecker->validateType(unionType);
    auto transformedError = errorTransform->transformError(errorType, checkedType);

    ASSERT_TRUE(transformedError->isError());
    ASSERT_TRUE(errorChain->containsError(transformedError));
}

TEST_F(ErrorChainIntegrationTest, IntersectionTypeErrorPropagation) {
    auto serializableType = std::make_shared<pryst::InterfaceType>("Serializable");
    auto comparableType = std::make_shared<pryst::InterfaceType>("Comparable");
    auto intersectionType = std::make_shared<pryst::advanced::IntersectionType>(
        std::vector<std::shared_ptr<pryst::Type>>{serializableType, comparableType}
    );

    auto errorType = std::make_shared<pryst::ErrorType>("IntersectionTypeError");
    auto propagatedError = errorPropagation->propagateError(errorType);
    auto checkedType = typeChecker->validateType(intersectionType);

    ASSERT_TRUE(checkedType->isError());
    ASSERT_TRUE(errorChain->containsError(propagatedError));
}

TEST_F(ErrorChainIntegrationTest, ParameterizedTypeErrorTransformation) {
    auto intType = registry->getIntType();
    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    auto errorType = std::make_shared<pryst::ErrorType>("ParameterizedTypeError");
    auto transformedError = errorTransform->transformError(errorType, listType);
    auto checkedType = typeChecker->validateType(transformedError);

    ASSERT_TRUE(checkedType->isError());
    ASSERT_TRUE(errorChain->containsError(checkedType));
}

TEST_F(ErrorChainIntegrationTest, NestedTypeErrorPropagation) {
    auto intType = registry->getIntType();
    auto innerListType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );
    auto outerListType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{innerListType}
    );

    auto innerError = std::make_shared<pryst::ErrorType>("InnerListError");
    auto outerError = std::make_shared<pryst::ErrorType>("OuterListError");

    auto propagatedInner = errorPropagation->propagateError(innerError);
    auto propagatedOuter = errorPropagation->propagateError(outerError);

    auto checkedType = typeChecker->validateType(outerListType);
    ASSERT_TRUE(checkedType->isError());
    ASSERT_TRUE(errorChain->containsError(propagatedInner));
    ASSERT_TRUE(errorChain->containsError(propagatedOuter));
}

TEST_F(ErrorChainIntegrationTest, ComplexErrorTransformationChain) {
    auto intType = registry->getIntType();
    auto stringType = registry->getStringType();

    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, stringType}
    );
    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{unionType}
    );

    auto error1 = std::make_shared<pryst::ErrorType>("InitialError");
    auto error2 = std::make_shared<pryst::ErrorType>("TransformedError");
    auto error3 = std::make_shared<pryst::ErrorType>("FinalError");

    auto transform1 = errorTransform->transformError(error1, error2);
    auto transform2 = errorTransform->transformError(transform1, error3);
    auto checkedType = typeChecker->validateType(listType);

    ASSERT_TRUE(checkedType->isError());
    ASSERT_TRUE(errorChain->containsError(transform2));
    ASSERT_EQ(errorChain->getErrorCount(), 3);
}
