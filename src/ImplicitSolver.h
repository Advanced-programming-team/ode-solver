#pragma once

#include <utility>

#include "ODESolver.h"

/**
 * @brief Abstract interface for solving ODEs using implicit methods.
 *
 */
class ImplicitSolver : public ODESolver {

protected:
    std::function<double(double y, double t)> df;
    const double tol = 1e-8;
    const unsigned int maxIter = 1000;

protected:
    /**
     * @brief Construct an object derived from ImplicitSolver.
     *
     * @param  f   Such that y' = f(y, t)
     * @param  df  Such that df(y, t)/ dy = df(y, t)
     * @param  y0  Initial value of y
     * @param  t0  Initial value of t
     */
    ImplicitSolver(std::function<double(double y, double t)> f, double y0, double t0,
                   std::function<double(double y, double t)> df) : ODESolver(std::move(f), y0, t0), df(std::move(df)) {}

    /**
    * @brief Newton-Raphson method for solving nonlinear equations
    * @param x0 Initial guess
    * @param g Function to solve
    * @param dg Derivative of function to solve
    * @const tol The allowable error of the zero value
    * @const maxIter Maximum number of iterations
    * @return A pair containing the solution and a boolean indicating if the method converged
    */
    std::pair<double, bool>
    NewtonRaphson(double x0, const std::function<double(double)>& g, const std::function<double(double)>& dg) const {
        double x_old = x0;
        double x_new = x0;
        unsigned int N = 0;
        for (; std::abs(g(x_new)) > tol && N < maxIter; N++) {
            x_old = x_new;
            x_new = x_old - g(x_old) / dg(x_old);
        }
        return {x_new, N != maxIter};
    }
};