#include "string_impl.hpp"
#include <stdexcept>
#include <algorithm>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Verifier.h"

namespace pryst {
namespace core {

StringImpl::StringImpl(const std::string& value) : value(value) {}

StringImpl::~StringImpl() {}

size_t StringImpl::length() const {
    return value.length();
}

std::string StringImpl::substring(size_t start, size_t length) const {
    return value.substr(start, length);
}

int StringImpl::indexOf(const std::string& str) const {
    size_t pos = value.find(str);
    return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

int StringImpl::lastIndexOf(const std::string& str) const {
    size_t pos = value.rfind(str);
    return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

std::string StringImpl::replace(const std::string& from, const std::string& to) const {
    std::string result = value;
    size_t start_pos = 0;
    while((start_pos = result.find(from, start_pos)) != std::string::npos) {
        result.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return result;
}

std::vector<std::string> StringImpl::split(const std::string& delimiter) const {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = value.find(delimiter);

    while (end != std::string::npos) {
        result.push_back(value.substr(start, end - start));
        start = end + delimiter.length();
        end = value.find(delimiter, start);
    }

    result.push_back(value.substr(start));
    return result;
}

std::string StringImpl::trim() const {
    auto start = value.begin();
    auto end = value.end();

    while (start != end && std::isspace(*start)) ++start;
    while (start != end && std::isspace(*(end - 1))) --end;

    return std::string(start, end);
}

std::string StringImpl::toString() const {
    return value;
}

void StringImpl::registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder) {
    auto& context = module->getContext();
    auto voidTy = llvm::Type::getVoidTy(context);
    auto int8PtrTy = llvm::Type::getInt8PtrTy(context);
    auto int32Ty = llvm::Type::getInt32Ty(context);
    auto int64Ty = llvm::Type::getInt64Ty(context);

    // Create String class type
    std::vector<llvm::Type*> stringFields;
    stringFields.push_back(int8PtrTy);  // value
    auto stringStructTy = llvm::StructType::create(context, stringFields, "struct.pryst.core.String");

    // Create constructor
    std::vector<llvm::Type*> ctorArgs = {int8PtrTy};  // value
    auto ctorTy = llvm::FunctionType::get(stringStructTy->getPointerTo(), ctorArgs, false);
    auto ctor = llvm::Function::Create(ctorTy, llvm::Function::ExternalLinkage,
                                     "String_new", module);

    // Create constructor body
    auto ctorBB = llvm::BasicBlock::Create(context, "entry", ctor);
    builder.SetInsertPoint(ctorBB);
    auto stringObj = builder.CreateAlloca(stringStructTy);
    auto valueGEP = builder.CreateStructGEP(stringStructTy, stringObj, 0);
    builder.CreateStore(ctor->getArg(0), valueGEP);
    builder.CreateRet(stringObj);

    // Create length method
    std::vector<llvm::Type*> lengthArgs = {stringStructTy->getPointerTo()};
    auto lengthTy = llvm::FunctionType::get(int64Ty, lengthArgs, false);
    auto length = llvm::Function::Create(lengthTy, llvm::Function::ExternalLinkage,
                                       "String_length", module);

    // Create length body
    auto lengthBB = llvm::BasicBlock::Create(context, "entry", length);
    builder.SetInsertPoint(lengthBB);
    auto lengthFn = module->getOrInsertFunction("pryst_core_String_length",
        llvm::FunctionType::get(int64Ty, {stringStructTy->getPointerTo()}, false));
    auto lengthResult = builder.CreateCall(lengthFn, {length->getArg(0)});
    builder.CreateRet(lengthResult);

    // Create substring method
    std::vector<llvm::Type*> substringArgs = {stringStructTy->getPointerTo(), int64Ty, int64Ty};
    auto substringTy = llvm::FunctionType::get(stringStructTy->getPointerTo(), substringArgs, false);
    auto substring = llvm::Function::Create(substringTy, llvm::Function::ExternalLinkage,
                                          "String_substring", module);

    // Create substring body
    auto substringBB = llvm::BasicBlock::Create(context, "entry", substring);
    builder.SetInsertPoint(substringBB);
    auto substringFn = module->getOrInsertFunction("pryst_core_String_substring",
        llvm::FunctionType::get(stringStructTy->getPointerTo(),
                               {stringStructTy->getPointerTo(), int64Ty, int64Ty}, false));
    auto substringResult = builder.CreateCall(substringFn,
        {substring->getArg(0), substring->getArg(1), substring->getArg(2)});
    builder.CreateRet(substringResult);

    // Create indexOf method
    std::vector<llvm::Type*> indexOfArgs = {stringStructTy->getPointerTo(), int8PtrTy};
    auto indexOfTy = llvm::FunctionType::get(int32Ty, indexOfArgs, false);
    auto indexOf = llvm::Function::Create(indexOfTy, llvm::Function::ExternalLinkage,
                                        "String_indexOf", module);

    // Create indexOf body
    auto indexOfBB = llvm::BasicBlock::Create(context, "entry", indexOf);
    builder.SetInsertPoint(indexOfBB);
    auto indexOfFn = module->getOrInsertFunction("pryst_core_String_indexOf",
        llvm::FunctionType::get(int32Ty, {stringStructTy->getPointerTo(), int8PtrTy}, false));
    auto indexOfResult = builder.CreateCall(indexOfFn,
        {indexOf->getArg(0), indexOf->getArg(1)});
    builder.CreateRet(indexOfResult);

    // Create lastIndexOf method
    auto lastIndexOf = llvm::Function::Create(indexOfTy, llvm::Function::ExternalLinkage,
                                            "String_lastIndexOf", module);

    // Create lastIndexOf body
    auto lastIndexOfBB = llvm::BasicBlock::Create(context, "entry", lastIndexOf);
    builder.SetInsertPoint(lastIndexOfBB);
    auto lastIndexOfFn = module->getOrInsertFunction("pryst_core_String_lastIndexOf",
        llvm::FunctionType::get(int32Ty, {stringStructTy->getPointerTo(), int8PtrTy}, false));
    auto lastIndexOfResult = builder.CreateCall(lastIndexOfFn,
        {lastIndexOf->getArg(0), lastIndexOf->getArg(1)});
    builder.CreateRet(lastIndexOfResult);

    // Create replace method
    std::vector<llvm::Type*> replaceArgs = {stringStructTy->getPointerTo(), int8PtrTy, int8PtrTy};
    auto replaceTy = llvm::FunctionType::get(stringStructTy->getPointerTo(), replaceArgs, false);
    auto replace = llvm::Function::Create(replaceTy, llvm::Function::ExternalLinkage,
                                        "String_replace", module);

    // Create replace body
    auto replaceBB = llvm::BasicBlock::Create(context, "entry", replace);
    builder.SetInsertPoint(replaceBB);
    auto replaceFn = module->getOrInsertFunction("pryst_core_String_replace",
        llvm::FunctionType::get(stringStructTy->getPointerTo(),
                               {stringStructTy->getPointerTo(), int8PtrTy, int8PtrTy}, false));
    auto replaceResult = builder.CreateCall(replaceFn,
        {replace->getArg(0), replace->getArg(1), replace->getArg(2)});
    builder.CreateRet(replaceResult);

    // Create split method
    std::vector<llvm::Type*> splitArgs = {stringStructTy->getPointerTo(), int8PtrTy};
    auto splitTy = llvm::FunctionType::get(int8PtrTy, splitArgs, false);  // Returns array pointer
    auto split = llvm::Function::Create(splitTy, llvm::Function::ExternalLinkage,
                                      "String_split", module);

    // Create split body
    auto splitBB = llvm::BasicBlock::Create(context, "entry", split);
    builder.SetInsertPoint(splitBB);
    auto splitFn = module->getOrInsertFunction("pryst_core_String_split",
        llvm::FunctionType::get(int8PtrTy, {stringStructTy->getPointerTo(), int8PtrTy}, false));
    auto splitResult = builder.CreateCall(splitFn,
        {split->getArg(0), split->getArg(1)});
    builder.CreateRet(splitResult);

    // Create trim method
    std::vector<llvm::Type*> trimArgs = {stringStructTy->getPointerTo()};
    auto trimTy = llvm::FunctionType::get(stringStructTy->getPointerTo(), trimArgs, false);
    auto trim = llvm::Function::Create(trimTy, llvm::Function::ExternalLinkage,
                                     "String_trim", module);

    // Create trim body
    auto trimBB = llvm::BasicBlock::Create(context, "entry", trim);
    builder.SetInsertPoint(trimBB);
    auto trimFn = module->getOrInsertFunction("pryst_core_String_trim",
        llvm::FunctionType::get(stringStructTy->getPointerTo(),
                               {stringStructTy->getPointerTo()}, false));
    auto trimResult = builder.CreateCall(trimFn, {trim->getArg(0)});
    builder.CreateRet(trimResult);

    // Create toString method
    std::vector<llvm::Type*> toStringArgs = {stringStructTy->getPointerTo()};
    auto toStringTy = llvm::FunctionType::get(int8PtrTy, toStringArgs, false);
    auto toString = llvm::Function::Create(toStringTy, llvm::Function::ExternalLinkage,
                                         "String_toString", module);

    // Create toString body
    auto toStringBB = llvm::BasicBlock::Create(context, "entry", toString);
    builder.SetInsertPoint(toStringBB);
    auto toStringFn = module->getOrInsertFunction("pryst_core_String_toString",
        llvm::FunctionType::get(int8PtrTy, {stringStructTy->getPointerTo()}, false));
    auto toStringResult = builder.CreateCall(toStringFn, {toString->getArg(0)});
    builder.CreateRet(toStringResult);

    // Verify all functions
    llvm::verifyFunction(*ctor);
    llvm::verifyFunction(*length);
    llvm::verifyFunction(*substring);
    llvm::verifyFunction(*indexOf);
    llvm::verifyFunction(*lastIndexOf);
    llvm::verifyFunction(*replace);
    llvm::verifyFunction(*split);
    llvm::verifyFunction(*trim);
    llvm::verifyFunction(*toString);
}

} // namespace core
} // namespace pryst
