#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdint>

int get_pointed_value(int* pointer) {
    return *pointer;
}

void set_pointed_value(int* pointer, int value) {
    *pointer = value;
}

uintptr_t get_pointer_address(int* pointer) {
    return reinterpret_cast<uintptr_t>(pointer);
}

TEST_CASE("get_pointed_value returns value stored at pointer") {
    int x = 99;
    int* p = &x;

    REQUIRE(get_pointed_value(p) == 99);
}

TEST_CASE("set_pointed_value modifies the value at pointer") {
    int x = 0;
    int* p = &x;

    set_pointed_value(p, 123);

    REQUIRE(x == 123);
    REQUIRE(get_pointed_value(p) == 123);
}

TEST_CASE("get_pointer_address returns correct address") {
    int x = 42;
    int* p = &x;
    
    uintptr_t addr = get_pointer_address(p);
    
    REQUIRE(reinterpret_cast<int*>(addr) == p);
}