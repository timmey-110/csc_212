#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "heapsort.h"
#include <vector>
#include <algorithm>

TEST_CASE("Empty vector remains empty") {
    std::vector<int> vec;
    heapsort(vec);
    CHECK(vec.empty());
}

TEST_CASE("Single element vector remains unchanged") {
    std::vector<int> vec = {42};
    heapsort(vec);
    CHECK(vec.size() == 1);
    CHECK(vec[0] == 42);
}

TEST_CASE("Already sorted vector stays sorted") {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> expected = vec;
    heapsort(vec);
    CHECK(vec == expected);
}

TEST_CASE("Reverse sorted vector gets sorted ascending") {
    std::vector<int> vec = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    heapsort(vec);
    CHECK(vec == expected);
}

TEST_CASE("Random vector gets sorted") {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    std::vector<int> expected = vec;
    std::sort(expected.begin(), expected.end());
    heapsort(vec);
    CHECK(vec == expected);
}

TEST_CASE("Vector with duplicates gets sorted") {
    std::vector<int> vec = {2, 3, 2, 1, 3, 1};
    std::vector<int> expected = {1, 1, 2, 2, 3, 3};
    heapsort(vec);
    CHECK(vec == expected);
}

TEST_CASE("Large vector gets sorted") {
    std::vector<int> vec(1000);
    for (int i = 0; i < 1000; ++i) vec[i] = 1000 - i;
    std::vector<int> expected(1000);
    for (int i = 0; i < 1000; ++i) expected[i] = i + 1;
    heapsort(vec);
    CHECK(vec == expected);
}
