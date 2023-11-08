# pragma once

#include "ODESolver.h"
#include <cmath>

/**
 * @brief Class for solving ODEs using the second order Heun Method.
 */

class Heun : public ODESolver {

public:
    /**
     * @brief Construct a Heun object
     *
     * @param f Such that y' = f(y, t)
     * @param y0 Initial value of y
     * @param t0 Initial value of t
     */
    Heun(std::function<double(double y, double t)> f, double y0, double t0) : ODESolver(std::move(f), y0, t0) {}

    /**
     * @brief Solves the ODE using the second order Heun method.
     * @param stepSize The step size.
     * @param tEnd The time to solve the ODE to.
     * @return A vector of the solution at each step.
     */
    std::vector<double> solve(double stepSize, double tEnd) override;

};



