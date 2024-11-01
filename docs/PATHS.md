# Build Configuration Paths

## Original Mac Configuration (User's Machine)
These are the original paths that worked on the user's machine:

### LLVM Configuration
- LLVM_DIR: `/usr/local/lib/cmake/llvm`
- Compiler paths:
  - C Compiler: `/usr/bin/clang`
  - C++ Compiler: `/usr/bin/clang++`

### ANTLR4 Configuration
- ANTLR4 Include Directory: `/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/include/antlr4-runtime`
- ANTLR4 Library Directory: `/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/lib`
- Required Headers Location: `antlr4-runtime.h` and related headers in the include directory

## Ubuntu Configuration
Current working configuration for Ubuntu systems:

### LLVM Configuration
- LLVM_DIR: `/usr/lib/llvm-20/cmake`
- LLVM Include Directory: `/usr/lib/llvm-20/include`
- Compiler paths:
  - C Compiler: `/usr/bin/clang-20`
  - C++ Compiler: `/usr/bin/clang++-20`

### ANTLR4 Configuration
- ANTLR4 Include Directory: `/usr/local/include/antlr4-runtime`
- ANTLR4 Library Directory: `/usr/local/lib`
- Required Headers: `antlr4-runtime.h` and related headers in `/usr/local/include/antlr4-runtime`

## Build System Configuration
The CMake build system should:
1. Check these paths in order of preference
2. Allow override via CMake variables
3. Support both Mac and Ubuntu environments

### Example CMake Commands

For Mac (original configuration):
```bash
cmake -DLLVM_DIR=/usr/local/lib/cmake/llvm \
      -DANTLR4_INCLUDE_DIR=/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/include/antlr4-runtime \
      -DANTLR4_LIBRARY_DIR=/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/lib \
      ..
```

For Ubuntu:
```bash
cmake -DLLVM_DIR=/usr/lib/llvm-20/cmake \
      -DANTLR4_INCLUDE_DIR=/usr/local/include/antlr4-runtime \
      -DANTLR4_LIBRARY_DIR=/usr/local/lib \
      ..
```
