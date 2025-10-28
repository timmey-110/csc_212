#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "min_priority_queue.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

TEST_CASE("Default constructor creates empty queue") {
    MinPriorityQueue pq;
    CHECK(pq.size() == 0);
    CHECK_THROWS_AS(pq.top(), std::out_of_range);
    CHECK_THROWS_AS(pq.pop(), std::out_of_range);
}

TEST_CASE("Constructor from vector produces correct order") {
    std::vector<int> data = {3, 1, 6, 5, 2, 4};
    std::vector<int> sorted_data = data;
    std::sort(sorted_data.begin(), sorted_data.end());

    MinPriorityQueue pq(data);

    for (int expected: sorted_data) {
        CHECK(pq.top() == expected);
        pq.pop();
    }

    CHECK(pq.size() == 0);
    CHECK_THROWS_AS(pq.top(), std::out_of_range);
    CHECK_THROWS_AS(pq.pop(), std::out_of_range);
}

TEST_CASE("Push elements produces correct order") {
    MinPriorityQueue pq;
    std::vector<int> data = {10, 5, 20};
    std::vector<int> sorted_data = data;
    std::sort(sorted_data.begin(), sorted_data.end());

    for (int v: data) pq.push(v);

    for (int expected: sorted_data) {
        CHECK(pq.top() == expected);
        pq.pop();
    }

    CHECK(pq.size() == 0);
}

TEST_CASE("Multiple pushes and pops produce correct order") {
    MinPriorityQueue pq;
    std::vector<int> data = {15, 3, 17, 10, 84, 19, 6, 22, 9};
    std::vector<int> sorted_data = data;
    std::sort(sorted_data.begin(), sorted_data.end());

    for (int v: data) pq.push(v);

    for (int expected: sorted_data) {
        CHECK(pq.top() == expected);
        pq.pop();
    }

    CHECK(pq.size() == 0);
}
