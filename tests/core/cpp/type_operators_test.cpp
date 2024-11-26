#include <gtest/gtest.h>
#include "type_checker.hpp"
#include "type_info.hpp"
#include "types.hpp"
#include "runtime/runtime_registry.hpp"
#include <llvm/IR/Module.h>

class TypeOperatorsTest : public ::testing::Test {
protected:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    pryst::runtime::RuntimeRegistry runtimeRegistry;
    pryst::TypeRegistry typeRegistry;
    pryst::TypeChecker typeChecker;

    TypeOperatorsTest()
        : context(std::make_unique<llvm::LLVMContext>())
        , module(std::make_unique<llvm::Module>("test", *context))
        , runtimeRegistry(module.get())
        , typeRegistry(*context, runtimeRegistry)
        , typeChecker(*context, typeRegistry, runtimeRegistry)
    {}
};

TEST_F(TypeOperatorsTest, InstanceofBasicTypes) {
    // Test instanceof with primitive types
    auto intType = std::make_shared<pryst::PrimitiveType>(pryst::Type::Kind::Int);
    auto stringType = std::make_shared<pryst::PrimitiveType>(pryst::Type::Kind::String);

    EXPECT_TRUE(typeChecker.isAssignable(std::any(intType), std::any(intType)));
    EXPECT_FALSE(typeChecker.isAssignable(std::any(stringType), std::any(intType)));
}

TEST_F(TypeOperatorsTest, InstanceofNullableTypes) {
    // Test instanceof with nullable types
    auto intType = std::make_shared<pryst::PrimitiveType>(pryst::Type::Kind::Int);
    auto nullableIntType = std::make_shared<pryst::NullableType>(intType);

    EXPECT_TRUE(typeChecker.isAssignable(std::any(intType), std::any(nullableIntType)));
    EXPECT_TRUE(typeChecker.isAssignable(std::any(nullableIntType), std::any(nullableIntType)));
}

TEST_F(TypeOperatorsTest, TypeofBasicTypes) {
    // Test typeof with primitive types
    auto intType = std::make_shared<pryst::PrimitiveType>(pryst::Type::Kind::Int);
    auto typeInfo = std::make_shared<pryst::TypeInfo>(intType);

    EXPECT_EQ(typeInfo->getName(), "Int");
    EXPECT_TRUE(typeInfo->isPrimitive());
    EXPECT_FALSE(typeInfo->isNullable());
}

TEST_F(TypeOperatorsTest, TypeofNullableTypes) {
    // Test typeof with nullable types
    auto stringType = std::make_shared<pryst::PrimitiveType>(pryst::Type::Kind::String);
    auto nullableStringType = std::make_shared<pryst::NullableType>(stringType);
    auto typeInfo = std::make_shared<pryst::TypeInfo>(stringType, true);

    EXPECT_EQ(typeInfo->getName(), "String");
    EXPECT_TRUE(typeInfo->isPrimitive());
    EXPECT_TRUE(typeInfo->isNullable());
}

TEST_F(TypeOperatorsTest, TypeofComplexTypes) {
    // Test typeof with class and interface types
    auto classType = std::make_shared<pryst::ClassType>("MyClass");
    auto interfaceType = std::make_shared<pryst::InterfaceType>("MyInterface");

    auto classTypeInfo = std::make_shared<pryst::TypeInfo>(classType);
    auto interfaceTypeInfo = std::make_shared<pryst::TypeInfo>(interfaceType);

    EXPECT_TRUE(classTypeInfo->isClass());
    EXPECT_FALSE(classTypeInfo->isInterface());
    EXPECT_TRUE(interfaceTypeInfo->isInterface());
    EXPECT_FALSE(interfaceTypeInfo->isClass());
}
