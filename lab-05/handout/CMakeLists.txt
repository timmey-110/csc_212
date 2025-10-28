cmake_minimum_required(VERSION 3.10)
project(csc212-lab-02)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_min_priority_queue min_priority_queue.cpp test_min_priority_queue.cpp)
add_executable(test_heapsort heapsort.cpp test_heapsort.cpp)
add_executable(test_max_priority_queue max_priority_queue.cpp test_max_priority_queue.cpp)
add_executable(bench_scheduler scheduler.cpp tracer.cpp bench_scheduler.cpp)
