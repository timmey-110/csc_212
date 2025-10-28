#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "perfect_plunder.h"
#include <vector>
#include <cstdint>
#include <algorithm>
#include <random>
#include <memory>

std::shared_ptr<House> make_cul_de_sac(const std::vector<uint32_t> &dollars_values) {
    if (dollars_values.empty()) return nullptr;

    std::vector<std::shared_ptr<House> > houses;
    houses.reserve(dollars_values.size());

    for (auto dollars: dollars_values)
        houses.push_back(std::make_shared<House>(dollars));

    const size_t n = houses.size();
    for (size_t i = 0; i < n; ++i) {
        houses[i]->left() = houses[(i + n - 1) % n];
        houses[i]->right() = houses[(i + 1) % n];
    }

    return houses.front();
}

uint32_t linear_max_plunder(const std::vector<uint32_t> &houses) {
    if (houses.empty()) return 0;
    if (houses.size() == 1) return houses[0];

    uint32_t prev2 = 0;
    uint32_t prev1 = houses[0];
    for (size_t i = 1; i < houses.size(); ++i) {
        auto curr = std::max(prev1, prev2 + houses[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

uint32_t circular_max_plunder(const std::vector<uint32_t> &houses) {
    if (houses.size() == 1) return houses[0];
    std::vector<uint32_t> without_first(houses.begin() + 1, houses.end());
    std::vector<uint32_t> without_last(houses.begin(), houses.end() - 1);
    return std::max(linear_max_plunder(without_first), linear_max_plunder(without_last));
}

TEST_CASE("perfect_plunder - single house") {
    auto cul = make_cul_de_sac({100});
    CHECK(perfect_plunder(cul) == 100);
}

TEST_CASE("perfect_plunder - two houses") {
    auto cul = make_cul_de_sac({100, 200});
    CHECK(perfect_plunder(cul) == 200);
}

TEST_CASE("perfect_plunder - three houses") {
    auto cul = make_cul_de_sac({2, 3, 2});
    CHECK(perfect_plunder(cul) == 3);
}

TEST_CASE("perfect_plunder - four houses") {
    auto cul = make_cul_de_sac({1, 2, 3, 1});
    CHECK(perfect_plunder(cul) == 4);
}

TEST_CASE("perfect_plunder - deterministic") {
    std::vector<uint32_t> dollars;
    for (int i = 1; i <= 10; ++i) dollars.push_back(i % 100);

    auto cul = make_cul_de_sac(dollars);
    uint32_t expected = circular_max_plunder(dollars);
    CHECK(perfect_plunder(cul) == expected);
}

TEST_CASE("perfect_plunder - random small tests") {
    std::mt19937 rng(12345);
    std::uniform_int_distribution<uint32_t> dist(1, 1000);

    for (int run = 0; run < 1000; ++run) {
        std::vector<uint32_t> dollars(10);
        for (auto &m: dollars) m = dist(rng);

        auto cul = make_cul_de_sac(dollars);
        uint32_t expected = circular_max_plunder(dollars);

        CHECK(perfect_plunder(cul) == expected);
    }
}
