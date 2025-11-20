#include "two_sum_fast.h"
#include <algorithm>

bool two_sum_fast(const std::vector<int> &arr, const int target) {
    const auto n = arr.size();
    if (n < 2) {
        return false;
    }

    std::vector<int> nums(arr);
    std::sort(nums.begin(), nums.end());

    auto left = 0;
    auto right = n - 1;
    while (left < right) {
        const auto sum = nums[left] + nums[right];
        if (sum == target) {
            return true;
        }
        if (sum < target) {
            ++left;
        } else {
            --right;
        }
    }

    return false;
}
