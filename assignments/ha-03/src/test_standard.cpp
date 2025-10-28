#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <stdexcept>

int evalStandard(const std::string& expr);

TEST_CASE("Evaluate") {
    CHECK(evalStandard("1+2") == 3);
    CHECK(evalStandard("3+4+5") == 12);
    CHECK(evalStandard("2*3") == 6);
    CHECK(evalStandard("(2+3)*4+1") == 21);
    CHECK(evalStandard("10/5-3+6*2+1") == 12);
    CHECK(evalStandard("(1*2*3*4*5)") == 120);
    CHECK(evalStandard("((100+200-300)/4)-5") == -5);
    CHECK(evalStandard("(100+(200-(300+(400-500))))") == 100);
    CHECK(evalStandard("(((15)/(4)))") == 3);
    CHECK(evalStandard("((0))") == 0);
}

TEST_CASE("Exceptions") {
    CHECK_THROWS_AS(evalStandard("(a+2)"), std::runtime_error);
    CHECK_THROWS_AS(evalStandard("100*200)-300)+400)"), std::runtime_error);
    CHECK_THROWS_AS(evalStandard("(1+)"), std::runtime_error);
    CHECK_THROWS_AS(evalStandard("((1+2)(3+4))"), std::runtime_error);
    CHECK_THROWS_AS(evalStandard("4/(3-3)"), std::runtime_error);
    CHECK_THROWS_AS(evalStandard("(1000<100)"), std::runtime_error);
}
