#pragma once
#include <cstddef>

class Sequence {
    // TODO: Define binary search tree member variables.

public:
    Sequence();

    ~Sequence();

    Sequence(const Sequence &other) = delete;

    Sequence &operator=(const Sequence &other) = delete;

    void insert(size_t index, int value);

    void erase(size_t index);

    [[nodiscard]] int &operator[](size_t index);

    [[nodiscard]] size_t size() const;
};
