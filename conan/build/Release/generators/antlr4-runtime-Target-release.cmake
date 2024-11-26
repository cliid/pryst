# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(antlr4-cppruntime_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(antlr4-cppruntime_FRAMEWORKS_FOUND_RELEASE "${antlr4-cppruntime_FRAMEWORKS_RELEASE}" "${antlr4-cppruntime_FRAMEWORK_DIRS_RELEASE}")

set(antlr4-cppruntime_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET antlr4-cppruntime_DEPS_TARGET)
    add_library(antlr4-cppruntime_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET antlr4-cppruntime_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${antlr4-cppruntime_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${antlr4-cppruntime_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### antlr4-cppruntime_DEPS_TARGET to all of them
conan_package_library_targets("${antlr4-cppruntime_LIBS_RELEASE}"    # libraries
                              "${antlr4-cppruntime_LIB_DIRS_RELEASE}" # package_libdir
                              antlr4-cppruntime_DEPS_TARGET
                              antlr4-cppruntime_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "antlr4-cppruntime")    # package_name

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${antlr4-cppruntime_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET antlr4_static
                 PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${antlr4-cppruntime_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${antlr4-cppruntime_LIBRARIES_TARGETS}>
                 APPEND)

    if("${antlr4-cppruntime_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET antlr4_static
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     antlr4-cppruntime_DEPS_TARGET
                     APPEND)
    endif()

    set_property(TARGET antlr4_static
                 PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${antlr4-cppruntime_LINKER_FLAGS_RELEASE}> APPEND)
    set_property(TARGET antlr4_static
                 PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${antlr4-cppruntime_INCLUDE_DIRS_RELEASE}> APPEND)
    set_property(TARGET antlr4_static
                 PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${antlr4-cppruntime_COMPILE_DEFINITIONS_RELEASE}> APPEND)
    set_property(TARGET antlr4_static
                 PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${antlr4-cppruntime_COMPILE_OPTIONS_RELEASE}> APPEND)

########## For the modules (FindXXX)
set(antlr4-cppruntime_LIBRARIES_RELEASE antlr4_static)
