#pragma once

#include "../semantic/type_info.hpp"
#include <llvm/IR/Module.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Metadata.h>
#include <llvm/IR/IRBuilder.h>
#include <memory>
#include <string>

namespace pryst {

class TypeMetadata {
public:
    TypeMetadata(llvm::LLVMContext& context, llvm::Module& module)
        : context_(context), module_(module) {}

    // Add type metadata to a value
    void addTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo);

    // Add function type metadata
    void addFunctionTypeInfo(llvm::Function* function, FunctionTypeInfoPtr typeInfo);

    // Add class type metadata
    void addClassTypeInfo(llvm::StructType* structType, ClassTypeInfoPtr typeInfo);

    // Retrieve type information from metadata
    TypeInfoPtr getTypeInfo(llvm::Value* value);
    FunctionTypeInfoPtr getFunctionTypeInfo(llvm::Function* function);
    ClassTypeInfoPtr getClassTypeInfo(llvm::StructType* structType);

private:
    llvm::LLVMContext& context_;
    llvm::Module& module_;

    // Convert type info to LLVM metadata
    llvm::MDNode* createTypeMetadata(TypeInfoPtr typeInfo);
    llvm::MDNode* createFunctionTypeMetadata(FunctionTypeInfoPtr typeInfo);
    llvm::MDNode* createClassTypeMetadata(ClassTypeInfoPtr typeInfo);

    // Convert LLVM metadata back to type info
    TypeInfoPtr parseTypeMetadata(llvm::MDNode* node);
    FunctionTypeInfoPtr parseFunctionTypeMetadata(llvm::MDNode* node);
    ClassTypeInfoPtr parseClassTypeMetadata(llvm::MDNode* node);

    // Helper methods
    llvm::MDString* getMDString(const std::string& str) {
        return llvm::MDString::get(context_, str);
    }

    std::string getMDStringValue(const llvm::MDString* mdStr) {
        return mdStr ? mdStr->getString().str() : "";
    }

    // Metadata kind IDs
    static constexpr unsigned TYPE_METADATA_KIND = 0;
    static constexpr unsigned FUNCTION_TYPE_METADATA_KIND = 1;
    static constexpr unsigned CLASS_TYPE_METADATA_KIND = 2;
};

} // namespace pryst
