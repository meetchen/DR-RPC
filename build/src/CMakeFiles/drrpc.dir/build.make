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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/duanran/workSpace/C++_WorkSpace/DR-RPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build

# Include any dependencies generated for this target.
include src/CMakeFiles/drrpc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/drrpc.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/drrpc.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/drrpc.dir/flags.make

src/CMakeFiles/drrpc.dir/drrpcapplication.cc.o: src/CMakeFiles/drrpc.dir/flags.make
src/CMakeFiles/drrpc.dir/drrpcapplication.cc.o: ../src/drrpcapplication.cc
src/CMakeFiles/drrpc.dir/drrpcapplication.cc.o: src/CMakeFiles/drrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/drrpc.dir/drrpcapplication.cc.o"
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/drrpc.dir/drrpcapplication.cc.o -MF CMakeFiles/drrpc.dir/drrpcapplication.cc.o.d -o CMakeFiles/drrpc.dir/drrpcapplication.cc.o -c /home/duanran/workSpace/C++_WorkSpace/DR-RPC/src/drrpcapplication.cc

src/CMakeFiles/drrpc.dir/drrpcapplication.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drrpc.dir/drrpcapplication.cc.i"
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duanran/workSpace/C++_WorkSpace/DR-RPC/src/drrpcapplication.cc > CMakeFiles/drrpc.dir/drrpcapplication.cc.i

src/CMakeFiles/drrpc.dir/drrpcapplication.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drrpc.dir/drrpcapplication.cc.s"
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duanran/workSpace/C++_WorkSpace/DR-RPC/src/drrpcapplication.cc -o CMakeFiles/drrpc.dir/drrpcapplication.cc.s

src/CMakeFiles/drrpc.dir/rpcprovider.cc.o: src/CMakeFiles/drrpc.dir/flags.make
src/CMakeFiles/drrpc.dir/rpcprovider.cc.o: ../src/rpcprovider.cc
src/CMakeFiles/drrpc.dir/rpcprovider.cc.o: src/CMakeFiles/drrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/drrpc.dir/rpcprovider.cc.o"
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/drrpc.dir/rpcprovider.cc.o -MF CMakeFiles/drrpc.dir/rpcprovider.cc.o.d -o CMakeFiles/drrpc.dir/rpcprovider.cc.o -c /home/duanran/workSpace/C++_WorkSpace/DR-RPC/src/rpcprovider.cc

src/CMakeFiles/drrpc.dir/rpcprovider.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drrpc.dir/rpcprovider.cc.i"
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duanran/workSpace/C++_WorkSpace/DR-RPC/src/rpcprovider.cc > CMakeFiles/drrpc.dir/rpcprovider.cc.i

src/CMakeFiles/drrpc.dir/rpcprovider.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drrpc.dir/rpcprovider.cc.s"
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duanran/workSpace/C++_WorkSpace/DR-RPC/src/rpcprovider.cc -o CMakeFiles/drrpc.dir/rpcprovider.cc.s

# Object files for target drrpc
drrpc_OBJECTS = \
"CMakeFiles/drrpc.dir/drrpcapplication.cc.o" \
"CMakeFiles/drrpc.dir/rpcprovider.cc.o"

# External object files for target drrpc
drrpc_EXTERNAL_OBJECTS =

src/libdrrpc.so: src/CMakeFiles/drrpc.dir/drrpcapplication.cc.o
src/libdrrpc.so: src/CMakeFiles/drrpc.dir/rpcprovider.cc.o
src/libdrrpc.so: src/CMakeFiles/drrpc.dir/build.make
src/libdrrpc.so: src/CMakeFiles/drrpc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libdrrpc.so"
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/drrpc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/drrpc.dir/build: src/libdrrpc.so
.PHONY : src/CMakeFiles/drrpc.dir/build

src/CMakeFiles/drrpc.dir/clean:
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src && $(CMAKE_COMMAND) -P CMakeFiles/drrpc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/drrpc.dir/clean

src/CMakeFiles/drrpc.dir/depend:
	cd /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/duanran/workSpace/C++_WorkSpace/DR-RPC /home/duanran/workSpace/C++_WorkSpace/DR-RPC/src /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src /home/duanran/workSpace/C++_WorkSpace/DR-RPC/build/src/CMakeFiles/drrpc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/drrpc.dir/depend
