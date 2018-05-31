cmake_minimum_required(VERSION 2.8)
project(ComparisonOfTreeImplementations)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        include/AvlTree.hpp
        include/BinarySearchTree.hpp
        include/RedBlackTree.hpp
        include/ScapeGoatTree.hpp
        include/SkipList.hpp
        include/SplayTree.hpp
        include/VanEmdeBoasTree.hpp)
set(SOURCE_FILES
        Source/AvlTree.cpp
        Source/BinarySearchTree.cpp
        Source/RedBlackTree.cpp
        Source/ScapeGoatTree.cpp
        Source/SkipList.cpp
        Source/SplayTree.cpp
        Source/VanEmdeBoasTree.cpp)

include_directories(ComparisonOfTreeImplementations Source)
include_directories(ComparisonOfTreeImplementations include)

add_executable(ComparisonOfTreeImplementations ${HEADER_FILES} ${SOURCE_FILES} test.cpp)