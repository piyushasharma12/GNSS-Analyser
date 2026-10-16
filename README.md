# GNSS Analyser 🛰️

A GNSS positioning accuracy and satellite signal analysis project developed to explore satellite navigation, positioning errors, and signal-quality visualization.

## 📌 Overview

The GNSS Analyser combines C++-based GNSS observation analysis with a web-based dashboard to process data, calculate positioning error metrics, and visualize results.

## ✨ Features

- **GNSS Data Processing:** Read and analyse satellite observations from CSV files using C++.
- **Signal Quality Analysis:** Classify satellite signals using C/N₀ measurements.
- **Positioning Accuracy:** Compare estimated coordinates with reference coordinates.
- **Error Metrics:** Calculate horizontal error, RMSE, median error, P95, and maximum error.
- **Interactive Visualizations:** Explore positioning errors and signal measurements through charts.
- **Geographic Mapping:** Display estimated and reference positions on an interactive map.
- **Report Generation:** Export analysis results and summary reports.

## 🛠️ Technologies Used

- C++
- HTML5
- CSS3
- JavaScript
- Chart.js
- Leaflet
- CSV data processing

## 📂 Project Structure

```text
gnss-analyser/
├── main.cpp
├── sample_gnss.csv
├── dashboard/
│   └── index.html
├── README.md
├── LICENSE
└── .gitignore
```

*The structure above is an example; adjust it to match the files in your repository.*

## 🚀 Getting Started

### C++ Analysis

1. Clone or download this repository.
2. Open the project folder in Visual Studio Code.
3. Compile `main.cpp` using a C++ compiler such as g++.
4. Run the generated executable with the required CSV file in the expected location.

Example commands:

```bash
g++ main.cpp -o gnss_analyzer
./gnss_analyzer
```

On Windows, run the generated executable using:

```powershell
.\gnss_analyzer.exe
```

### Web Dashboard

1. Open the `dashboard` folder.
2. Run `index.html` using VS Code Live Server or a local web server.
3. Upload the required CSV datasets to explore the available analysis features.

The dashboard uses browser-based visualization libraries and may require an internet connection for external libraries and map tiles.

## 📊 Analysis Metrics

- Mean horizontal positioning error
- Root Mean Square Error (RMSE)
- Median error
- 95th-percentile error (P95)
- Maximum positioning error
- Satellite C/N₀ signal measurements

## 📌 Data and Limitations

The accuracy of the results depends on the input dataset and the reliability of the reference coordinates. Demonstration data is intended for testing and visualization and should not be interpreted as real-world GNSS accuracy validation.

## 🎯 Learning Objectives

- Understand GNSS positioning fundamentals.
- Explore satellite signal-quality measurements.
- Learn how positioning errors are evaluated statistically.
- Apply C++ programming and web technologies to an engineering analysis tool.

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

Author
Piyusha Sharma
BTECH ECE
