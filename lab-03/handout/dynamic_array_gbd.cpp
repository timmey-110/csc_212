#include "dynamic_array_gbd.h"

DynamicArrayGBD::DynamicArrayGBD() {
    // TODO: Initialize an empty dynamic array. Any initial capacity is acceptable.
}

DynamicArrayGBD::~DynamicArrayGBD() {
    // TODO: Deallocate dynamically allocated memory.
}

int &DynamicArrayGBD::operator[](size_t index) {
    // TODO: Return the element at index `index`. If `index` is out of bounds, throw `std::out_of_range`.
}

void DynamicArrayGBD::push_back(int value) {
    // TODO: Append `value` to the array. If there are no available slots to store `value`, double the capacity.
}
