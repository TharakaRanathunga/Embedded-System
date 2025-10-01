#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string brand;
    int year;

    void honk() {
        cout << "Beep beep!"  <<endl;
     }
};



int main() {
    Car myCar;
    myCar.brand = "Toyota";
    myCar.year = 2020;
    myCar.honk();

    return 0;
}