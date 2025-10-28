#pragma once
#include <cstddef>

class Queue {
    int *m_data;
    size_t m_size;
    size_t m_capacity;

public:
    Queue();

    ~Queue();

    Queue(const Queue &other) = delete;

    Queue &operator=(const Queue &other) = delete;

    void push(int value);

    void pop();

    [[nodiscard]] int front() const;

    [[nodiscard]] size_t size() const { return m_size; }
};
