#include <gtest/gtest.h>
#include "../src/type_checker.hpp"
#include "../src/types.hpp"
#include "../src/error_handler.hpp"
#include "../src/type_registry.hpp"
#include "../src/runtime/runtime_registry.hpp"
#include <llvm/IR/LLVMContext.h>

namespace pryst {
namespace testing {

class TypeCheckerErrorPropagationTest : public ::testing::Test {
protected:
    void SetUp() override {
        llvmContext = std::make_unique<::llvm::LLVMContext>();
        typeRegistry = std::make_unique<TypeRegistry>();
        runtimeRegistry = std::make_unique<runtime::RuntimeRegistry>();
        scopeManager = std::make_unique<ScopeManager>(*typeRegistry);
        typeChecker = std::make_unique<TypeChecker>(*llvmContext, *typeRegistry, *runtimeRegistry);
        errorHandler = std::make_shared<ErrorHandler>();
    }

    void TearDown() override {
        typeChecker.reset();
        scopeManager.reset();
        runtimeRegistry.reset();
        typeRegistry.reset();
        llvmContext.reset();
    }

    std::unique_ptr<::llvm::LLVMContext> llvmContext;
    std::unique_ptr<TypeRegistry> typeRegistry;
    std::unique_ptr<runtime::RuntimeRegistry> runtimeRegistry;
    std::unique_ptr<ScopeManager> scopeManager;
    std::unique_ptr<TypeChecker> typeChecker;
    std::shared_ptr<ErrorHandler> errorHandler;
};

TEST_F(TypeCheckerErrorPropagationTest, TestNullableTypeErrorPropagation) {
    auto result = typeChecker->visitNullableType(nullptr);
    auto type = std::any_cast<std::shared_ptr<Type>>(result);
    auto errorType = std::dynamic_pointer_cast<ErrorType>(type);
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_EQ(errorType->getMessage(), "Invalid nullable type");
}

TEST_F(TypeCheckerErrorPropagationTest, TestArithmeticErrorPropagation) {
    auto result = typeChecker->visitMultiplicativeExpr(nullptr);
    auto type = std::any_cast<std::shared_ptr<Type>>(result);
    auto errorType = std::dynamic_pointer_cast<ErrorType>(type);
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_EQ(errorType->getMessage(), "Invalid operands for multiplication");

    result = typeChecker->visitAdditiveExpr(nullptr);
    type = std::any_cast<std::shared_ptr<Type>>(result);
    errorType = std::dynamic_pointer_cast<ErrorType>(type);
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_EQ(errorType->getMessage(), "Invalid operands for addition");
}

TEST_F(TypeCheckerErrorPropagationTest, TestScopedErrorPropagation) {
    scopeManager->enterScope("testScope");

    auto result = typeChecker->visitQualifiedType(nullptr);
    auto type = std::any_cast<std::shared_ptr<Type>>(result);
    auto errorType = std::dynamic_pointer_cast<ErrorType>(type);
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_EQ(errorType->getScope(), "testScope");

    scopeManager->exitScope();
}

TEST_F(TypeCheckerErrorPropagationTest, TestInstanceofErrorPropagation) {
    auto result = typeChecker->visitInstanceofExpr(nullptr);
    auto type = std::any_cast<std::shared_ptr<Type>>(result);
    auto errorType = std::dynamic_pointer_cast<ErrorType>(type);
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_EQ(errorType->getMessage(), "Invalid operands for instanceof operation");
}

TEST_F(TypeCheckerErrorPropagationTest, TestUnionTypeErrorPropagation) {
    // Create test types
    auto intType = typeRegistry->getBasicType(BasicType::Int);
    auto stringType = typeRegistry->getBasicType(BasicType::String);
    auto errorType = std::make_shared<ErrorType>("Test error");

    // Create union type with int | string
    auto unionType = std::make_shared<UnionType>(intType, stringType);

    // Test error propagation with first type being error
    auto errorUnion = std::make_shared<UnionType>(errorType, stringType);
    EXPECT_EQ(errorUnion->getKind(), Type::Kind::Error);
    EXPECT_EQ(std::dynamic_pointer_cast<ErrorType>(errorUnion)->getMessage(), "Test error");

    // Test error propagation with second type being error
    auto unionError = std::make_shared<UnionType>(intType, errorType);
    EXPECT_EQ(unionError->getKind(), Type::Kind::Error);
    EXPECT_EQ(std::dynamic_pointer_cast<ErrorType>(unionError)->getMessage(), "Test error");
}

TEST_F(TypeCheckerErrorPropagationTest, TestIntersectionTypeErrorPropagation) {
    // Create test types
    auto intType = typeRegistry->getBasicType(BasicType::Int);
    auto stringType = typeRegistry->getBasicType(BasicType::String);
    auto errorType = std::make_shared<ErrorType>("Test error");

    // Create intersection type with int & string
    auto intersectionType = std::make_shared<IntersectionType>(intType, stringType);

    // Test error propagation with first type being error
    auto errorIntersection = std::make_shared<IntersectionType>(errorType, stringType);
    EXPECT_EQ(errorIntersection->getKind(), Type::Kind::Error);
    EXPECT_EQ(std::dynamic_pointer_cast<ErrorType>(errorIntersection)->getMessage(), "Test error");

    // Test error propagation with second type being error
    auto intersectionError = std::make_shared<IntersectionType>(intType, errorType);
    EXPECT_EQ(intersectionError->getKind(), Type::Kind::Error);
    EXPECT_EQ(std::dynamic_pointer_cast<ErrorType>(intersectionError)->getMessage(), "Test error");
}

TEST_F(TypeCheckerErrorPropagationTest, TestComplexTypeErrorPropagation) {
    // Create test types
    auto intType = std::make_shared<PrimitiveType>(Type::Kind::Int);
    auto stringType = std::make_shared<PrimitiveType>(Type::Kind::String);
    auto errorType = std::make_shared<ErrorType>("Test error");

    // Test union of intersection types with error
    auto intersection = std::make_shared<IntersectionType>(intType, stringType);
    auto unionWithError = std::make_shared<UnionType>(intersection, errorType);
    EXPECT_EQ(unionWithError->getKind(), Type::Kind::Error);
    EXPECT_EQ(std::dynamic_pointer_cast<ErrorType>(unionWithError)->getMessage(), "Test error");

    // Test intersection of union types with error
    auto validUnion = std::make_shared<UnionType>(intType, stringType);
    auto intersectionWithError = std::make_shared<IntersectionType>(validUnion, errorType);
    EXPECT_EQ(intersectionWithError->getKind(), Type::Kind::Error);
    EXPECT_EQ(std::dynamic_pointer_cast<ErrorType>(intersectionWithError)->getMessage(), "Test error");
}

TEST_F(TypeCheckerErrorPropagationTest, TestErrorPropagationThroughScope) {
    auto errorType = std::make_shared<ErrorType>("Initial error");
    auto result = typeChecker->propagateErrorThroughScope(errorType, "function scope");
    auto propagatedError = std::dynamic_pointer_cast<ErrorType>(result);

    ASSERT_TRUE(propagatedError != nullptr);
    EXPECT_TRUE(propagatedError->getMessage().find("Initial error") != std::string::npos);
    EXPECT_TRUE(propagatedError->getMessage().find("function scope") != std::string::npos);

    // Test with empty context
    result = typeChecker->propagateErrorThroughScope(errorType, "");
    propagatedError = std::dynamic_pointer_cast<ErrorType>(result);
    ASSERT_TRUE(propagatedError != nullptr);
    EXPECT_EQ(propagatedError->getMessage(), "Initial error");
}

TEST_F(TypeCheckerErrorPropagationTest, TestErrorPropagationWithTransform) {
    auto errorType = std::make_shared<ErrorType>("Base error");
    auto result = typeChecker->propagateErrorWithTransform(
        errorType,
        [](const std::string& msg) { return "Transformed: " + msg; }
    );
    auto transformedError = std::dynamic_pointer_cast<ErrorType>(result);

    ASSERT_TRUE(transformedError != nullptr);
    EXPECT_EQ(transformedError->getMessage(), "Transformed: Base error");

    // Test with multiple transformations
    result = typeChecker->propagateErrorWithTransform(
        transformedError,
        [](const std::string& msg) { return msg + " (additional context)"; }
    );
    auto doubleTransformed = std::dynamic_pointer_cast<ErrorType>(result);
    ASSERT_TRUE(doubleTransformed != nullptr);
    EXPECT_EQ(doubleTransformed->getMessage(), "Transformed: Base error (additional context)");
}

TEST_F(TypeCheckerErrorPropagationTest, TestGenericTypeInferenceErrorPropagation) {
    auto intType = typeRegistry->getBasicType(BasicType::Int);
    auto result = typeChecker->inferGenericType(std::any(intType), std::any(intType));
    auto errorType = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result));
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_TRUE(errorType->getMessage().find("base type must be a class") != std::string::npos);
}

TEST_F(TypeCheckerErrorPropagationTest, TestLambdaReturnTypeErrorPropagation) {
    std::vector<any> paramTypes;
    std::vector<string> bodyOps;
    auto result = typeChecker->inferLambdaReturnType(paramTypes, bodyOps);
    auto errorType = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result));
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_TRUE(errorType->getMessage().find("Empty lambda expression") != std::string::npos);
}

TEST_F(TypeCheckerErrorPropagationTest, TestComplexExpressionErrorPropagation) {
    std::vector<any> types;
    std::vector<string> operators;
    auto result = typeChecker->checkComplexExpression(types, operators);
    auto errorType = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result));
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_TRUE(errorType->getMessage().find("Empty complex expression") != std::string::npos);
}

    // Test array access with non-integer index
    auto arrayType = std::make_shared<ArrayType>(intType);
    auto stringType = typeRegistry->getBasicType(BasicType::String);
    result = typeChecker->checkArrayAccess(std::any(arrayType), std::any(stringType));
    errorType = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result));
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_TRUE(errorType->getMessage().find("Array index must be an integer") != std::string::npos);

    // Test array assignment with incompatible types
    auto floatType = typeRegistry->getBasicType(BasicType::Float);
    auto floatArrayType = std::make_shared<ArrayType>(floatType);
    result = typeChecker->checkArrayAssignment(std::any(arrayType), std::any(floatArrayType));
    errorType = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result));
    ASSERT_TRUE(errorType != nullptr);
    EXPECT_TRUE(errorType->getMessage().find("Incompatible array types") != std::string::npos);
}

} // namespace testing
} // namespace pryst
