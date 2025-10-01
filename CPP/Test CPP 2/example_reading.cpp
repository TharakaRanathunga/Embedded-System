#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream inFile("example.txt"); //opens file for reading
    std::string line;
    
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) { //reads file line by line
            std::cout << line << std::endl;  //prints each line
        }
        inFile.close(); //closes the file
    } else {
        std::cout << "Unable to open the file." << std::endl;
    }  
    return 0;
}