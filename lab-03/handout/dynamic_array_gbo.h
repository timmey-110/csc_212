#pragma once
#include <cstddef>

class DynamicArrayGBO {
    int *m_data;
    size_t m_size;
    size_t m_capacity;

public:
    DynamicArrayGBO();

    ~DynamicArrayGBO();

    DynamicArrayGBO(const DynamicArrayGBO &other) = delete;

    DynamicArrayGBO &operator=(const DynamicArrayGBO &other) = delete;

    [[nodiscard]] int &operator[](size_t index);

    void push_back(int value);

    [[nodiscard]] size_t size() const { return m_size; }

    [[nodiscard]] size_t capacity() const { return m_capacity; }
};
