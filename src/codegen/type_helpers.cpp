#include "llvm_codegen.hpp"
#include "type_metadata.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

// Helper functions for type reflection

void LLVMCodegen::implementTypeHelpers() {
    // Implement getTypeKind function
    std::vector<llvm::Type*> getTypeKindArgs = {
        llvm::Type::getInt8PtrTy(*context)  // value pointer
    };
    auto* getTypeKindFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), getTypeKindArgs, false),
        llvm::Function::ExternalLinkage,
        "getTypeKind",
        module.get()
    );

    auto* block = llvm::BasicBlock::Create(*context, "entry", getTypeKindFunc);
    builder->SetInsertPoint(block);

    auto* value = getTypeKindFunc->arg_begin();
    auto* typeInfo = typeMetadata->getTypeInfo(value);
    auto* kind = builder->CreateCall(
        module->getFunction("getTypeInfoKind"),
        {typeInfo},
        "type.kind"
    );
    builder->CreateRet(kind);

    // Implement getBasicTypeName function
    std::vector<llvm::Type*> getTypeNameArgs = {
        llvm::Type::getInt8PtrTy(*context)  // value pointer
    };
    auto* getBasicTypeNameFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*context), getTypeNameArgs, false),
        llvm::Function::ExternalLinkage,
        "getBasicTypeName",
        module.get()
    );

    block = llvm::BasicBlock::Create(*context, "entry", getBasicTypeNameFunc);
    builder->SetInsertPoint(block);

    value = getBasicTypeNameFunc->arg_begin();
    typeInfo = typeMetadata->getTypeInfo(value);
    auto* basicTypeName = builder->CreateGlobalStringPtr(typeInfo->getName(), "basic.type.name");
    builder->CreateRet(basicTypeName);

    // Implement getClassTypeName function
    auto* getClassTypeNameFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*context), getTypeNameArgs, false),
        llvm::Function::ExternalLinkage,
        "getClassTypeName",
        module.get()
    );

    block = llvm::BasicBlock::Create(*context, "entry", getClassTypeNameFunc);
    builder->SetInsertPoint(block);

    value = getClassTypeNameFunc->arg_begin();
    auto* classTypeInfo = typeMetadata->getClassTypeInfo(
        llvm::dyn_cast<llvm::StructType>(value->getType())
    );
    auto* classTypeName = builder->CreateGlobalStringPtr(
        classTypeInfo ? classTypeInfo->getName() : "unknown",
        "class.type.name"
    );
    builder->CreateRet(classTypeName);

    // Implement getFunctionTypeName function
    auto* getFunctionTypeNameFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*context), getTypeNameArgs, false),
        llvm::Function::ExternalLinkage,
        "getFunctionTypeName",
        module.get()
    );

    block = llvm::BasicBlock::Create(*context, "entry", getFunctionTypeNameFunc);
    builder->SetInsertPoint(block);

    value = getFunctionTypeNameFunc->arg_begin();
    auto* functionTypeInfo = typeMetadata->getFunctionTypeInfo(
        llvm::dyn_cast<llvm::Function>(value)
    );
    auto* functionTypeName = builder->CreateGlobalStringPtr(
        functionTypeInfo ? "function" : "unknown",
        "function.type.name"
    );
    builder->CreateRet(functionTypeName);

    // Implement getTypeInfo function
    auto* getTypeInfoFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*context), getTypeNameArgs, false),
        llvm::Function::ExternalLinkage,
        "getTypeInfo",
        module.get()
    );

    block = llvm::BasicBlock::Create(*context, "entry", getTypeInfoFunc);
    builder->SetInsertPoint(block);

    value = getTypeInfoFunc->arg_begin();
    typeInfo = typeMetadata->getTypeInfo(value);
    auto* typeInfoPtr = builder->CreateGlobalStringPtr(
        typeInfo ? typeInfo->getName() : "unknown",
        "type.info"
    );
    builder->CreateRet(typeInfoPtr);

    // Implement checkTypeMatch function
    std::vector<llvm::Type*> checkTypeMatchArgs = {
        llvm::Type::getInt8PtrTy(*context),  // type info pointer
        llvm::Type::getInt8PtrTy(*context)   // type name to check
    };
    auto* checkTypeMatchFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt1Ty(*context), checkTypeMatchArgs, false),
        llvm::Function::ExternalLinkage,
        "checkTypeMatch",
        module.get()
    );

    block = llvm::BasicBlock::Create(*context, "entry", checkTypeMatchFunc);
    builder->SetInsertPoint(block);

    auto args = checkTypeMatchFunc->arg_begin();
    auto* typeInfoPtr = args++;
    auto* checkType = args;

    // Direct type comparison
    auto* matches = builder->CreateICmpEQ(typeInfoPtr, checkType);

    // For class types, check inheritance chain
    auto* isClass = builder->CreateCall(
        module->getFunction("isClassType"),
        {typeInfoPtr},
        "is.class"
    );

    auto* checkInheritanceBlock = llvm::BasicBlock::Create(*context, "check.inheritance", checkTypeMatchFunc);
    auto* returnBlock = llvm::BasicBlock::Create(*context, "return", checkTypeMatchFunc);

    builder->CreateCondBr(isClass, checkInheritanceBlock, returnBlock);

    builder->SetInsertPoint(checkInheritanceBlock);
    auto* inheritanceMatch = builder->CreateCall(
        module->getFunction("checkInheritanceChain"),
        {typeInfoPtr, checkType},
        "inheritance.match"
    );
    auto* finalMatch = builder->CreateOr(matches, inheritanceMatch);
    builder->CreateBr(returnBlock);

    builder->SetInsertPoint(returnBlock);
    auto* phi = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "result");
    phi->addIncoming(matches, block);
    phi->addIncoming(finalMatch, checkInheritanceBlock);
    builder->CreateRet(phi);

    // Add functions to the module
    functions["getTypeKind"] = getTypeKindFunc;
    functions["getBasicTypeName"] = getBasicTypeNameFunc;
    functions["getClassTypeName"] = getClassTypeNameFunc;
    functions["getFunctionTypeName"] = getFunctionTypeNameFunc;
    functions["getTypeInfo"] = getTypeInfoFunc;
    functions["checkTypeMatch"] = checkTypeMatchFunc;
}
