cmake_minimum_required(VERSION 3.10)
project(csc212-lab-08)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_pseudoset pseudoset.cpp test_pseudoset.cpp)
add_executable(test_set set.cpp test_set.cpp)
