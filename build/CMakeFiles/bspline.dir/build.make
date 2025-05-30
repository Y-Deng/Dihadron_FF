# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /root/DengYongjie/BsplineInterpolation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/DengYongjie/BsplineInterpolation/build

# Include any dependencies generated for this target.
include CMakeFiles/bspline.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bspline.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bspline.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bspline.dir/flags.make

CMakeFiles/bspline.dir/src/BSpline.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/BSpline.cc.o: ../src/BSpline.cc
CMakeFiles/bspline.dir/src/BSpline.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bspline.dir/src/BSpline.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/BSpline.cc.o -MF CMakeFiles/bspline.dir/src/BSpline.cc.o.d -o CMakeFiles/bspline.dir/src/BSpline.cc.o -c /root/DengYongjie/BsplineInterpolation/src/BSpline.cc

CMakeFiles/bspline.dir/src/BSpline.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/BSpline.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/BSpline.cc > CMakeFiles/bspline.dir/src/BSpline.cc.i

CMakeFiles/bspline.dir/src/BSpline.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/BSpline.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/BSpline.cc -o CMakeFiles/bspline.dir/src/BSpline.cc.s

CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o: ../src/BSpline_Interpolate.cc
CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o -MF CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o.d -o CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o -c /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate.cc

CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate.cc > CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.i

CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate.cc -o CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.s

CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o: ../src/BSpline_Interpolate1D.cc
CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o -MF CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o.d -o CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o -c /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate1D.cc

CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate1D.cc > CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.i

CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate1D.cc -o CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.s

CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o: ../src/BSpline_Interpolate2D.cc
CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o -MF CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o.d -o CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o -c /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate2D.cc

CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate2D.cc > CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.i

CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate2D.cc -o CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.s

CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o: ../src/BSpline_Interpolate3D.cc
CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o -MF CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o.d -o CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o -c /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate3D.cc

CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate3D.cc > CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.i

CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/BSpline_Interpolate3D.cc -o CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.s

CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o: ../src/Field-FeynmanModel.cc
CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o -MF CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o.d -o CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o -c /root/DengYongjie/BsplineInterpolation/src/Field-FeynmanModel.cc

CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/Field-FeynmanModel.cc > CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.i

CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/Field-FeynmanModel.cc -o CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.s

CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o: ../src/QCDNUM_Evolution.cc
CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o -MF CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o.d -o CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o -c /root/DengYongjie/BsplineInterpolation/src/QCDNUM_Evolution.cc

CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/QCDNUM_Evolution.cc > CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.i

CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/QCDNUM_Evolution.cc -o CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.s

CMakeFiles/bspline.dir/src/Tensor.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/Tensor.cc.o: ../src/Tensor.cc
CMakeFiles/bspline.dir/src/Tensor.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/bspline.dir/src/Tensor.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/Tensor.cc.o -MF CMakeFiles/bspline.dir/src/Tensor.cc.o.d -o CMakeFiles/bspline.dir/src/Tensor.cc.o -c /root/DengYongjie/BsplineInterpolation/src/Tensor.cc

CMakeFiles/bspline.dir/src/Tensor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/Tensor.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/Tensor.cc > CMakeFiles/bspline.dir/src/Tensor.cc.i

CMakeFiles/bspline.dir/src/Tensor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/Tensor.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/Tensor.cc -o CMakeFiles/bspline.dir/src/Tensor.cc.s

CMakeFiles/bspline.dir/src/Tools.cc.o: CMakeFiles/bspline.dir/flags.make
CMakeFiles/bspline.dir/src/Tools.cc.o: ../src/Tools.cc
CMakeFiles/bspline.dir/src/Tools.cc.o: CMakeFiles/bspline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/bspline.dir/src/Tools.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bspline.dir/src/Tools.cc.o -MF CMakeFiles/bspline.dir/src/Tools.cc.o.d -o CMakeFiles/bspline.dir/src/Tools.cc.o -c /root/DengYongjie/BsplineInterpolation/src/Tools.cc

CMakeFiles/bspline.dir/src/Tools.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bspline.dir/src/Tools.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/DengYongjie/BsplineInterpolation/src/Tools.cc > CMakeFiles/bspline.dir/src/Tools.cc.i

CMakeFiles/bspline.dir/src/Tools.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bspline.dir/src/Tools.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/DengYongjie/BsplineInterpolation/src/Tools.cc -o CMakeFiles/bspline.dir/src/Tools.cc.s

# Object files for target bspline
bspline_OBJECTS = \
"CMakeFiles/bspline.dir/src/BSpline.cc.o" \
"CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o" \
"CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o" \
"CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o" \
"CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o" \
"CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o" \
"CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o" \
"CMakeFiles/bspline.dir/src/Tensor.cc.o" \
"CMakeFiles/bspline.dir/src/Tools.cc.o"

# External object files for target bspline
bspline_EXTERNAL_OBJECTS =

libbspline.a: CMakeFiles/bspline.dir/src/BSpline.cc.o
libbspline.a: CMakeFiles/bspline.dir/src/BSpline_Interpolate.cc.o
libbspline.a: CMakeFiles/bspline.dir/src/BSpline_Interpolate1D.cc.o
libbspline.a: CMakeFiles/bspline.dir/src/BSpline_Interpolate2D.cc.o
libbspline.a: CMakeFiles/bspline.dir/src/BSpline_Interpolate3D.cc.o
libbspline.a: CMakeFiles/bspline.dir/src/Field-FeynmanModel.cc.o
libbspline.a: CMakeFiles/bspline.dir/src/QCDNUM_Evolution.cc.o
libbspline.a: CMakeFiles/bspline.dir/src/Tensor.cc.o
libbspline.a: CMakeFiles/bspline.dir/src/Tools.cc.o
libbspline.a: CMakeFiles/bspline.dir/build.make
libbspline.a: CMakeFiles/bspline.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/DengYongjie/BsplineInterpolation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libbspline.a"
	$(CMAKE_COMMAND) -P CMakeFiles/bspline.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bspline.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bspline.dir/build: libbspline.a
.PHONY : CMakeFiles/bspline.dir/build

CMakeFiles/bspline.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bspline.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bspline.dir/clean

CMakeFiles/bspline.dir/depend:
	cd /root/DengYongjie/BsplineInterpolation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/DengYongjie/BsplineInterpolation /root/DengYongjie/BsplineInterpolation /root/DengYongjie/BsplineInterpolation/build /root/DengYongjie/BsplineInterpolation/build /root/DengYongjie/BsplineInterpolation/build/CMakeFiles/bspline.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bspline.dir/depend

