#pragma once
#include <cstddef>
#include <vector>

class MinPriorityQueue {
    std::vector<int> m_data;

    [[nodiscard]] size_t parent(size_t index) const;

    [[nodiscard]] size_t left(size_t index) const;

    [[nodiscard]] size_t right(size_t index) const;

    void heapify_down(size_t index);

    void heapify_up(size_t index);

public:
    MinPriorityQueue();

    MinPriorityQueue(const std::vector<int> &data);

    void push(int value);

    void pop();

    [[nodiscard]] int top() const;

    [[nodiscard]] size_t size() const { return m_data.size(); }
};
