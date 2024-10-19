cmake_minimum_required(VERSION 3.10)
project(PrystCompiler)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)
set(LLVM_DIR "/usr/local/lib/cmake/llvm")

add_definitions(${LLVM_DEFINITIONS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(ANTLR4_INCLUDE_DIR "/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/include/antlr4-runtime")
include_directories(${ANTLR4_INCLUDE_DIR})
link_directories(/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/lib)

add_custom_command(
    OUTPUT
        ${CMAKE_SOURCE_DIR}/src/generated/PrystLexer.cpp
        ${CMAKE_SOURCE_DIR}/src/generated/PrystParser.cpp
        ${CMAKE_SOURCE_DIR}/src/generated/PrystVisitor.cpp
        ${CMAKE_SOURCE_DIR}/src/generated/PrystBaseVisitor.cpp
        ${CMAKE_SOURCE_DIR}/src/generated/PrystLexer.h
        ${CMAKE_SOURCE_DIR}/src/generated/PrystParser.h
        ${CMAKE_SOURCE_DIR}/src/generated/PrystVisitor.h
        ${CMAKE_SOURCE_DIR}/src/generated/PrystBaseVisitor.h
    COMMAND
        antlr4 -Dlanguage=Cpp -no-listener -visitor -o ${CMAKE_SOURCE_DIR}/src/generated ${CMAKE_SOURCE_DIR}/Pryst.g4
    DEPENDS
        ${CMAKE_SOURCE_DIR}/Pryst.g4
)

file(GLOB GENERATED_SRC 
    "${CMAKE_SOURCE_DIR}/src/generated/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/generated/*.h"
)

add_custom_target(GenerateParser DEPENDS ${GENERATED_SRC})

# add_library(jit_compiler ${CMAKE_SOURCE_DIR}/src/jit/jit_compiler.cpp ${CMAKE_SOURCE_DIR}/src/jit/jit_compiler.hpp)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(pryst ${SOURCES})

add_dependencies(pryst GenerateParser)

target_sources(pryst PRIVATE ${SOURCES} ${GENERATED_SRC})

# Set include directories for the target
target_include_directories(pryst PRIVATE
    include
    src
    src/generated
    ${LLVM_INCLUDE_DIRS}
    ${ANTLR4_INCLUDE_DIR}
)

# Link LLVM libraries
llvm_map_components_to_libnames(LLVM_LIBS
    Core
    Support
    native
    OrcJIT
    MC
    MCJIT
    ExecutionEngine
    AsmParser
    AsmPrinter
    Target
    X86CodeGen
    X86AsmParser
    X86Desc
    X86Info
    AArch64CodeGen
    AArch64AsmParser
    AArch64Desc
    AArch64Info
)

# target_link_libraries(jit_compiler PRIVATE ${LLVM_LIBS} antlr4-runtime)
target_link_libraries(pryst PRIVATE ${LLVM_LIBS} antlr4-runtime)
