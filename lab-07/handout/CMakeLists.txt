cmake_minimum_required(VERSION 3.10)
project(csc212-lab-07)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_playlist_period playlist_period.cpp test_playlist_period.cpp)
add_executable(test_bug_bisect bug_bisect.cpp test_bug_bisect.cpp)
add_executable(test_perfect_plunder perfect_plunder.cpp test_perfect_plunder.cpp)
add_executable(test_genetic_gap genetic_gap.cpp test_genetic_gap.cpp)
add_executable(test_strategic_silicon strategic_silicon.cpp test_strategic_silicon.cpp)