#pragma once
#include <cstddef>

class DynamicArrayDE {
    // TODO: Define underlying representation.
    size_t m_size;
    size_t m_capacity;

public:
    DynamicArrayDE();

    ~DynamicArrayDE();

    DynamicArrayDE(const DynamicArrayDE &other) = delete;

    DynamicArrayDE &operator=(const DynamicArrayDE &other) = delete;

    [[nodiscard]] int &operator[](size_t index);

    void push_front(int value);

    void push_back(int value);

    [[nodiscard]] size_t size() const { return m_size; }

    [[nodiscard]] size_t capacity() const { return m_capacity; }
};
