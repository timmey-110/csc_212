cmake_minimum_required(VERSION 3.10)
project(csc212-lab-02)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_two_sum two_sum.cpp two_sum_fast.cpp test_two_sum.cpp)
add_executable(bench_two_sum two_sum.cpp two_sum_fast.cpp bench_two_sum.cpp)

add_executable(test_three_sum three_sum.cpp three_sum_fast.cpp test_three_sum.cpp)
add_executable(bench_three_sum three_sum.cpp three_sum_fast.cpp bench_three_sum.cpp)

add_executable(test_subset_sum subset_sum.cpp test_subset_sum.cpp)
add_executable(bench_subset_sum subset_sum.cpp bench_subset_sum.cpp)
