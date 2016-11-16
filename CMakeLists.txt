cmake_minimum_required(VERSION 3.5)
project(opengl_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(opengl_test ${SOURCE_FILES})