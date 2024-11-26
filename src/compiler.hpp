#pragma once

// LLVM includes
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>

#include <memory>
#include <string>
#include "type_registry.hpp"
#include "error.hpp"
#include "type_checker.hpp"
#include "llvm_codegen.hpp"
#include "runtime/runtime_registry.hpp"

namespace pryst {

class Compiler {
public:
    Compiler();
    ~Compiler();

    // Get LLVM components
    llvm::LLVMContext& getContext() { return *Context; }
    llvm::Module& getModule() { return *ModuleInstance; }
    llvm::IRBuilder<llvm::ConstantFolder, llvm::IRBuilderDefaultInserter>& getBuilder() { return *Builder; }
    types::TypeRegistry& getRegistry() { return *Registry; }
    TypeChecker& getTypeChecker() { return *typeChecker; }
    runtime::RuntimeRegistry& getRuntimeRegistry() { return *runtimeRegistry; }

    // Test helper method to inject test type checker
    void setTypeChecker(std::unique_ptr<TypeChecker> checker) {
        typeChecker = std::move(checker);
    }

    // Compile AST
    bool compile(antlr4::tree::ParseTree* tree);

    // Compile the current module to an object file
    bool compileToObjectFile(const std::string& filename);

    // Run optimization passes
    void optimize();

private:
    // Initialize target for current machine
    void initializeTarget();

    std::unique_ptr<llvm::LLVMContext> Context;
    std::unique_ptr<llvm::Module> ModuleInstance;
    std::unique_ptr<llvm::IRBuilder<llvm::ConstantFolder, llvm::IRBuilderDefaultInserter>> Builder;
    std::unique_ptr<llvm::TargetMachine> Target;
    std::unique_ptr<types::TypeRegistry> Registry;
    std::unique_ptr<TypeChecker> typeChecker;
    std::unique_ptr<LLVMCodeGen> codeGen;
    std::unique_ptr<runtime::RuntimeRegistry> runtimeRegistry;
};

} // namespace pryst
