cmake_minimum_required(VERSION 3.10)
project(Pryst VERSION 1.0)

# Set C++17 as required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Find LLVM 14
find_package(LLVM 14 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Add LLVM flags and definitions
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Get LLVM library directory and add to link path
link_directories(/usr/lib/llvm-14/lib)

# Get LLVM library list from llvm-config
execute_process(
    COMMAND llvm-config-14 --libs
    OUTPUT_VARIABLE LLVM_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "LLVM Libs from llvm-config: ${LLVM_LIBS}")

# Find Boehm GC
find_package(PkgConfig REQUIRED)
pkg_check_modules(GC REQUIRED bdw-gc)
include_directories(${GC_INCLUDE_DIRS})
link_directories(${GC_LIBRARY_DIRS})

# Find Java for ANTLR
find_package(Java REQUIRED COMPONENTS Runtime)

# Set up ANTLR4 with platform-specific paths
if(DEFINED ENV{ANTLR4_ROOT})
    set(ANTLR4_ROOT $ENV{ANTLR4_ROOT})
else()
    if(APPLE)
        set(ANTLR4_ROOT "/usr/local")
    else()
        set(ANTLR4_ROOT "/usr/local")
    endif()
endif()

set(ANTLR4_JAR_LOCATION ${ANTLR4_ROOT}/lib/antlr-4.13.2-complete.jar)
set(ANTLR4_INCLUDE_DIR ${ANTLR4_ROOT}/include/antlr4-runtime)
if(APPLE)
    set(ANTLR4_RUNTIME_LIBRARIES ${ANTLR4_ROOT}/lib/libantlr4-runtime.dylib)
else()
    set(ANTLR4_RUNTIME_LIBRARIES ${ANTLR4_ROOT}/lib/libantlr4-runtime.so)
endif()

# Add ANTLR4 runtime library
add_library(antlr4_runtime SHARED IMPORTED)
set_target_properties(antlr4_runtime PROPERTIES
    IMPORTED_LOCATION ${ANTLR4_RUNTIME_LIBRARIES}
    INTERFACE_INCLUDE_DIRECTORIES ${ANTLR4_INCLUDE_DIR}
)

# Set up generated files directory
set(GENERATED_DIR "${CMAKE_SOURCE_DIR}/src/generated")
set(GENERATED_SRC
    ${GENERATED_DIR}/PrystLexer.cpp
    ${GENERATED_DIR}/PrystParser.cpp
    ${GENERATED_DIR}/PrystParserBaseVisitor.cpp
    ${GENERATED_DIR}/PrystParserVisitor.cpp
)

set(GENERATED_HEADERS
    ${GENERATED_DIR}/PrystLexer.h
    ${GENERATED_DIR}/PrystParser.h
    ${GENERATED_DIR}/PrystParserBaseVisitor.h
    ${GENERATED_DIR}/PrystParserVisitor.h
)

# Create custom target for generated files
add_custom_target(antlr4_generation
    COMMAND
        java -jar ${ANTLR4_JAR_LOCATION} -Dlanguage=Cpp -no-listener -visitor
        -package pryst
        -o ${GENERATED_DIR}
        ${CMAKE_SOURCE_DIR}/src/PrystLexer.g4
        ${CMAKE_SOURCE_DIR}/src/PrystParser.g4
    DEPENDS
        ${CMAKE_SOURCE_DIR}/src/PrystLexer.g4
        ${CMAKE_SOURCE_DIR}/src/PrystParser.g4
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/generated
    ${ANTLR4_INCLUDE_DIR}
)

# Add source files
set(SOURCE_FILES
    src/main.cpp
    src/compiler.cpp
    src/type_checker.cpp
    src/llvm_codegen.cpp
    src/runtime.cpp
    src/webserver.cpp
    src/types.cpp
    src/type_registry.cpp
    src/diagnostic_error_listener.cpp
)

# Add header files
set(HEADER_FILES
    src/diagnostic_error_listener.hpp
)

# Add main executable
add_executable(pryst
    ${SOURCE_FILES}
    ${GENERATED_SRC}
    ${HEADER_FILES}
)
add_dependencies(pryst antlr4_generation)

# Add test executables
add_executable(parser_test
    src/test/parser_test.cpp
    src/compiler.cpp
    src/type_checker.cpp
    src/llvm_codegen.cpp
    src/runtime.cpp
    src/types.cpp
    src/type_registry.cpp
    ${GENERATED_SRC}
)
add_dependencies(parser_test antlr4_generation)

add_executable(webserver_test
    src/test/webserver_test.cpp
    src/compiler.cpp
    src/type_checker.cpp
    src/llvm_codegen.cpp
    src/runtime.cpp
    src/webserver.cpp
    src/types.cpp
    src/type_registry.cpp
    src/diagnostic_error_listener.cpp
    ${GENERATED_SRC}
)
add_dependencies(webserver_test antlr4_generation)

# Link libraries
foreach(target pryst parser_test webserver_test)
    target_link_libraries(${target}
        antlr4_runtime
        LLVM-14
        ${GC_LIBRARIES}
    )

    target_include_directories(${target} PRIVATE
        ${GENERATED_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${ANTLR4_INCLUDE_DIR}
    )
endforeach()

# Create test directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/src/test)

# Copy test files to build directory
foreach(test_file
    parser_test.pst
    webserver_test.pst
    runtime_functions_test.pst
    test.pst
)
    configure_file(
        ${CMAKE_SOURCE_DIR}/src/test/${test_file}
        ${CMAKE_BINARY_DIR}/src/test/${test_file}
        COPYONLY
    )
endforeach()

# Add tests
add_test(NAME ParserTest COMMAND parser_test)
add_test(NAME WebServerTest COMMAND webserver_test)
