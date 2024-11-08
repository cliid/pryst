#pragma once

// Include LLVM headers outside any namespace
#include <llvm/IR/Module.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/Error.h>
#include <memory>

// Forward declarations of LLVM types we'll use
namespace llvm {
namespace orc {
class LLJIT;
}
}

namespace pryst {

class JITCompiler {
public:
    JITCompiler();
    void compileAndRun(std::unique_ptr<llvm::Module> module);
private:
    std::unique_ptr<llvm::orc::LLJIT> jit;
};

} // namespace pryst
