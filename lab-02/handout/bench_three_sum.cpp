#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include "three_sum.h"
#include "three_sum_fast.h"

int main(const int argc, const char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>\n";
        return 1;
    }

    const auto n = std::stoi(argv[1]);
    if (n <= 0) {
        std::cerr << "n must be a positive integer\n";
        return 1;
    }

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }
    const auto target = 3 * n;

    const auto runs = std::max(1, 1000 / n);

    // Benchmark three_sum
    double total_time1 = 0.0;
    bool result1 = false;
    for (int i = 0; i < runs; ++i) {
        const auto start = std::chrono::high_resolution_clock::now();
        result1 = three_sum(arr, target);
        const auto end = std::chrono::high_resolution_clock::now();
        total_time1 += std::chrono::duration<double, std::milli>(end - start).count();
    }
    std::cout << "three_sum result: " << result1
            << ", average time over " << runs << " runs: "
            << (total_time1 / runs) << " ms\n";

    // Benchmark three_sum_fast
    double total_time2 = 0.0;
    bool result2 = false;
    for (int i = 0; i < runs; ++i) {
        const auto start = std::chrono::high_resolution_clock::now();
        result2 = three_sum_fast(arr, target);
        const auto end = std::chrono::high_resolution_clock::now();
        total_time2 += std::chrono::duration<double, std::milli>(end - start).count();
    }
    std::cout << "three_sum_fast result: " << result2
            << ", average time over " << runs << " runs: "
            << (total_time2 / runs) << " ms\n";

    return 0;
}
