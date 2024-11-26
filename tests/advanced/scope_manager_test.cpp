#include "scope_manager.hpp"
#include "type_registry.hpp"
#include "type.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace pryst {
namespace testing {

class ScopeManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        typeRegistry = std::make_shared<TypeRegistry>();
        // Register some error types
        typeRegistry->registerType("IOException", std::make_shared<ErrorType>("IOException"));
        typeRegistry->registerType("NetworkError", std::make_shared<ErrorType>("NetworkError"));
    }

    std::shared_ptr<TypeRegistry> typeRegistry;
};

TEST_F(ScopeManagerTest, BasicScopePushPop) {
    ScopeManager manager(typeRegistry);

    // Test initial state
    EXPECT_NO_THROW(manager.pushScope());
    EXPECT_NO_THROW(manager.popScope());

    // Test multiple push/pop operations
    EXPECT_NO_THROW(manager.pushScope());
    EXPECT_NO_THROW(manager.pushScope());
    EXPECT_NO_THROW(manager.popScope());
    EXPECT_NO_THROW(manager.popScope());
}

TEST_F(ScopeManagerTest, GenerateScopeReportWithTypeChanges) {
    ScopeManager manager(typeRegistry);

    // Push a few scopes and generate report
    manager.pushScope();
    manager.pushScope();

    std::string report = manager.generateScopeReport();
    EXPECT_FALSE(report.empty());
    EXPECT_NE(report.find("Scope Report"), std::string::npos);
}

TEST_F(ScopeManagerTest, GetVisibilityChanges) {
    ScopeManager manager(typeRegistry);

    // Push scopes and check visibility changes
    manager.pushScope();
    manager.pushScope();

    auto changes = manager.getVisibilityChanges();
    EXPECT_TRUE(changes.empty()); // Initially empty as no variables added
}

TEST_F(ScopeManagerTest, VariableDeclarationAndLookup) {
    ScopeManager manager(typeRegistry);
    auto ioError = std::make_shared<ErrorType>("IOException");

    // Test variable declaration
    EXPECT_NO_THROW(manager.declareVariable("handler", ioError));

    // Test variable lookup
    auto type = manager.lookupVariable("handler");
    EXPECT_TRUE(type->isError());
    EXPECT_EQ(type->toString(), "IOException");

    // Test variable shadowing
    manager.pushScope();
    auto netError = std::make_shared<ErrorType>("NetworkError");
    EXPECT_NO_THROW(manager.declareVariable("handler", netError));

    // Verify shadowed variable
    type = manager.lookupVariable("handler");
    EXPECT_EQ(type->toString(), "NetworkError");

    // Pop scope and verify original variable
    manager.popScope();
    type = manager.lookupVariable("handler");
    EXPECT_EQ(type->toString(), "IOException");
}

TEST_F(ScopeManagerTest, ErrorTypeHandling) {
    ScopeManager manager(typeRegistry);

    // Test error type recognition
    auto ioError = std::make_shared<ErrorType>("IOException");
    auto netError = std::make_shared<ErrorType>("NetworkError");

    EXPECT_TRUE(typeRegistry->isErrorType("IOException"));
    EXPECT_TRUE(typeRegistry->isErrorType("NetworkError"));

    // Test error handling changes tracking
    manager.pushScope();
    auto changes = manager.getErrorHandlingChanges();
    EXPECT_TRUE(changes.empty());
}

TEST_F(ScopeManagerTest, DetailedScopeReport) {
    ScopeManager manager(typeRegistry);

    manager.pushScope();
    std::string report = manager.generateScopeReport();

    EXPECT_FALSE(report.empty());
    EXPECT_NE(report.find("Scope Report"), std::string::npos);
    EXPECT_NE(report.find("============="), std::string::npos);
}

TEST_F(ScopeManagerTest, ErrorHandlingScenarios) {
    ScopeManager manager(typeRegistry);

    // Test popping global scope
    EXPECT_THROW(manager.popScope(), Error);

    // Test looking up non-existent variable
    EXPECT_THROW(manager.lookupVariable("nonexistent"), Error);

    // Test scope depth handling
    manager.pushScope();
    manager.pushScope();
    EXPECT_NO_THROW(manager.popScope());
    EXPECT_NO_THROW(manager.popScope());
    EXPECT_THROW(manager.popScope(), Error);  // Should not be able to pop global scope

    // Test variable shadowing with error types
    auto ioError = std::make_shared<ErrorType>("IOException");
    auto netError = std::make_shared<ErrorType>("NetworkError");

    manager.pushScope();
    manager.declareVariable("error", ioError);
    manager.pushScope();
    manager.declareVariable("error", netError);

    auto changes = manager.getErrorHandlingChanges();
    EXPECT_EQ(changes.size(), 2);
}

TEST_F(ScopeManagerTest, VariableRedeclarationHandling) {
    ScopeManager manager(typeRegistry);
    auto ioError = std::make_shared<ErrorType>("IOException");
    auto netError = std::make_shared<ErrorType>("NetworkError");

    // First declaration should succeed
    EXPECT_NO_THROW(manager.declareVariable("error", ioError));

    // Redeclaration in same scope should throw
    EXPECT_THROW(manager.declareVariable("error", netError), Error);

    // Declaration in new scope should succeed (shadowing)
    manager.pushScope();
    EXPECT_NO_THROW(manager.declareVariable("error", netError));

    // Verify correct type in each scope
    auto type = manager.lookupVariable("error");
    EXPECT_EQ(type->toString(), "NetworkError");

    manager.popScope();
    type = manager.lookupVariable("error");
    EXPECT_EQ(type->toString(), "IOException");
}

} // namespace testing
} // namespace pryst
