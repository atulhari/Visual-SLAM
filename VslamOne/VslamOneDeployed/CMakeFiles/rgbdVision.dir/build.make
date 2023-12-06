# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /VslamOne

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /VslamOne/VslamOneDeployed

# Include any dependencies generated for this target.
include CMakeFiles/rgbdVision.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rgbdVision.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rgbdVision.dir/flags.make

CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.o: CMakeFiles/rgbdVision.dir/flags.make
CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.o: ../src/rgbdVision.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/VslamOne/VslamOneDeployed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.o -c /VslamOne/src/rgbdVision.cpp

CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /VslamOne/src/rgbdVision.cpp > CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.i

CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /VslamOne/src/rgbdVision.cpp -o CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.s

# Object files for target rgbdVision
rgbdVision_OBJECTS = \
"CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.o"

# External object files for target rgbdVision
rgbdVision_EXTERNAL_OBJECTS =

Targets/rgbdVision: CMakeFiles/rgbdVision.dir/src/rgbdVision.cpp.o
Targets/rgbdVision: CMakeFiles/rgbdVision.dir/build.make
Targets/rgbdVision: /usr/local/lib/libopencv_dnn.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_gapi.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_highgui.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_ml.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_objdetect.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_photo.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_stitching.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_video.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_videoio.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libpangolin.so
Targets/rgbdVision: /usr/local/lib/libopencv_imgcodecs.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_calib3d.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_features2d.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_flann.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_imgproc.so.4.2.0
Targets/rgbdVision: /usr/local/lib/libopencv_core.so.4.2.0
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libOpenGL.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libGLX.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libGLU.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libGLEW.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libEGL.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libSM.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libICE.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libX11.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libXext.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libOpenGL.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libGLX.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libGLU.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libGLEW.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libEGL.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libSM.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libICE.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libX11.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libXext.so
Targets/rgbdVision: /usr/lib/x86_64-linux-gnu/libjpeg.so
Targets/rgbdVision: /usr/local/lib/libfmt.a
Targets/rgbdVision: CMakeFiles/rgbdVision.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/VslamOne/VslamOneDeployed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Targets/rgbdVision"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rgbdVision.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rgbdVision.dir/build: Targets/rgbdVision

.PHONY : CMakeFiles/rgbdVision.dir/build

CMakeFiles/rgbdVision.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rgbdVision.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rgbdVision.dir/clean

CMakeFiles/rgbdVision.dir/depend:
	cd /VslamOne/VslamOneDeployed && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /VslamOne /VslamOne /VslamOne/VslamOneDeployed /VslamOne/VslamOneDeployed /VslamOne/VslamOneDeployed/CMakeFiles/rgbdVision.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rgbdVision.dir/depend

