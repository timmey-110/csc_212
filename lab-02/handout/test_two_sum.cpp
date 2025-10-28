#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "two_sum.h"
#include "two_sum_fast.h"
#include <vector>

template<typename TwoSumFunc>
void run_two_sum_tests(TwoSumFunc func) {
    SUBCASE("empty array") {
        CHECK(func({}, 5) == false);
    }

    SUBCASE("single element array") {
        CHECK(func({7}, 7) == false);
    }

    SUBCASE("two elements sum to target") {
        CHECK(func({3, 4}, 7) == true);
    }

    SUBCASE("two elements do not sum to target") {
        CHECK(func({3, 4}, 10) == false);
    }

    SUBCASE("several elements containing a valid pair") {
        CHECK(func({1, 2, 3, 9}, 5) == true);
    }

    SUBCASE("several elements without a valid pair") {
        CHECK(func({1, 2, 4, 8}, 20) == false);
    }

    SUBCASE("negative numbers sum to target") {
        CHECK(func({-3, -1, 4, 6}, 3) == true);
    }

    SUBCASE("negatives do not form target") {
        CHECK(func({-5, -2, -7}, -3) == false);
    }

    SUBCASE("mix of negatives and positives") {
        CHECK(func({-10, 2, 8, 4}, -2) == true);
    }

    SUBCASE("zero with positive numbers") {
        CHECK(func({0, 5, 9}, 5) == true);
    }

    SUBCASE("zero with negative numbers") {
        CHECK(func({0, -3, 7}, -3) == true);
    }

    SUBCASE("only zeros, target nonzero") {
        CHECK(func({0, 0, 0}, 5) == false);
    }

    SUBCASE("two zeros sum to zero") {
        CHECK(func({0, 0, 1}, 0) == true);
    }

    SUBCASE("duplicates forming target") {
        CHECK(func({2, 2, 3}, 4) == true);
    }

    SUBCASE("target requires using same number twice") {
        CHECK(func({2, 3}, 4) == false);
    }
}

TEST_CASE("two_sum implementation") {
    run_two_sum_tests(two_sum);
}

TEST_CASE("two_sum_fast implementation") {
    run_two_sum_tests(two_sum_fast);
}
