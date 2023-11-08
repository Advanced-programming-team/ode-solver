#include "ImplicitEuler.h"

std::vector<double> ImplicitEuler::solve(double stepSize, double tEnd) {
    double t = t0;
    unsigned int N = ceil((tEnd - t0) / stepSize) + 1;
    std::vector<double> y;
    y.reserve(N);
    y.push_back(y0);
    auto g = [&y, &t, stepSize, this](double x) {
        return stepSize * f(x, t + stepSize) + y.back() - x;
    };
    auto dg = [&t, stepSize, this](double x) {
        return stepSize * df(x, t + stepSize) - 1;
    };
    for (int n = 1; n < N; n++) {
        auto [y_new, converged] = NewtonRaphson(y.back(), g, dg);
        if (converged) {
            y.push_back(y_new);
            t = t0 + n * stepSize;
        } else {
            std::cout << "Newton-Raphson method did not converge" << std::endl;
            break;
        }

    }
    return y;
}

