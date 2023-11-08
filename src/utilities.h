#pragma once

#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <cmath>
#include <array>
#include <memory>


/**
 * @brief Some useful tools for solving ODEs.
 *
 */
namespace utilities {

    /**
     * @brief Specification of an ODE
     *
     * @param name              Name of the ODEe
     * @param f                 Such that y' = f(y, t)
     * @param df                Such that df(y, t)/ dy = df(y, t)
     * @param y0                Initial value of y
     * @param t0                Initial value of t
     * @param tEnd              Time to solve the ODE to
     * @param stepSize          Step size
    */
    struct ODESpecification {
        std::string name;
        std::function<double(double, double)> f;
        std::function<double(double, double)> df;
        double y0;
        double t0;
        double tEnd;
        double stepSize;
    };

    /**
    * @brief Writes the solution to a csv.
    *
    * @param filename   Name of the file to write to
    * @param t0         Initial value of t
    * @param stepSize   Step size
    * @param y          Solution vector
    */
    void writeSolution(const std::string& filename, double t0, double stepSize, const std::vector<double>& y);

    /**
    * @brief Calculates the Root Mean Squared Error between the solution and the analytical solution.
    *
    * @param yNumerical  Approximated solution obtained by a numerical method
    * @param yAnalytical Exact, analytical solution
    */
    double calculateRMSE(const std::vector<double> &yNumerical, const std::vector<double> &yAnalytical);
}


