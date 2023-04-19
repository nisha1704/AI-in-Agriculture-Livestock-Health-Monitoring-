#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

// Define a struct to store sensor data
struct SensorData {
    float temperature;
    float humidity;
    float activityLevel;
    bool isSick;
};

// Define a class to represent the AI model
class HealthMonitorAI {
private:
    float temperatureThreshold = 39.0; // Celsius
    float humidityThreshold = 70.0; // Percent
    float activityThreshold = 0.2; // Threshold for detecting inactivity
    float minTemperature = 35.0; // Celsius
    float maxTemperature = 40.0; // Celsius
    float minHumidity = 30.0; // Percent
    float maxHumidity = 80.0; // Percent
    float minActivityLevel = 0.0;
    float maxActivityLevel = 1.0;
public:
    // Function to predict whether an animal is sick or healthy based on sensor data
    bool predict(SensorData data) {
        // Check for out-of-range values
        if (data.temperature < minTemperature || data.temperature > maxTemperature ||
            data.humidity < minHumidity || data.humidity > maxHumidity ||
            data.activityLevel < minActivityLevel || data.activityLevel > maxActivityLevel) {
            return true; // Sensor malfunction or abnormal readings
        }
        // Check for potential signs of sickness
        if (data.temperature > temperatureThreshold ||
            data.humidity > humidityThreshold ||
            data.activityLevel < activityThreshold) {
            return true; // Animal is potentially sick
        }
        return false; // Animal is healthy
    }
};

int main() {
    // Read in data from file
    ifstream infile("sensor_data.txt");
    if (!infile) {
        cout << "Error: could not open file" << endl;
        return 1;
    }
    vector<SensorData> data;
    SensorData d;
    while (infile >> d.temperature >> d.humidity >> d.activityLevel >> d.isSick) {
        data.push_back(d);
    }

    // Initialize the AI model
    HealthMonitorAI model;

    // Evaluate the AI model on the data
    int numCorrectPredictions = 0;
    for (int i = 0; i < data.size(); i++) {
        bool prediction = model.predict(data[i]);
        if (prediction == data[i].isSick) {
            numCorrectPredictions++;
        }
    }

    // Calculate accuracy
    float accuracy = (float) numCorrectPredictions / data.size();
    cout << "Accuracy: " << accuracy << endl;

    // Store sensor data in a file
    ofstream outfile("sensor_data_output.txt");
    if (!outfile) {
        cout << "Error: could not open file" << endl;
        return 1;
    }
    for (int i = 0; i < data.size(); i++) {
        outfile << data[i].temperature << " " << data[i].humidity << " " << data[i].activityLevel << " " << data[i].isSick << endl;
    }

    return 0;
}
