#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

int main() {
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; //Days of the week
    
    vector<double> temperatures = {14.5, 18.3, 27.8, 30.5, 10.5, 5.1, 7.8}; //Temperature data

    tuple<string, double> highestDay = make_tuple(days[0], temperatures[0]);

    cout << "\nTemperature of the Week:\n\n";
    
    for (size_t i = 0; i < days.size(); i++) {  //Prints each day, temp and category
        cout << days[i] << ": " << temperatures[i] << "C - ";


        if (temperatures[i] < 10)
            cout << "Cold";
        else if (temperatures[i] <= 20)
            cout << "Ok";
        else
            cout << "Warm";

        cout << endl;

        if (temperatures[i] > get<1>(highestDay)) {
            highestDay = make_tuple(days[i], temperatures[i]);
        }
    }

    cout << "\nThe Highest Temperature Recorded on the day " << get<0>(highestDay)
         << " as " << get<1>(highestDay) << "C" << endl;

    return 0;

}
