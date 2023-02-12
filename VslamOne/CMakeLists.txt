cmake_minimum_required(VERSION 2.8)
project(VslamOne)

message("CMAKE_BUILD_TYPE: ${BUILD_TYPE}")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build")
ELSE()
    message("Release with Debug information build")
ENDIF()

add_library(intro libSlamIntro.cpp)
add_executable(slamIntro slamIntro.cpp)
target_link_libraries(slamIntro intro)

