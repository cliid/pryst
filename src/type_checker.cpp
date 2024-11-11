#include "type_checker.hpp"
#include "types.hpp"
#include <stdexcept>
#include <sstream>

namespace pryst {

TypeChecker::TypeChecker() {
    pushScope(); // Global scope
}

void TypeChecker::pushScope() {
    scopeStack.push_back(std::map<std::string, std::shared_ptr<Type>>());
}

void TypeChecker::popScope() {
    if (!scopeStack.empty()) {
        scopeStack.pop_back();
    }
}



void TypeChecker::declareVariable(const std::string& name, std::shared_ptr<Type> type) {
    if (scopeStack.empty()) {
        throw std::runtime_error("No active scope");
    }
    scopeStack.back()[name] = type;
}

std::shared_ptr<Type> TypeChecker::lookupVariable(const std::string& name) {
    for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return found->second;
        }
    }
    return nullptr;
}

bool TypeChecker::isAssignable(std::shared_ptr<Type> target, std::shared_ptr<Type> source) {
    // Handle null assignment to nullable types
    if (source->getKind() == Type::Kind::Null) {
        return target->canBeNull();
    }

    // Handle nullable source types
    if (auto nullableSource = std::dynamic_pointer_cast<NullableType>(source)) {
        return isAssignable(target, nullableSource->getInnerType());
    }

    // Handle nullable target types
    if (auto nullableTarget = std::dynamic_pointer_cast<NullableType>(target)) {
        return isAssignable(nullableTarget->getInnerType(), source);
    }

    if (target->getKind() == source->getKind()) return true;

    // Allow int to float conversion
    if (target->getKind() == Type::Kind::Float && source->getKind() == Type::Kind::Int) {
        return true;
    }

    // Handle error propagation types
    if (auto errorType = std::dynamic_pointer_cast<ErrorPropagationType>(source)) {
        return isAssignable(target, errorType->getInnerType());
    }

    return false;
}

std::shared_ptr<Type> TypeChecker::checkTypeCast(std::shared_ptr<Type> targetType, std::shared_ptr<Type> sourceType) {
    // Allow numeric conversions
    if ((targetType->getKind() == Type::Kind::Int || targetType->getKind() == Type::Kind::Float) &&
        (sourceType->getKind() == Type::Kind::Int || sourceType->getKind() == Type::Kind::Float)) {
        return targetType;
    }

    // Allow string conversion for basic types
    if (targetType->getKind() == Type::Kind::String) {
        if (sourceType->getKind() == Type::Kind::Int ||
            sourceType->getKind() == Type::Kind::Float ||
            sourceType->getKind() == Type::Kind::Bool) {
            return STRING_TYPE;
        }
    }

    throw std::runtime_error("Invalid type cast from " + sourceType->toString() + " to " + targetType->toString());
}

std::shared_ptr<Type> TypeChecker::checkBinaryOp(const std::string& op,
                                              std::shared_ptr<Type> left,
                                              std::shared_ptr<Type> right) {
    // Arithmetic operators
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
        if (left->getKind() == Type::Kind::Int && right->getKind() == Type::Kind::Int) {
            return INT_TYPE;
        }
        if ((left->getKind() == Type::Kind::Int || left->getKind() == Type::Kind::Float) &&
            (right->getKind() == Type::Kind::Int || right->getKind() == Type::Kind::Float)) {
            return FLOAT_TYPE;
        }
        // String concatenation
        if (op == "+" && left->getKind() == Type::Kind::String) {
            return STRING_TYPE;
        }
    }

    // Comparison operators
    if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") {
        if (left->getKind() == right->getKind() ||
            (left->getKind() == Type::Kind::Int && right->getKind() == Type::Kind::Float) ||
            (left->getKind() == Type::Kind::Float && right->getKind() == Type::Kind::Int)) {
            return BOOL_TYPE;
        }
    }

    // Logical operators
    if (op == "&&" || op == "||") {
        if (left->getKind() == Type::Kind::Bool && right->getKind() == Type::Kind::Bool) {
            return BOOL_TYPE;
        }
    }

    throw std::runtime_error("Invalid operands for operator " + op);
}

std::shared_ptr<Type> TypeChecker::checkUnaryOp(const std::string& op, std::shared_ptr<Type> operand) {
    if (op == "!") {
        if (operand->getKind() == Type::Kind::Bool) {
            return BOOL_TYPE;
        }
    }

    if (op == "-") {
        if (operand->getKind() == Type::Kind::Int) {
            return INT_TYPE;
        }
        if (operand->getKind() == Type::Kind::Float) {
            return FLOAT_TYPE;
        }
    }

    if (op == "?") {
        return std::make_shared<ErrorPropagationType>(operand);
    }

    throw std::runtime_error("Invalid operand for operator " + op);
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
    pushScope();

    // Handle both field declarations and method declarations
    for (size_t i = 0; i < ctx->type().size(); i++) {
        auto fieldType = getTypeFromTypeContext(ctx->type(i));
        declareVariable(ctx->IDENTIFIER(i + 1)->getText(), fieldType);
    }

    for (auto funcDecl : ctx->functionDecl()) {
        visit(funcDecl);
    }

    popScope();
    return std::make_shared<ClassType>(ctx->IDENTIFIER(0)->getText());
}

std::any TypeChecker::visitVarDecl(PrystParser::VarDeclContext* ctx) {
    std::shared_ptr<Type> type;
    if (ctx->type()) {
        type = getTypeFromTypeContext(ctx->type());
    } else {
        type = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    }

    if (ctx->IDENTIFIER()) {
        declareVariable(ctx->IDENTIFIER()->getText(), type);
    }

    return type;
}

std::any TypeChecker::visitIfStmt(PrystParser::IfStmtContext* ctx) {
    auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    if (condType->getKind() != Type::Kind::Bool) {
        throw std::runtime_error("If condition must be boolean");
    }

    pushScope();
    visit(ctx->block(0)); // Then branch
    popScope();

    if (ctx->block().size() > 1) { // Has else branch
        pushScope();
        visit(ctx->block(1));
        popScope();
    }

    return VOID_TYPE;
}

std::any TypeChecker::visitWhileStmt(PrystParser::WhileStmtContext* ctx) {
    auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    if (condType->getKind() != Type::Kind::Bool) {
        throw std::runtime_error("While condition must be boolean");
    }

    pushScope();
    visit(ctx->block());
    popScope();

    return VOID_TYPE;
}

std::any TypeChecker::visitForStmt(PrystParser::ForStmtContext* ctx) {
    pushScope();

    if (ctx->varDecl()) { // C-style for loop
        visit(ctx->varDecl());
        auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
        if (condType->getKind() != Type::Kind::Bool) {
            throw std::runtime_error("For condition must be boolean");
        }
        visit(ctx->expression(1)); // increment expression
    } else { // Iterator-style for loop
        auto iterableType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
        if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(iterableType)) {
            declareVariable(ctx->IDENTIFIER()->getText(), arrayType->getElementType());
        } else {
            throw std::runtime_error("For-in loop requires array type");
        }
    }

    visit(ctx->block());
    popScope();

    return VOID_TYPE;
}

std::any TypeChecker::visitTryStmt(PrystParser::TryStmtContext* ctx) {
    pushScope();
    visit(ctx->block(0)); // try block
    popScope();

    pushScope();
    declareVariable(ctx->IDENTIFIER()->getText(), ERROR_TYPE);
    visit(ctx->block(1)); // catch block
    popScope();

    return VOID_TYPE;
}

std::any TypeChecker::visitReturnStmt(PrystParser::ReturnStmtContext* ctx) {
    if (!ctx->expression()) {
        return VOID_TYPE;
    }
    return visit(ctx->expression());
}

std::any TypeChecker::visitExpression(PrystParser::ExpressionContext* ctx) {
    if (ctx->unaryExpr()) {
        return visit(ctx->unaryExpr());
    }

    if (ctx->op) {
        auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
        auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
        return checkBinaryOp(ctx->op->getText(), left, right);
    }

    if (ctx->type()) { // Type cast
        auto targetType = getTypeFromTypeContext(ctx->type());
        auto sourceType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
        return checkTypeCast(targetType, sourceType);
    }

    if (ctx->lambdaExpr()) {
        return visit(ctx->lambdaExpr());
    }

    return visitChildren(ctx);
}

std::any TypeChecker::visitPrimary(PrystParser::PrimaryContext* ctx) {
    if (ctx->INTEGER()) {
        return INT_TYPE;
    }
    if (ctx->FLOAT_LITERAL()) {
        return FLOAT_TYPE;
    }
    if (ctx->STRING()) {
        return STRING_TYPE;
    }
    if (ctx->BOOLEAN()) {
        return BOOL_TYPE;
    }
    if (ctx->NULL_LITERAL()) {
        return NULL_TYPE;
    }
    if (ctx->IDENTIFIER()) {
        return lookupVariable(ctx->IDENTIFIER()->getText());
    }
    if (ctx->expression()) {
        return visit(ctx->expression());
    }
    if (ctx->arrayLiteral()) {
        if (ctx->arrayLiteral()->expression().empty()) {
            return std::make_shared<ArrayType>(VOID_TYPE);
        }
        auto firstType = std::any_cast<std::shared_ptr<Type>>(
            visit(ctx->arrayLiteral()->expression(0)));
        return std::make_shared<ArrayType>(firstType);
    }
    if (ctx->mapLiteral()) {
        if (ctx->mapLiteral()->mapEntry().empty()) {
            return std::make_shared<MapType>(VOID_TYPE, VOID_TYPE);
        }
        auto firstEntry = ctx->mapLiteral()->mapEntry()[0];
        auto keyType = std::any_cast<std::shared_ptr<Type>>(
            visit(firstEntry));
        auto valueType = std::any_cast<std::shared_ptr<Type>>(
            visit(firstEntry->expression()));
        return std::make_shared<MapType>(keyType, valueType);
    }
    return ERROR_TYPE;
}

std::any TypeChecker::visitUnaryExpr(PrystParser::UnaryExprContext* ctx) {
    if (ctx->NOT()) {
        auto operandType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->unaryExpr()));
        return checkUnaryOp("!", operandType);
    }
    return visit(ctx->postfixExpr());
}

std::any TypeChecker::visitPostfixExpr(PrystParser::PostfixExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->primary()));
    bool isNullable = false;

    // Handle member access, method calls, and nullable access
    for (size_t i = 0; i < ctx->DOT().size(); i++) {
        bool currentNullable = false;
        // Check if this access is nullable (has ?. operator)
        if (i < ctx->NULLABLE_DOT().size() && ctx->NULLABLE_DOT()[i]) {
            currentNullable = true;
            isNullable = true;
        }

        // Handle method calls
        if (i < ctx->arguments().size()) {
            std::vector<std::shared_ptr<Type>> argTypes;
            for (auto arg : ctx->arguments()[i]->expression()) {
                argTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(arg)));
            }
            // If this is a method call, check member access first
            if (i < ctx->IDENTIFIER().size()) {
                baseType = checkMemberAccess(baseType, ctx->IDENTIFIER()[i]->getText(), currentNullable);
            }
            // Method call result inherits nullability
            if (isNullable) {
                baseType = std::make_shared<NullableType>(baseType);
            }
        }
        // Handle property access
        else if (i < ctx->IDENTIFIER().size()) {
            baseType = checkMemberAccess(baseType, ctx->IDENTIFIER()[i]->getText(), currentNullable);
            if (isNullable) {
                baseType = std::make_shared<NullableType>(baseType);
            }
        }
    }

    // Handle array access
    if (ctx->LBRACK() && ctx->expression()) {
        auto indexType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
        if (!indexType) {
            return ERROR_TYPE;
        }
        if (indexType->getKind() != Type::Kind::Int) {
            throw std::runtime_error("Array index must be an integer");
        }
        if (baseType->getKind() != Type::Kind::Array) {
            throw std::runtime_error("Cannot index a non-array type");
        }
        auto arrayType = std::dynamic_pointer_cast<ArrayType>(baseType);
        baseType = arrayType->getElementType();
        if (isNullable) {
            baseType = std::make_shared<NullableType>(baseType);
        }
    }

    return baseType;
}

std::any TypeChecker::visitLambdaExpr(PrystParser::LambdaExprContext* ctx) {
    pushScope();
    std::vector<std::shared_ptr<Type>> paramTypes;

    // Handle lambda parameters
    if (ctx->parameters()) {
        for (auto param : ctx->parameters()->parameter()) {
            auto paramType = getTypeFromTypeContext(param->type());
            paramTypes.push_back(paramType);
            declareVariable(param->IDENTIFIER()->getText(), paramType);
        }
    }

    // Infer return type from arrow expression or block
    std::shared_ptr<Type> returnType;
    if (ctx->type()) {
        // Explicit return type after arrow: (params) -> ReturnType { ... }
        returnType = getTypeFromTypeContext(ctx->type());
    } else if (ctx->expression()) {
        // Arrow expression form: (params) -> expr
        returnType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    } else if (ctx->block()) {
        // Block form with type inference: (params) -> { statements }
        returnType = inferReturnType(ctx->block());
    } else {
        returnType = VOID_TYPE;
    }

    auto funcType = std::make_shared<FunctionType>(returnType, paramTypes);

    // Visit the lambda body
    if (ctx->block()) {
        visit(ctx->block());
    } else if (ctx->expression()) {
        visit(ctx->expression());
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

    if (ctx->VOID()) return VOID_TYPE;
    if (ctx->INT()) return INT_TYPE;
    if (ctx->FLOAT()) return FLOAT_TYPE;
    if (ctx->BOOL()) return BOOL_TYPE;
    if (ctx->STR()) return STRING_TYPE;

    if (ctx->IDENTIFIER()) {
        auto className = ctx->IDENTIFIER()->getText();
        return std::make_shared<ClassType>(className);
    }

    // Handle array type: type[]
    if (ctx->LBRACK()) {
        auto elementType = getTypeFromTypeContext(ctx->type(0));
        return std::make_shared<ArrayType>(elementType);
    }

    // Handle map type: map<KeyType, ValueType>
    if (ctx->MAP()) {
        auto keyType = getTypeFromTypeContext(ctx->type(0));
        auto valueType = getTypeFromTypeContext(ctx->type(1));
        return std::make_shared<MapType>(keyType, valueType);
    }

    // Handle function type: fn<ReturnType>(ArgTypes...)
    if (ctx->FN()) {
        auto returnType = getTypeFromTypeContext(ctx->type(0));
        std::vector<std::shared_ptr<Type>> paramTypes;

        // Get parameter types after the opening parenthesis
        for (size_t i = 1; i < ctx->type().size(); i++) {
            paramTypes.push_back(getTypeFromTypeContext(ctx->type(i)));
        }

        return std::make_shared<FunctionType>(returnType, paramTypes);
    }

    throw std::runtime_error("Unknown type");
}

std::any TypeChecker::visitBlock(PrystParser::BlockContext* ctx) {
    pushScope();
    for (auto stmt : ctx->statement()) {
        visit(stmt);
    }
    auto result = inferReturnType(ctx);
    popScope();
    return result;
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
    if (isNullable) {
        if (!baseType || baseType->getKind() == Type::Kind::Null) {
            return std::make_shared<NullableType>(VOID_TYPE);
        }
    } else if (!baseType) {
        throw std::runtime_error("Cannot access member '" + memberName + "' of null type");
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
    if (baseType->getKind() == Type::Kind::Class) {
        auto memberType = lookupVariable(memberName);
        if (!memberType) {
            throw std::runtime_error("Member '" + memberName + "' not found in class '" + baseType->toString() + "'");
        }
        return isNullable ? std::make_shared<NullableType>(memberType) : memberType;
    }

    throw std::runtime_error("Cannot access member '" + memberName + "' of type '" + baseType->toString() + "'");
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

std::any TypeChecker::visitArrayLiteral(PrystParser::ArrayLiteralContext* ctx) {
    if (ctx->expression().empty()) {
        return std::make_shared<ArrayType>(VOID_TYPE);
    }

    auto elementType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    for (size_t i = 1; i < ctx->expression().size(); i++) {
        auto nextType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(i)));
        if (!isAssignable(elementType, nextType)) {
            throw std::runtime_error("Inconsistent array element types");
        }
    }

    return std::make_shared<ArrayType>(elementType);
}

std::any TypeChecker::visitMapLiteral(PrystParser::MapLiteralContext* ctx) {
    auto entries = ctx->mapEntry();
    if (entries.empty()) {
        return std::make_shared<MapType>(VOID_TYPE, VOID_TYPE);
    }

    auto firstEntry = entries[0];
    if (!firstEntry->STRING() && !firstEntry->IDENTIFIER()) {
        return ERROR_TYPE;
    }
    if (!firstEntry->expression()) {
        return ERROR_TYPE;
    }

    // Key type is always string in map literals
    auto keyType = STRING_TYPE;
    auto valueType = std::any_cast<std::shared_ptr<Type>>(visit(firstEntry->expression()));

    for (size_t i = 1; i < entries.size(); i++) {
        auto entry = entries[i];
        if (!entry->STRING() && !entry->IDENTIFIER()) {
            throw std::runtime_error("Map key must be a string or identifier");
        }
        if (!entry->expression()) {
            return ERROR_TYPE;
        }
        auto nextValueType = std::any_cast<std::shared_ptr<Type>>(visit(entry->expression()));
        if (!isAssignable(valueType, nextValueType)) {
            throw std::runtime_error("Inconsistent map value types");
        }
    }

    return std::make_shared<MapType>(keyType, valueType);
}

std::any TypeChecker::visitMapEntry(PrystParser::MapEntryContext* ctx) {
    if (!ctx->STRING() && !ctx->IDENTIFIER()) {
        return ERROR_TYPE;
    }

    auto keyType = STRING_TYPE;  // Map keys are always strings
    auto valueType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    return std::make_pair(keyType, valueType);
}

std::shared_ptr<Type> TypeChecker::getLambdaType(PrystParser::LambdaExprContext* ctx) {
    std::vector<std::shared_ptr<Type>> paramTypes;

    // Handle lambda parameters
    if (ctx->parameters()) {
        for (auto param : ctx->parameters()->parameter()) {
            auto paramType = getTypeFromTypeContext(param->type());
            paramTypes.push_back(paramType);
        }
    }

    // Infer return type from arrow expression or block
    std::shared_ptr<Type> returnType;
    if (ctx->type()) {
        // Explicit return type after arrow: (params) -> ReturnType { ... }
        returnType = getTypeFromTypeContext(ctx->type());
    } else if (ctx->expression()) {
        // Arrow expression form: (params) -> expr
        returnType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    } else if (ctx->block()) {
        // Block form with type inference: (params) -> { statements }
        returnType = inferReturnType(ctx->block());
    } else {
        returnType = VOID_TYPE;
    }

    return std::make_shared<FunctionType>(returnType, paramTypes);
}

// Expression visitor methods for labeled alternatives
std::any TypeChecker::visitPrimaryExpr(PrystParser::PrimaryExprContext* ctx) {
    return visit(ctx->primary());
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

std::any TypeChecker::visitMemberAccessExpr(PrystParser::MemberAccessExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    return checkMemberAccess(baseType, ctx->IDENTIFIER()->getText(), false);
}

std::any TypeChecker::visitNullableMemberExpr(PrystParser::NullableMemberExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    return checkMemberAccess(baseType, ctx->IDENTIFIER()->getText(), true);
}

std::any TypeChecker::visitMethodCallExpr(PrystParser::MethodCallExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    auto methodType = checkMemberAccess(baseType, ctx->IDENTIFIER()->getText(), false);
    if (auto funcType = std::dynamic_pointer_cast<FunctionType>(methodType)) {
        return funcType->getReturnType();
    }
    throw std::runtime_error("Member is not a method: " + ctx->IDENTIFIER()->getText());
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

std::any TypeChecker::visitPostfixExpr(PrystParser::PostfixExprContext* ctx) {
    auto baseType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->primary()));
    bool isNullable = false;

    // Handle member access, method calls, and nullable access
    for (size_t i = 0; i < ctx->DOT().size(); i++) {
        bool currentNullable = false;
        // Check if this access is nullable (has ?. operator)
        if (i < ctx->NULLABLE_DOT().size() && ctx->NULLABLE_DOT()[i]) {
            currentNullable = true;
            isNullable = true;
        }

        // Handle method calls
        if (i < ctx->arguments().size()) {
            std::vector<std::shared_ptr<Type>> argTypes;
            for (auto arg : ctx->arguments()[i]->expression()) {
                argTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(arg)));
            }
            // If this is a method call, check member access first
            if (i < ctx->IDENTIFIER().size()) {
                baseType = checkMemberAccess(baseType, ctx->IDENTIFIER()[i]->getText(), currentNullable);
            }
            // Method call result inherits nullability
            if (isNullable) {
                baseType = std::make_shared<NullableType>(baseType);
            }
        }
        // Handle property access
        else if (i < ctx->IDENTIFIER().size()) {
            baseType = checkMemberAccess(baseType, ctx->IDENTIFIER()[i]->getText(), currentNullable);
            if (isNullable) {
                baseType = std::make_shared<NullableType>(baseType);
            }
        }
    }

    // Handle array access
    if (ctx->LBRACK() && ctx->expression()) {
        auto indexType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
        if (!indexType) {
            return ERROR_TYPE;
        }
        if (indexType->getKind() != Type::Kind::Int) {
            throw std::runtime_error("Array index must be an integer");
        }
        if (baseType->getKind() != Type::Kind::Array) {
            throw std::runtime_error("Cannot index a non-array type");
        }
        auto arrayType = std::dynamic_pointer_cast<ArrayType>(baseType);
        baseType = arrayType->getElementType();
        if (isNullable) {
            baseType = std::make_shared<NullableType>(baseType);
        }
    }

    // Handle increment/decrement operators
    if (ctx->INC() || ctx->DEC()) {
        std::string op = ctx->INC() ? "++" : "--";
        return checkUnaryOp(op, baseType);
    }

    return baseType;
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

std::any TypeChecker::visitMapKey(PrystParser::MapKeyContext* ctx) {
    return STRING_TYPE;  // Map keys are always strings
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
    if (ctx->arguments()) {
        std::vector<std::shared_ptr<Type>> argTypes;
        for (auto arg : ctx->arguments()->expression()) {
            argTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(arg)));
        }
    }
    return VOID_TYPE;  // Return type will be determined by the method being called
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
    for (size_t i = 0; i < ctx->type().size(); i++) {
        auto paramType = getTypeFromTypeContext(ctx->type(i));
        paramTypes.push_back(paramType);
    }
    return paramTypes;
}

} // namespace pryst
