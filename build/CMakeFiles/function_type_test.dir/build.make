# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/pryst-workspace/pryst-tmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/pryst-workspace/pryst-tmp/build

# Include any dependencies generated for this target.
include CMakeFiles/function_type_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/function_type_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/function_type_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/function_type_test.dir/flags.make

CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o: CMakeFiles/function_type_test.dir/flags.make
CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o: ../tests/function_type_test.cpp
CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o: CMakeFiles/function_type_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/pryst-workspace/pryst-tmp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o -MF CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o.d -o CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o -c /home/ubuntu/pryst-workspace/pryst-tmp/tests/function_type_test.cpp

CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/pryst-workspace/pryst-tmp/tests/function_type_test.cpp > CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.i

CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/pryst-workspace/pryst-tmp/tests/function_type_test.cpp -o CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.s

# Object files for target function_type_test
function_type_test_OBJECTS = \
"CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o"

# External object files for target function_type_test
function_type_test_EXTERNAL_OBJECTS =

function_type_test: CMakeFiles/function_type_test.dir/tests/function_type_test.cpp.o
function_type_test: CMakeFiles/function_type_test.dir/build.make
function_type_test: liblibpryst.a
function_type_test: lib/libgtest.a
function_type_test: lib/libgtest_main.a
function_type_test: lib/libgtest.a
function_type_test: CMakeFiles/function_type_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/pryst-workspace/pryst-tmp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable function_type_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/function_type_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/function_type_test.dir/build: function_type_test
.PHONY : CMakeFiles/function_type_test.dir/build

CMakeFiles/function_type_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/function_type_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/function_type_test.dir/clean

CMakeFiles/function_type_test.dir/depend:
	cd /home/ubuntu/pryst-workspace/pryst-tmp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/pryst-workspace/pryst-tmp /home/ubuntu/pryst-workspace/pryst-tmp /home/ubuntu/pryst-workspace/pryst-tmp/build /home/ubuntu/pryst-workspace/pryst-tmp/build /home/ubuntu/pryst-workspace/pryst-tmp/build/CMakeFiles/function_type_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/function_type_test.dir/depend

