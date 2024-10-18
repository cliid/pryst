#include "ast.hpp"

// Implement constructors and accept methods

void AssignmentExpression::accept(ASTVisitor& visitor) {
    visitor.visitAssignmentExpression(*this);
}

void GroupingExpression::accept(ASTVisitor& visitor) {
    visitor.visitGroupingExpression(*this);
}

void LiteralExpression::accept(ASTVisitor& visitor) {
    visitor.visitLiteralExpression(*this);
}

void Parameter::accept(ASTVisitor& visitor) {
    visitor.visitParameter(*this);
}

void FunctionDeclaration::accept(ASTVisitor& visitor) {
    visitor.visitFunctionDeclaration(*this);
}

// Implement accept methods for other AST node classes similarly