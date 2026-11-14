#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {5, 2, 9, 1}; // Unsorted numbers

    std::sort(nums.begin(), nums.end()); // Sorts in ascending order

    for (int num : nums) {
        std::cout << num << " "; // Prints sorted numbers
    }
    

    return 0;
}