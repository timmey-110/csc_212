#pragma once
#include <cstddef>

class Stack {
    int *m_data;
    size_t m_size;
    size_t m_capacity;

public:
    Stack();

    ~Stack();

    Stack(const Stack &other) = delete;

    Stack &operator=(const Stack &other) = delete;

    void push(int value);

    void pop();

    [[nodiscard]] int top() const;

    [[nodiscard]] size_t size() const { return m_size; }
};
