#include "AdamsBashforthTwo.h"

std::vector<double> AdamsBashforthTwo::solve(double stepSize, double tEnd) {
    double t = t0;
    unsigned int N = ceil((tEnd - t0) / stepSize) + 1;
    std::vector<double> y;
    y.reserve(N);
    y.push_back(y0);
    y.push_back(y0 + stepSize / 2 * (f(y0 + stepSize * f(y0, t0), t0 + stepSize) + f(y0, t0))); // heun method for first step
    //y.push_back(y0 + stepSize*f(y0,y0)); // euler method for first step
    for (int n = 2; n < N; n++) {
        t = t0 + n * stepSize;
        y.push_back(y.back() + stepSize * (3/2*f(y.back(), t - stepSize) - 1/2*f(y[n - 2], t - 2*stepSize)));
    }
    return y;
}
