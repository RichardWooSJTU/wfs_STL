cmake_minimum_required(VERSION 3.17)
project(mySTL)

set(CMAKE_CXX_STANDARD 14)

add_executable(mySTL main.cpp my_allocator.h)