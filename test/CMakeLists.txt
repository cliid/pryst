cmake_minimum_required(VERSION 3.10)

# Add test executable
add_executable(module_tests
    test_runner.cpp
)

# Link with main project libraries
target_link_libraries(module_tests
    PRIVATE
    pryst_lib
    ${LLVM_LIBS}
    ${ANTLR4_RUNTIME}
)

# Include directories
target_include_directories(module_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${LLVM_INCLUDE_DIRS}
    ${ANTLR4_INCLUDE_DIRS}
)

# Copy test modules to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/modules
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add test target
add_test(NAME ModuleSystemTests
         COMMAND module_tests
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Set test properties
set_tests_properties(ModuleSystemTests PROPERTIES
    ENVIRONMENT "PRYST_TEST_DIR=${CMAKE_CURRENT_SOURCE_DIR}/modules"
)
