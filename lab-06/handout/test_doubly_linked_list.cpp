#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "doubly_linked_list.h"
#include <stdexcept>

TEST_CASE("Empty list") {
    DoublyLinkedList list;
    CHECK(list.size() == 0);
    CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
    CHECK_THROWS_AS(list.pop_back(), std::out_of_range);
    CHECK_THROWS_AS((void)list[0], std::out_of_range);
}

TEST_CASE("Push front single element") {
    DoublyLinkedList list;
    list.push_front(10);
    CHECK(list.size() == 1);
    CHECK(list[0] == 10);
}

TEST_CASE("Push back single element") {
    DoublyLinkedList list;
    list.push_back(20);
    CHECK(list.size() == 1);
    CHECK(list[0] == 20);
}

TEST_CASE("Push front multiple elements") {
    DoublyLinkedList list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    CHECK(list.size() == 3);
    CHECK(list[0] == 3);
    CHECK(list[1] == 2);
    CHECK(list[2] == 1);
}

TEST_CASE("Push back multiple elements") {
    DoublyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    CHECK(list.size() == 3);
    CHECK(list[0] == 1);
    CHECK(list[1] == 2);
    CHECK(list[2] == 3);
}

TEST_CASE("Pop front reduces size and removes correct element") {
    DoublyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.pop_front();
    CHECK(list.size() == 2);
    CHECK(list[0] == 2);
}

TEST_CASE("Pop back reduces size and removes correct element") {
    DoublyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.pop_back();
    CHECK(list.size() == 2);
    CHECK(list[1] == 2);
}

TEST_CASE("Operator[] access and modification") {
    DoublyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    CHECK(list[0] == 1);
    CHECK(list[1] == 2);
    CHECK(list[2] == 3);

    list[1] = 42;
    CHECK(list[1] == 42);
}

TEST_CASE("Operator[] throws on out of range") {
    DoublyLinkedList list;
    list.push_back(1);
    CHECK_THROWS_AS((void)list[1], std::out_of_range);
    CHECK_THROWS_AS((void)list[10], std::out_of_range);
}

TEST_CASE("Drain/reuse with push_front -> pop_front") {
    DoublyLinkedList list;
    for (int i = 0; i < 5; i++) list.push_front(i);
    for (int i = 0; i < 5; i++) list.pop_front();
    CHECK(list.size() == 0);
    list.push_front(42);
    CHECK(list.size() == 1);
    CHECK(list[0] == 42);
}

TEST_CASE("Drain/reuse with push_back -> pop_back") {
    DoublyLinkedList list;
    for (int i = 0; i < 5; i++) list.push_back(i);
    for (int i = 0; i < 5; i++) list.pop_back();
    CHECK(list.size() == 0);
    list.push_back(99);
    CHECK(list.size() == 1);
    CHECK(list[0] == 99);
}

TEST_CASE("Drain/reuse with push_front -> pop_back") {
    DoublyLinkedList list;
    for (int i = 0; i < 5; i++) list.push_front(i);
    for (int i = 0; i < 5; i++) list.pop_back();
    CHECK(list.size() == 0);
    list.push_front(123);
    CHECK(list.size() == 1);
    CHECK(list[0] == 123);
}

TEST_CASE("Drain/reuse with push_back -> pop_front") {
    DoublyLinkedList list;
    for (int i = 0; i < 5; i++) list.push_back(i);
    for (int i = 0; i < 5; i++) list.pop_front();
    CHECK(list.size() == 0);
    list.push_back(456);
    CHECK(list.size() == 1);
    CHECK(list[0] == 456);
}

TEST_CASE("Sequential drain multiple times") {
    DoublyLinkedList list;
    for (int cycle = 0; cycle < 3; cycle++) {
        for (int i = 0; i < 5; i++) list.push_back(i);
        CHECK(list.size() == 5);
        for (int i = 0; i < 5; i++) list.pop_front();
        CHECK(list.size() == 0);
    }
}

TEST_CASE("Alternating push and pop operations") {
    DoublyLinkedList list;
    list.push_front(1);
    CHECK(list[0] == 1);
    list.pop_back();
    CHECK(list.size() == 0);

    list.push_back(2);
    CHECK(list[0] == 2);
    list.push_front(3);
    CHECK(list[0] == 3);
    list.pop_front();
    CHECK(list[0] == 2);
}

TEST_CASE("Boundary access at last valid index") {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    CHECK(list[2] == 30);
    CHECK_THROWS_AS((void)list[3], std::out_of_range);
}

TEST_CASE("Stress test with many push/pop operations") {
    DoublyLinkedList list;
    const int N = 10000;
    for (int i = 0; i < N; i++) list.push_back(i);
    CHECK(list.size() == N);
    CHECK(list[0] == 0);
    CHECK(list[N - 1] == N - 1);

    for (int i = 0; i < N; i++) list.pop_front();
    CHECK(list.size() == 0);

    for (int i = 0; i < N; i++) list.push_front(i);
    CHECK(list.size() == N);
    CHECK(list[0] == N - 1);
    CHECK(list[N - 1] == 0);
}
