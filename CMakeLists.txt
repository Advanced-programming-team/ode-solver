cmake_minimum_required(VERSION 3.23)
project(ode_solver)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

################################
# Fetching dependencies
################################
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip

)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

################################
# muParser
################################
SET( muParser_SRC
        deps/muParser.cpp
        deps/muParserBase.cpp
        deps/muParserBytecode.cpp
        deps/muParserCallback.cpp
        deps/muParserError.cpp
        deps/muParserTokenReader.cpp)

################################
# Unit Tests
################################
enable_testing()

add_executable(unit_test
        test/unit_test.cpp
        src/ODESolver.h
        src/ImplicitSolver.h
        src/ExplicitEuler.h
        src/ExplicitEuler.cpp
        src/ImplicitEuler.cpp
        src/ImplicitEuler.h
        src/RungeKutta.cpp
        src/RungeKutta.h
        src/utilities.cpp
        src/AdamsBashforthTwo.cpp
        src/AdamsBashforthTwo.h
        src/Heun.cpp
        src/Heun.h
        ${muParser_SRC})
target_link_libraries(unit_test GTest::gtest_main)

include(GoogleTest)
gtest_add_tests(unit_test "" AUTO)

################################
# Main executable
################################

add_executable(solver src/solver.cpp
        src/ODESolver.h
        src/ImplicitSolver.h
        src/ExplicitEuler.h
        src/ExplicitEuler.cpp
        src/ImplicitEuler.cpp
        src/ImplicitEuler.h
        src/RungeKutta.cpp
        src/RungeKutta.h
        src/utilities.h
        src/utilities.cpp
        src/AdamsBashforthTwo.cpp
        src/AdamsBashforthTwo.h
        src/Heun.cpp
        src/Heun.h
        ${muParser_SRC})

include_directories(deps/include)
target_link_libraries(solver nlohmann_json::nlohmann_json)

