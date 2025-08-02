include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.8
)
FetchContent_MakeAvailable(Catch2)

add_executable(flowequations_tests tests.cpp flowequations_t.cpp)

target_compile_options(flowequations_tests PRIVATE
    $<$<COMPILE_LANGUAGE:CUDA>:--expt-extended-lambda; --expt-relaxed-constexpr>
)

target_include_directories(flowequations_tests PRIVATE
    ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
)

target_link_libraries(flowequations_tests PRIVATE
    flowequations
    devdat::devdat
    Catch2::Catch2
)

include(${catch2_SOURCE_DIR}/contrib/Catch.cmake)
catch_discover_tests(flowequations_tests)