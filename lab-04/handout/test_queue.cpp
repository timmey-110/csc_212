#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "queue.h"
#include <stdexcept>

TEST_CASE("Queue default construction") {
    Queue q;
    CHECK(q.size() == 0);
}

TEST_CASE("Push elements increases size") {
    Queue q;
    q.push(10);
    CHECK(q.size() == 1);
    CHECK(q.front() == 10);

    q.push(20);
    CHECK(q.size() == 2);
    CHECK(q.front() == 10);

    q.push(-5);
    CHECK(q.size() == 3);
    CHECK(q.front() == 10);
}

TEST_CASE("Pop elements decreases size") {
    Queue q;
    q.push(1);
    q.push(2);
    q.push(3);

    CHECK(q.size() == 3);
    CHECK(q.front() == 1);

    q.pop();
    CHECK(q.size() == 2);
    CHECK(q.front() == 2);

    q.pop();
    CHECK(q.size() == 1);
    CHECK(q.front() == 3);

    q.pop();
    CHECK(q.size() == 0);
}

TEST_CASE("Pop on empty queue throws") {
    Queue q;
    CHECK_THROWS_AS(q.pop(), std::out_of_range);
}

TEST_CASE("Front on empty queue throws") {
    Queue q;
    CHECK_THROWS_AS(q.front(), std::out_of_range);
}

TEST_CASE("Push a large number of elements") {
    Queue q;
    for (int i = 0; i < 1000; i++) {
        q.push(i);
        CHECK(q.front() == 0);
        CHECK(q.size() == static_cast<size_t>(i + 1));
    }

    for (int i = 0; i < 1000; i++) {
        CHECK(q.front() == i);
        q.pop();
    }
    CHECK(q.size() == 0);
}
