#include <gtest/gtest.h>
#include "../src/types.hpp"
#include "../src/type_registry.hpp"
#include "test_utils.hpp"

using namespace pryst;
using namespace pryst::testing;

class NullableTypeTest : public PrystTestFixture {
protected:
    void SetUp() override {
        PrystTestFixture::SetUp();
    }
};

TEST_F(NullableTypeTest, TestNullTypeAssignment) {
    auto nullableInt = INT_TYPE->makeNullable();
    EXPECT_TRUE(NULL_TYPE->isAssignableTo(nullableInt));
    EXPECT_FALSE(NULL_TYPE->isAssignableTo(INT_TYPE));
}

TEST_F(NullableTypeTest, TestNullableTypeConversion) {
    auto nullableInt = INT_TYPE->makeNullable();
    auto nullableFloat = FLOAT_TYPE->makeNullable();

    EXPECT_TRUE(NULL_TYPE->canConvertTo(nullableInt));
    EXPECT_FALSE(nullableInt->canConvertTo(INT_TYPE));
    EXPECT_FALSE(nullableInt->canConvertTo(nullableFloat));
}

TEST_F(NullableTypeTest, TestMethodPropagation) {
    auto nullableString = STRING_TYPE->makeNullable();
    auto lengthMethod = nullableString->getMethod("length");
    EXPECT_TRUE(lengthMethod != nullptr);
    EXPECT_TRUE(lengthMethod->isNullable());
}

TEST_F(NullableTypeTest, TestToString) {
    auto nullableInt = INT_TYPE->makeNullable();
    EXPECT_EQ(nullableInt->toString(), "int?");
    EXPECT_EQ(NULL_TYPE->toString(), "null");
}

TEST_F(NullableTypeTest, TestIsInstanceOf) {
    auto nullableInt = INT_TYPE->makeNullable();
    EXPECT_TRUE(nullableInt->isInstanceOf(INT_TYPE));
    EXPECT_TRUE(NULL_TYPE->isInstanceOf(nullableInt));
}

// Add tests that actually compile and run code
TEST_F(NullableTypeTest, TestNullableVariableDeclaration) {
    EXPECT_TRUE(compileCode(R"(
        let x: int? = null;
        let y: int? = 42;
    )"));
}

TEST_F(NullableTypeTest, TestNullableMethodCall) {
    EXPECT_TRUE(compileCode(R"(
        let s: str? = "hello";
        let len: int? = s?.length();
    )"));
}

TEST_F(NullableTypeTest, TestNullCoalescing) {
    EXPECT_TRUE(compileCode(R"(
        let x: int? = null;
        let y: int = x ?? 0;
        let s: str? = null;
        let t: str = s ?? "default";
    )"));
}

TEST_F(NullableTypeTest, TestNullableChaining) {
    EXPECT_TRUE(compileCode(R"(
        class Container {
            let value: int?;
            let next: Container?;

            fn getValue() -> int? {
                return value;
            }

            fn getNext() -> Container? {
                return next;
            }
        }

        let container = new Container();
        container.next = new Container();
        let value = container?.next?.getValue();
    )"));
}
