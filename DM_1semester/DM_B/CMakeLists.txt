cmake_minimum_required(VERSION 3.6)
project(DM_B)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(DM_B ${SOURCE_FILES})