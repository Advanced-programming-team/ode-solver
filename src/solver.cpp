#include <nlohmann/json.hpp>
#include <muParser.h>
#include <memory>
#include <iostream>
#include "ODESolver.h"
#include "utilities.h"
#include "ExplicitEuler.h"
#include "ImplicitEuler.h"
#include "RungeKutta.h"
#include "Heun.h"
#include "AdamsBashforthTwo.h"

using namespace nlohmann;

/**
 * @brief Solver configuration and ODE specification.
 */
struct SolverConfiguration : public utilities::ODESpecification {
    std::unique_ptr<ODESolver> solver;
};

/**
     * @brief Creates the default solver configuration as config.json, with the following structure:
     *
     *
     * @key name              Name of the ODEe
     * @key solver            Name of the solver
     * @key function_provider Mode of function provision (Default|Custom)
     * @key f                 function_provider = Default:    Number specifying which given ODE to solve
     *                        function_provider = Custom: Command to execute (command line argument should be 2 doubles y and t)
     * @key df                function_provider = Default:    irrelevant
     *                        function_provider = Custom: Command to execute (command line argument should be 2 doubles y and t)
     * @key y0                Initial value of y
     * @key t0                Initial value of t
     * @key tEnd              Time to solve the ODE to
     * @key stepSize          Step size
*/
void createDefaultConfig(const std::string &filename) {
    ordered_json config;
    config["name"] = "default";
    config["solver"] = "ExplicitEuler";
    config["function_provider"] = "Default";
    config["f"] = 1;
    config["df"] = {};
    config["y0"] = 1;
    config["t0"] = 0;
    config["tEnd"] = 1;
    config["stepSize"] = 0.1;
    std::ofstream file;
    file.open(filename);
    file << config.dump(4) << std::endl;
    file.close();
}

/**
 * @brief Parses the config.json file to create c++ functions for f and df.
 * @param config    The json object containing the configuration.
 * @return A pair of functions f and df.
*/
std::pair<std::function<double(double, double)>, std::function<double(double, double)>> parseFunction(json &config) {
    std::function<double(double, double)> f;
    std::function<double(double, double)> df;
    if (config.at("function_provider") == "Default") {
        switch (config["f"].get<int>()) {
            case 1:
                f = [](double y, double t) { return y; };
                df = [](double y, double t) { return 1; };
                break;
            case 2:
                f = [](double y, double t) { return (y + 1) * sin(t); };
                df = [](double y, double t) { return sin(t); };
                break;
            default:
                throw std::invalid_argument("Invalid function number");
        }
    } else if (config.at("function_provider") == "Custom") {
        mu::Parser parserF;
        parserF.SetExpr(config.at("f"));

        mu::Parser parserDF;
        parserDF.SetExpr(config.at("df"));

        f = [parserF](double y, double t) mutable -> double {
            parserF.DefineVar("t", &t);
            parserF.DefineVar("y", &y);
            return parserF.Eval();
        };
        df = [parserDF](double y, double t)  mutable -> double {
            parserDF.DefineVar("t", &t);
            parserDF.DefineVar("y", &y);
            return parserDF.Eval();
        };
    } else {
        throw std::invalid_argument("Invalid function_provider");
    }
    return std::make_pair(f, df);
}

/**
 * @brief Parses the config.json file to create a solver.
 * @param config    The json object containing the configuration.
 * @return A pointer to the solver object.
*/
std::unique_ptr<ODESolver>
parseSolver(json &config, std::function<double(double, double)> f, std::function<double(double, double)> df) {
    std::string solverName = config["solver"];
    if (solverName == "ExplicitEuler") {
        std::unique_ptr<ODESolver> solver = make_unique<ExplicitEuler>(f, config["y0"], config["t0"]);
        return solver;
    } else if (solverName == "RungeKutta") {
        std::unique_ptr<ODESolver> solver = make_unique<RungeKutta>(f, config["y0"], config["t0"]);
        return solver;
    } else if (solverName == "ImplicitEuler") {
        return make_unique<ImplicitEuler>(f, config["y0"], config["t0"], df);
    } else if (solverName == "Heun") {
        return make_unique<Heun>(f, config["y0"], config["t0"]);
    } else if (solverName == "AdamsBashforthTwo") {
        return make_unique<AdamsBashforthTwo>(f, config["y0"], config["t0"]);
    } else {
        throw std::invalid_argument("Invalid solver name");
    }
}

/**
 * @brief Parses the config.json file to create a solver configuration.
 * @param config    The json object containing the configuration.
 * @return The solver configuration.
*/
SolverConfiguration parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.fail()) {
        throw std::runtime_error("Could not open file");
    }
    json rawJSON;
    file >> rawJSON;

    auto [f, df] = parseFunction(rawJSON);

    SolverConfiguration config = {
            {
                    rawJSON["name"],
                    f,
                    df,
                    rawJSON["y0"],
                    rawJSON["t0"],
                    rawJSON["tEnd"],
                    rawJSON["stepSize"]
            },
            parseSolver(rawJSON, f, df)
    };
    return config;
}

int main(int argc, char **argv) {
    std::string configFile = "config.json";
    if (argc != 2) {
        std::cout << "No path to configuration file given. Generating default configuration: ./config.json"
                  << std::endl;
        createDefaultConfig(configFile);
    } else {
        configFile = argv[1];
    }

    SolverConfiguration config;
    try {
        config = parseFile(configFile);
    } catch (mu::Parser::exception_type &e) {
        std::cout << "[FUNCTION_PARSING_ERROR]" << e.GetMsg() << std::endl;
    }
    catch (json::parse_error &e) {
        std::cout << "[PARSE_ERROR]" << e.what() << std::endl;
        return 1;
    } catch (std::runtime_error &e) {
        std::cout << "[RUNTIME_ERROR]" << e.what() << std::endl;
        return 1;
    } catch (std::invalid_argument &e) {
        std::cout << "[INVALID_ARGUMENT]" << e.what() << std::endl;
        return 1;
    }

    utilities::writeSolution("results_" + config.name, config.t0, config.stepSize, config.solver->solve(config.stepSize, config.tEnd));
}