#include <gtest/gtest.h>
#include "llvm_codegen.hpp"
#include "type_system/advanced/inference/type_inference_advanced.hpp"
#include "type_system/advanced/validation/type_validation.hpp"
#include "type_system/advanced/types/advanced_types.hpp"

class LLVMTypeIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();

        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>("test_module", *context);
        builder = std::make_unique<llvm::IRBuilder<>>(*context);

        registry = std::make_shared<pryst::TypeRegistry>();
        typeInference = std::make_shared<pryst::advanced::TypeInference>(registry);
        codeGen = std::make_shared<pryst::LLVMCodeGen>(context.get(), module.get(), builder.get());
    }

    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::shared_ptr<pryst::TypeRegistry> registry;
    std::shared_ptr<pryst::advanced::TypeInference> typeInference;
    std::shared_ptr<pryst::LLVMCodeGen> codeGen;
};

TEST_F(LLVMTypeIntegrationTest, InferredTypeLLVMGeneration) {
    // Test that inferred types generate correct LLVM types
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();

    std::vector<std::shared_ptr<pryst::Type>> types = {intType, floatType};
    std::vector<std::string> ops = {"+"};

    auto inferredType = typeInference->inferType(types, ops);
    auto llvmType = codeGen->getLLVMType(inferredType);

    ASSERT_TRUE(llvmType->isFloatTy());
}

TEST_F(LLVMTypeIntegrationTest, NullableTypeLLVMRepresentation) {
    // Test nullable type LLVM representation
    auto intType = registry->getIntType();
    auto nullableInt = std::make_shared<pryst::NullableType>(intType);

    auto llvmType = codeGen->getLLVMType(nullableInt);
    ASSERT_TRUE(llvmType->isStructTy());

    auto structType = llvm::dyn_cast<llvm::StructType>(llvmType);
    ASSERT_EQ(structType->getNumElements(), 2); // value and isNull flag
    ASSERT_TRUE(structType->getElementType(0)->isIntegerTy(32));
    ASSERT_TRUE(structType->getElementType(1)->isIntegerTy(1));
}

TEST_F(LLVMTypeIntegrationTest, FunctionTypeLLVMGeneration) {
    // Test function type LLVM generation
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();

    std::vector<std::shared_ptr<pryst::Type>> paramTypes = {intType, floatType};
    auto funcType = std::make_shared<pryst::FunctionType>(floatType, paramTypes);

    auto llvmType = codeGen->getLLVMType(funcType);
    ASSERT_TRUE(llvmType->isFunctionTy());

    auto functionType = llvm::dyn_cast<llvm::FunctionType>(llvmType);
    ASSERT_EQ(functionType->getNumParams(), 2);
    ASSERT_TRUE(functionType->getReturnType()->isFloatTy());
}

TEST_F(LLVMTypeIntegrationTest, ErrorTypeLLVMHandling) {
    // Test error type LLVM representation
    auto errorType = std::make_shared<pryst::ErrorType>("TestError");
    auto llvmType = codeGen->getLLVMType(errorType);

    // Error types should be represented as tagged unions in LLVM
    ASSERT_TRUE(llvmType->isStructTy());
    auto structType = llvm::dyn_cast<llvm::StructType>(llvmType);

    // Tag + error message string
    ASSERT_EQ(structType->getNumElements(), 2);
    ASSERT_TRUE(structType->getElementType(0)->isIntegerTy(32)); // tag
    ASSERT_TRUE(structType->getElementType(1)->isPointerTy()); // error message
}

TEST_F(LLVMTypeIntegrationTest, UnionTypeLLVMGeneration) {
    auto intType = registry->getIntType();
    auto floatType = registry->getFloatType();
    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, floatType}
    );

    auto llvmType = codeGen->getLLVMType(unionType);
    ASSERT_TRUE(llvmType->isStructTy());

    auto structType = llvm::dyn_cast<llvm::StructType>(llvmType);
    ASSERT_EQ(structType->getNumElements(), 3); // tag + value + type info
    ASSERT_TRUE(structType->getElementType(0)->isIntegerTy(32)); // tag
}

TEST_F(LLVMTypeIntegrationTest, IntersectionTypeLLVMGeneration) {
    auto serializableType = std::make_shared<pryst::InterfaceType>("Serializable");
    auto comparableType = std::make_shared<pryst::InterfaceType>("Comparable");
    auto intersectionType = std::make_shared<pryst::advanced::IntersectionType>(
        std::vector<std::shared_ptr<pryst::Type>>{serializableType, comparableType}
    );

    auto llvmType = codeGen->getLLVMType(intersectionType);
    ASSERT_TRUE(llvmType->isStructTy());

    auto structType = llvm::dyn_cast<llvm::StructType>(llvmType);
    ASSERT_GE(structType->getNumElements(), 2); // vtables for each interface
}

TEST_F(LLVMTypeIntegrationTest, ParameterizedTypeLLVMGeneration) {
    auto intType = registry->getIntType();
    auto paramType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    auto llvmType = codeGen->getLLVMType(paramType);
    ASSERT_TRUE(llvmType->isStructTy());

    auto structType = llvm::dyn_cast<llvm::StructType>(llvmType);
    ASSERT_GE(structType->getNumElements(), 1); // at least data storage
}

TEST_F(LLVMTypeIntegrationTest, ComplexTypeHierarchyLLVMGeneration) {
    // Test complex nested type hierarchy LLVM generation
    auto intType = registry->getIntType();
    auto stringType = registry->getStringType();

    // Create a parameterized list of union types
    auto unionType = std::make_shared<pryst::advanced::UnionType>(
        std::vector<std::shared_ptr<pryst::Type>>{intType, stringType}
    );

    auto listType = std::make_shared<pryst::advanced::ParameterizedType>(
        "List",
        std::vector<std::shared_ptr<pryst::Type>>{unionType}
    );

    auto llvmType = codeGen->getLLVMType(listType);
    ASSERT_TRUE(llvmType->isStructTy());

    auto structType = llvm::dyn_cast<llvm::StructType>(llvmType);
    ASSERT_GE(structType->getNumElements(), 3); // size, capacity, data array

    // Verify the data array element type is a union type struct
    auto arrayType = structType->getElementType(2);
    ASSERT_TRUE(arrayType->isPointerTy());
    auto elementType = arrayType->getPointerElementType();
    ASSERT_TRUE(elementType->isStructTy());
}

TEST_F(LLVMTypeIntegrationTest, RecursiveTypeLLVMGeneration) {
    // Test recursive type LLVM generation (e.g., linked list)
    auto intType = registry->getIntType();
    auto nodeType = std::make_shared<pryst::advanced::ParameterizedType>(
        "Node",
        std::vector<std::shared_ptr<pryst::Type>>{intType}
    );

    auto llvmType = codeGen->getLLVMType(nodeType);
    ASSERT_TRUE(llvmType->isStructTy());

    auto structType = llvm::dyn_cast<llvm::StructType>(llvmType);
    ASSERT_GE(structType->getNumElements(), 2); // data + next pointer
    ASSERT_TRUE(structType->getElementType(1)->isPointerTy()); // next pointer
}
