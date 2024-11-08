# Utils library CMakeLists.txt
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(UTILS_SOURCES
    logger.cpp
)

# Create static library
add_library(pryst_utils STATIC ${UTILS_SOURCES})

# Set compiler flags
target_compile_options(pryst_utils PRIVATE
    -Wall
    -Wextra
    -frtti
    -fexceptions
)

# Include directories
target_include_directories(pryst_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

# Set output directory
set_target_properties(pryst_utils PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
