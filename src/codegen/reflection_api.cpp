#include "llvm_codegen.hpp"
#include "type_metadata.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

// Implementation of reflection API functions for Pryst

void LLVMCodegen::implementReflectionAPI() {
    // Implement getType function
    std::vector<llvm::Type*> getTypeArgs = {
        llvm::Type::getInt8PtrTy(*context)  // value pointer
    };
    auto* getTypeFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*context), getTypeArgs, false),
        llvm::Function::ExternalLinkage,
        "getType",
        module.get()
    );

    // Create function body
    auto* block = llvm::BasicBlock::Create(*context, "entry", getTypeFunc);
    builder->SetInsertPoint(block);

    // Get type info from value
    auto* value = getTypeFunc->arg_begin();

    // Create basic blocks for type checking
    auto* basicTypeBlock = llvm::BasicBlock::Create(*context, "basic.type", getTypeFunc);
    auto* classTypeBlock = llvm::BasicBlock::Create(*context, "class.type", getTypeFunc);
    auto* functionTypeBlock = llvm::BasicBlock::Create(*context, "function.type", getTypeFunc);
    auto* returnBlock = llvm::BasicBlock::Create(*context, "return", getTypeFunc);

    // Get type info
    auto* typeInfo = typeMetadata->getTypeInfo(value);

    // Switch on type kind
    auto* typeKind = builder->CreateCall(
        module->getFunction("getTypeKind"),
        {value},
        "type.kind"
    );

    auto* switchInst = builder->CreateSwitch(typeKind, basicTypeBlock, 3);
    switchInst->addCase(builder->getInt32(0), basicTypeBlock);    // Basic type
    switchInst->addCase(builder->getInt32(1), classTypeBlock);    // Class type
    switchInst->addCase(builder->getInt32(2), functionTypeBlock); // Function type

    // Handle basic types
    builder->SetInsertPoint(basicTypeBlock);
    auto* basicTypeName = builder->CreateCall(
        module->getFunction("getBasicTypeName"),
        {value},
        "basic.type.name"
    );
    builder->CreateBr(returnBlock);

    // Handle class types
    builder->SetInsertPoint(classTypeBlock);
    auto* classTypeName = builder->CreateCall(
        module->getFunction("getClassTypeName"),
        {value},
        "class.type.name"
    );
    builder->CreateBr(returnBlock);

    // Handle function types
    builder->SetInsertPoint(functionTypeBlock);
    auto* functionTypeName = builder->CreateCall(
        module->getFunction("getFunctionTypeName"),
        {value},
        "function.type.name"
    );
    builder->CreateBr(returnBlock);

    // Return block
    builder->SetInsertPoint(returnBlock);
    auto* phi = builder->CreatePHI(llvm::Type::getInt8PtrTy(*context), 3, "type.name");
    phi->addIncoming(basicTypeName, basicTypeBlock);
    phi->addIncoming(classTypeName, classTypeBlock);
    phi->addIncoming(functionTypeName, functionTypeBlock);
    builder->CreateRet(phi);

    // Implement isInstance function
    std::vector<llvm::Type*> isInstanceArgs = {
        llvm::Type::getInt8PtrTy(*context),  // value pointer
        llvm::Type::getInt8PtrTy(*context)   // type name
    };
    auto* isInstanceFunc = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt1Ty(*context), isInstanceArgs, false),
        llvm::Function::ExternalLinkage,
        "isInstance",
        module.get()
    );

    // Create function body
    block = llvm::BasicBlock::Create(*context, "entry", isInstanceFunc);
    builder->SetInsertPoint(block);

    // Get arguments
    auto args = isInstanceFunc->arg_begin();
    auto* checkValue = args++;
    auto* checkType = args;

    // Get type info
    auto* valueTypeInfo = builder->CreateCall(
        module->getFunction("getTypeInfo"),
        {checkValue},
        "value.type.info"
    );

    // Check if types match (including inheritance)
    auto* result = builder->CreateCall(
        module->getFunction("checkTypeMatch"),
        {valueTypeInfo, checkType},
        "type.match"
    );

    builder->CreateRet(result);

    // Add functions to the module
    functions["getType"] = getTypeFunc;
    functions["isInstance"] = isInstanceFunc;
}

// Helper function to get type name from LLVM value
std::string LLVMCodegen::getTypeName(llvm::Value* value) {
    if (!value) return "void";

    if (auto* typeInfo = typeMetadata->getTypeInfo(value)) {
        return typeInfo->getName();
    }

    // Fallback to LLVM type name if no metadata
    std::string typeName;
    llvm::raw_string_ostream rso(typeName);
    value->getType()->print(rso);
    return typeName;
}
