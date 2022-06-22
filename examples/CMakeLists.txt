add_executable(flowequations_examples main.cpp src/lorentz_attractor_flow_equation.cu src/lorentz_attractor_jacobian_equation.cu)
target_link_libraries(flowequations_examples PRIVATE devdat::devdat flowequations)

target_compile_options(flowequations_examples PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--expt-extended-lambda; --expt-relaxed-constexpr>) 

target_include_directories(devdat_examples PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}>
    $<BUILD_INTERFACE:${json_SOURCE_DIR}/include/>
)