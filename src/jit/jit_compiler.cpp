#include "jit_compiler.hpp"
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/Error.h>
#include <iostream>

JITCompiler::JITCompiler() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    auto JIT = llvm::orc::LLJITBuilder().create();
    if (!JIT) {
        std::cerr << "Failed to create LLJIT: " << llvm::toString(JIT.takeError()) << std::endl;
        std::exit(1);
    }
    jit = std::move(*JIT);
}

void JITCompiler::compileAndRun(std::unique_ptr<llvm::Module> module) {
    // Add the module to the JIT
    auto err = jit->addIRModule(llvm::orc::ThreadSafeModule(std::move(module), std::make_unique<llvm::LLVMContext>()));
    if (err) {
        std::cerr << "Failed to add module: " << llvm::toString(std::move(err)) << std::endl;
        return;
    }

    // Look up the JIT'd code
    auto mainSymbol = jit->lookup("main");
    if (!mainSymbol) {
        std::cerr << "Failed to find main function: " << llvm::toString(mainSymbol.takeError()) << std::endl;
        return;
    }

    // Cast the symbol address to a function pointer
    int (*mainFunc)() = reinterpret_cast<int(*)()>(mainSymbol->getValue());

    // Call the JIT'd code
    int result = mainFunc();
    std::cout << "JIT execution result: " << result << std::endl;
}
