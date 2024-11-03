#pragma once

#include <memory>
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/SubtargetFeature.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/TargetParser/Host.h>
#include <string>

class AOTCompiler {
public:
    AOTCompiler();
    void compile(llvm::Module& module, const std::string& outputFilename);

private:
    std::unique_ptr<llvm::TargetMachine> targetMachine;
};
