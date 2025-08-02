#include <flowequations/flow_equation.hpp>
#include <catch2/catch.hpp>

using namespace flowequations;

TEST_CASE( "cuda_version", "[cuda]") {
    int driver_version , runtime_version;
    cudaDriverGetVersion( &driver_version );
    cudaRuntimeGetVersion ( &runtime_version );
    std::cout << driver_version << "\t" << runtime_version << std::endl;
}

/* TEST_CASE( "add_one", "[adder]" ){
  REQUIRE(add_one(0) == 1);
  REQUIRE(add_one(123) == 124);
  REQUIRE(add_one(-1) == 0);
} */