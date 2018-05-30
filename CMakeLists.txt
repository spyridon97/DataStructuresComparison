cmake_minimum_required(VERSION 2.8)
project(ComparisonOfTreeImplementations)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        include/A2B4Tree.hpp
        include/AvlTree.hpp
        include/BinarySearchTree.hpp
        include/RedBlackTree.hpp

        include/SkipList.hpp
        include/SplayTree.hpp)
set(SOURCE_FILES
        Source/A2B4Tree.cpp
        Source/AvlTree.cpp
        Source/BinarySearchTree.cpp
        Source/RedBlackTree.cpp

        Source/SkipList.cpp
        Source/SplayTree.cpp)

include_directories(ComparisonOfTreeImplementations Source)
include_directories(ComparisonOfTreeImplementations include)

add_executable(ComparisonOfTreeImplementations ${HEADER_FILES} ${SOURCE_FILES} main.cpp)