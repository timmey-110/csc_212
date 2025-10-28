#include "dynamic_array_gbf.h"

DynamicArrayGBF::DynamicArrayGBF(double growth_factor) {
    // TODO: Initialize an empty dynamic array. Any initial capacity is acceptable. If `growth_factor` is less than or
    // equal to 1.0, throw `std::invalid_argument`.
}

DynamicArrayGBF::~DynamicArrayGBF() {
    // TODO: Deallocate dynamically allocated memory.
}

int &DynamicArrayGBF::operator[](size_t index) {
    // TODO: Return the element at index `index`. If `index` is out of bounds, throw `std::out_of_range`.
}

void DynamicArrayGBF::push_back(int value) {
    // TODO: Append `value` to the array. If there are no available slots to store `value`, increase the capacity by a
    // factor of `m_growth_factor` rounded up to the nearest integer.
}
