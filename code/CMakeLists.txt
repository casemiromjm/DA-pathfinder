cmake_minimum_required(VERSION 3.30)
project(code)

set(CMAKE_CXX_STANDARD 14)

# Add the directory containing the header fies
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(code main.cpp data_structures/CSV.h data_structures/OutputData.h data_structures/InputData.h)
