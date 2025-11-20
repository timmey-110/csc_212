#pragma once
#include <cstddef>

class Map {
    struct Node {
        // TODO: Define binary search tree node member variables.
    };

    // TODO: Define binary search tree member variables.

    [[nodiscard]] static Node *insert(Node *root, int key, int value);

    [[nodiscard]] static Node *erase(Node *root, int key);

    [[nodiscard]] static Node *find(Node *root, int key);

    static void destroy(Node *root);

public:
    Map();

    ~Map();

    Map(const Map &other) = delete;

    Map &operator=(const Map &other) = delete;

    void insert(int key, int value);

    void erase(int key);

    [[nodiscard]] int &operator[](int key);

    [[nodiscard]] size_t size() const;
};
