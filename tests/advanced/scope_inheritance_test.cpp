#include "type_checker.hpp"
#include "scope_manager.hpp"
#include <gtest/gtest.h>

using namespace pryst;

class ScopeInheritanceTest : public ::testing::Test {
protected:
    ScopeInheritanceTest() : registry(std::make_shared<TypeRegistry>()), scopeManager(registry) {}

    void SetUp() override {
        registry->registerType("Int", std::make_shared<PrimitiveType>("Int"));
        registry->registerType("String", std::make_shared<PrimitiveType>("String"));
    }

    std::shared_ptr<TypeRegistry> registry;
    ScopeManager scopeManager;
};

TEST_F(ScopeInheritanceTest, VariableShadowing) {
    auto intType = registry->getType("Int");
    auto stringType = registry->getType("String");

    // Declare in outer scope
    scopeManager.declareVariable("x", intType);
    EXPECT_EQ(scopeManager.lookupVariable("x")->toString(), "Int");

    // Create inner scope and shadow
    scopeManager.pushScope();
    scopeManager.declareVariable("x", stringType);
    EXPECT_EQ(scopeManager.lookupVariable("x")->toString(), "String");

    // Pop back to outer scope
    scopeManager.popScope();
    EXPECT_EQ(scopeManager.lookupVariable("x")->toString(), "Int");
}

TEST_F(ScopeInheritanceTest, NestedScopeAccess) {
    auto intType = registry->getType("Int");

    scopeManager.declareVariable("outer", intType);
    scopeManager.pushScope();
    EXPECT_EQ(scopeManager.lookupVariable("outer")->toString(), "Int");

    scopeManager.declareVariable("inner", intType);
    scopeManager.pushScope();
    EXPECT_EQ(scopeManager.lookupVariable("outer")->toString(), "Int");
    EXPECT_EQ(scopeManager.lookupVariable("inner")->toString(), "Int");

    scopeManager.popScope();
    scopeManager.popScope();
}

TEST_F(ScopeInheritanceTest, ScopeIsolation) {
    auto intType = registry->getType("Int");

    scopeManager.pushScope();
    scopeManager.declareVariable("isolated", intType);
    scopeManager.popScope();

    EXPECT_THROW(scopeManager.lookupVariable("isolated"), std::runtime_error);
}
