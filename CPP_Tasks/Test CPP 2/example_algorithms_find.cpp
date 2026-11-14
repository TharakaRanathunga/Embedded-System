#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {10, 20, 30, 40}; 

    auto it = std::find(nums.begin(), nums.end(), 30); 

    if (it != nums.end()) {
        std::cout << "Found: " << *it << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }
    

    return 0;
}