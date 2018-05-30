cmake_minimum_required(VERSION 2.8)
project(ComparisonOfTreeImplementations)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        include/AvlTree.hpp

        include/RedBlackTree.hpp
        include/A2B4Tree.hpp
        include/SplayTree.hpp
        include/SkipList.hpp)
set(SOURCE_FILES
        Source/AvlTree.cpp

        Source/RedBlackTree.cpp
        Source/A2B4Tree.cpp
        Source/SplayTree.cpp
        Source/SkipList.cpp)

include_directories(ComparisonOfTreeImplementations Source)
include_directories(ComparisonOfTreeImplementations include)

add_executable(ComparisonOfTreeImplementations ${HEADER_FILES} ${SOURCE_FILES} main.cpp)