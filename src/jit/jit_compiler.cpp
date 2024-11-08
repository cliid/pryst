// Include project headers first
#include "jit_compiler.hpp"
#include "utils/debug.hpp"
#include "utils/logger.hpp"

// Then include LLVM headers
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>

#include <memory>
#include <string>

namespace pryst {

JITCompiler::JITCompiler() {
    PRYST_DEBUG("Initializing JIT compiler");
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
}

void JITCompiler::compileAndRun(std::unique_ptr<llvm::Module> module) {
    if (!module) {
        PRYST_ERROR("Null module provided to compileAndRun");
        return;
    }

    PRYST_DEBUG("Creating LLJIT instance");
    auto jitOrErr = llvm::orc::LLJITBuilder().create();
    if (!jitOrErr) {
        std::string errMsg;
        llvm::raw_string_ostream os(errMsg);
        os << jitOrErr.takeError();
        PRYST_ERROR("Failed to create LLJIT: " + errMsg);
        return;
    }

    jit = std::move(*jitOrErr);
    PRYST_DEBUG("Created LLJIT instance successfully");

    auto tsm = llvm::orc::ThreadSafeModule(std::move(module), std::make_unique<llvm::LLVMContext>());
    PRYST_DEBUG("Created ThreadSafeModule");

    if (auto err = jit->addIRModule(std::move(tsm))) {
        std::string errMsg;
        llvm::raw_string_ostream os(errMsg);
        os << err;
        PRYST_ERROR("Failed to add IR module: " + errMsg);
        return;
    }
    PRYST_DEBUG("Added IR module successfully");

    auto mainSymbol = jit->lookup("main");
    if (!mainSymbol) {
        std::string errMsg;
        llvm::raw_string_ostream os(errMsg);
        os << mainSymbol.takeError();
        PRYST_ERROR("Failed to find main function: " + errMsg);
        return;
    }
    PRYST_DEBUG("Found main function");

    auto mainFn = (int(*)())(intptr_t)mainSymbol->getValue();
    PRYST_DEBUG("Executing main function");
    mainFn();
    PRYST_DEBUG("Main function execution completed");
}

} // namespace pryst
