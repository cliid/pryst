#include "llvm_codegen.hpp"
#include "../semantic/type_info.hpp"
#include "../semantic/basic_type_info.hpp"
#include "../semantic/type_kinds.hpp"

namespace pryst {

LLVMCodegen::LLVMCodegen(llvm::LLVMContext& ctx)
    : context(ctx)
    , builder(std::make_unique<llvm::IRBuilder<>>(ctx))
    , typeRegistry(std::make_unique<TypeRegistry>(ctx))
    , typeMetadata(std::make_unique<TypeMetadata>()) {
    initializeModule();
}

void LLVMCodegen::setModule(std::unique_ptr<llvm::Module> mod) {
    module = std::move(mod);
    initializeBuiltins();
}

void LLVMCodegen::initializeModule() {
    // Implementation
}

void LLVMCodegen::initializeBuiltins() {
    // Implementation
}

std::any LLVMCodegen::visitProgram(PrystParser::ProgramContext* ctx) {
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitNamedFunction(PrystParser::NamedFunctionContext* ctx) {
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitBlockStatement(PrystParser::BlockStatementContext* ctx) {
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitReturnStatement(PrystParser::ReturnStatementContext* ctx) {
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitInferredVariableDecl(PrystParser::InferredVariableDeclContext* ctx) {
    auto expr = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    if (!expr) return nullptr;

    auto typeInfo = getTypeInfo(expr);
    if (!typeInfo) return nullptr;

    auto alloca = builder->CreateAlloca(expr->getType(), nullptr, ctx->IDENTIFIER()->getText());
    builder->CreateStore(expr, alloca);
    return alloca;
}

std::any LLVMCodegen::visitTypedVariableDecl(PrystParser::TypedVariableDeclContext* ctx) {
    auto type = getLLVMType(ctx->type()->getText());
    if (!type) return nullptr;

    auto expr = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    if (!expr) return nullptr;

    if (expr->getType() != type && isConvertible(expr, ctx->type()->getText())) {
        expr = convertType(expr, ctx->type()->getText());
    }

    auto alloca = builder->CreateAlloca(type, nullptr, ctx->IDENTIFIER()->getText());
    builder->CreateStore(expr, alloca);
    return alloca;
}

std::any LLVMCodegen::visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext* ctx) {
    auto type = getLLVMType(ctx->type()->getText());
    if (!type) return nullptr;

    auto alloca = builder->CreateAlloca(type, nullptr, ctx->IDENTIFIER()->getText());
    return alloca;
}

std::any LLVMCodegen::visitClassInferredVariableDecl(PrystParser::ClassInferredVariableDeclContext* ctx) {
    auto expr = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    if (!expr) return nullptr;

    auto typeInfo = getTypeInfo(expr);
    if (!typeInfo) return nullptr;

    auto alloca = builder->CreateAlloca(expr->getType(), nullptr, ctx->IDENTIFIER()->getText());
    builder->CreateStore(expr, alloca);
    return alloca;
}

std::any LLVMCodegen::visitClassTypedVariableDecl(PrystParser::ClassTypedVariableDeclContext* ctx) {
    auto type = getLLVMType(ctx->type()->getText());
    if (!type) return nullptr;

    auto expr = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    if (!expr) return nullptr;

    if (expr->getType() != type && isConvertible(expr, ctx->type()->getText())) {
        expr = convertType(expr, ctx->type()->getText());
    }

    auto alloca = builder->CreateAlloca(type, nullptr, ctx->IDENTIFIER()->getText());
    builder->CreateStore(expr, alloca);
    return alloca;
}

std::any LLVMCodegen::visitClassConstInferredDecl(PrystParser::ClassConstInferredDeclContext* ctx) {
    auto expr = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    if (!expr) return nullptr;

    auto typeInfo = getTypeInfo(expr);
    if (!typeInfo) return nullptr;

    auto alloca = builder->CreateAlloca(expr->getType(), nullptr, ctx->IDENTIFIER()->getText());
    builder->CreateStore(expr, alloca);
    return alloca;
}

std::any LLVMCodegen::visitClassConstTypedDecl(PrystParser::ClassConstTypedDeclContext* ctx) {
    auto type = getLLVMType(ctx->type()->getText());
    if (!type) return nullptr;

    auto expr = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    if (!expr) return nullptr;

    if (expr->getType() != type && isConvertible(expr, ctx->type()->getText())) {
        expr = convertType(expr, ctx->type()->getText());
    }

    auto alloca = builder->CreateAlloca(type, nullptr, ctx->IDENTIFIER()->getText());
    builder->CreateStore(expr, alloca);
    return alloca;
}

std::any LLVMCodegen::visitExpression(PrystParser::ExpressionContext* ctx) {
    return visitChildren(ctx);
}

llvm::Type* LLVMCodegen::getLLVMType(const std::string& typeName) {
    if (typeName == "int") {
        return llvm::Type::getInt32Ty(context);
    } else if (typeName == "float") {
        return llvm::Type::getFloatTy(context);
    } else if (typeName == "bool") {
        return llvm::Type::getInt1Ty(context);
    } else if (typeName == "string") {
        return llvm::PointerType::get(context, 0);  // Use opaque pointers in LLVM 20.0.0
    } else if (typeName == "void") {
        return llvm::Type::getVoidTy(context);
    }
    return nullptr;
}

TypeInfoPtr LLVMCodegen::getTypeInfo(llvm::Value* value) {
    if (!value) return nullptr;
    llvm::Type* type = value->getType();

    if (type->isIntegerTy(32)) {
        return std::make_shared<BasicTypeInfo>(BasicTypeInfo::BasicKind::Int, "int", type);
    } else if (type->isFloatTy()) {
        return std::make_shared<BasicTypeInfo>(BasicTypeInfo::BasicKind::Float, "float", type);
    } else if (type->isIntegerTy(1)) {
        return std::make_shared<BasicTypeInfo>(BasicTypeInfo::BasicKind::Bool, "bool", type);
    } else if (type->isPointerTy()) {
        return std::make_shared<BasicTypeInfo>(BasicTypeInfo::BasicKind::String, "string", type);
    }
    return nullptr;
}

bool LLVMCodegen::isConvertible(llvm::Value* from, const std::string& toType) {
    if (!from) return false;
    llvm::Type* fromType = from->getType();
    llvm::Type* targetType = getLLVMType(toType);

    if (!targetType) return false;

    // Allow numeric conversions
    if (isNumericType(fromType) && isNumericType(targetType)) {
        return true;
    }

    // Allow string conversions
    if (isStringType(targetType) || isStringType(fromType)) {
        return true;
    }

    return false;
}

bool LLVMCodegen::isNumericType(llvm::Type* type) {
    return type && (type->isIntegerTy(32) || type->isFloatTy());
}

bool LLVMCodegen::isStringType(llvm::Type* type) {
    return type && type->isPointerTy();
}

} // namespace pryst
