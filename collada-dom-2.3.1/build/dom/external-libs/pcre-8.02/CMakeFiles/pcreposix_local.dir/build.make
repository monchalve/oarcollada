# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build

# Include any dependencies generated for this target.
include dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/depend.make

# Include the progress variables for this target.
include dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/progress.make

# Include the compile flags for this target's objects.
include dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/flags.make

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o: dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/flags.make
dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o: ../dom/external-libs/pcre-8.02/pcreposix.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o"
	cd /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/dom/external-libs/pcre-8.02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/pcreposix_local.dir/pcreposix.c.o   -c /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/dom/external-libs/pcre-8.02/pcreposix.c

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pcreposix_local.dir/pcreposix.c.i"
	cd /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/dom/external-libs/pcre-8.02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/dom/external-libs/pcre-8.02/pcreposix.c > CMakeFiles/pcreposix_local.dir/pcreposix.c.i

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pcreposix_local.dir/pcreposix.c.s"
	cd /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/dom/external-libs/pcre-8.02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/dom/external-libs/pcre-8.02/pcreposix.c -o CMakeFiles/pcreposix_local.dir/pcreposix.c.s

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.requires:
.PHONY : dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.requires

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.provides: dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.requires
	$(MAKE) -f dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/build.make dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.provides.build
.PHONY : dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.provides

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.provides.build: dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o
.PHONY : dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.provides.build

# Object files for target pcreposix_local
pcreposix_local_OBJECTS = \
"CMakeFiles/pcreposix_local.dir/pcreposix.c.o"

# External object files for target pcreposix_local
pcreposix_local_EXTERNAL_OBJECTS =

dom/external-libs/pcre-8.02/libpcreposix_local.a: dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o
dom/external-libs/pcre-8.02/libpcreposix_local.a: dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/build.make
dom/external-libs/pcre-8.02/libpcreposix_local.a: dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libpcreposix_local.a"
	cd /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/dom/external-libs/pcre-8.02 && $(CMAKE_COMMAND) -P CMakeFiles/pcreposix_local.dir/cmake_clean_target.cmake
	cd /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/dom/external-libs/pcre-8.02 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pcreposix_local.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/build: dom/external-libs/pcre-8.02/libpcreposix_local.a
.PHONY : dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/build

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/requires: dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/pcreposix.c.o.requires
.PHONY : dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/requires

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/clean:
	cd /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/dom/external-libs/pcre-8.02 && $(CMAKE_COMMAND) -P CMakeFiles/pcreposix_local.dir/cmake_clean.cmake
.PHONY : dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/clean

dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/depend:
	cd /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1 /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/dom/external-libs/pcre-8.02 /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/dom/external-libs/pcre-8.02 /Users/anmorales1/Desktop/OAR:COLLADA/collada-dom-2.3.1/build/dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : dom/external-libs/pcre-8.02/CMakeFiles/pcreposix_local.dir/depend
