#include "max_priority_queue.h"

MaxPriorityQueue::MaxPriorityQueue() {
    // TODO: Initialize an empty max-priority queue. The underlying data structure should be a max-heap.
}

MaxPriorityQueue::MaxPriorityQueue(const std::vector<int> &data) {
    // TODO: Construct a max-priority queue containing the elements of `data` in O(n) time. The underlying data
    // structure should be a max-heap. Use `heapify`.
}

size_t MaxPriorityQueue::parent(size_t index) {
    // TODO: Return the index of the parent of `index` in a max-heap.
}

size_t MaxPriorityQueue::left(size_t index) {
    // TODO: Return the index of the left child of `index` in a max-heap.
}

size_t MaxPriorityQueue::right(size_t index) {
    // TODO: Return the index of the right child of `index` in a max-heap.
}

void MaxPriorityQueue::heapify_down(std::vector<int> &heap, size_t index) {
    // TODO: Assume `heap[index+1:]` is a valid max-heap. Move the element at index `index` down until `heap[index:]` is
    // a valid max-heap. Use `left` and `right`.
}

void MaxPriorityQueue::heapify_up(std::vector<int> &heap, size_t index) {
    // TODO: Assume `heap[:index]` is a valid max-heap. Move the element at index `index` up until the `heap[:index+1]`
    // is a valid max-heap. Use `parent`.
}

void MaxPriorityQueue::heapify(std::vector<int> &heap) {
    // TODO: Convert `heap` into a valid max-heap in O(n) time. Use `heapify_down`.
}

void MaxPriorityQueue::push(int value) {
    // TODO: Add `value` to the max-priority queue. Use `heapify_up`.
}

void MaxPriorityQueue::pop() {
    // TODO: Remove the maximum value from the max-priority queue. If the max-priority queue is empty, throw
    // `std::out_of_range`. Use `heapify_down`.
}

int MaxPriorityQueue::top() const {
    // TODO: Return the maximum value from the max-priority queue. If the max-priority queue is empty, throw
    // `std::out_of_range`.
}
