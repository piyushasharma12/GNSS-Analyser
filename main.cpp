Author
Piyusha Sharma
BTECH ECE


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

struct GNSSObservation {
    string timestamp;
    int satelliteID;
    double signalStrength;
};

string classifySignal(double cn0) {
    if (cn0 >= 40.0)
        return "Strong";
    else if (cn0 >= 30.0)
        return "Moderate";
    else
        return "Weak";
}

int main() {
    string filename = "sample_gnss.csv";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return 1;
    }

    vector<GNSSObservation> observations;
    string line;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string timestamp, satelliteText, signalText;

        if (!getline(ss, timestamp, ',') ||
            !getline(ss, satelliteText, ',') ||
            !getline(ss, signalText, ','))
            continue;

        try {
            GNSSObservation obs;
            obs.timestamp = timestamp;
            obs.satelliteID = stoi(satelliteText);
            obs.signalStrength = stod(signalText);
            observations.push_back(obs);
        }
        catch (...) {
            cout << "Skipping invalid CSV row: " << line << endl;
        }
    }

    file.close();

    if (observations.empty()) {
        cout << "No valid GNSS observations found." << endl;
        return 1;
    }

    ofstream report("gnss_analysis_report.csv");

    if (!report.is_open()) {
        cout << "Error: Could not create analysis report." << endl;
        return 1;
    }

    report << "Timestamp,Satellite ID,C/N0 (dB-Hz),Signal Quality\n";
    report << fixed << setprecision(2);

    double totalSignal = 0.0;
    double strongestSignal = observations[0].signalStrength;

    int strongCount = 0;
    int moderateCount = 0;
    int weakCount = 0;

    map<int, double> satelliteTotals;
    map<int, int> satelliteCounts;
    map<int, GNSSObservation> previousObservation;

    cout << fixed << setprecision(2);

    cout << "\n========================================\n";
    cout << " GNSS DATA ANALYSIS TOOL\n";
    cout << "========================================\n";

    cout << "\nTotal observations: "
         << observations.size() << endl;

    cout << "\nIndividual Observation Analysis:\n";
    cout << "----------------------------------------\n";

    for (const auto& obs : observations) {
        string quality = classifySignal(obs.signalStrength);

        cout << "Timestamp: " << obs.timestamp
             << " | Satellite ID: " << obs.satelliteID
             << " | C/N0: " << obs.signalStrength
             << " dB-Hz | Quality: " << quality << endl;

        report << obs.timestamp << ","
               << obs.satelliteID << ","
               << obs.signalStrength << ","
               << quality << "\n";

        totalSignal += obs.signalStrength;
        satelliteTotals[obs.satelliteID] += obs.signalStrength;
        satelliteCounts[obs.satelliteID]++;

        if (obs.signalStrength > strongestSignal)
            strongestSignal = obs.signalStrength;

        if (quality == "Strong")
            strongCount++;
        else if (quality == "Moderate")
            moderateCount++;
        else
            weakCount++;
    }

    double averageSignal = totalSignal / observations.size();

    cout << "\nOverall Signal Statistics:\n";
    cout << "----------------------------------------\n";
    cout << "Average C/N0: " << averageSignal << " dB-Hz\n";
    cout << "Strongest C/N0: " << strongestSignal << " dB-Hz\n";

    cout << "\nAverage Signal Strength Per Satellite:\n";
    cout << "----------------------------------------\n";

    for (const auto& entry : satelliteTotals) {
        int id = entry.first;
        double average = entry.second / satelliteCounts[id];

        cout << "Satellite " << id << ": "
             << average << " dB-Hz\n";
    }

    cout << "\nSignal Quality Summary:\n";
    cout << "----------------------------------------\n";
    cout << "Strong observations: " << strongCount << endl;
    cout << "Moderate observations: " << moderateCount << endl;
    cout << "Weak observations: " << weakCount << endl;

    cout << "\nStrongest Observation:\n";
    cout << "----------------------------------------\n";

    for (const auto& obs : observations) {
        if (obs.signalStrength == strongestSignal) {
            cout << "Satellite ID: " << obs.satelliteID << endl;
            cout << "Timestamp: " << obs.timestamp << endl;
            cout << "Signal strength: "
                 << obs.signalStrength << " dB-Hz\n";
            break;
        }
    }

    cout << "\nSignal Change Analysis:\n";
    cout << "----------------------------------------\n";

    bool foundComparison = false;

    for (const auto& obs : observations) {
        int id = obs.satelliteID;

        auto it = previousObservation.find(id);

        if (it != previousObservation.end()) {
            double change =
                obs.signalStrength - it->second.signalStrength;

            cout << "Satellite ID: " << id << endl;
            cout << "Previous C/N0: "
                 << it->second.signalStrength << " dB-Hz\n";
            cout << "Current C/N0: "
                 << obs.signalStrength << " dB-Hz\n";
            cout << "Signal change: "
                 << (change > 0 ? "+" : "")
                 << change << " dB-Hz\n";

            if (change > 0)
                cout << "Status: Signal improved\n";
            else if (change < 0)
                cout << "Status: Signal decreased\n";
            else
                cout << "Status: No signal change\n";

            cout << "----------------------------------------\n";
            foundComparison = true;
        }

        previousObservation[id] = obs;
    }

    if (!foundComparison)
        cout << "No repeated satellite observations available.\n";

    report.close();

    cout << "\nAnalysis report saved to "
         << "gnss_analysis_report.csv\n";

    cout << "Analysis completed successfully.\n";

    return 0;
}


