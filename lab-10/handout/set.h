#pragma once
#include <cstddef>

class Set {
    // TODO: Define member variables.

public:
    Set();

    ~Set();

    Set(const Set &other) = delete;

    Set &operator=(Set &other) = delete;

    void insert(int value);

    void erase(int value);

    [[nodiscard]] bool contains(int value) const;

    [[nodiscard]] size_t size() const;
};
