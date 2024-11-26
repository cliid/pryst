#include "runtime/io_impl.hpp"
#include "runtime/runtime_registry.hpp"
#include "type_registry.hpp"
#include <gtest/gtest.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

using namespace pryst;
using namespace pryst::runtime;

class IOTest : public ::testing::Test {
protected:
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<TypeRegistry> typeRegistry;
    std::unique_ptr<RuntimeRegistry> runtimeRegistry;

    void SetUp() override {
        module = std::make_unique<llvm::Module>("test_module", context);
        typeRegistry = std::make_unique<TypeRegistry>(context);
        runtimeRegistry = std::make_unique<RuntimeRegistry>(module.get());
        runtimeRegistry->setTypeRegistry(typeRegistry.get());
        runtimeRegistry->registerBuiltins();
    }
};

TEST_F(IOTest, FileClassRegistration) {
    // Verify File class registration from registerBuiltins()
    EXPECT_TRUE(typeRegistry->hasClass("pryst::io::File"));
    EXPECT_TRUE(runtimeRegistry->hasClass("pryst::io::File"));

    // Test nullable File type
    typeRegistry->registerNullableType("pryst::io::File");
    auto nullableType = typeRegistry->getCachedType("pryst::io::File?");
    EXPECT_TRUE(nullableType != nullptr);

    // Verify method registration
    const auto* fileClass = runtimeRegistry->getClass("pryst::io::File");
    EXPECT_TRUE(fileClass != nullptr);
    EXPECT_FALSE(fileClass->methods.empty());

    // Verify specific methods exist
    bool hasWriteString = false;
    bool hasReadString = false;
    bool hasClose = false;

    for (const auto& method : fileClass->methods) {
        if (method.name == "writeString") hasWriteString = true;
        if (method.name == "readString") hasReadString = true;
        if (method.name == "close") hasClose = true;
    }

    EXPECT_TRUE(hasWriteString) << "writeString method not found";
    EXPECT_TRUE(hasReadString) << "readString method not found";
    EXPECT_TRUE(hasClose) << "close method not found";
}
