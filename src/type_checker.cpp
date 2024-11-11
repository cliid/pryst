#include "type_checker.hpp"
#include "types.hpp"
#include <stdexcept>
#include <sstream>

namespace pryst {

// Remove constructor definition since it's already defined in the header

void TypeChecker::pushScope() {
    scopes.push_back(std::unordered_map<std::string, std::shared_ptr<Type>>());
}

void TypeChecker::popScope() {
    if (scopes.empty()) {
        throw std::runtime_error("No scope to pop");
    }
    scopes.pop_back();
}

void TypeChecker::declareVariable(const std::string& name, std::shared_ptr<Type> type) {
    if (scopes.empty()) {
        throw std::runtime_error("No active scope");
    }
    scopes.back()[name] = type;
}

std::shared_ptr<Type> TypeChecker::lookupVariable(const std::string& name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return found->second;
        }
    }
    throw std::runtime_error("Variable '" + name + "' not found");
}



std::any TypeChecker::visitBlock(PrystParser::BlockContext* ctx) {
    for (auto stmt : ctx->statement()) {
        visit(stmt);
    }
    return nullptr;
}



std::shared_ptr<Type> TypeChecker::inferReturnType(PrystParser::BlockContext* ctx) {
    std::shared_ptr<Type> returnType = VOID_TYPE;
    bool hasReturn = false;

    for (auto stmt : ctx->statement()) {
        if (auto returnStmt = dynamic_cast<PrystParser::ReturnStmtContext*>(stmt)) {
            if (returnStmt->expression()) {
                auto exprType = std::any_cast<std::shared_ptr<Type>>(visit(returnStmt->expression()));
                if (!hasReturn) {
                    returnType = exprType;
                    hasReturn = true;
                } else if (!isAssignable(returnType, exprType)) {
                    throw std::runtime_error("Inconsistent return types in function");
                }
            }
        }
    }

    return returnType;
}

// Visitor pattern implementation
std::any TypeChecker::visitProgram(PrystParser::ProgramContext* ctx) {
    for (auto decl : ctx->declaration()) {
        visit(decl);
    }
    return VOID_TYPE;
}

std::any TypeChecker::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    pushScope();

    std::vector<std::shared_ptr<Type>> paramTypes;
    if (ctx->parameters()) {
        auto params = ctx->parameters();
        for (auto param : params->parameter()) {
            auto paramType = getTypeFromTypeContext(param->type());
            paramTypes.push_back(paramType);
            auto id = param->IDENTIFIER();
            if (id) {
                declareVariable(id->getText(), paramType);
            }
        }
    }

    auto returnType = ctx->type().empty() ? VOID_TYPE : getTypeFromTypeContext(ctx->type()[0]);
    auto funcType = std::make_shared<FunctionType>(returnType, paramTypes);

    auto id = ctx->IDENTIFIER();
    if (id) {
        declareVariable(id->getText(), funcType);
    }

    if (ctx->block()) {
        visit(ctx->block());
    }
    popScope();

    return funcType;
}

std::any TypeChecker::visitClassDecl(PrystParser::ClassDeclContext* ctx) {
    std::string className = ctx->IDENTIFIER(0)->getText();
    auto classType = std::make_shared<ClassType>(className);

    // Process class members
    for (auto member : ctx->classMember()) {
        if (member->type().size() > 0) {  // Field declaration
            auto fieldType = getTypeFromTypeContext(member->type(0));
            classType->addField(member->IDENTIFIER()->getText(), fieldType);
        }
    }

    // Process constructors and methods
    for (auto ctor : ctx->constructorDecl()) {
        visit(ctor);
    }

    return nullptr;
}

std::any TypeChecker::visitVarDecl(PrystParser::VarDeclContext* ctx) {
    std::shared_ptr<Type> type;
    if (ctx->type()) {
        type = getTypeFromTypeContext(ctx->type());
    } else if (ctx->expression()) {
        type = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    } else {
        throw std::runtime_error("Variable declaration must have type or initializer");
    }

    if (ctx->identifierList()) {
        auto idList = ctx->identifierList();
        for (auto id : idList->IDENTIFIER()) {
            declareVariable(id->getText(), type);
        }
    }

    return type;
}

std::any TypeChecker::visitIfStmt(PrystParser::IfStmtContext* ctx) {
    auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    if (condType->getKind() != Type::Kind::Bool) {
        throw std::runtime_error("If condition must be boolean");
    }

    pushScope();
    visit(ctx->statement(0)); // Then branch
    popScope();

    if (ctx->statement().size() > 1) { // Has else branch
        pushScope();
        visit(ctx->statement(1));
        popScope();
    }

    return nullptr;
}

std::any TypeChecker::visitWhileStmt(PrystParser::WhileStmtContext* ctx) {
    auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    if (condType->getKind() != Type::Kind::Bool) {
        throw std::runtime_error("While condition must be boolean");
    }

    pushScope();
    isInLoop = true;
    visit(ctx->statement());
    isInLoop = false;
    popScope();

    return nullptr;
}

std::any TypeChecker::visitForStmt(PrystParser::ForStmtContext* ctx) {
    pushScope();
    isInLoop = true;

    if (ctx->varDecl()) { // C-style for loop
        visit(ctx->varDecl());
        auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
        if (condType->getKind() != Type::Kind::Bool) {
            throw std::runtime_error("For condition must be boolean");
        }
        if (ctx->expression().size() > 1) {
            visit(ctx->expression(1)); // increment expression
        }
    } else if (ctx->IDENTIFIER() && ctx->IN()) { // For-in loop
        auto iterableType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
        if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(iterableType)) {
            declareVariable(ctx->IDENTIFIER()->getText(), arrayType->getElementType());
        } else {
            throw std::runtime_error("For-in loop requires array type");
        }
    }

    visit(ctx->statement());
    isInLoop = false;
    popScope();

    return nullptr;
}

std::any TypeChecker::visitTryStmt(PrystParser::TryStmtContext* ctx) {
    pushScope();
    visit(ctx->block(0)); // try block
    popScope();

    for (size_t i = 0; i < ctx->CATCH().size(); i++) {
        pushScope();
        auto errorType = getTypeFromTypeContext(ctx->type(i));
        declareVariable(ctx->IDENTIFIER(i)->getText(), errorType);
        visit(ctx->block(i + 1)); // catch block
        popScope();
    }

    return nullptr;
}

std::any TypeChecker::visitReturnStmt(PrystParser::ReturnStmtContext* ctx) {
    if (!ctx->expression()) {
        return VOID_TYPE;
    }
    return visit(ctx->expression());
}



std::any TypeChecker::visitPrimaryExpr(PrystParser::PrimaryExprContext* ctx) {
    auto primary = ctx->primary();
    if (!primary) return ERROR_TYPE;

    if (primary->INTEGER()) {
        return INT_TYPE;
    }
    if (primary->FLOAT_LITERAL()) {
        return FLOAT_TYPE;
    }
    if (primary->STRING()) {
        return STRING_TYPE;
    }
    if (primary->BOOLEAN()) {
        return BOOL_TYPE;
    }
    if (primary->IDENTIFIER()) {
        return lookupVariable(primary->IDENTIFIER()->getText());
    }
    if (primary->arrayLiteral()) {
        return visit(primary->arrayLiteral());
    }
    if (primary->mapLiteral()) {
        return visit(primary->mapLiteral());
    }
    return ERROR_TYPE;
}

std::any TypeChecker::visitPostfixExpr(PrystParser::PostfixExprContext* ctx) {
    auto exprType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));

    if (ctx->INC() || ctx->DEC()) {
        if (exprType->getKind() != Type::Kind::Int) {
            throw std::runtime_error("Increment/decrement operators can only be applied to integer types");
        }
        return INT_TYPE;
    }

    throw std::runtime_error("Unknown postfix operator");
}

std::any TypeChecker::visitMethodCallExpr(PrystParser::MethodCallExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));

    // Handle nullable method calls
    bool isNullable = baseType->isNullable();
    if (isNullable) {
        // If base is nullable, unwrap it for method lookup but keep track of nullability
        if (baseType->getKind() == Type::Kind::Nullable) {
            baseType = std::static_pointer_cast<NullableType>(baseType)->getInnerType();
        }
    }

    // Get method name and check if it exists
    std::string methodName = ctx->IDENTIFIER()->getText();
    auto methodType = checkMemberAccess(baseType, methodName, isNullable);

    // Check argument types
    if (ctx->arguments()) {
        auto argTypes = std::any_cast<std::vector<std::shared_ptr<Type>>>(visit(ctx->arguments()));
        // TODO: Match argument types with method parameters when method overloading is implemented
    }

    // If base was nullable, make result nullable
    return isNullable ? std::make_shared<NullableType>(methodType) : methodType;
}

std::any TypeChecker::visitMemberAccessExpr(PrystParser::MemberAccessExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    return checkMemberAccess(baseType, ctx->IDENTIFIER()->getText(), false);
}

std::any TypeChecker::visitNullableMemberExpr(PrystParser::NullableMemberExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    // For chained nullable access, ensure the result is always nullable
    auto resultType = checkMemberAccess(baseType, ctx->IDENTIFIER()->getText(), true);
    // If the base type is nullable, the result must be nullable
    return baseType->isNullable() ? std::make_shared<NullableType>(resultType) : resultType;
}

std::any TypeChecker::visitLambdaExpr(PrystParser::LambdaExprContext* ctx) {
    pushScope();
    std::vector<std::shared_ptr<Type>> paramTypes;

    // Handle lambda parameters
    if (ctx->lambdaParams()) {
        for (size_t i = 0; i < ctx->lambdaParams()->type().size(); i++) {
            auto paramType = getTypeFromTypeContext(ctx->lambdaParams()->type(i));
            paramTypes.push_back(paramType);
            declareVariable(ctx->lambdaParams()->IDENTIFIER(i)->getText(), paramType);
        }
    }

    // Infer return type from arrow expression or block
    std::shared_ptr<Type> returnType;
    if (ctx->type()) {
        // Explicit return type after arrow: (params) -> ReturnType { ... }
        returnType = getTypeFromTypeContext(ctx->type());
    } else if (ctx->VOID()) {
        returnType = VOID_TYPE;
    } else {
        // Block form with type inference: (params) -> { statements }
        returnType = inferReturnType(ctx->block());
    }

    auto funcType = std::make_shared<FunctionType>(returnType, paramTypes);

    // Visit the lambda body
    if (ctx->block()) {
        visit(ctx->block());
    }

    popScope();
    return funcType;
}

std::shared_ptr<Type> TypeChecker::checkArrayAccess(std::shared_ptr<Type> arrayType, std::shared_ptr<Type> indexType) {
    if (!indexType) {
        return ERROR_TYPE;
    }
    if (indexType->getKind() != Type::Kind::Int) {
        throw std::runtime_error("Array index must be an integer");
    }
    if (arrayType->getKind() != Type::Kind::Array) {
        throw std::runtime_error("Cannot index a non-array type");
    }
    auto array = std::dynamic_pointer_cast<ArrayType>(arrayType);
    return array->getElementType();
}

std::shared_ptr<Type> TypeChecker::getTypeFromTypeContext(PrystParser::TypeContext* ctx) {
    if (!ctx) return VOID_TYPE;

    auto basicTypeCtx = ctx->basicType();
    if (basicTypeCtx) {
        if (basicTypeCtx->VOID()) return VOID_TYPE;
        if (basicTypeCtx->INT()) return INT_TYPE;
        if (basicTypeCtx->FLOAT()) return FLOAT_TYPE;
        if (basicTypeCtx->BOOL()) return BOOL_TYPE;
        if (basicTypeCtx->STR()) return STRING_TYPE;
        if (basicTypeCtx->IDENTIFIER()) {
            auto className = basicTypeCtx->IDENTIFIER()->getText();
            return std::make_shared<ClassType>(className);
        }
    }

    // Handle array types
    auto arrayTypeCtx = ctx->arrayType();
    if (arrayTypeCtx) {
        auto basicTypeCtx = arrayTypeCtx->basicType();
        auto elementType = basicTypeCtx->VOID() ? VOID_TYPE :
                          basicTypeCtx->INT() ? INT_TYPE :
                          basicTypeCtx->FLOAT() ? FLOAT_TYPE :
                          basicTypeCtx->BOOL() ? BOOL_TYPE :
                          basicTypeCtx->STR() ? STRING_TYPE :
                          basicTypeCtx->IDENTIFIER() ? std::make_shared<ClassType>(basicTypeCtx->IDENTIFIER()->getText()) :
                          VOID_TYPE;
        return std::make_shared<ArrayType>(elementType);
    }

    // Handle map types
    auto mapTypeCtx = ctx->mapType();
    if (mapTypeCtx) {
        auto keyType = mapTypeCtx->keyType()->STR() ? STRING_TYPE : INT_TYPE;
        auto valueType = getTypeFromTypeContext(mapTypeCtx->type());
        return std::make_shared<MapType>(keyType, valueType);
    }

    // Handle function types
    auto functionTypeCtx = ctx->functionType();
    if (functionTypeCtx) {
        auto returnType = getTypeFromTypeContext(functionTypeCtx->type());
        std::vector<std::shared_ptr<Type>> paramTypes;
        if (auto typeList = functionTypeCtx->typeList()) {
            for (auto paramType : typeList->type()) {
                paramTypes.push_back(getTypeFromTypeContext(paramType));
            }
        }
        return std::make_shared<FunctionType>(returnType, paramTypes);
    }

    throw std::runtime_error("Unknown type");
}



std::any TypeChecker::visitStatement(PrystParser::StatementContext* ctx) {
    if (ctx->varDecl()) return visit(ctx->varDecl());
    if (ctx->ifStmt()) return visit(ctx->ifStmt());
    if (ctx->whileStmt()) return visit(ctx->whileStmt());
    if (ctx->forStmt()) return visit(ctx->forStmt());
    if (ctx->tryStmt()) return visit(ctx->tryStmt());
    if (ctx->returnStmt()) return visit(ctx->returnStmt());
    if (ctx->expressionStmt()) return visit(ctx->expressionStmt());
    if (ctx->breakStmt()) return visit(ctx->breakStmt());
    if (ctx->continueStmt()) return visit(ctx->continueStmt());
    return VOID_TYPE;
}

std::any TypeChecker::visitType(PrystParser::TypeContext* ctx) {
    auto type = getTypeFromTypeContext(ctx);
    return type;
}

std::shared_ptr<Type> TypeChecker::checkMemberAccess(std::shared_ptr<Type> baseType, const std::string& memberName, bool isNullable) {
    // Handle nullable access
    if (baseType->getKind() == Type::Kind::Nullable) {
        if (!isNullable) {
            throw std::runtime_error("Unsafe member access '" + memberName + "' on nullable type '" +
                                   baseType->toString() + "'. Use '?.' for null-safe navigation");
        }
        baseType = std::static_pointer_cast<NullableType>(baseType)->getInnerType();
    }

    // Handle array built-in methods
    if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(baseType)) {
        if (memberName == "length") {
            return INT_TYPE;
        }
        if (memberName == "push" || memberName == "pop") {
            return arrayType->getElementType();
        }
        if (memberName == "map" || memberName == "filter") {
            return arrayType;
        }
        if (memberName == "reduce") {
            return VOID_TYPE; // Return type depends on reducer function
        }
    }

    // Handle string built-in methods
    if (baseType->getKind() == Type::Kind::String) {
        if (memberName == "length") {
            return INT_TYPE;
        }
        if (memberName == "contains" || memberName == "startsWith" || memberName == "endsWith") {
            return BOOL_TYPE;
        }
        if (memberName == "upper" || memberName == "lower" || memberName == "trim") {
            return STRING_TYPE;
        }
        if (memberName == "split") {
            return std::make_shared<ArrayType>(STRING_TYPE);
        }
    }

    // Handle map built-in methods
    if (auto mapType = std::dynamic_pointer_cast<MapType>(baseType)) {
        if (memberName == "length") {
            return INT_TYPE;
        }
        if (memberName == "has") {
            return BOOL_TYPE;
        }
        if (memberName == "get") {
            auto valueType = mapType->getValueType();
            return isNullable ? std::make_shared<NullableType>(valueType) : valueType;
        }
        if (memberName == "keys") {
            return std::make_shared<ArrayType>(mapType->getKeyType());
        }
        if (memberName == "values") {
            return std::make_shared<ArrayType>(mapType->getValueType());
        }
    }

    // Handle class members
    if (auto classType = std::dynamic_pointer_cast<ClassType>(baseType)) {
        auto field = classType->getField(memberName);
        if (!field) {
            throw std::runtime_error("Member '" + memberName + "' not found in class '" +
                                   classType->getName() + "'. Available members: " +
                                   [&]() {
                                       std::string result;
                                       const auto& members = classType->getAvailableMembers();
                                       for (size_t i = 0; i < members.size(); ++i) {
                                           result += members[i];
                                           if (i < members.size() - 1) result += ", ";
                                       }
                                       return result;
                                   }());
        }
        return isNullable ? std::make_shared<NullableType>(field) : field;
    }

    throw std::runtime_error("Cannot access member '" + memberName + "' on type '" +
                           baseType->toString() + "'. Type does not support member access");
}

std::any TypeChecker::visitImportDecl(PrystParser::ImportDeclContext* ctx) {
    return VOID_TYPE;
}

std::any TypeChecker::visitImportPath(PrystParser::ImportPathContext* ctx) {
    return VOID_TYPE;
}

std::any TypeChecker::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    if (ctx->functionDecl()) return visit(ctx->functionDecl());
    if (ctx->classDecl()) return visit(ctx->classDecl());
    if (ctx->varDecl()) return visit(ctx->varDecl());
    return VOID_TYPE;
}

std::any TypeChecker::visitParameters(PrystParser::ParametersContext* ctx) {
    std::vector<std::shared_ptr<Type>> paramTypes;
    for (auto param : ctx->parameter()) {
        paramTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(param)));
    }
    return paramTypes;
}

std::any TypeChecker::visitParameter(PrystParser::ParameterContext* ctx) {
    auto type = getTypeFromTypeContext(ctx->type());
    declareVariable(ctx->IDENTIFIER()->getText(), type);
    return type;
}

std::any TypeChecker::visitAssignment(PrystParser::AssignmentContext* ctx) {
    auto targetType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto valueType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));

    if (!isAssignable(targetType, valueType)) {
        throw std::runtime_error("Cannot assign " + valueType->toString() + " to " + targetType->toString());
    }

    return targetType;
}

std::any TypeChecker::visitBreakStmt(PrystParser::BreakStmtContext* ctx) {
    return VOID_TYPE;
}

std::any TypeChecker::visitContinueStmt(PrystParser::ContinueStmtContext* ctx) {
    return VOID_TYPE;
}

std::any TypeChecker::visitExpressionStmt(PrystParser::ExpressionStmtContext* ctx) {
    return visit(ctx->expression());
}

std::any TypeChecker::visitArguments(PrystParser::ArgumentsContext* ctx) {
    std::vector<std::shared_ptr<Type>> argTypes;
    for (auto arg : ctx->expression()) {
        argTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(arg)));
    }
    return argTypes;
}

std::any TypeChecker::visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext* ctx) {
    return std::make_shared<ArrayType>(VOID_TYPE);
}

std::any TypeChecker::visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext* ctx) {
    auto firstType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    for (size_t i = 1; i < ctx->expression().size(); i++) {
        auto nextType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(i)));
        if (!isAssignable(firstType, nextType)) {
            throw std::runtime_error("Inconsistent array element types");
        }
    }
    return std::make_shared<ArrayType>(firstType);
}

std::any TypeChecker::visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext* ctx) {
    return std::make_shared<MapType>(VOID_TYPE, VOID_TYPE);
}

std::any TypeChecker::visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext* ctx) {
    auto entries = ctx->mapEntry();
    auto firstEntry = entries[0];
    auto keyType = STRING_TYPE;  // Map keys are always strings
    auto valueType = std::any_cast<std::shared_ptr<Type>>(visit(firstEntry->expression()));

    for (size_t i = 1; i < entries.size(); i++) {
        auto nextValueType = std::any_cast<std::shared_ptr<Type>>(visit(entries[i]->expression()));
        if (!isAssignable(valueType, nextValueType)) {
            throw std::runtime_error("Inconsistent map value types");
        }
    }

    return std::make_shared<MapType>(keyType, valueType);
}



std::shared_ptr<Type> TypeChecker::getLambdaType(PrystParser::LambdaExprContext* ctx) {
    std::vector<std::shared_ptr<Type>> paramTypes;
    std::shared_ptr<Type> returnType;

    if (ctx->lambdaParams()) {
        for (size_t i = 0; i < ctx->lambdaParams()->type().size(); i++) {
            auto paramType = getTypeFromTypeContext(ctx->lambdaParams()->type(i));
            paramTypes.push_back(paramType);
        }
    }

    if (ctx->type()) {
        returnType = getTypeFromTypeContext(ctx->type());
    } else if (ctx->VOID()) {
        returnType = VOID_TYPE;
    } else {
        returnType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->block()));
    }

    return std::make_shared<FunctionType>(returnType, paramTypes);
}

std::any TypeChecker::visitBuiltinFunctionCall(PrystParser::BuiltinFunctionCallContext* ctx) {
    auto funcName = ctx->IDENTIFIER()->getText();
    std::vector<std::shared_ptr<Type>> argTypes;
    if (ctx->arguments()) {
        for (auto arg : ctx->arguments()->expression()) {
            argTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(arg)));
        }
    }
    // Handle built-in functions
    if (funcName == "print" || funcName == "println") {
        return VOID_TYPE;
    }
    if (funcName == "len" || funcName == "length") {
        if (argTypes.size() != 1) {
            throw std::runtime_error("length() requires exactly one argument");
        }
        return INT_TYPE;
    }
    throw std::runtime_error("Unknown built-in function: " + funcName);
}

std::any TypeChecker::visitConstructorExpr(PrystParser::ConstructorExprContext* ctx) {
    auto className = ctx->IDENTIFIER()->getText();
    auto classType = std::make_shared<ClassType>(className);
    // TODO: Check constructor arguments match class definition
    return classType;
}

std::any TypeChecker::visitArrayAccessExpr(PrystParser::ArrayAccessExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto indexType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    return checkArrayAccess(baseType, indexType);
}

std::any TypeChecker::visitCastExpr(PrystParser::CastExprContext* ctx) {
    auto targetType = getTypeFromTypeContext(ctx->type());
    auto sourceType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    return checkTypeCast(targetType, sourceType);
}

std::any TypeChecker::visitParenExpr(PrystParser::ParenExprContext* ctx) {
    return visit(ctx->expression());
}

std::any TypeChecker::visitPrefixExpr(PrystParser::PrefixExprContext* ctx) {
    auto operandType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    std::string op;
    if (ctx->NOT()) op = "!";
    else if (ctx->MINUS()) op = "-";
    else if (ctx->INC()) op = "++";
    else if (ctx->DEC()) op = "--";
    return checkUnaryOp(op, operandType);
}



std::any TypeChecker::visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext* ctx) {
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    return checkBinaryOp(ctx->op->getText(), left, right);
}

std::any TypeChecker::visitAdditiveExpr(PrystParser::AdditiveExprContext* ctx) {
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    return checkBinaryOp(ctx->op->getText(), left, right);
}

std::any TypeChecker::visitRelationalExpr(PrystParser::RelationalExprContext* ctx) {
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    return checkBinaryOp(ctx->op->getText(), left, right);
}

std::any TypeChecker::visitEqualityExpr(PrystParser::EqualityExprContext* ctx) {
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    return checkBinaryOp(ctx->op->getText(), left, right);
}

std::any TypeChecker::visitLogicalAndExpr(PrystParser::LogicalAndExprContext* ctx) {
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    return checkBinaryOp("&&", left, right);
}

std::any TypeChecker::visitLogicalOrExpr(PrystParser::LogicalOrExprContext* ctx) {
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    return checkBinaryOp("||", left, right);
}

std::any TypeChecker::visitConditionalExpr(PrystParser::ConditionalExprContext* ctx) {
    auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    if (condType->getKind() != Type::Kind::Bool) {
        throw std::runtime_error("Condition must be boolean");
    }
    auto thenType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    auto elseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(2)));
    if (!isAssignable(thenType, elseType)) {
        throw std::runtime_error("Conditional expression branches must have compatible types");
    }
    return thenType;
}

std::any TypeChecker::visitAssignmentExpr(PrystParser::AssignmentExprContext* ctx) {
    auto targetType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto valueType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    if (!isAssignable(targetType, valueType)) {
        throw std::runtime_error("Cannot assign " + valueType->toString() + " to " + targetType->toString());
    }
    return targetType;
}

std::any TypeChecker::visitBuiltinFunction(PrystParser::BuiltinFunctionContext* ctx) {
    std::string funcName = ctx->IDENTIFIER()->getText();
    std::vector<std::shared_ptr<Type>> argTypes;
    if (ctx->arguments()) {
        for (auto arg : ctx->arguments()->expression()) {
            argTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(arg)));
        }
    }

    // Handle built-in functions
    if (funcName == "print" || funcName == "println") {
        return VOID_TYPE;
    }
    if (funcName == "len" || funcName == "length") {
        if (argTypes.size() != 1) {
            throw std::runtime_error("length() requires exactly one argument");
        }
        return INT_TYPE;
    }
    throw std::runtime_error("Unknown built-in function: " + funcName);
}

std::any TypeChecker::visitChainedCall(PrystParser::ChainedCallContext* ctx) {
    // Use the last expression type as the base type
    if (!lastExpressionType) {
        throw std::runtime_error("No base expression for chained call");
    }
    auto baseType = lastExpressionType;

    // Handle nullable chained calls
    bool isNullable = baseType->isNullable();
    if (isNullable && baseType->getKind() == Type::Kind::Nullable) {
        baseType = std::static_pointer_cast<NullableType>(baseType)->getInnerType();
    }

    // Get method name from the identifier
    std::string methodName = ctx->IDENTIFIER()->getText();
    baseType = checkMemberAccess(baseType, methodName, isNullable);

    // Check argument types if present
    if (ctx->arguments()) {
        auto argTypes = std::any_cast<std::vector<std::shared_ptr<Type>>>(visit(ctx->arguments()));
        // TODO: Match argument types with method parameters when method overloading is implemented
    }

    // Store and return the result
    lastExpressionType = isNullable ? std::make_shared<NullableType>(baseType) : baseType;
    return lastExpressionType;
}

std::any TypeChecker::visitConstructorCall(PrystParser::ConstructorCallContext* ctx) {
    auto className = ctx->IDENTIFIER()->getText();
    auto classType = std::make_shared<ClassType>(className);
    // TODO: Check constructor arguments match class definition
    return classType;
}

std::any TypeChecker::visitStringLiteral(PrystParser::StringLiteralContext* ctx) {
    return STRING_TYPE;
}

std::any TypeChecker::visitLambdaParams(PrystParser::LambdaParamsContext* ctx) {
    std::vector<std::shared_ptr<Type>> paramTypes;
    for (auto typeCtx : ctx->type()) {
        paramTypes.push_back(getTypeFromTypeContext(typeCtx));
    }
    return paramTypes;
}

bool TypeChecker::isAssignable(std::shared_ptr<Type> targetType, std::shared_ptr<Type> sourceType) {
    // Handle null source type
    if (sourceType->getKind() == Type::Kind::Null) {
        if (!targetType->isNullable()) {
            throw std::runtime_error("Cannot assign null to non-nullable type " + targetType->toString());
        }
        return true;
    }

    // Handle nullable target type
    if (targetType->getKind() == Type::Kind::Nullable) {
        auto nullableTarget = std::static_pointer_cast<NullableType>(targetType);
        // Allow assignment from nullable to nullable if inner types are compatible
        if (sourceType->getKind() == Type::Kind::Nullable) {
            auto nullableSource = std::static_pointer_cast<NullableType>(sourceType);
            try {
                return isAssignable(nullableTarget->getInnerType(), nullableSource->getInnerType());
            } catch (const std::runtime_error& e) {
                throw std::runtime_error("Invalid nullable type conversion: " + std::string(e.what()));
            }
        }
        // Allow non-nullable to nullable if types are compatible
        try {
            return isAssignable(nullableTarget->getInnerType(), sourceType);
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Cannot convert type " + sourceType->toString() +
                                   " to nullable type " + targetType->toString() + ": " + e.what());
        }
    }

    // Handle nullable source type - requires explicit null check
    if (sourceType->getKind() == Type::Kind::Nullable) {
        throw std::runtime_error("Cannot assign nullable type " + sourceType->toString() +
                               " to non-nullable type " + targetType->toString() +
                               " without explicit null check");
    }

    // Handle primitive types
    if (targetType->getKind() == sourceType->getKind()) {
        return true;
    }

    // Handle array types
    if (targetType->getKind() == Type::Kind::Array && sourceType->getKind() == Type::Kind::Array) {
        auto targetArray = std::static_pointer_cast<ArrayType>(targetType);
        auto sourceArray = std::static_pointer_cast<ArrayType>(sourceType);
        try {
            return isAssignable(targetArray->getElementType(), sourceArray->getElementType());
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Invalid array type conversion: " + std::string(e.what()));
        }
    }

    // Handle map types
    if (targetType->getKind() == Type::Kind::Map && sourceType->getKind() == Type::Kind::Map) {
        auto targetMap = std::static_pointer_cast<MapType>(targetType);
        auto sourceMap = std::static_pointer_cast<MapType>(sourceType);
        try {
            bool keyAssignable = isAssignable(targetMap->getKeyType(), sourceMap->getKeyType());
            bool valueAssignable = isAssignable(targetMap->getValueType(), sourceMap->getValueType());
            return keyAssignable && valueAssignable;
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Invalid map type conversion: " + std::string(e.what()));
        }
    }

    throw std::runtime_error("Cannot convert type " + sourceType->toString() + " to " + targetType->toString());
}

} // namespace pryst
