cmake_minimum_required(VERSION 3.10)
project(csc212-lab-02)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_stack stack.cpp test_stack.cpp)
add_executable(test_queue queue.cpp test_queue.cpp)
add_executable(test_rna rna.cpp test_rna.cpp)
add_executable(test_eval eval.cpp test_eval.cpp)
add_executable(test_deque deque.cpp test_deque.cpp)