cmake_minimum_required(VERSION 3.15)

# Set a name and a version number for your project:
project(Example VERSION 0.0.1 LANGUAGES CXX CUDA)

# Initialize some default paths
include(GNUInstallDirs)

# Define the minimum C++ standard that is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include libraries
find_package(devdat CONFIG REQUIRED)
find_package(flowequations CONFIG REQUIRED)

add_executable(flowequations_examples main.cpp src/lorentz_attractor_flow_equation.cu src/lorentz_attractor_jacobian_equation.cu)

target_compile_options(flowequations_examples PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--expt-extended-lambda; --expt-relaxed-constexpr>)

target_link_libraries(flowequations_examples PRIVATE devdat::devdat flowequations::flowequations)

target_include_directories(flowequations_examples PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

# This prints a summary of found dependencies
include(FeatureSummary)
feature_summary(WHAT ALL)