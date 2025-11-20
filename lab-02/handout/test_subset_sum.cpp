#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "subset_sum.h"
#include <vector>

void run_subset_sum_tests() {
    SUBCASE("empty array") {
        CHECK(subset_sum({}, 5) == false);
    }

    SUBCASE("single element array equal to target") {
        CHECK(subset_sum({7}, 7) == true);
    }

    SUBCASE("single element array not equal to target") {
        CHECK(subset_sum({3}, 7) == false);
    }

    SUBCASE("two elements sum to target") {
        CHECK(subset_sum({3, 4}, 7) == true);
    }

    SUBCASE("two elements do not sum to target") {
        CHECK(subset_sum({2, 5}, 10) == false);
    }

    SUBCASE("several elements containing a valid subset") {
        CHECK(subset_sum({1, 2, 3, 4, 5}, 9) == true);
    }

    SUBCASE("several elements without a valid subset") {
        CHECK(subset_sum({1, 2, 4, 8}, 20) == false);
    }

    SUBCASE("negative numbers forming target") {
        CHECK(subset_sum({-3, -1, 4, 6}, 2) == true);
    }

    SUBCASE("negatives do not form target") {
        CHECK(subset_sum({-5, -2, -7}, -10) == false);
    }

    SUBCASE("mix of negatives and positives") {
        CHECK(subset_sum({-10, 2, 8, 4}, 0) == true);
    }

    SUBCASE("zero with positive numbers") {
        CHECK(subset_sum({0, 2, 3}, 5) == true);
    }

    SUBCASE("zero with negative numbers") {
        CHECK(subset_sum({0, -3, 7}, 4) == true);
    }

    SUBCASE("only zeros, target nonzero") {
        CHECK(subset_sum({0, 0, 0}, 5) == false);
    }

    SUBCASE("zeros summing to zero") {
        CHECK(subset_sum({0, 0, 0, 1}, 0) == true);
    }

    SUBCASE("duplicates forming target") {
        CHECK(subset_sum({2, 2, 3, 1}, 7) == true);
    }

    SUBCASE("target requires using same number more than available") {
        CHECK(subset_sum({2, 3, 4}, 12) == false);
    }

    SUBCASE("large numbers") {
        CHECK(subset_sum({1000000, 500000, 250000}, 1750000) == true);
    }

    SUBCASE("all negatives") {
        CHECK(subset_sum({-1, -2, -3, -4}, -6) == true);
    }
}

TEST_CASE("subset_sum implementation") {
    run_subset_sum_tests();
}
