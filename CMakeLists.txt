cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")
project( kdtree )

set(EXECUTABLE_OUTPUT_PATH ../bin)

add_executable( kdtree src/main.cpp src/KdNode.hpp src/KdTree.hpp )
