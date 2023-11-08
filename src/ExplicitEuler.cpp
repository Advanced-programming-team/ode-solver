#include "ExplicitEuler.h"

std::vector<double> ExplicitEuler::solve(double stepSize, double tEnd) {
    double t = t0;
    unsigned int N = ceil((tEnd - t0) / stepSize) + 1;
    std::vector<double> y;
    y.reserve(N);
    y.push_back(y0);
    for (int n = 1; n < N; n++) {
        t = t0 + n * stepSize;
        y.emplace_back(y.back() + stepSize * f(y.back(), t));
    }
    return y;
}