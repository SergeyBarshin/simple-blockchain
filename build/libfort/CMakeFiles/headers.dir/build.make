# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/build"

# Utility rule file for headers.

# Include any custom commands dependencies for this target.
include libfort/CMakeFiles/headers.dir/compiler_depend.make

# Include the progress variables for this target.
include libfort/CMakeFiles/headers.dir/progress.make

headers: libfort/CMakeFiles/headers.dir/build.make
.PHONY : headers

# Rule to build all files generated by this target.
libfort/CMakeFiles/headers.dir/build: headers
.PHONY : libfort/CMakeFiles/headers.dir/build

libfort/CMakeFiles/headers.dir/clean:
	cd "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/build/libfort" && $(CMAKE_COMMAND) -P CMakeFiles/headers.dir/cmake_clean.cmake
.PHONY : libfort/CMakeFiles/headers.dir/clean

libfort/CMakeFiles/headers.dir/depend:
	cd "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/src" "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/src/libfort" "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/build" "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/build/libfort" "/Users/sergey/Documents/BMSTU/2 sem/ПКШ/simple-blockchain/build/libfort/CMakeFiles/headers.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : libfort/CMakeFiles/headers.dir/depend

