#include "aot_compiler.hpp"
#include <llvm/Support/CodeGen.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Support/Host.h>
#include <llvm/MC/TargetRegistry.h>
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
#include <system_error>
#include <optional>

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
    std::optional<llvm::Reloc::Model> RM = std::nullopt;
    targetMachine = std::unique_ptr<llvm::TargetMachine>(
        target->createTargetMachine(targetTriple, CPU, features, opt, RM));

    module.setDataLayout(targetMachine->createDataLayout());

    std::error_code EC;
    llvm::raw_fd_ostream dest(outputFilename, EC, llvm::sys::fs::OF_None);
    if (EC) {
        llvm::errs() << "Could not open file: " << EC.message();
        return;
    }

    // Create the legacy pass manager
    llvm::legacy::PassManager pass;

    // Add passes to emit object file
    if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, llvm::CodeGenFileType::ObjectFile)) {
        llvm::errs() << "TargetMachine can't emit a file of this type\n";
        return;
    }

    // Run the passes
    pass.run(module);
    dest.flush();
}
