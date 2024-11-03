#include "aot_compiler.hpp"
#include <llvm/ADT/STLExtras.h>
#include <llvm/Analysis/TargetLibraryInfo.h>
#include <llvm/Analysis/TargetTransformInfo.h>
#include <llvm/CodeGen/CommandFlags.h>
#include <llvm/CodeGen/LinkAllAsmWriterComponents.h>
#include <llvm/CodeGen/LinkAllCodegenComponents.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/PassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Utils.h>
#include <llvm/Analysis/AliasAnalysis.h>
#include <llvm/Analysis/BasicAliasAnalysis.h>
#include <llvm/Analysis/GlobalsModRef.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/ADT/BitVector.h>
#include <llvm/Support/MathExtras.h>
#include <optional>

using namespace llvm;
using namespace llvm::sys;

AOTCompiler::AOTCompiler() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
}

void AOTCompiler::compile(Module& module, const std::string& outputFilename) {
    auto targetTriple = Triple::normalize(getProcessTriple());
    module.setTargetTriple(targetTriple);

    std::string error;
    auto target = TargetRegistry::lookupTarget(targetTriple, error);

    if (!target) {
        throw std::runtime_error("Failed to lookup target: " + error);
    }

    std::string CPU = "generic";
    std::string features = "";
    TargetOptions opt;

    // Create target machine with correct optimization level
    std::optional<llvm::Reloc::Model> RM = llvm::Reloc::PIC_;
    std::optional<llvm::CodeModel::Model> CM = llvm::CodeModel::Small;
    targetMachine = std::unique_ptr<TargetMachine>(
        target->createTargetMachine(targetTriple, CPU, features, opt, RM, CM));

    if (!targetMachine) {
        throw std::runtime_error("Failed to create target machine");
    }

    module.setDataLayout(targetMachine->createDataLayout());
    module.setTargetTriple(targetTriple);

    // Create output file
    std::error_code EC;
    raw_fd_ostream dest(outputFilename, EC, sys::fs::OF_None);
    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return;
    }

    // Initialize PassBuilder and analysis managers
    LoopAnalysisManager LAM;
    FunctionAnalysisManager FAM;
    CGSCCAnalysisManager CGAM;
    ModuleAnalysisManager MAM;

    // Create PassBuilder with target machine info
    PassBuilder PB(targetMachine.get());

    // Register target-specific analysis passes
    PB.registerModuleAnalyses(MAM);
    PB.registerCGSCCAnalyses(CGAM);
    PB.registerFunctionAnalyses(FAM);
    PB.registerLoopAnalyses(LAM);
    PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

    // Create optimization pipeline
    ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(OptimizationLevel::O2);

    // Run optimization passes
    MPM.run(module, MAM);

    // Create and run code generation pipeline using legacy pass manager
    // Note: LLVM 20.0.0 still requires legacy pass manager for code generation
    legacy::PassManager CodeGenPM;
    if (targetMachine->addPassesToEmitFile(CodeGenPM, dest, nullptr, CodeGenFileType::ObjectFile)) {
        errs() << "TargetMachine can't emit a file of this type";
        return;
    }

    CodeGenPM.run(module);
    dest.flush();
}
