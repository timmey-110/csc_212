#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "three_sum.h"
#include "three_sum_fast.h"
#include <vector>

template<typename ThreeSumFunc>
void run_three_sum_tests(ThreeSumFunc func) {
    SUBCASE("empty array") {
        CHECK(func({}, 5) == false);
    }

    SUBCASE("single element array") {
        CHECK(func({7}, 7) == false);
    }

    SUBCASE("two element array") {
        CHECK(func({3, 4}, 7) == false);
    }

    SUBCASE("three elements do not sum to target") {
        CHECK(func({1, 2, 3}, 10) == false);
    }

    SUBCASE("three elements sum to target") {
        CHECK(func({1, 2, 4}, 7) == true);
    }

    SUBCASE("several elements containing a valid triplet") {
        CHECK(func({1, 2, 3, 4, 5}, 9) == true);
    }

    SUBCASE("several elements without a valid triplet") {
        CHECK(func({1, 2, 4, 8}, 20) == false);
    }

    SUBCASE("negative numbers forming target") {
        CHECK(func({-3, -1, 4, 6}, 2) == true);
    }

    SUBCASE("negatives do not form target") {
        CHECK(func({-5, -2, -7}, -10) == false);
    }

    SUBCASE("mix of negatives and positives") {
        CHECK(func({-10, 2, 8, 4}, 0) == true);
    }

    SUBCASE("zero with positive numbers") {
        CHECK(func({0, 2, 3}, 5) == true);
    }

    SUBCASE("zero with negative numbers") {
        CHECK(func({0, -3, 7}, 4) == true);
    }

    SUBCASE("only zeros, target nonzero") {
        CHECK(func({0, 0, 0}, 5) == false);
    }

    SUBCASE("three zeros sum to zero") {
        CHECK(func({0, 0, 0, 1}, 0) == true);
    }

    SUBCASE("duplicates forming target") {
        CHECK(func({2, 2, 3, 1}, 7) == true);
    }

    SUBCASE("target requires using same number more than available") {
        CHECK(func({2, 3, 4}, 12) == false);
    }
}

TEST_CASE("three_sum implementation") {
    run_three_sum_tests(three_sum);
}

TEST_CASE("three_sum_fast implementation") {
    run_three_sum_tests(three_sum_fast);
}
