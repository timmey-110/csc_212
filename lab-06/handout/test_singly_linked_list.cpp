#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "singly_linked_list.h"
#include <stdexcept>

TEST_CASE("New list is empty") {
    SinglyLinkedList list;
    CHECK(list.size() == 0);
    CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
    CHECK_THROWS_AS((void)list[0], std::out_of_range);
}

TEST_CASE("push_front adds single element") {
    SinglyLinkedList list;
    list.push_front(10);
    CHECK(list.size() == 1);
    CHECK(list[0] == 10);
}

TEST_CASE("push_front adds multiple elements in correct order") {
    SinglyLinkedList list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    CHECK(list.size() == 3);
    CHECK(list[0] == 30);
    CHECK(list[1] == 20);
    CHECK(list[2] == 10);
}

TEST_CASE("pop_front removes elements and throws when empty") {
    SinglyLinkedList list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    CHECK(list.size() == 3);
    list.pop_front();
    CHECK(list.size() == 2);
    CHECK(list[0] == 20);
    list.pop_front();
    CHECK(list.size() == 1);
    CHECK(list[0] == 10);
    list.pop_front();
    CHECK(list.size() == 0);
    CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
}

TEST_CASE("operator[] returns correct values") {
    SinglyLinkedList list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    CHECK(list[0] == 3);
    CHECK(list[1] == 2);
    CHECK(list[2] == 1);
}

TEST_CASE("operator[] allows modification") {
    SinglyLinkedList list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list[1] = 42;
    CHECK(list[0] == 3);
    CHECK(list[1] == 42);
    CHECK(list[2] == 1);
}

TEST_CASE("operator[] throws on out of range") {
    SinglyLinkedList list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    CHECK_THROWS_AS((void)list[3], std::out_of_range);
    CHECK_THROWS_AS((void)list[99], std::out_of_range);
}

TEST_CASE("Multiple operations combined") {
    SinglyLinkedList list;
    for (int i = 0; i < 5; i++) {
        list.push_front(i);
    }
    CHECK(list.size() == 5);
    CHECK(list[0] == 4);
    CHECK(list[1] == 3);
    CHECK(list[2] == 2);
    CHECK(list[3] == 1);
    CHECK(list[4] == 0);
    list.pop_front();
    CHECK(list.size() == 4);
    CHECK(list[0] == 3);
    list.pop_front();
    CHECK(list.size() == 3);
    CHECK(list[0] == 2);
}

TEST_CASE("List can be drained to zero and reused") {
    SinglyLinkedList list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    CHECK(list.size() == 3);
    list.pop_front();
    list.pop_front();
    list.pop_front();
    CHECK(list.size() == 0);
    CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
    CHECK_THROWS_AS((void)list[0], std::out_of_range);
    list.push_front(42);
    CHECK(list.size() == 1);
    CHECK(list[0] == 42);
    list.push_front(99);
    CHECK(list.size() == 2);
    CHECK(list[0] == 99);
    CHECK(list[1] == 42);
    list.pop_front();
    CHECK(list.size() == 1);
    CHECK(list[0] == 42);
}

TEST_CASE("Stress test with many push/pop operations") {
    SinglyLinkedList list;
    const int N = 10000;
    for (int i = 0; i < N; i++) {
        list.push_front(i);
    }
    CHECK(list.size() == N);
    CHECK(list[0] == N - 1);
    CHECK(list[1] == N - 2);
    CHECK(list[N - 1] == 0);
    for (int i = 0; i < N; i++) {
        list.pop_front();
    }
    CHECK(list.size() == 0);
    list.push_front(123);
    CHECK(list.size() == 1);
    CHECK(list[0] == 123);
}

TEST_CASE("Access after mutation does not affect other elements") {
    SinglyLinkedList list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list[1] = 99;
    CHECK(list[0] == 3);
    CHECK(list[1] == 99);
    CHECK(list[2] == 1);
}

TEST_CASE("Sequential drain multiple times") {
    SinglyLinkedList list;
    for (int cycle = 0; cycle < 3; cycle++) {
        for (int i = 0; i < 5; i++) {
            list.push_front(i);
        }
        CHECK(list.size() == 5);
        for (int i = 0; i < 5; i++) {
            list.pop_front();
        }
        CHECK(list.size() == 0);
    }
}

TEST_CASE("Alternating push and pop keeps list consistent") {
    SinglyLinkedList list;
    list.push_front(1);
    CHECK(list[0] == 1);
    list.pop_front();
    CHECK(list.size() == 0);
    list.push_front(2);
    CHECK(list[0] == 2);
    list.push_front(3);
    CHECK(list[0] == 3);
    list.pop_front();
    CHECK(list[0] == 2);
}

TEST_CASE("Boundary access at last valid index") {
    SinglyLinkedList list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    CHECK(list.size() == 3);
    CHECK(list[2] == 10);
    CHECK_THROWS_AS((void)list[3], std::out_of_range);
}

TEST_CASE("Exception safety: list remains valid after out_of_range") {
    SinglyLinkedList list;
    list.push_front(5);
    list.push_front(6);
    CHECK_THROWS_AS((void)list[10], std::out_of_range);
    CHECK(list.size() == 2);
    CHECK(list[0] == 6);
    CHECK(list[1] == 5);
    list.pop_front();
    CHECK(list.size() == 1);
}
