#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "set.h"
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

TEST_CASE("empty set") {
    Set s;
    std::set<int> ref;

    CHECK_EQ(s.size(), ref.size());
    for (int i = -10; i <= 10; ++i)
        CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("insert single element") {
    Set s;
    std::set<int> ref;

    s.insert(42);
    ref.insert(42);

    CHECK_EQ(s.size(), ref.size());
    CHECK_EQ(s.contains(42), ref.count(42) != 0);
}

TEST_CASE("incremental build test") {
    Set s;
    std::set<int> ref;

    std::vector<int> values(50);
    std::iota(values.begin(), values.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);

    // Incrementally insert and check
    for (size_t i = 0; i < values.size(); ++i) {
        int val = values[i];
        s.insert(val);
        ref.insert(val);

        CHECK_EQ(s.size(), ref.size());

        for (int j = 1; j <= 50; ++j) {
            bool expected = ref.count(j) != 0;
            CHECK_EQ(s.contains(j), expected);
        }
    }
}

TEST_CASE("erase elements one by one to empty") {
    Set s;
    std::set<int> ref;

    for (int i = 1; i <= 20; ++i) {
        s.insert(i);
        ref.insert(i);
    }

    std::vector<int> values(20);
    std::iota(values.begin(), values.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);

    for (int val: values) {
        s.erase(val);
        ref.erase(val);
        CHECK_EQ(s.size(), ref.size());
        for (int j = 1; j <= 20; ++j)
            CHECK_EQ(s.contains(j), ref.count(j) != 0);
    }

    CHECK_EQ(s.size(), 0);
}

TEST_CASE("build back up after draining") {
    Set s;
    std::set<int> ref;

    std::vector<int> values(20);
    std::iota(values.begin(), values.end(), 1);

    for (int val: values) {
        s.insert(val);
        ref.insert(val);
        CHECK_EQ(s.size(), ref.size());
        for (int j = 1; j <= 20; ++j)
            CHECK_EQ(s.contains(j), ref.count(j) != 0);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);
    for (int val: values) {
        s.erase(val);
        ref.erase(val);
        CHECK_EQ(s.size(), ref.size());
        for (int j = 1; j <= 20; ++j)
            CHECK_EQ(s.contains(j), ref.count(j) != 0);
    }

    CHECK_EQ(s.size(), 0);

    // Build up again in reverse order
    for (auto it = values.rbegin(); it != values.rend(); ++it) {
        s.insert(*it);
        ref.insert(*it);
        CHECK_EQ(s.size(), ref.size());
        for (int j = 1; j <= 20; ++j)
            CHECK_EQ(s.contains(j), ref.count(j) != 0);
    }
}
