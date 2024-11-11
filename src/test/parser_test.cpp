#include <iostream>
#include <fstream>
#include <sstream>
#include <any>
#include <vector>
#include "antlr4-runtime.h"
#include "generated/PrystLexer.h"
#include "generated/PrystParser.h"
#include "generated/PrystParserVisitor.h"

using namespace antlr4;
using namespace antlr4::tree;

class TestVisitor : public pryst::PrystVisitor {
public:
    virtual std::any visitProgram(pryst::PrystParser::ProgramContext *ctx) override {
        std::cout << "Visiting program" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitImportDecl(pryst::PrystParser::ImportDeclContext *ctx) override {
        std::cout << "Visiting import declaration" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitImportPath(pryst::PrystParser::ImportPathContext *ctx) override {
        std::cout << "Visiting import path" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitDeclaration(pryst::PrystParser::DeclarationContext *ctx) override {
        std::cout << "Visiting declaration" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitFunctionDecl(pryst::PrystParser::FunctionDeclContext *ctx) override {
        auto* identifier = ctx->IDENTIFIER();
        if (identifier != nullptr) {
            std::cout << "Found function declaration: " << identifier->getText() << std::endl;
        }
        return visitChildren(ctx);
    }

    virtual std::any visitParameters(pryst::PrystParser::ParametersContext *ctx) override {
        std::cout << "Visiting parameters" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitParameter(pryst::PrystParser::ParameterContext *ctx) override {
        std::cout << "Visiting parameter" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitBlock(pryst::PrystParser::BlockContext *ctx) override {
        std::cout << "Visiting block" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitStatement(pryst::PrystParser::StatementContext *ctx) override {
        std::cout << "Visiting statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitVarDecl(pryst::PrystParser::VarDeclContext *ctx) override {
        auto* identifier = ctx->IDENTIFIER();
        if (identifier != nullptr) {
            std::cout << "Found variable declaration: " << identifier->getText() << std::endl;
        }
        return visitChildren(ctx);
    }

    virtual std::any visitAssignment(pryst::PrystParser::AssignmentContext *ctx) override {
        std::cout << "Visiting assignment" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitIfStmt(pryst::PrystParser::IfStmtContext *ctx) override {
        std::cout << "Visiting if statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitWhileStmt(pryst::PrystParser::WhileStmtContext *ctx) override {
        std::cout << "Visiting while statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitForStmt(pryst::PrystParser::ForStmtContext *ctx) override {
        std::cout << "Visiting for statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitReturnStmt(pryst::PrystParser::ReturnStmtContext *ctx) override {
        std::cout << "Visiting return statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitTryStmt(pryst::PrystParser::TryStmtContext *ctx) override {
        std::cout << "Visiting try statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitBreakStmt(pryst::PrystParser::BreakStmtContext *ctx) override {
        std::cout << "Visiting break statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitContinueStmt(pryst::PrystParser::ContinueStmtContext *ctx) override {
        std::cout << "Visiting continue statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitExpressionStmt(pryst::PrystParser::ExpressionStmtContext *ctx) override {
        std::cout << "Visiting expression statement" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitClassDecl(pryst::PrystParser::ClassDeclContext *ctx) override {
        auto identifiers = ctx->IDENTIFIER();
        if (!identifiers.empty()) {
            std::cout << "Found class declaration: " << identifiers[0]->getText() << std::endl;
            for (size_t i = 1; i < identifiers.size(); i++) {
                std::cout << "  With member: " << identifiers[i]->getText() << std::endl;
            }
        }
        return visitChildren(ctx);
    }

    virtual std::any visitType(pryst::PrystParser::TypeContext *ctx) override {
        std::cout << "Visiting type" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitExpression(pryst::PrystParser::ExpressionContext *ctx) override {
        std::cout << "Visiting expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitUnaryExpr(pryst::PrystParser::UnaryExprContext *ctx) override {
        std::cout << "Visiting unary expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitPostfixExpr(pryst::PrystParser::PostfixExprContext *ctx) override {
        std::cout << "Visiting postfix expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitLambdaExpr(pryst::PrystParser::LambdaExprContext *ctx) override {
        std::cout << "Visiting lambda expression" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitArguments(pryst::PrystParser::ArgumentsContext *ctx) override {
        std::cout << "Visiting arguments" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitPrimary(pryst::PrystParser::PrimaryContext *ctx) override {
        std::cout << "Visiting primary" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitArrayLiteral(pryst::PrystParser::ArrayLiteralContext *ctx) override {
        std::cout << "Visiting array literal" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitMapLiteral(pryst::PrystParser::MapLiteralContext *ctx) override {
        std::cout << "Visiting map literal" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitMapEntry(pryst::PrystParser::MapEntryContext *ctx) override {
        std::cout << "Visiting map entry" << std::endl;
        return visitChildren(ctx);
    }
};

int main(int argc, char* argv[]) {
    try {
        // Create input stream from test file
        std::ifstream stream;
        const char* testFile = "src/test/parser_test.pst";
        stream.open(testFile);
        if (!stream.is_open()) {
            std::cerr << "Could not open " << testFile << std::endl;
            return 1;
        }

        ANTLRInputStream input(stream);

        // Create lexer
        pryst::PrystLexer lexer(&input);
        CommonTokenStream tokens(&lexer);

        // Create parser
        pryst::PrystParser parser(&tokens);
        tree::ParseTree* tree = parser.program();

        if (parser.getNumberOfSyntaxErrors() > 0) {
            std::cerr << "Syntax errors found" << std::endl;
            return 1;
        }

        // Create and run visitor
        TestVisitor visitor;
        visitor.visit(tree);

        std::cout << "All tests passed successfully" << std::endl;
        return 0;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
