#include "../../../src/type_checker.hpp"
#include "../../../src/type_registry.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <llvm/IR/LLVMContext.h>

namespace pryst {
namespace testing {

class ArrayTypeTest : public ::testing::Test {
protected:
    void SetUp() override {
        context = std::make_unique<llvm::LLVMContext>();
        typeRegistry = std::make_unique<TypeRegistry>(*context);
        runtimeRegistry = std::make_unique<runtime::RuntimeRegistry>();
        typeChecker = std::make_unique<TypeChecker>(*context, *typeRegistry, *runtimeRegistry);
    }

    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<TypeRegistry> typeRegistry;
    std::unique_ptr<runtime::RuntimeRegistry> runtimeRegistry;
    std::unique_ptr<TypeChecker> typeChecker;
};

TEST_F(ArrayTypeTest, ArrayCreation) {
    auto arrayType = std::make_shared<ArrayType>(INT_TYPE);
    EXPECT_EQ(arrayType->getKind(), Type::Kind::Array);
    EXPECT_EQ(arrayType->getElementType(), INT_TYPE);
}

TEST_F(ArrayTypeTest, NestedArrayTypes) {
    auto innerArrayType = std::make_shared<ArrayType>(INT_TYPE);
    auto outerArrayType = std::make_shared<ArrayType>(innerArrayType);

    EXPECT_EQ(outerArrayType->getKind(), Type::Kind::Array);
    auto elementType = std::static_pointer_cast<ArrayType>(outerArrayType->getElementType());
    EXPECT_EQ(elementType->getKind(), Type::Kind::Array);
    EXPECT_EQ(elementType->getElementType(), INT_TYPE);
}

TEST_F(ArrayTypeTest, ArrayTypeCompatibility) {
    auto intArrayType = std::make_shared<ArrayType>(INT_TYPE);
    auto floatArrayType = std::make_shared<ArrayType>(FLOAT_TYPE);

    EXPECT_FALSE(intArrayType->isAssignableTo(floatArrayType));
    EXPECT_FALSE(floatArrayType->isAssignableTo(intArrayType));
}

TEST_F(ArrayTypeTest, NullableArrayType) {
    auto nullableIntType = INT_TYPE->makeNullable();
    auto nullableArrayType = std::make_shared<ArrayType>(nullableIntType);

    EXPECT_EQ(nullableArrayType->getKind(), Type::Kind::Array);
    EXPECT_TRUE(nullableArrayType->getElementType()->isNullable());
}

TEST_F(ArrayTypeTest, ArrayTypeConversion) {
    auto intArrayType = std::make_shared<ArrayType>(INT_TYPE);
    auto anyArrayType = std::make_shared<ArrayType>(ANY_TYPE);

    EXPECT_TRUE(intArrayType->canConvertTo(anyArrayType));
    EXPECT_FALSE(anyArrayType->canConvertTo(intArrayType));
}

TEST_F(ArrayTypeTest, ArrayTypeRegistration) {
    auto arrayType = std::make_shared<ArrayType>(INT_TYPE);
    typeRegistry->registerType("int[]", arrayType);

    auto retrievedType = typeRegistry->getType("int[]");
    EXPECT_EQ(retrievedType->getKind(), Type::Kind::Array);
    EXPECT_EQ(retrievedType->toString(), "int[]");
}

TEST_F(ArrayTypeTest, ArrayTypeStringRepresentation) {
    auto intArrayType = std::make_shared<ArrayType>(INT_TYPE);
    auto boolArrayType = std::make_shared<ArrayType>(BOOL_TYPE);
    auto nestedArrayType = std::make_shared<ArrayType>(intArrayType);

    EXPECT_EQ(intArrayType->toString(), "int[]");
    EXPECT_EQ(boolArrayType->toString(), "bool[]");
    EXPECT_EQ(nestedArrayType->toString(), "int[][]");
}

TEST_F(ArrayTypeTest, ArrayTypeMethodAccess) {
    auto arrayType = std::make_shared<ArrayType>(INT_TYPE);
    auto lengthMethod = arrayType->getMethod("length");
    EXPECT_NE(lengthMethod, nullptr);
    EXPECT_EQ(lengthMethod->getKind(), Type::Kind::Function);
}

TEST_F(ArrayTypeTest, ArrayTypeElementAccess) {
    auto arrayType = std::make_shared<ArrayType>(INT_TYPE);
    auto getMethod = arrayType->getMethod("get");
    auto setMethod = arrayType->getMethod("set");
    EXPECT_NE(getMethod, nullptr);
    EXPECT_NE(setMethod, nullptr);
}

TEST_F(ArrayTypeTest, ArrayTypeNullAssignment) {
    auto nullableArrayType = std::make_shared<ArrayType>(INT_TYPE)->makeNullable();
    EXPECT_TRUE(NULL_TYPE->isAssignableTo(nullableArrayType));
    EXPECT_TRUE(nullableArrayType->canBeNull());
}

} // namespace testing
} // namespace pryst
