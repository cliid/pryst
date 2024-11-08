# Test configuration
cmake_minimum_required(VERSION 3.10)

# Test sources
set(TEST_SOURCES
    test_runner.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_registry.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/type_metadata.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/reflection_api.cpp
)

# Add test executable
add_executable(pryst_tests ${TEST_SOURCES})

# Include directories
target_include_directories(pryst_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/include
    ${LLVM_INCLUDE_DIRS}
)

# Link against LLVM libraries and main library
target_link_libraries(pryst_tests PRIVATE
    ${llvm_libs}
    pryst_lib
)

# Enable testing
enable_testing()

# Add test cases
add_test(NAME type_reflection_test
         COMMAND pryst_tests ${CMAKE_CURRENT_SOURCE_DIR}/reflection/type_reflection_test.pst)
add_test(NAME inheritance_test
         COMMAND pryst_tests ${CMAKE_CURRENT_SOURCE_DIR}/reflection/inheritance_test.pst)
add_test(NAME type_conversion_test
         COMMAND pryst_tests ${CMAKE_CURRENT_SOURCE_DIR}/reflection/type_conversion_test.pst)

# Set test properties
set_tests_properties(type_reflection_test inheritance_test type_conversion_test
    PROPERTIES
    ENVIRONMENT "PRYST_TEST_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
)

# Add compiler flags
target_compile_features(pryst_tests PRIVATE cxx_std_17)
target_compile_options(pryst_tests PRIVATE -Wall -Wextra)
