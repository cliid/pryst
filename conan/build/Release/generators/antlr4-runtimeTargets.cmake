# Load the debug and release variables
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
file(GLOB DATA_FILES "${_DIR}/antlr4-runtime-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${antlr4-cppruntime_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${antlr4-runtime_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET antlr4_static)
    add_library(antlr4_static INTERFACE IMPORTED)
    message(${antlr4-runtime_MESSAGE_MODE} "Conan: Target declared 'antlr4_static'")
endif()
# Load the debug and release library finders
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
file(GLOB CONFIG_FILES "${_DIR}/antlr4-runtime-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()