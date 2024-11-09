cmake_minimum_required(VERSION 3.10)
project(pryst)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM 20.0.0 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Find ANTLR
set(ANTLR4_ROOT /usr/local)
set(ANTLR4_INCLUDE_DIR ${ANTLR4_ROOT}/include/antlr4-runtime)
set(ANTLR4_LIBRARY_DIR ${ANTLR4_ROOT}/lib)
set(ANTLR4_EXECUTABLE ${ANTLR4_ROOT}/bin/antlr4)

message(STATUS "Configuration Summary:")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  LLVM Version: ${LLVM_PACKAGE_VERSION}")
message(STATUS "  LLVM Directory: ${LLVM_DIR}")
message(STATUS "  ANTLR4 Include Directory: ${ANTLR4_INCLUDE_DIR}")
message(STATUS "  ANTLR4 Library Directory: ${ANTLR4_LIBRARY_DIR}")
message(STATUS "  ANTLR4 Executable: ${ANTLR4_EXECUTABLE}")

# Add LLVM includes and definitions
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Add ANTLR includes
include_directories(${ANTLR4_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/generated)
link_directories(${ANTLR4_LIBRARY_DIR})

# Generate ANTLR parser
add_custom_target(GenerateParser
    COMMAND ${ANTLR4_EXECUTABLE} -Dlanguage=Cpp -no-listener -visitor -o ${CMAKE_CURRENT_SOURCE_DIR}/src/generated ${CMAKE_CURRENT_SOURCE_DIR}/PrystLexer.g4 ${CMAKE_CURRENT_SOURCE_DIR}/PrystParser.g4
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/PrystLexer.g4 ${CMAKE_CURRENT_SOURCE_DIR}/PrystParser.g4
)

# Add source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/codegen/*.cpp"
    "src/semantic/*.cpp"
    "src/utils/*.cpp"
    "src/generated/*.cpp"
)

# Create executable
add_executable(pryst ${SOURCES})
add_dependencies(pryst GenerateParser)

# Link libraries
llvm_map_components_to_libnames(LLVM_LIBS
    core
    support
    irreader
    codegen
    target
    mcjit
    native
)

target_link_libraries(pryst
    antlr4-runtime
    ${LLVM_LIBS}
)

# Include directories
target_include_directories(pryst PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/generated
)
