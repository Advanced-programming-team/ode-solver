#pragma once

#include <utility>
#include <vector>
#include <functional>

/**
 * @brief Abstract interface for solving ODEs.
 *
 */
class ODESolver {

protected:
    std::function<double(double y, double t)> f;
    double y0;
    double t0;

protected:
    /**
     * @brief Construct an object derived from ODESolver.
     *
     * @param  f  Such that y' = f(y, t)
     * @param y0  Initial value of y
     * @param t0  Initial value of t
     */
    ODESolver(std::function<double(double y, double t)> f, double y0, double t0) : f(std::move(f)), y0(y0), t0(t0) {}

public:
    /**
     * @brief Solves the ODE.
     * @param stepSize The step size.
     * @param tEnd The time to solve the ODE to.
     * @return A vector of the solution at each step.
     */
    virtual std::vector<double> solve(double stepSize, double tEnd) = 0;
    virtual ~ODESolver() {} ;
};


