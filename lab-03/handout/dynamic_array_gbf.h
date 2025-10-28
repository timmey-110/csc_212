#pragma once
#include <cstddef>

class DynamicArrayGBF {
    int *m_data;
    size_t m_size;
    size_t m_capacity;
    double m_growth_factor;

public:
    DynamicArrayGBF(double growth_factor);

    ~DynamicArrayGBF();

    DynamicArrayGBF(const DynamicArrayGBF &other) = delete;

    DynamicArrayGBF &operator=(const DynamicArrayGBF &other) = delete;

    [[nodiscard]] int &operator[](size_t index);

    void push_back(int value);

    [[nodiscard]] size_t size() const { return m_size; }

    [[nodiscard]] size_t capacity() const { return m_capacity; }
};
