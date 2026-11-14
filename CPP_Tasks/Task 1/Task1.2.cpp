#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <cmath> // round off

using namespace std;

int main() {
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    map<string, double> temperatures = {      //map stores key-value pairs, can combine day and temperature in one container
        {"Monday", 14.5},
        {"Tuesday", 18.3},
        {"Wednesday", 27.8},
        {"Thursday", 30.5},
        {"Friday", 10.5},
        {"Saturday", 5.1},
        {"Sunday", 7.8}
    };

    map<string, char> weatherconditions = {          //S- Sunny R- Rainy C- Cloudy
        {"Monday", 'S'},
        {"Tuesday", 'C'},
        {"Wednesday", 'S'},
        {"Thursday", 'S'},
        {"Friday", 'R'},
        {"Saturday", 'R'},
        {"Sunday", 'C'}
    };

    tuple<string, double> highestDay = make_tuple(days[0], temperatures[days[0]]);
    double sum = 0.0;

    cout << "\nTemperature and weather condition of the Week:\n\n";

    for (const auto &day : days) {
        double temp = temperatures[day];
        char cond = weatherconditions[day];

        cout << day << ": " << temp << "C - ";

        if (temp < 10)
            cout << "Cold";
        else if (temp <= 20)
            cout << "Ok";
        else
            cout << "Warm";

        cout << " > Weather Condition: " << cond << endl;

        if (temp > get<1>(highestDay))
            highestDay = make_tuple(day, temp);      //highestDay tuple holds 2 different types

        sum += temp;
    }

    double average = sum / days.size();         //size - number of elements 7

    
    double roundedAvg = round(average * 100) / 100;    // round off to 2 decimal places

    cout << "\nThe Highest Temperature Recorded on " << get<0>(highestDay)
         << " as " << get<1>(highestDay) << "C" << endl;

    cout << "\nAverage Temperature of the Week: " << roundedAvg << "C" << endl;

    return 0;
}
