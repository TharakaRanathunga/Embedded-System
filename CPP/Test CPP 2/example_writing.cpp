#include <fstream>
#include <iostream>

int main() {
    std::ofstream outFile("example.txt"); //creates and opens file

    if (!outFile.is_open()) {
        outFile << "Hello, file!" << std::endl;
        outFile << "This is a second line." << std::endl;
        outFile.close(); //Closes the file
    } else {
        std::cout << "Unable to open the file." << std::endl;
    }  
    return 0;
}
