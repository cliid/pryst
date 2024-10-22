# pryst compiler

a compiler for pryst, a statically-typed, object-oriented language inspired by TypeScript and C++.

## features

- basic types: `int`, `float`, `bool`, `str`
- functions and classes
- control structures: `if-else`, `while`, `for`
- inheritance

## tech stack

- developed in C/C++
- ANTLR4 for lexing/parsing
- LLVM for code generation and optimization
- CMake for build management

## key components

- `Pryst.g4`: antlr4 grammar
- `semantic_analyzer.cpp`: ast analysis
- `llvm_codegen.cpp`: llvm ir generation
- `jit_compiler.cpp`: jit compilation
- `aot_compiler.cpp`: aot compilation

## build instructions

prerequisites: `cmake`, `antlr4`, `llvm`

```bash
mkdir build && cd build
cmake .. && make
```

## usage

```bash
./pryst path/to/program.pst
```

## development status

work in progress:

- standard library
- advanced OOP features
- optimization
- module system

contributions welcome. feel free to open issues or submit PRs.

## acknowledgments

built with ANTLR4 and LLVM.
