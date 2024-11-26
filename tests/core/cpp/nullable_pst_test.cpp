#include <gtest/gtest.h>
#include "../../../src/compiler.hpp"
#include "../../../src/type_checker.hpp"
#include "../../../src/type_registry.hpp"
#include "../../../src/runtime/runtime_registry.hpp"
#include "../../../src/generated/PrystLexer.h"
#include "../../../src/generated/PrystParser.h"
#include <antlr4-runtime.h>
#include <fstream>
#include <sstream>

using namespace pryst;

class NullablePSTTest : public ::testing::Test {
protected:
    std::unique_ptr<Compiler> compiler;
    std::unique_ptr<antlr4::ANTLRInputStream> input;
    std::unique_ptr<PrystLexer> lexer;
    std::unique_ptr<antlr4::CommonTokenStream> tokens;
    std::unique_ptr<PrystParser> parser;

    NullablePSTTest()
        : compiler(std::make_unique<Compiler>())
        , input(std::make_unique<antlr4::ANTLRInputStream>()) {}

    void SetUp() override {}

    std::unique_ptr<antlr4::tree::ParseTree> parseCode(const std::string& code) {
        input->load(code);
        lexer = std::make_unique<PrystLexer>(input.get());
        tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
        parser = std::make_unique<PrystParser>(tokens.get());
        return std::unique_ptr<antlr4::tree::ParseTree>(parser->program());
    }

    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

TEST_F(NullablePSTTest, TestNullableTypesPST) {
    std::string code = readFile("tests/nullable_types.pst");
    EXPECT_NO_THROW({
        auto ast = parseCode(code);
        EXPECT_TRUE(compiler->compile(ast.get()));
    });
}
