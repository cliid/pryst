cmake_minimum_required(VERSION 3.10)
project(PrystCompiler)

# Allow overriding the compiler, default to system clang
if(NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER clang)
endif()
if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER clang++)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Find LLVM package, allow overriding LLVM_DIR
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/llvm-20" "/usr/local/opt/llvm@20" "/usr/local/llvm-20")
find_package(LLVM 20 REQUIRED CONFIG)

if(NOT LLVM_FOUND)
    message(FATAL_ERROR "LLVM 20 not found. Please install LLVM 20 or set LLVM_DIR to the correct path.")
else()
    message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
endif()

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Allow overriding ANTLR4 include and library paths
if(NOT ANTLR4_INCLUDE_DIR)
    set(ANTLR4_INCLUDE_DIR "/usr/local/include/antlr4-runtime")
endif()
if(NOT ANTLR4_LIBRARY_DIR)
    set(ANTLR4_LIBRARY_DIR "/usr/local/lib")
endif()
include_directories(${ANTLR4_INCLUDE_DIR})
link_directories(${ANTLR4_LIBRARY_DIR})

# Verify ANTLR4 runtime library exists
find_library(ANTLR4_RUNTIME_LIBRARY antlr4-runtime HINTS ${ANTLR4_LIBRARY_DIR})
if(NOT ANTLR4_RUNTIME_LIBRARY)
    message(FATAL_ERROR "ANTLR4 runtime library not found. Please install or set ANTLR4_LIBRARY_DIR to the correct path.")
endif()

# Check for ANTLR4 executable
find_program(ANTLR4_EXECUTABLE antlr4)
if(NOT ANTLR4_EXECUTABLE)
    message(FATAL_ERROR "ANTLR4 executable not found. Please ensure it is installed and in your PATH.")
endif()

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
        ${ANTLR4_EXECUTABLE} -Dlanguage=Cpp -no-listener -visitor -o ${CMAKE_SOURCE_DIR}/src/generated ${CMAKE_SOURCE_DIR}/Pryst.g4
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
    MCParser
    Object
    BitWriter
    Analysis
    CodeGen
    BitReader
)

# target_link_libraries(jit_compiler PRIVATE ${LLVM_LIBS} antlr4-runtime)
target_link_libraries(pryst PRIVATE ${LLVM_LIBS} antlr4-runtime)

# Configuration summary
message(STATUS "Configuration Summary:")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  LLVM Version: ${LLVM_PACKAGE_VERSION}")
message(STATUS "  LLVM Directory: ${LLVM_DIR}")
message(STATUS "  ANTLR4 Include Directory: ${ANTLR4_INCLUDE_DIR}")
message(STATUS "  ANTLR4 Library Directory: ${ANTLR4_LIBRARY_DIR}")
message(STATUS "  ANTLR4 Executable: ${ANTLR4_EXECUTABLE}")
