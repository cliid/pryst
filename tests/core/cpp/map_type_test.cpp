#include <gtest/gtest.h>
#include "type_registry.hpp"
#include "type_checker.hpp"
#include "compiler.hpp"
#include <llvm/IR/LLVMContext.h>
#include <memory>

namespace pryst {
namespace test {

class MapTypeTest : public ::testing::Test {
protected:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<TypeRegistry> typeRegistry;
    std::unique_ptr<Compiler> compiler;

    void SetUp() override {
        context = std::make_unique<llvm::LLVMContext>();
        compiler = std::make_unique<Compiler>();
        typeRegistry = std::make_unique<TypeRegistry>(*context);
    }

    void TearDown() override {
        typeRegistry.reset();
        compiler.reset();
        context.reset();
    }
};

TEST_F(MapTypeTest, BasicMapTypeRegistration) {
    // Test basic map type registration
    auto mapType = typeRegistry->registerMapType("str", "int");
    ASSERT_TRUE(mapType != nullptr) << "Failed to register map<str,int>";

    // Verify the type is cached
    auto cachedType = typeRegistry->getCachedType("map<str,int>");
    ASSERT_TRUE(cachedType != nullptr) << "Failed to retrieve cached map<str,int>";
    ASSERT_EQ(mapType, cachedType) << "Cached type does not match registered type";
}

TEST_F(MapTypeTest, NestedMapTypeRegistration) {
    // Test nested map type registration
    auto innerMapType = typeRegistry->registerMapType("str", "int");
    ASSERT_TRUE(innerMapType != nullptr) << "Failed to register inner map<str,int>";

    auto outerMapType = typeRegistry->registerMapType("str", "map<str,int>");
    ASSERT_TRUE(outerMapType != nullptr) << "Failed to register map<str,map<str,int>>";

    // Verify nested type is cached correctly
    auto cachedType = typeRegistry->getCachedType("map<str,map<str,int>>");
    ASSERT_TRUE(cachedType != nullptr) << "Failed to retrieve cached map<str,map<str,int>>";
    ASSERT_EQ(outerMapType, cachedType) << "Cached nested type does not match registered type";
}

TEST_F(MapTypeTest, MapTypeWithArrays) {
    // Test map type with array value
    auto arrayType = typeRegistry->registerArrayType("int");
    ASSERT_TRUE(arrayType != nullptr) << "Failed to register int[]";

    auto mapType = typeRegistry->registerMapType("str", "int[]");
    ASSERT_TRUE(mapType != nullptr) << "Failed to register map<str,int[]>";

    // Verify complex type is cached correctly
    auto cachedType = typeRegistry->getCachedType("map<str,int[]>");
    ASSERT_TRUE(cachedType != nullptr) << "Failed to retrieve cached map<str,int[]>";
    ASSERT_EQ(mapType, cachedType) << "Cached array map type does not match registered type";
}

TEST_F(MapTypeTest, MapTypePreservesGenericParameters) {
    // Register various map types
    auto mapStrStr = typeRegistry->registerMapType("str", "str");
    auto mapIntInt = typeRegistry->registerMapType("int", "int");
    auto mapStrInt = typeRegistry->registerMapType("str", "int");

    // Verify each type is cached correctly and independently
    ASSERT_TRUE(typeRegistry->getCachedType("map<str,str>") != nullptr);
    ASSERT_TRUE(typeRegistry->getCachedType("map<int,int>") != nullptr);
    ASSERT_TRUE(typeRegistry->getCachedType("map<str,int>") != nullptr);

    // Verify types are distinct
    ASSERT_NE(typeRegistry->getCachedType("map<str,str>"), typeRegistry->getCachedType("map<int,int>"));
    ASSERT_NE(typeRegistry->getCachedType("map<str,str>"), typeRegistry->getCachedType("map<str,int>"));
    ASSERT_NE(typeRegistry->getCachedType("map<int,int>"), typeRegistry->getCachedType("map<str,int>"));
}

TEST_F(MapTypeTest, ComplexNestedTypes) {
    // Test complex nested type: map<str,map<int,str[]>[]>
    auto strArrayType = typeRegistry->registerArrayType("str");
    auto innerMapType = typeRegistry->registerMapType("int", "str[]");
    auto innerArrayType = typeRegistry->registerArrayType("map<int,str[]>");
    auto complexType = typeRegistry->registerMapType("str", "map<int,str[]>[]");

    ASSERT_TRUE(complexType != nullptr) << "Failed to register complex nested type";

    // Verify complex type is cached correctly
    auto cachedType = typeRegistry->getCachedType("map<str,map<int,str[]>[]>");
    ASSERT_TRUE(cachedType != nullptr) << "Failed to retrieve cached complex type";
    ASSERT_EQ(complexType, cachedType) << "Cached complex type does not match registered type";
}

} // namespace test
} // namespace pryst
