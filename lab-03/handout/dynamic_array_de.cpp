#include "dynamic_array_de.h"

DynamicArrayDE::DynamicArrayDE() {
    // TODO: Initialize an empty dynamic array. Any initial capacity is acceptable.
}

DynamicArrayDE::~DynamicArrayDE() {
    // TODO: Deallocate dynamically allocated memory.
}

int &DynamicArrayDE::operator[](size_t index) {
    // TODO: Return the element at index `index`. If `index` is out of bounds, throw `std::out_of_range`.
}

void DynamicArrayDE::push_back(int value) {
    // TODO: Append `value` to the array. Must obtain O(1) amortized complexity over any sequence of calls to
    // `push_front` and `push_back`.
}

void DynamicArrayDE::push_front(int value) {
    // TODO: Prepend `value` to the array. Must obtain O(1) amortized complexity over any sequence of calls to
    // `push_front` and `push_back`.
}
