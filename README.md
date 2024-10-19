# Pryst Compiler

Welcome to the Pryst Compiler project! This is an exciting journey into the world of programming language design and implementation. Pryst is a custom language that combines simplicity with powerful features, aiming to provide a smooth coding experience.

## What is Pryst?

Pryst is a statically-typed, object-oriented language with a syntax inspired by TypeScript and C++. It supports:

- Basic types: int, float, bool, str
- Functions and classes
- Control structures: if-else, while, for
- Object-oriented programming with inheritance

## Project Structure

The compiler is built using C++ and leverages several key technologies:

- ANTLR4 for lexing and parsing
- LLVM for code generation and optimization
- CMake for build management

Key components include:

- `Pryst.g4`: The ANTLR4 grammar definition for Pryst
- `semantic_analyzer.cpp`: Performs semantic analysis on the AST
- `llvm_codegen.cpp`: Generates LLVM IR from the analyzed AST
- `jit_compiler.cpp`: Provides Just-In-Time compilation capabilities
- `aot_compiler.cpp`: Provides Ahead-Of-Time compilation capabilities

## Building the Project

To build the Pryst compiler:

1. Ensure you have CMake, ANTLR4, and LLVM installed.
2. Clone this repository.
3. Run the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

## Running Pryst Programs

After building, you can run Pryst programs using:

`./pryst path/to/your/program.pst --aot`

## Current State and Future Work
This project is a work in progress. While basic functionality is implemented, there's still much to explore and improve. Some areas for future development include:

- Expanding the standard library
- Implementing more advanced OOP features
- Optimizing the code generation process
- Adding support for modules and imports

## Contributing
We're always excited to welcome new contributors! If you're interested in helping develop Pryst, feel free to fork the repository, make your changes, and submit a pull request.

## Acknowledgments
This project wouldn't be possible without the amazing open-source communities behind ANTLR4, LLVM, and CMake. Their tools and documentation have been invaluable in bringing Pryst to life.

_Thank you for your interest in Pryst. Happy coding!_

