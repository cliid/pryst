#include "semantic_analyzer.hpp"
#include "utils/debug.hpp"
#include <stdexcept>
#include <sstream>
#include <regex>

namespace pryst {

SemanticAnalyzer::SemanticAnalyzer() : currentFunction(""), inLoop(false) {}

std::any SemanticAnalyzer::visitProgram(PrystParser::ProgramContext* ctx) {
    PRYST_DEBUG("Visiting program");
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return nullptr;
}

std::any SemanticAnalyzer::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    PRYST_DEBUG("Visiting declaration");
    return visitChildren(ctx);
}

std::any SemanticAnalyzer::visitNamespaceDecl(PrystParser::NamespaceDeclContext* ctx) {
    PRYST_DEBUG("Visiting namespace declaration");
    auto qualifiedId = visit(ctx->qualifiedIdentifier());
    std::string name = std::any_cast<std::string>(qualifiedId);
    currentNamespace.push_back(name);

    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    currentNamespace.pop_back();
    return nullptr;
}

std::any SemanticAnalyzer::visitModuleDecl(PrystParser::ModuleDeclContext* ctx) {
    PRYST_DEBUG("Visiting module declaration");
    auto qualifiedId = visit(ctx->qualifiedIdentifier());
    std::string name = std::any_cast<std::string>(qualifiedId);
    currentModule = name;

    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    currentModule.clear();
    return nullptr;
}

std::any SemanticAnalyzer::visitImportDecl(PrystParser::ImportDeclContext* ctx) {
    try {
        std::string importPath = ctx->qualifiedIdentifier()->getText();
        PRYST_DEBUG("Processing import declaration: " + importPath);

        if (!moduleLoader.loadModule(importPath)) {
            PRYST_ERROR("Failed to load module: " + importPath);
            return nullptr;
        }

        return nullptr;
    } catch (const std::exception& ex) {
        PRYST_ERROR("Failed to load module - " + std::string(ex.what()));
        return nullptr;
    }
}

std::any SemanticAnalyzer::visitUsingDecl(PrystParser::UsingDeclContext* ctx) {
    PRYST_DEBUG("Visiting using declaration");
    auto qualifiedId = visit(ctx->qualifiedIdentifier());
    std::string target = std::any_cast<std::string>(qualifiedId);
    symbolTable.addUsingDeclaration(target, ctx->MODULE() != nullptr);
    return nullptr;
}

std::any SemanticAnalyzer::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    PRYST_DEBUG("Visiting function declaration");
    if (ctx->forwardDecl()) {
        return visit(ctx->forwardDecl());
    } else if (ctx->namedFunction()) {
        return visit(ctx->namedFunction());
    } else if (ctx->lambdaFunction()) {
        return visit(ctx->lambdaFunction());
    }
    return nullptr;
}

std::any SemanticAnalyzer::visitForwardDecl(PrystParser::ForwardDeclContext* ctx) {
    PRYST_DEBUG("Visiting forward declaration");
    std::string name = ctx->IDENTIFIER()->getText();
    std::string returnType = std::any_cast<std::string>(visit(ctx->type()));

    // Process parameters
    std::vector<std::string> paramTypes;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            std::string paramType = std::any_cast<std::string>(visit(param->type()));
            paramTypes.push_back(paramType);
        }
    }

    // Add forward declaration to symbol table
    symbolTable.addForwardDeclaration(name, returnType, paramTypes,
                                    ctx->getStart()->getLine() + ":" +
                                    ctx->getStart()->getCharPositionInLine());
    return nullptr;
}

std::any SemanticAnalyzer::visitNamedFunction(PrystParser::NamedFunctionContext* ctx) {
    PRYST_DEBUG("Visiting named function");
    std::string name = ctx->IDENTIFIER()->getText();
    std::string returnType;

    // Get return type based on function declaration style
    if (ctx->FN() && ctx->LESS()) {
        returnType = std::any_cast<std::string>(visit(ctx->type()));
    } else if (ctx->ARROW()) {
        returnType = std::any_cast<std::string>(visit(ctx->type()));
    } else {
        returnType = std::any_cast<std::string>(visit(ctx->type()));
    }

    currentFunction = name;

    // Process parameters
    std::vector<std::string> paramTypes;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            std::string paramType = std::any_cast<std::string>(visit(param->type()));
            paramTypes.push_back(paramType);
            symbolTable.addVariable(param->IDENTIFIER()->getText(), paramType);
        }
    }

    // Check if this implements a forward declaration
    if (symbolTable.isForwardDeclared(name)) {
        symbolTable.implementFunction(name, paramTypes);
    } else {
        symbolTable.addFunction(name, returnType, paramTypes);
    }

    visit(ctx->block());
    currentFunction.clear();
    return nullptr;
}

std::any SemanticAnalyzer::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    PRYST_DEBUG("Visiting variable declaration");
    std::string name = ctx->IDENTIFIER()->getText();
    std::string type = std::any_cast<std::string>(visit(ctx->type()));

    if (ctx->expression()) {
        std::string exprType = std::any_cast<std::string>(visit(ctx->expression()));
        if (!areTypesCompatible(type, exprType)) {
            throw std::runtime_error("Type mismatch in variable declaration: " + name);
        }
    }

    symbolTable.addVariable(name, type);
    return nullptr;
}

std::any SemanticAnalyzer::visitPrimary(PrystParser::PrimaryContext* ctx) {
    if (!ctx) {
        PRYST_ERROR("Null primary context");
        throw std::runtime_error("Null primary context");
    }

    PRYST_DEBUG("Visiting primary expression");

    try {
        if (ctx->TRUE() || ctx->FALSE()) {
            PRYST_DEBUG("Processing boolean literal");
            return std::any(std::string("bool"));
        }

        if (ctx->NULL_()) {
            PRYST_DEBUG("Processing null literal");
            return std::any(std::string("null"));
        }

        if (ctx->NUMBER()) {
            PRYST_DEBUG("Processing number literal");
            if (!ctx->NUMBER()->getText().empty()) {
                std::string numStr = ctx->NUMBER()->getText();
                return std::any(std::string(numStr.find('.') != std::string::npos ? "float" : "int"));
            }
            throw std::runtime_error("Invalid number literal");
        }

        if (ctx->STRING()) {
            PRYST_DEBUG("Processing string literal");
            std::string str = ctx->STRING()->getText();
            // Remove quotes
            str = str.substr(1, str.length() - 2);

            // Check for string interpolation
            std::regex interpolationPattern("\\{([^}]+)\\}");
            if (std::regex_search(str, interpolationPattern)) {
                PRYST_DEBUG("Found string interpolation pattern");
                std::smatch match;
                std::string::const_iterator searchStart(str.cbegin());
                while (std::regex_search(searchStart, str.cend(), match, interpolationPattern)) {
                    std::string expr = match[1].str();
                    PRYST_DEBUG("Checking interpolated expression: " + expr);

                    size_t formatPos = expr.find(':');
                    std::string varName = formatPos != std::string::npos ? expr.substr(0, formatPos) : expr;
                    std::string formatSpec = formatPos != std::string::npos ? expr.substr(formatPos + 1) : "";

                    if (!symbolTable.variableExists(varName)) {
                        PRYST_ERROR("Unknown variable in string interpolation: " + varName);
                        throw std::runtime_error("Unknown variable in string interpolation: " + varName);
                    }

                    std::string varType = symbolTable.getVariableType(varName);
                    PRYST_DEBUG("Variable type in interpolation: " + varType);

                    if (!formatSpec.empty() && formatSpec.find('f') != std::string::npos && varType != "float") {
                        PRYST_ERROR("Format specifier 'f' can only be used with float type");
                        throw std::runtime_error("Format specifier 'f' can only be used with float type");
                    }

                    searchStart = match.suffix().first;
                }
            }
            return std::any(std::string("str"));
        }

        if (ctx->qualifiedIdentifier()) {
            if (!ctx->qualifiedIdentifier()->getText().empty()) {
                std::string name = ctx->qualifiedIdentifier()->getText();
                PRYST_DEBUG("Processing qualified identifier: " + name);

                // First check if it's a variable
                if (symbolTable.variableExists(name)) {
                    PRYST_DEBUG("Found variable: " + name);
                    std::string varType = symbolTable.getVariableType(name);
                    PRYST_DEBUG("Variable type: " + varType);

                    try {
                        // If it's a function call, check if the variable is a lambda function
                        if (ctx->LPAREN() && varType.length() >= 3 && varType.substr(0, 3) == "fn<") {
                            PRYST_DEBUG("Processing lambda function call");
                            // Parse the lambda function type to get return and param types
                            size_t returnTypeStart = 3;
                            size_t returnTypeEnd = varType.find('>', returnTypeStart);
                            if (returnTypeEnd == std::string::npos) {
                                throw std::runtime_error("Invalid lambda function type: " + varType);
                            }
                            std::string returnType = varType.substr(returnTypeStart, returnTypeEnd - returnTypeStart);
                            PRYST_DEBUG("Lambda return type: " + returnType);

                            // Extract parameter types
                            std::vector<std::string> paramTypes;
                            size_t pos = returnTypeEnd + 1;
                            while (pos < varType.length()) {
                                if (varType[pos] == '(') {
                                    size_t end = varType.find(')', pos);
                                    if (end == std::string::npos) break;
                                    std::string paramType = varType.substr(pos + 1, end - pos - 1);
                                    PRYST_DEBUG("Found parameter type: " + paramType);
                                    paramTypes.push_back(paramType);
                                    pos = end + 1;
                                } else {
                                    pos++;
                                }
                            }

                            // Check argument count
                            size_t actualArgs = ctx->arguments() ? ctx->arguments()->expression().size() : 0;
                            PRYST_DEBUG("Checking argument count: expected=" + std::to_string(paramTypes.size()) +
                                      ", actual=" + std::to_string(actualArgs));
                            if (actualArgs != paramTypes.size()) {
                                throw std::runtime_error("Wrong number of arguments for lambda function " + name +
                                                      ". Expected " + std::to_string(paramTypes.size()) +
                                                      ", got " + std::to_string(actualArgs));
                            }

                            // Check argument types
                            if (ctx->arguments()) {
                                PRYST_DEBUG("Checking argument types");
                                for (size_t i = 0; i < actualArgs; i++) {
                                    auto expr = ctx->arguments()->expression(i);
                                    if (!expr) {
                                        throw std::runtime_error("Null expression in argument " + std::to_string(i + 1));
                                    }
                                    auto argResult = visit(expr);
                                    std::string argType = std::any_cast<std::string>(argResult);
                                    PRYST_DEBUG("Argument " + std::to_string(i + 1) + " type: " + argType);
                                    checkTypes(paramTypes[i], argType,
                                             "Type mismatch in argument " + std::to_string(i + 1) +
                                             " of lambda function " + name);
                                }
                            }

                            PRYST_DEBUG("Lambda function call validated, returning type: " + returnType);
                            return std::any(returnType);
                        }
                    } catch (const std::exception& e) {
                        PRYST_DEBUG("Error processing lambda function: " + std::string(e.what()));
                        throw;
                    }
                    return std::any(varType);
                }

                // If not a variable, check if it's a regular function call
                if (ctx->LPAREN()) {
                    PRYST_DEBUG("Looking up function: " + name);
                    auto funcInfo = symbolTable.lookupFunction(name);
                    if (!funcInfo) {
                        throw std::runtime_error("Unknown function: " + name);
                    }

                    // Check argument count
                    size_t expectedArgs = funcInfo->paramTypes.size();
                    size_t actualArgs = 0;

                    if (ctx->arguments()) {
                        actualArgs = ctx->arguments()->expression().size();
                    }
                    PRYST_DEBUG("Checking function arguments: expected=" + std::to_string(expectedArgs) +
                               ", actual=" + std::to_string(actualArgs));

                    if (actualArgs != expectedArgs) {
                        throw std::runtime_error("Wrong number of arguments for function " + name +
                                               ". Expected " + std::to_string(expectedArgs) +
                                               ", got " + std::to_string(actualArgs));
                    }

                    // Check argument types
                    if (ctx->arguments()) {
                        PRYST_DEBUG("Checking function argument types");
                        for (size_t i = 0; i < actualArgs; i++) {
                            auto expr = ctx->arguments()->expression(i);
                            if (!expr) {
                                throw std::runtime_error("Null expression in argument " + std::to_string(i + 1));
                            }
                            auto argResult = visit(expr);
                            std::string argType = std::any_cast<std::string>(argResult);
                            PRYST_DEBUG("Function argument " + std::to_string(i + 1) + " type: " + argType);
                            checkTypes(funcInfo->paramTypes[i], argType,
                                     "Type mismatch in argument " + std::to_string(i + 1) +
                                     " of function " + name);
                        }
                    }

                    PRYST_DEBUG("Function call validated, returning type: " + funcInfo->returnType);
                    return std::any(funcInfo->returnType);
                }

                throw std::runtime_error("Unknown identifier: " + name);
            }
            throw std::runtime_error("Empty qualified identifier");
        } else if (ctx->LPAREN() && ctx->expression()) {
            PRYST_DEBUG("Processing parenthesized expression");
            return visit(ctx->expression());
        } else if (ctx->SUPER()) {
            throw std::runtime_error("'super' keyword not implemented");
        } else if (ctx->newExpression()) {
            PRYST_DEBUG("Processing new expression");
            return visit(ctx->newExpression());
        }

        throw std::runtime_error("Invalid primary expression");
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in visitPrimary: " + std::string(ex.what()));
        throw;
    }
}

std::any SemanticAnalyzer::visitQualifiedIdentifier(PrystParser::QualifiedIdentifierContext* ctx) {
    if (!ctx) {
        PRYST_ERROR("Null qualified identifier context");
        throw std::runtime_error("Null qualified identifier context");
    }

    PRYST_DEBUG("Visiting qualified identifier");

    try {
        std::string identifier;
        for (auto id : ctx->IDENTIFIER()) {
            if (!identifier.empty()) {
                identifier += "::";
            }
            identifier += id->getText();
        }

        PRYST_DEBUG("Processing qualified identifier: " + identifier);

        // Check if it's a variable
        if (symbolTable.variableExists(identifier)) {
            PRYST_DEBUG("Found variable: " + identifier);
            return std::any(symbolTable.getVariableType(identifier));
        }

        // Check if it's a function
        if (auto funcInfo = symbolTable.lookupFunction(identifier)) {
            PRYST_DEBUG("Found function: " + identifier);
            return std::any(funcInfo->returnType);
        }

        // Check if it's a module
        if (symbolTable.moduleExists(identifier)) {
            PRYST_DEBUG("Found module: " + identifier);
            return std::any("module");
        }

        // Check if it's a namespace
        if (symbolTable.namespaceExists(identifier)) {
            PRYST_DEBUG("Found namespace: " + identifier);
            return std::any("namespace");
        }

        PRYST_ERROR("Unknown identifier: " + identifier);
        throw std::runtime_error("Unknown identifier: " + identifier);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in visitQualifiedIdentifier: " + std::string(ex.what()));
        throw;
    }
}

std::string SemanticAnalyzer::getExpressionType(antlr4::tree::ParseTree* ctx) {
    try {
        auto result = visit(ctx);
        return std::any_cast<std::string>(result);
    } catch (const std::exception& ex) {
        PRYST_ERROR("Error in getExpressionType: " + std::string(ex.what()));
        return "error";
    }
}

bool SemanticAnalyzer::areTypesCompatible(const std::string& expected, const std::string& actual) {
    if (expected == actual) return true;
    if (expected == "float" && actual == "int") return true;
    return false;
}

std::string SemanticAnalyzer::resolveType(const std::string& type) {
    if (type == "int" || type == "float" || type == "bool" || type == "string" || type == "void") {
        return type;
    }

    // Check if it's a class type
    if (symbolTable.isClassDefined(type)) {
        return type;
    }

    // Check if it's a qualified type (with namespace)
    size_t pos = type.find("::");
    if (pos != std::string::npos) {
        std::string ns = type.substr(0, pos);
        std::string className = type.substr(pos + 2);
        if (symbolTable.isClassDefinedInNamespace(className, ns)) {
            return type;
        }
    }

    throw std::runtime_error("Unknown type: " + type);
}

void SemanticAnalyzer::checkVariableUsage(const std::string& name, antlr4::tree::ParseTree* ctx) {
    if (!symbolTable.isVariableDefined(name)) {
        std::stringstream ss;
        ss << "Variable '" << name << "' is not defined";
        throw std::runtime_error(ss.str());
    }
}

} // namespace pryst
