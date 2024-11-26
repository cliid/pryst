#include <gtest/gtest.h>
#include "type_checker.hpp"
#include "type.hpp"
#include "type_registry.hpp"

namespace pryst {
namespace test {

class FunctionTypeTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_shared<TypeRegistry>();
        checker = std::make_unique<TypeChecker>(registry);
    }

    std::shared_ptr<TypeRegistry> registry;
    std::unique_ptr<TypeChecker> checker;
};

TEST_F(FunctionTypeTest, BasicFunctionTypeCheck) {
    // Test basic function type with single parameter
    auto intType = std::make_shared<PrimitiveType>("Int");
    auto boolType = std::make_shared<PrimitiveType>("Bool");

    auto funcType = std::make_shared<FunctionType>(
        std::vector<std::shared_ptr<Type>>{intType},
        boolType
    );

    EXPECT_TRUE(funcType->isFunction());
    EXPECT_EQ(funcType->getParameterTypes().size(), 1);
    EXPECT_EQ(funcType->getReturnType()->toString(), "Bool");
}

TEST_F(FunctionTypeTest, FunctionTypeCompatibility) {
    // Test function type compatibility checks
    auto intType = std::make_shared<PrimitiveType>("Int");
    auto floatType = std::make_shared<PrimitiveType>("Float");
    auto boolType = std::make_shared<PrimitiveType>("Bool");

    auto func1 = std::make_shared<FunctionType>(
        std::vector<std::shared_ptr<Type>>{intType},
        boolType
    );

    auto func2 = std::make_shared<FunctionType>(
        std::vector<std::shared_ptr<Type>>{floatType},
        boolType
    );

    EXPECT_FALSE(checker->areTypesCompatible(func1, func2));
}

TEST_F(FunctionTypeTest, FunctionOverloadResolution) {
    // Test function overload resolution
    auto intType = std::make_shared<PrimitiveType>("Int");
    auto floatType = std::make_shared<PrimitiveType>("Float");
    auto boolType = std::make_shared<PrimitiveType>("Bool");

    auto func1 = std::make_shared<FunctionType>(
        std::vector<std::shared_ptr<Type>>{intType},
        boolType
    );

    auto func2 = std::make_shared<FunctionType>(
        std::vector<std::shared_ptr<Type>>{floatType},
        boolType
    );

    registry->registerType("func1", func1);
    registry->registerType("func2", func2);

    checker->pushScope();  // Create a new scope for the functions
    checker->declareVariable("func1", func1);  // Register in scope manager
    checker->declareVariable("func2", func2);  // Register in scope manager

    // Test overload resolution with exact match
    auto resolvedType = checker->resolveOverload(
        "func1",
        std::vector<std::shared_ptr<Type>>{intType}
    );

    // Compare with the return type of func1, not the full function type
    EXPECT_EQ(resolvedType->toString(), func1->getReturnType()->toString());
    checker->popScope();
}

TEST_F(FunctionTypeTest, GenericFunctionTypes) {
    // Test generic function types
    auto genericT = std::make_shared<GenericType>("T");
    auto genericU = std::make_shared<GenericType>("U");

    auto genericFunc = std::make_shared<FunctionType>(
        std::vector<std::shared_ptr<Type>>{genericT},
        genericU
    );

    EXPECT_TRUE(genericFunc->isFunction());
    EXPECT_TRUE(genericFunc->getParameterTypes()[0]->isClass());
    EXPECT_TRUE(genericFunc->getReturnType()->isClass());
}

} // namespace test
} // namespace pryst
