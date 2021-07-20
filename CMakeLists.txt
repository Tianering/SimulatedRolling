cmake_minimum_required(VERSION 3.19)
project(SimulatedRolling)

set(CMAKE_CXX_STANDARD 14)

# opencv
find_package(OpenCV 4.5.2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(SimulatedRolling main.cpp)
target_link_libraries(SimulatedRolling ${OpenCV_LIBS})