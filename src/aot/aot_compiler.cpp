#include "aot_compiler.hpp"
#include <llvm/TargetParser/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/raw_ostream.h>
#include <system_error>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/MC/MCContext.h>
#include <llvm/MC/MCTargetOptions.h>
#include <llvm/MC/MCAsmBackend.h>
#include <llvm/MC/MCCodeEmitter.h>
#include <llvm/MC/MCObjectStreamer.h>
#include <llvm/MC/MCObjectWriter.h>
#include <llvm/MC/MCSymbol.h>
#include <llvm/MC/MCExpr.h>
#include <llvm/MC/MCStreamer.h>
#include <llvm/MC/MCELFObjectWriter.h>
#include <llvm/MC/MCELFStreamer.h>
#include <llvm/MC/MCAsmInfo.h>

AOTCompiler::AOTCompiler() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
}

void AOTCompiler::compile(llvm::Module& module, const std::string& outputFilename) {
    auto targetTriple = llvm::Triple::normalize(llvm::sys::getProcessTriple());
    module.setTargetTriple(targetTriple);

    std::string error;
    auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

    if (!target) {
        llvm::errs() << error;
        return;
    }

    auto CPU = "generic";
    auto features = "";

    llvm::MCTargetOptions MCOpt;
    llvm::TargetOptions opt;
    auto RM = std::optional<llvm::Reloc::Model>();
    targetMachine = std::unique_ptr<llvm::TargetMachine>(
        target->createTargetMachine(targetTriple, CPU, features, opt, RM));

    module.setDataLayout(targetMachine->createDataLayout());

    llvm::LoopAnalysisManager LAM;
    llvm::FunctionAnalysisManager FAM;
    llvm::CGSCCAnalysisManager CGAM;
    llvm::ModuleAnalysisManager MAM;

    llvm::PassBuilder PB(targetMachine.get());

    PB.registerModuleAnalyses(MAM);
    PB.registerCGSCCAnalyses(CGAM);
    PB.registerFunctionAnalyses(FAM);
    PB.registerLoopAnalyses(LAM);
    PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

    // Run optimization passes
    llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(llvm::OptimizationLevel::O2);
    MPM.run(module, MAM);

    // Emit object file
    if (auto EC = targetMachine->emitToObjectFile(module, outputFilename)) {
        llvm::errs() << "Could not emit module to file: " << EC.message();
        return;
    }
}
