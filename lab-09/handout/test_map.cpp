#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "map.h"
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

TEST_CASE("empty map") {
    Map m;
    std::map<int, int> ref;

    CHECK_EQ(m.size(), ref.size());
}

TEST_CASE("insert single element") {
    Map m;
    std::map<int, int> ref;

    m.insert(42, 100);
    ref[42] = 100;

    CHECK_EQ(m.size(), ref.size());
    CHECK_EQ(m[42], ref[42]);
}

TEST_CASE("insert multiple unique elements") {
    Map m;
    std::map<int, int> ref;

    std::vector<int> keys = {5, 2, 8, 1, 3, 7, 9};
    for (size_t i = 0; i < keys.size(); ++i) {
        m.insert(keys[i], static_cast<int>(i * 10));
        ref[keys[i]] = static_cast<int>(i * 10);
    }

    CHECK_EQ(m.size(), ref.size());
    for (auto &[k,v]: ref)
        CHECK_EQ(m[k], v);
}

TEST_CASE("operator[] updates values") {
    Map m;
    std::map<int, int> ref;

    m[10] = 100;
    ref[10] = 100;
    CHECK_EQ(m[10], ref[10]);

    m[10] = 200;
    ref[10] = 200;
    CHECK_EQ(m[10], ref[10]);

    m[20] = 50;
    ref[20] = 50;
    CHECK_EQ(m[20], ref[20]);

    CHECK_EQ(m.size(), ref.size());
}

TEST_CASE("erase elements") {
    Map m;
    std::map<int, int> ref;

    std::vector<int> keys = {5, 2, 8, 1, 3, 7, 9};
    for (size_t i = 0; i < keys.size(); ++i) {
        m.insert(keys[i], static_cast<int>(i * 10));
        ref[keys[i]] = static_cast<int>(i * 10);
    }

    std::vector<int> toErase = {3, 8, 1};
    for (int k: toErase) {
        m.erase(k);
        ref.erase(k);
    }

    CHECK_EQ(m.size(), ref.size());
    for (auto &[k,v]: ref)
        CHECK_EQ(m[k], v);
}

TEST_CASE("erase non-existing keys (no effect)") {
    Map m;
    std::map<int, int> ref;

    std::vector<int> keys = {10, 20, 30};
    for (int k: keys) {
        m.insert(k, k * 10);
        ref[k] = k * 10;
    }

    std::vector<int> toErase = {5, 15, 25, 35};
    for (int k: toErase) {
        m.erase(k);
        ref.erase(k);
    }

    CHECK_EQ(m.size(), ref.size());
    for (auto &[k,v]: ref)
        CHECK_EQ(m[k], v);
}

TEST_CASE("randomized insert/erase consistency") {
    Map m;
    std::map<int, int> ref;

    std::vector<int> keys(100);
    std::iota(keys.begin(), keys.end(), 0);

    std::mt19937 rng(12345);
    std::shuffle(keys.begin(), keys.end(), rng);

    for (int k: keys) {
        m.insert(k, k * 5);
        ref[k] = k * 5;
    }

    CHECK_EQ(m.size(), ref.size());
    for (auto &[k,v]: ref)
        CHECK_EQ(m[k], v);

    std::shuffle(keys.begin(), keys.end(), rng);
    for (int i = 0; i < 50; ++i) {
        m.erase(keys[i]);
        ref.erase(keys[i]);
    }

    CHECK_EQ(m.size(), ref.size());
    for (auto &[k,v]: ref)
        CHECK_EQ(m[k], v);
}

TEST_CASE("erase all keys to size 0 and reinsert") {
    Map m;
    std::map<int, int> ref;

    std::vector<int> keys = {5, 3, 7, 2, 4, 6, 8};
    for (size_t i = 0; i < keys.size(); ++i) {
        m.insert(keys[i], static_cast<int>(i * 10));
        ref[keys[i]] = static_cast<int>(i * 10);
    }

    for (int k: keys) {
        m.erase(k);
        ref.erase(k);
        CHECK_EQ(m.size(), ref.size());
    }

    CHECK_EQ(m.size(), 0);
    CHECK_EQ(ref.size(), 0);

    for (int i = -3; i <= 3; ++i) {
        m[i] = i * 100;
        ref[i] = i * 100;
        CHECK_EQ(m.size(), ref.size());
        for (int j = -3; j <= 3; ++j)
            CHECK_EQ(m[j], ref[j]);
    }

    CHECK_EQ(m.size(), ref.size());
}

TEST_CASE("interleaved insert/erase and operator[]") {
    Map m;
    std::map<int, int> ref;

    for (int i = 0; i < 50; ++i) {
        if (i % 3 == 0) {
            m[i] = i * 10;
            ref[i] = i * 10;
        } else {
            m.erase(i - 1);
            ref.erase(i - 1);
        }
        CHECK_EQ(m.size(), ref.size());
        for (auto &[k,v]: ref)
            CHECK_EQ(m[k], v);
    }
}
