cmake_minimum_required(VERSION 3.10)
project(Pryst VERSION 1.0)

# Set up system paths
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

# Set C++17 as required and enable debug symbols
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -frtti")

# Enable testing
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Find LLVM 14
find_package(LLVM 14 REQUIRED CONFIG)
if(NOT LLVM_FOUND OR NOT LLVM_PACKAGE_VERSION VERSION_EQUAL "14.0.6")
    message(FATAL_ERROR "LLVM 14.0.x is required. Found version: ${LLVM_PACKAGE_VERSION}")
endif()
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

# Find Boehm GC and verify version
find_package(PkgConfig REQUIRED)
pkg_check_modules(GC REQUIRED bdw-gc>=8.0.0)
if(NOT GC_FOUND)
    message(FATAL_ERROR "Boehm GC >= 8.0.0 is required")
endif()
message(STATUS "Found Boehm GC ${GC_VERSION}")
include_directories(${GC_INCLUDE_DIRS})
link_directories(${GC_LIBRARY_DIRS})

# Handle cpp-httplib and verify version
if(NOT EXISTS "/usr/local/include/httplib/httplib.h")
    message(FATAL_ERROR "cpp-httplib header not found. Please install it manually:
    git clone https://github.com/yhirose/cpp-httplib.git
    cd cpp-httplib
    sudo mkdir -p /usr/local/include/httplib
    sudo cp httplib.h /usr/local/include/httplib/")
endif()

include_directories("/usr/local/include")

# Find Java for ANTLR
find_package(Java REQUIRED COMPONENTS Runtime)

# Find system ANTLR4 Runtime
find_package(PkgConfig REQUIRED)
pkg_check_modules(ANTLR4 REQUIRED antlr4-runtime>=4.13.1)
message(STATUS "Found ANTLR4 Runtime: ${ANTLR4_VERSION}")

# Set up ANTLR JAR and verify version
set(ANTLR4_JAR_LOCATION /usr/local/lib/antlr-4.13.1-complete.jar)
execute_process(
    COMMAND java -jar ${ANTLR4_JAR_LOCATION} -version
    OUTPUT_VARIABLE ANTLR4_TOOL_VERSION
    ERROR_VARIABLE ANTLR4_TOOL_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
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
    ${ANTLR4_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/src/type_system/core
    ${CMAKE_SOURCE_DIR}/src/type_system/advanced
    ${CMAKE_SOURCE_DIR}/src/error_handling/core
    ${CMAKE_SOURCE_DIR}/src/error_handling/advanced
    ${CMAKE_SOURCE_DIR}/src/runtime/core
)

# Add source files (excluding main.cpp for library use)
set(LIB_SOURCE_FILES
    src/compiler.cpp
    src/type_checker.cpp
    src/type_system/core/llvm_codegen.cpp
    src/type_system/core/types.cpp
    src/type_system/core/type_registry.cpp
    src/error_handling/core/diagnostic_error_listener.cpp
    src/error_handling/core/error_handler.cpp
    src/error_handling/core/error_chain.cpp
    src/type_system/core/type_inference.cpp
    src/runtime/core/runtime.cpp
    src/runtime/core/runtime_registry.cpp
    src/runtime/core/web.cpp
    src/runtime/core/web_types.cpp
    src/runtime/core/web_impl.cpp
    src/runtime/core/map_impl.cpp
    src/runtime/core/array_impl.cpp
    src/runtime/core/string_impl.cpp
    src/runtime/core/error_impl.cpp
    src/runtime/core/error_bindings.cpp
    src/runtime/core/string_bindings.cpp
    src/runtime/core/array_bindings.cpp
    src/runtime/core/map_bindings.cpp
    src/runtime/core/io_impl.cpp
    src/runtime/core/io_bindings.cpp
    src/runtime/core/runtime_type_ops.cpp
    src/runtime/core/type_ops.cpp
    src/type_system/advanced/type_checker_advanced.cpp
    src/error_handling/advanced/chain/error_chain_advanced.cpp
    src/error_handling/advanced/propagation/error_propagation.cpp
    src/error_handling/advanced/transformation/error_transform.cpp
    src/type_system/advanced/inference/type_inference_advanced.cpp
    src/type_system/advanced/validation/type_validation.cpp
)

# Create library target
add_library(libpryst STATIC ${LIB_SOURCE_FILES} ${GENERATED_SRC} ${HEADER_FILES})
add_dependencies(libpryst antlr4_generation)
set_target_properties(libpryst PROPERTIES OUTPUT_NAME "pryst")

# Link libraries to libpryst
target_link_libraries(libpryst
    ${ANTLR4_LIBRARIES}
    LLVM-14
    ${GC_LIBRARIES}
    pthread
    dl
    ${HTTPLIB_LIBRARIES}
)

# Add header files
set(HEADER_FILES
    src/error_handling/core/diagnostic_error_listener.hpp
    src/error_handling/core/error.hpp
    src/error_handling/core/error_chain.hpp
    src/error_handling/core/error_handler.hpp
    src/type_system/core/llvm_codegen.hpp
    src/type_system/core/types.hpp
    src/type_system/core/type_registry.hpp
    src/type_system/core/type_inference.hpp
    src/runtime/core/runtime.hpp
    src/runtime/core/runtime_registry.hpp
    src/runtime/core/web.hpp
    src/runtime/core/web_types.hpp
    src/runtime/core/web_impl.hpp
    src/runtime/core/map_impl.hpp
    src/runtime/core/array_impl.hpp
    src/runtime/core/string_impl.hpp
    src/runtime/core/error_impl.hpp
    src/runtime/core/io_impl.hpp
    src/runtime/core/runtime_type_ops.hpp
    src/runtime/core/type_ops.hpp
)

# Add main executable
add_executable(pryst
    src/main.cpp
    ${LIB_SOURCE_FILES}
    ${GENERATED_SRC}
    ${HEADER_FILES}
)
add_dependencies(pryst antlr4_generation)

# Add unified test executable
add_executable(run_tests
    tests/test_runner.cpp
    tests/error_handling_test.cpp
    tests/nullable_test.cpp
    tests/nullable_type_test.cpp
    tests/type_checker_tests.cpp
    tests/core/cpp/parser_test.cpp
    tests/core/cpp/map_type_test.cpp
    tests/core/cpp/type_ops_test.cpp
    tests/core/cpp/type_operators_test.cpp
    tests/core/cpp/io_test.cpp
    tests/core/cpp/nullable_pst_test.cpp
    tests/core/cpp/function_type_test.cpp
    tests/core/cpp/array_type_test.cpp
    tests/core/cpp/runtime/io_test.cpp
    tests/web/webserver_test.cpp
    tests/advanced/type_system_test.cpp
    tests/advanced/error_handling_test.cpp
    tests/advanced/type_system_integration_test.cpp
    tests/advanced/type_checker_integration_test.cpp
    tests/advanced/error_chain_integration_test.cpp
    tests/advanced/llvm_type_integration_test.cpp
    tests/advanced/scope_integration_test.cpp
    tests/advanced/web_type_integration_test.cpp
    ${LIB_SOURCE_FILES}
    ${GENERATED_SRC}
)
add_dependencies(run_tests antlr4_generation)

# Link libraries for main executable and unified test target
foreach(target pryst run_tests)
    target_link_libraries(${target}
        ${ANTLR4_LIBRARIES}
        LLVM-14
        ${GC_LIBRARIES}
        pthread
        dl
        ${HTTPLIB_LIBRARIES}
    )

    target_include_directories(${target} PRIVATE
        ${GENERATED_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${ANTLR4_INCLUDE_DIRS}
    )
endforeach()

# Add GTest only to run_tests target
target_link_libraries(run_tests
    ${GTEST_LIBRARIES}
    gtest
    gtest_main
)

target_include_directories(run_tests PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

# Create unified test directory structure
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

# Add unified tests directory
add_subdirectory(tests)

# Copy test files during configure phase
file(GLOB_RECURSE ALL_PST_FILES
    "${CMAKE_SOURCE_DIR}/tests/**/*.pst"
)

# Copy each test file to the build directory
foreach(TEST_FILE ${ALL_PST_FILES})
    get_filename_component(FILENAME ${TEST_FILE} NAME)
    configure_file(${TEST_FILE} ${CMAKE_BINARY_DIR}/tests/${FILENAME} COPYONLY)
endforeach()

# Add unified test suite
add_test(NAME PrystTests COMMAND run_tests)

# Set test environment
set_tests_properties(PrystTests PROPERTIES
    ENVIRONMENT "TEST_FILES_DIR=${CMAKE_BINARY_DIR}/tests"
)
