cmake_minimum_required(VERSION 3.10)
project(csc212-lab-06)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_singly_linked_list singly_linked_list.cpp test_singly_linked_list.cpp)
add_executable(bench_singly_linked_list singly_linked_list.cpp bench_singly_linked_list.cpp)
add_executable(test_doubly_linked_list doubly_linked_list.cpp test_doubly_linked_list.cpp)
add_executable(test_skiplist skiplist.cpp test_skiplist.cpp)
