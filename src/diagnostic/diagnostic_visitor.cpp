#include "diagnostic_visitor.hpp"
#include "utils/debug.hpp"
#include <sstream>
#include <stdexcept>

namespace pryst {

DiagnosticVisitor::DiagnosticVisitor() : currentFunction(""), inLoop(false) {}

std::any DiagnosticVisitor::visitProgram(PrystParser::ProgramContext* ctx) {
    PRYST_DEBUG("Diagnosing program");
    try {
        for (auto decl : ctx->declaration()) {
            visit(decl);
        }
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in program: " + std::string(ex.what()));
        throw;
    }
}

std::any DiagnosticVisitor::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    PRYST_DEBUG("Diagnosing function declaration");
    try {
        std::string name = ctx->IDENTIFIER()->getText();
        currentFunction = name;

        // Check return type
        std::string returnType = std::any_cast<std::string>(visit(ctx->type()));
        PRYST_DEBUG("Function return type: " + returnType);

        // Check parameters
        if (ctx->paramList()) {
            for (auto param : ctx->paramList()->param()) {
                std::string paramType = std::any_cast<std::string>(visit(param->type()));
                PRYST_DEBUG("Parameter type: " + paramType);
                symbolTable.addVariable(param->IDENTIFIER()->getText(), paramType);
            }
        }

        // Visit function body
        visit(ctx->functionBody());

        currentFunction.clear();
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in function declaration: " + std::string(ex.what()));
        throw;
    }
}

std::any DiagnosticVisitor::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    PRYST_DEBUG("Diagnosing variable declaration");
    try {
        std::string name = ctx->IDENTIFIER()->getText();
        std::string type = std::any_cast<std::string>(visit(ctx->type()));

        if (ctx->expression()) {
            std::string exprType = std::any_cast<std::string>(visit(ctx->expression()));
            if (!areTypesCompatible(type, exprType)) {
                std::stringstream ss;
                ss << "Type mismatch in variable declaration '" << name
                   << "': expected '" << type << "', got '" << exprType << "'";
                throw std::runtime_error(ss.str());
            }
        }

        symbolTable.addVariable(name, type);
        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in variable declaration: " + std::string(ex.what()));
        throw;
    }
}

std::any DiagnosticVisitor::visitBinary(PrystParser::BinaryContext* ctx) {
    PRYST_DEBUG("Diagnosing binary expression");
    try {
        std::string leftType = std::any_cast<std::string>(visit(ctx->left));
        std::string rightType = std::any_cast<std::string>(visit(ctx->right));
        std::string op = ctx->op->getText();

        // Check numeric operations
        if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
            if (!isNumericType(leftType) || !isNumericType(rightType)) {
                throw std::runtime_error("Numeric operator '" + op +
                    "' requires numeric operands, got '" + leftType +
                    "' and '" + rightType + "'");
            }
            return std::any(promoteTypes(leftType, rightType));
        }

        // Check comparison operations
        if (op == "<" || op == ">" || op == "<=" || op == ">=") {
            if (!isNumericType(leftType) || !isNumericType(rightType)) {
                throw std::runtime_error("Comparison operator '" + op +
                    "' requires numeric operands, got '" + leftType +
                    "' and '" + rightType + "'");
            }
            return std::any(std::string("bool"));
        }

        // Check equality operations
        if (op == "==" || op == "!=") {
            if (!areTypesCompatible(leftType, rightType)) {
                throw std::runtime_error("Cannot compare values of types '" +
                    leftType + "' and '" + rightType + "'");
            }
            return std::any(std::string("bool"));
        }

        // Check logical operations
        if (op == "&&" || op == "||") {
            if (leftType != "bool" || rightType != "bool") {
                throw std::runtime_error("Logical operator '" + op +
                    "' requires boolean operands, got '" + leftType +
                    "' and '" + rightType + "'");
            }
            return std::any(std::string("bool"));
        }

        throw std::runtime_error("Unknown binary operator: " + op);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in binary expression: " + std::string(ex.what()));
        throw;
    }
}

std::any DiagnosticVisitor::visitUnary(PrystParser::UnaryContext* ctx) {
    PRYST_DEBUG("Diagnosing unary expression");
    try {
        std::string exprType = std::any_cast<std::string>(visit(ctx->expression()));
        std::string op = ctx->op->getText();

        if (op == "-") {
            if (!isNumericType(exprType)) {
                throw std::runtime_error("Unary minus requires numeric operand, got '" +
                    exprType + "'");
            }
            return std::any(exprType);
        }

        if (op == "!") {
            if (exprType != "bool") {
                throw std::runtime_error("Logical not requires boolean operand, got '" +
                    exprType + "'");
            }
            return std::any(std::string("bool"));
        }

        throw std::runtime_error("Unknown unary operator: " + op);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in unary expression: " + std::string(ex.what()));
        throw;
    }
}

std::any DiagnosticVisitor::visitCall(PrystParser::CallContext* ctx) {
    PRYST_DEBUG("Diagnosing function call");
    try {
        std::string name = ctx->IDENTIFIER()->getText();
        auto funcInfo = symbolTable.lookupFunction(name);
        if (!funcInfo) {
            throw std::runtime_error("Unknown function: " + name);
        }

        // Check argument count
        size_t expectedArgs = funcInfo->paramTypes.size();
        size_t actualArgs = ctx->arguments() ? ctx->arguments()->expression().size() : 0;

        if (actualArgs != expectedArgs) {
            std::stringstream ss;
            ss << "Wrong number of arguments for function '" << name
               << "': expected " << expectedArgs << ", got " << actualArgs;
            throw std::runtime_error(ss.str());
        }

        // Check argument types
        if (ctx->arguments()) {
            for (size_t i = 0; i < actualArgs; i++) {
                std::string argType = std::any_cast<std::string>(
                    visit(ctx->arguments()->expression(i)));
                if (!areTypesCompatible(funcInfo->paramTypes[i], argType)) {
                    std::stringstream ss;
                    ss << "Type mismatch in argument " << (i + 1)
                       << " of function '" << name << "': expected '"
                       << funcInfo->paramTypes[i] << "', got '" << argType << "'";
                    throw std::runtime_error(ss.str());
                }
            }
        }

        return std::any(funcInfo->returnType);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in function call: " + std::string(ex.what()));
        throw;
    }
}

std::any DiagnosticVisitor::visitVariable(PrystParser::VariableContext* ctx) {
    PRYST_DEBUG("Diagnosing variable reference");
    try {
        std::string name = ctx->IDENTIFIER()->getText();
        if (!symbolTable.variableExists(name)) {
            throw std::runtime_error("Unknown variable: " + name);
        }
        return std::any(symbolTable.getVariableType(name));
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in variable reference: " + std::string(ex.what()));
        throw;
    }
}

std::any DiagnosticVisitor::visitAssignment(PrystParser::AssignmentContext* ctx) {
    PRYST_DEBUG("Diagnosing assignment");
    try {
        std::string name = ctx->IDENTIFIER()->getText();
        if (!symbolTable.variableExists(name)) {
            throw std::runtime_error("Unknown variable: " + name);
        }

        std::string varType = symbolTable.getVariableType(name);
        std::string exprType = std::any_cast<std::string>(visit(ctx->expression()));

        if (!areTypesCompatible(varType, exprType)) {
            std::stringstream ss;
            ss << "Type mismatch in assignment to '" << name
               << "': cannot assign value of type '" << exprType
               << "' to variable of type '" << varType << "'";
            throw std::runtime_error(ss.str());
        }

        return std::any(varType);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in assignment: " + std::string(ex.what()));
        throw;
    }
}

bool DiagnosticVisitor::isNumericType(const std::string& type) {
    return type == "int" || type == "float";
}

std::string DiagnosticVisitor::promoteTypes(const std::string& type1, const std::string& type2) {
    if (type1 == "float" || type2 == "float") return "float";
    return "int";
}

bool DiagnosticVisitor::areTypesCompatible(const std::string& expected, const std::string& actual) {
    if (expected == actual) return true;
    if (expected == "float" && actual == "int") return true;
    return false;
}

} // namespace pryst
