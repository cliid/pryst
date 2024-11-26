# Unified test suite for Pryst
add_executable(pryst_tests
    test_runner.cpp
)

target_sources(pryst_tests
    PRIVATE
    core/cpp/parser_test.cpp
    core/cpp/io_test.cpp
    core/cpp/map_type_test.cpp
    core/cpp/type_ops_test.cpp
    core/cpp/array_type_test.cpp
    core/cpp/runtime/io_test.cpp
    web/webserver_test.cpp
    type_checker_error_propagation_test.cpp
    error_propagation_integration_test.cpp
    error_propagation_complex_test.cpp
    error_propagation_nullable_test.cpp
)

target_link_libraries(pryst_tests
    PRIVATE
    libpryst
    gtest
    gtest_main
    pthread
)

target_include_directories(pryst_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/runtime
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party
)

# Enable testing
enable_testing()
add_test(NAME pryst_tests COMMAND pryst_tests)
