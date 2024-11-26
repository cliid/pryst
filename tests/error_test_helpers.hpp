#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../src/type_registry.hpp"
#include "../src/error_propagation.hpp"

namespace pryst::testing {

class ErrorTestHelper {
public:
    static void expectErrorType(const std::function<void()>& operation,
                              const std::string& expectedType,
                              const std::string& expectedMessagePart) {
        try {
            operation();
            FAIL() << "Expected error of type " << expectedType << " was not thrown";
        } catch (const Error& e) {
            EXPECT_EQ(e.type(), expectedType);
            EXPECT_TRUE(e.what().find(expectedMessagePart) != std::string::npos)
                << "Expected message containing '" << expectedMessagePart
                << "' but got: " << e.what();
        }
    }

    static void expectErrorChain(const std::function<void()>& operation,
                               const std::vector<std::string>& expectedChain) {
        try {
            operation();
            FAIL() << "Expected error chain was not thrown";
        } catch (const Error& e) {
            std::string message = e.what();
            for (const auto& expected : expectedChain) {
                EXPECT_TRUE(message.find(expected) != std::string::npos)
                    << "Expected chain element '" << expected
                    << "' not found in: " << message;
            }
        }
    }

    static std::shared_ptr<Type> createMockType(const std::string& name) {
        class MockType : public Type {
        public:
            explicit MockType(std::string n) : name(std::move(n)) {}
            std::string toString() const override { return name; }
        private:
            std::string name;
        };
        return std::make_shared<MockType>(name);
    }

    static TypeRegistry createTestRegistry() {
        TypeRegistry registry;
        registry.registerPrimitiveType("int");
        registry.registerPrimitiveType("string");
        registry.registerPrimitiveType("bool");
        return registry;
    }
};

} // namespace pryst::testing
