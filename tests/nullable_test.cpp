#include <gtest/gtest.h>
#include "test_utils.hpp"
#include "../src/type_checker.hpp"
#include "../src/type_registry.hpp"
#include "../src/runtime/runtime_registry.hpp"
#include <llvm/IR/LLVMContext.h>

using namespace pryst;
using namespace pryst::testing;

class NullableTypeTest : public PrystTestFixture {
protected:
    void SetUp() override {
        PrystTestFixture::SetUp();  // Call base class setup
        // Additional setup if needed
    }
};

TEST_F(NullableTypeTest, TestNullableMethodCall) {
    // Test that nullable method calls require ?. operator
    const char* code = R"(
        class Test {
            fn method() -> int { return 42; }
        }
        let x: Test? = null;
        x.method();  // Should fail
    )";

    EXPECT_THROW({
        auto ast = pryst::testing::parseCode(code);
        compiler->getTypeChecker().visit(ast);
    }, Error);

    const char* validCode = R"(
        class Test {
            fn method() -> int { return 42; }
        }
        let x: Test? = null;
        x?.method();  // Should pass
    )";

    EXPECT_NO_THROW({
        auto ast = pryst::testing::parseCode(validCode);
        compiler->getTypeChecker().visit(ast);
    });
}

TEST_F(NullableTypeTest, TestNullCoalescing) {
    const char* code = R"(
        let x: int? = null;
        let y = x ?? 42;  // Should infer y as int
    )";

    EXPECT_NO_THROW({
        auto ast = pryst::testing::parseCode(code);
        compiler->getTypeChecker().visit(ast);
    });
}

TEST_F(NullableTypeTest, TestNullableChain) {
    const char* code = R"(
        class Inner {
            fn getValue() -> int { return 42; }
        }
        class Outer {
            let inner: Inner?;
        }
        let x: Outer? = null;
        let y = x?.inner?.getValue();  // Should infer y as int?
    )";

    EXPECT_NO_THROW({
        auto ast = pryst::testing::parseCode(code);
        compiler->getTypeChecker().visit(ast);
    });
}

TEST_F(NullableTypeTest, TestNullableTypeConversion) {
    const char* code = R"(
        class Base {
            fn method() -> int { return 42; }
        }
        class Derived extends Base {}
        let x: Derived? = null;
        let y: Base? = x;  // Should allow nullable upcasting
    )";

    EXPECT_NO_THROW({
        auto ast = pryst::testing::parseCode(code);
        compiler->getTypeChecker().visit(ast);
    });
}

TEST_F(NullableTypeTest, TestNullableFieldAccess) {
    const char* code = R"(
        class Test {
            let value: int;
        }
        let x: Test? = null;
        let y = x?.value;  // Should infer y as int?
    )";

    EXPECT_NO_THROW({
        auto ast = pryst::testing::parseCode(code);
        compiler->getTypeChecker().visit(ast);
    });
}

TEST_F(NullableTypeTest, TestNestedNullableTypes) {
    const char* code = R"(
        class Inner {
            let value: int?;
        }
        class Outer {
            let inner: Inner?;
        }
        let x: Outer? = null;
        let y = x?.inner?.value;  // Should infer y as int?
        let z = y ?? 42;  // Should infer z as int
    )";

    EXPECT_NO_THROW({
        auto ast = pryst::testing::parseCode(code);
        compiler->getTypeChecker().visit(ast);
    });
}
