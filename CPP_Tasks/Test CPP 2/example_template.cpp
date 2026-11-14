#include <iostream>

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add<int>(3, 4) << std::endl;         // Works with integers
    std::cout << add<double>(3.4, 2.5) << std::endl;     // Works with doubles
    return 0;
}




