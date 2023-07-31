cmake_minimum_required(VERSION 3.25)
project(Containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Containers
        AvlTree.tpp
        Map.cpp Map.h)
