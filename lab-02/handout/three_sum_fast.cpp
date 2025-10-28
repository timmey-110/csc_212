#include "three_sum_fast.h"
#include <algorithm>

bool three_sum_fast(const std::vector<int> &arr, const int target) {
    const auto n = arr.size();
    if (n < 3) {
        return false;
    }

    std::vector<int> nums(arr);
    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 2; ++i) {
        auto left = i + 1;
        auto right = n - 1;

        while (left < right) {
            const auto sum = nums[i] + nums[left] + nums[right];
            if (sum == target) {
                return true;
            }

            if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return false;
}
