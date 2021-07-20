cmake_minimum_required(VERSION 3.19)
project(SimulatedRolling)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/eigen3")
# opencv
find_package(OpenCV 4.5.2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(SimulatedRolling main.cpp objectIR.h rolling.h rollingImp.cpp stringSpilt.h stringSpiltImp.cpp)
target_link_libraries(SimulatedRolling ${OpenCV_LIBS})