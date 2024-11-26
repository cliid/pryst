########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(antlr4-cppruntime_COMPONENT_NAMES "")
set(antlr4-cppruntime_FIND_DEPENDENCY_NAMES "")

########### VARIABLES #######################################################################
#############################################################################################
set(antlr4-cppruntime_PACKAGE_FOLDER_RELEASE "/home/ubuntu/.conan/data/antlr4-cppruntime/4.13.1/_/_/package/6557f18ca99c0b6a233f43db00e30efaa525e27e")
set(antlr4-cppruntime_BUILD_MODULES_PATHS_RELEASE )


set(antlr4-cppruntime_INCLUDE_DIRS_RELEASE "${antlr4-cppruntime_PACKAGE_FOLDER_RELEASE}/include"
			"${antlr4-cppruntime_PACKAGE_FOLDER_RELEASE}/include/antlr4-runtime")
set(antlr4-cppruntime_RES_DIRS_RELEASE )
set(antlr4-cppruntime_DEFINITIONS_RELEASE )
set(antlr4-cppruntime_SHARED_LINK_FLAGS_RELEASE )
set(antlr4-cppruntime_EXE_LINK_FLAGS_RELEASE )
set(antlr4-cppruntime_OBJECTS_RELEASE )
set(antlr4-cppruntime_COMPILE_DEFINITIONS_RELEASE )
set(antlr4-cppruntime_COMPILE_OPTIONS_C_RELEASE )
set(antlr4-cppruntime_COMPILE_OPTIONS_CXX_RELEASE )
set(antlr4-cppruntime_LIB_DIRS_RELEASE "${antlr4-cppruntime_PACKAGE_FOLDER_RELEASE}/lib")
set(antlr4-cppruntime_LIBS_RELEASE antlr4-runtime)
set(antlr4-cppruntime_SYSTEM_LIBS_RELEASE m pthread)
set(antlr4-cppruntime_FRAMEWORK_DIRS_RELEASE )
set(antlr4-cppruntime_FRAMEWORKS_RELEASE )
set(antlr4-cppruntime_BUILD_DIRS_RELEASE "${antlr4-cppruntime_PACKAGE_FOLDER_RELEASE}/")

# COMPOUND VARIABLES
set(antlr4-cppruntime_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${antlr4-cppruntime_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${antlr4-cppruntime_COMPILE_OPTIONS_C_RELEASE}>")
set(antlr4-cppruntime_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${antlr4-cppruntime_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${antlr4-cppruntime_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${antlr4-cppruntime_EXE_LINK_FLAGS_RELEASE}>")


set(antlr4-cppruntime_COMPONENTS_RELEASE )