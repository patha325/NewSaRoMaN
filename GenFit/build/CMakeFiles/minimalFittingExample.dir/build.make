# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /root/NewSaRoMaN/GenFit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/NewSaRoMaN/GenFit/build

# Include any dependencies generated for this target.
include CMakeFiles/minimalFittingExample.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/minimalFittingExample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minimalFittingExample.dir/flags.make

CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o: CMakeFiles/minimalFittingExample.dir/flags.make
CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o: ../test/minimalFittingExample/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/GenFit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o -c /root/NewSaRoMaN/GenFit/test/minimalFittingExample/main.cc

CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/GenFit/test/minimalFittingExample/main.cc > CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.i

CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/GenFit/test/minimalFittingExample/main.cc -o CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.s

CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o.requires:

.PHONY : CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o.requires

CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o.provides: CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o.requires
	$(MAKE) -f CMakeFiles/minimalFittingExample.dir/build.make CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o.provides.build
.PHONY : CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o.provides

CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o.provides.build: CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o


# Object files for target minimalFittingExample
minimalFittingExample_OBJECTS = \
"CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o"

# External object files for target minimalFittingExample
minimalFittingExample_EXTERNAL_OBJECTS =

bin/minimalFittingExample: CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o
bin/minimalFittingExample: CMakeFiles/minimalFittingExample.dir/build.make
bin/minimalFittingExample: lib/libgenfit2.so.2.2.0
bin/minimalFittingExample: CMakeFiles/minimalFittingExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/NewSaRoMaN/GenFit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/minimalFittingExample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minimalFittingExample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minimalFittingExample.dir/build: bin/minimalFittingExample

.PHONY : CMakeFiles/minimalFittingExample.dir/build

CMakeFiles/minimalFittingExample.dir/requires: CMakeFiles/minimalFittingExample.dir/test/minimalFittingExample/main.cc.o.requires

.PHONY : CMakeFiles/minimalFittingExample.dir/requires

CMakeFiles/minimalFittingExample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minimalFittingExample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minimalFittingExample.dir/clean

CMakeFiles/minimalFittingExample.dir/depend:
	cd /root/NewSaRoMaN/GenFit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/NewSaRoMaN/GenFit /root/NewSaRoMaN/GenFit /root/NewSaRoMaN/GenFit/build /root/NewSaRoMaN/GenFit/build /root/NewSaRoMaN/GenFit/build/CMakeFiles/minimalFittingExample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minimalFittingExample.dir/depend
