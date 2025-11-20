#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include "dynamic_array_gbf.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <n> <growth_factor>\n";
        return 1;
    }

    const auto n = std::stoi(argv[1]);
    const auto growth_factor = std::stod(argv[2]);

    if (n <= 0) {
        std::cerr << "Error: n must be a positive integer.\n";
        return 1;
    }

    if (growth_factor <= 1.0) {
        std::cerr << "Error: growth_factor must be greater than one.\n";
        return 1;
    }

    DynamicArrayGBF arr(growth_factor);
    const auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        arr.push_back(i);
    }
    const auto end1 = std::chrono::high_resolution_clock::now();
    const auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    std::cout << "DynamicArrayGBF time: " << duration1 << " ms\n";

    std::vector<int> vec;
    const auto start2 = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < static_cast<std::size_t>(n); ++i) {
        vec.push_back(static_cast<int>(i));
    }
    const auto end2 = std::chrono::high_resolution_clock::now();
    const auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
    std::cout << "std::vector time: " << duration2 << " ms\n";

    return 0;
}
