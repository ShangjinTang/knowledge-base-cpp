# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/sol/.local/share/rtx/installs/cmake/3.26.5/bin/cmake

# The command to remove a file.
RM = /home/sol/.local/share/rtx/installs/cmake/3.26.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sol/github/myrepos/cpp/modern_c++_template/advanced

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sol/github/myrepos/cpp/modern_c++_template/advanced

# Utility rule file for format-sources.

# Include any custom commands dependencies for this target.
include CMakeFiles/format-sources.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/format-sources.dir/progress.make

CMakeFiles/format-sources:
	clang-format --style=file -i /home/sol/github/myrepos/cpp/modern_c++_template/advanced/CMakeFiles/3.26.5/CompilerIdCXX/CMakeCXXCompilerId.cpp /home/sol/github/myrepos/cpp/modern_c++_template/advanced/apphello/src/apphello.cpp /home/sol/github/myrepos/cpp/modern_c++_template/advanced/build/CMakeFiles/3.26.5/CompilerIdCXX/CMakeCXXCompilerId.cpp /home/sol/github/myrepos/cpp/modern_c++_template/advanced/libhello/src/libhello.cpp /home/sol/github/myrepos/cpp/modern_c++_template/advanced/libhello/test/test_libhello.cpp

format-sources: CMakeFiles/format-sources
format-sources: CMakeFiles/format-sources.dir/build.make
.PHONY : format-sources

# Rule to build all files generated by this target.
CMakeFiles/format-sources.dir/build: format-sources
.PHONY : CMakeFiles/format-sources.dir/build

CMakeFiles/format-sources.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/format-sources.dir/cmake_clean.cmake
.PHONY : CMakeFiles/format-sources.dir/clean

CMakeFiles/format-sources.dir/depend:
	cd /home/sol/github/myrepos/cpp/modern_c++_template/advanced && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sol/github/myrepos/cpp/modern_c++_template/advanced /home/sol/github/myrepos/cpp/modern_c++_template/advanced /home/sol/github/myrepos/cpp/modern_c++_template/advanced /home/sol/github/myrepos/cpp/modern_c++_template/advanced /home/sol/github/myrepos/cpp/modern_c++_template/advanced/CMakeFiles/format-sources.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/format-sources.dir/depend

