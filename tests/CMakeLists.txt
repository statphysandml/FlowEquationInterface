add_executable(flowequations_tests tests.cpp flowequations_t.cpp)
target_link_libraries(flowequations_tests PUBLIC flowequations Catch2::Catch2)

target_compile_options(flowequations_tests PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--expt-extended-lambda; --expt-relaxed-constexpr>) 

# allow user to run tests with `make test` or `ctest`
catch_discover_tests(flowequations_tests)
