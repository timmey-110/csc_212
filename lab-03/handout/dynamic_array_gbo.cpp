#include "dynamic_array_gbo.h"

DynamicArrayGBO::DynamicArrayGBO() {
    // TODO: Initialize an empty dynamic array. Any initial capacity is acceptable.
}

DynamicArrayGBO::~DynamicArrayGBO() {
    // TODO: Deallocate dynamically allocated memory.
}

int &DynamicArrayGBO::operator[](size_t index) {
    // TODO: Return the element at index `index`. If `index` is out of bounds, throw `std::out_of_range`.
}

void DynamicArrayGBO::push_back(int value) {
    // TODO: Append `value` to the array. If there are no available slots to store `value`, increase the capacity by one.
}
