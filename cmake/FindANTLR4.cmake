# Find ANTLR4 C++ runtime library and include files
#
# The following variables are set:
# ANTLR4_FOUND - True if ANTLR4 was found
# ANTLR4_INCLUDE_DIRS - ANTLR4 include directories
# ANTLR4_LIBRARIES - ANTLR4 libraries to link against

find_path(ANTLR4_INCLUDE_DIR
    NAMES antlr4-runtime.h
    PATHS
        /usr/local/include/antlr4-runtime
        /usr/include/antlr4-runtime
)

find_library(ANTLR4_LIBRARY
    NAMES libantlr4-runtime.so.4.13.2
    PATHS
        /usr/local/lib
        /usr/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ANTLR4
    REQUIRED_VARS
        ANTLR4_INCLUDE_DIR
        ANTLR4_LIBRARY
)

if(ANTLR4_FOUND)
    set(ANTLR4_INCLUDE_DIRS ${ANTLR4_INCLUDE_DIR})
    set(ANTLR4_LIBRARIES ${ANTLR4_LIBRARY})
endif()

mark_as_advanced(ANTLR4_INCLUDE_DIR ANTLR4_LIBRARY)
