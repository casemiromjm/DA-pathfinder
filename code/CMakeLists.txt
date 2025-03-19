cmake_minimum_required(VERSION 3.30)
project(code)

set(CMAKE_CXX_STANDARD 14)

# Add the directory containing the header fies
include_directories(${CMAKE_SOURCE_DIR}/data_structures)

add_executable(code main.cpp)
