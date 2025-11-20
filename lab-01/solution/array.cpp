#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>

class Array {
private:
    int* m_data;
    int m_size;

public:
    Array(int size, int default_value) {
        // TODO: Initialize the member variables of the `Array` object. After dynamically allocating `m_data`, fill it 
        // with `default_value`.
        m_data = new int[size];
        for (int i = 0; i < size; ++i) {
            m_data[i] = default_value;
        }
        m_size = size;
    }
    
    ~Array() {
        // TODO: Deallocate `m_data`.
        delete[] m_data;
    }
    
    // C++ magic. Feel free to ignore these two lines, or ask a staff member if you are curious.
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;
    
    int get(int idx) {
        // TODO: Return the element at index `idx` in the array. If `idx` is out-of-bounds, throw an `std::out_of_range`
        // exception.
        if (idx < 0 || idx >= m_size) {
            throw std::out_of_range("get with out-of-bounds index");
        }
        return m_data[idx];
    }
    
    void set(int idx, int value) {
        // TODO: Set the element at index `idx` in the array to `value`. If `idx` is out-of-bounds, throw an 
        // `std::out_of_range` exception.
        if (idx < 0 || idx >= m_size) {
            throw std::out_of_range("set with out-of-bounds index");
        }
        m_data[idx] = value;
    }
    
    int size() {
        // TODO: Return the size of the array.
        return m_size;
    }
};

TEST_CASE("Array initializes with default value") {
    Array arr(5, 42);
    REQUIRE(arr.size() == 5);

    for (int i = 0; i < arr.size(); i++) {
        REQUIRE(arr.get(i) == 42);
    }
}

TEST_CASE("Array set and get work correctly") {
    Array arr(3, 0);
    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);

    REQUIRE(arr.get(0) == 10);
    REQUIRE(arr.get(1) == 20);
    REQUIRE(arr.get(2) == 30);
}

TEST_CASE("Array overwriting values") {
    Array arr(2, 7);
    arr.set(0, 100);
    REQUIRE(arr.get(0) == 100);
}

TEST_CASE("Array throws on get out-of-bounds") {
    Array arr(3, 0);
    REQUIRE_THROWS_AS(arr.get(-1), std::out_of_range);
    REQUIRE_THROWS_AS(arr.get(3), std::out_of_range);
}

TEST_CASE("Array throws on set out-of-bounds") {
    Array arr(2, 0);
    REQUIRE_THROWS_AS(arr.set(-1, 10), std::out_of_range);
    REQUIRE_THROWS_AS(arr.set(2, 20), std::out_of_range);
}

TEST_CASE("Array size remains constant after set") {
    Array arr(4, 5);
    REQUIRE(arr.size() == 4);
    arr.set(1, 50);
    REQUIRE(arr.size() == 4);
}