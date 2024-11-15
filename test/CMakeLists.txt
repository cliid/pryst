# Test configuration
cmake_minimum_required(VERSION 3.10)

# Enable testing
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)

# Create type registry test executable
add_executable(type_registry_test
    type_registry_test.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_registry.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_metadata.cpp
)

# Include directories for type registry test
target_include_directories(type_registry_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

# Link against LLVM libraries and GTest
target_link_libraries(type_registry_test PRIVATE
    LLVM-14
    GTest::GTest
    GTest::Main
)

# Add test case
add_test(NAME TypeRegistryTest
         COMMAND type_registry_test)

# Set test properties
set_tests_properties(TypeRegistryTest
    PROPERTIES
    ENVIRONMENT "PRYST_TEST_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
)

# Add compiler flags
target_compile_features(type_registry_test PRIVATE cxx_std_17)
target_compile_options(type_registry_test PRIVATE -Wall -Wextra)

# Define TESTING macro for conditional compilation
target_compile_definitions(type_registry_test PRIVATE TESTING=1)
