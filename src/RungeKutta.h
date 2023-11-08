#pragma once

#include <cmath>
#include <utility>
#include <vector>
#include <functional>
#include "ODESolver.h"

/**
 * @brief Class for solving ODEs using the Runge-Kutta method.
 *
 */
class RungeKutta : public ODESolver {

public:
    /**
     * @brief Construct a RungeKutta object
     *
     * @param  f  Such that y' = f(y, t)
     * @param y0  Initial value of y
     * @param t0  Initial value of t
     */
RungeKutta(std::function<double(double y, double t)> f, double y0, double t0) : ODESolver(std::move(f), y0, t0) {}

    /**
     * @brief Solves the ODE using the Runge-Kutta method.
     * @param stepSize The step size.
     * @param tEnd The time to solve the ODE to.
     * @return A vector of the solution at each step.
     */
    std::vector<double> solve(double stepSize, double tEnd) override;
};




