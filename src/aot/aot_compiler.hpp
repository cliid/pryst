#pragma once

#include <memory>
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>
#include <string>

class AOTCompiler {
public:
    AOTCompiler();
    void compile(llvm::Module& module, const std::string& outputFilename);

private:
    std::unique_ptr<llvm::TargetMachine> targetMachine;
};
