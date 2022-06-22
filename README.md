# Welcome to Flow Equation Interface

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub Workflow Status](https://img.shields.io/github/workflow/status/statphysandml/FlowEquationInterface/CI)](https://github.com/statphysandml/FlowEquationInterface/actions?query=workflow%3ACI)
[![codecov](https://codecov.io/gh/statphysandml/FlowEquationInterface/branch/main/graph/badge.svg)](https://codecov.io/gh/statphysandml/FlowEquationInterface)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=statphysandml_FlowEquationInterface&metric=alert_status)](https://sonarcloud.io/dashboard?id=statphysandml_FlowEquationInterface)

# Prerequisites

Building Flow Equation Interface requires the following software installed:

* A C++17-compliant compiler
* CMake `>= 3.15`
* Cuda `>=10.1`

# Building Flow Equation Interface

The following sequence of commands builds Flow Equation Interface.
It assumes that your current working directory is the top-level directory
of the freshly cloned repository:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

The build process can be customized with the following CMake variables,
which can be set by adding `-D<var>={ON, OFF}` to the `cmake` call:

* `BUILD_TESTING`: Enable building of the test suite (default: `ON`)



# Testing Flow Equation Interface

When built according to the above explanation (with `-DBUILD_TESTING=ON`),
the C++ test suite of `Flow Equation Interface` can be run using
`ctest` from the build directory:

```
cd build
ctest
```
# Building the example

The example directory demonstrates how the library can be integrated into a cmake project:

```
cd examples
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=~/FlowEquationInterface/install ..   
cmake --build .
```

Note that we have assumed here that the library was built beforehand locally by running the following commands in the top-level directory of the repository:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./../install ..    
make install -j9
```


# Documentation

ToDo

