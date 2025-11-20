#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "genetic_gap.h"
#include "doctest.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cstdint>

inline DNA make_dna(const std::initializer_list<Base> bases) {
    return DNA(std::vector<Base>(bases));
}

uint32_t genetic_gap_dp(const DNA &dna1, const DNA &dna2) {
    const size_t n = dna1.size();
    const size_t m = dna2.size();
    std::vector<std::vector<uint32_t> > dp(n + 1, std::vector<uint32_t>(m + 1, 0));

    for (size_t i = 0; i <= n; ++i) dp[i][0] = static_cast<uint32_t>(i);
    for (size_t j = 0; j <= m; ++j) dp[0][j] = static_cast<uint32_t>(j);

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            const uint32_t cost = (dna1[i - 1] != dna2[j - 1]) ? 1u : 0u;
            dp[i][j] = std::min({
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + cost
            });
        }
    }
    return dp[n][m];
}

Base random_base(std::mt19937 &rng) {
    std::uniform_int_distribution<int> dist(0, 3);
    return static_cast<Base>(dist(rng));
}

DNA random_dna(const size_t length, std::mt19937 &rng) {
    std::vector<Base> seq(length);
    for (auto &b: seq) b = random_base(rng);
    return DNA(std::move(seq));
}

TEST_CASE("genetic_gap - identical sequences") {
    auto dna1 = make_dna({Base::Adenine, Base::Cytosine, Base::Guanine, Base::Thymine});
    auto dna2 = make_dna({Base::Adenine, Base::Cytosine, Base::Guanine, Base::Thymine});
    CHECK(genetic_gap(dna1, dna2) == 0);
}

TEST_CASE("genetic_gap - single mutation") {
    auto dna1 = make_dna({Base::Adenine, Base::Cytosine, Base::Guanine});
    auto dna2 = make_dna({Base::Adenine, Base::Thymine, Base::Guanine});
    CHECK(genetic_gap(dna1, dna2) == 1);
}

TEST_CASE("genetic_gap - multiple mutations") {
    auto dna1 = make_dna({Base::Adenine, Base::Cytosine, Base::Guanine});
    auto dna2 = make_dna({Base::Thymine, Base::Guanine, Base::Cytosine});
    CHECK(genetic_gap(dna1, dna2) == 3);
}

TEST_CASE("genetic_gap - empty sequences") {
    auto empty1 = make_dna({});
    auto empty2 = make_dna({});
    CHECK(genetic_gap(empty1, empty2) == 0);

    auto nonempty = make_dna({Base::Adenine});
    CHECK(genetic_gap(empty1, nonempty) == 1);
    CHECK(genetic_gap(nonempty, empty2) == 1);
}

TEST_CASE("genetic_gap - random sequences verified with DP") {
    std::mt19937 rng(42);
    constexpr size_t num_tests = 1000;

    for (size_t t = 0; t < num_tests; ++t) {
        auto dna1 = random_dna(5 + rng() % 10, rng);
        auto dna2 = random_dna(5 + rng() % 10, rng);

        uint32_t expected = genetic_gap_dp(dna1, dna2);
        uint32_t actual = genetic_gap(dna1, dna2);

        CHECK(actual == expected);
    }
}
