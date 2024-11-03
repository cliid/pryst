#include "semantic_analyzer.hpp"
#include "module_loader.hpp"
#include "../codegen/type_registry.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>

SemanticAnalyzer::SemanticAnalyzer() : currentFunction(""), symbolTable(), moduleLoader(std::make_shared<ModuleLoader>()) {
    try {
        std::cerr << "DEBUG: Starting SemanticAnalyzer initialization" << std::endl;

        // Get TypeRegistry instance and verify basic types
        auto& registry = TypeRegistry::getInstance();
        std::cerr << "DEBUG: Got TypeRegistry instance" << std::endl;

        // Verify each basic type exists
        if (!registry.getIntType()) {
            throw std::runtime_error("Int type not initialized in TypeRegistry");
        }
        std::cerr << "DEBUG: Verified int type" << std::endl;

        if (!registry.getFloatType()) {
            throw std::runtime_error("Float type not initialized in TypeRegistry");
        }
        std::cerr << "DEBUG: Verified float type" << std::endl;

        if (!registry.getBoolType()) {
            throw std::runtime_error("Bool type not initialized in TypeRegistry");
        }
        std::cerr << "DEBUG: Verified bool type" << std::endl;

        if (!registry.getStrType()) {
            throw std::runtime_error("String type not initialized in TypeRegistry");
        }
        std::cerr << "DEBUG: Verified string type" << std::endl;

        // Register print functions with both SymbolTable and TypeRegistry
        std::cerr << "DEBUG: Registering print functions" << std::endl;
        symbolTable.addFunction("print", "void", {"int"});
        symbolTable.addFunction("print", "void", {"float"});
        symbolTable.addFunction("print", "void", {"bool"});
        symbolTable.addFunction("print", "void", {"str"});

        std::cerr << "DEBUG: SemanticAnalyzer initialization completed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: SemanticAnalyzer initialization failed: " << e.what() << std::endl;
        throw;
    }
}

// Add semantic analyzer methods here...



// ******************** SemanticAnalyzer Implementation *********************

bool areTypesCompatibleForEquality(const std::string& type1, const std::string& type2);
bool areTypesCompatibleForComparison(const std::string& type1, const std::string& type2);

std::any SemanticAnalyzer::visitProgram(PrystParser::ProgramContext* ctx) {
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return std::any();
}

std::any SemanticAnalyzer::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    if (ctx->functionDecl()) {
        visit(ctx->functionDecl());
    } else if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->classDeclaration()) {
        visit(ctx->classDeclaration());
    } else {
        visit(ctx->statement());
    }
    return std::any();
}

std::any SemanticAnalyzer::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    if (ctx->namedFunction()) {
        return visit(ctx->namedFunction());
    } else if (ctx->lambdaFunction()) {
        return visit(ctx->lambdaFunction());
    }
    return std::any();
}

std::any SemanticAnalyzer::visitNamedFunction(PrystParser::NamedFunctionContext* ctx) {
    std::string functionName = ctx->IDENTIFIER()->getText();
    if (functionName == "print") {
        throw std::runtime_error("Cannot redeclare built-in function 'print'");
    }
    std::string returnType = ctx->type()->getText();

    if (symbolTable.functionExists(functionName)) {
        throw std::runtime_error("Function '" + functionName + "' already declared");
    }

    std::vector<std::string> paramTypes;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(param->type()->getText());
        }
    }

    symbolTable.addFunction(functionName, returnType, paramTypes);

    currentFunction = functionName;

    symbolTable.pushScope();

    if (ctx->paramList()) {
        size_t idx = 0;
        for (auto param : ctx->paramList()->param()) {
            std::string paramName = param->IDENTIFIER()->getText();
            std::string paramType = paramTypes[idx];
            symbolTable.addVariable(paramName, paramType, false);  // Parameters are not const by default
            ++idx;
        }
    }

    // Process function body declarations
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    symbolTable.popScope();

    currentFunction.clear();

    return std::any();
}

std::any SemanticAnalyzer::visitLambdaFunction(PrystParser::LambdaFunctionContext* ctx) {
    std::string returnType = ctx->type()->getText();
    std::vector<std::string> paramTypes;

    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(param->type()->getText());
        }
    }

    symbolTable.pushScope();

    if (ctx->paramList()) {
        size_t idx = 0;
        for (auto param : ctx->paramList()->param()) {
            std::string paramName = param->IDENTIFIER()->getText();
            std::string paramType = paramTypes[idx];
            symbolTable.addVariable(paramName, paramType, false);  // Lambda parameters are not const by default
            ++idx;
        }
    }

    // Process function body declarations
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    symbolTable.popScope();

    return std::any();
}

std::any SemanticAnalyzer::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string varType = ctx->type()->getText();

    std::cout << varName << " " << varType << std::endl;

    if (symbolTable.variableExistsInCurrentScope(varName)) {
        throw std::runtime_error("Variable '" + varName + "' already declared in this scope");
    }

    symbolTable.addVariable(varName, varType, false);  // Variables are not const by default

    if (ctx->expression()) {
        auto exprResult = visit(ctx->expression());
        if (exprResult.type() != typeid(std::string)) {
            throw std::runtime_error("Expression did not return a type string");
        }
        std::string exprType = std::any_cast<std::string>(exprResult);
        checkTypes(varType, exprType, "Type mismatch in variable declaration");
    }

    return std::any();
}

std::any SemanticAnalyzer::visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) {
    std::string className = ctx->IDENTIFIER(0)->getText();

    std::string superClassName;
    if (ctx->EXTENDS()) {
        superClassName = ctx->IDENTIFIER(1)->getText();

        if (!symbolTable.classExists(superClassName)) {
            throw std::runtime_error("Undefined superclass: '" + superClassName + "'");
        }
    }

    if (symbolTable.classExists(className)) {
        throw std::runtime_error("Class '" + className + "' already declared");
    }

    SymbolTable::ClassInfo classInfo;
    classInfo.superClassName = superClassName;

    symbolTable.pushScope();

    if (ctx->classBody()) {
        for (auto memberCtx : ctx->classBody()->classMember()) {
            visit(memberCtx);  // This will call visitClassVariableDecl or visitClassFunctionDecl
        }
    }

    classInfo.members = symbolTable.getCurrentScopeVariables();
    classInfo.methods = symbolTable.getCurrentScopeFunctions();

    symbolTable.clearCurrentScopeVariables();
    symbolTable.clearCurrentScopeFunctions();

    symbolTable.popScope();

    symbolTable.addClass(className, classInfo);

    return std::any();
}

std::any SemanticAnalyzer::visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) {
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string varType = ctx->type()->getText();

    if (symbolTable.variableExistsInCurrentScope(varName)) {
        throw std::runtime_error("Variable '" + varName + "' already declared in this scope");
    }

    symbolTable.addVariable(varName, varType, false);  // Class member variables are not const by default

    if (ctx->expression()) {
        auto exprResult = visit(ctx->expression());
        if (exprResult.type() != typeid(std::string)) {
            throw std::runtime_error("Expression did not return a type string");
        }
        std::string exprType = std::any_cast<std::string>(exprResult);
        checkTypes(varType, exprType, "Type mismatch in variable declaration");
    }

    return std::any();
}

std::any SemanticAnalyzer::visitExpression(PrystParser::ExpressionContext* ctx) {
    if (ctx->assignment()) {
        return visit(ctx->assignment());
    } else {
        return visit(ctx->logicOr());
    }
}

std::any SemanticAnalyzer::visitAssignment(PrystParser::AssignmentContext* ctx) {
    std::string varType;

    if (ctx->call()) {
        auto callResult = visit(ctx->call());
        if (callResult.type() != typeid(std::string)) {
            throw std::runtime_error("Call did not return a type string");
        }
        std::string objectType = std::any_cast<std::string>(callResult);

        if (ctx->IDENTIFIER() == nullptr) {
            throw std::runtime_error("Expected identifier in member assignment");
        }
        std::string memberName = ctx->IDENTIFIER()->getText();

        varType = getMemberVariableType(objectType, memberName);
    } else {
        if (ctx->IDENTIFIER() == nullptr) {
            throw std::runtime_error("Expected identifier in assignment");
        }
        std::string varName = ctx->IDENTIFIER()->getText();

        if (!symbolTable.variableExists(varName)) {
            throw std::runtime_error("Undefined variable: '" + varName + "'");
        }

        varType = symbolTable.getVariableType(varName);
    }

    auto exprResult = visit(ctx->expression());
    if (exprResult.type() != typeid(std::string)) {
        throw std::runtime_error("Expression did not return a type string");
    }
    std::string exprType = std::any_cast<std::string>(exprResult);
    std::cout << exprType << std::endl;

    checkTypes(varType, exprType, "Type mismatch in assignment");

    return std::any(varType);
}

std::any SemanticAnalyzer::visitLogicOr(PrystParser::LogicOrContext* ctx) {
    auto leftType = visit(ctx->logicAnd(0));
    if (leftType.type() != typeid(std::string)) {
        throw std::runtime_error("LogicAnd did not return a type string");
    }
    std::string type = std::any_cast<std::string>(leftType);

    if (ctx->logicAnd().size() > 1) {
        checkTypes(type, "bool", "Left operand of logical OR must be boolean");
        for (size_t i = 1; i < ctx->logicAnd().size(); ++i) {
            auto rightType = visit(ctx->logicAnd(i));
            if (rightType.type() != typeid(std::string)) {
                throw std::runtime_error("LogicAnd did not return a type string");
            }
            std::string rightTypeStr = std::any_cast<std::string>(rightType);
            checkTypes(rightTypeStr, "bool", "Right operand of logical OR must be boolean");
        }
        type = "bool";
    }

    return std::any(type);
}

std::any SemanticAnalyzer::visitLogicAnd(PrystParser::LogicAndContext* ctx) {
    auto leftType = visit(ctx->equality(0));
    if (leftType.type() != typeid(std::string)) {
        throw std::runtime_error("Equality did not return a type string");
    }
    std::string type = std::any_cast<std::string>(leftType);

    if (ctx->equality().size() > 1) {
        checkTypes(type, "bool", "Left operand of logical AND must be boolean");
        for (size_t i = 1; i < ctx->equality().size(); ++i) {
            auto rightType = visit(ctx->equality(i));
            if (rightType.type() != typeid(std::string)) {
                throw std::runtime_error("Equality did not return a type string");
            }
            std::string rightTypeStr = std::any_cast<std::string>(rightType);
            checkTypes(rightTypeStr, "bool", "Right operand of logical AND must be boolean");
        }
        type = "bool";
    }

    return std::any(type);
}

std::any SemanticAnalyzer::visitEquality(PrystParser::EqualityContext* ctx) {
    auto leftType = visit(ctx->comparison(0));
    if (leftType.type() != typeid(std::string)) {
        throw std::runtime_error("Comparison did not return a type string");
    }
    std::string type = std::any_cast<std::string>(leftType);

    for (size_t i = 1; i < ctx->comparison().size(); ++i) {
        auto rightType = visit(ctx->comparison(i));
        if (rightType.type() != typeid(std::string)) {
            throw std::runtime_error("Comparison did not return a type string");
        }
        std::string rightTypeStr = std::any_cast<std::string>(rightType);
        
        if (!areTypesCompatibleForEquality(type, rightTypeStr)) {
            throw std::runtime_error("Type mismatch in equality comparison: '" + type + "' and '" + rightTypeStr + "'");
        }
        
        type = "bool";
    }

    return std::any(type);
}

std::any SemanticAnalyzer::visitComparison(PrystParser::ComparisonContext* ctx) {
    auto leftType = visit(ctx->addition(0));
    if (leftType.type() != typeid(std::string)) {
        throw std::runtime_error("Addition did not return a type string");
    }
    std::string type = std::any_cast<std::string>(leftType);

    for (size_t i = 1; i < ctx->addition().size(); ++i) {
        auto rightType = visit(ctx->addition(i));
        if (rightType.type() != typeid(std::string)) {
            throw std::runtime_error("Addition did not return a type string");
        }
        std::string rightTypeStr = std::any_cast<std::string>(rightType);
        
        if (!areTypesCompatibleForComparison(type, rightTypeStr)) {
            throw std::runtime_error("Type mismatch in comparison: '" + type + "' and '" + rightTypeStr + "'");
        }
        
        type = "bool";
    }

    return std::any(type);
}

// Helper functions

bool areTypesCompatibleForEquality(const std::string& type1, const std::string& type2) {
    if (type1 == type2) return true;
    if ((type1 == "int" || type1 == "float") && (type2 == "int" || type2 == "float")) return true;
    return false;
}

bool areTypesCompatibleForComparison(const std::string& type1, const std::string& type2) {
    return (type1 == "int" || type1 == "float") && (type2 == "int" || type2 == "float");
}


std::any SemanticAnalyzer::visitAddition(PrystParser::AdditionContext* ctx) {
    auto typeResult = visit(ctx->multiplication(0));
    if (typeResult.type() != typeid(std::string)) {
        throw std::runtime_error("Multiplication did not return a type string");
    }
    std::string type = std::any_cast<std::string>(typeResult);

    for (size_t i = 1; i < ctx->multiplication().size(); ++i) {
        auto rightTypeResult = visit(ctx->multiplication(i));
        if (rightTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("Multiplication did not return a type string");
        }
        std::string rightType = std::any_cast<std::string>(rightTypeResult);
        if (type == "str" && rightType == "str") {
            type = "str";
            continue;
        }
        checkTypes(type, rightType, "Type mismatch in addition/subtraction");
        if (type != "int" && type != "float") {
            throw std::runtime_error("Addition/subtraction requires numeric operands");
        }
    }

    return std::any(type);
}

std::any SemanticAnalyzer::visitMultiplication(PrystParser::MultiplicationContext* ctx) {
    auto typeResult = visit(ctx->unary(0));
    if (typeResult.type() != typeid(std::string)) {
        throw std::runtime_error("Unary did not return a type string");
    }
    std::string type = std::any_cast<std::string>(typeResult);

    for (size_t i = 1; i < ctx->unary().size(); ++i) {
        auto rightTypeResult = visit(ctx->unary(i));
        if (rightTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("Unary did not return a type string");
        }
        std::string rightType = std::any_cast<std::string>(rightTypeResult);
        checkTypes(type, rightType, "Type mismatch in multiplication/division");
        if (type != "int" && type != "float") {
            throw std::runtime_error("Multiplication/division requires numeric operands");
        }
    }

    return std::any(type);
}

std::any SemanticAnalyzer::visitUnary(PrystParser::UnaryContext* ctx) {
    if (ctx->unary()) {
        auto typeResult = visit(ctx->unary());
        if (typeResult.type() != typeid(std::string)) {
            throw std::runtime_error("Unary did not return a type string");
        }
        std::string type = std::any_cast<std::string>(typeResult);
        if (ctx->BANG()) {
            checkTypes(type, "bool", "Logical NOT operation requires boolean operand");
            return std::any(std::string("bool"));
        } else if (ctx->MINUS()) {
            if (type != "int" && type != "float") {
                throw std::runtime_error("Unary minus requires numeric operand");
            }
            return std::any(type);
        } else if (ctx->INCREMENT() || ctx->DECREMENT()) {
            if (type != "int") {
                throw std::runtime_error("Increment/decrement requires integer operand");
            }
            return std::any(std::string("int"));
        }
    } else {
        return visit(ctx->postfix());
    }
    throw std::runtime_error("Invalid unary operation");
}

std::any SemanticAnalyzer::visitPostfix(PrystParser::PostfixContext* ctx) {
    auto typeResult = visit(ctx->primary());
    if (typeResult.type() != typeid(std::string)) {
        throw std::runtime_error("Primary did not return a type string");
    }
    std::string type = std::any_cast<std::string>(typeResult);

    if (!ctx->INCREMENT().empty() || !ctx->DECREMENT().empty()) {
        if (type != "int") {
            throw std::runtime_error("Increment/decrement requires integer operand");
        }
        return std::any(std::string("int"));
    }

    return std::any(type);
}

std::any SemanticAnalyzer::visitCall(PrystParser::CallContext* ctx) {
    auto typeResult = visit(ctx->primary());
    if (typeResult.type() != typeid(std::string)) {
        throw std::runtime_error("Primary did not return a type string");
    }
    std::string type = std::any_cast<std::string>(typeResult);

    // Process member access chain
    for (auto identifier : ctx->IDENTIFIER()) {
        std::string memberName = identifier->getText();
        currentCallType = type;

        if (!symbolTable.classExists(type)) {
            throw std::runtime_error("Type '" + type + "' has no members");
        }

        SymbolTable::ClassInfo classInfo = symbolTable.getClassInfo(type);
        if (classInfo.members.find(memberName) != classInfo.members.end()) {
            type = classInfo.members[memberName].type;
        } else if (classInfo.methods.find(memberName) != classInfo.methods.end()) {
            type = classInfo.methods[memberName].returnType;
        } else {
            throw std::runtime_error("Class '" + type + "' has no member named '" + memberName + "'");
        }
    }

    return std::any(type);
}

std::any SemanticAnalyzer::visitCallSuffix(PrystParser::CallSuffixContext* ctx) {
    throw std::runtime_error("CallSuffix should not be called directly");
}

std::any SemanticAnalyzer::visitPrimary(PrystParser::PrimaryContext* ctx) {
    if (ctx->TRUE() || ctx->FALSE()) {
        return std::any(std::string("bool"));
    } else if (ctx->NULL_()) {
        return std::any(std::string("null"));
    } else if (ctx->NUMBER()) {
        std::string numStr = ctx->NUMBER()->getText();
        return std::any(std::string(numStr.find('.') != std::string::npos ? "float" : "int"));
    } else if (ctx->STRING()) {
        return std::any(std::string("str"));
    } else if (ctx->IDENTIFIER()) {
        std::string name = ctx->IDENTIFIER()->getText();

        if (ctx->LPAREN()) {  // Function call
            if (!symbolTable.functionExists(name)) {
                throw std::runtime_error("Undefined function: '" + name + "'");
            }

            SymbolTable::FunctionInfo funcInfo = symbolTable.getFunctionInfo(name);
            size_t argCount = ctx->arguments() ? ctx->arguments()->expression().size() : 0;

            // Special handling for print function
            if (name == "print") {
                if (argCount != 1) {
                    throw std::runtime_error("print function expects exactly one argument");
                }
                auto argTypeResult = visit(ctx->arguments()->expression(0));
                if (argTypeResult.type() != typeid(std::string)) {
                    throw std::runtime_error("Argument expression did not return a type string");
                }
                std::string argType = std::any_cast<std::string>(argTypeResult);
                if (argType != "int" && argType != "float" && argType != "bool" && argType != "str") {
                    throw std::runtime_error("print function only accepts int, float, bool, or str arguments");
                }
                return std::any(std::string("void"));
            }

            // Regular function call
            if (argCount != funcInfo.paramTypes.size()) {
                throw std::runtime_error("Function '" + name + "' expects " +
                                      std::to_string(funcInfo.paramTypes.size()) + " arguments, got " +
                                      std::to_string(argCount));
            }

            if (ctx->arguments()) {
                for (size_t i = 0; i < argCount; ++i) {
                    auto argTypeResult = visit(ctx->arguments()->expression(i));
                    if (argTypeResult.type() != typeid(std::string)) {
                        throw std::runtime_error("Argument expression did not return a type string");
                    }
                    std::string argType = std::any_cast<std::string>(argTypeResult);
                    checkTypes(funcInfo.paramTypes[i], argType, "Type mismatch in function call argument");
                }
            }

            return std::any(funcInfo.returnType);
        }

        if (symbolTable.variableExists(name)) {
            return std::any(symbolTable.getVariableType(name));
        } else if (symbolTable.functionExists(name)) {
            return std::any(name);
        } else if (symbolTable.classExists(name)) {
            return std::any(name);
        } else {
            throw std::runtime_error("Undefined identifier: '" + name + "'");
        }
    } else if (ctx->LPAREN()) {
        return visit(ctx->expression());
    } else if (ctx->SUPER()) {
        throw std::runtime_error("'super' keyword not implemented");
    } else if (ctx->newExpression()) {
        return visit(ctx->newExpression());
    }

    throw std::runtime_error("Unexpected primary expression");
}

std::any SemanticAnalyzer::visitNewExpression(PrystParser::NewExpressionContext* ctx) {
    std::string className = ctx->IDENTIFIER()->getText();

    if (!symbolTable.classExists(className)) {
        throw std::runtime_error("Undefined class: '" + className + "'");
    }

    size_t argCount = ctx->arguments() ? ctx->arguments()->expression().size() : 0;

    if (argCount > 0) {
        throw std::runtime_error("Constructors with arguments are not implemented");
    }

    return std::any(className);
}

std::any SemanticAnalyzer::visitExprStatement(PrystParser::ExprStatementContext* ctx) {
    visit(ctx->expression());
    return std::any();
}

std::any SemanticAnalyzer::visitIfStatement(PrystParser::IfStatementContext* ctx) {
    auto conditionTypeResult = visit(ctx->expression());
    if (conditionTypeResult.type() != typeid(std::string)) {
        throw std::runtime_error("If condition did not return a type string");
    }
    std::string conditionType = std::any_cast<std::string>(conditionTypeResult);
    checkTypes(conditionType, "bool", "If condition must be a boolean expression");

    visit(ctx->statement(0));

    if (ctx->ELSE()) {
        visit(ctx->statement(1));
    }

    return std::any();
}

std::any SemanticAnalyzer::visitWhileStatement(PrystParser::WhileStatementContext* ctx) {
    auto conditionTypeResult = visit(ctx->expression());
    if (conditionTypeResult.type() != typeid(std::string)) {
        throw std::runtime_error("While condition did not return a type string");
    }
    std::string conditionType = std::any_cast<std::string>(conditionTypeResult);
    checkTypes(conditionType, "bool", "While condition must be a boolean expression");

    visit(ctx->statement());

    return std::any();
}

std::any SemanticAnalyzer::visitForStatement(PrystParser::ForStatementContext* ctx) {
    symbolTable.pushScope();

    if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->expression(0)) {
        visit(ctx->expression(0));
    }

    if (ctx->expression(1)) {
        auto conditionTypeResult = visit(ctx->expression(1));
        if (conditionTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("For loop condition did not return a type string");
        }
        std::string conditionType = std::any_cast<std::string>(conditionTypeResult);
        checkTypes(conditionType, "bool", "For loop condition must be a boolean expression");
    }

    if (ctx->expression(2)) {
        visit(ctx->expression(2));
    }

    visit(ctx->statement());

    symbolTable.popScope();

    return std::any();
}

std::any SemanticAnalyzer::visitReturnStatement(PrystParser::ReturnStatementContext* ctx) {
    if (currentFunction.empty()) {
        throw std::runtime_error("Return statement outside of function");
    }

    std::string expectedReturnType = symbolTable.getFunctionInfo(currentFunction).returnType;

    if (ctx->expression()) {
        auto actualReturnTypeResult = visit(ctx->expression());
        if (actualReturnTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("Return expression did not return a type string");
        }
        std::string actualReturnType = std::any_cast<std::string>(actualReturnTypeResult);
        checkTypes(expectedReturnType, actualReturnType, "Return type mismatch");
    } else {
        if (expectedReturnType != "void") {
            throw std::runtime_error("Function '" + currentFunction + "' must return a value");
        }
    }

    return std::any();
}

std::any SemanticAnalyzer::visitBlockStatement(PrystParser::BlockStatementContext* ctx) {
    symbolTable.pushScope();

    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    symbolTable.popScope();

    return std::any();
}

std::any SemanticAnalyzer::visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) {
    std::string functionName = ctx->IDENTIFIER()->getText();
    std::string returnType = ctx->type()->getText();

    if (symbolTable.functionExists(functionName)) {
        throw std::runtime_error("Function '" + functionName + "' already declared in this scope");
    }

    std::vector<std::string> paramTypes;
    if (ctx->paramList()) {
        for (auto param : ctx->paramList()->param()) {
            paramTypes.push_back(param->type()->getText());
        }
    }

    symbolTable.addFunction(functionName, returnType, paramTypes);

    currentFunction = functionName;
    symbolTable.pushScope();

    if (ctx->paramList()) {
        size_t idx = 0;
        for (auto param : ctx->paramList()->param()) {
            std::string paramName = param->IDENTIFIER()->getText();
            std::string paramType = paramTypes[idx];
            symbolTable.addVariable(paramName, paramType, false);  // Class method parameters are not const by default
            ++idx;
        }
    }

    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    symbolTable.popScope();
    currentFunction.clear();

    return std::any();
}

void SemanticAnalyzer::checkTypes(const std::string& expected, const std::string& actual, const std::string& errorMessage) {
    if (expected != actual) {
        throw std::runtime_error(errorMessage + ": expected '" + expected + "', got '" + actual + "'");
    }
}

std::string SemanticAnalyzer::getMemberVariableType(const std::string& className, const std::string& memberName) {
    if (!symbolTable.classExists(className)) {
        throw std::runtime_error("Undefined class: '" + className + "'");
    }

    SymbolTable::ClassInfo classInfo = symbolTable.getClassInfo(className);

    auto it = classInfo.members.find(memberName);
    if (it != classInfo.members.end()) {
        return it->second.type;
    } else {
        throw std::runtime_error("Class '" + className + "' has no member variable named '" + memberName + "'");
    }
}

SymbolTable::FunctionInfo SemanticAnalyzer::getMemberFunctionInfo(const std::string& className, const std::string& methodName) {
    if (!symbolTable.classExists(className)) {
        throw std::runtime_error("Undefined class: '" + className + "'");
    }

    SymbolTable::ClassInfo classInfo = symbolTable.getClassInfo(className);

    auto it = classInfo.methods.find(methodName);
    if (it != classInfo.methods.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Class '" + className + "' has no method named '" + methodName + "'");
    }
}

