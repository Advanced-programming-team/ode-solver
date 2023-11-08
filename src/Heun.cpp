#include "Heun.h"

std::vector<double> Heun::solve(double stepSize, double tEnd) {
    double t = t0;
    unsigned int N = ceil((tEnd - t0) / stepSize) + 1;
    std::vector<double> y;
    y.reserve(N);
    y.push_back(y0);
    for (int n = 1; n < N; n++) {
        t = t0 + n * stepSize;
        y.push_back(y.back() + stepSize / 2 * (f(y.back() + stepSize * f(y.back(), t), t + stepSize) + f(y.back(), t)));
    }
    return y;
}