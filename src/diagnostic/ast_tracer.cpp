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
        if (auto* namedFunc = dynamic_cast<PrystParser::NamedFunctionContext*>(ctx->functionDecl())) {
            std::cout << getIndent() << "Named Function: " << namedFunc->IDENTIFIER()->getText() << std::endl;
            visit(namedFunc);
        } else if (auto* lambdaFunc = dynamic_cast<PrystParser::LambdaFunctionContext*>(ctx->functionDecl())) {
            std::cout << getIndent() << "Lambda Function" << std::endl;
            visit(lambdaFunc);
        }
    } else if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->statement()) {
        visit(ctx->statement());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Declaration" << std::endl;
    return std::any();
}

std::any ASTTracer::visitInferredVariableDecl(PrystParser::InferredVariableDeclContext* ctx) {
    std::cout << getIndent() << "Entering InferredVariableDecl: " << ctx->IDENTIFIER()->getText() << std::endl;
    indentLevel++;
    if (ctx->expression()) {
        std::cout << getIndent() << "Processing initialization expression" << std::endl;
        visit(ctx->expression());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting InferredVariableDecl" << std::endl;
    return std::any();
}

std::any ASTTracer::visitTypedVariableDecl(PrystParser::TypedVariableDeclContext* ctx) {
    std::cout << getIndent() << "Entering TypedVariableDecl: " << ctx->IDENTIFIER()->getText()
              << " : " << ctx->type()->getText() << std::endl;
    indentLevel++;
    if (ctx->expression()) {
        std::cout << getIndent() << "Processing initialization expression" << std::endl;
        visit(ctx->expression());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting TypedVariableDecl" << std::endl;
    return std::any();
}

std::any ASTTracer::visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext* ctx) {
    std::cout << getIndent() << "Entering UninitializedVariableDecl: " << ctx->IDENTIFIER()->getText()
              << " : " << ctx->type()->getText() << std::endl;
    indentLevel++;
    indentLevel--;
    std::cout << getIndent() << "Exiting UninitializedVariableDecl" << std::endl;
    return std::any();
}

std::any ASTTracer::visitClassInferredVariableDecl(PrystParser::ClassInferredVariableDeclContext* ctx) {
    std::cout << getIndent() << "Entering ClassInferredVariableDecl: " << ctx->IDENTIFIER()->getText() << std::endl;
    indentLevel++;
    if (ctx->expression()) {
        std::cout << getIndent() << "Processing initialization expression" << std::endl;
        visit(ctx->expression());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting ClassInferredVariableDecl" << std::endl;
    return std::any();
}

std::any ASTTracer::visitClassTypedVariableDecl(PrystParser::ClassTypedVariableDeclContext* ctx) {
    std::cout << getIndent() << "Entering ClassTypedVariableDecl: " << ctx->IDENTIFIER()->getText()
              << " : " << ctx->type()->getText() << std::endl;
    indentLevel++;
    if (ctx->expression()) {
        std::cout << getIndent() << "Processing initialization expression" << std::endl;
        visit(ctx->expression());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting ClassTypedVariableDecl" << std::endl;
    return std::any();
}

std::any ASTTracer::visitClassConstInferredDecl(PrystParser::ClassConstInferredDeclContext* ctx) {
    std::cout << getIndent() << "Entering ClassConstInferredDecl: " << ctx->IDENTIFIER()->getText() << std::endl;
    indentLevel++;
    if (ctx->expression()) {
        std::cout << getIndent() << "Processing initialization expression" << std::endl;
        visit(ctx->expression());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting ClassConstInferredDecl" << std::endl;
    return std::any();
}

std::any ASTTracer::visitClassConstTypedDecl(PrystParser::ClassConstTypedDeclContext* ctx) {
    std::cout << getIndent() << "Entering ClassConstTypedDecl: " << ctx->IDENTIFIER()->getText()
              << " : " << ctx->type()->getText() << std::endl;
    indentLevel++;
    if (ctx->expression()) {
        std::cout << getIndent() << "Processing initialization expression" << std::endl;
        visit(ctx->expression());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting ClassConstTypedDecl" << std::endl;
    return std::any();
}

std::any ASTTracer::visitExpression(PrystParser::ExpressionContext* ctx) {
    std::cout << getIndent() << "Entering Expression" << std::endl;
    indentLevel++;
    if (ctx->assignment()) {
        visit(ctx->assignment());
    } else if (ctx->typeCastExpr()) {
        auto* castExpr = ctx->typeCastExpr();
        if (dynamic_cast<PrystParser::ParenthesizedCastContext*>(castExpr)) {
            visitParenthesizedCast(dynamic_cast<PrystParser::ParenthesizedCastContext*>(castExpr));
        } else if (dynamic_cast<PrystParser::ConstructorCastContext*>(castExpr)) {
            visitConstructorCast(dynamic_cast<PrystParser::ConstructorCastContext*>(castExpr));
        }
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
    } else if (ctx->qualifiedIdentifier()) {
        visit(ctx->qualifiedIdentifier());
        if (ctx->LPAREN()) {
            std::cout << getIndent() << "Function call" << std::endl;
            if (ctx->arguments()) {
                visit(ctx->arguments());
            }
        }
    } else if (ctx->TRUE() || ctx->FALSE()) {
        std::cout << getIndent() << "Boolean literal: " << ctx->getText() << std::endl;
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Primary" << std::endl;
    return std::any();
}

std::any ASTTracer::visitNamedFunction(PrystParser::NamedFunctionContext* ctx) {
    std::cout << getIndent() << "Entering Named Function: " << ctx->IDENTIFIER()->getText() << std::endl;
    indentLevel++;
    if (ctx->paramList()) {
        std::cout << getIndent() << "Parameters:" << std::endl;
        visit(ctx->paramList());
    }
    if (ctx->functionBody()) {
        std::cout << getIndent() << "Processing function body" << std::endl;
        visit(ctx->functionBody());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Named Function" << std::endl;
    return std::any();
}

std::any ASTTracer::visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) {
    std::cout << getIndent() << "Entering Lambda Function" << std::endl;
    indentLevel++;
    if (ctx->paramList()) {
        std::cout << getIndent() << "Parameters:" << std::endl;
        visit(ctx->paramList());
    }
    if (!ctx->declaration().empty()) {
        std::cout << getIndent() << "Processing lambda body" << std::endl;
        for (auto decl : ctx->declaration()) {
            visit(decl);
        }
    } else if (ctx->expression()) {
        std::cout << getIndent() << "Processing lambda expression" << std::endl;
        visit(ctx->expression());
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Lambda Function" << std::endl;
    return std::any();
}

std::any ASTTracer::visitParenthesizedCast(PrystParser::ParenthesizedCastContext* ctx) {
    std::cout << getIndent() << "Entering Parenthesized Cast Expression" << std::endl;
    indentLevel++;
    std::cout << getIndent() << "Target Type: " << ctx->type()->getText() << std::endl;
    visit(ctx->expression());
    indentLevel--;
    std::cout << getIndent() << "Exiting Parenthesized Cast Expression" << std::endl;
    return std::any();
}

std::any ASTTracer::visitConstructorCast(PrystParser::ConstructorCastContext* ctx) {
    std::cout << getIndent() << "Entering Constructor Cast Expression" << std::endl;
    indentLevel++;
    std::cout << getIndent() << "Target Type: " << ctx->type()->getText() << std::endl;
    visit(ctx->expression());
    indentLevel--;
    std::cout << getIndent() << "Exiting Constructor Cast Expression" << std::endl;
    return std::any();
}

std::any ASTTracer::visitSimpleString(PrystParser::SimpleStringContext* ctx) {
    std::cout << getIndent() << "Entering Simple String" << std::endl;
    indentLevel++;
    if (ctx->STRING_CONTENT()) {
        std::cout << getIndent() << "String content: " << ctx->STRING_CONTENT()->getText() << std::endl;
    }
    indentLevel--;
    std::cout << getIndent() << "Exiting Simple String" << std::endl;
    return std::any();
}
