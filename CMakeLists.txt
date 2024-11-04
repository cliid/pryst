cmake_minimum_required(VERSION 3.10)
project(PrystCompiler)

# Use environment variables for compiler settings if available
if(DEFINED ENV{CC})
    set(CMAKE_C_COMPILER $ENV{CC})
else()
    set(CMAKE_C_COMPILER clang)
endif()

if(DEFINED ENV{CXX})
    set(CMAKE_CXX_COMPILER $ENV{CXX})
else()
    set(CMAKE_CXX_COMPILER clang++)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Create lists of source files that need different RTTI settings
set(LLVM_SOURCES
    # Empty - all files need RTTI for our type system
)

set(ANTLR_SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/aot/aot_compiler.cpp
    ${CMAKE_SOURCE_DIR}/src/jit/jit_compiler.cpp
    ${CMAKE_SOURCE_DIR}/src/generated/PrystLexer.cpp
    ${CMAKE_SOURCE_DIR}/src/generated/PrystParser.cpp
    ${CMAKE_SOURCE_DIR}/src/generated/PrystVisitor.cpp
    ${CMAKE_SOURCE_DIR}/src/generated/PrystBaseVisitor.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/llvm_codegen.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/builtin_functions.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/visitor_antlr.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/string_utils.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/reflection_api.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_utils.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_registry.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_metadata.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/llvm_utils.cpp
    ${CMAKE_SOURCE_DIR}/src/semantic/semantic_analyzer.cpp
    ${CMAKE_SOURCE_DIR}/src/semantic/symbol_table.cpp
    ${CMAKE_SOURCE_DIR}/src/semantic/type_info.cpp
    ${CMAKE_SOURCE_DIR}/src/semantic/module_loader.cpp
    ${CMAKE_SOURCE_DIR}/src/diagnostic/diagnostic_visitor.cpp
)

# Set RTTI flags based on file types
set_source_files_properties(
    ${LLVM_SOURCES}
    PROPERTIES COMPILE_FLAGS "-fno-rtti"
)

set_source_files_properties(
    ${ANTLR_SOURCES}
    PROPERTIES COMPILE_FLAGS "-frtti"
)

# Use LLVM_DIR from environment if available
if(DEFINED ENV{LLVM_DIR})
    set(LLVM_DIR "$ENV{LLVM_DIR}" CACHE PATH "Path to LLVM CMake config")
    message(STATUS "Using LLVM_DIR from environment: $ENV{LLVM_DIR}")
    # Try to find LLVMConfig.cmake in common locations relative to LLVM_DIR
    list(APPEND CMAKE_PREFIX_PATH
        "$ENV{LLVM_DIR}"
        "$ENV{LLVM_DIR}/lib/cmake/llvm"
        "$ENV{LLVM_DIR}/lib/cmake"
        "$ENV{LLVM_DIR}/share/llvm/cmake"
        "/usr/lib/llvm-20/lib/cmake/llvm"
        "/usr/local/llvm-20/lib/cmake/llvm"
        "/opt/llvm-20/lib/cmake/llvm"
    )
else()
    if(APPLE)
        set(LLVM_DIR "/usr/local" CACHE PATH "Path to LLVM CMake config")
    else()
        set(LLVM_DIR "/usr/lib/llvm-20/lib/cmake/llvm" CACHE PATH "Path to LLVM CMake config")
    endif()
endif()

# Find LLVM package and check version
find_package(LLVM REQUIRED CONFIG)

# Verify LLVM version is 20.0.0
if(NOT LLVM_PACKAGE_VERSION VERSION_EQUAL "20.0.0")
    message(FATAL_ERROR "LLVM 20.0.0 is required. Found version ${LLVM_PACKAGE_VERSION}")
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Set ANTLR paths based on platform and try multiple common locations
if(APPLE)
    set(ANTLR4_SEARCH_PATHS
        "/opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2"
        "/usr/local/opt/antlr4-cpp-runtime"
        "/opt/homebrew/opt/antlr4-cpp-runtime"
        "/usr/local"
    )
else()
    set(ANTLR4_SEARCH_PATHS
        "/usr/local"
        "/usr"
        "/usr/local/opt/antlr4-cpp-runtime"
    )
endif()

# Find ANTLR4 runtime in search paths
foreach(base_path ${ANTLR4_SEARCH_PATHS})
    if(EXISTS "${base_path}/include/antlr4-runtime")
        set(ANTLR4_INCLUDE_DIR "${base_path}/include/antlr4-runtime" CACHE PATH "ANTLR4 include directory")
        set(ANTLR4_LIBRARY_DIR "${base_path}/lib" CACHE PATH "ANTLR4 library directory")
        break()
    endif()
endforeach()

# Allow override through environment variables
if(DEFINED ENV{ANTLR4_INCLUDE_DIR})
    set(ANTLR4_INCLUDE_DIR "$ENV{ANTLR4_INCLUDE_DIR}" CACHE PATH "ANTLR4 include directory" FORCE)
endif()
if(DEFINED ENV{ANTLR4_LIBRARY_DIR})
    set(ANTLR4_LIBRARY_DIR "$ENV{ANTLR4_LIBRARY_DIR}" CACHE PATH "ANTLR4 library directory" FORCE)
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

# Add source files
set(SOURCES
    ${LLVM_SOURCES}
    ${ANTLR_SOURCES}
)

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

# Update LLVM libraries based on architecture
llvm_map_components_to_libnames(LLVM_LIBS
    Core Support native
    MC MCParser MCDisassembler Object BitWriter Analysis CodeGen BitReader
    OrcJIT MCJIT ExecutionEngine RuntimeDyld
    AsmParser AsmPrinter Target TargetParser
    Passes IPO TransformUtils
    X86CodeGen X86AsmParser X86Desc X86Info X86TargetMCA
)

# Add architecture-specific libraries based on target
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    # X86 libraries already included above
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    list(REMOVE_ITEM LLVM_LIBS
        X86CodeGen X86AsmParser X86Desc X86Info X86TargetMCA
    )
    list(APPEND LLVM_LIBS
        AArch64CodeGen AArch64AsmParser AArch64Desc AArch64Info AArch64TargetMCA
    )
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
    # list(APPEND LLVM_LIBS)
endif()

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
