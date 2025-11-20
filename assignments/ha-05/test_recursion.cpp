#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "functions.h"

TEST_CASE("Palindrome") {
    CHECK(palindrome("") == true);
    CHECK(palindrome("a") == true);
    CHECK(palindrome("racecar") == true);
    CHECK(palindrome("madam") == true);
    CHECK(palindrome("hello") == false);
    CHECK(palindrome("world") == false);
}

TEST_CASE("Reverse") {
    std::vector<int> vec1;
    reverse(vec1);
    CHECK(vec1.empty());
    std::vector<int> vec2 = {1};
    reverse(vec2);
    CHECK(vec2 == std::vector<int>{1});
    std::vector<int> vec3 = {1, 2, 3, 4, 5};
    reverse(vec3);
    CHECK(vec3 == std::vector<int>{5, 4, 3, 2, 1});
}

TEST_CASE("Binsearch") {
    std::vector<int> arr = {9, 7, 5, 3, 3};
    size_t index;    
    CHECK(bin_search(arr, 7, index) == true);
    CHECK(index == 1);
    CHECK(bin_search(arr, 3, index) == true);
    CHECK((index == 3 || index == 4));
    CHECK(bin_search(arr, 6, index) == false);
    CHECK(bin_search(arr, 1, index) == false);
}

TEST_CASE("str2int") {
    CHECK(str2int("67890") == 67890);
    CHECK(str2int("-12345") == -12345);
    CHECK(str2int("0") == 0);
    CHECK(str2int("42") == 42);
}

TEST_CASE("Countcells") {
    CHECK(count_cells("tiny-0.txt", 0, 0) == 0);
    CHECK(count_cells("tiny-0.txt", 1, 1) == 0);
    CHECK(count_cells("tiny-1.txt", 0, 0) == 4);
    CHECK(count_cells("tiny-1.txt", 1, 1) == 4);
    CHECK(count_cells("grid.txt", 1, 2) == 8);
    CHECK(count_cells("grid.txt", 4, 1) == 2);
    CHECK(count_cells("grid.txt", 3, 3) == 8);
    CHECK(count_cells("grid.txt", 0, 1) == 0);
}
