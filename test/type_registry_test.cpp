#include "../src/codegen/type_registry.hpp"
#include "../src/semantic/basic_type_info.hpp"
#include <gtest/gtest.h>

namespace pryst {
namespace test {

class TypeRegistryTest : public ::testing::Test {
protected:
    llvm::LLVMContext context;
    TypeRegistry registry{context};
};

TEST_F(TypeRegistryTest, BasicTypeRegistration) {
    EXPECT_TRUE(registry.getLLVMType("int") != nullptr);
    EXPECT_TRUE(registry.getLLVMType("bool") != nullptr);
    EXPECT_TRUE(registry.getLLVMType("float") != nullptr);
    EXPECT_TRUE(registry.getLLVMType("str") != nullptr);
}

TEST_F(TypeRegistryTest, NamespaceRegistration) {
    registry.registerNamespace("pryst::web");
    EXPECT_TRUE(registry.isNamespaceRegistered("pryst::web"));

    registry.setCurrentNamespace("pryst::web");
    EXPECT_EQ(registry.getCurrentNamespace(), "pryst::web");
}

TEST_F(TypeRegistryTest, TypeRegistrationWithNamespace) {
    registry.registerNamespace("pryst::web");

    auto requestType = std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Class,
        "Request",
        registry.getVoidType()  // Placeholder type for testing
    );

    registry.registerType("pryst::web::Request", requestType);
    EXPECT_TRUE(registry.isTypeAvailableInScope("pryst::web::Request"));

    registry.setCurrentNamespace("pryst::web");
    EXPECT_TRUE(registry.isTypeAvailableInScope("Request"));
}

TEST_F(TypeRegistryTest, UsingDeclarations) {
    registry.registerNamespace("pryst::web");

    auto requestType = std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Class,
        "Request",
        registry.getVoidType()
    );

    registry.registerType("pryst::web::Request", requestType);
    registry.addUsingDeclaration("pryst::web::Request");

    EXPECT_TRUE(registry.isTypeAvailableInScope("Request"));
}

TEST_F(TypeRegistryTest, UsingNamespace) {
    registry.registerNamespace("pryst::web");

    auto requestType = std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Class,
        "Request",
        registry.getVoidType()
    );

    auto responseType = std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Class,
        "Response",
        registry.getVoidType()
    );

    registry.registerType("pryst::web::Request", requestType);
    registry.registerType("pryst::web::Response", responseType);

    registry.addUsingNamespace("pryst::web");

    EXPECT_TRUE(registry.isTypeAvailableInScope("Request"));
    EXPECT_TRUE(registry.isTypeAvailableInScope("Response"));
}

TEST_F(TypeRegistryTest, NestedNamespaceResolution) {
    registry.registerNamespace("pryst::web::http");

    auto requestType = std::make_shared<BasicTypeInfo>(
        BasicTypeInfo::BasicKind::Class,
        "Request",
        registry.getVoidType()
    );

    registry.registerType("pryst::web::http::Request", requestType);

    registry.setCurrentNamespace("pryst::web::http");
    EXPECT_TRUE(registry.isTypeAvailableInScope("Request"));

    registry.setCurrentNamespace("");
    EXPECT_TRUE(registry.isTypeAvailableInScope("pryst::web::http::Request"));
}

} // namespace test
} // namespace pryst
