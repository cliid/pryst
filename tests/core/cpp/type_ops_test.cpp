#include <gtest/gtest.h>
#include "compiler.hpp"
#include "runtime/runtime_type_ops.hpp"
#include "type_checker.hpp"
#include "error.hpp"
#include <antlr4-runtime.h>
#include "PrystLexer.h"
#include "PrystParser.h"

namespace pryst {
namespace test {

class TypeOpsTest : public ::testing::Test {
protected:
    void SetUp() override {
        compiler = std::make_unique<Compiler>();
    }

    antlr4::tree::ParseTree* parseCode(const std::string& code) {
        antlr4::ANTLRInputStream input(code);
        PrystLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        PrystParser parser(&tokens);
        return parser.program();
    }

    std::unique_ptr<Compiler> compiler;
};

TEST_F(TypeOpsTest, TestInstanceOf) {
    const char* code = R"(
        class Animal {
            string name;
        }
        class Dog extends Animal {
            void bark() {}
        }

        Dog dog = new Dog();
        print(dog instanceof Dog);    // Should print true
        print(dog instanceof Animal); // Should print true
        print(dog instanceof String); // Should print false
    )";

    ASSERT_NO_THROW(compiler->compile(parseCode(code)));
}

TEST_F(TypeOpsTest, TestTypeof) {
    const char* code = R"(
        int x = 42;
        print(typeof x);       // Should print "int"

        Dog? dog = new Dog();
        print(typeof dog);     // Should print "Dog?"

        print(typeof null);    // Should print "null"
    )";

    ASSERT_NO_THROW(compiler->compile(parseCode(code)));
}

TEST_F(TypeOpsTest, TestTypeofWithNullable) {
    const char* code = R"(
        String? nullableStr = null;
        print(typeof nullableStr);  // Should print "String?"

        nullableStr = "Hello";
        print(typeof nullableStr);  // Should still print "String?"
    )";

    ASSERT_NO_THROW(compiler->compile(parseCode(code)));
}

TEST_F(TypeOpsTest, TestInstanceOfInheritance) {
    const char* code = R"(
        class Animal { string name; }
        class Dog extends Animal { void bark() {} }
        class Cat extends Animal { void meow() {} }
        Dog dog = new Dog(); Cat cat = new Cat();
        print(dog instanceof Animal);  // true
        print(cat instanceof Animal);  // true
        print(dog instanceof Cat);     // false
    )";
    ASSERT_NO_THROW(compiler->compile(parseCode(code)));
}

TEST_F(TypeOpsTest, TestTypeofPrimitives) {
    const char* code = R"(
        int i = 42; float f = 3.14; bool b = true;
        print(typeof i); print(typeof f); print(typeof b);
    )";
    ASSERT_NO_THROW(compiler->compile(parseCode(code)));
}

TEST_F(TypeOpsTest, TestTypeofNullableArray) {
    const char* code = R"(
        int[]? nullableArray = null;
        print(typeof nullableArray);  // Should print "int[]?"
        nullableArray = [1, 2, 3];
        print(typeof nullableArray);  // Should still print "int[]?"

        String[]? nullableStrArray = ["hello", "world"];
        print(typeof nullableStrArray);  // Should print "String[]?"
        print(nullableStrArray instanceof String[]);  // Should print true
        print(nullableStrArray instanceof Object);    // Should print true
    )";
    ASSERT_NO_THROW(compiler->compile(parseCode(code)));
}

TEST_F(TypeOpsTest, TestInstanceOfWithNull) {
    const char* code = R"(
        class Animal { string name; }
        Animal? nullableAnimal = null;
        print(nullableAnimal instanceof Animal);  // Should print false
        print(nullableAnimal instanceof Object);  // Should print false

        nullableAnimal = new Animal();
        print(nullableAnimal instanceof Animal);  // Should print true
        print(nullableAnimal instanceof Object);  // Should print true
    )";
    ASSERT_NO_THROW(compiler->compile(parseCode(code)));
}

TEST_F(TypeOpsTest, TestTypeofWithNestedNullable) {
    const char* code = R"(
        Animal[]? nullableAnimalArray = [new Animal(), new Animal()];
        print(typeof nullableAnimalArray);  // Should print "Animal[]?"

        Map<String, Animal?>? nullableMap = null;
        print(typeof nullableMap);  // Should print "Map<String, Animal?>?"
    )";
    ASSERT_NO_THROW(compiler->compile(parseCode(code)));
}

} // namespace test
} // namespace pryst
