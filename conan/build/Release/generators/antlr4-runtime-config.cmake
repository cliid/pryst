########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(antlr4-runtime_FIND_QUIETLY)
    set(antlr4-runtime_MESSAGE_MODE VERBOSE)
else()
    set(antlr4-runtime_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/antlr4-runtimeTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${antlr4-cppruntime_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(antlr4-runtime_VERSION_STRING "4.13.1")
set(antlr4-runtime_INCLUDE_DIRS ${antlr4-cppruntime_INCLUDE_DIRS_RELEASE} )
set(antlr4-runtime_INCLUDE_DIR ${antlr4-cppruntime_INCLUDE_DIRS_RELEASE} )
set(antlr4-runtime_LIBRARIES ${antlr4-cppruntime_LIBRARIES_RELEASE} )
set(antlr4-runtime_DEFINITIONS ${antlr4-cppruntime_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${antlr4-cppruntime_BUILD_MODULES_PATHS_RELEASE} )
    message(${antlr4-runtime_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


