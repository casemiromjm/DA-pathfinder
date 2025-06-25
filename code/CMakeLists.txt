cmake_minimum_required(VERSION 3.28)
project(pathfinder)

set(CMAKE_CXX_STANDARD 20)

# Add the directory containing the header fies
include_directories(${CMAKE_SOURCE_DIR}/data_structures
                    ${CMAKE_SOURCE_DIR}/algorithms
)

add_executable(pathfinder main.cpp
        algorithms/dijkstra_driving.cpp
        algorithms/dijkstra_drive_walk.cpp
)
