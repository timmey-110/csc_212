#pragma once
#include <cstddef>

class Deque {
    // TODO: Define required member variables.

public:
    Deque();

    ~Deque();

    Deque(const Deque &other) = delete;

    Deque &operator=(const Deque &other) = delete;

    void push_front(int value);

    void push_back(int value);

    void pop_front();

    void pop_back();

    [[nodiscard]] int front() const;

    [[nodiscard]] int back() const;

    [[nodiscard]] size_t size() const;
};
