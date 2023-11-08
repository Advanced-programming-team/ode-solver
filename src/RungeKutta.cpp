#include "RungeKutta.h"

std::vector<double> RungeKutta::solve(double stepSize, double tEnd) {
    double t = t0;
    unsigned int N = ceil((tEnd - t0) / stepSize) + 1;
    std::vector<double> y;
    y.reserve(N);
    y.push_back(y0);
    for (int n = 1; n < N; n++) {
        double k1 = f(y.back(), t);
        double k2 = f(y.back() + stepSize * k1 / 2, t + stepSize / 2);
        double k3 = f(y.back() + stepSize * k2 / 2, t + stepSize / 2);
        double k4 = f(y.back() + stepSize * k3, t + stepSize);
        y.emplace_back(y.back() + stepSize * (k1 + 2 * k2 + 2 * k3 + k4) / 6);
        t = t0 + n * stepSize;
    }
    return y;
}