#pragma once
#include <cstddef>

class DoublyLinkedList {
    struct Node {
        // TODO: Define linked list node member variables.
    };

    // TODO: Define linked list member variables.

public:
    DoublyLinkedList();

    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList &other) = delete;

    DoublyLinkedList &operator=(const DoublyLinkedList &other) = delete;

    [[nodiscard]] int &operator[](size_t index);

    void push_front(int value);

    void pop_front();

    void push_back(int value);

    void pop_back();

    [[nodiscard]] size_t size() const;
};
