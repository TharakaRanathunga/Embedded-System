#include <iostream>
using namespace std;

int main() {
    int* arr = new int[5]; // allocates array

    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10; // fills array
    }

    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " "; // prints array
    }

    delete [] arr; //free memory
    return 0;
}
