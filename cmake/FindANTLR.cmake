find_path(ANTLR_INCLUDE_DIR
  NAMES antlr4-runtime.h
  PATHS
    ${ANTLR4_INCLUDE_DIR}
    /opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/include/antlr4-runtime
  PATH_SUFFIXES antlr4-runtime
)

find_library(ANTLR_LIBRARY
  NAMES 
    antlr4-runtime
    libantlr4-runtime.so
    libantlr4-runtime.dylib
  PATHS
    /opt/homebrew/Cellar/antlr4-cpp-runtime/4.13.2/lib
    /usr/local/lib
    /usr/lib
    /usr/lib/x86_64-linux-gnu
  PATH_SUFFIXES
    antlr4-runtime
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ANTLR DEFAULT_MSG ANTLR_LIBRARY ANTLR_INCLUDE_DIR)

mark_as_advanced(ANTLR_INCLUDE_DIR ANTLR_LIBRARY)

set(ANTLR_LIBRARIES ${ANTLR_LIBRARY})
set(ANTLR_INCLUDE_DIRS ${ANTLR_INCLUDE_DIR})
