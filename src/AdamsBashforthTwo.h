#pragma once

#include "ODESolver.h"
#include <cmath>

/**
 * @brief Class for solving ODEs with the Adams-Bashforth method with s=2.
 */

class AdamsBashforthTwo : public ODESolver {

    /**
     * @brief Construct an AdamsBashforthTwo object
     *
     * @param f Such that y' = f(y, t)
     * @param y0 Initial value of y
     * @param t0 Initial value of t
     */
public:
    AdamsBashforthTwo(std::function<double(double y, double t)> f, double y0, double t0) : ODESolver(std::move(f), y0,
                                                                                                     t0) {}

    /** @Brief Solves the ODE using the Adams-Bashforth method with s=2.
     *  @param stepSize The step size.
     *  @apram tEnd The time to solve the ODE to.
     *  @return A vector of the solution at each step.
     */

    std::vector<double> solve(double stepSize, double tEnd) override;

};



