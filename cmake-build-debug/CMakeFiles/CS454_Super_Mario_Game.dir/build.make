# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /Users/george/Desktop/Courses/CS454/Project2023

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CS454_Super_Mario_Game.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CS454_Super_Mario_Game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CS454_Super_Mario_Game.dir/flags.make

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o: ../Engine/Src/timing.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/timing.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/timing.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/timing.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.s

CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o: ../app.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/app.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/app.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/app.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.s

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o: ../Engine/Src/terrain.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/terrain.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/terrain.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/terrain.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.s

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o: ../Engine/game.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/Engine/game.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/Engine/game.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/Engine/game.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.s

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o: ../Engine/Src/rendering.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/rendering.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/rendering.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/rendering.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.s

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o: ../Engine/Src/input.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/input.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/input.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/input.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.s

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o: ../Engine/Src/animation.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/animation.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/animation.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/animation.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.s

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o: ../Engine/Src/sprite.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/sprite.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/sprite.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/sprite.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.s

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/flags.make
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o: ../Engine/Src/sound.cpp
CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o: CMakeFiles/CS454_Super_Mario_Game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o -MF CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o.d -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o -c /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/sound.cpp

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/sound.cpp > CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.i

CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/george/Desktop/Courses/CS454/Project2023/Engine/Src/sound.cpp -o CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.s

# Object files for target CS454_Super_Mario_Game
CS454_Super_Mario_Game_OBJECTS = \
"CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o" \
"CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o" \
"CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o" \
"CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o" \
"CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o" \
"CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o" \
"CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o" \
"CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o" \
"CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o"

# External object files for target CS454_Super_Mario_Game
CS454_Super_Mario_Game_EXTERNAL_OBJECTS =

CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/timing.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/app.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/terrain.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/Engine/game.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/rendering.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/input.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/animation.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sprite.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/Engine/Src/sound.cpp.o
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/build.make
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_acodec.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_acodec.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_acodec.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_audio.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_audio.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_audio.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_color.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_color.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_color.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_dialog.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_dialog.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_dialog.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_font.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_font.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_font.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_image.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_image.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_image.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_main.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_main.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_main.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_memfile.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_memfile.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_memfile.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_physfs.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_physfs.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_physfs.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_primitives.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_primitives.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_primitives.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_ttf.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_ttf.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_ttf.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_video.5.2.7.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_video.5.2.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: /usr/local/Cellar/allegro/5.2.7.0/lib/liballegro_video.dylib
CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game: CMakeFiles/CS454_Super_Mario_Game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CS454_Super_Mario_Game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CS454_Super_Mario_Game.dir/build: CS454_Super_Mario_Game.app/Contents/MacOS/CS454_Super_Mario_Game
.PHONY : CMakeFiles/CS454_Super_Mario_Game.dir/build

CMakeFiles/CS454_Super_Mario_Game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CS454_Super_Mario_Game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CS454_Super_Mario_Game.dir/clean

CMakeFiles/CS454_Super_Mario_Game.dir/depend:
	cd /Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/george/Desktop/Courses/CS454/Project2023 /Users/george/Desktop/Courses/CS454/Project2023 /Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug /Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug /Users/george/Desktop/Courses/CS454/Project2023/cmake-build-debug/CMakeFiles/CS454_Super_Mario_Game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CS454_Super_Mario_Game.dir/depend

