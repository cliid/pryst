// Type conversion operations implementation

#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

// toString operation
llvm::Function* LLVMCodegen::declareToString() {
    if (auto* existingFunc = functions["toString"]) return existingFunc;

    // Create function type for toString(value: any) -> str
    auto int8Ty = llvm::Type::getInt8Ty(*context);
    auto int8PtrTy = llvm::PointerType::getUnqual(int8Ty);
    std::vector<llvm::Type*> toStrArgs = {
        int8PtrTy  // Generic pointer type for any value
    };
    auto* toStrType = llvm::FunctionType::get(
        int8PtrTy,  // Return type (string)
        toStrArgs,
        false
    );

    // Create function
    auto* toStrFunc = llvm::Function::Create(
        toStrType,
        llvm::Function::ExternalLinkage,
        "toString",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", toStrFunc);
    auto* intCase = llvm::BasicBlock::Create(*context, "int_case", toStrFunc);
    auto* floatCase = llvm::BasicBlock::Create(*context, "float_case", toStrFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context, "bool_case", toStrFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context, "default_case", toStrFunc);

    // Entry block: Check value type
    builder->SetInsertPoint(entry);
    auto* value = toStrFunc->arg_begin();

    // Allocate buffer for result
    auto* buffer = builder->CreateCall(
        declareMalloc(),
        {llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 64)},  // 64 bytes should be enough
        "buffer"
    );

    // Declare sprintf
    std::vector<llvm::Type*> sprintfArgs = {
        int8PtrTy,  // buffer
        int8PtrTy,  // format
        int8PtrTy   // value
    };
    auto* sprintfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        sprintfArgs,
        true  // varargs
    );
    llvm::FunctionCallee sprintfCallee = module->getOrInsertFunction("sprintf", sprintfType);

    // Convert based on type
    auto* valueType = value->getType();
    if (valueType == llvm::Type::getInt32Ty(*context)) {
        builder->CreateBr(intCase);
    } else if (valueType == llvm::Type::getDoubleTy(*context)) {
        builder->CreateBr(floatCase);
    } else if (valueType == llvm::Type::getInt1Ty(*context)) {
        builder->CreateBr(boolCase);
    } else {
        builder->CreateBr(defaultCase);
    }

    // Int case: Convert int to string
    builder->SetInsertPoint(intCase);
    // Create global string with explicit type for LLVM 20.0.0
    auto* intFormat = builder->CreateGlobalString("%d", "int_format");
    builder->CreateCall(sprintfCallee, {buffer, intFormat, value});
    builder->CreateRet(buffer);

    // Float case: Convert float to string
    builder->SetInsertPoint(floatCase);
    // Create global string with explicit type for LLVM 20.0.0
    auto* floatFormat = builder->CreateGlobalString("%.6f", "float_format");
    builder->CreateCall(sprintfCallee, {buffer, floatFormat, value});
    builder->CreateRet(buffer);

    // Bool case: Convert bool to string
    builder->SetInsertPoint(boolCase);
    // Create global strings with explicit type for LLVM 20.0.0
    auto* trueStr = builder->CreateGlobalString("true", "true_str");
    auto* falseStr = builder->CreateGlobalString("false", "false_str");
    auto* boolStr = builder->CreateSelect(value, trueStr, falseStr, "bool_str");
    builder->CreateRet(boolStr);

    // Default case: Return empty string
    builder->SetInsertPoint(defaultCase);
    auto* emptyStr = builder->CreateGlobalString("", "empty_str");
    builder->CreateRet(emptyStr);

    functions["toString"] = toStrFunc;
    return toStrFunc;
}

// toInt operation
llvm::Function* LLVMCodegen::declareToInt() {
    if (auto* existingFunc = functions["toInt"]) return existingFunc;

    // Create function type for toInt(value: any) -> int
    auto int8Ty = llvm::Type::getInt8Ty(*context);
    auto int8PtrTy = llvm::PointerType::getUnqual(int8Ty);
    std::vector<llvm::Type*> toIntArgs = {
        int8PtrTy  // Generic pointer type for any value
    };
    auto* toIntType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),  // Return type (int)
        toIntArgs,
        false
    );

    // Create function
    auto* toIntFunc = llvm::Function::Create(
        toIntType,
        llvm::Function::ExternalLinkage,
        "toInt",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", toIntFunc);
    auto* strCase = llvm::BasicBlock::Create(*context, "str_case", toIntFunc);
    auto* floatCase = llvm::BasicBlock::Create(*context, "float_case", toIntFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context, "bool_case", toIntFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context, "default_case", toIntFunc);

    // Entry block: Check value type
    builder->SetInsertPoint(entry);
    auto* value = toIntFunc->arg_begin();

    // Convert based on type
    auto* valueType = value->getType();
    if (valueType == int8PtrTy) {
        builder->CreateBr(strCase);
    } else if (valueType == llvm::Type::getDoubleTy(*context)) {
        builder->CreateBr(floatCase);
    } else if (valueType == llvm::Type::getInt1Ty(*context)) {
        builder->CreateBr(boolCase);
    } else {
        builder->CreateBr(defaultCase);
    }

    // String case: Convert string to int using atoi
    builder->SetInsertPoint(strCase);
    std::vector<llvm::Type*> atoiArgs = {
        int8PtrTy  // str
    };
    auto* atoiType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        atoiArgs,
        false
    );
    llvm::FunctionCallee atoiCallee = module->getOrInsertFunction("atoi", atoiType);
    auto* intVal = builder->CreateCall(atoiCallee, {value}, "int_val");
    builder->CreateRet(intVal);

    // Float case: Convert float to int by truncation
    builder->SetInsertPoint(floatCase);
    auto* intVal2 = builder->CreateFPToSI(value, llvm::Type::getInt32Ty(*context), "int_val");
    builder->CreateRet(intVal2);

    // Bool case: Convert bool to int (true = 1, false = 0)
    builder->SetInsertPoint(boolCase);
    auto* intVal3 = builder->CreateZExt(value, llvm::Type::getInt32Ty(*context), "int_val");
    builder->CreateRet(intVal3);

    // Default case: Return 0
    builder->SetInsertPoint(defaultCase);
    builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0));

    functions["toInt"] = toIntFunc;
    return toIntFunc;
}

// toFloat operation
llvm::Function* LLVMCodegen::declareToFloat() {
    if (auto* existingFunc = functions["toFloat"]) return existingFunc;

    // Create function type for toFloat(value: any) -> float
    auto int8Ty = llvm::Type::getInt8Ty(*context);
    auto int8PtrTy = llvm::PointerType::getUnqual(int8Ty);
    std::vector<llvm::Type*> toFloatArgs = {
        int8PtrTy  // Generic pointer type for any value
    };
    auto* toFloatType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),  // Return type (float)
        toFloatArgs,
        false
    );

    // Create function
    auto* toFloatFunc = llvm::Function::Create(
        toFloatType,
        llvm::Function::ExternalLinkage,
        "toFloat",
        module.get()
    );

    // Create blocks
    auto* entry = llvm::BasicBlock::Create(*context, "entry", toFloatFunc);
    auto* strCase = llvm::BasicBlock::Create(*context, "str_case", toFloatFunc);
    auto* intCase = llvm::BasicBlock::Create(*context, "int_case", toFloatFunc);
    auto* boolCase = llvm::BasicBlock::Create(*context, "bool_case", toFloatFunc);
    auto* defaultCase = llvm::BasicBlock::Create(*context, "default_case", toFloatFunc);

    // Entry block: Check value type
    builder->SetInsertPoint(entry);
    auto* value = toFloatFunc->arg_begin();

    // Convert based on type
    auto* valueType = value->getType();
    if (valueType == int8PtrTy) {
        builder->CreateBr(strCase);
    } else if (valueType == llvm::Type::getInt32Ty(*context)) {
        builder->CreateBr(intCase);
    } else if (valueType == llvm::Type::getInt1Ty(*context)) {
        builder->CreateBr(boolCase);
    } else {
        builder->CreateBr(defaultCase);
    }

    // String case: Convert string to float using atof
    builder->SetInsertPoint(strCase);
    std::vector<llvm::Type*> atofArgs = {
        int8PtrTy  // str
    };
    auto* atofType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),
        atofArgs,
        false
    );
    llvm::FunctionCallee atofCallee = module->getOrInsertFunction("atof", atofType);
    auto* floatVal = builder->CreateCall(atofCallee, {value}, "float_val");
    builder->CreateRet(floatVal);

    // Int case: Convert int to float
    builder->SetInsertPoint(intCase);
    auto* floatVal2 = builder->CreateSIToFP(value, llvm::Type::getDoubleTy(*context), "float_val");
    builder->CreateRet(floatVal2);


    // Bool case: Convert bool to float (true = 1.0, false = 0.0)
    builder->SetInsertPoint(boolCase);
    auto* intVal = builder->CreateZExt(value, llvm::Type::getInt32Ty(*context), "int_val");
    auto* floatVal3 = builder->CreateSIToFP(intVal, llvm::Type::getDoubleTy(*context), "float_val");
    builder->CreateRet(floatVal3);

    // Default case: Return 0.0
    builder->SetInsertPoint(defaultCase);
    builder->CreateRet(llvm::ConstantFP::get(llvm::Type::getDoubleTy(*context), 0.0));

    functions["toFloat"] = toFloatFunc;
    return toFloatFunc;
}
