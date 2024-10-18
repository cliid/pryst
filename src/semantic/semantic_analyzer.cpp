#include "semantic_analyzer.hpp"
#include <stdexcept>

void SemanticAnalyzer::analyze(Program& program) {
    for (const auto& decl : program.declarations) {
        decl->accept(*this);
    }
}

void SemanticAnalyzer::visitClassDeclaration(ClassDeclaration& node) {
    // Check for duplicate field/method names, etc.
    symbolTable.defineClass(node.name, &node);
}

void SemanticAnalyzer::visitNewExpression(NewExpression& node) {
    auto classType = symbolTable.lookupClass(node.className);
    if (!classType) {
        throw std::runtime_error("Undefined class: " + node.className);
    }
    // Check constructor arguments
    node.setType(std::make_shared<ObjectType>(node.className));
}

void SemanticAnalyzer::visitFunctionDeclaration(FunctionDeclaration& node) {
    currentFunction = &node;
    symbolTable.enterScope();
    
    for (const auto& param : node.parameters) {
        symbolTable.define(param.second, getType(param.first));
    }
    
    node.body->accept(*this);
    
    symbolTable.exitScope();
    currentFunction = nullptr;
}

void SemanticAnalyzer::visitVariableDeclaration(VariableDeclaration& node) {
    if (node.initializer) {
        node.initializer->accept(*this);
        checkTypes(getType(node.type), node.initializer->getType(), "Type mismatch in variable declaration");
    }
    symbolTable.define(node.name, getType(node.type));
}

void SemanticAnalyzer::visitBlock(Block& node) {
    symbolTable.enterScope();
    for (const auto& stmt : node.statements) {
        stmt->accept(*this);
    }
    symbolTable.exitScope();
}

void SemanticAnalyzer::visitExpressionStatement(ExpressionStatement& node) {
    node.expression->accept(*this);
}

void SemanticAnalyzer::visitIfStatement(IfStatement& node) {
    node.condition->accept(*this);
    checkTypes(std::make_shared<BoolType>(), node.condition->getType(), "If condition must be a boolean");
    node.thenBranch->accept(*this);
    if (node.elseBranch) {
        node.elseBranch->accept(*this);
    }
}

void SemanticAnalyzer::visitWhileStatement(WhileStatement& node) {
    node.condition->accept(*this);
    checkTypes(std::make_shared<BoolType>(), node.condition->getType(), "While condition must be a boolean");
    node.body->accept(*this);
}

void SemanticAnalyzer::visitForStatement(ForStatement& node) {
    symbolTable.enterScope();
    if (node.initializer) {
        node.initializer->accept(*this);
    }
    if (node.condition) {
        node.condition->accept(*this);
        checkTypes(std::make_shared<BoolType>(), node.condition->getType(), "For condition must be a boolean");
    }
    if (node.increment) {
        node.increment->accept(*this);
    }
    node.body->accept(*this);
    symbolTable.exitScope();
}

void SemanticAnalyzer::visitReturnStatement(ReturnStatement& node) {
    if (!currentFunction) {
        throw std::runtime_error("Return statement outside of function");
    }
    if (node.value) {
        node.value->accept(*this);
        checkTypes(getType(currentFunction->returnType), node.value->getType(), "Return type mismatch");
    } else {
        checkTypes(std::make_shared<VoidType>(), getType(currentFunction->returnType), "Function must return a value");
    }
}

void SemanticAnalyzer::visitBinaryExpression(BinaryExpression& node) {
    node.left->accept(*this);
    node.right->accept(*this);
    checkTypes(node.left->getType(), node.right->getType(), "Type mismatch in binary expression");
    node.setType(node.left->getType());
}

void SemanticAnalyzer::visitUnaryExpression(UnaryExpression& node) {
    node.operand->accept(*this);
    if (node.op == "!") {
        if (!std::dynamic_pointer_cast<BoolType>(node.operand->getType()) &&
            !std::dynamic_pointer_cast<IntType>(node.operand->getType())) {
            throw std::runtime_error("Operand must be a boolean or integer for logical NOT operation");
        }
        node.setType(std::make_shared<BoolType>());
    } else if (node.op == "~") {
        checkTypes(std::make_shared<IntType>(), node.operand->getType(), "Operand must be an integer for bitwise NOT operation");
        node.setType(std::make_shared<IntType>());
    } else if (node.op == "-") {
        if (!std::dynamic_pointer_cast<IntType>(node.operand->getType()) &&
            !std::dynamic_pointer_cast<FloatType>(node.operand->getType())) {
            throw std::runtime_error("Operand must be a number for negation");
        }
        node.setType(node.operand->getType());
    }
}

void SemanticAnalyzer::visitLiteralExpression(LiteralExpression& node) {
    node.setType(getType(node.getType()->getName()));
}

void SemanticAnalyzer::visitVariableExpression(VariableExpression& node) {
    auto type = symbolTable.lookup(node.name);
    if (!type) {
        throw std::runtime_error("Undefined variable: " + node.name);
    }
    node.setType(type);
}

void SemanticAnalyzer::visitCallExpression(CallExpression& node) {
    // Assuming we have a function table, we would look up the function here
    // For now, we'll just check that all arguments are well-typed
    for (const auto& arg : node.arguments) {
        arg->accept(*this);
    }
    // Set a placeholder return type
    node.setType(std::make_shared<IntType>());
}

void SemanticAnalyzer::visitAssignmentExpression(AssignmentExpression& node) {
    auto varType = symbolTable.lookup(node.name);
    if (!varType) {
        throw std::runtime_error("Undefined variable: " + node.name);
    }
    node.value->accept(*this);
    checkTypes(varType, node.value->getType(), "Type mismatch in assignment");
    node.setType(varType);
}

void SemanticAnalyzer::visitGroupingExpression(GroupingExpression& node) {
    node.expression->accept(*this);
    node.setType(node.expression->getType());
}

std::shared_ptr<Type> SemanticAnalyzer::getType(const std::string& typeName) const {
    if (typeName == "int") return std::make_shared<IntType>();
    if (typeName == "float") return std::make_shared<FloatType>();
    if (typeName == "bool") return std::make_shared<BoolType>();
    if (typeName == "str") return std::make_shared<StrType>();
    if (typeName == "void") return std::make_shared<VoidType>();
    throw std::runtime_error("Unknown type: " + typeName);
}

void SemanticAnalyzer::checkTypes(const std::shared_ptr<Type>& expected, const std::shared_ptr<Type>& actual, const std::string& errorMessage) const {
    if (expected->getName() != actual->getName()) {
        throw std::runtime_error(errorMessage + ": Expected " + expected->getName() + ", got " + actual->getName());
    }
}

void SemanticAnalyzer::visitParameter(Parameter& node) {
    // Implement any necessary logic for visiting a parameter.
    // For example, you might want to check the parameter's type or name.
    // This is a placeholder implementation.
    symbolTable.define(node.name, getType(node.type));
}
