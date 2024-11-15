# Test configuration
cmake_minimum_required(VERSION 3.10)

# Enable testing
enable_testing()

# Test sources
set(TEST_SOURCES
    type_registry_test.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_registry.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_metadata.cpp
)

# Add test executable
add_executable(pryst_tests ${TEST_SOURCES})

# Include directories
target_include_directories(pryst_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
    ${ANTLR4_INCLUDE_DIR}
)

# Link against LLVM libraries and main library
target_link_libraries(pryst_tests PRIVATE
    ${LLVM_LIBS}
    antlr4-runtime
)

# Add test cases
add_test(NAME TypeRegistryTest
         COMMAND pryst_tests)

# Set test properties
set_tests_properties(TypeRegistryTest
    PROPERTIES
    ENVIRONMENT "PRYST_TEST_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
)

# Add compiler flags
target_compile_features(pryst_tests PRIVATE cxx_std_17)
target_compile_options(pryst_tests PRIVATE -Wall -Wextra)
