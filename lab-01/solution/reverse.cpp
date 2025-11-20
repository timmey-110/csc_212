#define CATCH_CONFIG_MAIN
#include "catch.hpp"

void reverse_array(int *array, int n) {
    if (n == 0) {
        return;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        std::swap(array[i], array[j]);
        i += 1;
        j -= 1;
    }
}

TEST_CASE("reverse_array reverses small arrays") {
    int arr[] = {1, 2, 3};
    reverse_array(arr, 3);

    REQUIRE(arr[0] == 3);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 1);
}

TEST_CASE("reverse_array works on even-length arrays") {
    int arr[] = {10, 20, 30, 40};
    reverse_array(arr, 4);

    REQUIRE(arr[0] == 40);
    REQUIRE(arr[1] == 30);
    REQUIRE(arr[2] == 20);
    REQUIRE(arr[3] == 10);
}

TEST_CASE("reverse_array leaves single-element array unchanged") {
    int arr[] = {99};
    reverse_array(arr, 1);

    REQUIRE(arr[0] == 99);
}

TEST_CASE("reverse_array leaves empty array unchanged") {
    int arr[] = {0};
    reverse_array(arr, 0);

    // Nothing to check except that it compiles and runs without error
    REQUIRE(true);
}