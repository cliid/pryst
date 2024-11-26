#include "type_checker.hpp"  // Must come first
#include "antlr4-runtime.h"
#include "generated/PrystParserBaseVisitor.h"
#include "generated/PrystParser.h"
#include "generated/PrystLexer.h"
#include "types.hpp"
#include "llvm_type_converter.hpp"
#include "error.hpp"
#include "error_type.hpp"
#include "error_chain.hpp"
#include <llvm/IR/LLVMContext.h>
#include "type_registry.hpp"
#include "runtime/runtime_registry.hpp"
#include "runtime/web_types.hpp"
#include <any>
#include <memory>
#include <iostream>

namespace pryst {

using std::string;
using std::vector;
using std::any;
using std::shared_ptr;

TypeChecker::TypeChecker(llvm::LLVMContext& context, TypeRegistry& typeRegistry, RuntimeRegistry& runtimeRegistry)
    : context_(context)
    , typeRegistry_(typeRegistry)
    , runtimeRegistry_(runtimeRegistry)
    , errorHandler_(typeInference_.getErrorHandler())
    , scopeManager_(typeRegistry)
    , converter_(context)
    , currentFunctionReturnType(std::any())
    , lastExpressionType(std::any())
    , isInLoop(false) {

    // Register core namespaces first, before any type registration
    if (!typeRegistry_.isNamespaceRegistered("pryst")) {
        typeRegistry_.registerNamespace("pryst");
    }
    if (!typeRegistry_.isNamespaceRegistered("pryst::runtime::web")) {
        typeRegistry_.registerNamespace("pryst::runtime::web");
    }

    initializeGlobalScope();
}

void TypeChecker::initializeGlobalScope() {
    std::cout << "Debug [initializeGlobalScope]: Initializing global scope" << std::endl;

    // Register all known types from type registry in global scope
    for (const auto& [typeName, type] : typeRegistry_.getAllTypes()) {
        scopeManager_.declareVariable(typeName, type);
    }
}

void TypeChecker::debugPrintType(const std::shared_ptr<Type>& type, const std::string& context) {
    std::cout << "Debug [" << context << "]: ";
    if (type) {
        std::cout << "Type: " << type->toString() << std::endl;
    } else {
        std::cout << "Null type" << std::endl;
    }
}

void TypeChecker::declareVariable(const std::string& name, std::any type) {
    auto typeSPtr = std::any_cast<std::shared_ptr<Type>>(type);
    std::cout << "Debug [declareVariable]: Registering variable " << name
              << " with type " << (typeSPtr ? typeSPtr->toString() : "null") << std::endl;

    if (typeSPtr && typeSPtr->getKind() == Type::Kind::Class) {
        auto classType = std::static_pointer_cast<ClassType>(typeSPtr);
        std::string typeName = classType->getName();
        typeRegistry_.cacheType(typeName, typeSPtr);

        size_t lastSeparator = typeName.rfind("::");
        if (lastSeparator != std::string::npos) {
            std::string shortName = typeName.substr(lastSeparator + 2);
            typeRegistry_.cacheType(shortName, typeSPtr);
        }
    }

    scopeManager_.declareVariable(name, typeSPtr);
}

void TypeChecker::pushScope() {
    std::cout << "Debug [pushScope]: Creating new scope" << std::endl;
    scopeManager_.pushScope();
}

void TypeChecker::popScope() {
    std::cout << "Debug [popScope]: Removing current scope" << std::endl;

    // Before popping the scope, ensure all class types and their namespaces are preserved
    auto currentScope = scopeManager_.getCurrentScope();
    for (const auto& [name, type] : currentScope) {
        if (type->getKind() == Type::Kind::Class) {
            auto classType = std::static_pointer_cast<ClassType>(type);
            std::string typeName = classType->getName();
            std::cout << "Debug [popScope]: Preserving type " << typeName << " in registry" << std::endl;

            // Cache with full name
            typeRegistry_.cacheType(typeName, type);

            // Parse and register all namespace parts
            std::vector<std::string> parts;
            std::string currentNamespace;
            size_t start = 0;
            size_t end = typeName.find("::");

            // Register core namespaces first
            typeRegistry_.registerNamespace("pryst");
            typeRegistry_.registerNamespace("pryst::runtime::web");

            while (end != std::string::npos) {
                std::string part = typeName.substr(start, end - start);
                if (!currentNamespace.empty()) {
                    currentNamespace += "::";
                }
                currentNamespace += part;
                std::cout << "Debug [popScope]: Registering namespace: " << currentNamespace << std::endl;
                typeRegistry_.registerNamespace(currentNamespace);

                start = end + 2;
                end = typeName.find("::", start);
            }

            // Cache with short name if it's a qualified name
            size_t lastSeparator = typeName.rfind("::");
            if (lastSeparator != std::string::npos) {
                std::string shortName = typeName.substr(lastSeparator + 2);
                typeRegistry_.cacheType(shortName, type);
            }
        }
    }

    scopeManager_.popScope();
}

std::any TypeChecker::lookupVariable(const std::string& name) {
    try {
        auto type = scopeManager_.getVariableType(name);
        return std::any(type);
    } catch (const core::Error& e) {
        throw core::Error("ReferenceError", "Undefined variable: " + name);
    }
}

std::shared_ptr<Type> TypeChecker::validateErrorChain(
    std::shared_ptr<Type> errorType,
    std::shared_ptr<Type> chainedType) {

    // Use the new error handler for validation
    if (!isValidErrorChain(chainedType)) {
        auto invalidChainError = std::make_shared<core::Error>("TypeError", "Invalid error chain type");
        errorHandler_.handleTypedError(*invalidChainError, "InvalidErrorChain");
        return typeRegistry_.registerErrorType("InvalidErrorChain");
    }
    return createErrorChain(errorType, chainedType);
}

bool TypeChecker::isValidErrorChain(std::shared_ptr<Type> chainedType) {
    if (!chainedType) return false;
    return chainedType->getKind() == Type::Kind::Error ||
           typeRegistry_.isErrorType(chainedType->toString());
}

bool TypeChecker::isErrorType(std::shared_ptr<Type> type) {
    if (!type) return false;
    return type->getKind() == Type::Kind::Error ||
           typeRegistry_.isErrorType(type->toString());
}

bool TypeChecker::validateErrorMethodSignature(const std::string& methodName,
                                           const std::shared_ptr<FunctionType>& method,
                                           const std::shared_ptr<Type>& baseType) {
    if (auto baseClass = std::dynamic_pointer_cast<ClassType>(baseType)) {
        auto baseMethod = baseClass->getMethod(methodName);
        if (baseMethod) {
            if (auto baseFuncType = std::dynamic_pointer_cast<FunctionType>(baseMethod)) {
                return method->isCompatibleWith(baseFuncType);
            }
        }
    }
    return true;  // No base method to validate against
}

std::shared_ptr<Type> TypeChecker::createErrorChain(const std::shared_ptr<Type>& error,
                                                 const std::shared_ptr<Type>& cause) {
    if (!isValidErrorChain(error) || (cause && !isValidErrorChain(cause))) {
        auto typeError = std::make_shared<core::Error>("TypeError",
            "Invalid error chain: both error and cause must be valid error types");
        errorHandler_.handleTypedError(*typeError, "TypeError");
        return typeRegistry_.registerErrorType("TypeError");
    }

    try {
        // Create and validate the error chain using type registry
        return validateErrorChain(error, cause);
    } catch (const core::Error& e) {
        errorHandler_.handleTypedError(e, "ErrorChainValidation");
        return typeRegistry_.registerErrorType("ErrorChainValidation");
    }
}

std::any TypeChecker::checkMemberAccess(std::any baseType, const std::string& member, bool isNullable) {
    auto baseTypeSPtr = std::any_cast<std::shared_ptr<Type>>(baseType);
    std::cout << "Debug [checkMemberAccess]: Checking member '" << member
              << "' on type " << baseTypeSPtr->toString() << std::endl;

    // Handle nullable types with proper chain operator support
    if (auto nullableType = std::dynamic_pointer_cast<NullableType>(baseTypeSPtr)) {
        auto innerType = nullableType->getInnerType();
        if (!isNullable) {
            throw core::Error("TypeError", "Cannot access member '" + member + "' on nullable type without using ?. operator");
        }
        auto result = checkMemberAccess(std::any(innerType), member, true);
        return std::any(std::make_shared<NullableType>(std::any_cast<std::shared_ptr<Type>>(result)));
    }

    // Handle class types
    if (auto classType = std::dynamic_pointer_cast<ClassType>(baseTypeSPtr)) {
        if (auto fieldType = classType->getField(member)) {
            return std::any(isNullable ? std::make_shared<NullableType>(fieldType) : fieldType);
        }
        if (auto methodType = classType->getMethod(member)) {
            return std::any(isNullable ? std::make_shared<NullableType>(methodType) : methodType);
        }
    }

    throw core::Error("TypeError", "Type " + baseTypeSPtr->toString() + " has no member '" + member + "'");
}

std::any TypeChecker::unwrapNullableType(std::any type) {
    auto typeSPtr = std::any_cast<std::shared_ptr<Type>>(type);
    if (typeSPtr->getKind() == Type::Kind::Nullable) {
        return std::any(std::static_pointer_cast<NullableType>(typeSPtr)->getInnerType());
    }
    return type;
}

bool TypeChecker::isNullableType(std::any type) {
    auto typeSPtr = std::any_cast<std::shared_ptr<Type>>(type);
    return typeSPtr->getKind() == Type::Kind::Nullable;
}

std::any TypeChecker::wrapAsNullable(std::any type) {
    auto typeSPtr = std::any_cast<std::shared_ptr<Type>>(type);
    if (typeSPtr->isNullable()) {
        return type;
    }
    return std::any(std::make_shared<NullableType>(typeSPtr));
}

std::any TypeChecker::propagateNullability(std::any sourceType, std::any targetType) {
    auto sourceSPtr = std::any_cast<std::shared_ptr<Type>>(sourceType);
    auto targetSPtr = std::any_cast<std::shared_ptr<Type>>(targetType);

    if (sourceSPtr->isNullable()) {
        return wrapAsNullable(targetType);
    }
    return targetType;
}

std::any TypeChecker::visitNullableMethodCallExpr(PrystParser::NullableMethodCallExprContext* ctx) {
    auto baseType = visit(ctx->expression());
    if (!isNullableType(baseType)) {
        throw Error("TypeError", "Cannot use ?. operator on non-nullable type");
    }

    auto methodName = ctx->IDENTIFIER()->getText();
    auto unwrappedType = unwrapNullableType(baseType);
    auto baseTypeSPtr = std::any_cast<std::shared_ptr<Type>>(unwrappedType);

    // Check if method exists on unwrapped type
    auto methodType = baseTypeSPtr->getMethod(methodName);
    if (!methodType) {
        throw Error("TypeError", "Method '" + methodName + "' not found on type " + baseTypeSPtr->toString());
    }

    // Process arguments
    std::vector<std::shared_ptr<Type>> argTypes;
    if (ctx->arguments()) {
        for (auto arg : ctx->arguments()->expression()) {
            auto argType = std::any_cast<std::shared_ptr<Type>>(visit(arg));
            argTypes.push_back(argType);
        }
    }

    // Verify argument types match method parameters
    auto funcType = std::static_pointer_cast<FunctionType>(methodType);
    if (argTypes.size() != funcType->getParameterTypes().size()) {
        throw Error("TypeError", "Wrong number of arguments for method '" + methodName + "'");
    }

    // Return type is always nullable when using ?. operator
    return wrapAsNullable(std::any(funcType->getReturnType()));
}

std::any TypeChecker::visitNullableChain(PrystParser::NullableChainContext* ctx) {
    auto currentType = visit(ctx->expression());
    auto baseType = std::any_cast<std::shared_ptr<Type>>(currentType);

    if (!baseType->isNullable()) {
        throw Error("TypeError", "Cannot use ?. operator on non-nullable type '" + baseType->toString() + "'");
    }

    auto nullableType = std::static_pointer_cast<NullableType>(baseType);
    auto memberName = ctx->IDENTIFIER()->getText();

    // Try to get field from nullable type
    auto memberType = nullableType->getField(memberName);
    if (!memberType) {
        throw Error("TypeError", "Member '" + memberName + "' not found on type " + nullableType->getInnerType()->toString());
    }

    return std::any(memberType);
}

std::any TypeChecker::visitMethodCallExpr(PrystParser::MethodCallExprContext* ctx) {
    auto baseType = visit(ctx->expression());
    auto methodName = ctx->IDENTIFIER()->getText();
    auto baseTypeSPtr = std::any_cast<std::shared_ptr<Type>>(baseType);

    // Handle nullable types without ?. operator
    if (baseTypeSPtr->isNullable()) {
        throw Error("TypeError", "Cannot call method '" + methodName + "' on nullable type without using ?. operator");
    }

    // Get method type
    auto methodType = baseTypeSPtr->getMethod(methodName);
    if (!methodType) {
        throw Error("TypeError", "Method '" + methodName + "' not found on type " + baseTypeSPtr->toString());
    }

    // Process arguments
    std::vector<std::shared_ptr<Type>> argTypes;
    if (ctx->arguments()) {
        for (auto arg : ctx->arguments()->expression()) {
            argTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(arg)));
        }
    }

    auto funcType = std::static_pointer_cast<FunctionType>(methodType);
    if (argTypes.size() != funcType->getParameterTypes().size()) {
        throw Error("TypeError", "Wrong number of arguments for method '" + methodName + "'");
    }

    return std::any(funcType->getReturnType());
}

std::any TypeChecker::visitMemberAccessExpr(PrystParser::MemberAccessExprContext* ctx) {
    auto baseType = visit(ctx->expression());
    auto memberName = ctx->IDENTIFIER()->getText();
    auto baseTypeSPtr = std::any_cast<std::shared_ptr<Type>>(baseType);

    // Handle nullable types without ?. operator
    if (baseTypeSPtr->isNullable()) {
        throw Error("TypeError", "Cannot access member '" + memberName + "' on nullable type without using ?. operator");
    }

    if (auto classType = std::dynamic_pointer_cast<ClassType>(baseTypeSPtr)) {
        auto memberType = classType->getField(memberName);
        if (!memberType) {
            throw Error("TypeError", "Member '" + memberName + "' not found in class " +
                      classType->getName());
        }
        return std::any(memberType);
    }

    return checkMemberAccess(baseType, memberName, false);
}

std::any TypeChecker::getTypeFromTypeContext(PrystParser::TypeContext* ctx) {
    std::cout << "Debug [getTypeFromTypeContext]: Processing type context" << std::endl;
    std::cout << "Debug [getTypeFromTypeContext]: Context text: " << ctx->getText() << std::endl;

    try {
        if (!ctx) {
            std::cerr << "Error [getTypeFromTypeContext]: Null type context" << std::endl;
            throw Error("TypeError", "Null type context");
        }

        // Handle qualified types (e.g., runtime::web::Request)
        if (ctx->qualifiedType()) {
            std::cout << "Debug [getTypeFromTypeContext]: Processing qualified type" << std::endl;
            auto qualifiedType = ctx->qualifiedType();

            // Build the full type name and namespace parts
            std::vector<std::string> parts;
            for (auto identifier : qualifiedType->IDENTIFIER()) {
                parts.push_back(identifier->getText());
            }

            // Build full type name first
            std::string fullTypeName;
            for (size_t i = 0; i < parts.size(); ++i) {
                if (i > 0) fullTypeName += "::";
                fullTypeName += parts[i];
            }
            std::cout << "Debug [getTypeFromTypeContext]: Full type name: " << fullTypeName << std::endl;

            // Pre-register web types immediately if this might be a web type
            if (fullTypeName.find("pryst::runtime::web") == 0 || parts[0] == "pryst" || parts[0] == "web") {
                std::cout << "Debug [getTypeFromTypeContext]: Pre-registering web types early for: " << fullTypeName << std::endl;

                // Register namespaces first
                typeRegistry_.registerNamespace("pryst");
                typeRegistry_.registerNamespace("pryst::runtime::web");

                // Then register web types
                runtime::web::registerWebTypes(runtimeRegistry_);

                // Try to get the type immediately after registration
                auto type = typeRegistry_.getCachedType(fullTypeName);
                if (type) {
                    std::cout << "Debug [getTypeFromTypeContext]: Found type immediately after web registration: " << fullTypeName << std::endl;
                    return std::any(type);
                }
            }

            // Build and register namespace parts
            std::string namespacePart;
            for (size_t i = 0; i < parts.size() - 1; ++i) {
                if (i > 0) namespacePart += "::";
                namespacePart += parts[i];
                if (!namespacePart.empty()) {
                    std::cout << "Debug [getTypeFromTypeContext]: Registering namespace: " << namespacePart << std::endl;
                    typeRegistry_.registerNamespace(namespacePart);
                }
            }

            std::shared_ptr<Type> type;

            // 1. Try exact qualified name in type registry
            type = typeRegistry_.getCachedType(fullTypeName);
            if (type) {
                std::cout << "Debug [getTypeFromTypeContext]: Found type in cache: " << fullTypeName << std::endl;
                return type;
            }

            // 2. Try runtime registry with full name
            if (runtimeRegistry_.hasClass(fullTypeName)) {
                std::cout << "Debug [getTypeFromTypeContext]: Found type in runtime registry: " << fullTypeName << std::endl;
                type = std::make_shared<ClassType>(fullTypeName);
                typeRegistry_.cacheType(fullTypeName, type);

                // Cache with short name and all possible namespace variations
                std::string shortName = parts.back();
                typeRegistry_.cacheType(shortName, type);

                // Cache with intermediate namespace combinations
                std::string intermediateName;
                for (size_t i = parts.size() - 2; i < parts.size(); ++i) {
                    if (i > parts.size() - 2) intermediateName += "::";
                    intermediateName += parts[i];
                    typeRegistry_.cacheType(intermediateName, type);
                }

                return type;
            }

            // 3. Try namespace resolution
            if (!namespacePart.empty()) {
                std::cout << "Debug [getTypeFromTypeContext]: Checking namespace: " << namespacePart << std::endl;

                // Try direct namespace lookup
                if (typeRegistry_.isNamespaceRegistered(namespacePart)) {
                    std::string resolvedNamespace = typeRegistry_.resolveNamespace(namespacePart);
                    if (!resolvedNamespace.empty()) {
                        std::string resolvedTypeName = resolvedNamespace + "::" + parts.back();
                        std::cout << "Debug [getTypeFromTypeContext]: Trying resolved type name: " << resolvedTypeName << std::endl;

                        // Try resolved name in type registry
                        type = typeRegistry_.getCachedType(resolvedTypeName);
                        if (type) {
                            std::cout << "Debug [getTypeFromTypeContext]: Found type through namespace resolution: " << resolvedTypeName << std::endl;
                            typeRegistry_.cacheType(fullTypeName, type);
                            typeRegistry_.cacheType(parts.back(), type);  // Cache short name too
                            return type;
                        }

                        // Try resolved name in runtime registry
                        if (runtimeRegistry_.hasClass(resolvedTypeName)) {
                            std::cout << "Debug [getTypeFromTypeContext]: Found type in runtime registry through namespace: " << resolvedTypeName << std::endl;
                            type = std::make_shared<ClassType>(resolvedTypeName);
                            typeRegistry_.cacheType(resolvedTypeName, type);
                            typeRegistry_.cacheType(fullTypeName, type);
                            typeRegistry_.cacheType(parts.back(), type);  // Cache short name too
                            return type;
                        }
                    }
                }

                // Try runtime registry with namespace variations
                std::string runtimeTypeName = namespacePart + "::" + parts.back();
                if (runtimeRegistry_.hasClass(runtimeTypeName)) {
                    std::cout << "Debug [getTypeFromTypeContext]: Found type in runtime registry with namespace: " << runtimeTypeName << std::endl;
                    type = std::make_shared<ClassType>(runtimeTypeName);
                    typeRegistry_.cacheType(runtimeTypeName, type);
                    typeRegistry_.cacheType(fullTypeName, type);
                    typeRegistry_.cacheType(parts.back(), type);  // Cache short name too
                    return type;
                }
            }

            // 4. Try short name as last resort
            std::string shortName = parts.back();
            type = typeRegistry_.getCachedType(shortName);
            if (type) {
                std::cout << "Debug [getTypeFromTypeContext]: Found type with short name: " << shortName << std::endl;
                typeRegistry_.cacheType(fullTypeName, type);
                return type;
            }

            // 5. One final attempt with runtime registry and short name
            if (runtimeRegistry_.hasClass(shortName)) {
                std::cout << "Debug [getTypeFromTypeContext]: Found type in runtime registry with short name: " << shortName << std::endl;
                type = std::make_shared<ClassType>(shortName);
                typeRegistry_.cacheType(shortName, type);
                typeRegistry_.cacheType(fullTypeName, type);
                return type;
            }

            // Add detailed debug information about the state of registries
            std::cout << "Debug [getTypeFromTypeContext]: Failed to resolve type. Registry state:" << std::endl;
            std::cout << "Full type name: " << fullTypeName << std::endl;
            std::cout << "Namespace part: " << namespacePart << std::endl;
            std::cout << "Short name: " << shortName << std::endl;
            std::cout << "Namespace registered: " << (typeRegistry_.isNamespaceRegistered(namespacePart) ? "yes" : "no") << std::endl;
            std::cout << "Runtime registry has class (full): " << (runtimeRegistry_.hasClass(fullTypeName) ? "yes" : "no") << std::endl;
            std::cout << "Runtime registry has class (short): " << (runtimeRegistry_.hasClass(shortName) ? "yes" : "no") << std::endl;
            std::cout << "Type registry has cached type (full): " << (typeRegistry_.getCachedType(fullTypeName) ? "yes" : "no") << std::endl;
            std::cout << "Type registry has cached type (short): " << (typeRegistry_.getCachedType(shortName) ? "yes" : "no") << std::endl;

            // One last attempt to register web types if we haven't found the type
            if (fullTypeName.find("pryst::runtime::web::") == 0) {
                std::cout << "Debug [getTypeFromTypeContext]: Final attempt to register web types for: " << fullTypeName << std::endl;
                runtime::web::registerWebTypes(runtimeRegistry_);

                // Check one last time
                type = typeRegistry_.getCachedType(fullTypeName);
                if (type) {
                    std::cout << "Debug [getTypeFromTypeContext]: Found type in final attempt: " << fullTypeName << std::endl;
                    return type;
                }
            }

            throw core::Error("TypeError", "Unknown qualified type: " + fullTypeName);
        }

        // Handle other type contexts (basic, nullable, array, etc.)
        if (ctx->basicType()) {
            return visit(ctx->basicType());
        }
        if (ctx->nullableType()) {
            return visit(ctx->nullableType());
        }
        if (ctx->arrayType()) {
            return visit(ctx->arrayType());
        }
        if (ctx->mapType()) {
            return visit(ctx->mapType());
        }
        if (ctx->functionType()) {
            return visit(ctx->functionType());
        }

        throw core::Error("TypeError", "Unknown type: " + ctx->getText());
    } catch (const std::exception& e) {
        std::cerr << "Error [getTypeFromTypeContext]: Exception while processing type: "
                  << ctx->getText() << " - " << e.what() << std::endl;
        throw;
    }
}

std::any TypeChecker::getTypeFromReturnTypeContext(PrystParser::ReturnTypeContext* ctx) {
    std::cout << "Debug [getTypeFromReturnTypeContext]: Processing return type context" << std::endl;

    if (!ctx) {
        std::cerr << "Error [getTypeFromReturnTypeContext]: Null return type context" << std::endl;
        throw core::Error("TypeError", "Null return type context");
    }

    if (ctx->VOID()) {
        std::cout << "Debug [getTypeFromReturnTypeContext]: Found void return type" << std::endl;
        return std::any(VOID_TYPE);
    }

    if (ctx->type()) {
        std::cout << "Debug [getTypeFromReturnTypeContext]: Processing type for return type" << std::endl;
        return visit(ctx->type());
    }

    throw core::Error("TypeError", "Invalid return type");
}

std::any TypeChecker::visitStatement(PrystParser::StatementContext* ctx) {
    try {
        if (ctx->tryStmt()) {
            auto tryResult = visit(ctx->tryStmt());
            auto tryType = std::any_cast<std::shared_ptr<Type>>(tryResult);

            // Validate that catch blocks handle error types properly
            if (auto errorType = std::dynamic_pointer_cast<ErrorType>(tryType)) {
                errorHandler_.validateErrorChain({errorType});
            }
            return tryResult;
        }

        if (ctx->varDecl()) return visit(ctx->varDecl());
        if (ctx->ifStmt()) return visit(ctx->ifStmt());
        if (ctx->whileStmt()) return visit(ctx->whileStmt());
        if (ctx->forStmt()) return visit(ctx->forStmt());
        if (ctx->returnStmt()) return visit(ctx->returnStmt());
        if (ctx->expressionStmt()) return visit(ctx->expressionStmt());
        if (ctx->breakStmt()) return visit(ctx->breakStmt());
        if (ctx->continueStmt()) return visit(ctx->continueStmt());
        return std::any(VOID_TYPE);
    } catch (const core::Error& e) {
        errorHandler_.handleTypedError(e, e.getType());
        return std::any(typeRegistry_.registerErrorType(e.getType()));
    }
}

std::any TypeChecker::visitType(PrystParser::TypeContext* ctx) {
    return std::any(getTypeFromTypeContext(ctx));
}

std::any TypeChecker::visitMapType(PrystParser::MapTypeContext* ctx) {
    std::cout << "Debug [visitMapType]: Processing map type" << std::endl;

    auto keyTypeCtx = ctx->keyType();
    auto valueTypeCtx = ctx->type();
    if (!keyTypeCtx || !valueTypeCtx) {
        throw core::Error("TypeError", "Map type requires key and value type arguments");
    }

    auto keyType = std::any_cast<std::shared_ptr<Type>>(visit(keyTypeCtx));
    auto valueType = std::any_cast<std::shared_ptr<Type>>(visit(valueTypeCtx));

    return std::any(std::make_shared<MapType>(keyType, valueType));
}

std::any TypeChecker::visitFunctionType(PrystParser::FunctionTypeContext* ctx) {
    std::cout << "Debug [visitFunctionType]: Processing function type" << std::endl;

    auto paramTypes = std::vector<std::shared_ptr<Type>>();
    auto typeList = ctx->typeList();
    if (typeList) {
        for (auto typeCtx : typeList->type()) {
            paramTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visit(typeCtx)));
        }
    }

    auto returnType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->returnType()));
    return std::any(std::make_shared<FunctionType>(returnType, paramTypes));
}

std::any TypeChecker::checkTypesMatch(
    std::any expectedTypeAny,
    std::any actualTypeAny,
    antlr4::ParserRuleContext* ctx
) {
    auto expectedType = std::any_cast<std::shared_ptr<Type>>(expectedTypeAny);
    auto actualType = std::any_cast<std::shared_ptr<Type>>(actualTypeAny);

    std::cout << "Debug [checkTypesMatch]: Checking if " << actualType->toString()
              << " matches expected type " << expectedType->toString() << std::endl;

    if (!isAssignable(expectedTypeAny, actualTypeAny)) {
        throw core::Error("TypeError", "Type mismatch: expected " + expectedType->toString() +
                   " but got " + actualType->toString());
    }
    return expectedTypeAny;
}

std::any TypeChecker::visitClassDecl(PrystParser::ClassDeclContext* ctx) {
    std::cout << "Debug [visitClassDecl]: Processing class declaration" << std::endl;
    std::string className = ctx->IDENTIFIER(0)->getText();

    // Check if we already have a placeholder class type
    auto existingType = typeRegistry_.getCachedType(className);
    std::shared_ptr<ClassType> classType;

    if (existingType && existingType->getKind() == Type::Kind::Class) {
        std::cout << "Debug [visitClassDecl]: Found existing class type for " << className << std::endl;
        classType = std::static_pointer_cast<ClassType>(existingType);
    } else {
        std::cout << "Debug [visitClassDecl]: Creating new class type for " << className << std::endl;
        classType = std::make_shared<ClassType>(className);
        typeRegistry_.cacheType(className, classType);
    }

    scopeManager_.pushScope();
    scopeManager_.declareVariable(className, classType);

    // Process members
    std::vector<std::pair<std::string, llvm::Type*>> classMembers;
    for (const auto& memberCtx : ctx->classMember()) {
        if (memberCtx->type()) {  // Check if there is a type
            auto memberName = memberCtx->IDENTIFIER()->getText();
            auto memberTypeAny = visit(memberCtx->type());
            auto memberType = std::any_cast<std::shared_ptr<Type>>(memberTypeAny);

            std::cout << "Debug [visitClassDecl]: Successfully got type for field " << memberName
                      << " with type " << memberType->toString() << std::endl;

            // Get LLVM type for the member
            llvm::Type* llvmType = typeRegistry_.getLLVMType(memberType);
            if (!llvmType) {
                std::cerr << "Error [visitClassDecl]: Failed to get LLVM type for member " << memberName << std::endl;
                throw core::Error("TypeError", "Failed to get LLVM type for member " + memberName);
            }

            std::cout << "Debug [visitClassDecl]: Adding field " << memberName
                      << " with type " << memberType->toString() << std::endl;

            // Add member to both scope and class type
            scopeManager_.declareVariable(memberName, memberType);
            classMembers.push_back({memberName, llvmType});
            classType->addField(memberName, memberType);
        }
    }

    // Register or update the class with its members
    if (!typeRegistry_.hasClass(className)) {
        std::cout << "Debug [visitClassDecl]: Registering new class " << className << std::endl;
        typeRegistry_.registerClass(className, classMembers);
    } else {
        std::cout << "Debug [visitClassDecl]: Updating existing class " << className << std::endl;
        // Update existing class registration with new members
        for (const auto& member : classMembers) {
            typeRegistry_.registerMemberIndex(className, member.first, classMembers.size());
        }
    }

    scopeManager_.popScope();
    return std::any(classType);
}

std::any TypeChecker::visitInstanceOfExpr(PrystParser::InstanceOfExprContext* ctx) {
    std::cout << "Debug [visitInstanceOfExpr]: Processing instanceof expression" << std::endl;

    auto exprType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    auto checkType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->type()));

    // Special handling for error types
    if (typeRegistry_.isErrorType(checkType->toString())) {
        if (!typeRegistry_.isErrorType(exprType->toString())) {
            throw core::Error("TypeError", "Cannot check if non-error type is instance of error type");
        }

        // Get variable name for type narrowing if this is a variable expression
        if (auto varExpr = dynamic_cast<PrystParser::VariableExprContext*>(ctx->expression())) {
            std::string varName = varExpr->IDENTIFIER()->getText();
            scopeManager_.narrowType(varName, checkType);
        }
    }

    // Handle other type checks
    if (exprType->getKind() != Type::Kind::Class || checkType->getKind() != Type::Kind::Class) {
        throw core::Error("TypeError", "instanceof can only be used with class types");
    }

    return std::any(BOOL_TYPE);
}

std::any TypeChecker::visitFunctionDecl(PrystParser::FunctionDeclContext* ctx) {
    std::cout << "Debug [visitFunctionDecl]: Processing function declaration" << std::endl;
    std::string funcName = ctx->IDENTIFIER()->getText();
    auto returnType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->returnType()));

    scopeManager_.pushScope();

    std::vector<std::shared_ptr<Type>> paramTypes;
    for (const auto& param : ctx->parameters()) {
        auto paramType = std::any_cast<std::shared_ptr<Type>>(visit(param->type()));
        auto paramName = param->IDENTIFIER()->getText();
        scopeManager_.declareVariable(paramName, paramType);
        paramTypes.push_back(paramType);
    }

    auto funcType = std::make_shared<FunctionType>(returnType, paramTypes);
    scopeManager_.declareVariable(funcName, funcType);

    visit(ctx->block());
    scopeManager_.popScope();

    return std::any(funcType);
}





std::any TypeChecker::visitErrorField(PrystParser::ErrorFieldContext* ctx) {
    std::cout << "Debug [visitErrorField]: Processing error field" << std::endl;
    auto memberName = ctx->IDENTIFIER()->getText();
    auto memberTypeAny = visit(ctx->type());
    auto memberType = std::any_cast<std::shared_ptr<Type>>(memberTypeAny);

    if (memberType->getKind() == Type::Kind::Error) {
        auto fieldError = std::make_shared<core::Error>("TypeError", "Error fields cannot be of Error type");
        errorHandler_.handleTypedError(*fieldError, "TypeError");
        return std::any(typeRegistry_.registerErrorType("TypeError"));
    }

    return std::any(memberType);
}

std::any TypeChecker::visitErrorMethod(PrystParser::ErrorMethodContext* ctx) {
    std::cout << "Debug [visitErrorMethod]: Processing error method" << std::endl;
    auto returnTypeAny = visit(ctx->returnType());
    auto returnType = std::any_cast<std::shared_ptr<Type>>(returnTypeAny);
    auto methodName = ctx->IDENTIFIER()->getText();

    std::vector<std::shared_ptr<Type>> paramTypes;
    if (ctx->parameters()) {
        for (auto paramCtx : ctx->parameters()->parameter()) {
            auto paramTypeAny = visit(paramCtx->type());
            paramTypes.push_back(std::any_cast<std::shared_ptr<Type>>(paramTypeAny));
        }
    }

    auto methodType = std::make_shared<FunctionType>(returnType, paramTypes);

    auto errorCtx = dynamic_cast<PrystParser::ErrorDeclContext*>(ctx->parent->parent);
    if (errorCtx) {
        std::string errorClassName = errorCtx->IDENTIFIER(0)->getText();
        std::string baseClass = errorCtx->EXTENDS() ? errorCtx->IDENTIFIER(1)->getText() : "Error";
        try {
            typeRegistry_.validateErrorMethodOverride(errorClassName, methodName, methodType, baseClass);
        } catch (const Error& e) {
            auto validationError = std::make_shared<Error>(e.getType(), e.getMessage());
            errorHandler_.handleTypedError(*validationError, "ErrorMethodValidation");
            return std::any(typeRegistry_.registerErrorType("ErrorMethodValidation"));
        }
    }

    return std::any(methodType);
}

    auto causeType = std::make_shared<NullableType>(typeRegistry_.getCachedType("Error"));
    llvm::Type* causeLLVMType = typeRegistry_.getLLVMType(causeType);

    std::vector<std::pair<std::string, llvm::Type*>> errorMembers;
    errorMembers.push_back({"cause", causeLLVMType});

    auto errorType = std::make_shared<ErrorType>(errorName);
    errorType->addField("cause", causeType);
    scopeManager_.declareVariable("cause", causeType);

    for (const auto& memberCtx : ctx->errorMember()) {
        if (auto methodCtx = dynamic_cast<PrystParser::ErrorMethodContext*>(memberCtx)) {
            scopeManager_.pushScope();
            auto returnType = visit(methodCtx->returnType());
            auto methodName = methodCtx->IDENTIFIER()->getText();
            auto params = visit(methodCtx->parameters());
            auto methodType = std::make_shared<FunctionType>(
                std::any_cast<std::shared_ptr<Type>>(returnType),
                std::any_cast<std::vector<std::shared_ptr<Type>>>(params)
            );

            if (baseClass != "Error") {
                typeRegistry_.validateErrorMethodOverride(errorName, methodName, methodType, baseClass);
            }

            errorType->addMethod(methodName, methodType);
        } else if (auto fieldCtx = dynamic_cast<PrystParser::ErrorFieldContext*>(memberCtx)) {
            auto fieldType = visit(fieldCtx->type());
            auto fieldTypePtr = std::any_cast<std::shared_ptr<Type>>(fieldType);
            auto fieldName = fieldCtx->IDENTIFIER()->getText();

            if (errorType->hasMember(fieldName)) {
                auto dupError = std::make_shared<core::Error>("TypeError",
                    "Duplicate field name in error class: " + fieldName);
                errorHandler_.handleTypedError(*dupError, "TypeError");
                return std::any(typeRegistry_.registerErrorType("TypeError"));
            }

            llvm::Type* llvmType = typeRegistry_.getLLVMType(fieldTypePtr);
            errorMembers.push_back({fieldName, llvmType});
            errorType->addField(fieldName, fieldTypePtr);
        } else if (auto chainCtx = dynamic_cast<PrystParser::ErrorChainFieldContext*>(memberCtx)) {
            auto chainType = visitErrorChainField(chainCtx);
            auto chainTypePtr = std::any_cast<std::shared_ptr<Type>>(chainType);
            auto fieldName = chainCtx->IDENTIFIER()->getText();

            if (errorType->hasMember(fieldName)) {
                auto dupError = std::make_shared<core::Error>("TypeError",
                    "Duplicate field name in error class: " + fieldName);
                errorHandler_.handleTypedError(*dupError, "TypeError");
                return std::any(typeRegistry_.registerErrorType("TypeError"));
            }

            typeRegistry_.validateErrorChain(errorName, chainTypePtr->toString());
            llvm::Type* llvmType = typeRegistry_.getLLVMType(chainTypePtr);
            errorMembers.push_back({fieldName, llvmType});
            errorType->addField(fieldName, chainTypePtr);
        }
    }

    typeRegistry_.registerClass(errorName, errorMembers, baseClass);
    declareVariable(errorName, errorType);
    return std::any(errorType);
}

// Removed duplicate implementation of visitNullableChain - using version defined earlier

// Removed duplicate implementation of visitMemberAccessExpr - using version defined earlier

std::any TypeChecker::visitEmptyArrayLiteral(PrystParser::EmptyArrayLiteralContext* ctx) {
    std::cout << "Debug [visitEmptyArrayLiteral]: Processing empty array literal" << std::endl;

    // Empty array literals don't have explicit type in grammar
    // Default to int[] if no type is specified
    auto elementType = INT_TYPE;
    typeRegistry_.registerArrayType(elementType->toString());
    return std::any(std::make_shared<ArrayType>(elementType));
}

std::any TypeChecker::visitNonEmptyArrayLiteral(PrystParser::NonEmptyArrayLiteralContext* ctx) {
    std::cout << "Debug [visitNonEmptyArrayLiteral]: Processing non-empty array literal" << std::endl;
    if (ctx->expression().empty()) {
        auto emptyError = std::make_shared<core::Error>("TypeError", "Array literal must not be empty");
        errorHandler_.handleTypedError(*emptyError, "TypeError");
        return std::any(typeRegistry_.registerErrorType("TypeError"));
    }

    auto firstExpr = visit(ctx->expression(0));
    auto elementType = std::any_cast<std::shared_ptr<Type>>(firstExpr);

    for (size_t i = 1; i < ctx->expression().size(); ++i) {
        auto exprType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(i)));
        if (!isAssignable(std::any(elementType), std::any(exprType))) {
            auto typeError = std::make_shared<core::Error>("TypeError",
                "Inconsistent types in array literal: expected " + elementType->toString() +
                ", got " + exprType->toString());
            errorHandler_.handleTypedError(*typeError, "TypeError");
            return std::any(typeRegistry_.registerErrorType("TypeError"));
        }
    }

    return std::any(std::make_shared<ArrayType>(elementType));
}

std::any TypeChecker::visitTryStmt(PrystParser::TryStmtContext* ctx) {
    std::cout << "Debug [visitTryStmt]: Processing try statement" << std::endl;

    // Process try block
    scopeManager_.pushScope();
    auto tryResult = visit(ctx->block(0));
    auto tryType = std::any_cast<std::shared_ptr<Type>>(tryResult);
    scopeManager_.popScope();

    std::shared_ptr<Type> resultType = tryType;

    // Process catch clauses
    for (auto catchClause : ctx->catchClause()) {
        auto errorType = std::any_cast<std::shared_ptr<Type>>(visit(catchClause->type()));

        // Verify catch clause type is Error or extends Error
        if (!isErrorType(errorType)) {
            auto typeError = std::make_shared<core::Error>("TypeError",
                "Catch clause type must be Error or extend Error: " + errorType->toString());
            errorHandler_.handleTypedError(*typeError, "TypeError");
            return std::any(typeRegistry_.registerErrorType("TypeError"));
        }

        // Create new scope for catch block with exception variable
        scopeManager_.pushScope();
        auto errorVar = catchClause->IDENTIFIER()->getText();
        scopeManager_.declareVariable(errorVar, errorType);

        // Handle error chaining if present
        if (catchClause->CHAIN()) {
            auto chainExpr = visit(catchClause->expression());
            auto chainType = std::any_cast<std::shared_ptr<Type>>(chainExpr);

            // Use the new error chain validation
            auto chainedType = validateErrorChain(errorType, chainType);
            if (chainedType->getKind() == Type::Kind::Error) {
                scopeManager_.updateVariableType(errorVar, chainedType);
            }
        }

        auto catchResult = visit(catchClause->block());
        auto catchType = std::any_cast<std::shared_ptr<Type>>(catchResult);

        // Ensure catch block type matches try block type
        if (!isAssignable(std::any(resultType), std::any(catchType))) {
            auto matchError = std::make_shared<core::Error>("TypeError",
                "Catch block type mismatch: expected " + resultType->toString() +
                " but got " + catchType->toString());
            errorHandler_.handleTypedError(*matchError, "TypeError");
            return std::any(typeRegistry_.registerErrorType("TypeError"));
        }

        scopeManager_.popScope();
    }

    // Process finally block if present
    if (ctx->FINALLY()) {
        scopeManager_.pushScope();
        visit(ctx->block(1));
        scopeManager_.popScope();
    }

    return std::any(resultType);
}

std::any TypeChecker::visitEmptyMapLiteral(PrystParser::EmptyMapLiteralContext* ctx) {
    std::cout << "Debug [visitEmptyMapLiteral]: Processing empty map literal" << std::endl;

    // Empty map literals don't have explicit types in grammar
    // Default to Map<string, any> if no types specified
    auto keyType = STRING_TYPE;
    auto valueType = ANY_TYPE;
    typeRegistry_.registerMapType(keyType->toString(), valueType->toString());
    return std::any(std::make_shared<MapType>(keyType, valueType));
}

std::any TypeChecker::visitNonEmptyMapLiteral(PrystParser::NonEmptyMapLiteralContext* ctx) {
    std::cout << "Debug [visitNonEmptyMapLiteral]: Processing non-empty map literal" << std::endl;
    if (ctx->mapEntry().empty()) {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError"),
            scopeManager_.getCurrentScopeName(),
            false));  // Don't propagate to parent since this is a literal error
    }

    // Visit first entry to get value type
    auto firstEntry = ctx->mapEntry(0);
    auto firstValueAny = visit(firstEntry->expression());
    auto firstValueType = std::any_cast<std::shared_ptr<Type>>(firstValueAny);

    std::cout << "Debug [visitNonEmptyMapLiteral]: First entry value type: " << firstValueType->toString() << std::endl;

    // Check that all entries have compatible types
    for (size_t i = 1; i < ctx->mapEntry().size(); i++) {
        auto entry = ctx->mapEntry(i);
        auto valueAny = visit(entry->expression());
        auto valueType = std::any_cast<std::shared_ptr<Type>>(valueAny);

        std::cout << "Debug [visitNonEmptyMapLiteral]: Entry " << i << " value type: " << valueType->toString() << std::endl;

        if (!isAssignable(firstValueType, valueType)) {
            return std::any(propagateErrorWithTransform(
                typeRegistry_.registerErrorType("TypeError"),
                {firstValueType, valueType},
                [](std::shared_ptr<Type> err) {
                    return std::make_shared<ErrorType>("TypeError", "Incompatible value types in map literal");
                }));
        }
    }

    return std::any(std::make_shared<MapType>(STRING_TYPE, firstValueType));
}

std::any TypeChecker::visitMapEntry(PrystParser::MapEntryContext* ctx) {
    std::cout << "Debug [visitMapEntry]: Processing map entry" << std::endl;
    return visit(ctx->expression());
}

std::any TypeChecker::visitMapKey(PrystParser::MapKeyContext* ctx) {
    std::cout << "Debug [visitMapKey]: Processing map key" << std::endl;
    // Map keys are always strings in Pryst
    return std::any(STRING_TYPE);
}



std::any TypeChecker::visitErrorChainField(PrystParser::ErrorChainFieldContext* ctx) {
    std::cout << "Debug [visitErrorChainField]: Processing error chain field" << std::endl;

    auto chainType = visit(ctx->type());
    auto chainTypePtr = std::any_cast<std::shared_ptr<Type>>(chainType);
    auto fieldName = ctx->IDENTIFIER()->getText();

    // Use advanced error propagation system
    if (!isValidErrorChain(chainTypePtr)) {
        auto invalidError = std::make_shared<core::Error>("TypeError",
            "Invalid error chain type: " + chainTypePtr->toString());
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError"),
            scopeManager_.getCurrentScopeName()));
    }

    try {
        // Create error chain type with propagation
        auto baseError = std::make_shared<core::ErrorType>("Error");
        auto chainedType = propagateErrorWithTransform(
            baseError,
            {chainTypePtr},
            [this](std::shared_ptr<Type> err) {
                return validateErrorChain(err, std::static_pointer_cast<ErrorType>(err));
            });

        auto nullableChainType = std::make_shared<NullableType>(chainedType);
        typeRegistry_.registerNullableType(chainedType->toString());
        return std::any(nullableChainType);
    } catch (const core::Error& e) {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("ErrorChainValidation"),
            scopeManager_.getCurrentScopeName()));
    }
}

std::any TypeChecker::visitNonNullAssertExpr(PrystParser::NonNullAssertExprContext* ctx) {
    std::cout << "Debug [visitNonNullAssertExpr]: Processing non-null assertion" << std::endl;
    auto exprType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));

    if (exprType->getKind() != Type::Kind::Nullable) {
        auto assertError = std::make_shared<core::Error>("TypeError", "Non-null assertion can only be used on nullable types");
        errorHandler_.handleTypedError(*assertError, "TypeError");
        return std::any(typeRegistry_.registerErrorType("TypeError"));
    }

    auto nullableType = std::static_pointer_cast<NullableType>(exprType);
    std::cout << "Debug [visitNonNullAssertExpr]: Unwrapping nullable type: "
              << nullableType->getInnerType()->toString() << std::endl;
    return std::any(nullableType->getInnerType());
}

bool TypeChecker::isAssignable(std::any targetTypeAny, std::any sourceTypeAny) {
    try {
        auto targetType = std::any_cast<std::shared_ptr<Type>>(targetTypeAny);
        auto sourceType = std::any_cast<std::shared_ptr<Type>>(sourceTypeAny);

        std::cout << "Debug [isAssignable]: Checking if " << sourceType->toString()
                  << " is assignable to " << targetType->toString() << std::endl;

        // Handle null assignment to nullable types
        if (sourceType->getKind() == Type::Kind::Null) {
            bool isNullable = typeRegistry_.isTypeNullable(typeRegistry_.convertTypeToLLVMType(targetType));
            std::cout << "Debug [isAssignable]: Source is null, target "
                      << (isNullable ? "is" : "is not") << " nullable" << std::endl;
            return isNullable;
        }

        // Handle nullable source types
        if (sourceType->getKind() == Type::Kind::Nullable) {
            auto nullableSource = std::static_pointer_cast<NullableType>(sourceType);
            // Allow null assignment to nullable types
            if (nullableSource->getInnerType()->getKind() == Type::Kind::Null) {
                return typeRegistry_.isTypeNullable(typeRegistry_.convertTypeToLLVMType(targetType));
            }
            // Check if inner type is assignable
            return isAssignable(targetTypeAny, std::any(nullableSource->getInnerType()));
        }

        // Handle nullable target types
        if (targetType->getKind() == Type::Kind::Nullable) {
            auto nullableTarget = std::static_pointer_cast<NullableType>(targetType);
            // Allow null assignment
            if (sourceType->getKind() == Type::Kind::Null) {
                return true;
            }
            // Check if source type can be assigned to inner type
            return isAssignable(std::any(nullableTarget->getInnerType()), sourceTypeAny);
        }

        // Direct type equality
        if (targetType->toString() == sourceType->toString()) {
            std::cout << "Debug [isAssignable]: Types match exactly" << std::endl;
            return true;
        }

        // Error type compatibility
        if (typeRegistry_.isErrorType(targetType->toString()) &&
            typeRegistry_.isErrorType(sourceType->toString())) {
            return typeRegistry_.isSubclassOf(sourceType->toString(), targetType->toString());
        }

        // Array type compatibility
        if (targetType->getKind() == Type::Kind::Array && sourceType->getKind() == Type::Kind::Array) {
            auto targetArray = std::static_pointer_cast<ArrayType>(targetType);
            auto sourceArray = std::static_pointer_cast<ArrayType>(sourceType);
            return isAssignable(std::any(targetArray->getElementType()), std::any(sourceArray->getElementType()));
        }

        // Map type compatibility
        if (targetType->getKind() == Type::Kind::Map && sourceType->getKind() == Type::Kind::Map) {
            auto targetMap = std::static_pointer_cast<MapType>(targetType);
            auto sourceMap = std::static_pointer_cast<MapType>(sourceType);
            return isAssignable(std::any(targetMap->getKeyType()), std::any(sourceMap->getKeyType())) &&
                   isAssignable(std::any(targetMap->getValueType()), std::any(sourceMap->getValueType()));
        }

        // Function type compatibility
        if (targetType->getKind() == Type::Kind::Function && sourceType->getKind() == Type::Kind::Function) {
            auto targetFunc = std::static_pointer_cast<FunctionType>(targetType);
            auto sourceFunc = std::static_pointer_cast<FunctionType>(sourceType);

            // Check return type compatibility
            if (!isAssignable(std::any(targetFunc->getReturnType()), std::any(sourceFunc->getReturnType()))) {
                return false;
            }

            // Check parameter types compatibility
            auto& targetParams = targetFunc->getParameterTypes();
            auto& sourceParams = sourceFunc->getParameterTypes();

            if (targetParams.size() != sourceParams.size()) {
                return false;
            }

            for (size_t i = 0; i < targetParams.size(); i++) {
                if (!isAssignable(std::any(targetParams[i]), std::any(sourceParams[i]))) {
                    return false;
                }
            }
            return true;
        } else if (targetType->getKind() == Type::Kind::Interface && sourceType->getKind() == Type::Kind::Class) {
            return typeRegistry_.implementsInterface(sourceType->toString(), targetType->toString());
        }

        // Handle interface type compatibility
        if (targetType->getKind() == Type::Kind::Interface) {
            if (sourceType->getKind() == Type::Kind::Class) {
                return typeRegistry_.implementsInterface(sourceType->toString(), targetType->toString());
            }
            return false;
        }
    } catch (const std::bad_any_cast& e) {
        return false;
    }



std::any TypeChecker::visitKeyType(PrystParser::KeyTypeContext* ctx) {
    std::cout << "Debug [visitKeyType]: Processing key type" << std::endl;
    if (ctx->STR()) {
        return std::any(STRING_TYPE);
    } else if (ctx->INT()) {
        return std::any(INT_TYPE);
    }
    auto typeError = std::make_shared<core::Error>("TypeError", "Invalid key type");
    errorHandler_.handleTypedError(*typeError, "TypeError");
    return std::any(typeRegistry_.registerErrorType("TypeError"));
}

std::any TypeChecker::visitPrimary(PrystParser::PrimaryContext* ctx) {
    std::cout << "Debug [visitPrimary]: Processing primary expression" << std::endl;

    if (ctx->NULL_LIT()) {
        std::cout << "Debug [visitPrimary]: Found null literal" << std::endl;
        return std::any(NULL_TYPE);
    }

    if (ctx->IDENTIFIER()) {
        std::cout << "Debug [visitPrimary]: Found identifier: " << ctx->IDENTIFIER()->getText() << std::endl;
        return std::any(lookupVariable(ctx->IDENTIFIER()->getText()));
    }

    if (ctx->INTEGER()) {
        std::cout << "Debug [visitPrimary]: Found integer literal" << std::endl;
        return std::any(INT_TYPE);
    }

    if (ctx->FLOAT_LITERAL()) {
        std::cout << "Debug [visitPrimary]: Found float literal" << std::endl;
        return std::any(FLOAT_TYPE);
    }

    if (ctx->BOOLEAN()) {
        std::cout << "Debug [visitPrimary]: Found boolean literal" << std::endl;
        return std::any(BOOL_TYPE);
    }

    if (ctx->STRING()) {
        std::cout << "Debug [visitPrimary]: Found string literal" << std::endl;
        return std::any(STRING_TYPE);
    }

    std::cout << "Debug [visitPrimary]: Delegating to child nodes" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitNullCoalesceExpr(PrystParser::NullCoalesceExprContext* ctx) {
    std::cout << "Debug [visitNullCoalesceExpr]: Processing null coalesce expression" << std::endl;

    auto leftType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto rightType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));

    if (!leftType->isNullable()) {
        auto nullError = std::make_shared<core::Error>("TypeError", "Left operand of ?? must be nullable");
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError"),
            scopeManager_.getCurrentScopeName()));
    }

    auto innerType = std::static_pointer_cast<NullableType>(leftType)->getInnerType();
    if (!isAssignable(innerType, rightType) && !isAssignable(rightType, innerType)) {
        auto compatError = std::make_shared<core::Error>("TypeError",
            "Incompatible types in null coalescing expression: " +
            innerType->toString() + " and " + rightType->toString());
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError"),
            scopeManager_.getCurrentScopeName()));
    }

    return std::any(isAssignable(innerType, rightType) ? rightType : innerType);
}

std::any TypeChecker::visitStringInterpolation(PrystParser::StringInterpolationContext* ctx) {
    std::cout << "Debug [visitStringInterpolation]: Processing string interpolation" << std::endl;
    for (auto expr : ctx->expression()) {
        auto exprType = visit(expr);
        std::cout << "Debug [visitStringInterpolation]: Expression type: "
                  << std::any_cast<std::shared_ptr<Type>>(exprType)->toString() << std::endl;
    }
    return std::any(STRING_TYPE);
}

std::any TypeChecker::visitIdentifierList(PrystParser::IdentifierListContext* ctx) {
    std::cout << "Debug [visitIdentifierList]: Processing identifier list" << std::endl;
    std::vector<std::string> identifiers;
    for (auto id : ctx->IDENTIFIER()) {
        identifiers.push_back(id->getText());
    }
    return std::any(identifiers);
}

std::any TypeChecker::visitGenericParams(PrystParser::GenericParamsContext* ctx) {
    std::cout << "Debug [visitGenericParams]: Processing generic parameters" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitGenericArgs(PrystParser::GenericArgsContext* ctx) {
    std::cout << "Debug [visitGenericArgs]: Processing generic arguments" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitInterfaceMember(PrystParser::InterfaceMemberContext* ctx) {
    std::cout << "Debug [visitInterfaceMember]: Processing interface member" << std::endl;
    auto result = visitChildren(ctx);
    if (auto error = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result))) {
        return std::any(propagateErrorThroughScope(error,
            scopeManager_.getCurrentScopeName(),
            false));  // Don't propagate interface errors to parent
    }
    return result;
}

std::any TypeChecker::visitClassMember(PrystParser::ClassMemberContext* ctx) {
    std::cout << "Debug [visitClassMember]: Processing class member" << std::endl;
    auto result = visitChildren(ctx);
    if (auto error = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result))) {
        return std::any(propagateErrorThroughScope(error,
            scopeManager_.getCurrentScopeName(),
            false));  // Don't propagate class member errors to parent
    }
    return result;
}



std::any TypeChecker::visitOverloadParams(PrystParser::OverloadParamsContext* ctx) {
    std::cout << "Debug [visitOverloadParams]: Processing overload parameters" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitConstructorDecl(PrystParser::ConstructorDeclContext* ctx) {
    std::cout << "Debug [visitConstructorDecl]: Processing constructor declaration" << std::endl;
    auto result = visitChildren(ctx);
    if (auto error = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result))) {
        return std::any(propagateErrorThroughScope(error,
            scopeManager_.getCurrentScopeName()));
    }
    return result;
}

std::any TypeChecker::visitConstructorBlock(PrystParser::ConstructorBlockContext* ctx) {
    std::cout << "Debug [visitConstructorBlock]: Processing constructor block" << std::endl;
    pushScope();
    auto result = visitChildren(ctx);
    if (auto error = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result))) {
        result = std::any(propagateErrorThroughScope(error,
            scopeManager_.getCurrentScopeName()));
    }
    popScope();
    return result;
}

std::any TypeChecker::visitTypeList(PrystParser::TypeListContext* ctx) {
    std::cout << "Debug [visitTypeList]: Processing type list" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitStringLiteral(PrystParser::StringLiteralContext* ctx) {
    std::cout << "Debug [visitStringLiteral]: Processing string literal" << std::endl;
    return std::any(STRING_TYPE);
}

std::any TypeChecker::visitMultiplicativeExpr(PrystParser::MultiplicativeExprContext* ctx) {
    std::cout << "Debug [visitMultiplicativeExpr]: Processing multiplicative expression" << std::endl;

    auto leftType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto rightType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));

    if (!typeRegistry_.isNumericType(leftType) || !typeRegistry_.isNumericType(rightType)) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {leftType, rightType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Multiplicative operators require numeric operands");
            }));
    }

    scopeManager_.pushScope();
    auto resultType = typeRegistry_.getCommonNumericType(leftType, rightType);
    scopeManager_.popScope();

    return std::any(resultType);
}

std::any TypeChecker::visitAdditiveExpr(PrystParser::AdditiveExprContext* ctx) {
    std::cout << "Debug [visitAdditiveExpr]: Processing additive expression" << std::endl;

    auto leftType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto rightType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));

    if (ctx->op->getType() == PrystParser::PLUS) {
        if (leftType->toString() == "string" || rightType->toString() == "string") {
            return std::any(propagateErrorWithTransform(
                typeRegistry_.registerErrorType("TypeError"),
                {leftType, rightType},
                [](std::shared_ptr<Type> err) {
                    return std::make_shared<ErrorType>("TypeError",
                        "String concatenation with non-string types is not allowed");
                }));
        }
    }

    if (!typeRegistry_.isNumericType(leftType) || !typeRegistry_.isNumericType(rightType)) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {leftType, rightType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Additive operators require numeric operands");
            }));
    }

    scopeManager_.pushScope();
    auto resultType = typeRegistry_.getCommonNumericType(leftType, rightType);
    scopeManager_.popScope();

    return std::any(resultType);
}

std::any TypeChecker::visitLambdaParams(PrystParser::LambdaParamsContext* ctx) {
    std::cout << "Debug [visitLambdaParams]: Processing lambda parameters" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitImportPath(PrystParser::ImportPathContext* ctx) {
    std::cout << "Debug [visitImportPath]: Processing import path" << std::endl;
    return std::any(VOID_TYPE);
}

std::any TypeChecker::visitChainedCall(PrystParser::ChainedCallContext* ctx) {
    std::cout << "Debug [visitChainedCall]: Processing chained call" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitProgram(PrystParser::ProgramContext* ctx) {
    std::cout << "Debug [visitProgram]: Processing program" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitBlock(PrystParser::BlockContext* ctx) {
    std::cout << "Debug [visitBlock]: Processing block" << std::endl;
    pushScope();
    auto result = visitChildren(ctx);
    popScope();
    return result;
}

std::any TypeChecker::visitRelationalExpr(PrystParser::RelationalExprContext* ctx) {
    std::cout << "Debug [visitRelationalExpr]: Processing relational expression" << std::endl;

    auto leftType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto rightType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));

    if (!typeRegistry_.isComparable(leftType, rightType)) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {leftType, rightType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Cannot compare incompatible types");
            }));
    }

    return std::any(BOOL_TYPE);
}

std::any TypeChecker::visitVarDecl(PrystParser::VarDeclContext* ctx) {
    std::cout << "Debug [visitVarDecl]: Processing variable declaration" << std::endl;

    auto identList = ctx->identifierList();
    if (!identList) {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("InternalError", "Variable declaration missing identifier list"),
            scopeManager_.getCurrentScopeName()));
    }

    std::shared_ptr<Type> varType;
    if (ctx->type()) {
        auto typeAny = getTypeFromTypeContext(ctx->type());
        varType = std::any_cast<std::shared_ptr<Type>>(typeAny);
    } else if (ctx->expression()) {
        auto exprAny = visit(ctx->expression());
        varType = std::any_cast<std::shared_ptr<Type>>(exprAny);
    } else {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("InternalError", "Variable declaration missing both type and initializer"),
            scopeManager_.getCurrentScopeName()));
    }

    for (auto ident : identList->IDENTIFIER()) {
        std::string varName = ident->getText();
        std::cout << "Debug [visitVarDecl]: Declaring variable " << varName
                  << " with type " << varType->toString() << std::endl;
        scopeManager_.declareVariable(varName, varType);
    }

    if (ctx->expression()) {
        auto initAny = visit(ctx->expression());
        auto initType = std::any_cast<std::shared_ptr<Type>>(initAny);
        if (!isAssignable(varType, initType)) {
            return std::any(propagateErrorWithTransform(
                typeRegistry_.registerErrorType("TypeError"),
                {varType, initType},
                [](std::shared_ptr<Type> err) {
                    return std::make_shared<ErrorType>("TypeError",
                        "Type mismatch in variable initialization");
                }));
        }
    }

    return std::any(varType);
}

std::any TypeChecker::visitEqualityExpr(PrystParser::EqualityExprContext* ctx) {
    std::cout << "Debug [visitEqualityExpr]: Processing equality expression" << std::endl;
    auto leftType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto rightType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));

    if (!typeRegistry_.isEquatable(leftType, rightType)) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {leftType, rightType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Cannot compare incompatible types for equality");
            }));
    }

    return std::any(BOOL_TYPE);
}

std::any TypeChecker::visitWhileStmt(PrystParser::WhileStmtContext* ctx) {
    std::cout << "Debug [visitWhileStmt]: Processing while statement" << std::endl;
    auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    if (!isAssignable(BOOL_TYPE, condType)) {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError", "While condition must be boolean"),
            scopeManager_.getCurrentScopeName()));
    }

    scopeManager_.pushScope();
    isInLoop = true;
    visit(ctx->statement());
    isInLoop = false;
    scopeManager_.popScope();

    return std::any();
}

std::any TypeChecker::visitForStmt(PrystParser::ForStmtContext* ctx) {
    std::cout << "Debug [visitForStmt]: Processing for statement" << std::endl;
    pushScope();

    if (ctx->IN()) {
        std::cout << "Debug [visitForStmt]: Processing for-in loop" << std::endl;
        auto iterableType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
        if (iterableType->getKind() != Type::Kind::Array) {
            return std::any(propagateErrorWithTransform(
                typeRegistry_.registerErrorType("TypeError"),
                {iterableType},
                [](std::shared_ptr<Type> err) {
                    return std::make_shared<ErrorType>("TypeError",
                        "For-in loop requires array type");
                }));
        }

        auto arrayType = std::static_pointer_cast<ArrayType>(iterableType);
        scopeManager_.declareVariable(ctx->IDENTIFIER()->getText(), arrayType->getElementType());

    } else {
        std::cout << "Debug [visitForStmt]: Processing C-style for loop" << std::endl;
        if (ctx->varDecl()) {
            visit(ctx->varDecl());
        } else if (ctx->expressionStmt()) {
            visit(ctx->expressionStmt());
        }

        if (ctx->expression().size() > 0) {
            auto condType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
            if (!isAssignable(BOOL_TYPE, condType)) {
                return std::any(propagateErrorWithTransform(
                    typeRegistry_.registerErrorType("TypeError"),
                    {condType},
                    [](std::shared_ptr<Type> err) {
                        return std::make_shared<ErrorType>("TypeError",
                            "For loop condition must be boolean");
                    }));
            }
        }

        if (ctx->expression().size() > 1) {
            visit(ctx->expression(1));
        }
    }

    auto result = visit(ctx->statement());
    scopeManager_.popScope();
    return result;
}

std::any TypeChecker::visitReturnStmt(PrystParser::ReturnStmtContext* ctx) {
    std::cout << "Debug [visitReturnStmt]: Processing return statement" << std::endl;
    if (ctx->expression()) {
        return visit(ctx->expression());
    }
    return std::any(VOID_TYPE);
}

std::any TypeChecker::visitBreakStmt(PrystParser::BreakStmtContext* ctx) {
    std::cout << "Debug [visitBreakStmt]: Processing break statement" << std::endl;
    return std::any(VOID_TYPE);
}

std::any TypeChecker::visitContinueStmt(PrystParser::ContinueStmtContext* ctx) {
    std::cout << "Debug [visitContinueStmt]: Processing continue statement" << std::endl;
    return std::any(VOID_TYPE);
}

std::any TypeChecker::visitExpressionStmt(PrystParser::ExpressionStmtContext* ctx) {
    std::cout << "Debug [visitExpressionStmt]: Processing expression statement" << std::endl;
    return visit(ctx->expression());
}

std::any TypeChecker::visitArguments(PrystParser::ArgumentsContext* ctx) {
    std::cout << "Debug [visitArguments]: Processing function arguments" << std::endl;
    std::vector<std::shared_ptr<Type>> argTypes;
    if (ctx && ctx->expression().size() > 0) {
        for (auto expr : ctx->expression()) {
            auto argType = std::any_cast<std::shared_ptr<Type>>(visit(expr));
            std::cout << "Debug [visitArguments]: Argument type: " << argType->toString() << std::endl;
            argTypes.push_back(argType);
        }
    }
    return std::any(std::make_shared<std::vector<std::shared_ptr<Type>>>(argTypes));
}

std::any TypeChecker::visitImportDecl(PrystParser::ImportDeclContext* ctx) {
    std::cout << "Debug [visitImportDecl]: Processing import declaration" << std::endl;

    auto importPath = ctx->importPath();
    if (!importPath) {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("ImportError", "Invalid import declaration - missing path"),
            scopeManager_.getCurrentScopeName()));
    }

    std::string currentPath = "";
    std::vector<std::string> identifiers;
    for (auto identifier : importPath->IDENTIFIER()) {
        identifiers.push_back(identifier->getText());
        if (!currentPath.empty()) currentPath += "::";
        currentPath += identifier->getText();
        std::cout << "Debug [visitImportDecl]: Registering parent namespace: " << currentPath << std::endl;
        typeRegistry_.registerNamespace(currentPath);
    }

    std::string fullPath = "";
    for (size_t i = 0; i < identifiers.size(); ++i) {
        if (!fullPath.empty()) fullPath += "::";
        fullPath += identifiers[i];
    }
    std::cout << "Debug [visitImportDecl]: Full import path: " << fullPath << std::endl;
    typeRegistry_.registerNamespace(fullPath);

    if (fullPath == "pryst::runtime::web") {
        std::cout << "Debug [visitImportDecl]: Pre-registering web types" << std::endl;
        runtime::web::registerWebTypes(this->runtimeRegistry_);

        const std::vector<std::string> webTypes = {
            "pryst::runtime::web::Request",
            "pryst::runtime::web::Response",
            "pryst::runtime::web::WebServer"
        };

        for (const auto& typeName : webTypes) {
            if (auto classType = runtimeRegistry_.getClass(typeName)) {
                auto sharedType = std::make_shared<ClassType>(typeName);
                typeRegistry_.cacheType(typeName, sharedType);
                size_t lastSeparator = typeName.rfind("::");
                if (lastSeparator != std::string::npos) {
                    std::string shortName = typeName.substr(lastSeparator + 2);
                    typeRegistry_.cacheType(shortName, sharedType);
                }
            }
        }
    }

    if (ctx->FROM()) {
        std::cout << "Debug [visitImportDecl]: Processing FROM import" << std::endl;
        for (auto identifier : ctx->IDENTIFIER()) {
            std::string importedName = identifier->getText();
            std::string fullTypeName = fullPath + "::" + importedName;
            std::cout << "Debug [visitImportDecl]: Importing " << importedName << " from " << fullPath << std::endl;

            typeRegistry_.registerNamespaceAlias(importedName, fullTypeName);

            if (fullPath == "pryst::runtime::web") {
                if (auto classType = runtimeRegistry_.getClass(fullTypeName)) {
                    std::cout << "Debug [visitImportDecl]: Registering web type: " << fullTypeName << std::endl;
                    auto sharedType = std::make_shared<ClassType>(fullTypeName);
                    typeRegistry_.cacheType(fullTypeName, sharedType);
                    typeRegistry_.cacheType(importedName, sharedType);
                }
            }
        }
    } else if (ctx->AS() && !ctx->IDENTIFIER().empty()) {
        std::string alias = ctx->IDENTIFIER()[0]->getText();
        std::cout << "Debug [visitImportDecl]: Registering alias " << alias << " for " << fullPath << std::endl;
        typeRegistry_.registerNamespaceAlias(alias, fullPath);
    }

    auto result = visitChildren(ctx);
    if (auto error = std::dynamic_pointer_cast<ErrorType>(std::any_cast<std::shared_ptr<Type>>(result))) {
        return std::any(propagateErrorThroughScope(error,
            scopeManager_.getCurrentScopeName()));
    }
    return result;
}

std::any TypeChecker::visitDeclaration(PrystParser::DeclarationContext* ctx) {
    std::cout << "Debug [visitDeclaration]: Processing declaration" << std::endl;
    return visitChildren(ctx);
}

std::any TypeChecker::visitBasicType(PrystParser::BasicTypeContext* ctx) {
    std::cout << "Debug [visitBasicType]: Processing basic type" << std::endl;
    std::shared_ptr<Type> type;

    if (ctx->STR()) type = STRING_TYPE;
    else if (ctx->INT()) type = INT_TYPE;
    else if (ctx->FLOAT()) type = FLOAT_TYPE;
    else if (ctx->BOOL()) type = BOOL_TYPE;
    else if (ctx->VOID()) type = VOID_TYPE;
    else if (ctx->IDENTIFIER()) {
        auto typeName = ctx->IDENTIFIER()->getText();
        type = typeRegistry_.getCachedType(typeName);
        if (!type) {
            std::cout << "Debug [visitBasicType]: Type " << typeName << " not found in cache, creating and registering class type" << std::endl;
            type = std::make_shared<ClassType>(typeName);
            typeRegistry_.cacheType(typeName, type);
            if (!typeRegistry_.hasClass(typeName)) {
                std::cout << "Debug [visitBasicType]: Registering new class " << typeName << " with TypeRegistry" << std::endl;
                typeRegistry_.registerClass(typeName, {});
            }
            std::cout << "Debug [visitBasicType]: Successfully registered class type: " << typeName << std::endl;
        }
    } else {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError", "Unknown basic type"),
            scopeManager_.getCurrentScopeName()));
    }

    std::cout << "Debug [visitBasicType]: Created type: " << type->toString() << std::endl;
    return std::any(type);
}

std::any TypeChecker::visitInterfaceDecl(PrystParser::InterfaceDeclContext* ctx) {
    std::cout << "Debug [visitInterfaceDecl]: Processing interface declaration" << std::endl;
    auto interfaceType = std::make_shared<InterfaceType>(ctx->IDENTIFIER(0)->getText());

    scopeManager_.pushScope();
    scopeManager_.declareVariable(interfaceType->getName(), interfaceType);

    for (const auto& method : ctx->interfaceMember()) {
        scopeManager_.pushScope();
        auto methodType = std::any_cast<std::shared_ptr<Type>>(visit(method));
        scopeManager_.popScope();
        interfaceType->addMethod(method->IDENTIFIER()->getText(), methodType);
    }

    scopeManager_.popScope();
    typeRegistry_.registerInterfaceType(interfaceType);
    return std::any(interfaceType);
}

std::any TypeChecker::visitArrayType(PrystParser::ArrayTypeContext* ctx) {
    std::cout << "Debug [visitArrayType]: Processing array type" << std::endl;
    auto typeAny = visit(ctx->basicType());
    auto elementType = std::any_cast<std::shared_ptr<Type>>(typeAny);
    return std::any(std::make_shared<ArrayType>(elementType));
}

std::any TypeChecker::visitAssignmentExpr(PrystParser::AssignmentExprContext* ctx) {
    std::cout << "Debug [visitAssignmentExpr]: Processing assignment expression" << std::endl;
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));

    if (!isAssignable(left, right)) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {left, right},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Cannot assign incompatible types");
            }));
    }
    return std::any(right);
}

std::any TypeChecker::visitLogicalAndExpr(PrystParser::LogicalAndExprContext* ctx) {
    std::cout << "Debug [visitLogicalAndExpr]: Processing logical AND expression" << std::endl;
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));
    if (left->toString() != "bool" || right->toString() != "bool") {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {left, right},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Logical operators require boolean operands");
            }));
    }
    return std::any(BOOL_TYPE);
}

std::any TypeChecker::visitInstanceofExpr(PrystParser::InstanceofExprContext* ctx) {
    std::cout << "Debug [visitInstanceofExpr]: Processing instanceof expression" << std::endl;

    auto exprType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    auto targetType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->type()));

    std::cout << "Debug [visitInstanceofExpr]: Checking if " << exprType->toString()
              << " is instanceof " << targetType->toString() << std::endl;

    if (exprType->getKind() != Type::Kind::Class && exprType->getKind() != Type::Kind::Nullable) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {exprType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "instanceof can only be used with class types");
            }));
    }

    if (targetType->getKind() != Type::Kind::Class && targetType->getKind() != Type::Kind::Interface) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {targetType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Target type must be a class or interface type");
            }));
    }

    if (exprType->getKind() == Type::Kind::Nullable) {
        auto nullableType = std::static_pointer_cast<NullableType>(exprType);
        exprType = nullableType->getInnerType();
    }

std::any TypeChecker::visitTypeofExpr(PrystParser::TypeofExprContext* ctx) {
    std::cout << "Debug [visitTypeofExpr]: Processing typeof expression" << std::endl;

    auto exprType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    if (exprType->getKind() == Type::Kind::Error) {
        return std::any(propagateErrorThroughScope(
            std::static_pointer_cast<ErrorType>(exprType),
            scopeManager_.getCurrentScopeName()));
    }

    bool isNullable = false;
    std::shared_ptr<Type> innerType = exprType;

    if (exprType->getKind() == Type::Kind::Nullable) {
        auto nullableType = std::static_pointer_cast<NullableType>(exprType);
        innerType = nullableType->getInnerType();
        isNullable = true;
        std::cout << "Debug [visitTypeofExpr]: Nullable type with inner type: "
                  << innerType->toString() << std::endl;
    }

    auto typeInfo = std::make_shared<TypeInfo>(innerType, isNullable);
    std::cout << "Debug [visitTypeofExpr]: Created TypeInfo for type: " << typeInfo->toString() << std::endl;
    return std::any(typeInfo);
}

std::any TypeChecker::visitCastExpr(PrystParser::CastExprContext* ctx) {
    std::cout << "Debug [visitCastExpr]: Processing cast expression" << std::endl;
    auto targetType = getTypeFromTypeContext(ctx->type());
    auto exprType = visit(ctx->expression());
    if (!isAssignable(std::any_cast<std::shared_ptr<Type>>(targetType),
                    std::any_cast<std::shared_ptr<Type>>(exprType))) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {std::any_cast<std::shared_ptr<Type>>(exprType),
             std::any_cast<std::shared_ptr<Type>>(targetType)},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Invalid type cast between incompatible types");
            }));
    }
    return targetType;
}

std::any TypeChecker::visitParenExpr(PrystParser::ParenExprContext* ctx) {
    std::cout << "Debug [visitParenExpr]: Processing parenthesized expression" << std::endl;
    return visit(ctx->expression());
}

std::any TypeChecker::visitPrefixExpr(PrystParser::PrefixExprContext* ctx) {
    std::string op;
    if (ctx->prefix) {
        op = ctx->prefix->getText();
    }

    auto exprAny = visit(ctx->expression());
    auto operand = std::any_cast<std::shared_ptr<Type>>(exprAny);

    if (op == "-" || op == "+") {
        if (operand == INT_TYPE || operand == FLOAT_TYPE) {
            return std::any(operand);
        }
    } else if (op == "!") {
        if (operand == BOOL_TYPE) {
            return std::any(BOOL_TYPE);
        }
    }

    return std::any(propagateErrorWithTransform(
        typeRegistry_.registerErrorType("TypeError"),
        {operand},
        [op](std::shared_ptr<Type> err) {
            return std::make_shared<ErrorType>("TypeError",
                "Invalid operand type for prefix operator " + op);
        }));
}

std::any TypeChecker::visitLogicalOrExpr(PrystParser::LogicalOrExprContext* ctx) {
    std::cout << "Debug [visitLogicalOrExpr]: Processing logical OR expression" << std::endl;
    auto left = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(0)));
    auto right = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression(1)));

    if (left != BOOL_TYPE || right != BOOL_TYPE) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {left, right},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError",
                    "Logical operators require boolean operands");
            }));
    }
    return std::any(BOOL_TYPE);
}

std::any TypeChecker::visitArrayAccessExpr(PrystParser::ArrayAccessExprContext* ctx) {
    std::cout << "Debug [visitArrayAccessExpr]: Processing array access" << std::endl;
    auto array = visit(ctx->expression(0));
    auto index = visit(ctx->expression(1));

    auto arrayType = std::any_cast<std::shared_ptr<Type>>(array);
    auto indexType = std::any_cast<std::shared_ptr<Type>>(index);

    if (arrayType->getKind() == Type::Kind::Array) {
        auto elementType = std::static_pointer_cast<ArrayType>(arrayType)->getElementType();
        if (indexType->getKind() == Type::Kind::Int) {
            return std::any(elementType);
        }
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError", "Array index must be integer"),
            scopeManager_.getCurrentScopeName()));
    }

    return std::any(propagateErrorWithTransform(
        typeRegistry_.registerErrorType("TypeError"),
        {arrayType},
        [](std::shared_ptr<Type> err) {
            return std::make_shared<ErrorType>("TypeError", "Type is not an array");
        }));
}

std::any TypeChecker::visitPrimaryExpr(PrystParser::PrimaryExprContext* ctx) {
    auto result = visit(ctx->primary());
    return result;
}

std::any TypeChecker::visitLambdaExpr(PrystParser::LambdaExprContext* ctx) {
    std::cout << "Debug [visitLambdaExpr]: Processing lambda expression" << std::endl;
    pushScope();
    std::vector<std::shared_ptr<Type>> paramTypes;

    if (ctx->lambdaParams()) {
        auto params = ctx->lambdaParams();
        for (size_t i = 0; i < params->type().size(); i++) {
            auto paramType = getTypeFromTypeContext(params->type(i));
            declareVariable(params->IDENTIFIER(i)->getText(), paramType);
            paramTypes.push_back(std::any_cast<std::shared_ptr<Type>>(paramType));
        }
    }

    std::shared_ptr<Type> returnType = VOID_TYPE;
    if (ctx->returnType()) {
        returnType = std::any_cast<std::shared_ptr<Type>>(getTypeFromReturnTypeContext(ctx->returnType()));
    }

    if (ctx->block()) {
        visit(ctx->block());
    } else if (ctx->expression()) {
        auto exprType = visit(ctx->expression());
        if (!returnType->isVoidType() &&
            !isAssignable(returnType, std::any_cast<std::shared_ptr<Type>>(exprType))) {
            return std::any(propagateErrorWithTransform(
                typeRegistry_.registerErrorType("TypeError"),
                {std::any_cast<std::shared_ptr<Type>>(exprType), returnType},
                [](std::shared_ptr<Type> err) {
                    return std::make_shared<ErrorType>("TypeError",
                        "Lambda return type mismatch");
                }));
        }
        returnType = std::any_cast<std::shared_ptr<Type>>(exprType);
    }

    popScope();

    return std::any(std::make_shared<FunctionType>(returnType, paramTypes));
}

std::any TypeChecker::visitPostfixExpr(PrystParser::PostfixExprContext* ctx) {
    std::cout << "Debug [visitPostfixExpr]: Processing postfix expression" << std::endl;
    auto expr = std::any_cast<std::shared_ptr<Type>>(visit(ctx->expression()));
    return std::any(expr);
}

std::any TypeChecker::visitConstructorExpr(PrystParser::ConstructorExprContext* ctx) {
    auto typeAny = visit(ctx->qualifiedType());
    auto constructorType = std::any_cast<std::shared_ptr<Type>>(typeAny);

    if (auto classType = std::dynamic_pointer_cast<ClassType>(constructorType)) {
        std::vector<std::shared_ptr<Type>> argTypes;
        if (ctx->arguments()) {
            for (auto arg : ctx->arguments()->expression()) {
                auto argAny = visit(arg);
                argTypes.push_back(std::any_cast<std::shared_ptr<Type>>(argAny));
            }
        }

        const auto& constructorParams = typeRegistry_.getConstructorParams(classType->getName());
        if (argTypes.size() != constructorParams.size()) {
            return std::any(propagateErrorWithTransform(
                typeRegistry_.registerErrorType("TypeError"),
                {constructorType},
                [](std::shared_ptr<Type> err) {
                    return std::make_shared<ErrorType>("TypeError",
                        "Constructor called with wrong number of arguments");
                }));
        }

        for (size_t i = 0; i < argTypes.size(); i++) {
            if (!isAssignable(constructorParams[i], argTypes[i])) {
                return std::any(propagateErrorWithTransform(
                    typeRegistry_.registerErrorType("TypeError"),
                    {argTypes[i], constructorParams[i]},
                    [](std::shared_ptr<Type> err) {
                        return std::make_shared<ErrorType>("TypeError",
                            "Constructor argument type mismatch");
                    }));
            }
        }
        return std::any(classType);
    }

    return std::any(propagateErrorWithTransform(
        typeRegistry_.registerErrorType("TypeError"),
        {constructorType},
        [](std::shared_ptr<Type> err) {
            return std::make_shared<ErrorType>("TypeError",
                "Cannot construct non-class type");
        }));
}

std::any TypeChecker::visitNullableType(PrystParser::NullableTypeContext* ctx) {
    std::cout << "Debug [visitNullableType]: Processing nullable type" << std::endl;

    std::any baseTypeAny;
    if (auto qualType = ctx->qualifiedType()) {
        baseTypeAny = visit(qualType);
    } else if (auto funcType = ctx->functionType()) {
        baseTypeAny = visit(funcType);
    } else if (auto arrayType = ctx->arrayType()) {
        baseTypeAny = visit(arrayType);
    } else if (auto mapType = ctx->mapType()) {
        baseTypeAny = visit(mapType);
    } else if (auto basicType = ctx->basicType()) {
        baseTypeAny = visit(basicType);
    } else {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError", "Invalid nullable type"),
            scopeManager_.getCurrentScopeName()));
    }

    auto baseType = std::any_cast<std::shared_ptr<Type>>(baseTypeAny);
    typeRegistry_.registerNullableType(baseType->toString());
    return std::any(std::make_shared<NullableType>(baseType));
}

std::any TypeChecker::visitUnionType(PrystParser::UnionTypeContext* ctx) {
    std::cout << "Debug [visitUnionType]: Processing union type" << std::endl;

    std::vector<std::shared_ptr<Type>> types;

    auto firstType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->type(0)));
    if (auto error = std::dynamic_pointer_cast<ErrorType>(firstType)) {
        return std::any(propagateErrorWithTransform(
            error,
            {},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("UnionTypeError",
                    "Invalid first type in union type declaration: " + err->toString());
            }));
    }
    types.push_back(firstType);

    auto secondType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->type(1)));
    if (auto error = std::dynamic_pointer_cast<ErrorType>(secondType)) {
        return std::any(propagateErrorWithTransform(
            error,
            {firstType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("UnionTypeError",
                    "Invalid second type in union type declaration: " + err->toString());
            }));
    }
    types.push_back(secondType);

    if (!typeRegistry_.areTypesUnionable(firstType, secondType)) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {firstType, secondType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("UnionTypeError",
                    "Cannot create union of incompatible types");
            }));
    }

    auto unionType = std::make_shared<UnionType>(types);
    typeRegistry_.registerUnionType(unionType);

    std::cout << "Debug [visitUnionType]: Created union type: " << unionType->toString() << std::endl;
    return std::any(unionType);
}

std::any TypeChecker::visitIntersectionType(PrystParser::IntersectionTypeContext* ctx) {
    std::cout << "Debug [visitIntersectionType]: Processing intersection type" << std::endl;

    std::vector<std::shared_ptr<Type>> types;

    auto firstType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->type(0)));
    if (auto error = std::dynamic_pointer_cast<ErrorType>(firstType)) {
        return std::any(propagateErrorWithTransform(
            error,
            {},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("IntersectionTypeError",
                    "Invalid first type in intersection type declaration: " + err->toString());
            }));
    }
    types.push_back(firstType);

    auto secondType = std::any_cast<std::shared_ptr<Type>>(visit(ctx->type(1)));
    if (auto error = std::dynamic_pointer_cast<ErrorType>(secondType)) {
        return std::any(propagateErrorWithTransform(
            error,
            {firstType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("IntersectionTypeError",
                    "Invalid second type in intersection type declaration: " + err->toString());
            }));
    }
    types.push_back(secondType);

    if (!typeRegistry_.areTypesIntersectable(firstType, secondType)) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {firstType, secondType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("IntersectionTypeError",
                    "Cannot create intersection of incompatible types");
            }));
    }

    auto intersectionType = std::make_shared<IntersectionType>(types);
    typeRegistry_.registerIntersectionType(intersectionType);

    std::cout << "Debug [visitIntersectionType]: Created intersection type: " << intersectionType->toString() << std::endl;
    return std::any(intersectionType);
}

std::any TypeChecker::visitQualifiedType(PrystParser::QualifiedTypeContext* ctx) {
    std::cout << "Debug [visitQualifiedType]: Processing qualified type" << std::endl;

    std::string typeName;
    for (auto identifier : ctx->IDENTIFIER()) {
        if (!typeName.empty()) typeName += "::";
        typeName += identifier->getText();
    }

    auto type = typeRegistry_.getCachedType(typeName);
    if (!type) {
        return std::any(propagateErrorThroughScope(
            typeRegistry_.registerErrorType("TypeError", "Unknown type: " + typeName),
            scopeManager_.getCurrentScopeName()));
    }

    return std::any(type);
}

std::any TypeChecker::visitParameters(PrystParser::ParametersContext* ctx) {
    std::cout << "Debug [visitParameters]: Processing parameters" << std::endl;
    std::vector<std::shared_ptr<Type>> paramTypes;

    if (ctx && ctx->parameter().size() > 0) {
        for (auto param : ctx->parameter()) {
            auto paramType = std::any_cast<std::shared_ptr<Type>>(visit(param));
            paramTypes.push_back(paramType);
        }
    }

    return std::any(std::make_shared<std::vector<std::shared_ptr<Type>>>(paramTypes));
}

std::any TypeChecker::visitParameter(PrystParser::ParameterContext* ctx) {
    std::cout << "Debug [visitParameter]: Processing parameter" << std::endl;

    auto paramType = getTypeFromTypeContext(ctx->type());

    std::string paramName = ctx->IDENTIFIER()->getText();
    declareVariable(paramName, paramType);

    return paramType;
}

std::any TypeChecker::checkArrayAccess(std::any arrayTypeAny, std::any indexTypeAny) {
    std::cout << "Debug [TypeChecker::checkArrayAccess]: Checking array access" << std::endl;

    auto arrayType = std::any_cast<std::shared_ptr<Type>>(arrayTypeAny);
    auto indexType = std::any_cast<std::shared_ptr<Type>>(indexTypeAny);

    if (!arrayType->isArray()) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {arrayType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError", "Not an array type");
            }));
    }

    if (indexType->toString() != "int") {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {indexType},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError", "Array index must be an integer");
            }));
    }

    return std::any(std::static_pointer_cast<ArrayType>(arrayType)->getElementType());
}

std::any TypeChecker::checkArrayAssignment(std::any targetArrayAny, std::any sourceArrayAny) {
    std::cout << "Debug [TypeChecker::checkArrayAssignment]: Checking array assignment" << std::endl;

    auto targetArray = std::any_cast<std::shared_ptr<Type>>(targetArrayAny);
    auto sourceArray = std::any_cast<std::shared_ptr<Type>>(sourceArrayAny);

    auto targetArrayType = std::dynamic_pointer_cast<ArrayType>(targetArray);
    auto sourceArrayType = std::dynamic_pointer_cast<ArrayType>(sourceArray);

    if (!targetArrayType || !sourceArrayType) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {targetArray, sourceArray},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError", "Both types must be arrays");
            }));
    }

    if (!isAssignable(std::any(targetArrayType->getElementType()),
                      std::any(sourceArrayType->getElementType()))) {
        return std::any(propagateErrorWithTransform(
            typeRegistry_.registerErrorType("TypeError"),
            {targetArrayType->getElementType(), sourceArrayType->getElementType()},
            [](std::shared_ptr<Type> err) {
                return std::make_shared<ErrorType>("TypeError", "Incompatible array types");
            }));
    }

    return targetArrayAny;
}

std::any TypeChecker::checkArrayCreation(std::any elementTypeAny) {
    std::cout << "Debug [TypeChecker::checkArrayCreation]: Creating array type" << std::endl;

    auto elementType = std::any_cast<std::shared_ptr<Type>>(elementTypeAny);
    auto errorType = std::dynamic_pointer_cast<ErrorType>(elementType);
    if (errorType) {
        return elementTypeAny;
    }
    return std::any(std::make_shared<ArrayType>(elementType));
}

} // namespace pryst
