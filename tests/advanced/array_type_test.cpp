#include "../include/type_checker.hpp"
#include "../type_system/advanced/type_registry.hpp"
#include <gtest/gtest.h>
#include <memory>

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;

namespace pryst {
namespace core {
namespace test {

class ArrayTypeTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("Boolean", std::make_shared<PrimitiveType>("Boolean"));
        registry->registerType("String", std::make_shared<PrimitiveType>("String"));
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(ArrayTypeTest, ArrayCreation) {
    auto intType = registry->getType("Int");
    auto arrayType = std::make_shared<ArrayType>(intType);

    EXPECT_TRUE(arrayType->isArray());
    EXPECT_EQ(arrayType->getElementType(), intType);
    EXPECT_EQ(arrayType->toString(), "Int[]");
}

TEST_F(ArrayTypeTest, ArrayTypeRegistration) {
    auto intType = registry->getType("Int");
    auto arrayType = std::make_shared<ArrayType>(intType);
    registry->registerType("Int[]", arrayType);

    auto retrievedType = registry->getType("Int[]");
    EXPECT_TRUE(retrievedType->isArray());
    EXPECT_EQ(retrievedType->toString(), "Int[]");
}

TEST_F(ArrayTypeTest, NestedArrayTypes) {
    auto intType = registry->getType("Int");
    auto innerArrayType = std::make_shared<ArrayType>(intType);
    auto outerArrayType = std::make_shared<ArrayType>(innerArrayType);

    EXPECT_TRUE(outerArrayType->isArray());
    EXPECT_TRUE(std::static_pointer_cast<ArrayType>(outerArrayType->getElementType())->isArray());
    EXPECT_EQ(outerArrayType->toString(), "Int[][]");
}

TEST_F(ArrayTypeTest, ArrayTypeCompatibility) {
    auto intType = registry->getType("Int");
    auto boolType = registry->getType("Boolean");

    auto intArrayType = std::make_shared<ArrayType>(intType);
    auto boolArrayType = std::make_shared<ArrayType>(boolType);

    EXPECT_NE(intArrayType->toString(), boolArrayType->toString());
    EXPECT_NE(intArrayType->getElementType(), boolArrayType->getElementType());
}

TEST_F(ArrayTypeTest, NullableArrayType) {
    auto stringType = registry->getType("String");
    auto nullableStringType = std::make_shared<NullableType>("String");
    auto nullableArrayType = std::make_shared<ArrayType>(nullableStringType);

    EXPECT_TRUE(nullableArrayType->isArray());
    EXPECT_TRUE(nullableArrayType->getElementType()->isNullable());
    EXPECT_EQ(nullableArrayType->toString(), "String?[]");
}

} // namespace test
} // namespace core
} // namespace pryst
