#include "compiler.hpp"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Transforms/Utils.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/ADT/Optional.h>
#include <memory>
#include <string>

namespace pryst {
    // Forward declarations if needed
} // namespace pryst

using namespace pryst;

void Compiler::initializeTarget() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();
}

void Compiler::optimize() {
    // Create the analysis managers
    llvm::PassManagerBuilder PMBuilder;
    PMBuilder.OptLevel = 3;  // -O3 optimization
    PMBuilder.SizeLevel = 0;
    PMBuilder.Inliner = llvm::createFunctionInliningPass(3, 0, false);
    PMBuilder.LoopVectorize = true;
    PMBuilder.SLPVectorize = true;

    // Create and populate module pass manager
    llvm::legacy::PassManager MPM;

    // Add optimization passes
    MPM.add(llvm::createPromoteMemoryToRegisterPass());    // Promote allocas to registers
    MPM.add(llvm::createInstructionCombiningPass());       // Combine instructions
    MPM.add(llvm::createReassociatePass());               // Reassociate expressions
    MPM.add(llvm::createGVNPass());                       // Eliminate common subexpressions
    MPM.add(llvm::createCFGSimplificationPass());         // Simplify the control flow graph
    MPM.add(llvm::createAggressiveDCEPass());            // Delete dead code aggressively

    // Run the optimizations
    MPM.run(*Module);
}

Compiler::Compiler() :
    Context(std::make_unique<llvm::LLVMContext>()),
    Module(std::make_unique<llvm::Module>("pryst_module", *Context)),
    Builder(std::make_unique<llvm::IRBuilder<>>(*Context)),
    Registry(std::make_unique<TypeRegistry>()) {
    initializeTarget();
}

Compiler::~Compiler() = default;

bool Compiler::compileToObjectFile(const std::string& filename) {
    // Optimize the module
    optimize();

    // Get the target triple
    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    Module->setTargetTriple(targetTriple);

    // Get the target
    std::string error;
    auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
    if (!target) {
        llvm::errs() << "Target lookup failed: " << error;
        return false;
    }

    // Create target machine
    auto CPU = "generic";
    auto features = "";
    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto targetMachine = target->createTargetMachine(targetTriple, CPU, features, opt, RM);

    // Configure module data layout
    Module->setDataLayout(targetMachine->createDataLayout());

    // Open output file
    std::error_code EC;
    llvm::raw_fd_ostream dest(filename, EC, llvm::sys::fs::OF_None);
    if (EC) {
        llvm::errs() << "Could not open file: " << EC.message();
        return false;
    }

    // Create pass pipeline
    llvm::legacy::PassManager pass;

    // Generate object file
    if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, llvm::CGFT_ObjectFile)) {
        llvm::errs() << "Target machine can't emit a file of this type";
        return false;
    }

    pass.run(*Module);
    dest.flush();
    return true;
}
