#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "strategic_silicon.h"
#include "doctest.h"
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <limits>
#include <cstdint>
#include <numeric>

struct Position {
    int r, c;
};

static Component make_component(std::string name) {
    return Component(std::move(name));
}

static int manhattan(const Position &a, const Position &b) {
    return std::abs(a.r - b.r) + std::abs(a.c - b.c);
}

static std::uint32_t total_cost(const std::vector<Position> &placement,
                                const std::vector<std::pair<int, int> > &connections) {
    std::uint32_t cost = 0;
    for (auto [i,j]: connections) cost += manhattan(placement[i], placement[j]);
    return cost;
}

static std::uint32_t solve_exact(const Device &device, std::size_t height, std::size_t width) {
    std::size_t N = device.components.size();
    std::size_t M = height * width;
    std::vector<Position> cells;
    for (std::size_t r = 0; r < height; ++r)
        for (std::size_t c = 0; c < width; ++c)
            cells.push_back({int(r), int(c)});

    std::vector<std::pair<int, int> > conn_idx;
    for (auto &conn: device.connections) {
        int idx1 = std::distance(device.components.begin(), std::find_if(
                                     device.components.begin(), device.components.end(),
                                     [&](const Component &c) { return c.name == conn.first.name; }));
        int idx2 = std::distance(device.components.begin(), std::find_if(
                                     device.components.begin(), device.components.end(),
                                     [&](const Component &c) { return c.name == conn.second.name; }));
        conn_idx.emplace_back(idx1, idx2);
    }

    std::vector<bool> bitmask(M, false);
    std::fill(bitmask.begin(), bitmask.begin() + N, true);
    std::uint32_t best_cost = std::numeric_limits<std::uint32_t>::max();

    do {
        std::vector<Position> chosen_positions;
        for (std::size_t i = 0; i < M; ++i)
            if (bitmask[i]) chosen_positions.push_back(cells[i]);

        std::vector<int> perm(N);
        std::iota(perm.begin(), perm.end(), 0);
        do {
            std::vector<Position> placement(N);
            for (std::size_t i = 0; i < N; ++i)
                placement[perm[i]] = chosen_positions[i];
            best_cost = std::min(best_cost, total_cost(placement, conn_idx));
        } while (std::next_permutation(perm.begin(), perm.end()));
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return best_cost;
}

static Device random_device(int num_components, int num_connections, std::mt19937 &rng) {
    std::vector<Component> comps;
    for (int i = 0; i < num_components; ++i)
        comps.push_back(make_component("C" + std::to_string(i)));

    std::uniform_int_distribution<int> dist(0, num_components - 1);
    std::vector<std::pair<Component, Component> > conns;
    while ((int) conns.size() < num_connections) {
        int a = dist(rng), b = dist(rng);
        if (a != b) conns.emplace_back(comps[a], comps[b]);
    }

    return Device(std::move(comps), std::move(conns));
}

TEST_CASE("strategic_silicon - randomized small devices") {
    std::mt19937 rng(42);
    const int num_tests = 1000;
    std::uniform_int_distribution<int> comp_dist(2, 5);
    std::uniform_int_distribution<int> conn_dist(1, 6);
    std::uniform_int_distribution<int> size_dist(2, 3);

    for (int t = 0; t < num_tests; ++t) {
        int num_components = comp_dist(rng);
        int num_connections = std::min(conn_dist(rng), num_components * (num_components - 1));
        int height = size_dist(rng);
        int width = size_dist(rng);

        Device device = random_device(num_components, num_connections, rng);
        std::uint32_t exact_cost = solve_exact(device, height, width);
        std::uint32_t actual_cost = strategic_silicon(device, height, width);

        CHECK(actual_cost == exact_cost);
    }
}
