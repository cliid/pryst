#include <gtest/gtest.h>
#include "type_system/advanced/inference/type_inference_advanced.hpp"
#include "type_system/advanced/validation/type_validation.hpp"
#include "llvm_codegen.hpp"
#include "type_registry.hpp"
#include "type_system/advanced/types/advanced_types.hpp"

using namespace pryst::advanced;

class TypeSystemIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<pryst::TypeRegistry>();
        inference = std::make_shared<TypeInference>(registry);
        validation = std::make_shared<TypeValidation>(registry);
        codegen = std::make_shared<pryst::LLVMCodegen>();
    }

    std::shared_ptr<pryst::TypeRegistry> registry;
    std::shared_ptr<TypeInference> inference;
    std::shared_ptr<TypeValidation> validation;
    std::shared_ptr<pryst::LLVMCodegen> codegen;
};

TEST_F(TypeSystemIntegrationTest, InferredTypeToLLVM) {
    // Test that inferred types correctly map to LLVM types
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();

    std::vector<std::shared_ptr<pryst::Type>> types = {intType, floatType};
    std::vector<std::string> ops = {"+"};

    auto inferredType = inference->inferType(types, ops);
    ASSERT_TRUE(inferredType->equals(floatType));

    // Verify LLVM type generation
    auto llvmType = codegen->getLLVMType(inferredType);
    ASSERT_TRUE(llvmType->isFloatTy());
}

TEST_F(TypeSystemIntegrationTest, NullableTypeHandling) {
    // Test nullable type handling in LLVM codegen
    auto intType = registry->getIntType();
    auto nullableInt = std::make_shared<pryst::NullableType>(intType);

    ASSERT_TRUE(validation->validateCompatibility(intType, nullableInt, true));

    // Verify LLVM struct type for nullable
    auto llvmType = codegen->getLLVMType(nullableInt);
    ASSERT_TRUE(llvmType->isStructTy());
}

TEST_F(TypeSystemIntegrationTest, ComplexTypeInferenceWithUnions) {
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();
    auto stringType = registry->getStringType();

    auto numericUnion = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, floatType}
    );
    auto stringNumUnion = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{stringType, numericUnion}
    );

    // Test inference with nested union types
    auto inferredType = inference->inferBinaryOperation(
        numericUnion, stringNumUnion, "+"
    );
    ASSERT_TRUE(inferredType->equals(stringNumUnion));
    ASSERT_TRUE(validation->validateType(inferredType));
}

TEST_F(TypeSystemIntegrationTest, TypeInferenceWithConstraints) {
    auto comparableType = std::make_shared<pryst::InterfaceType>("Comparable");
    auto typeParam = std::make_shared<pryst::TypeParameter>("T", comparableType);
    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{typeParam}
    );

    // Test inference with type parameter constraints
    auto inferredType = inference->inferGenericType(listType, registry->getIntType());
    ASSERT_TRUE(validation->validateType(inferredType));
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(inferredType) != nullptr);
}

TEST_F(TypeSystemIntegrationTest, HigherKindedTypeInference) {
    auto typeParam = std::make_shared<pryst::TypeParameter>("T");
    auto higherKindedType = std::make_shared<pryst::advanced::HigherKindedType>(
        "Functor",
        std::vector<std::shared_ptr<pryst::Type>>{typeParam}
    );

    auto intType = registry->getIntType();
    auto inferredType = inference->inferHigherKindedType(
        higherKindedType,
        intType
    );

    ASSERT_TRUE(validation->validateType(inferredType));
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::HigherKindedType>(inferredType) != nullptr);
}

TEST_F(TypeSystemIntegrationTest, MonadicTypeInference) {
    auto typeParam = std::make_shared<pryst::TypeParameter>("T");
    auto monadType = std::make_shared<pryst::advanced::HigherKindedType>(
        "Monad",
        std::vector<std::shared_ptr<pryst::Type>>{typeParam}
    );

    auto intType = registry->getIntType();
    auto inferredType = inference->inferMonadicOperation(
        monadType,
        intType,
        "bind"
    );

    ASSERT_TRUE(validation->validateType(inferredType));
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::HigherKindedType>(inferredType) != nullptr);
}

    // Test inference with type parameter constraints
    auto inferredType = inference->inferGenericType(listType, registry->getIntType());
    ASSERT_TRUE(validation->validateType(inferredType));
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(inferredType) != nullptr);
}

TEST_F(TypeSystemIntegrationTest, IntersectionTypeInference) {
    auto serializableType = std::make_shared<pryst::InterfaceType>("Serializable");
    auto comparableType = std::make_shared<pryst::InterfaceType>("Comparable");
    auto intersectionType = std::make_shared<pryst::advanced::IntersectionType>(
        std::vector<std::shared_ptr<pryst::Type>>{serializableType, comparableType}
    );

    auto intType = registry->getIntType();
    auto inferredType = inference->inferMethodCall(
        intersectionType,
        "compareTo",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    ASSERT_TRUE(inferredType->equals(intType));
    ASSERT_TRUE(validation->validateType(inferredType));
}

TEST_F(TypeSystemIntegrationTest, RecursiveTypeInference) {
    auto intType = registry->getIntType();
    auto nodeType = std::make_shared<pryst::advanced::ParameterizedType>(
        "Node",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    auto inferredType = inference->inferRecursiveType(nodeType);
    ASSERT_TRUE(validation->validateType(inferredType));
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(inferredType) != nullptr);
}

    // Test inference with type parameter constraints
    auto inferredType = inference->inferGenericType(listType, registry->getIntType());
    ASSERT_TRUE(validation->validateType(inferredType));
    ASSERT_TRUE(std::dynamic_pointer_cast<pryst::advanced::ParameterizedType>(inferredType) != nullptr);
}

TEST_F(TypeSystemIntegrationTest, UnionTypeLLVMGeneration) {
    auto intType = registry->getIntType();
    auto stringType = registry->getStringType();
    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, stringType}
    );

    // Union types should be represented as tagged unions in LLVM
    auto llvmType = codegen->getLLVMType(unionType);
    ASSERT_TRUE(llvmType->isStructTy());
    ASSERT_TRUE(validation->validateType(unionType));
}

TEST_F(TypeSystemIntegrationTest, IntersectionTypeLLVMGeneration) {
    auto serializableType = std::make_shared<pryst::InterfaceType>("Serializable");
    auto comparableType = std::make_shared<pryst::InterfaceType>("Comparable");
    auto intersectionType = std::make_shared<pryst::advanced::IntersectionType>(
        std::vector<std::shared_ptr<pryst::Type>>{serializableType, comparableType}
    );

    // Intersection types should be represented as structs in LLVM
    auto llvmType = codegen->getLLVMType(intersectionType);
    ASSERT_TRUE(llvmType->isStructTy());
    ASSERT_TRUE(validation->validateIntersectionType(intersectionType));
}

TEST_F(TypeSystemIntegrationTest, ParameterizedTypeLLVMGeneration) {
    auto intType = registry->getIntType();
    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    // Parameterized types should generate appropriate container types in LLVM
    auto llvmType = codegen->getLLVMType(listType);
    ASSERT_TRUE(llvmType->isStructTy());
    ASSERT_TRUE(validation->validateParameterizedType(listType));
}
