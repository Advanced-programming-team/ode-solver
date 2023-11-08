#pragma once

#include "ImplicitSolver.h"
#include <utility>
#include <vector>
#include <functional>
#include <iostream>
#include <cmath>

/**
 * @brief Class for solving ODEs using the Implicit Euler method.
 *
 */
class ImplicitEuler : public ImplicitSolver {
public:
    /**
     * @brief Construct an ImplicitEuler object
     *
     * @param  f  Such that y' = f(y, t)
     * @param y0  Initial value of y
     * @param t0  Initial value of t
     */
    ImplicitEuler(std::function<double(double y, double t)> f, double y0, double t0,
                  std::function<double(double y, double t)> df) : ImplicitSolver(std::move(f), y0, t0, std::move(df)) {}

    /**
     * @brief Solves the ODE using the Implicit Euler method.
     * @param h The step size.
     * @param t The time to solve the ODE to.
     * @return A vector of the solution at each step.
     */
    std::vector<double> solve(double stepSize, double tEnd) override;
};

