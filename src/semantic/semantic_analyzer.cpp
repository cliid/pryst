#include "semantic_analyzer.hpp"
#include <stdexcept>
#include <iostream>

// *********************** SymbolTable Implementation ***********************

SymbolTable::SymbolTable() : currentScopeLevel(0) {}

// Scope management
void SymbolTable::pushScope() {
    ++currentScopeLevel;
}

void SymbolTable::popScope() {
    // Remove variables declared in the current scope
    for (auto it = variables.begin(); it != variables.end();) {
        if (it->second.scopeLevel == currentScopeLevel) {
            it = variables.erase(it);
        } else {
            ++it;
        }
    }
    // Remove functions declared in the current scope
    for (auto it = functions.begin(); it != functions.end();) {
        if (it->second.scopeLevel == currentScopeLevel) {
            it = functions.erase(it);
        } else {
            ++it;
        }
    }
    --currentScopeLevel;
}

int SymbolTable::getCurrentScopeLevel() const {
    return currentScopeLevel;
}

// Variable management
bool SymbolTable::variableExists(const std::string& name) const {
    return variables.find(name) != variables.end();
}

bool SymbolTable::variableExistsInCurrentScope(const std::string& name) const {
    auto it = variables.find(name);
    return it != variables.end() && it->second.scopeLevel == currentScopeLevel;
}

void SymbolTable::addVariable(const std::string& name, const std::string& type) {
    if (variableExistsInCurrentScope(name)) {
        throw std::runtime_error("Variable '" + name + "' already declared in this scope");
    }
    variables[name] = VariableInfo{type, currentScopeLevel};
}

std::string SymbolTable::getVariableType(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second.type;
    }
    throw std::runtime_error("Undefined variable: '" + name + "'");
}

std::unordered_map<std::string, SymbolTable::VariableInfo> SymbolTable::getCurrentScopeVariables() const {
    std::unordered_map<std::string, VariableInfo> currentScopeVars;
    for (const auto& [name, info] : variables) {
        if (info.scopeLevel == currentScopeLevel) {
            currentScopeVars[name] = info;
        }
    }
    return currentScopeVars;
}

void SymbolTable::clearCurrentScopeVariables() {
    for (auto it = variables.begin(); it != variables.end();) {
        if (it->second.scopeLevel == currentScopeLevel) {
            it = variables.erase(it);
        } else {
            ++it;
        }
    }
}

// Function management
bool SymbolTable::functionExists(const std::string& name) const {
    return functions.find(name) != functions.end();
}

void SymbolTable::addFunction(const std::string& name, const std::string& returnType, const std::vector<std::string>& paramTypes) {
    if (functionExists(name)) {
        throw std::runtime_error("Function '" + name + "' already declared");
    }
    functions[name] = FunctionInfo{returnType, paramTypes, currentScopeLevel};
}

SymbolTable::FunctionInfo SymbolTable::getFunctionInfo(const std::string& name) const {
    auto it = functions.find(name);
    if (it != functions.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined function: '" + name + "'");
}

std::unordered_map<std::string, SymbolTable::FunctionInfo> SymbolTable::getCurrentScopeFunctions() const {
    std::unordered_map<std::string, FunctionInfo> currentScopeFuncs;
    for (const auto& [name, info] : functions) {
        if (info.scopeLevel == currentScopeLevel) {
            currentScopeFuncs[name] = info;
        }
    }
    return currentScopeFuncs;
}

void SymbolTable::clearCurrentScopeFunctions() {
    for (auto it = functions.begin(); it != functions.end();) {
        if (it->second.scopeLevel == currentScopeLevel) {
            it = functions.erase(it);
        } else {
            ++it;
        }
    }
}

// Class management
bool SymbolTable::classExists(const std::string& name) const {
    return classes.find(name) != classes.end();
}

void SymbolTable::addClass(const std::string& name, const ClassInfo& classInfo) {
    if (classExists(name)) {
        throw std::runtime_error("Class '" + name + "' already declared");
    }
    classes[name] = classInfo;
}

SymbolTable::ClassInfo SymbolTable::getClassInfo(const std::string& name) const {
    auto it = classes.find(name);
    if (it != classes.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined class: '" + name + "'");
}

// ******************** SemanticAnalyzer Implementation *********************

SemanticAnalyzer::SemanticAnalyzer() : currentFunction("") {
    symbolTable.addFunction("print", "void", {"str"});
}

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
            symbolTable.addVariable(paramName, paramType);
            ++idx;
        }
    }

    visit(ctx->block());

    symbolTable.popScope();

    currentFunction.clear();

    return std::any();
}

std::any SemanticAnalyzer::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string varType = ctx->type()->getText();

    if (symbolTable.variableExistsInCurrentScope(varName)) {
        throw std::runtime_error("Variable '" + varName + "' already declared in this scope");
    }

    symbolTable.addVariable(varName, varType);

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

    for (auto memberCtx : ctx->classMember()) {
        visit(memberCtx);
    }

    classInfo.members = symbolTable.getCurrentScopeVariables();
    classInfo.methods = symbolTable.getCurrentScopeFunctions();

    symbolTable.clearCurrentScopeVariables();
    symbolTable.clearCurrentScopeFunctions();

    symbolTable.popScope();

    symbolTable.addClass(className, classInfo);

    return std::any();
}

std::any SemanticAnalyzer::visitClassMember(PrystParser::ClassMemberContext* ctx) {
    if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->functionDecl()) {
        visit(ctx->functionDecl());
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

        std::string memberName = ctx->IDENTIFIER()->getText();

        varType = getMemberVariableType(objectType, memberName);
    } else {
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

    checkTypes(varType, exprType, "Type mismatch in assignment");

    return std::any(varType);
}

std::any SemanticAnalyzer::visitLogicOr(PrystParser::LogicOrContext* ctx) {
    auto typeResult = visit(ctx->logicAnd(0));
    if (typeResult.type() != typeid(std::string)) {
        throw std::runtime_error("LogicAnd did not return a type string");
    }
    std::string type = std::any_cast<std::string>(typeResult);
    checkTypes(type, "bool", "Logical OR operation requires boolean operands");

    for (size_t i = 1; i < ctx->logicAnd().size(); ++i) {
        auto rightTypeResult = visit(ctx->logicAnd(i));
        if (rightTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("LogicAnd did not return a type string");
        }
        std::string rightType = std::any_cast<std::string>(rightTypeResult);
        checkTypes(rightType, "bool", "Logical OR operation requires boolean operands");
    }

    return std::any(std::string("bool"));
}

std::any SemanticAnalyzer::visitLogicAnd(PrystParser::LogicAndContext* ctx) {
    auto typeResult = visit(ctx->equality(0));
    if (typeResult.type() != typeid(std::string)) {
        throw std::runtime_error("Equality did not return a type string");
    }
    std::string type = std::any_cast<std::string>(typeResult);
    checkTypes(type, "bool", "Logical AND operation requires boolean operands");

    for (size_t i = 1; i < ctx->equality().size(); ++i) {
        auto rightTypeResult = visit(ctx->equality(i));
        if (rightTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("Equality did not return a type string");
        }
        std::string rightType = std::any_cast<std::string>(rightTypeResult);
        checkTypes(rightType, "bool", "Logical AND operation requires boolean operands");
    }

    return std::any(std::string("bool"));
}

std::any SemanticAnalyzer::visitEquality(PrystParser::EqualityContext* ctx) {
    auto typeResult = visit(ctx->comparison(0));
    if (typeResult.type() != typeid(std::string)) {
        throw std::runtime_error("Comparison did not return a type string");
    }
    std::string type = std::any_cast<std::string>(typeResult);

    for (size_t i = 1; i < ctx->comparison().size(); ++i) {
        auto rightTypeResult = visit(ctx->comparison(i));
        if (rightTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("Comparison did not return a type string");
        }
        std::string rightType = std::any_cast<std::string>(rightTypeResult);
        checkTypes(type, rightType, "Type mismatch in equality comparison");
    }

    return std::any(std::string("bool"));
}

std::any SemanticAnalyzer::visitComparison(PrystParser::ComparisonContext* ctx) {
    auto typeResult = visit(ctx->addition(0));
    if (typeResult.type() != typeid(std::string)) {
        throw std::runtime_error("Addition did not return a type string");
    }
    std::string type = std::any_cast<std::string>(typeResult);

    for (size_t i = 1; i < ctx->addition().size(); ++i) {
        auto rightTypeResult = visit(ctx->addition(i));
        if (rightTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("Addition did not return a type string");
        }
        std::string rightType = std::any_cast<std::string>(rightTypeResult);
        checkTypes(type, rightType, "Type mismatch in comparison");
        if (type != "int" && type != "float") {
            throw std::runtime_error("Comparison operations require numeric operands");
        }
    }

    return std::any(std::string("bool"));
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

    if (ctx->INCREMENT() || ctx->DECREMENT()) {
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

    for (auto suffixCtx : ctx->callSuffix()) {
        if (suffixCtx->LPAREN()) {
            SymbolTable::FunctionInfo funcInfo;

            if (symbolTable.classExists(type)) {
                if (suffixCtx->arguments()) {
                    throw std::runtime_error("Calling constructors with arguments not implemented");
                }
                return std::any(type);
            } else if (symbolTable.functionExists(type)) {
                funcInfo = symbolTable.getFunctionInfo(type);
            } else {
                throw std::runtime_error("Undefined function: '" + type + "'");
            }

            size_t argCount = suffixCtx->arguments() ? suffixCtx->arguments()->expression().size() : 0;
            if (argCount != funcInfo.paramTypes.size()) {
                throw std::runtime_error("Function '" + type + "' expects " +
                                         std::to_string(funcInfo.paramTypes.size()) + " arguments, got " +
                                         std::to_string(argCount));
            }

            if (suffixCtx->arguments()) {
                for (size_t i = 0; i < argCount; ++i) {
                    auto argTypeResult = visit(suffixCtx->arguments()->expression(i));
                    if (argTypeResult.type() != typeid(std::string)) {
                        throw std::runtime_error("Argument expression did not return a type string");
                    }
                    std::string argType = std::any_cast<std::string>(argTypeResult);
                    checkTypes(funcInfo.paramTypes[i], argType, "Type mismatch in function call argument");
                }
            }

            type = funcInfo.returnType;

        } else if (suffixCtx->LBRACKET()) {
            if (type.find("[]") == std::string::npos) {
                throw std::runtime_error("Type '" + type + "' is not an array");
            }
            type = type.substr(0, type.length() - 2);

            auto indexTypeResult = visit(suffixCtx->expression());
            if (indexTypeResult.type() != typeid(std::string)) {
                throw std::runtime_error("Array index expression did not return a type string");
            }
            std::string indexType = std::any_cast<std::string>(indexTypeResult);
            if (indexType != "int") {
                throw std::runtime_error("Array index must be of type 'int'");
            }

        } else if (suffixCtx->DOT()) {
            std::string memberName = suffixCtx->IDENTIFIER()->getText();

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
    }

    return std::any(type);
}

std::any SemanticAnalyzer::visitCallSuffix(PrystParser::CallSuffixContext* ctx) {
    return std::any();
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

std::any SemanticAnalyzer::visitStatement(PrystParser::StatementContext* ctx) {
    if (ctx->expressionStmt()) {
        visit(ctx->expressionStmt());
    } else if (ctx->ifStmt()) {
        visit(ctx->ifStmt());
    } else if (ctx->whileStmt()) {
        visit(ctx->whileStmt());
    } else if (ctx->forStmt()) {
        visit(ctx->forStmt());
    } else if (ctx->returnStmt()) {
        visit(ctx->returnStmt());
    } else if (ctx->block()) {
        visit(ctx->block());
    } else {
        throw std::runtime_error("Unexpected statement type");
    }
    return std::any();
}

std::any SemanticAnalyzer::visitExpressionStmt(PrystParser::ExpressionStmtContext* ctx) {
    visit(ctx->expression());
    return std::any();
}

std::any SemanticAnalyzer::visitIfStmt(PrystParser::IfStmtContext* ctx) {
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

std::any SemanticAnalyzer::visitWhileStmt(PrystParser::WhileStmtContext* ctx) {
    auto conditionTypeResult = visit(ctx->expression());
    if (conditionTypeResult.type() != typeid(std::string)) {
        throw std::runtime_error("While condition did not return a type string");
    }
    std::string conditionType = std::any_cast<std::string>(conditionTypeResult);
    checkTypes(conditionType, "bool", "While condition must be a boolean expression");

    visit(ctx->statement());

    return std::any();
}

std::any SemanticAnalyzer::visitForStmt(PrystParser::ForStmtContext* ctx) {
    symbolTable.pushScope();

    if (ctx->variableDecl()) {
        visit(ctx->variableDecl());
    } else if (ctx->expressionStmt()) {
        visit(ctx->expressionStmt());
    } else if (ctx->SEMICOLON(0) != nullptr) {
        // Empty initializer; no action needed
    }

    if (ctx->expression(0)) {
        auto conditionTypeResult = visit(ctx->expression(0));
        if (conditionTypeResult.type() != typeid(std::string)) {
            throw std::runtime_error("For loop condition did not return a type string");
        }
        std::string conditionType = std::any_cast<std::string>(conditionTypeResult);
        checkTypes(conditionType, "bool", "For loop condition must be a boolean expression");
    }

    if (ctx->expression(1)) {
        visit(ctx->expression(1));
    }

    visit(ctx->statement());

    symbolTable.popScope();

    return std::any();
}

std::any SemanticAnalyzer::visitReturnStmt(PrystParser::ReturnStmtContext* ctx) {
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

std::any SemanticAnalyzer::visitBlock(PrystParser::BlockContext* ctx) {
    symbolTable.pushScope();

    for (auto decl : ctx->declaration()) {
        visit(decl);
    }

    symbolTable.popScope();

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

