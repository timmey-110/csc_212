#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int sum_of_squares(int n) {
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += i * i;
    }
    return total;
}

TEST_CASE("sum_of_squares computes correctly") {
    REQUIRE(sum_of_squares(1) == 1);
    REQUIRE(sum_of_squares(2) == 5);
    REQUIRE(sum_of_squares(3) == 14);
    REQUIRE(sum_of_squares(0) == 0);
    REQUIRE(sum_of_squares(5) == 55);
}