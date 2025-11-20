#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <string>
#include "subset_sum.h"

int main(const int argc, const char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>\n";
        return 1;
    }

    const auto n = std::stoi(argv[1]);
    if (n <= 0) {
        std::cerr << "n must be positive\n";
        return 1;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 1000000);

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = dist(rng);
    }

    std::shuffle(arr.begin(), arr.end(), rng);
    const auto subset_size = n / 2;
    int target = 0;
    for (int i = 0; i < subset_size; ++i) {
        target += arr[i];
    }

    const auto start = std::chrono::high_resolution_clock::now();
    const auto result = subset_sum(arr, target);
    const auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "subset_sum result: " << result
            << ", time: " << duration.count() << " ms\n";

    return 0;
}
