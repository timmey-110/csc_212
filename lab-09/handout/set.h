#pragma once
#include <cstddef>

class Set {
    struct Node {
        int value;
        Node *left;
        Node *right;

        explicit Node(const int value) : value(value), left(nullptr), right(nullptr) {
        }

        Node(const int value, Node *left, Node *right) : value(value), left(left), right(right) {
        }
    };

    // TODO: Define binary search tree member variables.

    [[nodiscard]] static Node *insert(Node *root, int value);

    [[nodiscard]] static Node *erase(Node *root, int value);

    [[nodiscard]] static const Node *find(const Node *root, int value);

    static void destroy(Node *root);

public:
    Set();

    ~Set();

    Set(const Set &other) = delete;

    Set &operator=(const Set &other) = delete;

    void insert(int value);

    void erase(int value);

    [[nodiscard]] bool contains(int value) const;

    [[nodiscard]] size_t size() const;

    friend class SetTester;
};
