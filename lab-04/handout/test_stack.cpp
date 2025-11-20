#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"
#include <stdexcept>

TEST_CASE("Stack default construction") {
    Stack s;
    CHECK(s.size() == 0);
}

TEST_CASE("Push elements increases size") {
    Stack s;
    s.push(10);
    CHECK(s.size() == 1);
    CHECK(s.top() == 10);

    s.push(20);
    CHECK(s.size() == 2);
    CHECK(s.top() == 20);

    s.push(-5);
    CHECK(s.size() == 3);
    CHECK(s.top() == -5);
}

TEST_CASE("Pop elements decreases size") {
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);

    CHECK(s.size() == 3);

    s.pop();
    CHECK(s.size() == 2);
    CHECK(s.top() == 2);

    s.pop();
    CHECK(s.size() == 1);
    CHECK(s.top() == 1);

    s.pop();
    CHECK(s.size() == 0);
}

TEST_CASE("Pop on empty stack throws") {
    Stack s;
    CHECK_THROWS_AS(s.pop(), std::out_of_range);
}

TEST_CASE("Top on empty stack throws") {
    Stack s;
    CHECK_THROWS_AS(s.top(), std::out_of_range);
}

TEST_CASE("Push a large number of elements") {
    Stack s;
    for (int i = 0; i < 1000; i++) {
        s.push(i);
        CHECK(s.top() == i);
        CHECK(s.size() == static_cast<size_t>(i + 1));
    }

    for (int i = 999; i >= 0; i--) {
        CHECK(s.top() == i);
        s.pop();
    }
    CHECK(s.size() == 0);
}
