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
        llvm::Type::getInt1Ty(*context_)
    };
    auto strType = typeRegistry_->getStrType();
    auto llvmStrType = strType;  // No need for getLLVMType since getStrType returns llvm::Type*
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmStrType,
        paramTypes,
        false
    );

    // Create the function
    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "boolToStr",
        module_.get()
    );

    // Create basic block
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context_, "entry", func);
    builder_->SetInsertPoint(entryBlock);

    // Create global string constants using LLVM 20.0.0 API
    auto trueStr = builder_->CreateGlobalString("true", "true_str");
    auto falseStr = builder_->CreateGlobalString("false", "false_str");

    // Get the function parameter
    llvm::Value* boolValue = &*func->arg_begin();

    // Create conditional selection
    llvm::Value* result = builder_->CreateSelect(
        boolValue,
        trueStr,
        falseStr,
        "bool_str"
    );

    builder_->CreateRet(result);
    return func;
}

llvm::Function* LLVMCodegen::declareIntToStr() {
    PRYST_DEBUG("Declaring int_to_str function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getInt32Ty(*context_)
    };
    auto strType = typeRegistry_->getStrType();
    auto llvmStrType = strType;  // No need for getLLVMType since getStrType returns llvm::Type*
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmStrType,
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "intToStr",
        module_.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context_, "entry", func);
    builder_->SetInsertPoint(entryBlock);

    // Get the function parameter
    llvm::Value* intValue = &*func->arg_begin();

    // Create buffer for string conversion
    auto bufferSize = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context_), 32);
    auto buffer = builder_->CreateAlloca(llvm::ArrayType::get(llvm::Type::getInt8Ty(*context_), 32));
    auto bufferPtr = builder_->CreateBitCast(buffer, typeRegistry_->getPointerType());

    // Create format string for integer
    auto formatStr = builder_->CreateGlobalString("%d", "int_format");

    // Declare sprintf
    std::vector<llvm::Type*> sprintfTypes;
    sprintfTypes.push_back(typeRegistry_->getPointerType());
    sprintfTypes.push_back(typeRegistry_->getPointerType());
    sprintfTypes.push_back(llvm::Type::getInt32Ty(*context_));
    llvm::FunctionType* sprintfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context_),
        sprintfTypes,
        false
    );
    auto sprintfFunc = module_->getOrInsertFunction("sprintf", sprintfType);

    // Call sprintf
    std::vector<llvm::Value*> args{bufferPtr, formatStr, intValue};
    builder_->CreateCall(sprintfFunc, args);

    builder_->CreateRet(bufferPtr);
    return func;
}

llvm::Function* LLVMCodegen::declareFloatToStr() {
    PRYST_DEBUG("Declaring float_to_str function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getDoubleTy(*context_)
    };
    auto strType = typeRegistry_->getStrType();
    auto llvmStrType = strType;  // No need for getLLVMType since getStrType returns llvm::Type*
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmStrType,
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "floatToStr",
        module_.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context_, "entry", func);
    builder_->SetInsertPoint(entryBlock);

    // Get the function parameter
    llvm::Value* floatValue = &*func->arg_begin();

    // Create buffer for string conversion
    auto bufferSize = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context_), 32);
    auto buffer = builder_->CreateAlloca(llvm::ArrayType::get(llvm::Type::getInt8Ty(*context_), 32));
    auto bufferPtr = builder_->CreateBitCast(buffer, typeRegistry_->getPointerType());

    // Create format string for float with 6 decimal places
    auto formatStr = builder_->CreateGlobalString("%.6f", "float_format");

    // Declare sprintf
    std::vector<llvm::Type*> sprintfTypes;
    sprintfTypes.push_back(typeRegistry_->getPointerType());
    sprintfTypes.push_back(typeRegistry_->getPointerType());
    sprintfTypes.push_back(llvm::Type::getDoubleTy(*context_));
    llvm::FunctionType* sprintfType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context_),
        sprintfTypes,
        false
    );
    auto sprintfFunc = module_->getOrInsertFunction("sprintf", sprintfType);

    // Call sprintf
    std::vector<llvm::Value*> args{bufferPtr, formatStr, floatValue};
    builder_->CreateCall(sprintfFunc, args);

    builder_->CreateRet(bufferPtr);
    return func;
}

llvm::Function* LLVMCodegen::declareMathSqrt() {
    PRYST_DEBUG("Declaring math_sqrt function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getDoubleTy(*context_)
    };

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context_),
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "mathSqrt",
        module_.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context_, "entry", func);
    builder_->SetInsertPoint(entryBlock);

    // Get function parameter
    llvm::Value* value = &*func->arg_begin();

    // Declare sqrt
    auto sqrtFunc = module_->getOrInsertFunction("sqrt",
        llvm::FunctionType::get(
            llvm::Type::getDoubleTy(*context_),
            {llvm::Type::getDoubleTy(*context_)},
            false
        )
    );

    // Call sqrt and return result
    auto result = builder_->CreateCall(sqrtFunc, {value});
    builder_->CreateRet(result);

    return func;
}

llvm::Function* LLVMCodegen::declareMathPow() {
    PRYST_DEBUG("Declaring math_pow function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getDoubleTy(*context_),  // base
        llvm::Type::getDoubleTy(*context_)   // exponent
    };

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context_),
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "mathPow",
        module_.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context_, "entry", func);
    builder_->SetInsertPoint(entryBlock);

    // Get function parameters
    auto it = func->arg_begin();
    llvm::Value* base = &*it++;
    llvm::Value* exponent = &*it;

    // Declare pow
    auto powFunc = module_->getOrInsertFunction("pow",
        llvm::FunctionType::get(
            llvm::Type::getDoubleTy(*context_),
            {llvm::Type::getDoubleTy(*context_),
             llvm::Type::getDoubleTy(*context_)},
            false
        )
    );

    // Call pow and return result
    auto result = builder_->CreateCall(powFunc, {base, exponent});
    builder_->CreateRet(result);

    return func;
}

llvm::Function* LLVMCodegen::declareMathAbs() {
    PRYST_DEBUG("Declaring math_abs function");
    std::vector<llvm::Type*> paramTypes = {
        llvm::Type::getDoubleTy(*context_)
    };

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*context_),
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "mathAbs",
        module_.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context_, "entry", func);
    builder_->SetInsertPoint(entryBlock);

    // Get function parameter
    llvm::Value* value = &*func->arg_begin();

    // Declare fabs
    auto fabsFunc = module_->getOrInsertFunction("fabs",
        llvm::FunctionType::get(
            llvm::Type::getDoubleTy(*context_),
            {llvm::Type::getDoubleTy(*context_)},
            false
        )
    );

    // Call fabs and return result
    auto result = builder_->CreateCall(fabsFunc, {value});
    builder_->CreateRet(result);

    return func;
}

llvm::Function* LLVMCodegen::declareStrConcat() {
    PRYST_DEBUG("Declaring str_concat function");
    auto strType = typeRegistry_->getStrType();
    auto llvmStrType = strType;

    std::vector<llvm::Type*> paramTypes;
    paramTypes.push_back(llvmStrType);
    paramTypes.push_back(llvmStrType);

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmStrType,
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "strConcat",
        module_.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context_, "entry", func);
    builder_->SetInsertPoint(entryBlock);

    // Get function parameters
    auto it = func->arg_begin();
    llvm::Value* str1 = &*it++;
    llvm::Value* str2 = &*it;

    // Declare strlen
    std::vector<llvm::Type*> strlenTypes;
    strlenTypes.push_back(typeRegistry_->getPointerType());
    llvm::FunctionType* strlenType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context_),
        strlenTypes,
        false
    );
    auto strlenFunc = module_->getOrInsertFunction("strlen", strlenType);

    // Get lengths of both strings
    auto len1 = builder_->CreateCall(strlenFunc, {str1});
    auto len2 = builder_->CreateCall(strlenFunc, {str2});

    // Calculate total length needed
    auto totalLen = builder_->CreateAdd(len1, len2);
    auto bufferSize = builder_->CreateAdd(totalLen, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context_), 1));

    // Allocate buffer for result
    auto buffer = builder_->CreateAlloca(llvm::Type::getInt8Ty(*context_), bufferSize);

    // Declare strcpy and strcat
    auto strcpyFunc = module_->getOrInsertFunction("strcpy",
        llvm::FunctionType::get(
            typeRegistry_->getPointerType(),
            std::vector<llvm::Type*>{
                typeRegistry_->getPointerType(),
                typeRegistry_->getPointerType()
            },
            false
        )
    );

    auto strcatFunc = module_->getOrInsertFunction("strcat",
        llvm::FunctionType::get(
            typeRegistry_->getPointerType(),
            std::vector<llvm::Type*>{
                typeRegistry_->getPointerType(),
                typeRegistry_->getPointerType()
            },
            false
        )
    );

    // Copy first string and concatenate second string
    builder_->CreateCall(strcpyFunc, {buffer, str1});
    builder_->CreateCall(strcatFunc, {buffer, str2});

    builder_->CreateRet(buffer);
    return func;
}

llvm::Function* LLVMCodegen::declareStrSubstr() {
    PRYST_DEBUG("Declaring str_substr function");
    auto strType = typeRegistry_->getStrType();
    auto llvmStrType = strType;

    std::vector<llvm::Type*> paramTypes;
    paramTypes.push_back(llvmStrType);
    paramTypes.push_back(llvm::Type::getInt32Ty(*context_));  // start
    paramTypes.push_back(llvm::Type::getInt32Ty(*context_));  // length

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmStrType,
        paramTypes,
        false
    );

    llvm::Function* func = llvm::Function::Create(
        funcType,
        llvm::Function::InternalLinkage,
        "strSubstr",
        module_.get()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context_, "entry", func);
    builder_->SetInsertPoint(entryBlock);

    // Get function parameters
    auto it = func->arg_begin();
    llvm::Value* str = &*it++;
    llvm::Value* start = &*it++;
    llvm::Value* length = &*it;

    // Allocate buffer for result
    auto bufferSize = builder_->CreateAdd(length, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context_), 1));
    auto buffer = builder_->CreateAlloca(llvm::Type::getInt8Ty(*context_), bufferSize);

    // Calculate source pointer
    auto sourcePtr = builder_->CreateGEP(llvm::Type::getInt8Ty(*context_), str, start);

    // Declare strncpy
    auto strncpyFunc = module_->getOrInsertFunction("strncpy",
        llvm::FunctionType::get(
            typeRegistry_->getPointerType(),
            std::vector<llvm::Type*>{
                typeRegistry_->getPointerType(),
                typeRegistry_->getPointerType(),
                llvm::Type::getInt32Ty(*context_)
            },
            false
        )
    );

    // Copy substring
    builder_->CreateCall(strncpyFunc, {buffer, sourcePtr, length});

    // Null terminate the string
    auto nullTerminator = builder_->CreateGEP(llvm::Type::getInt8Ty(*context_), buffer, length);
    builder_->CreateStore(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*context_), 0), nullTerminator);

    builder_->CreateRet(buffer);
    return func;
}

} // namespace pryst
