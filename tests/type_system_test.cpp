#include <gtest/gtest.h>
#include "../src/types.hpp"

using namespace pryst::core;

class TypeSystemTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(TypeSystemTest, UnionTypeBasics) {
    auto intType = std::make_shared<PrimitiveType>(Type::Kind::Int);
    auto stringType = std::make_shared<PrimitiveType>(Type::Kind::String);
    auto unionType = intType->makeUnion(stringType);

    EXPECT_TRUE(unionType->isUnion());
    EXPECT_TRUE(intType->isInstanceOf(unionType));
    EXPECT_TRUE(stringType->isInstanceOf(unionType));
}

TEST_F(TypeSystemTest, IntersectionTypeBasics) {
    auto printableType = std::make_shared<InterfaceType>("Printable");
    auto serializableType = std::make_shared<InterfaceType>("Serializable");
    auto intersectionType = printableType->makeIntersection(serializableType);

    EXPECT_TRUE(intersectionType->isIntersection());

    // Create a class that implements both interfaces
    auto myClass = std::make_shared<ClassType>("MyClass",
        std::vector<std::shared_ptr<Type>>{},
        nullptr,
        std::vector<std::shared_ptr<InterfaceType>>{printableType, serializableType});

    EXPECT_TRUE(myClass->isInstanceOf(intersectionType));
}

TEST_F(TypeSystemTest, GenericConstraints) {
    auto numberType = std::make_shared<PrimitiveType>(Type::Kind::Int);
    auto stringType = std::make_shared<PrimitiveType>(Type::Kind::String);

    // T extends (Number | String)
    auto unionConstraint = numberType->makeUnion(stringType);
    auto genericType = std::make_shared<GenericType>("T", unionConstraint);

    EXPECT_TRUE(numberType->isInstanceOf(genericType));
    EXPECT_TRUE(stringType->isInstanceOf(genericType));

    auto boolType = std::make_shared<PrimitiveType>(Type::Kind::Bool);
    EXPECT_FALSE(boolType->isInstanceOf(genericType));
}

TEST_F(TypeSystemTest, ComplexTypeComposition) {
    auto printableType = std::make_shared<InterfaceType>("Printable");
    auto serializableType = std::make_shared<InterfaceType>("Serializable");
    auto comparableType = std::make_shared<InterfaceType>("Comparable");

    // (Printable & Serializable) | Comparable
    auto intersectionType = printableType->makeIntersection(serializableType);
    auto complexType = intersectionType->makeUnion(comparableType);

    // Test class implementing Printable and Serializable
    auto myClass1 = std::make_shared<ClassType>("MyClass1",
        std::vector<std::shared_ptr<Type>>{},
        nullptr,
        std::vector<std::shared_ptr<InterfaceType>>{printableType, serializableType});

    // Test class implementing only Comparable
    auto myClass2 = std::make_shared<ClassType>("MyClass2",
        std::vector<std::shared_ptr<Type>>{},
        nullptr,
        std::vector<std::shared_ptr<InterfaceType>>{comparableType});

    EXPECT_TRUE(myClass1->isInstanceOf(complexType));
    EXPECT_TRUE(myClass2->isInstanceOf(complexType));
}

TEST_F(TypeSystemTest, NullableWithUnionType) {
    auto intType = std::make_shared<PrimitiveType>(Type::Kind::Int);
    auto stringType = std::make_shared<PrimitiveType>(Type::Kind::String);
    auto unionType = intType->makeUnion(stringType);
    auto nullableUnionType = unionType->makeNullable();

    EXPECT_TRUE(nullableUnionType->isNullable());
    EXPECT_TRUE(intType->isInstanceOf(nullableUnionType));
    EXPECT_TRUE(stringType->isInstanceOf(nullableUnionType));
}

TEST_F(TypeSystemTest, UnionTypeDistributivity) {
    auto intType = std::make_shared<PrimitiveType>(Type::Kind::Int);
    auto stringType = std::make_shared<PrimitiveType>(Type::Kind::String);
    auto boolType = std::make_shared<PrimitiveType>(Type::Kind::Bool);

    // Test (A | B) & C === (A & C) | (B & C)
    auto unionType = intType->makeUnion(stringType);
    auto intersectionWithUnion = unionType->makeIntersection(boolType);

    auto intAndBool = intType->makeIntersection(boolType);
    auto stringAndBool = stringType->makeIntersection(boolType);
    auto distributedType = intAndBool->makeUnion(stringAndBool);

    // Both types should accept the same set of values
    auto testClass = std::make_shared<ClassType>("TestClass",
        std::vector<std::shared_ptr<Type>>{},
        nullptr,
        std::vector<std::shared_ptr<InterfaceType>>{});

    EXPECT_EQ(testClass->isInstanceOf(intersectionWithUnion),
              testClass->isInstanceOf(distributedType));
}

TEST_F(TypeSystemTest, TypeNormalization) {
    auto intType = std::make_shared<PrimitiveType>(Type::Kind::Int);
    auto stringType = std::make_shared<PrimitiveType>(Type::Kind::String);

    // Test that A | A === A
    auto redundantUnion = intType->makeUnion(intType);
    EXPECT_TRUE(intType->isInstanceOf(redundantUnion));
    EXPECT_TRUE(redundantUnion->isInstanceOf(intType));

    // Test that (A | B) | A === A | B
    auto union1 = intType->makeUnion(stringType);
    auto redundantUnion2 = union1->makeUnion(intType);
    auto normalUnion = intType->makeUnion(stringType);

    EXPECT_TRUE(redundantUnion2->isInstanceOf(normalUnion));
    EXPECT_TRUE(normalUnion->isInstanceOf(redundantUnion2));
}
