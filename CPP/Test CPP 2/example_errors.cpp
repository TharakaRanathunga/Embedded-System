#include <iostream>
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero!");
    }
    return a / b;
}

int main() {
    try {
        std::cout << divide(10, 0) << std::endl; // This will throw an exception
    } 
    catch (const std::invalid_argument& e) {   // catch the correct type
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {          // fallback for all std exceptions
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}