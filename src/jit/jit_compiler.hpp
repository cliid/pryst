#pragma once

#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/Module.h>
#include <memory>

class JITCompiler {
public:
    JITCompiler();
    void compileAndRun(std::unique_ptr<llvm::Module> module);

private:
    std::unique_ptr<llvm::orc::LLJIT> jit;
};
