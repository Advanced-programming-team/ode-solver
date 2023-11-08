#include "utilities.h"
namespace utilities {
    void writeSolution(const std::string& filename, double t0, double stepSize, const std::vector<double>& y) {
        std::ofstream file;
        file.open(filename + ".csv");
        file << "t,y" << "\n";
        double t = t0;
        for (double y_i: y) {
            file << t << "," << y_i << "\n";
            t = t + stepSize;
        }
        file.close();
    }

    double calculateRMSE(const std::vector<double> &yNumerical, const std::vector<double> &yAnalytical) {
        double SumSquaredDifferences = 0.0;
        for (auto i = 0; i < yNumerical.size(); i++) {
            double difference = yNumerical[i] - yAnalytical[i];
            SumSquaredDifferences += difference * difference;
        }
        return sqrt(SumSquaredDifferences / yNumerical.size());
    }
}
