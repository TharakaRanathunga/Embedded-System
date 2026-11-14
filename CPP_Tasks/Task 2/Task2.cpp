#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;


float roundTo2(float value) {                                //round to 2 decimals manually
    return static_cast<int>(value * 100 + 0.5f) / 100.0f;
}


template <typename T>                           // Template for average calculation
T calculateAverage(T* data, int size) {
    if (size == 0) {
        throw runtime_error("Division by zero: no readings available.");
    }
    T sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum / size;
}

class WeatherStation {
private:
    string location;
    float* readings;
    int capacity;
    int count;

    void resize() {
        int newCapacity = capacity * 2;
        float* newArray = new float[newCapacity];
        for (int i = 0; i < count; i++) {
            newArray[i] = readings[i];
        }
        delete[] readings;
        readings = newArray;
        capacity = newCapacity;
    }

public:
    WeatherStation(string loc, int initialCapacity = 5)
        : location(loc), capacity(initialCapacity), count(0) {
        readings = new float[capacity];
    }

    WeatherStation(const WeatherStation& other) {
        location = other.location;
        capacity = other.capacity;
        count = other.count;
        readings = new float[capacity];
        for (int i = 0; i < count; i++) {
            readings[i] = other.readings[i];
        }
    }

    ~WeatherStation() {
        delete[] readings;
    }

    void addReading(float value) {
        if (count >= capacity) {
            resize();
        }
        readings[count++] = value;
    }

    void printReadings() const {
        cout << "Location: " << location << endl;
        cout << "Readings: ";
        for (int i = 0; i < count; i++) {
            cout << roundTo2(readings[i]) << " ";
        }
        cout << endl;
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            throw runtime_error("Error opening file for writing: " + filename);
        }
        outFile << location << endl;
        for (int i = 0; i < count; i++) {
            outFile << roundTo2(readings[i]) << " ";
        }
        outFile << endl;
        outFile.close();
        cout << "Saved to file: " << filename << endl;
    }

    float getAverage() const {
        return calculateAverage(readings, count);
    }

    int countAbove(float threshold) const {
        return count_if(readings, readings + count, [threshold](float val) {
            return val > threshold;
        });
    }

    void sortReadings() {
        sort(readings, readings + count);
    }

    static WeatherStation loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            throw runtime_error("Error opening file for reading: " + filename);
        }

        string loc;
        getline(inFile, loc);

        WeatherStation ws(loc);
        float value;
        while (inFile >> value) {
            ws.addReading(value);
        }
        inFile.close();
        return ws;
    }
};


int main() {
    try {
        string location;
        cout << "Enter location: ";
        getline(cin, location);

        WeatherStation station(location);

        cout << "Enter temperature readings (type -0 to stop):" << endl;
        while (true) {
            float val;
            cin >> val;
            if (val == -0) break;
            station.addReading(val);
        }

        station.sortReadings();

        station.printReadings();

        
        float avg = roundTo2(station.getAverage());       // Average calculation with manual rounding
        cout << "Average: " << avg << endl;

        
        float threshold;                         // Threshold input
        cout << "Enter threshold to count readings above: ";
        cin >> threshold;
        int above = station.countAbove(threshold);
        cout << "Readings above " << roundTo2(threshold) << "C: " << above << endl;

        
        string filename = location + "_readings.txt";       // Save to file (rounded values)
        station.saveToFile(filename);

        
        WeatherStation loaded = WeatherStation::loadFromFile(filename);       // Load back
        cout << "\n--- Reconstructed from file ---" << endl;
        loaded.printReadings();
        float avg2 = roundTo2(loaded.getAverage());
        cout << "Average: " << avg2 << endl;
        int above2 = loaded.countAbove(threshold);
        cout << "Readings above " << roundTo2(threshold) << "C: " << above2 << endl;

    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
