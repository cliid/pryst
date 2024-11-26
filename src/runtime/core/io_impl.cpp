#include "io_impl.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Verifier.h"

namespace pryst {
namespace io {

// IOImpl static method implementations
void IOImpl::print(const std::string& message) {
    std::cout << message;
}

void IOImpl::println(const std::string& message) {
    std::cout << message << std::endl;
}

std::string IOImpl::readLine() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

char IOImpl::getChar() {
    char c;
    std::cin.get(c);
    return c;
}

void IOImpl::registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder) {
    auto& context = module->getContext();
    auto voidTy = llvm::Type::getVoidTy(context);
    auto int8PtrTy = llvm::Type::getInt8PtrTy(context);
    auto int8Ty = llvm::Type::getInt8Ty(context);

    // Create IO class type
    std::vector<llvm::Type*> ioFields;  // Empty as all methods are static
    auto ioStructTy = llvm::StructType::create(context, ioFields, "struct.pryst.io.IO");

    // Register print method
    std::vector<llvm::Type*> printArgs = {int8PtrTy};
    auto printTy = llvm::FunctionType::get(voidTy, printArgs, false);
    auto printFn = llvm::Function::Create(printTy, llvm::Function::ExternalLinkage,
                                        "pryst_io_IO_print", module);

    auto printBB = llvm::BasicBlock::Create(context, "entry", printFn);
    builder.SetInsertPoint(printBB);
    auto printImpl = module->getOrInsertFunction("pryst_io_print_impl",
        llvm::FunctionType::get(voidTy, {int8PtrTy}, false));
    builder.CreateCall(printImpl, {printFn->getArg(0)});
    builder.CreateRetVoid();

    // Register println method
    auto printlnFn = llvm::Function::Create(printTy, llvm::Function::ExternalLinkage,
                                          "pryst_io_IO_println", module);
    auto printlnBB = llvm::BasicBlock::Create(context, "entry", printlnFn);
    builder.SetInsertPoint(printlnBB);
    auto printlnImpl = module->getOrInsertFunction("pryst_io_println_impl",
        llvm::FunctionType::get(voidTy, {int8PtrTy}, false));
    builder.CreateCall(printlnImpl, {printlnFn->getArg(0)});
    builder.CreateRetVoid();

    // Register readLine method
    auto readLineTy = llvm::FunctionType::get(int8PtrTy, {}, false);
    auto readLineFn = llvm::Function::Create(readLineTy, llvm::Function::ExternalLinkage,
                                           "pryst_io_IO_readLine", module);
    auto readLineBB = llvm::BasicBlock::Create(context, "entry", readLineFn);
    builder.SetInsertPoint(readLineBB);
    auto readLineImpl = module->getOrInsertFunction("pryst_io_readLine_impl",
        llvm::FunctionType::get(int8PtrTy, {}, false));
    auto result = builder.CreateCall(readLineImpl, {});
    builder.CreateRet(result);

    // Register getChar method
    auto getCharTy = llvm::FunctionType::get(int8Ty, {}, false);
    auto getCharFn = llvm::Function::Create(getCharTy, llvm::Function::ExternalLinkage,
                                          "pryst_io_IO_getChar", module);
    auto getCharBB = llvm::BasicBlock::Create(context, "entry", getCharFn);
    builder.SetInsertPoint(getCharBB);
    auto getCharImpl = module->getOrInsertFunction("pryst_io_getChar_impl",
        llvm::FunctionType::get(int8Ty, {}, false));
    auto charResult = builder.CreateCall(getCharImpl, {});
    builder.CreateRet(charResult);

    // Verify all functions
    llvm::verifyFunction(*printFn);
    llvm::verifyFunction(*printlnFn);
    llvm::verifyFunction(*readLineFn);
    llvm::verifyFunction(*getCharFn);
}

FileImpl::FileImpl(const std::string& path) : path(path) {
    file = std::make_unique<std::fstream>();
    file->open(path, std::ios::in | std::ios::out);
    if (!file->is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }
}

FileImpl::~FileImpl() {
    if (file && file->is_open()) {
        file->close();
    }
}

std::string* FileImpl::readString() {
    if (!isValid()) {
        return nullptr;
    }
    try {
        std::stringstream buffer;
        buffer << file->rdbuf();
        std::string* content = new std::string(buffer.str());
        return content;
    } catch (...) {
        return nullptr;
    }
}

bool FileImpl::writeString(const std::string& content) {
    if (!isValid()) {
        return false;
    }
    try {
        file->seekp(0);
        *file << content;
        file->flush();
        return true;
    } catch (...) {
        return false;
    }
}

void FileImpl::close() {
    if (file && file->is_open()) {
        file->close();
    }
}

void FileImpl::registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder) {
    auto& context = module->getContext();
    auto voidTy = llvm::Type::getVoidTy(context);
    auto int8PtrTy = llvm::Type::getInt8PtrTy(context);
    auto int64Ty = llvm::Type::getInt64Ty(context);
    auto int1Ty = llvm::Type::getInt1Ty(context);

    std::vector<llvm::Type*> fileFields;
    fileFields.push_back(int8PtrTy);
    fileFields.push_back(int8PtrTy);
    auto fileStructTy = llvm::StructType::create(context, fileFields, "struct.pryst.io.File");

    std::vector<llvm::Type*> ctorArgs = {int8PtrTy};
    auto ctorTy = llvm::FunctionType::get(fileStructTy->getPointerTo(), ctorArgs, false);
    auto ctor = llvm::Function::Create(ctorTy, llvm::Function::ExternalLinkage,
                                     "File_new", module);

    auto ctorBB = llvm::BasicBlock::Create(context, "entry", ctor);
    builder.SetInsertPoint(ctorBB);

    auto fileObj = builder.CreateAlloca(fileStructTy);
    auto pathGEP = builder.CreateStructGEP(fileStructTy, fileObj, 0);
    builder.CreateStore(ctor->getArg(0), pathGEP);

    auto createFileFn = module->getOrInsertFunction("pryst_io_File_new",
        llvm::FunctionType::get(int8PtrTy, {int8PtrTy}, false));
    auto fileHandle = builder.CreateCall(createFileFn, {ctor->getArg(0)});

    auto handleGEP = builder.CreateStructGEP(fileStructTy, fileObj, 1);
    builder.CreateStore(fileHandle, handleGEP);
    builder.CreateRet(fileObj);

    // readString method
    std::vector<llvm::Type*> readArgs = {fileStructTy->getPointerTo()};
    auto readTy = llvm::FunctionType::get(int8PtrTy, readArgs, false);
    auto read = llvm::Function::Create(readTy, llvm::Function::ExternalLinkage,
                                    "File_readString", module);

    auto readBB = llvm::BasicBlock::Create(context, "entry", read);
    builder.SetInsertPoint(readBB);

    auto thisObj = read->getArg(0);
    auto handleGEP2 = builder.CreateStructGEP(fileStructTy, thisObj, 1);
    auto handle = builder.CreateLoad(int8PtrTy, handleGEP2);

    auto readFileFn = module->getOrInsertFunction("pryst_io_File_readString",
        llvm::FunctionType::get(int8PtrTy, {int8PtrTy}, false));
    auto result = builder.CreateCall(readFileFn, {handle});
    builder.CreateRet(result);

    // writeString method
    std::vector<llvm::Type*> writeArgs = {fileStructTy->getPointerTo(), int8PtrTy};
    auto writeTy = llvm::FunctionType::get(int1Ty, writeArgs, false);
    auto write = llvm::Function::Create(writeTy, llvm::Function::ExternalLinkage,
                                     "File_writeString", module);

    auto writeBB = llvm::BasicBlock::Create(context, "entry", write);
    builder.SetInsertPoint(writeBB);

    auto thisObj2 = write->getArg(0);
    auto handleGEP3 = builder.CreateStructGEP(fileStructTy, thisObj2, 1);
    auto handle2 = builder.CreateLoad(int8PtrTy, handleGEP3);

    auto writeFileFn = module->getOrInsertFunction("pryst_io_File_writeString",
        llvm::FunctionType::get(int1Ty, {int8PtrTy, int8PtrTy}, false));
    auto writeResult = builder.CreateCall(writeFileFn, {handle2, write->getArg(1)});
    builder.CreateRet(writeResult);

    std::vector<llvm::Type*> closeArgs = {fileStructTy->getPointerTo()};
    auto closeTy = llvm::FunctionType::get(voidTy, closeArgs, false);
    auto close = llvm::Function::Create(closeTy, llvm::Function::ExternalLinkage,
                                      "File_close", module);

    auto closeBB = llvm::BasicBlock::Create(context, "entry", close);
    builder.SetInsertPoint(closeBB);

    auto thisObj3 = close->getArg(0);
    auto handleGEP4 = builder.CreateStructGEP(fileStructTy, thisObj3, 1);
    auto handle3 = builder.CreateLoad(int8PtrTy, handleGEP4);

    auto closeFileFn = module->getOrInsertFunction("pryst_io_File_close",
        llvm::FunctionType::get(voidTy, {int8PtrTy}, false));
    builder.CreateCall(closeFileFn, {handle3});
    builder.CreateRetVoid();

    llvm::verifyFunction(*ctor);
    llvm::verifyFunction(*read);
    llvm::verifyFunction(*write);
    llvm::verifyFunction(*close);
}

// Runtime binding implementations
extern "C" {

void pryst_io_print_impl(const char* message) {
    pryst::io::IOImpl::print(message);
}

void pryst_io_println_impl(const char* message) {
    pryst::io::IOImpl::println(message);
}

char* pryst_io_readLine_impl() {
    std::string line = pryst::io::IOImpl::readLine();
    char* result = new char[line.length() + 1];
    strcpy(result, line.c_str());
    return result;
}

char pryst_io_getChar_impl() {
    return pryst::io::IOImpl::getChar();
}

void* pryst_io_File_new(const char* path) {
    try {
        return new pryst::io::FileImpl(path);
    } catch (...) {
        return nullptr;
    }
}

char* pryst_io_File_readString(void* file) {
    if (!file) return nullptr;
    pryst::io::FileImpl* fileImpl = static_cast<pryst::io::FileImpl*>(file);
    std::string* content = fileImpl->readString();
    if (!content) return nullptr;
    char* result = new char[content->length() + 1];
    strcpy(result, content->c_str());
    delete content;
    return result;
}

bool pryst_io_File_writeString(void* file, const char* content) {
    if (!file || !content) return false;
    pryst::io::FileImpl* fileImpl = static_cast<pryst::io::FileImpl*>(file);
    return fileImpl->writeString(content);
}

void pryst_io_File_close(void* file) {
    if (!file) return;
    pryst::io::FileImpl* fileImpl = static_cast<pryst::io::FileImpl*>(file);
    try {
        fileImpl->close();
    } catch (const std::exception&) {
        // Handle error
    }
}

} // extern "C"

} // namespace io
} // namespace pryst
