#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array_gbd.h"
#include <stdexcept>

TEST_CASE("DynamicArrayGBD: Initial size and capacity") {
    DynamicArrayGBD arr;
    CHECK(arr.size() == 0);
    CHECK(arr.capacity() >= 0);
}

TEST_CASE("DynamicArrayGBD: push_back increases size and stores elements") {
    DynamicArrayGBD arr;
    arr.push_back(10);
    CHECK(arr.size() == 1);
    CHECK(arr[0] == 10);

    arr.push_back(20);
    CHECK(arr.size() == 2);
    CHECK(arr[1] == 20);
}

TEST_CASE("DynamicArrayGBD: Multiple push_backs") {
    DynamicArrayGBD arr;
    const int N = 100;
    for (int i = 0; i < N; ++i) {
        arr.push_back(i);
    }
    CHECK(arr.size() == N);
    for (int i = 0; i < N; ++i) {
        CHECK(arr[i] == i);
    }
}

TEST_CASE("DynamicArrayGBD: operator[] throws on out-of-range access") {
    DynamicArrayGBD arr;
    arr.push_back(1);
    arr.push_back(2);
    CHECK_THROWS_AS((void)arr[2], std::out_of_range);
    CHECK_THROWS_AS((void)arr[-1], std::out_of_range);
}

TEST_CASE("DynamicArrayGBD: Capacity doubles after resize") {
    DynamicArrayGBD arr;
    arr.push_back(0);
    size_t last_capacity = arr.capacity();

    for (int i = 1; i < 50; ++i) {
        arr.push_back(i);
        CHECK(arr[i] == i);

        if (arr.size() > last_capacity) {
            CHECK(arr.capacity() == last_capacity * 2);
        }
        last_capacity = arr.capacity();
    }
}
