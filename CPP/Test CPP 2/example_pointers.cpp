#include <iostream>

int main() {
    int value = 42;        // a normal integer
    int* ptr = &value;     // a pointer holding the address of 'value'

    std::cout << *ptr;     // dereference pointer -> outputs 42

    return 0;
}
