cmake_minimum_required(VERSION 3.10)
project(PrystCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)

# Find LibEdit package
find_package(PkgConfig REQUIRED)
pkg_check_modules(LibEdit REQUIRED libedit)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(pryst ${SOURCES})

# Set include directories for the target
target_include_directories(pryst PRIVATE
    include
    src
    ${LLVM_INCLUDE_DIRS}
    ${LibEdit_INCLUDE_DIRS}
)

# Add compiler definitions
target_compile_definitions(pryst PRIVATE ${LLVM_DEFINITIONS})

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
)
target_link_libraries(pryst PRIVATE ${LLVM_LIBS} ${LibEdit_LIBRARIES})
