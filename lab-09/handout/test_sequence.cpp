#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "sequence.h"
#include <vector>
#include <stdexcept>

TEST_CASE("empty sequence") {
    Sequence s;
    CHECK_EQ(s.size(), 0);
    CHECK_THROWS_AS((void)s[0], std::out_of_range);
    CHECK_THROWS_AS(s.erase(0), std::out_of_range);
    CHECK_THROWS_AS(s.insert(1, 42), std::out_of_range);
}

TEST_CASE("insert single element at index 0") {
    Sequence s;
    s.insert(0, 42);
    CHECK_EQ(s.size(), 1);
    CHECK_EQ(s[0], 42);
    CHECK_THROWS_AS((void)s[1], std::out_of_range);
    CHECK_THROWS_AS(s.insert(2, 99), std::out_of_range);
}

TEST_CASE("insert multiple elements at increasing indices") {
    Sequence s;
    for (int i = 0; i < 5; ++i)
        s.insert(i, i * 10);

    CHECK_EQ(s.size(), 5);
    for (size_t i = 0; i < 5; ++i)
        CHECK_EQ(s[i], i*10);

    CHECK_THROWS_AS(s.insert(6, 100), std::out_of_range);
}

TEST_CASE("insert at arbitrary positions") {
    Sequence s;
    s.insert(0, 1);
    s.insert(1, 3);
    s.insert(1, 2);
    s.insert(0, 0);
    s.insert(4, 4);

    CHECK_EQ(s.size(), 5);
    std::vector<int> expected = {0, 1, 2, 3, 4};
    for (size_t i = 0; i < expected.size(); ++i)
        CHECK_EQ(s[i], expected[i]);

    CHECK_THROWS_AS(s.insert(6, 99), std::out_of_range);
}

TEST_CASE("erase single element") {
    Sequence s;
    for (int v: {10, 20, 30, 40})
        s.insert(s.size(), v);

    s.erase(2);
    std::vector<int> expected = {10, 20, 40};
    CHECK_EQ(s.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i)
        CHECK_EQ(s[i], expected[i]);

    CHECK_THROWS_AS(s.erase(3), std::out_of_range);
}

TEST_CASE("erase multiple elements") {
    Sequence s;
    for (int v: {1, 2, 3, 4, 5})
        s.insert(s.size(), v);

    s.erase(0);
    s.erase(2);
    s.erase(s.size() - 1);

    std::vector<int> expected = {2, 3};
    CHECK_EQ(s.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i)
        CHECK_EQ(s[i], expected[i]);

    CHECK_THROWS_AS(s.erase(2), std::out_of_range);
}

TEST_CASE("sequence emptied and reused") {
    Sequence s;
    for (int i = 0; i < 5; ++i)
        s.insert(s.size(), i * 10);

    for (size_t i = 0; i < 5; ++i)
        s.erase(0);

    CHECK_EQ(s.size(), 0);
    CHECK_THROWS_AS((void)s[0], std::out_of_range);
    CHECK_THROWS_AS(s.erase(0), std::out_of_range);
    CHECK_THROWS_AS(s.insert(1, 42), std::out_of_range);

    for (int i = 0; i < 3; ++i)
        s.insert(i, i * 100);

    std::vector<int> expected = {0, 100, 200};
    for (size_t i = 0; i < expected.size(); ++i)
        CHECK_EQ(s[i], expected[i]);

    CHECK_THROWS_AS(s.insert(4, 999), std::out_of_range);
    CHECK_THROWS_AS(s.erase(3), std::out_of_range);
}

TEST_CASE("insert and erase at random positions") {
    Sequence s;
    for (int v: {10, 20, 30, 40, 50})
        s.insert(s.size(), v);

    s.insert(2, 25);
    s.erase(0);
    s.insert(1, 15);
    s.erase(s.size() - 1);

    std::vector<int> expected = {15, 20, 25, 40};
    CHECK_EQ(s.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i)
        CHECK_EQ(s[i], expected[i]);

    CHECK_THROWS_AS(s.insert(5,99), std::out_of_range);
    CHECK_THROWS_AS(s.erase(4), std::out_of_range);
    CHECK_THROWS_AS((void)s[4], std::out_of_range);
}
