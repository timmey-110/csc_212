#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "eval.h"

TEST_CASE("Single integer") {
    CHECK(eval("42") == 42);
    CHECK(eval("-7") == -7);
    CHECK(eval("0") == 0);
}

TEST_CASE("Addition") {
    CHECK(eval("(1+2)") == 3);
    CHECK(eval("(-3+5)") == 2);
    CHECK(eval("(-10+20)") == 10);
}

TEST_CASE("Subtraction") {
    CHECK(eval("(5-2)") == 3);
    CHECK(eval("(-3-5)") == -8);
    CHECK(eval("(10--5)") == 15);
}

TEST_CASE("Multiplication") {
    CHECK(eval("(2*3)") == 6);
    CHECK(eval("(-4*5)") == -20);
    CHECK(eval("(-2*-3)") == 6);
}

TEST_CASE("Division") {
    CHECK(eval("(6/2)") == 3);
    CHECK(eval("(-9/3)") == -3);
    CHECK(eval("(7/2)") == 3);
    CHECK(eval("(-7/2)") == -3);
}

TEST_CASE("Nested expressions") {
    CHECK(eval("((1+2)*(3+4))") == 21);
    CHECK(eval("((10-3)/2)") == 3);
    CHECK(eval("((2+3)*(4-1))") == 15);
    CHECK(eval("(((1+2)+(3+4))*2)") == 18);
}

TEST_CASE("Deep nesting") {
    CHECK(eval("(((1+2)*(3+4))/(5-2))") == 7);
    CHECK(eval("((1+(2+(3+4))))") == 10);
    CHECK(eval("(((2*3)*(4*5))/(10-5))") == 24);
}
