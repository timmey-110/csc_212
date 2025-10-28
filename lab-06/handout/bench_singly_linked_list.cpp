#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "singly_linked_list.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <n>\n";
        return 1;
    }

    const auto n = std::stoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Error: n must be a positive integer.\n";
        return 1;
    }

    SinglyLinkedList list;
    const auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        list.push_front(i);
    }
    const auto end1 = std::chrono::high_resolution_clock::now();
    const auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count();
    std::cout << "SinglyLinkedList push_front time: " << duration1 << " ns\n";

    std::vector<int> vec;
    const auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        vec.insert(vec.begin(), i);
    }
    const auto end2 = std::chrono::high_resolution_clock::now();
    const auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();
    std::cout << "std::vector push_front time: " << duration2 << " ns\n";

    return 0;
}
