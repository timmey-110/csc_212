#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array_gbo.h"
#include <stdexcept>

TEST_CASE("DynamicArrayGBO: Initial size and capacity") {
    DynamicArrayGBO arr;
    CHECK(arr.size() == 0);
    CHECK(arr.capacity() >= 0);
}

TEST_CASE("DynamicArrayGBO: push_back increases size and stores elements") {
    DynamicArrayGBO arr;
    arr.push_back(10);
    CHECK(arr.size() == 1);
    CHECK(arr[0] == 10);

    arr.push_back(20);
    CHECK(arr.size() == 2);
    CHECK(arr[1] == 20);
}

TEST_CASE("DynamicArrayGBO: Multiple push_backs") {
    DynamicArrayGBO arr;
    const int N = 100;
    for (int i = 0; i < N; ++i) {
        arr.push_back(i);
    }
    CHECK(arr.size() == N);
    for (int i = 0; i < N; ++i) {
        CHECK(arr[i] == i);
    }
}

TEST_CASE("DynamicArrayGBO: operator[] throws on out-of-range access") {
    DynamicArrayGBO arr;
    arr.push_back(1);
    arr.push_back(2);
    CHECK_THROWS_AS((void)arr[2], std::out_of_range);
    CHECK_THROWS_AS((void)arr[-1], std::out_of_range);
}

TEST_CASE("DynamicArrayGBO: Capacity grows by exactly one each time") {
    DynamicArrayGBO arr;
    size_t last_capacity = arr.capacity();

    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
        CHECK(arr[i] == i);

        if (arr.size() > last_capacity) {
            CHECK(arr.capacity() == last_capacity + 1);
        }
        last_capacity = arr.capacity();
    }
}
