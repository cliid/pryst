cmake_minimum_required(VERSION 3.10)
project(pryst)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add GTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

# Create library target
add_library(libpryst
    include/scope_manager.hpp
    include/type_registry.hpp
    include/type.hpp
    include/type_checker.hpp
    src/type_checker.cpp
)
set_target_properties(libpryst PROPERTIES LINKER_LANGUAGE CXX)

# Create test executables
enable_testing()
add_executable(scope_manager_test
    tests/scope_manager_test.cpp
)
target_link_libraries(scope_manager_test
    libpryst
    gtest
    gtest_main
)

add_executable(type_checker_test
    tests/type_checker_test.cpp
)
target_link_libraries(type_checker_test
    libpryst
    gtest
    gtest_main
)

add_executable(error_chain_test
    tests/error_chain_test.cpp
)
target_link_libraries(error_chain_test
    libpryst
    gtest
    gtest_main
)

add_executable(type_coercion_test
    tests/type_coercion_test.cpp
)
target_link_libraries(type_coercion_test
    libpryst
    gtest
    gtest_main
)

add_executable(scope_inheritance_test
    tests/scope_inheritance_test.cpp
)
target_link_libraries(scope_inheritance_test
    libpryst
    gtest
    gtest_main
)

add_executable(null_safety_test
    tests/null_safety_test.cpp
)
target_link_libraries(null_safety_test
    libpryst
    gtest
    gtest_main
)

add_executable(type_inference_test
    tests/type_inference_test.cpp
)
target_link_libraries(type_inference_test
    libpryst
    gtest
    gtest_main
)

add_executable(complex_error_chain_test
    tests/complex_error_chain_test.cpp
)
target_link_libraries(complex_error_chain_test
    libpryst
    gtest
    gtest_main
)

add_executable(error_transformation_test
    tests/error_transformation_test.cpp
)
target_link_libraries(error_transformation_test
    libpryst
    gtest
    gtest_main
)

add_executable(async_error_handling_test
    tests/async_error_handling_test.cpp
)
target_link_libraries(async_error_handling_test
    libpryst
    gtest
    gtest_main
)

add_executable(concurrent_error_handling_test
    tests/concurrent_error_handling_test.cpp
)
target_link_libraries(concurrent_error_handling_test
    libpryst
    gtest
    gtest_main
)

add_executable(generic_type_error_test
    tests/generic_type_error_test.cpp
)
target_link_libraries(generic_type_error_test
    libpryst
    gtest
    gtest_main
)

add_executable(recursive_type_error_test
    tests/recursive_type_error_test.cpp
)
target_link_libraries(recursive_type_error_test
    libpryst
    gtest
    gtest_main
)

add_executable(union_type_error_test
    tests/union_type_error_test.cpp
)
target_link_libraries(union_type_error_test
    libpryst
    gtest
    gtest_main
)

add_executable(parameterized_type_error_test
    tests/parameterized_type_error_test.cpp
)
target_link_libraries(parameterized_type_error_test
    libpryst
    gtest
    gtest_main
)

add_executable(intersection_type_error_test
    tests/intersection_type_error_test.cpp
)
target_link_libraries(intersection_type_error_test
    libpryst
    gtest
    gtest_main
)

add_executable(higher_kinded_type_error_test
    tests/higher_kinded_type_error_test.cpp
)
target_link_libraries(higher_kinded_type_error_test
    libpryst
    gtest
    gtest_main
)

add_executable(multi_type_arithmetic_test
    tests/multi_type_arithmetic_test.cpp
)
target_link_libraries(multi_type_arithmetic_test
    libpryst
    gtest
    gtest_main
)

add_executable(type_promotion_test
    tests/type_promotion_test.cpp
)
target_link_libraries(type_promotion_test
    libpryst
    gtest
    gtest_main
)

add_executable(function_type_test
    tests/function_type_test.cpp
)
target_link_libraries(function_type_test
    libpryst
    gtest
    gtest_main
)

add_executable(array_type_test
    tests/array_type_test.cpp
)
target_link_libraries(array_type_test
    libpryst
    gtest
    gtest_main
)

add_test(NAME scope_manager_test COMMAND scope_manager_test)
add_test(NAME type_checker_test COMMAND type_checker_test)
add_test(NAME error_chain_test COMMAND error_chain_test)
add_test(NAME type_coercion_test COMMAND type_coercion_test)
add_test(NAME scope_inheritance_test COMMAND scope_inheritance_test)
add_test(NAME null_safety_test COMMAND null_safety_test)
add_test(NAME type_inference_test COMMAND type_inference_test)
add_test(NAME complex_error_chain_test COMMAND complex_error_chain_test)
add_test(NAME multi_type_arithmetic_test COMMAND multi_type_arithmetic_test)
add_test(NAME type_promotion_test COMMAND type_promotion_test)
add_test(NAME function_type_test COMMAND function_type_test)
add_test(NAME error_transform_test COMMAND error_transformation_test)
add_test(NAME async_error_test COMMAND async_error_handling_test)
add_test(NAME concurrent_error_test COMMAND concurrent_error_handling_test)
add_test(NAME generic_type_test COMMAND generic_type_error_test)
add_test(NAME recursive_type_test COMMAND recursive_type_error_test)
add_test(NAME union_type_test COMMAND union_type_error_test)
add_test(NAME intersection_type_test COMMAND intersection_type_error_test)
add_test(NAME parameterized_type_test COMMAND parameterized_type_error_test)
add_test(NAME higher_kinded_type_test COMMAND higher_kinded_type_error_test)
add_test(NAME array_type_test COMMAND array_type_test)
