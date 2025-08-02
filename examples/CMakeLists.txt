cmake_minimum_required(VERSION 3.18)
project(flowequations_examples LANGUAGES CXX CUDA)

# Set C++ and CUDA standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Find the devdat package
find_package(devdat REQUIRED)

# Find the flowequations package
find_package(flowequations REQUIRED)

# Add CUDA directories
include_directories(include)

# Add the executable
add_executable(flowequations_examples
    main.cpp
    src/lorentz_attractor_flow_equation.cu
    src/lorentz_attractor_jacobian_equation.cu
)

# Link with devdat - all necessary include paths should come from this
target_link_libraries(flowequations_examples PRIVATE devdat::devdat flowequations::flowequations)