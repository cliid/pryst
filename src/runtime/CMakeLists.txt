add_library(pryst_runtime STATIC
    string_format.cpp
    string_conversion.cpp
)

target_include_directories(pryst_runtime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(pryst_runtime PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)
