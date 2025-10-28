#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "deque.h"
#include <stdexcept>

TEST_CASE("Deque default construction") {
    Deque d;
    CHECK(d.size() == 0);
}

TEST_CASE("Push front increases size and updates front") {
    Deque d;
    d.push_front(10);
    CHECK(d.size() == 1);
    CHECK(d.front() == 10);
    CHECK(d.back() == 10);

    d.push_front(20);
    CHECK(d.size() == 2);
    CHECK(d.front() == 20);
    CHECK(d.back() == 10);

    d.push_front(-5);
    CHECK(d.size() == 3);
    CHECK(d.front() == -5);
    CHECK(d.back() == 10);
}

TEST_CASE("Push back increases size and updates back") {
    Deque d;
    d.push_back(1);
    CHECK(d.size() == 1);
    CHECK(d.front() == 1);
    CHECK(d.back() == 1);

    d.push_back(2);
    CHECK(d.size() == 2);
    CHECK(d.front() == 1);
    CHECK(d.back() == 2);

    d.push_back(3);
    CHECK(d.size() == 3);
    CHECK(d.front() == 1);
    CHECK(d.back() == 3);
}

TEST_CASE("Pop front decreases size and updates front") {
    Deque d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);

    CHECK(d.size() == 3);
    CHECK(d.front() == 1);
    CHECK(d.back() == 3);

    d.pop_front();
    CHECK(d.size() == 2);
    CHECK(d.front() == 2);

    d.pop_front();
    CHECK(d.size() == 1);
    CHECK(d.front() == 3);
    CHECK(d.back() == 3);

    d.pop_front();
    CHECK(d.size() == 0);
}

TEST_CASE("Pop back decreases size and updates back") {
    Deque d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);

    CHECK(d.size() == 3);
    CHECK(d.front() == 1);
    CHECK(d.back() == 3);

    d.pop_back();
    CHECK(d.size() == 2);
    CHECK(d.back() == 2);

    d.pop_back();
    CHECK(d.size() == 1);
    CHECK(d.front() == 1);
    CHECK(d.back() == 1);

    d.pop_back();
    CHECK(d.size() == 0);
}

TEST_CASE("Pop from empty deque throws") {
    Deque d;
    CHECK_THROWS_AS(d.pop_front(), std::out_of_range);
    CHECK_THROWS_AS(d.pop_back(), std::out_of_range);
}

TEST_CASE("Front and back on empty deque throws") {
    Deque d;
    CHECK_THROWS_AS(d.front(), std::out_of_range);
    CHECK_THROWS_AS(d.back(), std::out_of_range);
}

TEST_CASE("Push a large number of elements") {
    Deque d;
    for (int i = 0; i < 1000; i++) {
        d.push_back(i);
        CHECK(d.front() == 0);
        CHECK(d.back() == i);
        CHECK(d.size() == static_cast<size_t>(i + 1));
    }

    for (int i = 0; i < 1000; i++) {
        CHECK(d.front() == i);
        d.pop_front();
    }
    CHECK(d.size() == 0);
}
