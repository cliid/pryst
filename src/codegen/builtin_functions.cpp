#include "llvm_codegen.hpp"
#include "utils/debug.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/GlobalVariable.h>

namespace pryst {

llvm::Function* LLVMCodegen::declareBoolToStr() {
    PRYST_DEBUG("Declaring bool_to_str function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getInt1Ty(*context)
    };

    // Get char* type for string return
    auto charPtrTy = typeRegistry->getPointerType();

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,
        paramTypes,
        false
    );

    // Create the function
    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "boolToStr",
        module.get()
    );

    // Create basic block
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Create global string constants using LLVM 20.0.0 API
    auto trueStr = builder->CreateGlobalString("true", "true_str");
    auto falseStr = builder->CreateGlobalString("false", "false_str");

    // Get the function parameter
    llvm::Value* boolValue = &*func->arg_begin();

    // Create conditional selection
    llvm::Value* result = builder->CreateSelect(
        boolValue,
        trueStr,
        falseStr,
        "bool_str"
    );

    builder->CreateRet(result);
    return func;
}

llvm::Function* LLVMCodegen::declareIntToStr() {
    PRYST_DEBUG("Declaring int_to_str function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getInt32Ty(*context)
    };

    // Get char* type for string return
    auto charPtrTy = typeRegistry->getPointerType();

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "intToStr",
        module.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Get the function parameter
    llvm::Value* intValue = &*func->arg_begin();

    // Create buffer for string conversion
    auto bufferSize = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 32);
    auto buffer = builder->CreateAlloca(llvm::ArrayType::get(llvm::Type::getInt8Ty(*context), 32));
    auto bufferPtr = builder->CreateBitCast(buffer, charPtrTy);

    // Create format string for integer
    auto formatStr = builder->CreateGlobalString("%d", "int_format");

    // Declare sprintf
    std::vector<llvm::Type*> sprintfTypes = {
        charPtrTy,
        charPtrTy,
        llvm::Type::getInt32Ty(*context)
    };
    llvm::FunctionType* sprintfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        sprintfTypes,
        false
    );
    auto sprintfFunc = module->getOrInsertFunction("sprintf", sprintfType);

    // Call sprintf
    std::vector<llvm::Value*> args = {bufferPtr, formatStr, intValue};
    builder->CreateCall(sprintfFunc, args);

    builder->CreateRet(bufferPtr);
    return func;
}

llvm::Function* LLVMCodegen::declareFloatToStr() {
    PRYST_DEBUG("Declaring float_to_str function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getDoubleTy(*context)
    };

    // Get char* type for string return
    auto charPtrTy = typeRegistry->getPointerType();

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "floatToStr",
        module.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Get the function parameter
    llvm::Value* floatValue = &*func->arg_begin();

    // Create buffer for string conversion
    auto bufferSize = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 32);
    auto buffer = builder->CreateAlloca(llvm::ArrayType::get(llvm::Type::getInt8Ty(*context), 32));
    auto bufferPtr = builder->CreateBitCast(buffer, charPtrTy);

    // Create format string for float with 6 decimal places
    auto formatStr = builder->CreateGlobalString("%.6f", "float_format");

    // Declare sprintf
    std::vector<llvm::Type*> sprintfTypes = {
        charPtrTy,
        charPtrTy,
        llvm::Type::getDoubleTy(*context)
    };
    llvm::FunctionType* sprintfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        sprintfTypes,
        false
    );
    auto sprintfFunc = module->getOrInsertFunction("sprintf", sprintfType);

    // Call sprintf
    std::vector<llvm::Value*> args = {bufferPtr, formatStr, floatValue};
    builder->CreateCall(sprintfFunc, args);

    builder->CreateRet(bufferPtr);
    return func;
}

llvm::Function* LLVMCodegen::declareMathSqrt() {
    PRYST_DEBUG("Declaring math_sqrt function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getDoubleTy(*context)
    };

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "mathSqrt",
        module.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Get function parameter
    llvm::Value* value = &*func->arg_begin();

    // Declare sqrt
    auto sqrtFunc = module->getOrInsertFunction("sqrt",
        llvm::FunctionType::get(
            llvm::Type::getDoubleTy(*context),
            {llvm::Type::getDoubleTy(*context)},
            false
        )
    );

    // Call sqrt and return result
    auto result = builder->CreateCall(sqrtFunc, {value});
    builder->CreateRet(result);

    return func;
}

llvm::Function* LLVMCodegen::declareMathPow() {
    PRYST_DEBUG("Declaring math_pow function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getDoubleTy(*context),  // base
        llvm::Type::getDoubleTy(*context)   // exponent
    };

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "mathPow",
        module.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Get function parameters
    auto it = func->arg_begin();
    llvm::Value* base = &*it++;
    llvm::Value* exponent = &*it;

    // Declare pow
    auto powFunc = module->getOrInsertFunction("pow",
        llvm::FunctionType::get(
            llvm::Type::getDoubleTy(*context),
            {llvm::Type::getDoubleTy(*context),
             llvm::Type::getDoubleTy(*context)},
            false
        )
    );

    // Call pow and return result
    auto result = builder->CreateCall(powFunc, {base, exponent});
    builder->CreateRet(result);

    return func;
}

llvm::Function* LLVMCodegen::declareMathAbs() {
    PRYST_DEBUG("Declaring math_abs function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getDoubleTy(*context)
    };

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context),
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "mathAbs",
        module.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Get function parameter
    llvm::Value* value = &*func->arg_begin();

    // Declare fabs
    auto fabsFunc = module->getOrInsertFunction("fabs",
        llvm::FunctionType::get(
            llvm::Type::getDoubleTy(*context),
            {llvm::Type::getDoubleTy(*context)},
            false
        )
    );

    // Call fabs and return result
    auto result = builder->CreateCall(fabsFunc, {value});
    builder->CreateRet(result);

    return func;
}

llvm::Function* LLVMCodegen::declareStrConcat() {
    PRYST_DEBUG("Declaring str_concat function");

    // Get char* type for string parameters and return
    auto charPtrTy = typeRegistry->getPointerType();

    std::vector<llvm::Type*> paramTypes = {
        charPtrTy,
        charPtrTy
    };

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "strConcat",
        module.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Get function parameters
    auto it = func->arg_begin();
    llvm::Value* str1 = &*it++;
    llvm::Value* str2 = &*it;

    // Declare strlen
    std::vector<llvm::Type*> strlenTypes = {
        charPtrTy
    };
    llvm::FunctionType* strlenType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        strlenTypes,
        false
    );
    auto strlenFunc = module->getOrInsertFunction("strlen", strlenType);

    // Get lengths of both strings
    auto len1 = builder->CreateCall(strlenFunc, {str1});
    auto len2 = builder->CreateCall(strlenFunc, {str2});

    // Calculate total length needed
    auto totalLen = builder->CreateAdd(len1, len2);
    auto bufferSize = builder->CreateAdd(totalLen, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 1));

    // Allocate buffer for result
    auto buffer = builder->CreateAlloca(llvm::Type::getInt8Ty(*context), bufferSize);

    // Declare strcpy and strcat
    auto strcpyFunc = module->getOrInsertFunction("strcpy",
        llvm::FunctionType::get(
            charPtrTy,
            {charPtrTy, charPtrTy},
            false
        )
    );

    auto strcatFunc = module->getOrInsertFunction("strcat",
        llvm::FunctionType::get(
            charPtrTy,
            {charPtrTy, charPtrTy},
            false
        )
    );

    // Copy first string and concatenate second string
    builder->CreateCall(strcpyFunc, {buffer, str1});
    builder->CreateCall(strcatFunc, {buffer, str2});

    builder->CreateRet(buffer);
    return func;
}

llvm::Function* LLVMCodegen::declareStrSubstr() {
    PRYST_DEBUG("Declaring str_substr function");

    // Get char* type for string parameter and return
    auto charPtrTy = typeRegistry->getPointerType();

    std::vector<llvm::Type*> paramTypes = {
        charPtrTy,
        llvm::Type::getInt32Ty(*context),  // start
        llvm::Type::getInt32Ty(*context)   // length
    };

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "strSubstr",
        module.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Get function parameters
    auto it = func->arg_begin();
    llvm::Value* str = &*it++;
    llvm::Value* start = &*it++;
    llvm::Value* length = &*it;

    // Allocate buffer for result
    auto bufferSize = builder->CreateAdd(length, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 1));
    auto buffer = builder->CreateAlloca(llvm::Type::getInt8Ty(*context), bufferSize);

    // Calculate source pointer
    auto sourcePtr = builder->CreateGEP(llvm::Type::getInt8Ty(*context), str, start);

    // Declare strncpy
    auto strncpyFunc = module->getOrInsertFunction("strncpy",
        llvm::FunctionType::get(
            charPtrTy,
            {charPtrTy, charPtrTy, llvm::Type::getInt32Ty(*context)},
            false
        )
    );

    // Copy substring
    builder->CreateCall(strncpyFunc, {buffer, sourcePtr, length});

    // Null terminate the string
    auto nullTerminator = builder->CreateGEP(llvm::Type::getInt8Ty(*context), buffer, length);
    builder->CreateStore(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*context), 0), nullTerminator);

    builder->CreateRet(buffer);
    return func;
}

} // namespace pryst
