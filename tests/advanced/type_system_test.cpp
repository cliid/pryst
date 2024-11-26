#include <gtest/gtest.h>
#include "type_system/advanced/inference/type_inference_advanced.hpp"
#include "type_system/advanced/validation/type_validation.hpp"
#include "error_handling/advanced/chain/error_chain_advanced.hpp"
#include "error_handling/advanced/propagation/error_propagation.hpp"
#include "error_handling/advanced/transformation/error_transform.hpp"
#include "type_registry.hpp"
#include "type_system/advanced/types/advanced_types.hpp"

using std::shared_ptr;
using std::vector;
using std::string;
using std::make_shared;
using namespace pryst::core;
using namespace pryst::type_system::advanced;

class AdvancedTypeSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = make_shared<TypeRegistry>();
        inference = make_shared<TypeInference>(registry);
        validation = make_shared<TypeValidation>(registry);
        errorTransform = make_shared<ErrorTransform>(registry);
        errorPropagation = make_shared<ErrorPropagation>(registry);
    }

    shared_ptr<TypeRegistry> registry;
    shared_ptr<TypeInference> inference;
    shared_ptr<TypeValidation> validation;
    shared_ptr<ErrorTransform> errorTransform;
    shared_ptr<ErrorPropagation> errorPropagation;
};

TEST_F(AdvancedTypeSystemTest, TypeInferenceBasic) {
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();

    vector<shared_ptr<Type>> types = {intType, floatType};
    vector<string> ops = {"+"};

    auto result = inference->inferType(types, ops);
    ASSERT_TRUE(result->equals(floatType));
}

TEST_F(AdvancedTypeSystemTest, TypeValidationCompatibility) {
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();

    ASSERT_TRUE(validation->validateCompatibility(intType, floatType, true));
    ASSERT_FALSE(validation->validateCompatibility(floatType, intType, true));
}

TEST_F(AdvancedTypeSystemTest, ErrorTransformation) {
    auto sourceError = make_shared<ErrorType>("SourceError");
    auto targetError = make_shared<ErrorType>("TargetError");

    auto transformed = errorTransform->transformError(sourceError, targetError);
    ASSERT_TRUE(transformed->isError());
    ASSERT_TRUE(transformed->toString().find("SourceError") != string::npos);
    ASSERT_TRUE(transformed->toString().find("TargetError") != string::npos);
}

TEST_F(AdvancedTypeSystemTest, ErrorPropagation) {
    auto sourceError = make_shared<ErrorType>("InitialError");
    vector<shared_ptr<Type>> propagationPath = {
        make_shared<ErrorType>("IntermediateError"),
        make_shared<ErrorType>("FinalError")
    };

    auto result = errorPropagation->propagateError(sourceError, propagationPath);
    ASSERT_TRUE(result->isError());
    ASSERT_EQ(result->toString(), "FinalError");
}

TEST_F(AdvancedTypeSystemTest, UnionTypeValidation) {
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();
    vector<shared_ptr<Type>> types = {intType, floatType};

    auto unionType = make_shared<UnionType>(types);
    ASSERT_TRUE(validation->validateCompatibility(intType, unionType, true));
    ASSERT_TRUE(validation->validateCompatibility(floatType, unionType, true));
}

TEST_F(AdvancedTypeSystemTest, IntersectionTypeValidation) {
    auto serializableType = make_shared<InterfaceType>("Serializable");
    auto comparableType = make_shared<InterfaceType>("Comparable");
    vector<shared_ptr<Type>> types = {serializableType, comparableType};

    auto intersectionType = make_shared<IntersectionType>(types);
    ASSERT_TRUE(validation->validateCompatibility(serializableType, intersectionType, true));
    ASSERT_TRUE(validation->validateCompatibility(comparableType, intersectionType, true));
}

TEST_F(AdvancedTypeSystemTest, ParameterizedTypeValidation) {
    auto intType = registry->getIntType();
    vector<shared_ptr<Type>> typeArgs1 = {intType};
    vector<shared_ptr<Type>> typeArgs2 = {intType};

    auto listType1 = make_shared<ParameterizedType>("List", typeArgs1);
    auto listType2 = make_shared<ParameterizedType>("List", typeArgs2);

    ASSERT_TRUE(validation->validateCompatibility(listType1, listType2, true));
}

TEST_F(AdvancedTypeSystemTest, HigherKindedTypeValidation) {
    vector<string> typeParams = {"T"};
    auto higherKindedType = make_shared<HigherKindedType>("Container", typeParams);

    ASSERT_TRUE(higherKindedType->getName() == "Container");
    ASSERT_TRUE(higherKindedType->getTypeParameters().size() == 1);
}
