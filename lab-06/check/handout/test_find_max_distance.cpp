#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "find_max_distance.h"
#include <vector>

TEST_CASE("find_max_distance basic cases") {
    CHECK(find_max_distance({}) == 0);
    CHECK(find_max_distance({9}) == 0);
    CHECK(find_max_distance({-1, -1}) == 1);
    CHECK(find_max_distance({4, 2, 0, 4, 4, 2}) == 4);
}

TEST_CASE("find_max_distance all identical elements") {
    CHECK(find_max_distance({5, 5, 5}) == 2);
    CHECK(find_max_distance({-3, -3, -3, -3}) == 3);
}

TEST_CASE("find_max_distance only one max") {
    CHECK(find_max_distance({1, 2, 3, 4}) == 0);
    CHECK(find_max_distance({9, 5, 3, 1}) == 0);
}

TEST_CASE("find_max_distance multiple max scattered") {
    CHECK(find_max_distance({1, 9, 3, 9, 5, 9}) == 4);
    CHECK(find_max_distance({7, 1, 7, 2, 7, 3, 7}) == 6);
}

TEST_CASE("find_max_distance negatives and positives") {
    CHECK(find_max_distance({-10, -5, -10, -5}) == 2);
    CHECK(find_max_distance({-2, -2, -2, -2}) == 3);
    CHECK(find_max_distance({-100, 0, -100, 0}) == 2);
}

TEST_CASE("find_max_distance strictly increasing/decreasing") {
    CHECK(find_max_distance({1, 2, 3, 4, 5}) == 0);
    CHECK(find_max_distance({5, 4, 3, 2, 1}) == 0);
}

TEST_CASE("find_max_distance large values") {
    CHECK(find_max_distance({1000000, 1, 1000000}) == 2);
    CHECK(find_max_distance({-1000000, -500000, -1000000}) == 0);
}

TEST_CASE("find_max_distance edge index distances") {
    CHECK(find_max_distance({9, 0, 0, 0, 9}) == 4);
    CHECK(find_max_distance({1, 9, 0, 9, 1}) == 2);
    CHECK(find_max_distance({0, 0, 0, 0, 9}) == 0);
    CHECK(find_max_distance({9, 0, 0, 0, 0}) == 0);
}

TEST_CASE("find_max_distance stress test pattern") {
    std::vector<int> v(1000, 1);
    v[0] = 99;
    v[999] = 99;
    CHECK(find_max_distance(v) == 999);
}
