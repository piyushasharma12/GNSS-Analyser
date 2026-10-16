Author
Piyusha Sharma
BTECH ECE

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const double EARTH_RADIUS = 6371000.0;
const double PI = 3.14159265358979323846;

struct Position {
    string timestamp;
    double estimatedLat;
    double estimatedLon;
    double referenceLat;
    double referenceLon;
    double errorMeters;
};

double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

double calculateDistance(
    double lat1, double lon1,
    double lat2, double lon2
) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);

    double a =
        sin(dLat / 2) * sin(dLat / 2) +
        cos(toRadians(lat1)) *
        cos(toRadians(lat2)) *
        sin(dLon / 2) * sin(dLon / 2);

    // Protect against floating-point rounding errors.
    a = max(0.0, min(1.0, a));

    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    return EARTH_RADIUS * c;
}

int main() {
    ifstream file("sample_positions.csv");

    if (!file.is_open()) {
        cout << "Error: Cannot open sample_positions.csv\n";
        cout << "Create the CSV file in the project folder.\n";
        return 1;
    }

    vector<Position> positions;
    string line;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string timestamp, values[4];

        if (!getline(ss, timestamp, ','))
            continue;

        bool validRow = true;

        for (int i = 0; i < 4; i++) {
            if (!getline(ss, values[i], ',')) {
                validRow = false;
                break;
            }
        }

        if (!validRow)
            continue;

        try {
            Position p;
            p.timestamp = timestamp;
            p.estimatedLat = stod(values[0]);
            p.estimatedLon = stod(values[1]);
            p.referenceLat = stod(values[2]);
            p.referenceLon = stod(values[3]);

            if (abs(p.estimatedLat) > 90 ||
                abs(p.referenceLat) > 90 ||
                abs(p.estimatedLon) > 180 ||
                abs(p.referenceLon) > 180) {
                cout << "Skipping invalid coordinates: "
                     << timestamp << "\n";
                continue;
            }

            p.errorMeters = calculateDistance(
                p.estimatedLat, p.estimatedLon,
                p.referenceLat, p.referenceLon
            );

            positions.push_back(p);
        }
        catch (...) {
            cout << "Skipping invalid row: " << line << "\n";
        }
    }

    file.close();

    if (positions.empty()) {
        cout << "No valid position records found.\n";
        return 1;
    }

    ofstream report("position_analysis_report.csv");

    if (!report.is_open()) {
        cout << "Error: Cannot create position report.\n";
        return 1;
    }

    report << "Timestamp,Estimated Latitude,Estimated Longitude,"
           << "Reference Latitude,Reference Longitude,"
           << "Horizontal Error (m)\n";

    cout << fixed << setprecision(3);

    double totalError = 0.0;
    double minimumError = positions[0].errorMeters;
    double maximumError = positions[0].errorMeters;

    cout << "\n========================================\n";
    cout << " GNSS POSITIONING ACCURACY ANALYSIS\n";
    cout << "========================================\n";

    cout << "\nPosition Error for Each Observation:\n";
    cout << "----------------------------------------\n";

    for (const auto& p : positions) {
        cout << "Timestamp: " << p.timestamp << "\n";
        cout << "Horizontal error: "
             << p.errorMeters << " metres\n";
        cout << "----------------------------------------\n";

        report << p.timestamp << ","
               << p.estimatedLat << ","
               << p.estimatedLon << ","
               << p.referenceLat << ","
               << p.referenceLon << ","
               << p.errorMeters << "\n";

        totalError += p.errorMeters;
        minimumError = min(minimumError, p.errorMeters);
        maximumError = max(maximumError, p.errorMeters);
    }

    double meanError = totalError / positions.size();

    cout << "\nPositioning Error Summary:\n";
    cout << "----------------------------------------\n";
    cout << "Number of positions: " << positions.size() << "\n";
    cout << "Mean horizontal error: " << meanError << " m\n";
    cout << "Minimum horizontal error: " << minimumError << " m\n";
    cout << "Maximum horizontal error: " << maximumError << " m\n";

    report.close();

    cout << "\nReport saved to position_analysis_report.csv\n";
    cout << "Positioning analysis completed successfully.\n";

    return 0;
}
