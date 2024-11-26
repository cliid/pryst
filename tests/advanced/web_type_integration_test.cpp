#include <gtest/gtest.h>
#include "web/web_types.hpp"
#include "type_system/advanced/inference/type_inference_advanced.hpp"
#include "type_system/advanced/validation/type_validation.hpp"
#include "error_handling/advanced/chain/error_chain_advanced.hpp"
#include "type_system/advanced/types/advanced_types.hpp"

class WebTypeIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<pryst::TypeRegistry>();
        registry->registerWebTypes();
        typeInference = std::make_shared<pryst::advanced::TypeInference>(registry);
        typeValidation = std::make_shared<pryst::advanced::TypeValidation>(registry);
        errorChain = std::make_shared<pryst::advanced::ErrorChain>();
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::shared_ptr<pryst::advanced::TypeInference> typeInference;
    std::shared_ptr<pryst::advanced::TypeValidation> typeValidation;
    std::shared_ptr<pryst::advanced::ErrorChain> errorChain;
};

TEST_F(WebTypeIntegrationTest, HttpResponseTypeInference) {
    auto responseType = registry->getType("HttpResponse");
    auto stringType = registry->getStringType();

    ASSERT_TRUE(responseType != nullptr);
    ASSERT_TRUE(typeValidation->validateCompatibility(responseType, stringType, false));

    std::vector<std::shared_ptr<pryst::Type>> types = {responseType, stringType};
    auto inferredType = typeInference->inferType(types, {"+"});

    ASSERT_TRUE(inferredType->equals(stringType));
}

TEST_F(WebTypeIntegrationTest, WebServerErrorHandling) {
    auto serverType = registry->getType("WebServer");
    auto errorType = std::make_shared<pryst::ErrorType>("WebServerError");

    errorChain->addError(errorType);

    ASSERT_TRUE(serverType != nullptr);
    ASSERT_TRUE(typeValidation->validateWebServerType(serverType));

    auto validatedType = typeValidation->validateType(errorType);
    ASSERT_TRUE(validatedType->isError());
    ASSERT_TRUE(errorChain->containsError(validatedType));
}

TEST_F(WebTypeIntegrationTest, RouteHandlerTypeValidation) {
    auto handlerType = registry->getType("RouteHandler");
    auto responseType = registry->getType("HttpResponse");
    auto requestType = registry->getType("HttpRequest");

    ASSERT_TRUE(handlerType != nullptr);
    ASSERT_TRUE(responseType != nullptr);
    ASSERT_TRUE(requestType != nullptr);

    std::vector<std::shared_ptr<pryst::Type>> paramTypes = {requestType};
    auto funcType = std::make_shared<pryst::FunctionType>(responseType, paramTypes);

    ASSERT_TRUE(typeValidation->validateCompatibility(handlerType, funcType, true));
}

TEST_F(WebTypeIntegrationTest, JsonTypeInference) {
    auto jsonType = registry->getType("Json");
    auto mapType = registry->getMapType(registry->getStringType(), registry->getAnyType());

    ASSERT_TRUE(jsonType != nullptr);
    ASSERT_TRUE(typeValidation->validateCompatibility(jsonType, mapType, true));

    std::vector<std::shared_ptr<pryst::Type>> types = {jsonType, mapType};
    auto inferredType = typeInference->inferType(types, {"="});

    ASSERT_TRUE(inferredType->equals(jsonType));
}

TEST_F(WebTypeIntegrationTest, UnionTypeWebSerialization) {
    auto jsonType = registry->getType("Json");
    auto stringType = registry->getStringType();
    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{jsonType, stringType}
    );

    ASSERT_TRUE(typeValidation->validateWebType(unionType));
    auto inferredType = typeInference->inferWebType(unionType);
    ASSERT_TRUE(inferredType->equals(jsonType));
}

TEST_F(WebTypeIntegrationTest, IntersectionTypeWebHandling) {
    auto serializableType = std::make_shared<pryst::InterfaceType>("WebSerializable");
    auto validatableType = std::make_shared<pryst::InterfaceType>("WebValidatable");
    auto intersectionType = std::make_shared<pryst::advanced::IntersectionType>(
        std::vector<std::shared_ptr<pryst::Type>>{serializableType, validatableType}
    );

    ASSERT_TRUE(typeValidation->validateWebType(intersectionType));
    ASSERT_FALSE(errorChain->hasErrors());
}

TEST_F(WebTypeIntegrationTest, ParameterizedWebTypeValidation) {
    auto jsonType = registry->getType("Json");
    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "WebList",
        std::vector<std::shared_ptr<pryst::Type>>{jsonType}
    );

    ASSERT_TRUE(typeValidation->validateWebType(listType));
    auto inferredType = typeInference->inferWebType(listType);
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(inferredType) != nullptr);
}
