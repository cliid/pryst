// Type conversion operations implementation

#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

namespace pryst {

// toString operation
llvm::Function* LLVMCodegen::declareToString() {
    if (auto* existingFunc = functions_["toString"]) return existingFunc;

    // Create function type for toString(value: any) -> string
    auto strType = typeRegistry_->getStrType();
    auto llvmStrType = typeRegistry_->getLLVMType(strType);
    std::vector<llvm::Type*> toStrArgs;
    toStrArgs.push_back(llvmStrType);  // Generic type for any value

    auto* toStrType = llvm::FunctionType::get(
        llvmStrType,  // Return type (string)
        toStrArgs,
        false
    );

    // Create function
    auto* toStrFunc = llvm::Function::Create(
        toStrType,
        llvm::Function::ExternalLinkage,
        "toString",
        module_.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context_, "entry", toStrFunc);
    auto* intCase = llvm::BasicBlock::Create(*context_, "int_case", toStrFunc);
    auto* floatCase = llvm::BasicBlock::Create(*context_, "float_case", toStrFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context_, "bool_case", toStrFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context_, "default_case", toStrFunc);

    // Entry block: Check value type
    builder_->SetInsertPoint(entry);
    auto* value = toStrFunc->arg_begin();

    // Allocate buffer for result
    auto* buffer = builder_->CreateCall(
        declareMalloc(),
        {llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context_), 64)},  // 64 bytes should be enough
        "buffer"
    );

    // Declare sprintf using our type system
    std::vector<llvm::Type*> sprintfArgs;
    sprintfArgs.push_back(llvmStrType);  // buffer
    sprintfArgs.push_back(llvmStrType);  // format
    sprintfArgs.push_back(llvmStrType);  // value
    auto* sprintfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context_),
        sprintfArgs,
        true  // varargs
    );
    llvm::FunctionCallee sprintfCallee = module_->getOrInsertFunction("sprintf", sprintfType);

    // Convert based on type info from our type system
    auto valueTypeInfo = typeMetadata_->getTypeInfo(value);
    if (!valueTypeInfo) {
        builder_->CreateBr(defaultCase);
    } else if (valueTypeInfo == typeRegistry_->getIntType()) {
        builder_->CreateBr(intCase);
    } else if (valueTypeInfo == typeRegistry_->getFloatType()) {
        builder_->CreateBr(floatCase);
    } else if (valueTypeInfo == typeRegistry_->getBoolType()) {
        builder_->CreateBr(boolCase);
    } else {
        builder_->CreateBr(defaultCase);
    }

    // Int case: Convert int to string
    builder_->SetInsertPoint(intCase);
    auto charPtrTy = typeRegistry_->getOpaquePointerType();
    auto* intFormat = builder_->CreateGlobalString("%d", "int_format");
    auto* intFormatPtr = builder_->CreateBitCast(intFormat, charPtrTy);
    std::vector<llvm::Value*> intCallArgs = {buffer, intFormatPtr, value};
    builder_->CreateCall(sprintfCallee, llvm::ArrayRef<llvm::Value*>(intCallArgs));
    builder_->CreateRet(buffer);

    // Float case: Convert float to string
    builder_->SetInsertPoint(floatCase);
    auto* floatFormat = builder_->CreateGlobalString("%.6f", "float_format");
    auto* floatFormatPtr = builder_->CreateBitCast(floatFormat, charPtrTy);
    std::vector<llvm::Value*> floatCallArgs = {buffer, floatFormatPtr, value};
    builder_->CreateCall(sprintfCallee, llvm::ArrayRef<llvm::Value*>(floatCallArgs));
    builder_->CreateRet(buffer);

    // Bool case: Convert bool to string
    builder_->SetInsertPoint(boolCase);
    auto* trueStr = builder_->CreateGlobalString("true", "true_str");
    auto* falseStr = builder_->CreateGlobalString("false", "false_str");
    auto* boolFormat = builder_->CreateGlobalString("%s", "bool_format");
    auto* boolFormatPtr = builder_->CreateBitCast(boolFormat, charPtrTy);
    auto* selectedStr = builder_->CreateSelect(value, trueStr, falseStr, "bool_str");
    auto* selectedStrPtr = builder_->CreateBitCast(selectedStr, charPtrTy);
    std::vector<llvm::Value*> boolCallArgs = {buffer, boolFormatPtr, selectedStrPtr};
    builder_->CreateCall(sprintfCallee, llvm::ArrayRef<llvm::Value*>(boolCallArgs));
    builder_->CreateRet(buffer);

    // Default case: Return empty string
    builder_->SetInsertPoint(defaultCase);
    auto* emptyStr = builder_->CreateGlobalString("", "empty_str");
    auto* emptyStrPtr = builder_->CreateBitCast(emptyStr, charPtrTy);
    builder_->CreateRet(emptyStrPtr);

    functions_["toString"] = toStrFunc;
    return toStrFunc;
}

// toInt operation
llvm::Function* LLVMCodegen::declareToInt() {
    if (auto* existingFunc = functions_["toInt"]) return existingFunc;

    // Create function type for toInt(value: any) -> int
    auto strType = typeRegistry_->getStrType();
    auto llvmStrType = typeRegistry_->getLLVMType(strType);
    std::vector<llvm::Type*> toIntArgs = {
        llvmStrType  // Generic type for any value
    };
    auto* toIntType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context_),  // Return type (int)
        toIntArgs,
        false
    );

    // Create function
    auto* toIntFunc = llvm::Function::Create(
        toIntType,
        llvm::Function::ExternalLinkage,
        "toInt",
        module_.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context_, "entry", toIntFunc);
    auto* strCase = llvm::BasicBlock::Create(*context_, "str_case", toIntFunc);
    auto* floatCase = llvm::BasicBlock::Create(*context_, "float_case", toIntFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context_, "bool_case", toIntFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context_, "default_case", toIntFunc);

    // Entry block: Check value type
    builder_->SetInsertPoint(entry);
    auto* value = toIntFunc->arg_begin();

    // Convert based on type info from our type system
    auto valueTypeInfo = typeMetadata_->getTypeInfo(value);
    if (!valueTypeInfo) {
        builder_->CreateBr(defaultCase);
    } else if (valueTypeInfo == typeRegistry_->getStrType()) {
        builder_->CreateBr(strCase);
    } else if (valueTypeInfo == typeRegistry_->getFloatType()) {
        builder_->CreateBr(floatCase);
    } else if (valueTypeInfo == typeRegistry_->getBoolType()) {
        builder_->CreateBr(boolCase);
    } else {
        builder_->CreateBr(defaultCase);
    }

    // String case: Convert string to int using atoi
    builder_->SetInsertPoint(strCase);
    std::vector<llvm::Type*> atoiArgs = {
        llvmStrType  // str
    };
    auto* atoiType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context_),
        atoiArgs,
        false
    );
    llvm::FunctionCallee atoiCallee = module_->getOrInsertFunction("atoi", atoiType);
    auto* intVal = builder_->CreateCall(atoiCallee, {value}, "int_val");
    builder_->CreateRet(intVal);

    // Float case: Convert float to int by truncation
    builder_->SetInsertPoint(floatCase);
    auto* intVal2 = builder_->CreateFPToSI(value, llvm::Type::getInt32Ty(*context_), "int_val");
    builder_->CreateRet(intVal2);

    // Bool case: Convert bool to int (true = 1, false = 0)
    builder_->SetInsertPoint(boolCase);
    auto* intVal3 = builder_->CreateZExt(value, llvm::Type::getInt32Ty(*context_), "int_val");
    builder_->CreateRet(intVal3);

    // Default case: Return 0
    builder_->SetInsertPoint(defaultCase);
    builder_->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context_), 0));

    functions_["toInt"] = toIntFunc;
    return toIntFunc;
}

// toFloat operation
llvm::Function* LLVMCodegen::declareToFloat() {
    if (auto* existingFunc = functions_["toFloat"]) return existingFunc;

    // Create function type for toFloat(value: any) -> float
    auto strType = typeRegistry_->getStrType();
    auto llvmStrType = typeRegistry_->getLLVMType(strType);
    std::vector<llvm::Type*> toFloatArgs = {
        llvmStrType  // Generic type for any value
    };
    auto* toFloatType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context_),  // Return type (float)
        toFloatArgs,
        false
    );

    // Create function
    auto* toFloatFunc = llvm::Function::Create(
        toFloatType,
        llvm::Function::ExternalLinkage,
        "toFloat",
        module_.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context_, "entry", toFloatFunc);
    auto* strCase = llvm::BasicBlock::Create(*context_, "str_case", toFloatFunc);
    auto* intCase = llvm::BasicBlock::Create(*context_, "int_case", toFloatFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context_, "bool_case", toFloatFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context_, "default_case", toFloatFunc);

    // Entry block: Check value type
    builder_->SetInsertPoint(entry);
    auto* value = toFloatFunc->arg_begin();

    // Convert based on type info from our type system
    auto valueTypeInfo = typeMetadata_->getTypeInfo(value);
    if (!valueTypeInfo) {
        builder_->CreateBr(defaultCase);
    } else if (valueTypeInfo == typeRegistry_->getStrType()) {
        builder_->CreateBr(strCase);
    } else if (valueTypeInfo == typeRegistry_->getIntType()) {
        builder_->CreateBr(intCase);
    } else if (valueTypeInfo == typeRegistry_->getBoolType()) {
        builder_->CreateBr(boolCase);
    } else {
        builder_->CreateBr(defaultCase);
    }

    // String case: Convert string to float using atof
    builder_->SetInsertPoint(strCase);
    std::vector<llvm::Type*> atofArgs = {
        llvmStrType  // str
    };
    auto* atofType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context_),
        atofArgs,
        false
    );
    llvm::FunctionCallee atofCallee = module_->getOrInsertFunction("atof", atofType);
    auto* floatVal = builder_->CreateCall(atofCallee, {value}, "float_val");
    builder_->CreateRet(floatVal);

    // Int case: Convert int to float
    builder_->SetInsertPoint(intCase);
    auto* floatVal2 = builder_->CreateSIToFP(value, llvm::Type::getDoubleTy(*context_), "float_val");
    builder_->CreateRet(floatVal2);

    // Bool case: Convert bool to float (true = 1.0, false = 0.0)
    builder_->SetInsertPoint(boolCase);
    auto* intVal = builder_->CreateZExt(value, llvm::Type::getInt32Ty(*context_), "int_val");
    auto* floatVal3 = builder_->CreateSIToFP(intVal, llvm::Type::getDoubleTy(*context_), "float_val");
    builder_->CreateRet(floatVal3);

    // Default case: Return 0.0
    builder_->SetInsertPoint(defaultCase);
    builder_->CreateRet(llvm::ConstantFP::get(llvm::Type::getDoubleTy(*context_), 0.0));

    functions_["toFloat"] = toFloatFunc;
    return toFloatFunc;
}
}
