# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/w/srcRep/learnc++/build/final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/w/srcRep/learnc++/build/final

# Include any dependencies generated for this target.
include CMakeFiles/program_name.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/program_name.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/program_name.dir/flags.make

CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o: CMakeFiles/program_name.dir/flags.make
CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o: /home/w/srcRep/learnc++/src/final/so7.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/w/srcRep/learnc++/build/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o"
	clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o -c /home/w/srcRep/learnc++/src/final/so7.cpp

CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.i"
	clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/w/srcRep/learnc++/src/final/so7.cpp > CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.i

CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.s"
	clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/w/srcRep/learnc++/src/final/so7.cpp -o CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.s

CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o.requires:

.PHONY : CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o.requires

CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o.provides: CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o.requires
	$(MAKE) -f CMakeFiles/program_name.dir/build.make CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o.provides.build
.PHONY : CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o.provides

CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o.provides.build: CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o


# Object files for target program_name
program_name_OBJECTS = \
"CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o"

# External object files for target program_name
program_name_EXTERNAL_OBJECTS =

program_name: CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o
program_name: CMakeFiles/program_name.dir/build.make
program_name: CMakeFiles/program_name.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/w/srcRep/learnc++/build/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable program_name"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/program_name.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/program_name.dir/build: program_name

.PHONY : CMakeFiles/program_name.dir/build

CMakeFiles/program_name.dir/requires: CMakeFiles/program_name.dir/home/w/srcRep/learnc++/src/final/so7.cpp.o.requires

.PHONY : CMakeFiles/program_name.dir/requires

CMakeFiles/program_name.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/program_name.dir/cmake_clean.cmake
.PHONY : CMakeFiles/program_name.dir/clean

CMakeFiles/program_name.dir/depend:
	cd /home/w/srcRep/learnc++/build/final && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/w/srcRep/learnc++/build/final /home/w/srcRep/learnc++/build/final /home/w/srcRep/learnc++/build/final /home/w/srcRep/learnc++/build/final /home/w/srcRep/learnc++/build/final/CMakeFiles/program_name.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/program_name.dir/depend

