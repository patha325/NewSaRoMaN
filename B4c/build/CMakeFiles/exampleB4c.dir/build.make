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
CMAKE_SOURCE_DIR = /root/NewSaRoMaN/B4c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/NewSaRoMaN/B4c/build

# Include any dependencies generated for this target.
include CMakeFiles/exampleB4c.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exampleB4c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exampleB4c.dir/flags.make

CMakeFiles/exampleB4c.dir/exampleB4c.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/exampleB4c.cc.o: ../exampleB4c.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exampleB4c.dir/exampleB4c.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/exampleB4c.cc.o -c /root/NewSaRoMaN/B4c/exampleB4c.cc

CMakeFiles/exampleB4c.dir/exampleB4c.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/exampleB4c.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/exampleB4c.cc > CMakeFiles/exampleB4c.dir/exampleB4c.cc.i

CMakeFiles/exampleB4c.dir/exampleB4c.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/exampleB4c.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/exampleB4c.cc -o CMakeFiles/exampleB4c.dir/exampleB4c.cc.s

CMakeFiles/exampleB4c.dir/exampleB4c.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/exampleB4c.cc.o.requires

CMakeFiles/exampleB4c.dir/exampleB4c.cc.o.provides: CMakeFiles/exampleB4c.dir/exampleB4c.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/exampleB4c.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/exampleB4c.cc.o.provides

CMakeFiles/exampleB4c.dir/exampleB4c.cc.o.provides.build: CMakeFiles/exampleB4c.dir/exampleB4c.cc.o


CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o: ../src/B4PrimaryGeneratorAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o -c /root/NewSaRoMaN/B4c/src/B4PrimaryGeneratorAction.cc

CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/B4PrimaryGeneratorAction.cc > CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.i

CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/B4PrimaryGeneratorAction.cc -o CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.s

CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o.requires

CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o.provides: CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o.provides

CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o


CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o: ../src/B4RunAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o -c /root/NewSaRoMaN/B4c/src/B4RunAction.cc

CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/B4RunAction.cc > CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.i

CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/B4RunAction.cc -o CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.s

CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o.requires

CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o.provides: CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o.provides

CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o


CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o: ../src/B4cActionInitialization.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o -c /root/NewSaRoMaN/B4c/src/B4cActionInitialization.cc

CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/B4cActionInitialization.cc > CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.i

CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/B4cActionInitialization.cc -o CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.s

CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o.requires

CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o.provides: CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o.provides

CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o


CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o: ../src/B4cCalorHit.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o -c /root/NewSaRoMaN/B4c/src/B4cCalorHit.cc

CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/B4cCalorHit.cc > CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.i

CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/B4cCalorHit.cc -o CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.s

CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o.requires

CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o.provides: CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o.provides

CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o


CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o: ../src/B4cCalorimeterSD.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o -c /root/NewSaRoMaN/B4c/src/B4cCalorimeterSD.cc

CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/B4cCalorimeterSD.cc > CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.i

CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/B4cCalorimeterSD.cc -o CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.s

CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o.requires

CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o.provides: CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o.provides

CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o


CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o: ../src/B4cDetectorConstruction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o -c /root/NewSaRoMaN/B4c/src/B4cDetectorConstruction.cc

CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/B4cDetectorConstruction.cc > CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.i

CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/B4cDetectorConstruction.cc -o CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.s

CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o.requires

CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o.provides: CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o.provides

CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o


CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o: ../src/B4cEventAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o -c /root/NewSaRoMaN/B4c/src/B4cEventAction.cc

CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/B4cEventAction.cc > CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.i

CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/B4cEventAction.cc -o CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.s

CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o.requires

CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o.provides: CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o.provides

CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o


CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o: ../src/MindBarHit.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o -c /root/NewSaRoMaN/B4c/src/MindBarHit.cc

CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/MindBarHit.cc > CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.i

CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/MindBarHit.cc -o CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.s

CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o.requires

CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o.provides: CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o.provides

CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o


CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o: ../src/MindBarSD.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o -c /root/NewSaRoMaN/B4c/src/MindBarSD.cc

CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/MindBarSD.cc > CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.i

CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/MindBarSD.cc -o CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.s

CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o.requires

CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o.provides: CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o.provides

CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o


CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o: CMakeFiles/exampleB4c.dir/flags.make
CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o: ../src/MindFieldMapR.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o -c /root/NewSaRoMaN/B4c/src/MindFieldMapR.cc

CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/NewSaRoMaN/B4c/src/MindFieldMapR.cc > CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.i

CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/NewSaRoMaN/B4c/src/MindFieldMapR.cc -o CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.s

CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o.requires:

.PHONY : CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o.requires

CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o.provides: CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o.requires
	$(MAKE) -f CMakeFiles/exampleB4c.dir/build.make CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o.provides.build
.PHONY : CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o.provides

CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o.provides.build: CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o


# Object files for target exampleB4c
exampleB4c_OBJECTS = \
"CMakeFiles/exampleB4c.dir/exampleB4c.cc.o" \
"CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o" \
"CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o" \
"CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o" \
"CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o" \
"CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o" \
"CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o" \
"CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o" \
"CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o" \
"CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o" \
"CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o"

# External object files for target exampleB4c
exampleB4c_EXTERNAL_OBJECTS =

exampleB4c: CMakeFiles/exampleB4c.dir/exampleB4c.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o
exampleB4c: CMakeFiles/exampleB4c.dir/build.make
exampleB4c: /root/geant4/geant4-install/lib/libG4Tree.so
exampleB4c: /root/geant4/geant4-install/lib/libG4GMocren.so
exampleB4c: /root/geant4/geant4-install/lib/libG4visHepRep.so
exampleB4c: /root/geant4/geant4-install/lib/libG4RayTracer.so
exampleB4c: /root/geant4/geant4-install/lib/libG4VRML.so
exampleB4c: /root/geant4/geant4-install/lib/libG4OpenGL.so
exampleB4c: /root/geant4/geant4-install/lib/libG4gl2ps.so
exampleB4c: /root/geant4/geant4-install/lib/libG4interfaces.so
exampleB4c: /root/geant4/geant4-install/lib/libG4persistency.so
exampleB4c: /root/geant4/geant4-install/lib/libG4error_propagation.so
exampleB4c: /root/geant4/geant4-install/lib/libG4readout.so
exampleB4c: /root/geant4/geant4-install/lib/libG4physicslists.so
exampleB4c: /root/geant4/geant4-install/lib/libG4parmodels.so
exampleB4c: /root/geant4/geant4-install/lib/libG4FR.so
exampleB4c: /root/geant4/geant4-install/lib/libG4vis_management.so
exampleB4c: /root/geant4/geant4-install/lib/libG4modeling.so
exampleB4c: /usr/lib/x86_64-linux-gnu/libSM.so
exampleB4c: /usr/lib/x86_64-linux-gnu/libICE.so
exampleB4c: /usr/lib/x86_64-linux-gnu/libX11.so
exampleB4c: /usr/lib/x86_64-linux-gnu/libXext.so
exampleB4c: /usr/lib/x86_64-linux-gnu/libGL.so
exampleB4c: /usr/lib/x86_64-linux-gnu/libGLU.so
exampleB4c: /usr/lib/x86_64-linux-gnu/libXmu.so
exampleB4c: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.9.5
exampleB4c: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.9.5
exampleB4c: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.9.5
exampleB4c: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.9.5
exampleB4c: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.9.5
exampleB4c: /usr/lib/x86_64-linux-gnu/libxerces-c.so
exampleB4c: /root/geant4/geant4-install/lib/libG4run.so
exampleB4c: /root/geant4/geant4-install/lib/libG4event.so
exampleB4c: /root/geant4/geant4-install/lib/libG4tracking.so
exampleB4c: /root/geant4/geant4-install/lib/libG4processes.so
exampleB4c: /root/geant4/geant4-install/lib/libG4analysis.so
exampleB4c: /root/geant4/geant4-install/lib/libG4expat.so
exampleB4c: /root/geant4/geant4-install/lib/libG4zlib.so
exampleB4c: /root/geant4/geant4-install/lib/libG4digits_hits.so
exampleB4c: /root/geant4/geant4-install/lib/libG4track.so
exampleB4c: /root/geant4/geant4-install/lib/libG4particles.so
exampleB4c: /root/geant4/geant4-install/lib/libG4geometry.so
exampleB4c: /root/geant4/geant4-install/lib/libG4materials.so
exampleB4c: /root/geant4/geant4-install/lib/libG4graphics_reps.so
exampleB4c: /root/geant4/geant4-install/lib/libG4intercoms.so
exampleB4c: /root/geant4/geant4-install/lib/libG4global.so
exampleB4c: /root/geant4/geant4-install/lib/libG4clhep.so
exampleB4c: CMakeFiles/exampleB4c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/NewSaRoMaN/B4c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable exampleB4c"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exampleB4c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exampleB4c.dir/build: exampleB4c

.PHONY : CMakeFiles/exampleB4c.dir/build

CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/exampleB4c.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/B4PrimaryGeneratorAction.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/B4RunAction.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/B4cActionInitialization.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/B4cCalorHit.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/B4cCalorimeterSD.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/B4cDetectorConstruction.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/B4cEventAction.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/MindBarHit.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/MindBarSD.cc.o.requires
CMakeFiles/exampleB4c.dir/requires: CMakeFiles/exampleB4c.dir/src/MindFieldMapR.cc.o.requires

.PHONY : CMakeFiles/exampleB4c.dir/requires

CMakeFiles/exampleB4c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exampleB4c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exampleB4c.dir/clean

CMakeFiles/exampleB4c.dir/depend:
	cd /root/NewSaRoMaN/B4c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/NewSaRoMaN/B4c /root/NewSaRoMaN/B4c /root/NewSaRoMaN/B4c/build /root/NewSaRoMaN/B4c/build /root/NewSaRoMaN/B4c/build/CMakeFiles/exampleB4c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exampleB4c.dir/depend

