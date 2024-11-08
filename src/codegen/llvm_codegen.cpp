#include "llvm_codegen.hpp"
#include "utils/debug.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <string>

namespace pryst {

void LLVMCodegen::initializeModule() {
    context_ = std::make_unique<llvm::LLVMContext>();
    module_ = std::make_unique<llvm::Module>("pryst_module", *context_);
    builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
    typeRegistry_ = std::make_unique<LLVMTypeRegistry>(*context_);
    typeMetadata_ = std::make_unique<TypeMetadata>(*context_, *module_);
    currentFunction_ = nullptr;
}

std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(PrystParser::ProgramContext* ctx) {
    // Initialize module components
    context_ = std::make_unique<llvm::LLVMContext>();
    module_ = std::make_unique<llvm::Module>("pryst_module", *context_);
    builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
    typeRegistry_ = std::make_unique<LLVMTypeRegistry>(*context_);
    typeMetadata_ = std::make_unique<TypeMetadata>(*context_, *module_);
    declarePrintFunctions();
    visitProgram(ctx);

    // Verify module
    std::string errorInfo;
    llvm::raw_string_ostream errorStream(errorInfo);
    if (llvm::verifyModule(*module_, &errorStream)) {
        PRYST_ERROR("Module verification failed: " + errorInfo);
        return nullptr;
    }
    return std::move(module_);
}

std::any LLVMCodegen::visitProgram(PrystParser::ProgramContext *ctx) {
    PRYST_DEBUG("Visiting program");
    for (auto decl : ctx->declaration()) {
        visitDeclaration(decl);
    }
    return std::any();
}

std::any LLVMCodegen::visitDeclaration(PrystParser::DeclarationContext *ctx) {
    PRYST_DEBUG("Visiting declaration");
    return visitChildren(ctx);
}

std::any LLVMCodegen::visitGlobalUsingDecl(PrystParser::GlobalUsingDeclContext *ctx) {
    PRYST_DEBUG("Visiting global using declaration");
    return std::any();
}

std::any LLVMCodegen::visitBlockScopedNamespaceDecl(PrystParser::BlockScopedNamespaceDeclContext *ctx) {
    PRYST_DEBUG("Visiting block scoped namespace declaration");
    return std::any();
}

std::any LLVMCodegen::visitBlockScopedModuleDecl(PrystParser::BlockScopedModuleDeclContext *ctx) {
    PRYST_DEBUG("Visiting block scoped module declaration");
    return std::any();
}

std::any LLVMCodegen::visitNamespaceDecl(PrystParser::NamespaceDeclContext *ctx) {
    PRYST_DEBUG("Visiting namespace declaration");
    return std::any();
}

std::any LLVMCodegen::visitModuleDecl(PrystParser::ModuleDeclContext *ctx) {
    PRYST_DEBUG("Visiting module declaration");
    return std::any();
}

std::any LLVMCodegen::visitImportDecl(PrystParser::ImportDeclContext *ctx) {
    PRYST_DEBUG("Visiting import declaration");
    return std::any();
}

std::any LLVMCodegen::visitImportPath(PrystParser::ImportPathContext *ctx) {
    PRYST_DEBUG("Visiting import path");
    return std::any();
}

// String handling
std::any LLVMCodegen::visitSimpleString(PrystParser::SimpleStringContext *ctx) {
    PRYST_DEBUG("Visiting simple string");
    auto str = ctx->STRING()->getText();
    // Remove quotes from string literal
    str = str.substr(1, str.length() - 2);
    // Create a global string and get its pointer using GEP
    auto global = builder_->CreateGlobalString(str);
    auto zero = llvm::ConstantInt::get(*context_, llvm::APInt(32, 0));
    return builder_->CreateGEP(global->getValueType(), global, {zero, zero});
}

// Class member declarations
std::any LLVMCodegen::visitClassTypedVariableDecl(PrystParser::ClassTypedVariableDeclContext *ctx) {
    PRYST_DEBUG("Visiting class typed variable declaration");
    auto type = typeRegistry_->getType(ctx->type());
    auto name = ctx->IDENTIFIER()->getText();
    auto value = ctx->expression() ? std::any_cast<llvm::Value*>(visit(ctx->expression())) : nullptr;

    // Create class member variable
    auto alloca = createEntryBlockAlloca(currentFunction_, name, type);
    if (value) {
        builder_->CreateStore(value, alloca);
    }
    namedValues_[name] = alloca;
    return std::any();
}

std::any LLVMCodegen::visitClassConstTypedDecl(PrystParser::ClassConstTypedDeclContext *ctx) {
    PRYST_DEBUG("Visiting class const typed declaration");
    auto type = typeRegistry_->getType(ctx->type());
    auto name = ctx->IDENTIFIER()->getText();
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));

    // Create constant class member
    auto global = new llvm::GlobalVariable(
        *module_, type, true, llvm::GlobalValue::InternalLinkage,
        llvm::Constant::getNullValue(type), name
    );
    builder_->CreateStore(value, global);
    namedValues_[name] = global;
    return std::any();
}

std::any LLVMCodegen::visitClassInferredVariableDecl(PrystParser::ClassInferredVariableDeclContext *ctx) {
    PRYST_DEBUG("Visiting class inferred variable declaration");
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto type = value->getType();
    auto name = ctx->IDENTIFIER()->getText();

    // Create class member with inferred type
    auto alloca = createEntryBlockAlloca(currentFunction_, name, type);
    builder_->CreateStore(value, alloca);
    namedValues_[name] = alloca;
    return std::any();
}

std::any LLVMCodegen::visitClassConstInferredDecl(PrystParser::ClassConstInferredDeclContext *ctx) {
    PRYST_DEBUG("Visiting class const inferred declaration");
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto type = value->getType();
    auto name = ctx->IDENTIFIER()->getText();

    // Create constant class member with inferred type
    auto global = new llvm::GlobalVariable(
        *module_, type, true, llvm::GlobalValue::InternalLinkage,
        llvm::Constant::getNullValue(type), name
    );
    builder_->CreateStore(value, global);
    namedValues_[name] = global;
    return std::any();
}

// Type conversions
std::any LLVMCodegen::visitTypeCastExpr(PrystParser::TypeCastExprContext *ctx) {
    PRYST_DEBUG("Visiting type cast expression");
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto targetType = typeRegistry_->getType(ctx->type());
    return typeRegistry_->convertType(value, targetType, builder_.get());
}

std::any LLVMCodegen::visitTypeConversionExpr(PrystParser::TypeConversionExprContext *ctx) {
    PRYST_DEBUG("Visiting type conversion expression");
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto targetType = typeRegistry_->getType(ctx->type());
    return typeRegistry_->convertType(value, targetType, builder_.get());
}

std::any LLVMCodegen::visitClassConversionExpr(PrystParser::ClassConversionExprContext *ctx) {
    PRYST_DEBUG("Visiting class conversion expression");
    auto value = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    auto targetClassName = ctx->IDENTIFIER()->getText();
    auto targetType = typeRegistry_->getClassType(targetClassName);
    return typeRegistry_->convertClassType(value, targetType, builder_.get());
}

llvm::AllocaInst* LLVMCodegen::createEntryBlockAlloca(llvm::Function* function,
    const std::string& varName, llvm::Type* type) {
    llvm::IRBuilder<> tmpBuilder(&function->getEntryBlock(),
        function->getEntryBlock().begin());
    return tmpBuilder.CreateAlloca(type, nullptr, varName);
}

void LLVMCodegen::declarePrintFunctions() {
    // Print function declarations will be implemented in subsequent updates
}

llvm::Value* LLVMCodegen::generateGetType(llvm::Value* value) {
    if (!value) return nullptr;
    auto typeInfo = typeMetadata_->getTypeInfo(value);
    if (!typeInfo) return nullptr;
    auto global = builder_->CreateGlobalString(typeInfo->getName());
    auto zero = llvm::ConstantInt::get(*context_, llvm::APInt(32, 0));
    return builder_->CreateGEP(global->getValueType(), global, {zero, zero});
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    if (!value) return nullptr;
    auto typeInfo = typeMetadata_->getTypeInfo(value);
    if (!typeInfo) return nullptr;
    bool isInstance = (typeInfo->getName() == typeName);
    if (!isInstance && typeInfo->isClass()) {
        auto classType = std::dynamic_pointer_cast<ClassTypeInfo>(typeInfo);
        while (classType->getParent()) {
            classType = std::dynamic_pointer_cast<ClassTypeInfo>(classType->getParent());
            if (classType->getName() == typeName) {
                isInstance = true;
                break;
            }
        }
    }
    return llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context_), isInstance);
}

TypeInfoPtr LLVMCodegen::getTypeInfo(llvm::Value* value) const {
    return typeMetadata_->getTypeInfo(value);
}

void LLVMCodegen::attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) {
    typeMetadata_->addTypeInfo(value, typeInfo);
}

} // namespace pryst
