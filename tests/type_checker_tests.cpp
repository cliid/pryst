#include <gtest/gtest.h>
#include "../src/type_checker.hpp"
#include "../src/error.hpp"
#include <antlr4-runtime.h>
#include "../src/generated/PrystLexer.h"
#include "../src/generated/PrystParser.h"
#include "test_utils.hpp"
#include "test_type_checker.hpp"

// Avoid LLVM namespace conflicts
#include <llvm/Support/Error.h>
namespace llvm { }

using namespace antlr4;
using namespace pryst::testing;

namespace pryst {
namespace test {

class TypeCheckerTest : public PrystTestFixture {
protected:
    std::shared_ptr<Type> checkExpression(const std::string& code) {
        ANTLRInputStream input(code);
        PrystLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        PrystParser parser(&tokens);
        auto expr = parser.expression();
        return std::any_cast<std::shared_ptr<Type>>(compiler->getTypeChecker().visit(expr));
    }
};

TEST_F(TypeCheckerTest, EqualityExpressionTest) {
    // Test primitive type equality
    EXPECT_NO_THROW(checkExpression("42 == 42"));
    EXPECT_NO_THROW(checkExpression("42 != 42"));
    EXPECT_NO_THROW(checkExpression("3.14 == 3.14"));
    EXPECT_NO_THROW(checkExpression("true == false"));
    EXPECT_NO_THROW(checkExpression("\"hello\" == \"world\""));

    // Test nullable type equality
    EXPECT_NO_THROW(checkExpression("null == null"));

    // Test incompatible type comparison
    EXPECT_THROW(checkExpression("42 == \"42\""), Error);
    EXPECT_THROW(checkExpression("true == 1"), Error);
}

TEST_F(TypeCheckerTest, NullableTypeEqualityTest) {
    auto& typeChecker = static_cast<testing::TestTypeChecker&>(compiler->getTypeChecker());

    typeChecker.testPushScope();
    typeChecker.testDeclareVariable("nullableInt", std::make_shared<NullableType>(INT_TYPE));
    typeChecker.testDeclareVariable("nullableStr", std::make_shared<NullableType>(STRING_TYPE));

    EXPECT_NO_THROW(checkExpression("nullableInt == null"));
    EXPECT_NO_THROW(checkExpression("nullableStr == null"));
    EXPECT_NO_THROW(checkExpression("nullableInt == 42"));
    EXPECT_NO_THROW(checkExpression("nullableStr == \"hello\""));

    EXPECT_THROW(checkExpression("nullableInt == \"42\""), Error);
    EXPECT_THROW(checkExpression("nullableStr == 42"), Error);

    typeChecker.testPopScope();
}

TEST_F(TypeCheckerTest, ClassTypeEqualityTest) {
    auto& registry = getRegistry();
    auto& typeChecker = static_cast<testing::TestTypeChecker&>(compiler->getTypeChecker());

    // Register test classes and interfaces
    auto baseClass = std::make_shared<ClassType>("BaseClass", std::vector<std::shared_ptr<Type>>{});
    auto derivedClass = std::make_shared<ClassType>("DerivedClass", std::vector<std::shared_ptr<Type>>{}, baseClass);
    auto interface = std::make_shared<InterfaceType>("TestInterface");
    auto implementingClass = std::make_shared<ClassType>("ImplementingClass", std::vector<std::shared_ptr<Type>>{});

    // Register with empty member lists initially
    registry.registerClass("BaseClass", std::vector<std::pair<std::string, llvm::Type*>>{});
    registry.registerClass("DerivedClass", std::vector<std::pair<std::string, llvm::Type*>>{});
    registry.registerInterfaceType(interface);
    registry.registerClass("ImplementingClass", std::vector<std::pair<std::string, llvm::Type*>>{});
    registry.registerInterfaceImplementation("ImplementingClass", "TestInterface");

    // Register inheritance relationship
    registry.registerInheritance("DerivedClass", "BaseClass");

    typeChecker.testPushScope();
    // Base class variables
    typeChecker.testDeclareVariable("base1", baseClass);
    typeChecker.testDeclareVariable("base2", baseClass);
    typeChecker.testDeclareVariable("nullableBase", std::make_shared<NullableType>(baseClass));

    // Derived class variables
    typeChecker.testDeclareVariable("derived1", derivedClass);
    typeChecker.testDeclareVariable("derived2", derivedClass);
    typeChecker.testDeclareVariable("nullableDerived", std::make_shared<NullableType>(derivedClass));

    // Interface implementing class variables
    typeChecker.testDeclareVariable("impl1", implementingClass);
    typeChecker.testDeclareVariable("impl2", implementingClass);

    // Test class hierarchy comparisons
    EXPECT_NO_THROW(checkExpression("base1 == base2"));
    EXPECT_NO_THROW(checkExpression("derived1 == derived2"));
    EXPECT_NO_THROW(checkExpression("base1 == derived1")); // Derived can be compared with base
    EXPECT_NO_THROW(checkExpression("derived1 == base1")); // Base can be compared with derived

    // Test nullable class comparisons
    EXPECT_NO_THROW(checkExpression("nullableBase == null"));
    EXPECT_NO_THROW(checkExpression("nullableDerived == null"));
    EXPECT_NO_THROW(checkExpression("nullableBase == base1"));
    EXPECT_NO_THROW(checkExpression("nullableDerived == derived1"));
    EXPECT_NO_THROW(checkExpression("nullableBase == derived1")); // Nullable base can compare with derived

    // Test interface implementation comparisons
    EXPECT_NO_THROW(checkExpression("impl1 == impl2"));

    // Test invalid comparisons
    EXPECT_THROW(checkExpression("base1 == 42"), Error);
    EXPECT_THROW(checkExpression("derived1 == \"test\""), Error);
    EXPECT_THROW(checkExpression("impl1 == base1"), Error); // Different class hierarchies

    typeChecker.testPopScope();
}

TEST_F(TypeCheckerTest, InterfaceTypeEqualityTest) {
    auto& registry = getRegistry();
    auto& typeChecker = static_cast<testing::TestTypeChecker&>(compiler->getTypeChecker());

    auto interface1 = std::make_shared<InterfaceType>("Interface1");
    auto interface2 = std::make_shared<InterfaceType>("Interface2");
    auto implementingClass = std::make_shared<ClassType>("ImplementingClass", std::vector<std::shared_ptr<Type>>{});

    registry.registerInterfaceType(interface1);
    registry.registerInterfaceType(interface2);
    registry.registerClass("ImplementingClass", std::vector<std::pair<std::string, llvm::Type*>>{});
    registry.registerInterfaceImplementation("ImplementingClass", "Interface1");
    registry.registerInterfaceImplementation("ImplementingClass", "Interface2");

    typeChecker.testPushScope();
    typeChecker.testDeclareVariable("impl", implementingClass);
    typeChecker.testDeclareVariable("nullableImpl", std::make_shared<NullableType>(implementingClass));

    // Test interface implementation comparisons
    EXPECT_NO_THROW(checkExpression("impl == impl"));
    EXPECT_NO_THROW(checkExpression("nullableImpl == null"));
    EXPECT_NO_THROW(checkExpression("nullableImpl == impl"));

    typeChecker.testPopScope();
}

TEST_F(TypeCheckerTest, FunctionParameterOrderingTest) {
    auto& typeChecker = static_cast<testing::TestTypeChecker&>(compiler->getTypeChecker());

    // Valid function declarations with proper parameter ordering
    EXPECT_NO_THROW(compiler->compile(R"(
        str greet(str name, str title = "Mr.") { return "${title} ${name}"; }
        int sum(int a, int b, int? c = null) { return c == null ? a + b : a + b + c; }
    )"));

    // Invalid function declarations with wrong parameter ordering
    EXPECT_THROW(compiler->compile(R"(
        str greet(str name = "John", str title) { return "${title} ${name}"; }
    )"), Error);

    EXPECT_THROW(compiler->compile(R"(
        int calculate(int a = 1, int b) { return a + b; }
    )"), Error);

    // Test nullable default parameters
    EXPECT_NO_THROW(compiler->compile(R"(
        str? getMiddleName(str first, str last, str? middle = null) { return middle; }
    )"));

    // Test multiple default parameters
    EXPECT_NO_THROW(compiler->compile(R"(
        str formatName(str first, str? middle = null, str? title = null) {
            return "${title ?? ""} ${first} ${middle ?? ""}";
        }
    )"));
}

} // namespace test
} // namespace pryst
