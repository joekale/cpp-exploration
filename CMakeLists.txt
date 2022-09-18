cmake_minimum_required(VERSION 3.21)

project("Algorithm Exploration" CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)

add_subdirectory(vector_add)
