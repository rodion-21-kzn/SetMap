# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/oznakban/SetMap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/oznakban/SetMap/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Containers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Containers.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Containers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Containers.dir/flags.make

CMakeFiles/Containers.dir/Map.cpp.o: CMakeFiles/Containers.dir/flags.make
CMakeFiles/Containers.dir/Map.cpp.o: /Users/oznakban/SetMap/Map.cpp
CMakeFiles/Containers.dir/Map.cpp.o: CMakeFiles/Containers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/oznakban/SetMap/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Containers.dir/Map.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Containers.dir/Map.cpp.o -MF CMakeFiles/Containers.dir/Map.cpp.o.d -o CMakeFiles/Containers.dir/Map.cpp.o -c /Users/oznakban/SetMap/Map.cpp

CMakeFiles/Containers.dir/Map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Containers.dir/Map.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/oznakban/SetMap/Map.cpp > CMakeFiles/Containers.dir/Map.cpp.i

CMakeFiles/Containers.dir/Map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Containers.dir/Map.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/oznakban/SetMap/Map.cpp -o CMakeFiles/Containers.dir/Map.cpp.s

# Object files for target Containers
Containers_OBJECTS = \
"CMakeFiles/Containers.dir/Map.cpp.o"

# External object files for target Containers
Containers_EXTERNAL_OBJECTS =

Containers: CMakeFiles/Containers.dir/Map.cpp.o
Containers: CMakeFiles/Containers.dir/build.make
Containers: CMakeFiles/Containers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/oznakban/SetMap/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Containers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Containers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Containers.dir/build: Containers
.PHONY : CMakeFiles/Containers.dir/build

CMakeFiles/Containers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Containers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Containers.dir/clean

CMakeFiles/Containers.dir/depend:
	cd /Users/oznakban/SetMap/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/oznakban/SetMap /Users/oznakban/SetMap /Users/oznakban/SetMap/cmake-build-debug /Users/oznakban/SetMap/cmake-build-debug /Users/oznakban/SetMap/cmake-build-debug/CMakeFiles/Containers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Containers.dir/depend

