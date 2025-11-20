#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int* allocate_one() {
    // TODO: Allocate a single integer with the `new` operator.
    return new int;
}

void deallocate_one(int* pointer) {
    // TODO: Allocate a single integer with the `delete` operator.
    delete pointer;
}

int* allocate_many(int n) {
    // TODO: Allocate an array of `n` integers with the `new[]` operator.
    return new int[n];
}

void deallocate_many(int* pointer) {
    // TODO: Deallocate an array of integers with the `delete[]` operator.
    delete[] pointer;
}

TEST_CASE("allocate_one allocates an integer") {
    int* p = allocate_one();

    REQUIRE(p != nullptr);

    *p = 42;
    REQUIRE(*p == 42);

    deallocate_one(p);
}

TEST_CASE("allocate_many allocates an array of n integers") {
    int n = 5;
    int* arr = allocate_many(n);

    REQUIRE(arr != nullptr);

    for (int i = 0; i < n; i++) {
        arr[i] = i * 10;
    }
    for (int i = 0; i < n; i++) {
        REQUIRE(arr[i] == i * 10);
    }

    deallocate_many(arr);
}
