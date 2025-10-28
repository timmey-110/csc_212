#pragma once
#include <cstddef>

class SkipList {
    // TODO: Define skiplist member variables.

public:
    SkipList();

    ~SkipList();

    SkipList(const SkipList &other) = delete;

    SkipList &operator=(const SkipList &other) = delete;

    void insert(int value);

    void erase(int value);

    [[nodiscard]] bool contains(int value) const;

    [[nodiscard]] size_t size() const;
};
