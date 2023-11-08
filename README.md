# ODE-Solver
This is a simple ODE solver written in C++. 

## Installation
To use the solver simply clone the repository and build the solver executable with cmake using the provided 
CMakeLists.txt file.

## Dependencies
This project uses the MuParser library for parsing the ODE configurations https://github.com/beltoforion/muparser.

## Usage
First, we recommend running the following solver executable without command line arguments.
So simply call:
`./solver`
This will run the default case and generate 2 files: *config.json* and *results_default.csv*.

The *config.json* file contains the configuration file of the solver and its path can be given as command line argument.
You can modify this to adapt the problem to your needs. Its fields are:

    | Field                | Description                   | Values                                       |
    |----------------------|-------------------------------|----------------------------------------------|
    | name                 | Name of the problem           | string                                       |
    | solver               | Name of the solver            | "ExplicitEuler"/"ImplicitEuler"/"RungeKutta" |
    | function_provider    | Mode of function provision    | "Default"/"Custom"                       |
    | f                    | (function_provider=Default):  | 1(y'=y) / 2(y'=(y + 1) * sin(t))             |
    |                      | Number specifying which given |                                              |                 
    |                      | ODE to solve                  |                                              |
    |                      | (function_provider=Custom):   |                                              |
    |                      | Provides a string to be parsed|                                              |
    |                      | by muparser describing the ODE|                                              |
    | df                   | Same as f for the derivative  |                                              |
    | y0                   | Initial value of y            | double                                       |
    | t0                   | Initial value of t            | double                                       |
    | t_end                | End value of t                | double                                       |
    | stepSize             | Step size                     | double                                       |

The *default_results.csv* file contains the results of the solver.

Once you adapted the configuration file to your needs, you can run the solver with the following command:

`./solver <path_to_config_file>`

### User defined ODE 
There is also the capability to define your own ODE *y' = f(y,t)*.
To do so, you have to set the *function_provider* field to *Custom*.
Then, you have to provide the function and its derivative as strings in infix
notation. In the examples directory, you can find an example configuration file.

## Extending the solver
The solver is designed to be easily extensible. To add a new solver, you have to create a new class that inherits either from the abstract class *ImplicitSolver* or from the abstract class *ODESolver*, depending on the type of solver you want to implement. In case you want to implement an implicit method, your class should inherit from the *ImplicitSolver*, while if you want to implement an explicit method, your class should inherit from the *ODESolver*. We note that the *ImplicitSolver* class inherits from the abstact class *ODESolver*. This class has to implement the *solve* method, which takes  step size *stepSize* and end time *t_end* as arguments. The *solve* method has to return a vector of *doubles*. 

 Note: The initial time *t0* and the initial value *y0* are already stored in the *ODESolver* class.

## Support
Having questions regarding the code? Write an issue


## Authors
Angelos Nikitaras & Tim Walter

