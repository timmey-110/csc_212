#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "stack.h"
#include <stdexcept>

TEST_CASE("Constructor") {
    Stack s1(10);
    CHECK(s1.empty() == true);
    CHECK(s1.size() == 0);    
    Stack s2(1);
    CHECK(s2.empty() == true);
    CHECK(s2.size() == 0);
}

TEST_CASE("Memory") {
    for (int i = 100 ; i < 115 ; i++) {
        Stack s(i);
        for (int j = 0; j < i; ++j) {
            s.push(j);
        }
        CHECK(s.size() == static_cast<size_t>(i));
        for (int j = 0 ; j < i ; ++j) {
            s.pop();
        }
        CHECK(s.empty() == true);
    }
    // multiple stacks can coexist
    Stack s1(10);
    Stack s2(20);
    s1.push(1);
    s2.push(2);
    CHECK(s1.top() == 1);
    CHECK(s2.top() == 2);
}

TEST_CASE("Methods") {
    // multiple elements
    Stack s2(10);
    s2.push(1);
    s2.push(2);
    s2.push(3);
    REQUIRE(s2.size() == 3);
    CHECK(s2.top() == 3);
    s2.pop();
    REQUIRE(s2.top() == 2);
    s2.pop();
    REQUIRE(s2.top() == 1);
    s2.pop();
    CHECK(s2.empty() == true);
    // push and pop alternating operations
    Stack s3(50);
    for (int i = 0 ; i < 45 ; ++i) {
        s3.push(i);
        s3.push(-i);
        s3.pop();
        REQUIRE(s3.top() == i);
    }
    REQUIRE(s3.size() == 45);
    CHECK(s3.top() == 44);
}

TEST_CASE("Exceptions") {
    Stack s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    CHECK_THROWS_AS(s1.push(3), std::length_error);
    REQUIRE_THROWS_AS(s1.push(4), std::length_error);
    // pop throws out_of_range after emptying stack
    Stack s3(10);
    s3.push(1);
    s3.pop();
    REQUIRE_THROWS_AS(s3.pop(), std::out_of_range);
    // top throws out_of_range after emptying stack
    Stack s5(10);
    s5.push(5);
    s5.push(15);
    s5.push(5);
    s5.pop();
    s5.pop();
    s5.pop();
    REQUIRE_THROWS_AS(s5.top(), std::out_of_range); 
}