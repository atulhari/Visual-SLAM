cmake_minimum_required(VERSION 3.5)
project(VslamOne)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("CMAKE_BUILD_TYPE: ${BUILD_TYPE}")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build")
ELSE()
  message("Release with Debug information build")
ENDIF()

set(Sophus_DIRS "/Sophus/build")
include_directories("/usr/include/eigen3")
find_package(Pangolin REQUIRED)
find_package(Sophus REQUIRED)

include_directories(${Sophus_INCLUDE_DIRS})
include_directories(${Pangolin_INCLUDE_DIRS})
# Add a library intro in the src folder
add_library(intro
  src/libSlamIntro.cpp
)
add_library(draw
  src/drawTrajectory.cpp)

add_executable(visualizer
  src/visualizer.cpp
)
add_executable(slamIntro
  src/slamIntro.cpp)

add_executable(plotTrajectory
src/plotTrajectory.cpp)

add_executable(eigenMatrix
  src/eigenMatrix.cpp)

add_executable(eigenGeometry
  src/eigenGeometry.cpp)

add_executable(coordinateTransform
  src/coordinateTransform.cpp)

add_executable(sophusExample
  src/sophusExample.cpp)

# Add the include directory for library A
target_include_directories(slamIntro
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(plotTrajectory
  PRIVATE
  draw
  ${Pangolin_LIBRARIES}
)
target_link_libraries(visualizer
  PRIVATE
  ${Pangolin_LIBRARIES}
)
target_link_libraries(slamIntro
  PRIVATE
  intro)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}/Pangolin/build)
# Set the build directory to the build folder
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/VslamOneDeployed)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Targets)
set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH}/usr/local/lib)

# Set the library and include directories
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add any additional options or flags as needed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Optionally set the installation path
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

# Optionally set the output directory for the built targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
