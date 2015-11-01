cmake_minimum_required(VERSION 3.3)
project(C_Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(C_Test ${SOURCE_FILES})