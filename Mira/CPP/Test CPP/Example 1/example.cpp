#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>

using namespace std;

int main() {
    string name = "Tharaka";
    vector<int> scores = {85,90,95};
    map<string, int> ageMap;
    ageMap["Mira"] = 30;
    ageMap["Bob"] = 25;

    tuple<string, int, bool> person = {"John", 40, true};

    cout << "Name: " << name << endl;
    cout << "First score: " << scores[0] << endl;
    cout << "Bob's age: " << ageMap["Bob"] << endl;
    cout << "Tuple name: " << get<0>(person) << endl;

    return 0;
}