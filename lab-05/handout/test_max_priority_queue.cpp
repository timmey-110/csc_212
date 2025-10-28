#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "max_priority_queue.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <stdexcept>

class MaxPriorityQueueTester {
public:
    [[nodiscard]] static size_t parent(const size_t index) { return MaxPriorityQueue::parent(index); }

    [[nodiscard]] static size_t left(const size_t index) { return MaxPriorityQueue::left(index); };

    [[nodiscard]] static size_t right(const size_t index) { return MaxPriorityQueue::right(index); }

    void static heapify_down(std::vector<int> &heap, const size_t index) {
        MaxPriorityQueue::heapify_down(heap, index);
    }

    void static heapify_up(std::vector<int> &heap, const size_t index) { MaxPriorityQueue::heapify_up(heap, index); };

    void static heapify(std::vector<int> &heap) { MaxPriorityQueue::heapify(heap); }
};

TEST_CASE("parent returns parent index") {
    CHECK(MaxPriorityQueueTester::parent(1) == 0);
    CHECK(MaxPriorityQueueTester::parent(2) == 0);
    CHECK(MaxPriorityQueueTester::parent(3) == 1);
    CHECK(MaxPriorityQueueTester::parent(4) == 1);
    CHECK(MaxPriorityQueueTester::parent(5) == 2);
    CHECK(MaxPriorityQueueTester::parent(6) == 2);
}

TEST_CASE("left returns left child index") {
    CHECK(MaxPriorityQueueTester::left(0) == 1);
    CHECK(MaxPriorityQueueTester::left(1) == 3);
    CHECK(MaxPriorityQueueTester::left(2) == 5);
}

TEST_CASE("right returns right child index") {
    CHECK(MaxPriorityQueueTester::right(0) == 2);
    CHECK(MaxPriorityQueueTester::right(1) == 4);
    CHECK(MaxPriorityQueueTester::right(2) == 6);
}

TEST_CASE("heapify_down restores max-heap property with move from root") {
    std::vector<int> heap{1, 7, 8, 5, 6, 4, 3, 2};
    MaxPriorityQueueTester::heapify_down(heap, 0);

    CHECK(heap[0] >= heap[1]);
    CHECK(heap[0] >= heap[2]);
    CHECK(heap[1] >= heap[3]);
    CHECK(heap[1] >= heap[4]);
    CHECK(heap[2] >= heap[5]);
    CHECK(heap[2] >= heap[6]);
    CHECK(heap[3] >= heap[7]);
}

TEST_CASE("heapify_up restores max-heap property with move to root") {
    std::vector<int> heap{7, 6, 5, 3, 2, 4, 1, 8};
    MaxPriorityQueueTester::heapify_up(heap, 7);

    CHECK(heap[0] >= heap[1]);
    CHECK(heap[0] >= heap[2]);
    CHECK(heap[1] >= heap[3]);
    CHECK(heap[1] >= heap[4]);
    CHECK(heap[2] >= heap[5]);
    CHECK(heap[2] >= heap[6]);
    CHECK(heap[3] >= heap[7]);
}

TEST_CASE("heapify_down restores max-heap property with move from non-root") {
    std::vector<int> heap{8, 6, 7, 4, 5, 2, 1, 3};
    MaxPriorityQueueTester::heapify_down(heap, 3);

    CHECK(heap[0] >= heap[1]);
    CHECK(heap[0] >= heap[2]);
    CHECK(heap[1] >= heap[3]);
    CHECK(heap[1] >= heap[4]);
    CHECK(heap[2] >= heap[5]);
    CHECK(heap[2] >= heap[6]);
    CHECK(heap[3] >= heap[7]);
}

TEST_CASE("heapify_up restores max-heap property with move to non-root") {
    std::vector<int> heap{8, 7, 4, 3, 5, 1, 2, 6};
    MaxPriorityQueueTester::heapify_up(heap, 7);

    CHECK(heap[0] >= heap[1]);
    CHECK(heap[0] >= heap[2]);
    CHECK(heap[1] >= heap[3]);
    CHECK(heap[1] >= heap[4]);
    CHECK(heap[2] >= heap[5]);
    CHECK(heap[2] >= heap[6]);
    CHECK(heap[3] >= heap[7]);
}

TEST_CASE("heapify produces a valid max-heap") {
    std::vector<int> heap{3, 7, 1, 4, 6, 8, 5, 2};
    MaxPriorityQueueTester::heapify(heap);

    CHECK(heap[0] >= heap[1]);
    CHECK(heap[0] >= heap[2]);
    CHECK(heap[1] >= heap[3]);
    CHECK(heap[1] >= heap[4]);
    CHECK(heap[2] >= heap[5]);
    CHECK(heap[2] >= heap[6]);
    CHECK(heap[3] >= heap[7]);
}

TEST_CASE("Default constructor creates empty queue") {
    MaxPriorityQueue pq;
    CHECK(pq.size() == 0);
    CHECK_THROWS_AS((void)pq.top(), std::out_of_range);
}

TEST_CASE("Constructor from vector produces correct order") {
    std::vector<int> data{9, 2, 14, 5, 12, 7, 1, 15, 8, 11, 3, 6, 13, 10, 4};

    MaxPriorityQueue pq(data);
    std::priority_queue<int> expected(data.begin(), data.end());

    while (!expected.empty()) {
        CHECK(pq.top() == expected.top());
        CHECK(pq.size() == expected.size());
        pq.pop();
        expected.pop();
    }

    CHECK(pq.size() == expected.size());
    CHECK_THROWS_AS((void)pq.top(), std::out_of_range);
}

TEST_CASE("Push elements produces correct order") {
    std::vector<int> data{6, 13, 2, 10, 15, 3, 9, 5, 11, 7, 1, 12, 14, 8, 4};

    MaxPriorityQueue pq;
    std::priority_queue<int> expected;

    for (int i = 0; i < 3; ++i) {
        CHECK(pq.size() == expected.size());
        CHECK_THROWS_AS((void)pq.top(), std::out_of_range);

        for (auto v: data) {
            pq.push(v);
            expected.push(v);
            CHECK(pq.top() == expected.top());
            CHECK(pq.size() == expected.size());
        }

        while (!expected.empty()) {
            CHECK(pq.top() == expected.top());
            CHECK(pq.size() == expected.size());
            pq.pop();
            expected.pop();
        }

        CHECK(pq.size() == expected.size());
        CHECK_THROWS_AS((void)pq.top(), std::out_of_range);
    }
}
