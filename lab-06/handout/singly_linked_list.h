#pragma once
#include <cstddef>

class SinglyLinkedList {
    struct Node {
        // TODO: Define linked list node member variables.
    };

    // TODO: Define linked list member variables.

public:
    SinglyLinkedList();

    ~SinglyLinkedList();

    SinglyLinkedList(const SinglyLinkedList &other) = delete;

    SinglyLinkedList &operator=(const SinglyLinkedList &other) = delete;

    [[nodiscard]] int &operator[](size_t index);

    void push_front(int value);

    void pop_front();

    [[nodiscard]] size_t size() const;
};
