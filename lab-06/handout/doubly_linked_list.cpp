#include "doubly_linked_list.h"

DoublyLinkedList::DoublyLinkedList() {
    // TODO: Initialize an empty linked list.
}

DoublyLinkedList::~DoublyLinkedList() {
    // TODO: Deallocate dynamically allocated memory.
}

int &DoublyLinkedList::operator[](size_t index) {
    // TODO: Return the element at index `index`. If `index` is out of bounds, throw `std::out_of_range`.
}

void DoublyLinkedList::push_front(int value) {
    // TODO: Prepend `value` to the linked list.
}

void DoublyLinkedList::pop_front() {
    // TODO: Remove the first element in the linked list. If the linked list is empty, throw `std::out_of_range`.
}

void DoublyLinkedList::push_back(int value) {
    // TODO: Append `value` to the linked list.
}

void DoublyLinkedList::pop_back() {
    // TODO: Remove the last element in the linked list. If the linked list is empty, throw `std::out_of_range`.
}

size_t DoublyLinkedList::size() const {
    // TODO: Return the number of elements in the linked list.
}
