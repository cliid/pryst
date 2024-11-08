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
    auto llvmStrType = typeRegistry_->getStrType();
    TypeInfoPtr strTypeInfo = typeRegistry_->lookupType("string");
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
    TypeInfoPtr valueTypeInfo = typeMetadata_->getTypeInfo(value);
    TypeInfoPtr intTypeInfo = typeRegistry_->lookupType("int");
    TypeInfoPtr floatTypeInfo = typeRegistry_->lookupType("float");
    TypeInfoPtr boolTypeInfo = typeRegistry_->lookupType("bool");

    if (!valueTypeInfo) {
        builder_->CreateBr(defaultCase);
    } else if (valueTypeInfo->getKind() == intTypeInfo->getKind()) {
        builder_->CreateBr(intCase);
    } else if (valueTypeInfo->getKind() == floatTypeInfo->getKind()) {
        builder_->CreateBr(floatCase);
    } else if (valueTypeInfo->getKind() == boolTypeInfo->getKind()) {
        builder_->CreateBr(boolCase);
    } else {
        builder_->CreateBr(defaultCase);
    }

    // Int case: Convert int to string
    builder_->SetInsertPoint(intCase);
    auto charPtrTy = typeRegistry_->getPointerType();
    auto* intFormat = builder_->CreateGlobalString("%d", "int_format");
    auto* intFormatPtr = builder_->CreateBitCast(intFormat, charPtrTy);
    std::vector<llvm::Value*> intCallArgs;
    intCallArgs.push_back(buffer);
    intCallArgs.push_back(intFormatPtr);
    intCallArgs.push_back(value);
    builder_->CreateCall(sprintfCallee, llvm::ArrayRef<llvm::Value*>(intCallArgs));
    builder_->CreateRet(buffer);

    // Float case: Convert float to string
    builder_->SetInsertPoint(floatCase);
    auto* floatFormat = builder_->CreateGlobalString("%.6f", "float_format");
    auto* floatFormatPtr = builder_->CreateBitCast(floatFormat, charPtrTy);
    std::vector<llvm::Value*> floatCallArgs;
    floatCallArgs.push_back(buffer);
    floatCallArgs.push_back(floatFormatPtr);
    floatCallArgs.push_back(value);
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
    std::vector<llvm::Value*> boolCallArgs;
    boolCallArgs.push_back(buffer);
    boolCallArgs.push_back(boolFormatPtr);
    boolCallArgs.push_back(selectedStrPtr);
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
    auto llvmStrType = typeRegistry_->getStrType();
    TypeInfoPtr strTypeInfo = typeRegistry_->lookupType("string");
    std::vector<llvm::Type*> toIntArgs;
    toIntArgs.push_back(llvmStrType);  // Generic type for any value
    auto* toIntType = llvm::FunctionType::get(
        typeRegistry_->getIntType(), toIntArgs, false);

    // Create the function
    auto* toIntFunc = llvm::Function::Create(
        toIntType,
        llvm::Function::ExternalLinkage,
        "toInt",
        module_.get()
    );

    // Set up basic blocks for different type conversions
    auto* entry = llvm::BasicBlock::Create(*context_, "entry", toIntFunc);
    auto* strCase = llvm::BasicBlock::Create(*context_, "strCase", toIntFunc);
    auto* floatCase = llvm::BasicBlock::Create(*context_, "floatCase", toIntFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context_, "boolCase", toIntFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context_, "defaultCase", toIntFunc);
    auto* endBlock = llvm::BasicBlock::Create(*context_, "endBlock", toIntFunc);

    // Entry block: Check value type
    builder_->SetInsertPoint(entry);
    auto* value = toIntFunc->arg_begin();

    // Convert based on type info from our type system
    TypeInfoPtr valueTypeInfo = typeMetadata_->getTypeInfo(value);
    TypeInfoPtr floatTypeInfo = typeRegistry_->lookupType("float");
    TypeInfoPtr boolTypeInfo = typeRegistry_->lookupType("bool");

    if (!valueTypeInfo) {
        builder_->CreateBr(defaultCase);
    } else if (valueTypeInfo->getKind() == strTypeInfo->getKind()) {
        builder_->CreateBr(strCase);
    } else if (valueTypeInfo->getKind() == floatTypeInfo->getKind()) {
        builder_->CreateBr(floatCase);
    } else if (valueTypeInfo->getKind() == boolTypeInfo->getKind()) {
        builder_->CreateBr(boolCase);
    } else {
        builder_->CreateBr(defaultCase);
    }

    // String case: Convert string to int using atoi
    builder_->SetInsertPoint(strCase);
    std::vector<llvm::Type*> atoiArgs;
    atoiArgs.push_back(llvmStrType);  // str
    auto* atoiType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context_),
        atoiArgs,
        false
    );
    llvm::FunctionCallee atoiCallee = module_->getOrInsertFunction("atoi", atoiType);
    llvm::Value* atoiArgsArray[] = {value};
    auto* intVal = builder_->CreateCall(atoiCallee, llvm::ArrayRef<llvm::Value*>(atoiArgsArray, 1), "int_val");
    builder_->CreateBr(endBlock);  // Branch to end block instead of returning

    // Float case: Convert float to int by truncation
    builder_->SetInsertPoint(floatCase);
    auto* intVal2 = builder_->CreateFPToSI(value, llvm::Type::getInt32Ty(*context_), "int_val");
    builder_->CreateBr(endBlock);  // Branch to end block instead of returning

    // Bool case: Convert bool to int (true = 1, false = 0)
    builder_->SetInsertPoint(boolCase);
    auto* intVal3 = builder_->CreateZExt(value, llvm::Type::getInt32Ty(*context_), "int_val");
    builder_->CreateBr(endBlock);  // Branch to end block instead of returning

    // Default case: Return 0
    builder_->SetInsertPoint(defaultCase);
    builder_->CreateBr(endBlock);  // Branch to end block instead of returning

    // End block: Use PHI node to select the right value
    builder_->SetInsertPoint(endBlock);
    auto* phi = builder_->CreatePHI(typeRegistry_->getIntType(), 4, "result");
    phi->addIncoming(intVal, strCase);
    phi->addIncoming(intVal2, floatCase);
    phi->addIncoming(intVal3, boolCase);
    phi->addIncoming(llvm::ConstantInt::get(typeRegistry_->getIntType(), 0), defaultCase);
    builder_->CreateRet(phi);

    functions_["toInt"] = toIntFunc;
    return toIntFunc;
}

// toFloat operation
llvm::Function* LLVMCodegen::declareToFloat() {
    if (auto* existingFunc = functions_["toFloat"]) return existingFunc;

    // Create function type for toFloat(value: any) -> float
    auto llvmStrType = typeRegistry_->getStrType();
    TypeInfoPtr strTypeInfo = typeRegistry_->lookupType("string");
    std::vector<llvm::Type*> toFloatArgs;
    toFloatArgs.push_back(llvmStrType);  // Generic type for any value
    auto* toFloatType = llvm::FunctionType::get(
        typeRegistry_->getFloatType(),  // Return type (float)
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
    auto* endBlock = llvm::BasicBlock::Create(*context_, "endBlock", toFloatFunc);

    // Entry block: Check value type
    builder_->SetInsertPoint(entry);
    auto* value = toFloatFunc->arg_begin();

    // Convert based on type info from our type system
    TypeInfoPtr valueTypeInfo = typeMetadata_->getTypeInfo(value);
    TypeInfoPtr intTypeInfo = typeRegistry_->lookupType("int");
    TypeInfoPtr boolTypeInfo = typeRegistry_->lookupType("bool");

    if (!valueTypeInfo) {
        builder_->CreateBr(defaultCase);
    } else if (valueTypeInfo->getKind() == strTypeInfo->getKind()) {
        builder_->CreateBr(strCase);
    } else if (valueTypeInfo->getKind() == intTypeInfo->getKind()) {
        builder_->CreateBr(intCase);
    } else if (valueTypeInfo->getKind() == boolTypeInfo->getKind()) {
        builder_->CreateBr(boolCase);
    } else {
        builder_->CreateBr(defaultCase);
    }

    // String case: Convert string to float using atof
    builder_->SetInsertPoint(strCase);
    std::vector<llvm::Type*> atofArgs;
    atofArgs.push_back(llvmStrType);  // str
    auto* atofType = llvm::FunctionType::get(
        typeRegistry_->getFloatType(),
        atofArgs,
        false
    );
    llvm::FunctionCallee atofCallee = module_->getOrInsertFunction("atof", atofType);
    llvm::Value* atofArgsArray[] = {value};
    auto* strFloatVal = builder_->CreateCall(atofCallee, llvm::ArrayRef<llvm::Value*>(atofArgsArray, 1), "float_val");
    builder_->CreateBr(endBlock);

    // Int case: Convert int to float
    builder_->SetInsertPoint(intCase);
    auto* intFloatVal = builder_->CreateSIToFP(value, typeRegistry_->getFloatType(), "float_val");
    builder_->CreateBr(endBlock);

    // Bool case: Convert bool to float (true = 1.0, false = 0.0)
    builder_->SetInsertPoint(boolCase);
    auto* intVal = builder_->CreateZExt(value, llvm::Type::getInt32Ty(*context_), "int_val");
    auto* boolFloatVal = builder_->CreateSIToFP(intVal, typeRegistry_->getFloatType(), "float_val");
    builder_->CreateBr(endBlock);

    // Default case: Return 0.0
    builder_->SetInsertPoint(defaultCase);
    auto* defaultVal = llvm::ConstantFP::get(typeRegistry_->getFloatType(), 0.0);
    builder_->CreateBr(endBlock);

    // End block: Use PHI node to select the right value
    builder_->SetInsertPoint(endBlock);
    auto* phi = builder_->CreatePHI(typeRegistry_->getFloatType(), 4, "result");
    phi->addIncoming(strFloatVal, strCase);
    phi->addIncoming(intFloatVal, intCase);
    phi->addIncoming(boolFloatVal, boolCase);
    phi->addIncoming(defaultVal, defaultCase);
    builder_->CreateRet(phi);

    functions_["toFloat"] = toFloatFunc;
    return toFloatFunc;
}

} // namespace pryst
