#include <gtest/gtest.h>
#include "type_checker.hpp"
#include "type.hpp"
#include "type_registry.hpp"

namespace pryst {
namespace testing {

class TypePromotionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Register primitive types
        typeRegistry_ = std::make_shared<TypeRegistry>();
        typeRegistry_->registerType("Int", std::make_shared<PrimitiveType>("Int", false));
        typeRegistry_->registerType("Float", std::make_shared<PrimitiveType>("Float", false));
        typeRegistry_->registerType("Double", std::make_shared<PrimitiveType>("Double", false));
        typeChecker_ = std::make_shared<TypeChecker>(typeRegistry_);
    }

    std::shared_ptr<TypeRegistry> typeRegistry_;
    std::shared_ptr<TypeChecker> typeChecker_;
};

TEST_F(TypePromotionTest, IntToFloatPromotion) {
    auto intType = typeRegistry_->getType("Int");
    auto floatType = typeRegistry_->getType("Float");

    auto result = typeChecker_->checkBinaryExpression(intType, "+", floatType);
    EXPECT_EQ(result->toString(), "Float");
}

TEST_F(TypePromotionTest, FloatToDoublePromotion) {
    auto floatType = typeRegistry_->getType("Float");
    auto doubleType = typeRegistry_->getType("Double");

    auto result = typeChecker_->checkBinaryExpression(floatType, "*", doubleType);
    EXPECT_EQ(result->toString(), "Double");
}

TEST_F(TypePromotionTest, IntToDoublePromotion) {
    auto intType = typeRegistry_->getType("Int");
    auto doubleType = typeRegistry_->getType("Double");

    auto result = typeChecker_->checkBinaryExpression(intType, "/", doubleType);
    EXPECT_EQ(result->toString(), "Double");
}

TEST_F(TypePromotionTest, ComplexPromotionChain) {
    auto intType = typeRegistry_->getType("Int");
    auto floatType = typeRegistry_->getType("Float");
    auto doubleType = typeRegistry_->getType("Double");

    std::vector<std::shared_ptr<Type>> types = {intType, floatType, doubleType};
    std::vector<std::string> operators = {"+", "*"};

    auto result = typeChecker_->inferExpressionType(types, operators);
    EXPECT_EQ(result->toString(), "Double");
}

} // namespace testing
} // namespace pryst
