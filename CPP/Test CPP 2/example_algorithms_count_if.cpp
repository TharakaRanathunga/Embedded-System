#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool greater_than_5(int value)  {
    return value > 5;
}

int main() {
    vector<int> nums = {1, 7, 3, 5, 9, 2}; 

    int amount = count_if(nums.begin(), nums.end(), greater_than_5); 

    cout << "There are " << amount << " values greater than 5." ;

    return 0;
}
    