#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <stdexcept>

int evalFullyParenthesized(const std::string& expr);

TEST_CASE("Evaluate") {
    CHECK(evalFullyParenthesized("(1+2)") == 3);
    CHECK(evalFullyParenthesized("((3+4)+5)") == 12);
    CHECK(evalFullyParenthesized("(2*3)") == 6);
    CHECK(evalFullyParenthesized("((2+3)*(4+1))") == 25);
    CHECK(evalFullyParenthesized("((10/(5-3))+(6*(2+1)))") == 23);
    CHECK(evalFullyParenthesized("(((1+2)+3)+4)") == 10);
    CHECK(evalFullyParenthesized("((((1*2)*3)*4)*5)") == 120);
    CHECK(evalFullyParenthesized("((((100+200)-300)+400)-500)") == -100);
    CHECK(evalFullyParenthesized("(100+(200-(300+(400-500))))") == 100);
    CHECK(evalFullyParenthesized("(15/4)") == 3);
}

TEST_CASE("Exceptions") {
    CHECK_THROWS_AS(evalFullyParenthesized("(a+2)"), std::runtime_error);
    CHECK_THROWS_AS(evalFullyParenthesized("100*200)-300)+400)"), std::runtime_error);
    CHECK_THROWS_AS(evalFullyParenthesized("(1+)"), std::runtime_error);
    CHECK_THROWS_AS(evalFullyParenthesized("((1+2)(3+4))"), std::runtime_error);
    CHECK_THROWS_AS(evalFullyParenthesized("(1)"), std::runtime_error);
    CHECK_THROWS_AS(evalFullyParenthesized("(4/(3-3))"), std::runtime_error);
    CHECK_THROWS_AS(evalFullyParenthesized("(100000)"), std::runtime_error);
}
