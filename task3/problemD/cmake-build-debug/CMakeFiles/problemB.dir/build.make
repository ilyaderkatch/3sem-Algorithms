# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/98/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/98/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dalex/Desktop/mr_bubblegum/task3/problemD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dalex/Desktop/mr_bubblegum/task3/problemD/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/problemB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/problemB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/problemB.dir/flags.make

CMakeFiles/problemB.dir/main.cpp.o: CMakeFiles/problemB.dir/flags.make
CMakeFiles/problemB.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalex/Desktop/mr_bubblegum/task3/problemD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/problemB.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/problemB.dir/main.cpp.o -c /home/dalex/Desktop/mr_bubblegum/task3/problemD/main.cpp

CMakeFiles/problemB.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/problemB.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dalex/Desktop/mr_bubblegum/task3/problemD/main.cpp > CMakeFiles/problemB.dir/main.cpp.i

CMakeFiles/problemB.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/problemB.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dalex/Desktop/mr_bubblegum/task3/problemD/main.cpp -o CMakeFiles/problemB.dir/main.cpp.s

# Object files for target problemB
problemB_OBJECTS = \
"CMakeFiles/problemB.dir/main.cpp.o"

# External object files for target problemB
problemB_EXTERNAL_OBJECTS =

problemB: CMakeFiles/problemB.dir/main.cpp.o
problemB: CMakeFiles/problemB.dir/build.make
problemB: CMakeFiles/problemB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dalex/Desktop/mr_bubblegum/task3/problemD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable problemB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/problemB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/problemB.dir/build: problemB

.PHONY : CMakeFiles/problemB.dir/build

CMakeFiles/problemB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/problemB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/problemB.dir/clean

CMakeFiles/problemB.dir/depend:
	cd /home/dalex/Desktop/mr_bubblegum/task3/problemD/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dalex/Desktop/mr_bubblegum/task3/problemD /home/dalex/Desktop/mr_bubblegum/task3/problemD /home/dalex/Desktop/mr_bubblegum/task3/problemD/cmake-build-debug /home/dalex/Desktop/mr_bubblegum/task3/problemD/cmake-build-debug /home/dalex/Desktop/mr_bubblegum/task3/problemD/cmake-build-debug/CMakeFiles/problemB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/problemB.dir/depend

