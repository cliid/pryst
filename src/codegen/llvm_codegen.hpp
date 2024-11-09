#pragma once

#include <memory>
#include <string>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include "../generated/PrystParser.h"
#include "../generated/PrystParserBaseVisitor.h"
#include "type_registry.hpp"
#include "type_metadata.hpp"

namespace pryst {

class ClassTypeInfo;  // Forward declaration

class LLVMCodegen : public PrystParserBaseVisitor {
public:
    explicit LLVMCodegen(llvm::LLVMContext& ctx);
    ~LLVMCodegen() = default;

    // Module and context management
    void setModule(std::unique_ptr<llvm::Module> mod);
    llvm::Module* getModule() const { return module.get(); }
    llvm::LLVMContext& getContext() const { return context; }

    // Accessor methods for private members
    TypeRegistry* getTypeRegistry() const { return typeRegistry.get(); }
    llvm::IRBuilder<>* getBuilder() const { return builder.get(); }
    TypeMetadata* getTypeMetadata() const { return typeMetadata.get(); }
    llvm::Function* getCurrentFunction() const { return currentFunction; }
    llvm::BasicBlock* getCurrentBlock() const { return currentBlock; }

    // Builtin function declarations
    llvm::Function* declareBoolToStr();
    llvm::Function* declareIntToStr();
    llvm::Function* declareFloatToStr();
    llvm::Function* declareStrToBool();
    llvm::Function* declareStrToInt();
    llvm::Function* declareStrToFloat();
    llvm::Function* declareToString();

    // Type conversion methods
    llvm::Value* convertType(llvm::Value* value, const std::string& targetType);
    llvm::Type* getLLVMType(const std::string& typeName);
    TypeInfoPtr getTypeInfo(llvm::Value* value);
    bool isConvertible(llvm::Value* from, const std::string& toType);
    ClassTypeInfo* getClassInfo(const std::string& className);
    llvm::Value* convertToString(llvm::Value* value);
    llvm::Value* convertFromString(llvm::Value* value, llvm::Type* targetType);

    // Type helper methods
    bool isNumericType(llvm::Type* type);
    bool isStringType(llvm::Type* type);

    // Reflection API methods
    llvm::Value* generateTypeOf(llvm::Value* value);
    llvm::Value* generateIsInstance(llvm::Value* value, const std::string& typeName);
    llvm::Value* generateGetTypeInfo(const std::string& typeName);

    // ANTLR visitor overrides
    virtual std::any visitProgram(PrystParser::ProgramContext *ctx) override;
    virtual std::any visitNamedFunction(PrystParser::NamedFunctionContext *ctx) override;
    virtual std::any visitBlockStatement(PrystParser::BlockStatementContext *ctx) override;
    virtual std::any visitReturnStatement(PrystParser::ReturnStatementContext *ctx) override;
    virtual std::any visitInferredVariableDecl(PrystParser::InferredVariableDeclContext *ctx) override;
    virtual std::any visitTypedVariableDecl(PrystParser::TypedVariableDeclContext *ctx) override;
    virtual std::any visitUninitializedVariableDecl(PrystParser::UninitializedVariableDeclContext *ctx) override;
    virtual std::any visitClassInferredVariableDecl(PrystParser::ClassInferredVariableDeclContext *ctx) override;
    virtual std::any visitClassTypedVariableDecl(PrystParser::ClassTypedVariableDeclContext *ctx) override;
    virtual std::any visitClassConstInferredDecl(PrystParser::ClassConstInferredDeclContext *ctx) override;
    virtual std::any visitClassConstTypedDecl(PrystParser::ClassConstTypedDeclContext *ctx) override;
    virtual std::any visitExpression(PrystParser::ExpressionContext *ctx) override;
    virtual std::any visitTypeConversionExpr(PrystParser::TypeConversionExprContext *ctx) override;
    virtual std::any visitTypeCastExpr(PrystParser::TypeCastExprContext *ctx) override;
    virtual std::any visitClassConversionExpr(PrystParser::ClassConversionExprContext *ctx) override;

private:
    llvm::LLVMContext& context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<TypeRegistry> typeRegistry;
    std::unique_ptr<TypeMetadata> typeMetadata;
    llvm::Function* currentFunction;
    llvm::BasicBlock* currentBlock;
    llvm::Value* lastValue;

    void initializeModule();
    void initializeBuiltins();
};

} // namespace pryst
