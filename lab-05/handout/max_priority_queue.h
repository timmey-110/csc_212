#pragma once
#include <cstddef>
#include <vector>

class MaxPriorityQueue {
    std::vector<int> m_heap;

    [[nodiscard]] static size_t parent(size_t index);

    [[nodiscard]] static size_t left(size_t index);

    [[nodiscard]] static size_t right(size_t index);

    void static heapify_down(std::vector<int> &heap, size_t index);

    void static heapify_up(std::vector<int> &heap, size_t index);

    void static heapify(std::vector<int> &heap);

public:
    MaxPriorityQueue();

    explicit MaxPriorityQueue(const std::vector<int> &data);

    void push(int value);

    void pop();

    [[nodiscard]] int top() const;

    [[nodiscard]] size_t size() const { return m_heap.size(); }

    friend class MaxPriorityQueueTester;
};
