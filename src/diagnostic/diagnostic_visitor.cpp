#include "diagnostic_visitor.hpp"

std::any DiagnosticVisitor::visitProgram(PrystParser::ProgramContext* ctx) {
    printNode("Program");
    ScopeGuard guard(indentLevel);
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    printNode("Declaration");
    ScopeGuard guard(indentLevel);
    if (ctx->classDeclaration()) {
        visit(ctx->classDeclaration());
    } else if (ctx->functionDecl()) {
        visit(ctx->functionDecl());
    } else if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) {
    std::string details = "class " + ctx->IDENTIFIER(0)->getText();
    if (ctx->EXTENDS()) {
        details += " extends " + ctx->IDENTIFIER(1)->getText();
    }
    printNode("ClassDeclaration", details);
    ScopeGuard guard(indentLevel);
    auto bodyCtx = ctx->classBody();
    if (bodyCtx) {
        for (auto member : bodyCtx->classMember()) {
            visit(member);
        }
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) {
    std::string details = ctx->type()->getText() + " " + ctx->IDENTIFIER()->getText();
    if (ctx->expression()) {
        details += " = <expr>";
    }
    printNode("ClassVariableDecl", details);
    printNode("Location", "Line " + std::to_string(ctx->getStart()->getLine()) + ", Column " + std::to_string(ctx->getStart()->getCharPositionInLine()));
    ScopeGuard guard(indentLevel);
    if (ctx->expression()) {
        visit(ctx->expression());
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) {
    std::string details = ctx->type()->getText() + " " + ctx->IDENTIFIER()->getText() + "()";
    printNode("ClassFunctionDecl", details);
    printNode("Location", "Line " + std::to_string(ctx->getStart()->getLine()) + ", Column " + std::to_string(ctx->getStart()->getCharPositionInLine()));
    ScopeGuard guard(indentLevel);
    if (ctx->paramList()) {
        visit(ctx->paramList());
    }
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    std::string details = ctx->type()->getText() + " " + ctx->IDENTIFIER()->getText();
    if (ctx->expression()) {
        details += " = <expr>";
    }
    printNode("VariableDecl", details);
    ScopeGuard guard(indentLevel);
    if (ctx->expression()) {
        visit(ctx->expression());
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    std::string details = ctx->type()->getText() + " " + ctx->IDENTIFIER()->getText() + "()";
    printNode("FunctionDecl", details);
    ScopeGuard guard(indentLevel);
    if (ctx->paramList()) {
        visit(ctx->paramList());
    }
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitExprStatement(PrystParser::ExprStatementContext* ctx) {
    printNode("ExprStatement");
    ScopeGuard guard(indentLevel);
    visit(ctx->expression());
    return nullptr;
}

std::any DiagnosticVisitor::visitIfStatement(PrystParser::IfStatementContext* ctx) {
    printNode("IfStatement");
    ScopeGuard guard(indentLevel);
    printNode("Condition");
    visit(ctx->expression());
    printNode("Then Branch");
    visit(ctx->statement(0));
    if (ctx->ELSE()) {
        printNode("Else Branch");
        visit(ctx->statement(1));
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitWhileStatement(PrystParser::WhileStatementContext* ctx) {
    printNode("WhileStatement");
    ScopeGuard guard(indentLevel);
    printNode("Condition");
    visit(ctx->expression());
    printNode("Body");
    visit(ctx->statement());
    return nullptr;
}

std::any DiagnosticVisitor::visitForStatement(PrystParser::ForStatementContext* ctx) {
    printNode("ForStatement");
    ScopeGuard guard(indentLevel);
    if (ctx->variableDecl()) {
        printNode("Initializer (Variable)");
        visit(ctx->variableDecl());
    } else if (ctx->expression().size() > 0) {
        printNode("Initializer (Expression)");
        visit(ctx->expression(0));
    }
    if (ctx->expression().size() > 1) {
        printNode("Condition");
        visit(ctx->expression(1));
    }
    if (ctx->expression().size() > 2) {
        printNode("Increment");
        visit(ctx->expression(2));
    }
    printNode("Body");
    visit(ctx->statement());
    return nullptr;
}

std::any DiagnosticVisitor::visitReturnStatement(PrystParser::ReturnStatementContext* ctx) {
    printNode("ReturnStatement");
    ScopeGuard guard(indentLevel);
    if (ctx->expression()) {
        printNode("Return Value");
        visit(ctx->expression());
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitBlockStatement(PrystParser::BlockStatementContext* ctx) {
    printNode("BlockStatement");
    ScopeGuard guard(indentLevel);
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitExpression(PrystParser::ExpressionContext* ctx) {
    printNode("Expression");
    ScopeGuard guard(indentLevel);
    if (ctx->assignment()) {
        visit(ctx->assignment());
    } else {
        visit(ctx->logicOr());
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitAssignment(PrystParser::AssignmentContext* ctx) {
    std::string details;
    if (ctx->call()) {
        // Member assignment (call.IDENTIFIER = expr)
        details = "target: " + ctx->call()->getText() + "." + ctx->IDENTIFIER()->getText();
        printNode("Assignment (Member)", details);
        printNode("Location", "Line " + std::to_string(ctx->getStart()->getLine()) + ", Column " + std::to_string(ctx->getStart()->getCharPositionInLine()));

        ScopeGuard guard(indentLevel);
        printNode("Object Access Start");
        ScopeGuard accessGuard(indentLevel);
        visit(ctx->call());
        printNode("Final Member", "member: " + ctx->IDENTIFIER()->getText());
        printNode("Access End");
    } else {
        // Simple assignment (IDENTIFIER = expr)
        details = "target: " + ctx->IDENTIFIER()->getText();
        printNode("Assignment (Simple)", details);
        printNode("Location", "Line " + std::to_string(ctx->getStart()->getLine()) + ", Column " + std::to_string(ctx->getStart()->getCharPositionInLine()));
    }

    ScopeGuard guard(indentLevel);
    printNode("Assignment Value");
    ScopeGuard valueGuard(indentLevel);
    visit(ctx->expression());
    return nullptr;
}

std::any DiagnosticVisitor::visitCall(PrystParser::CallContext* ctx) {
    printNode("Call Chain Start");
    printNode("Location", "Line " + std::to_string(ctx->getStart()->getLine()) + ", Column " + std::to_string(ctx->getStart()->getCharPositionInLine()));

    ScopeGuard guard(indentLevel);

    // Visit primary expression
    visit(ctx->primary());

    // Process member access chain
    for (auto identifier : ctx->IDENTIFIER()) {
        printNode("Member Access", "member: " + identifier->getText());
    }

    printNode("Call Chain End");
    return nullptr;
}

std::any DiagnosticVisitor::visitCallSuffix(PrystParser::CallSuffixContext* ctx) {
    // Member access only
    if (ctx->IDENTIFIER()) {  // Member access
        printNode("Member Access", "member: " + ctx->IDENTIFIER()->getText());
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitPrimary(PrystParser::PrimaryContext* ctx) {
    std::string details;
    if (ctx->IDENTIFIER()) {
        std::string name = ctx->IDENTIFIER()->getText();
        if (ctx->LPAREN()) {  // Function call
            details = "function call: " + name;
            if (ctx->arguments()) {
                details += " with " + std::to_string(ctx->arguments()->expression().size()) + " arguments";
                if (name == "print") {
                    details += " (builtin print function)";
                }
            }
        } else {
            details = "identifier: " + name;
        }
    } else if (ctx->NUMBER()) {
        details = "number: " + ctx->NUMBER()->getText();
    } else if (ctx->STRING()) {
        details = "string: " + ctx->STRING()->getText();
    } else if (ctx->TRUE()) {
        details = "true";
    } else if (ctx->FALSE()) {
        details = "false";
    } else if (ctx->NULL_()) {
        details = "null";
    } else if (ctx->newExpression()) {
        details = "new expression";
    }
    printNode("Primary", details);
    ScopeGuard guard(indentLevel);

    if (ctx->arguments()) {
        printNode("Arguments");
        ScopeGuard argsGuard(indentLevel);
        for (auto arg : ctx->arguments()->expression()) {
            visit(arg);
        }
    } else if (ctx->expression()) {
        visit(ctx->expression());
    } else if (ctx->newExpression()) {
        visit(ctx->newExpression());
    }
    return nullptr;
}

std::any DiagnosticVisitor::visitNewExpression(PrystParser::NewExpressionContext* ctx) {
    printNode("NewExpression", "type: " + ctx->IDENTIFIER()->getText());
    return nullptr;
}
