#include "diagnostic_visitor.hpp"
#include "../utils/logger.hpp"
#include <sstream>

DiagnosticVisitor::DiagnosticVisitor(SymbolTable& symbolTable)
    : symbolTable(symbolTable) {}

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
        reportError(ctx, "Error in function declaration: " + std::string(ex.what()));
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
        reportError(ctx, "Error in variable declaration: " + std::string(ex.what()));
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
        reportError(ctx, "Error in binary expression: " + std::string(ex.what()));
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
        reportError(ctx, "Error in unary expression: " + std::string(ex.what()));
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
        reportError(ctx, "Error in function call: " + std::string(ex.what()));
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
        reportError(ctx, "Error in variable reference: " + std::string(ex.what()));
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
        reportError(ctx, "Error in assignment: " + std::string(ex.what()));
        throw;
    }
}

// Module and namespace support
std::any DiagnosticVisitor::visitModuleDecl(PrystParser::ModuleDeclContext* ctx) {
    PRYST_DEBUG("Visiting module declaration");
    auto qualifiedId = visit(ctx->qualifiedIdentifier());
    std::string name = std::any_cast<std::string>(qualifiedId);
    currentModule = name;
    auto result = visitChildren(ctx);
    currentModule.clear();
    return result;
}

std::any DiagnosticVisitor::visitNamespaceDecl(PrystParser::NamespaceDeclContext* ctx) {
    PRYST_DEBUG("Visiting namespace declaration");
    auto qualifiedId = visit(ctx->qualifiedIdentifier());
    std::string name = std::any_cast<std::string>(qualifiedId);
    currentNamespace.push_back(name);
    auto result = visitChildren(ctx);
    currentNamespace.pop_back();
    return result;
}

std::any DiagnosticVisitor::visitImportDecl(PrystParser::ImportDeclContext* ctx) {
    PRYST_DEBUG("Visiting import declaration");
    return visitChildren(ctx);
}

std::any DiagnosticVisitor::visitQualifiedIdentifier(PrystParser::QualifiedIdentifierContext* ctx) {
    PRYST_DEBUG("Visiting qualified identifier");
    std::string identifier;
    for (auto id : ctx->IDENTIFIER()) {
        if (!identifier.empty()) identifier += "::";
        identifier += id->getText();
    }
    return identifier;
}

// Helper methods
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

bool DiagnosticVisitor::isPrimitiveType(const std::string& type) {
    return type == "int" || type == "float" || type == "bool" || type == "string";
}

std::any DiagnosticVisitor::visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx) {
    PRYST_DEBUG("Diagnosing type cast expression");
    try {
        std::string targetType = std::any_cast<std::string>(visit(ctx->type()));
        std::string sourceType = std::any_cast<std::string>(visit(ctx->expression()));

        // Handle primitive type casting
        if (isPrimitiveType(targetType)) {
            // Numeric conversions
            if (isNumericType(targetType) && isNumericType(sourceType)) {
                return std::any(targetType);
            }
            // String conversions
            if (targetType == "string") {
                return std::any(targetType);
            }
            // Boolean conversions
            if (targetType == "bool" && isNumericType(sourceType)) {
                return std::any(targetType);
            }
            // Parse numeric from string
            if (isNumericType(targetType) && sourceType == "string") {
                return std::any(targetType);
            }
            throw std::runtime_error("Invalid primitive type cast from '" + sourceType +
                "' to '" + targetType + "'");
        }

        // Handle class type casting
        if (symbolTable.classExists(targetType)) {
            // Check if source is also a class type
            if (symbolTable.classExists(sourceType)) {
                // Check inheritance relationship
                if (!symbolTable.isSubclassOf(sourceType, targetType) &&
                    !symbolTable.hasConstructor(targetType, sourceType)) {
                    throw std::runtime_error("Cannot cast from '" + sourceType +
                        "' to '" + targetType + "': no inheritance relationship or constructor found");
                }
            } else {
                // Converting from primitive to class
                if (!symbolTable.hasConstructor(targetType, sourceType)) {
                    throw std::runtime_error("No constructor found in class '" + targetType +
                        "' for converting from type '" + sourceType + "'");
                }
            }
            return std::any(targetType);
        }

        throw std::runtime_error("Invalid cast: target type '" + targetType + "' is not recognized");
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in type cast: " + std::string(ex.what()));
        throw;
    }
}

std::any DiagnosticVisitor::visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) {
    PRYST_DEBUG("Diagnosing type conversion expression");
    try {
        std::string targetType = std::any_cast<std::string>(visit(ctx->type()));
        std::string sourceType = std::any_cast<std::string>(visit(ctx->expression()));

        // Constructor casts should not be used with primitive types
        if (isPrimitiveType(targetType)) {
            throw std::runtime_error("Constructor syntax cannot be used with primitive type '" +
                targetType + "'. Use parenthesized cast instead");
        }

        // Handle class type casting
        if (symbolTable.classExists(targetType)) {
            // Verify constructor exists for this type conversion
            if (!symbolTable.hasConstructor(targetType, sourceType)) {
                throw std::runtime_error("No constructor found in class '" + targetType +
                    "' for converting from type '" + sourceType + "'");
            }
            return std::any(targetType);
        }

        throw std::runtime_error("Invalid constructor cast: type '" + targetType + "' is not a class type");
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in type conversion: " + std::string(ex.what()));
        throw;
    }
}

} // namespace pryst
