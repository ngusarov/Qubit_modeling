# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\cmake-build-debug-mingw-1

# Include any dependencies generated for this target.
include CMakeFiles/Qubit_modeling.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Qubit_modeling.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Qubit_modeling.dir/flags.make

CMakeFiles/Qubit_modeling.dir/main.cpp.obj: CMakeFiles/Qubit_modeling.dir/flags.make
CMakeFiles/Qubit_modeling.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\cmake-build-debug-mingw-1\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Qubit_modeling.dir/main.cpp.obj"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Qubit_modeling.dir\main.cpp.obj -c C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\main.cpp

CMakeFiles/Qubit_modeling.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Qubit_modeling.dir/main.cpp.i"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\main.cpp > CMakeFiles\Qubit_modeling.dir\main.cpp.i

CMakeFiles/Qubit_modeling.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Qubit_modeling.dir/main.cpp.s"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\main.cpp -o CMakeFiles\Qubit_modeling.dir\main.cpp.s

# Object files for target Qubit_modeling
Qubit_modeling_OBJECTS = \
"CMakeFiles/Qubit_modeling.dir/main.cpp.obj"

# External object files for target Qubit_modeling
Qubit_modeling_EXTERNAL_OBJECTS =

Qubit_modeling.exe: CMakeFiles/Qubit_modeling.dir/main.cpp.obj
Qubit_modeling.exe: CMakeFiles/Qubit_modeling.dir/build.make
Qubit_modeling.exe: CMakeFiles/Qubit_modeling.dir/linklibs.rsp
Qubit_modeling.exe: CMakeFiles/Qubit_modeling.dir/objects1.rsp
Qubit_modeling.exe: CMakeFiles/Qubit_modeling.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\cmake-build-debug-mingw-1\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Qubit_modeling.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Qubit_modeling.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Qubit_modeling.dir/build: Qubit_modeling.exe

.PHONY : CMakeFiles/Qubit_modeling.dir/build

CMakeFiles/Qubit_modeling.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Qubit_modeling.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Qubit_modeling.dir/clean

CMakeFiles/Qubit_modeling.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\cmake-build-debug-mingw-1 C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\cmake-build-debug-mingw-1 C:\Users\Kolya\OneDrive\C++_coding\Qubit_modeling\cmake-build-debug-mingw-1\CMakeFiles\Qubit_modeling.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Qubit_modeling.dir/depend

