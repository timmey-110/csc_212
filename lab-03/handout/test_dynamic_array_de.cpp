#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array_de.h"
#include <stdexcept>

TEST_CASE("DynamicArrayDE: Initial size") {
    DynamicArrayDE arr;
    CHECK(arr.size() == 0);
}

TEST_CASE("DynamicArrayDE: push_back increases size and stores elements") {
    DynamicArrayDE arr;
    arr.push_back(10);
    CHECK(arr.size() == 1);
    CHECK(arr[0] == 10);

    arr.push_back(20);
    CHECK(arr.size() == 2);
    CHECK(arr[1] == 20);
}

TEST_CASE("DynamicArrayDE: push_front increases size and stores elements") {
    DynamicArrayDE arr;
    arr.push_front(10);
    CHECK(arr.size() == 1);
    CHECK(arr[0] == 10);

    arr.push_front(20);
    CHECK(arr.size() == 2);
    CHECK(arr[0] == 20);
    CHECK(arr[1] == 10);
}

TEST_CASE("DynamicArrayDE: push_front and push_back combined") {
    DynamicArrayDE arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_front(0);
    arr.push_front(-1);

    CHECK(arr.size() == 4);
    CHECK(arr[0] == -1);
    CHECK(arr[1] == 0);
    CHECK(arr[2] == 1);
    CHECK(arr[3] == 2);
}

TEST_CASE("DynamicArrayDE: Multiple push_backs and push_fronts") {
    DynamicArrayDE arr;
    const int N = 50;

    for (int i = 0; i < N; ++i) arr.push_back(i);
    for (int i = N; i < 2 * N; ++i) arr.push_front(i);

    CHECK(arr.size() == 2*N);
    for (int i = 0; i < N; ++i)
        CHECK(arr[i] == 2*N - 1 - i);
    for (int i = N; i < 2 * N; ++i)
        CHECK(arr[i] == i - N);
}

TEST_CASE("DynamicArrayDE: operator[] throws on out-of-range access") {
    DynamicArrayDE arr;
    arr.push_back(1);
    arr.push_front(0);

    CHECK_THROWS_AS((void)arr[2], std::out_of_range);
    CHECK_THROWS_AS((void)arr[-1], std::out_of_range);
}


TEST_CASE("DynamicArrayDE: stress test push_back") {
    DynamicArrayDE arr;
    const int N = 1000000;

    for (int i = 0; i < N; ++i) {
        arr.push_back(i);
    }

    CHECK(arr.size() == N);
    CHECK(arr[0] == 0);
    CHECK(arr[N/2] == N/2);
    CHECK(arr[N-1] == N-1);
}


TEST_CASE("DynamicArrayDE: stress test push_front") {
    DynamicArrayDE arr;
    const int N = 100001;

    for (int i = 0; i < N; ++i) {
        arr.push_front(i);
    }

    CHECK(arr.size() == N);
    CHECK(arr[0] == N-1);
    CHECK(arr[N/2] == N/2);
    CHECK(arr[N-1] == 0);
}

TEST_CASE("DynamicArrayDE: stress test alternating front/back") {
    DynamicArrayDE arr;
    const int N = 100000;

    for (int i = 0; i < N; ++i) {
        if (i % 2 == 0) arr.push_back(i);
        else arr.push_front(i);
    }

    CHECK(arr.size() == N);
    CHECK(arr[0] % 2 == 1);
    CHECK(arr[N-1] % 2 == 0);
    CHECK(arr[N/2] >= 0);
}
