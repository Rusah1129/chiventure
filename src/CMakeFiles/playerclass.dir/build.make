# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/cmake/3.13.4/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/3.13.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/simrenk/CS/cs220/chiventure/src/playerclass

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/simrenk/CS/cs220/chiventure/src

# Include any dependencies generated for this target.
include CMakeFiles/playerclass.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/playerclass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/playerclass.dir/flags.make

CMakeFiles/playerclass.dir/sandbox/player.c.o: CMakeFiles/playerclass.dir/flags.make
CMakeFiles/playerclass.dir/sandbox/player.c.o: playerclass/sandbox/player.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/simrenk/CS/cs220/chiventure/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/playerclass.dir/sandbox/player.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/playerclass.dir/sandbox/player.c.o   -c /home/simrenk/CS/cs220/chiventure/src/playerclass/sandbox/player.c

CMakeFiles/playerclass.dir/sandbox/player.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/playerclass.dir/sandbox/player.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/simrenk/CS/cs220/chiventure/src/playerclass/sandbox/player.c > CMakeFiles/playerclass.dir/sandbox/player.c.i

CMakeFiles/playerclass.dir/sandbox/player.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/playerclass.dir/sandbox/player.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/simrenk/CS/cs220/chiventure/src/playerclass/sandbox/player.c -o CMakeFiles/playerclass.dir/sandbox/player.c.s

# Object files for target playerclass
playerclass_OBJECTS = \
"CMakeFiles/playerclass.dir/sandbox/player.c.o"

# External object files for target playerclass
playerclass_EXTERNAL_OBJECTS =

libplayerclass.a: CMakeFiles/playerclass.dir/sandbox/player.c.o
libplayerclass.a: CMakeFiles/playerclass.dir/build.make
libplayerclass.a: CMakeFiles/playerclass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/simrenk/CS/cs220/chiventure/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libplayerclass.a"
	$(CMAKE_COMMAND) -P CMakeFiles/playerclass.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/playerclass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/playerclass.dir/build: libplayerclass.a

.PHONY : CMakeFiles/playerclass.dir/build

CMakeFiles/playerclass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/playerclass.dir/cmake_clean.cmake
.PHONY : CMakeFiles/playerclass.dir/clean

CMakeFiles/playerclass.dir/depend:
	cd /home/simrenk/CS/cs220/chiventure/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/simrenk/CS/cs220/chiventure/src/playerclass /home/simrenk/CS/cs220/chiventure/src/playerclass /home/simrenk/CS/cs220/chiventure/src /home/simrenk/CS/cs220/chiventure/src /home/simrenk/CS/cs220/chiventure/src/CMakeFiles/playerclass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/playerclass.dir/depend

