#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array_gbf.h"
#include <stdexcept>
#include <cmath>

TEST_CASE("DynamicArrayGBF: Constructor throws on invalid factor") {
    CHECK_THROWS_AS(DynamicArrayGBF(1.0), std::invalid_argument);
    CHECK_THROWS_AS(DynamicArrayGBF(0.5), std::invalid_argument);
    CHECK_THROWS_AS(DynamicArrayGBF(-2.0), std::invalid_argument);
}

TEST_CASE("DynamicArrayGBF: Initial size and capacity") {
    DynamicArrayGBF arr(1.5);
    CHECK(arr.size() == 0);
    CHECK(arr.capacity() >= 0);
}

TEST_CASE("DynamicArrayGBF: push_back increases size and stores elements") {
    DynamicArrayGBF arr(1.5);
    arr.push_back(10);
    CHECK(arr.size() == 1);
    CHECK(arr[0] == 10);

    arr.push_back(20);
    CHECK(arr.size() == 2);
    CHECK(arr[1] == 20);
}

TEST_CASE("DynamicArrayGBF: Multiple push_backs") {
    DynamicArrayGBF arr(1.5);
    const int N = 100;
    for (int i = 0; i < N; ++i) {
        arr.push_back(i);
    }
    CHECK(arr.size() == N);
    for (int i = 0; i < N; ++i) {
        CHECK(arr[i] == i);
    }
}

TEST_CASE("DynamicArrayGBF: operator[] throws on out-of-range access") {
    DynamicArrayGBF arr(1.5);
    arr.push_back(1);
    arr.push_back(2);
    CHECK_THROWS_AS((void)arr[2], std::out_of_range);
    CHECK_THROWS_AS((void)arr[-1], std::out_of_range);
}

TEST_CASE("DynamicArrayGBF: Capacity grows by factor") {
    double factor = 1.5;
    DynamicArrayGBF arr(factor);
    arr.push_back(0);
    size_t last_capacity = arr.capacity();

    for (int i = 1; i < 50; ++i) {
        arr.push_back(i);
        CHECK(arr[i] == i);

        if (arr.size() > last_capacity) {
            size_t expected_capacity = static_cast<size_t>(std::ceil(last_capacity * factor));
            CHECK(arr.capacity() == expected_capacity);
        }
        last_capacity = arr.capacity();
    }
}
