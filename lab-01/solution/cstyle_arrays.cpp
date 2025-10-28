#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <ostream>

void print_array(int* array, int n, std::ostream& os) {
    // TODO: Print each element of `array` to `os` separated by spaces. Do not include a trailing space.
    // NOTE: To print to `os` use the << operator. For example, `os << 5;` prints `5` to `os`.
    if (n == 0) {
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        os << array[i] << " ";
    }
    os << array[n - 1];
}

void print_string(char* string, std::ostream& os) {
    // TODO: Print each character in `string` to `os` separated by spaces. Do not include a trailing space.
    // NOTE: To print to `os` use the << operator. For example, `os << 5;` prints `5` to `os`.
    if (*string == '\0') {
        return;
    }

    os << *string++;
    while (*string != '\0') {
        os << " " << *string++;
    }
}

TEST_CASE("print_array prints integers separated by spaces") {
    int arr[] = {1, 2, 3, 4};
    std::ostringstream oss;

    print_array(arr, 4, oss);

    REQUIRE(oss.str() == "1 2 3 4");
}

TEST_CASE("print_array prints nothing for empty array") {
    int arr[] = {0};
    std::ostringstream oss;

    print_array(arr, 0, oss);

    REQUIRE(oss.str().empty());
}

TEST_CASE("print_string prints characters separated by spaces") {
    char str[] = "cat";
    std::ostringstream oss;

    print_string(str, oss);

    REQUIRE(oss.str() == "c a t");
}

TEST_CASE("print_string prints nothing for empty string") {
    char str[] = "";
    std::ostringstream oss;

    print_string(str, oss);

    REQUIRE(oss.str().empty());
}