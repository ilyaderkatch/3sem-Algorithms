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
CMAKE_SOURCE_DIR = /home/dalex/Desktop/mr_bubblegum/task3/problemC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dalex/Desktop/mr_bubblegum/task3/problemC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/problemC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/problemC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/problemC.dir/flags.make

CMakeFiles/problemC.dir/main.cpp.o: CMakeFiles/problemC.dir/flags.make
CMakeFiles/problemC.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalex/Desktop/mr_bubblegum/task3/problemC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/problemC.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/problemC.dir/main.cpp.o -c /home/dalex/Desktop/mr_bubblegum/task3/problemC/main.cpp

CMakeFiles/problemC.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/problemC.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dalex/Desktop/mr_bubblegum/task3/problemC/main.cpp > CMakeFiles/problemC.dir/main.cpp.i

CMakeFiles/problemC.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/problemC.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dalex/Desktop/mr_bubblegum/task3/problemC/main.cpp -o CMakeFiles/problemC.dir/main.cpp.s

# Object files for target problemC
problemC_OBJECTS = \
"CMakeFiles/problemC.dir/main.cpp.o"

# External object files for target problemC
problemC_EXTERNAL_OBJECTS =

problemC: CMakeFiles/problemC.dir/main.cpp.o
problemC: CMakeFiles/problemC.dir/build.make
problemC: CMakeFiles/problemC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dalex/Desktop/mr_bubblegum/task3/problemC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable problemC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/problemC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/problemC.dir/build: problemC

.PHONY : CMakeFiles/problemC.dir/build

CMakeFiles/problemC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/problemC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/problemC.dir/clean

CMakeFiles/problemC.dir/depend:
	cd /home/dalex/Desktop/mr_bubblegum/task3/problemC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dalex/Desktop/mr_bubblegum/task3/problemC /home/dalex/Desktop/mr_bubblegum/task3/problemC /home/dalex/Desktop/mr_bubblegum/task3/problemC/cmake-build-debug /home/dalex/Desktop/mr_bubblegum/task3/problemC/cmake-build-debug /home/dalex/Desktop/mr_bubblegum/task3/problemC/cmake-build-debug/CMakeFiles/problemC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/problemC.dir/depend

