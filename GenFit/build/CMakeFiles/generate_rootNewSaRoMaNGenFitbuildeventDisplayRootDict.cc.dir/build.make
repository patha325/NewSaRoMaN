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

# Utility rule file for generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.

# Include the progress variables for this target.
include CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/progress.make

CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc: eventDisplayRootDict.cc


eventDisplayRootDict.cc: ../eventDisplay/include/EventDisplay.h
eventDisplayRootDict.cc: ../eventDisplay/src/eventDisplayLinkDef.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/NewSaRoMaN/GenFit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating eventDisplayRootDict.cc, eventDisplayRootDict_rdict.pcm, eventDisplayRoot.rootmap"
	/root/root-build/bin/rootcling -f /root/NewSaRoMaN/GenFit/build/eventDisplayRootDict.cc -inlineInputHeader -rmf /root/NewSaRoMaN/GenFit/build/eventDisplayRoot.rootmap -rml libgenfit2.so -c -I/root/NewSaRoMaN/GenFit/core/include -I/root/NewSaRoMaN/GenFit/fitters/include -I/root/NewSaRoMaN/GenFit/eventDisplay/include -isystem/usr/local/include/eigen3 /root/NewSaRoMaN/GenFit/eventDisplay/include/EventDisplay.h /root/NewSaRoMaN/GenFit/eventDisplay/src/eventDisplayLinkDef.h

eventDisplayRootDict_rdict.pcm: eventDisplayRootDict.cc
	@$(CMAKE_COMMAND) -E touch_nocreate eventDisplayRootDict_rdict.pcm

eventDisplayRoot.rootmap: eventDisplayRootDict.cc
	@$(CMAKE_COMMAND) -E touch_nocreate eventDisplayRoot.rootmap

generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc: CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc
generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc: eventDisplayRootDict.cc
generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc: eventDisplayRootDict_rdict.pcm
generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc: eventDisplayRoot.rootmap
generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc: CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/build.make

.PHONY : generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc

# Rule to build all files generated by this target.
CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/build: generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc

.PHONY : CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/build

CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/clean

CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/depend:
	cd /root/NewSaRoMaN/GenFit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/NewSaRoMaN/GenFit /root/NewSaRoMaN/GenFit /root/NewSaRoMaN/GenFit/build /root/NewSaRoMaN/GenFit/build /root/NewSaRoMaN/GenFit/build/CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/generate_rootNewSaRoMaNGenFitbuildeventDisplayRootDict.cc.dir/depend
