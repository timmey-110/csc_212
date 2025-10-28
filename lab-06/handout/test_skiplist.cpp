#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "skiplist.h"

TEST_CASE("New skip list is empty") {
    SkipList list;
    CHECK(list.size() == 0);
    CHECK_FALSE(list.contains(10));
}

TEST_CASE("Insert single element") {
    SkipList list;
    list.insert(42);
    CHECK(list.size() == 1);
    CHECK(list.contains(42));
    CHECK_FALSE(list.contains(0));
}

TEST_CASE("Insert multiple elements") {
    SkipList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(20);
    CHECK(list.size() == 3);
    CHECK(list.contains(10));
    CHECK(list.contains(20));
    CHECK(list.contains(30));
    CHECK_FALSE(list.contains(40));
}

TEST_CASE("Erase element") {
    SkipList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    CHECK(list.contains(2));
    list.erase(2);
    CHECK_FALSE(list.contains(2));
    CHECK(list.size() == 2);
    list.erase(42);
    CHECK(list.size() == 2);
}

TEST_CASE("Erase all elements") {
    SkipList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.erase(1);
    list.erase(2);
    list.erase(3);
    CHECK(list.size() == 0);
    CHECK_FALSE(list.contains(1));
    CHECK_FALSE(list.contains(2));
    CHECK_FALSE(list.contains(3));
}

TEST_CASE("Insert and erase repeatedly") {
    SkipList list;
    for (int i = 0; i < 5; i++) list.insert(i);
    CHECK(list.size() == 5);

    for (int i = 0; i < 5; i++) {
        list.erase(i);
        CHECK_FALSE(list.contains(i));
    }

    CHECK(list.size() == 0);

    for (int i = 10; i < 15; i++) list.insert(i);
    CHECK(list.size() == 5);
    for (int i = 10; i < 15; i++)
        CHECK(list.contains(i));
}

TEST_CASE("Contains after multiple inserts and erases") {
    SkipList list;
    for (int i = 0; i < 10; i++) list.insert(i);
    for (int i = 0; i < 10; i += 2) list.erase(i);
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0)
            CHECK_FALSE(list.contains(i));
        else
            CHECK(list.contains(i));
    }
}

TEST_CASE("Insert duplicates have no effect on size") {
    SkipList list;
    list.insert(1);
    list.insert(1);
    list.insert(1);
    CHECK(list.size() == 1);
    list.erase(1);
    CHECK(list.size() == 0);
}

TEST_CASE("Stress test: many inserts and erases") {
    SkipList list;
    const int N = 10000;

    for (int i = 0; i < N; i++) list.insert(i);
    CHECK(list.size() == N);

    for (int i = 0; i < N; i += 2) list.erase(i);
    CHECK(list.size() == N / 2);

    for (int i = 1; i < N; i += 2)
        CHECK(list.contains(i));
    for (int i = 0; i < N; i += 2)
        CHECK_FALSE(list.contains(i));
}

TEST_CASE("Interleaved insert and erase") {
    SkipList list;
    list.insert(1);
    list.insert(2);
    list.erase(1);
    list.insert(3);
    list.erase(2);
    list.insert(4);
    CHECK(list.size() == 2);
    CHECK(list.contains(3));
    CHECK(list.contains(4));
    CHECK_FALSE(list.contains(1));
    CHECK_FALSE(list.contains(2));
}

TEST_CASE("Erase non-existent element does nothing") {
    SkipList list;
    list.insert(10);
    list.erase(42);
    CHECK(list.size() == 1);
    CHECK(list.contains(10));
}

TEST_CASE("Insert after erasing all elements") {
    SkipList list;
    list.insert(1);
    list.insert(2);
    list.erase(1);
    list.erase(2);
    CHECK(list.size() == 0);
    list.insert(3);
    CHECK(list.size() == 1);
    CHECK(list.contains(3));
}
