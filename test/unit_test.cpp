#include <cmath>
#include <gtest/gtest.h>
#include "../src/ExplicitEuler.h"
#include "../src/ImplicitEuler.h"
#include "../src/RungeKutta.h"
#include "../src/utilities.h"
#include "../src/Heun.h"
#include "../src/AdamsBashforthTwo.h"

using namespace testing;

/**
 * @brief Test configuration for the ODEs
 */
struct TestConfiguration : public utilities::ODESpecification {
    std::function<double(double)> y;
    std::vector<double> yValues;

    /**
     * @brief Fill the yValues vector with the exact solution of the ODE.
     */
    void fill_yValues() {
        unsigned int nValues = ceil((tEnd - t0) / stepSize) + 1;
        yValues.reserve(nValues);
        yValues.emplace_back(y0);
        for (int n = 1; n < nValues; n++) {
            yValues.emplace_back(y(t0 + stepSize * n));
        }
    }
};
std::vector<TestConfiguration> configurations{};

TEST(ODESolvers, ExplicitEuler) {
    for (auto const &conf: configurations) {
        ExplicitEuler solver = ExplicitEuler(conf.f, conf.y0, conf.t0);
        std::vector<double> yNumerical = solver.solve(conf.stepSize, conf.tEnd);
        double RMSE = utilities::calculateRMSE(yNumerical, conf.yValues);
        std::cout << conf.name << " Expl Euler RMSE: " << RMSE << std::endl;
        utilities::writeSolution(conf.name + "_ExplEuler.dat", conf.t0, conf.stepSize, yNumerical);
        EXPECT_LE(RMSE, 1e-3) << conf.name;
    }
}

TEST(ODESolvers, ImplicitEuler) {
    for (auto const &conf: configurations) {
        ImplicitEuler solver = ImplicitEuler(conf.f, conf.y0, conf.t0, conf.df);
        std::vector<double> yNumerical = solver.solve(conf.stepSize, conf.tEnd);
        double RMSE = utilities::calculateRMSE(yNumerical, conf.yValues);
        std::cout << conf.name << " Impl Euler RMSE: " << RMSE << std::endl;
        utilities::writeSolution(conf.name + "_ImplEuler.dat", conf.t0, conf.stepSize, yNumerical);
        EXPECT_LE(RMSE, 1e-3) << conf.name;
    }
}

TEST(ODESolvers, RungeKutta) {
    for (auto const &conf: configurations) {
        RungeKutta solver = RungeKutta(conf.f, conf.y0, conf.t0);
        std::vector<double> yNumerical = solver.solve(conf.stepSize, conf.tEnd);
        double RMSE = utilities::calculateRMSE(yNumerical, conf.yValues);
        std::cout << conf.name << " RungeKutta RMSE: " << RMSE << std::endl;
        utilities::writeSolution(conf.name + "_RungeKutta.dat", conf.t0, conf.stepSize, yNumerical);
        EXPECT_LE(RMSE, 1e-3) << conf.name;
    }
}

TEST(ODESolvers, Heun) {
    for (auto const &conf: configurations) {
        Heun solver = Heun(conf.f, conf.y0, conf.t0);
        std::vector<double> yNumerical = solver.solve(conf.stepSize, conf.tEnd);
        double RMSE = utilities::calculateRMSE(yNumerical, conf.yValues);
        std::cout << conf.name << " Heun RMSE: " << RMSE << std::endl;
        utilities::writeSolution(conf.name + "Heun.dat", conf.t0, conf.stepSize, yNumerical);
        EXPECT_LE(RMSE, 1e-3) << conf.name;
    }
}

TEST(ODESolvers, AdamsBashforthTwo) {
    for (auto const &conf: configurations) {
        AdamsBashforthTwo solver = AdamsBashforthTwo(conf.f, conf.y0, conf.t0);
        std::vector<double> yNumerical = solver.solve(conf.stepSize, conf.tEnd);
        double RMSE = utilities::calculateRMSE(yNumerical, conf.yValues);
        std::cout << conf.name << " AdamsBashforthTwo RMSE: " << RMSE << std::endl;
        utilities::writeSolution(conf.name + "AdamsBashforthTwo.dat", conf.t0, conf.stepSize, yNumerical);
        EXPECT_LE(RMSE, 1e-3) << conf.name;
    }
}

int main() {
    configurations.emplace_back(TestConfiguration{
            {
                    "linearODE",
                    [](double y, double t) { return -7 * y; },
                    [](double y, double t) { return -7; },
                    1.0,
                    0.0,
                    5.0,
                    1e-4
            },
            [](double t) { return exp(-7 * t); }
    });
    configurations[0].fill_yValues();
    configurations.emplace_back(TestConfiguration{
            {
                    "nonlinearODE",
                    [](double y, double t) { return (y + 1) * sin(t); },
                    [](double y, double t) { return sin(t); },
                    1.0,
                    0.0,
                    5.0,
                    1e-4
            },
            [](double t) { return 2 * exp(1) * exp(-cos(t)) - 1; }
    });
    configurations[1].fill_yValues();
    InitGoogleTest();
    return RUN_ALL_TESTS();
}

