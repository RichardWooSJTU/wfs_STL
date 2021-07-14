cmake_minimum_required(VERSION 3.17)
project(mySTL)

set(CMAKE_CXX_STANDARD 14)

add_executable(mySTL main.cpp my_allocator.h memory/construct.h traits/type_traits.h traits/iterator_traits.h memory/uninitialized.h container/my_vector.h container/my_deque.h iterator/deque_iterator.h)