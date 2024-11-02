#include "ast_tracer.hpp"

std::any ASTTracer::visitProgram(PrystParser::ProgramContext* ctx) {
    std::cout << getIndent() << "Entering Program" << std::endl;
    indentLevel++;
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Program" << std::endl;
    return std::any();
}

std::any ASTTracer::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    std::cout << getIndent() << "Entering Declaration" << std::endl;
    indentLevel++;
    if (ctx->functionDecl()) {
        visit(ctx->functionDecl());
    } else if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->statement()) {
        visit(ctx->statement());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Declaration" << std::endl;
    return std::any();
}

std::any ASTTracer::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    std::cout << getIndent() << "Entering VariableDecl: " << ctx->IDENTIFIER()->getText() << " : " << ctx->type()->getText() << std::endl;
    indentLevel++;
    if (ctx->expression()) {
        std::cout << getIndent() << "Processing initialization expression" << std::endl;
        visit(ctx->expression());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting VariableDecl" << std::endl;
    return std::any();
}

std::any ASTTracer::visitExpression(PrystParser::ExpressionContext* ctx) {
    std::cout << getIndent() << "Entering Expression" << std::endl;
    indentLevel++;
    if (ctx->assignment()) {
        visit(ctx->assignment());
    } else if (ctx->call()) {
        visit(ctx->call());
    } else if (ctx->logicOr()) {
        visit(ctx->logicOr());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Expression" << std::endl;
    return std::any();
}

std::any ASTTracer::visitLogicOr(PrystParser::LogicOrContext* ctx) {
    std::cout << getIndent() << "Entering LogicOr" << std::endl;
    indentLevel++;
    for (auto node : ctx->logicAnd()) {
        visit(node);
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting LogicOr" << std::endl;
    return std::any();
}

std::any ASTTracer::visitLogicAnd(PrystParser::LogicAndContext* ctx) {
    std::cout << getIndent() << "Entering LogicAnd" << std::endl;
    indentLevel++;
    for (auto node : ctx->equality()) {
        visit(node);
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting LogicAnd" << std::endl;
    return std::any();
}


std::any ASTTracer::visitEquality(PrystParser::EqualityContext* ctx) {
    std::cout << getIndent() << "Entering Equality" << std::endl;
    indentLevel++;
    for (auto node : ctx->comparison()) {
        visit(node);
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Equality" << std::endl;
    return std::any();
}

std::any ASTTracer::visitComparison(PrystParser::ComparisonContext* ctx) {
    std::cout << getIndent() << "Entering Comparison" << std::endl;
    indentLevel++;
    for (auto node : ctx->addition()) {
        visit(node);
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Comparison" << std::endl;
    return std::any();
}

std::any ASTTracer::visitAddition(PrystParser::AdditionContext* ctx) {
    std::cout << getIndent() << "Entering Addition" << std::endl;
    indentLevel++;
    for (auto node : ctx->multiplication()) {
        visit(node);
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Addition" << std::endl;
    return std::any();
}

std::any ASTTracer::visitMultiplication(PrystParser::MultiplicationContext* ctx) {
    std::cout << getIndent() << "Entering Multiplication" << std::endl;
    indentLevel++;
    for (auto node : ctx->unary()) {
        visit(node);
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Multiplication" << std::endl;
    return std::any();
}

std::any ASTTracer::visitUnary(PrystParser::UnaryContext* ctx) {
    std::cout << getIndent() << "Entering Unary" << std::endl;
    indentLevel++;
    if (ctx->unary()) {
        visit(ctx->unary());
    } else if (ctx->postfix()) {
        visit(ctx->postfix());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Unary" << std::endl;
    return std::any();
}

std::any ASTTracer::visitPrimary(PrystParser::PrimaryContext* ctx) {
    std::cout << getIndent() << "Entering Primary" << std::endl;
    indentLevel++;
    if (ctx->NUMBER()) {
        std::cout << getIndent() << "Number literal: " << ctx->NUMBER()->getText() << std::endl;
    } else if (ctx->STRING()) {
        std::cout << getIndent() << "String literal: " << ctx->STRING()->getText() << std::endl;
    } else if (ctx->IDENTIFIER()) {
        std::cout << getIndent() << "Identifier: " << ctx->IDENTIFIER()->getText() << std::endl;
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Primary" << std::endl;
    return std::any();
}
