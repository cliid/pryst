#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <map>
#include <string>
#include <memory>

class VisitorBase {
protected:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::Module> module;
    std::map<std::string, llvm::Value*> namedValues;
    llvm::Value* lastValue;

public:
    VisitorBase() :
        context(std::make_unique<llvm::LLVMContext>()),
        builder(std::make_unique<llvm::IRBuilder<>>(*context)),
        module(std::make_unique<llvm::Module>("pryst", *context)),
        lastValue(nullptr) {}

    virtual ~VisitorBase() = default;

    // LLVM utility methods that don't need RTTI
    llvm::Value* getLastValue() const { return lastValue; }
    void setLastValue(llvm::Value* value) { lastValue = value; }
    llvm::LLVMContext& getContext() { return *context; }
    llvm::IRBuilder<>& getBuilder() { return *builder; }
    llvm::Module& getModule() { return *module; }
    std::map<std::string, llvm::Value*>& getNamedValues() { return namedValues; }
};
