#define CATCH_CONFIG_MAIN
#include "catch.hpp"

void permute_pointers(int** array, int* permutation, int n) {
    // TODO: Permute `array` such that `array[i] = array[permutation[i]]`.
    // NOTE: Iterating over `i` and setting `array[i] = array[permutation[i]]` will not work. Why?

    int **permuted_array = new int*[n];

    for (int i = 0; i < n; i++) {
        permuted_array[i] = array[permutation[i]];
    }

    for (int i = 0; i < n; ++i) {
        array[i] = permuted_array[i];
    }

    delete[] permuted_array;
}

TEST_CASE("permute_pointers rearranges according to permutation array") {
    int a = 10, b = 20, c = 30;
    int* arr[] = {&a, &b, &c};

    // New order: arr[0] <- arr[2], arr[1] <- arr[0], arr[2] <- arr[1]
    int perm[] = {2, 0, 1};

    permute_pointers(arr, perm, 3);

    REQUIRE(*arr[0] == 30); // was c
    REQUIRE(*arr[1] == 10); // was a
    REQUIRE(*arr[2] == 20); // was b
}

TEST_CASE("permute_pointers works with identity permutation") {
    int x = 1, y = 2, z = 3;
    int* arr[] = {&x, &y, &z};
    int perm[] = {0, 1, 2};

    permute_pointers(arr, perm, 3);

    REQUIRE(*arr[0] == 1);
    REQUIRE(*arr[1] == 2);
    REQUIRE(*arr[2] == 3);
}

TEST_CASE("permute_pointers works with single element") {
    int x = 42;
    int* arr[] = {&x};
    int perm[] = {0};

    permute_pointers(arr, perm, 1);

    REQUIRE(*arr[0] == 42);
}

TEST_CASE("permute_pointers on empty array does nothing") {
    int** arr = nullptr;
    int* perm = nullptr;

    permute_pointers(arr, perm, 0);

    SUCCEED("No crash on empty array");
}