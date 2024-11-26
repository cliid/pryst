#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <any>
#include <filesystem>
#include <antlr4-runtime.h>
#include <tree/ParseTree.h>
#include "PrystLexer.h"
#include "PrystParser.h"
#include "PrystParserVisitor.h"
#include "PrystParserBaseVisitor.h"
#include <tree/AbstractParseTreeVisitor.h>
#include <gtest/gtest.h>

using namespace antlr4;
namespace fs = std::filesystem;

namespace pryst {

class TestVisitor : public PrystParserBaseVisitor {
public:
    using PrystParserBaseVisitor::visitChildren;

    virtual std::any visit(antlr4::tree::ParseTree* tree) override {
        if (!tree) {
            throw std::runtime_error("Null parse tree passed to TestVisitor");
        }
        try {
            return tree->accept(this);
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("Error in TestVisitor: ") + e.what());
        }
    }
    virtual std::any visitProgram(PrystParser::ProgramContext *ctx) override {
        std::cout << "Visiting program" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitImportDecl(PrystParser::ImportDeclContext *ctx) override {
        std::cout << "Visiting import declaration" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitImportPath(PrystParser::ImportPathContext *ctx) override {
        std::cout << "Visiting import path" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitDeclaration(PrystParser::DeclarationContext *ctx) override {
        std::cout << "Visiting declaration" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitFunctionDecl(PrystParser::FunctionDeclContext *ctx) override {
        auto* identifier = ctx->IDENTIFIER();
        if (identifier != nullptr) {
            std::cout << "Found function declaration: " << identifier->getText() << std::endl;
        }
        return visitChildren(ctx);
    }

    virtual std::any visitParameters(PrystParser::ParametersContext *ctx) override {
        std::cout << "Visiting parameters" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitParameter(PrystParser::ParameterContext *ctx) override {
        std::cout << "Visiting parameter" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitBlock(PrystParser::BlockContext *ctx) override {
        std::cout << "Visiting block" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitStatement(PrystParser::StatementContext *ctx) override {
        std::cout << "Visiting statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitVarDecl(PrystParser::VarDeclContext *ctx) override {
        std::cout << "Visiting variable declaration" << std::endl;

        auto* idList = ctx->identifierList();
        if (idList && !idList->IDENTIFIER().empty()) {
            std::cout << "Variable name: " << idList->IDENTIFIER(0)->getText() << std::endl;
        }

        return visitChildren(ctx);
    }

    virtual std::any visitIdentifierList(PrystParser::IdentifierListContext *ctx) override {
        std::cout << "Visiting identifier list" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitAssignment(PrystParser::AssignmentContext *ctx) override {
        std::cout << "Visiting assignment" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitIfStmt(PrystParser::IfStmtContext *ctx) override {
        std::cout << "Visiting if statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitWhileStmt(PrystParser::WhileStmtContext *ctx) override {
        std::cout << "Visiting while statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitForStmt(PrystParser::ForStmtContext *ctx) override {
        std::cout << "Visiting for statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitReturnStmt(PrystParser::ReturnStmtContext *ctx) override {
        std::cout << "Visiting return statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitTryStmt(PrystParser::TryStmtContext *ctx) override {
        std::cout << "Visiting try statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitBreakStmt(PrystParser::BreakStmtContext *ctx) override {
        std::cout << "Visiting break statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitContinueStmt(PrystParser::ContinueStmtContext *ctx) override {
        std::cout << "Visiting continue statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitExpressionStmt(PrystParser::ExpressionStmtContext *ctx) override {
        std::cout << "Visiting expression statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitClassDecl(PrystParser::ClassDeclContext *ctx) override {
        auto identifiers = ctx->IDENTIFIER();
        if (!identifiers.empty()) {
            std::cout << "Found class declaration: " << identifiers[0]->getText() << std::endl;
            for (size_t i = 1; i < identifiers.size(); i++) {
                std::cout << "  With member: " << identifiers[i]->getText() << std::endl;
            }
        }
        return visitChildren(ctx);
    }

    virtual std::any visitInterfaceDecl(PrystParser::InterfaceDeclContext *ctx) override {
        std::cout << "Visiting interface declaration" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitInterfaceMember(PrystParser::InterfaceMemberContext *ctx) override {
        std::cout << "Visiting interface member" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitGenericParams(PrystParser::GenericParamsContext *ctx) override {
        std::cout << "Visiting generic parameters" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitGenericArgs(PrystParser::GenericArgsContext *ctx) override {
        std::cout << "Visiting generic arguments" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitClassMember(PrystParser::ClassMemberContext *ctx) override {
        std::cout << "Visiting class member" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitOverloadParams(PrystParser::OverloadParamsContext *ctx) override {
        std::cout << "Visiting overload parameters" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitConstructorDecl(PrystParser::ConstructorDeclContext *ctx) override {
        std::cout << "Visiting constructor declaration" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitConstructorBlock(PrystParser::ConstructorBlockContext *ctx) override {
        std::cout << "Visiting constructor block" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitType(PrystParser::TypeContext *ctx) override {
        std::cout << "Visiting type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitQualifiedType(PrystParser::QualifiedTypeContext *ctx) override {
        std::cout << "Visiting qualified type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitReturnType(PrystParser::ReturnTypeContext *ctx) override {
        std::cout << "Visiting return type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitNullableType(PrystParser::NullableTypeContext *ctx) override {
        std::cout << "Visiting nullable type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitBasicType(PrystParser::BasicTypeContext *ctx) override {
        std::cout << "Visiting basic type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitArrayType(PrystParser::ArrayTypeContext *ctx) override {
        std::cout << "Visiting array type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitMapType(PrystParser::MapTypeContext *ctx) override {
        std::cout << "Visiting map type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitKeyType(PrystParser::KeyTypeContext *ctx) override {
        std::cout << "Visiting key type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitFunctionType(PrystParser::FunctionTypeContext *ctx) override {
        std::cout << "Visiting function type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitTypeList(PrystParser::TypeListContext *ctx) override {
        std::cout << "Visiting type list" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitAssignmentExpr(PrystParser::AssignmentExprContext *ctx) override {
        std::cout << "Visiting assignment expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitLogicalAndExpr(PrystParser::LogicalAndExprContext *ctx) override {
        std::cout << "Visiting logical AND expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitCastExpr(PrystParser::CastExprContext *ctx) override {
        std::cout << "Visiting cast expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitAdditiveExpr(PrystParser::AdditiveExprContext *ctx) override {
        std::cout << "Visiting additive expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitRelationalExpr(PrystParser::RelationalExprContext *ctx) override {
        std::cout << "Visiting relational expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitParenExpr(PrystParser::ParenExprContext *ctx) override {
        std::cout << "Visiting parenthesized expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitLogicalOrExpr(PrystParser::LogicalOrExprContext *ctx) override {
        std::cout << "Visiting logical OR expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitPrefixExpr(PrystParser::PrefixExprContext *ctx) override {
        std::cout << "Visiting prefix expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitMethodCallExpr(PrystParser::MethodCallExprContext *ctx) override {
        std::cout << "Visiting method call expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitArrayAccessExpr(PrystParser::ArrayAccessExprContext *ctx) override {
        std::cout << "Visiting array access expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitPrimaryExpr(PrystParser::PrimaryExprContext *ctx) override {
        std::cout << "Visiting primary expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitNullableChain(PrystParser::NullableChainContext *ctx) override {
        std::cout << "Visiting nullable chain expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitLambdaExpr(PrystParser::LambdaExprContext *ctx) override {
        std::cout << "Visiting lambda expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitMemberAccessExpr(PrystParser::MemberAccessExprContext *ctx) override {
        std::cout << "Visiting member access expression: " << ctx->IDENTIFIER()->getText() << std::endl;
        if (!ctx->expression()) {
            throw std::runtime_error("Null expression in member access");
        }
        return visitChildren(ctx);
    }

    virtual std::any visitPostfixExpr(PrystParser::PostfixExprContext *ctx) override {
        std::cout << "Visiting postfix expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitConstructorExpr(PrystParser::ConstructorExprContext *ctx) override {
        std::cout << "Visiting constructor expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext *ctx) override {
        std::cout << "Visiting multiplicative expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitEqualityExpr(PrystParser::EqualityExprContext *ctx) override {
        std::cout << "Visiting equality expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitConditionalExpr(PrystParser::ConditionalExprContext *ctx) override {
        std::cout << "Visiting conditional expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitPrimary(PrystParser::PrimaryContext *ctx) override {
        std::cout << "Visiting primary" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitStringInterpolation(PrystParser::StringInterpolationContext *ctx) override {
        std::cout << "Visiting string interpolation" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitChainedCall(PrystParser::ChainedCallContext *ctx) override {
        std::cout << "Visiting chained call" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitStringLiteral(PrystParser::StringLiteralContext *ctx) override {
        std::cout << "Visiting string literal" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitLambdaParams(PrystParser::LambdaParamsContext *ctx) override {
        std::cout << "Visiting lambda parameters" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitArguments(PrystParser::ArgumentsContext *ctx) override {
        std::cout << "Visiting arguments" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext *ctx) override {
        std::cout << "Visiting empty array literal" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext *ctx) override {
        std::cout << "Visiting non-empty array literal" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext *ctx) override {
        std::cout << "Visiting empty map literal" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext *ctx) override {
        std::cout << "Visiting non-empty map literal" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitMapEntry(PrystParser::MapEntryContext *ctx) override {
        std::cout << "Visiting map entry" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitMapKey(PrystParser::MapKeyContext *ctx) override {
        std::cout << "Visiting map key" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitErrorMember(PrystParser::ErrorMemberContext *ctx) override {
        std::cout << "Visiting error member" << std::endl;
        return visitChildren(ctx);
    }
};

} // end namespace pryst

class ParserTest : public ::testing::Test {
protected:
    std::string test_files_dir;

    void SetUp() override {
        try {
            // Get test files directory from environment with detailed error checking
            const char* env_dir = std::getenv("TEST_FILES_DIR");
            if (!env_dir) {
                ADD_FAILURE() << "TEST_FILES_DIR environment variable not set";
                return;
            }

            // Convert to string immediately for safer handling
            test_files_dir = std::string(env_dir);
            std::cout << "Test directory path: '" << test_files_dir << "'" << std::endl;

            try {
                // Create path with explicit error handling
                fs::path test_path;
                test_path = fs::path(test_files_dir);
                std::cout << "Created filesystem path: '" << test_path.string() << "'" << std::endl;

                if (!fs::exists(test_path)) {
                    ADD_FAILURE() << "Test directory does not exist: " << test_files_dir;
                    return;
                }
                if (!fs::is_directory(test_path)) {
                    ADD_FAILURE() << "Test path is not a directory: " << test_files_dir;
                    return;
                }
                std::cout << "Verified test directory exists and is accessible" << std::endl;
            } catch (const fs::filesystem_error& e) {
                ADD_FAILURE() << "Filesystem error: " << e.what() << "\nPath: " << test_files_dir;
                return;
            }
        } catch (const std::exception& e) {
            ADD_FAILURE() << "Unexpected error in SetUp: " << e.what();
            return;
        }
    }

    void TearDown() override {
        // Common cleanup code can go here
    }

    std::unique_ptr<antlr4::tree::ParseTree> parseFile(const std::string& filename) {
        fs::path file_path = fs::path(test_files_dir) / filename;
        std::string full_path = file_path.string();
        std::cout << "Attempting to parse file: " << full_path << std::endl;

        if (!fs::exists(file_path)) {
            ADD_FAILURE() << "Test file does not exist: " << full_path;
            return std::unique_ptr<antlr4::tree::ParseTree>(nullptr);
        }

        std::ifstream stream;
        stream.open(full_path);
        if (!stream.is_open()) {
            ADD_FAILURE() << "Could not open " << full_path;
            return std::unique_ptr<antlr4::tree::ParseTree>(nullptr);
        }

        try {
            antlr4::ANTLRInputStream input(stream);
            pryst::PrystLexer lexer(&input);
            antlr4::CommonTokenStream tokens(&lexer);
            pryst::PrystParser parser(&tokens);

            auto tree = parser.program();
            if (parser.getNumberOfSyntaxErrors() > 0) {
                ADD_FAILURE() << "Syntax errors found in " << full_path;
                return std::unique_ptr<antlr4::tree::ParseTree>(nullptr);
            }
            return std::unique_ptr<antlr4::tree::ParseTree>(tree);
        } catch (const std::exception& e) {
            ADD_FAILURE() << "Exception while parsing " << full_path << ": " << e.what();
            return std::unique_ptr<antlr4::tree::ParseTree>(nullptr);
        }
    }
};

TEST_F(ParserTest, ParseTestFile) {
    auto tree = parseFile("parser_test.pst");
    ASSERT_TRUE(tree != nullptr) << "Failed to parse test file";

    pryst::TestVisitor visitor;
    ASSERT_NO_THROW({
        std::any result = visitor.visit(tree.get());
    }) << "Error during test visitor execution";

    std::cout << "Parser test passed successfully" << std::endl;
}

TEST_F(ParserTest, ParseFunctionDeclaration) {
    auto tree = parseFile("function_test.pst");
    ASSERT_TRUE(tree != nullptr) << "Failed to parse function test file";

    pryst::TestVisitor visitor;
    ASSERT_NO_THROW({
        std::any result = visitor.visit(tree.get());
    }) << "Error during function declaration test";
}

TEST_F(ParserTest, ParseClassDeclaration) {
    auto tree = parseFile("class_test.pst");
    ASSERT_TRUE(tree != nullptr) << "Failed to parse class test file";

    pryst::TestVisitor visitor;
    ASSERT_NO_THROW({
        std::any result = visitor.visit(tree.get());
    }) << "Error during class declaration test";
}
