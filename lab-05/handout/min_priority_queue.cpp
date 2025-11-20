#include "min_priority_queue.h"

MinPriorityQueue::MinPriorityQueue() {
    // TODO: Initialize an empty min-priority queue. The underlying data structure should be a min-heap.
}

MinPriorityQueue::MinPriorityQueue(const std::vector<int> &data) {
    // TODO: Construct a min-priority queue containing the elements of `data` in O(n) time. The underlying data
    // structure should be a min-heap. Use `heapify_down`.
}

size_t MinPriorityQueue::parent(size_t index) const {
    // TODO: Return the index of the parent of `index` in the min-heap.
}

size_t MinPriorityQueue::left(size_t index) const {
    // TODO: Return the index of the left child of `index` in the min-heap.
}

size_t MinPriorityQueue::right(size_t index) const {
    // TODO: Return the index of the right child of `index` in the min-heap.
}

void MinPriorityQueue::heapify_down(size_t index) {
    // TODO: Heapify down in the min-heap from `index`. Use `left` and `right`.
}

void MinPriorityQueue::heapify_up(size_t index) {
    // TODO: Heapify up in the min-heap from `index`. Use `parent`.
}

void MinPriorityQueue::push(int value) {
    // TODO: Add `value` to the min-priority queue. Use `heapify_up`.
}

void MinPriorityQueue::pop() {
    // TODO: Remove the minimum value from the min-priority queue. If the min-priority queue is empty, throw
    // `std::out_of_range`. Use `heapify_down`.
}

int MinPriorityQueue::top() const {
    // TODO: Return the minimum value from the min-priority queue. If the min-priority queue is empty, throw
    // `std::out_of_range`.
}
