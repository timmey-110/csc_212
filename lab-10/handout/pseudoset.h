#pragma once
#include <cstddef>

class PseudoSet {
    enum class Color {
        Red, Black,
    };

    struct Node {
        int value;
        Node *left;
        Node *right;
        Color color;

        explicit Node(int value) : value(value), left(nullptr), right(nullptr), color(Color::Red) {
        }

        Node(int value, Node *left, Node *right, Color color) : value(value), left(left), right(right), color(color) {
        }
    };

    [[nodiscard]] static Node *fix_red_left_left(Node *root);

    [[nodiscard]] static Node *fix_red_left_right(Node *root);

    [[nodiscard]] static Node *fix_red_right_left(Node *root);

    [[nodiscard]] static Node *fix_red_right_right(Node *root);

    [[nodiscard]] static Node *balance(Node *root);

    [[nodiscard]] static Node *insert(Node *root, int value);

    [[nodiscard]] static Node *find(Node *root, int value);

    static void destroy(Node *root);

    // TODO: Define member variables.

public:
    PseudoSet();

    ~PseudoSet();

    PseudoSet(const PseudoSet &other) = delete;

    PseudoSet &operator=(PseudoSet &other) = delete;

    void insert(int value);

    [[nodiscard]] bool contains(int value) const;

    [[nodiscard]] size_t size() const;

    friend class PseudoSetTester;
};
